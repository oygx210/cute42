#include "WidgetHeaders/fovdialog.h"
#include "DataHeaders/fieldofview.h"
#include "DataHeaders/qt42_headers.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "ShareHeaders/qt42commands.h"
#include <QtWidgets>
#include "MVDheaders/qt42model.h"

FOVDialog::FOVDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("Fields of View"));
    if (parent)
        parentTabWidget = static_cast<QTabWidget*>(parent);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    m_undoStack = new QUndoStack(this);
    createWidgets();
    createActions();
    createConnections();
    QPalette* pal = new QPalette();
    pal->setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(*pal);
}

FOVDialog::~FOVDialog()
{

}

void FOVDialog::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    return;
}

void FOVDialog::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<FOVHeader>())
        return;
    m_index = index;
    m_FOVHeader = m_index.data().value<FOVHeader>();
    m_modelIndexMission = index.parent();
    m_modelIndexSCHeader = m_model->index(spacecraftHeaderRow, spacecraftHeaderColumn, m_modelIndexMission);
    mapDataFromModelToWidget();
    renewComboboxFOV();
    renewComboboxSC();
    comboboxSC->setCurrentIndex(0);
    comboboxSCB->setCurrentIndex(0);

    Mission m = m_modelIndexMission.data().value<Mission>();
    labelMissionForDialog->setText(tr("Mission: ") + m.name());
    editMission->setText(m.name());
    editDirectory->setText(m.directory());
    editNumberOfFOV->setText(QString::number(m_FOVHeader.numberOfFOV()));
    if (comboboxFOV->currentText().trimmed().isEmpty())
    {
        groupboxEdit1->setEnabled(false);
        groupboxEdit2->setEnabled(false);
        groupboxEdit3->setEnabled(false);
        btnRemoveFOV->setEnabled(false);
    }
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
}

void FOVDialog::createWidgets()
{
    QFormLayout* layoutDialog = new QFormLayout;
    QHBoxLayout* layoutTabWidgetDisplay = new QHBoxLayout;
    QVBoxLayout* layoutTabWidgetDisplayLeft = new QVBoxLayout;
    QLabel* labelGraphicsDisplay = new QLabel(tr("Left for Display."));

    labelMissionForDialog = new QLabel(labelMissionName);
    labelMissionForDialog->setStyleSheet("QLabel {color : white;}");
    labelFOVForDialog = new QLabel(tr("FOV: "));
    labelFOVForDialog->setStyleSheet("QLabel {color : white}");
    QHBoxLayout* layoutMissionFOVforDialog = new QHBoxLayout;
    layoutMissionFOVforDialog->addWidget(labelMissionForDialog,1);
    layoutMissionFOVforDialog->addWidget(labelFOVForDialog,1);

    tabWidgetFOV = new QTabWidget;
    fovPage1 = new QWidget(tabWidgetFOV);
    QVBoxLayout* layoutPage1 = new QVBoxLayout;
    fovPage2 = new QWidget(tabWidgetFOV);
    QVBoxLayout* layoutPage2 = new QVBoxLayout;
    fovPage3 = new QWidget(tabWidgetFOV);
    QVBoxLayout* layoutPage3 = new QVBoxLayout;

    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelDirectory = new QLabel(tr("Directory"));
    editDirectory = new QLineEdit;
    editDirectory->setReadOnly(true);
    labelNumberOfFOV = new QLabel(tr("Number of FOVs"));
    editNumberOfFOV = new QLineEdit();
    editNumberOfFOV->setReadOnly(true);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelDirectory, editDirectory);
    layoutDetails->addRow(labelNumberOfFOV, editNumberOfFOV);
    groupBoxDetails->setLayout(layoutDetails);

    groupboxFOV = new QGroupBox(tr("Select/Create/Remove FOV"));
    groupboxFOV->setAlignment(Qt::AlignCenter);
    QGridLayout* layoutFOV = new QGridLayout;
    labelFOV = new QLabel(tr("Field of View"));
    comboboxFOV = new QComboBox;
    btnCreateFOV = new QPushButton(tr("Create"));
    btnRemoveFOV = new QPushButton(tr("Remove"));
    layoutFOV->addWidget(labelFOV, 0,0 ,1,1);
    layoutFOV->addWidget(comboboxFOV, 0,1, 1, 1);
    layoutFOV->addWidget(btnCreateFOV, 1,0 ,1 ,1);
    layoutFOV->addWidget(btnRemoveFOV, 1,1 ,1 ,1);
    groupboxFOV->setLayout(layoutFOV);

    groupboxEdit1 = new QGroupBox(tr("Edit"));
    groupboxEdit1->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutEdit1 = new QFormLayout;
    groupboxEdit2 = new QGroupBox(tr("Edit-Continued"));
    groupboxEdit2->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutEdit2 = new QFormLayout;
    groupboxEdit3 = new QGroupBox(tr("Edit-Continued"));
    groupboxEdit3->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutEdit3 = new QFormLayout;

    labellabel = new QLabel(tr("Label"));
    editLabel = new QLineEdit();

    groupboxSides = new QGroupBox(tr("Sides"));
    QHBoxLayout* layoutSides = new QHBoxLayout;
    labelNumberOfSides = new QLabel(tr("Number of Sides"));
    spinBoxNumberOfSides = new QSpinBox;
    labelLengthOfSides = new QLabel(tr("Length of Sides [m]"));
    dblSpinBoxLengthOfSides = new QDoubleSpinBox();
    layoutSides->addWidget(labelNumberOfSides);
    layoutSides->addWidget(spinBoxNumberOfSides);
    layoutSides->addWidget(labelLengthOfSides);
    layoutSides->addWidget(dblSpinBoxLengthOfSides);
    layoutSides->setStretch(0,1);
    layoutSides->setStretch(1,2);
    layoutSides->setStretch(2,1);
    layoutSides->setStretch(3,2);
    groupboxSides->setLayout(layoutSides);

    groupboxWidthHeight = new QGroupBox;
    QHBoxLayout* layoutWidthHeight = new QHBoxLayout;
    labelXWidth = new QLabel(tr("X Width [deg]"));
    dblSpinBoxXWidth = new QDoubleSpinBox();
    labelYHeight = new QLabel(tr("Y Height [deg]"));
    dblSpinBoxYHeight = new QDoubleSpinBox();
    layoutWidthHeight->addWidget(labelXWidth);
    layoutWidthHeight->addWidget(dblSpinBoxXWidth);
    layoutWidthHeight->addWidget(labelYHeight);
    layoutWidthHeight->addWidget(dblSpinBoxYHeight);
    groupboxWidthHeight->setLayout(layoutWidthHeight);

    groupboxRGB_ALPHA = new QGroupBox(tr("Color RGB/") + QString::fromUtf8("\u03B1"));
    QHBoxLayout* layoutColor = new QHBoxLayout;
    labelRGB_R = new QLabel(tr("R"));
    dblSpinBoxRGB_R = new QDoubleSpinBox();
    labelRGB_G = new QLabel(tr("G"));
    dblSpinBoxRGB_G = new QDoubleSpinBox();
    labelRGB_B = new QLabel(tr("B"));
    dblSpinBoxRGB_B = new QDoubleSpinBox();
    labelRGB_Alpha = new QLabel(QString::fromUtf8("\u03B1"));
    dblSpinBoxRGB_Alpha = new QDoubleSpinBox();
    layoutColor->addWidget(labelRGB_R);
    layoutColor->addWidget(dblSpinBoxRGB_R);
    layoutColor->addWidget(labelRGB_G);
    layoutColor->addWidget(dblSpinBoxRGB_G);
    layoutColor->addWidget(labelRGB_B);
    layoutColor->addWidget(dblSpinBoxRGB_B);
    layoutColor->addWidget(labelRGB_Alpha);
    layoutColor->addWidget(dblSpinBoxRGB_Alpha);
    layoutColor->setStretch(0,1);
    layoutColor->setStretch(1,2);
    layoutColor->setStretch(2,1);
    layoutColor->setStretch(3,2);
    layoutColor->setStretch(4,1);
    layoutColor->setStretch(5,2);
    layoutColor->setStretch(6,1);
    layoutColor->setStretch(7,2);
    groupboxRGB_ALPHA->setLayout(layoutColor);

    labelDrawing = new QLabel(tr("Drawing"));
    comboboxDrawing = new QComboBox();
    comboboxDrawing->clear();
    comboboxDrawing->addItems(list_FOV_Drawing);

    groupboxDrawField = new QGroupBox();
    QHBoxLayout* layoutDrawField = new QHBoxLayout;
    chkbxDrawNearField = new QCheckBox(tr("Draw Near Field"));
    chkbxDrawFarField = new QCheckBox(tr("Draw Far Field"));
    layoutDrawField->addWidget(chkbxDrawNearField);
    layoutDrawField->addWidget(chkbxDrawFarField);
    layoutDrawField->setStretch(0,1);
    layoutDrawField->setStretch(1,1);
    groupboxDrawField->setLayout(layoutDrawField);

    groupboxSC_SCB = new QGroupBox;
    QFormLayout* layoutSC_SCB = new QFormLayout;
    labelSC = new QLabel(tr("Spacecraft"));
    comboboxSC = new QComboBox();
    labelSCB = new QLabel(tr("Body"));
    comboboxSCB = new QComboBox();
    layoutSC_SCB->addRow(labelSC,comboboxSC);
    layoutSC_SCB->addRow(labelSCB,comboboxSCB);
    groupboxSC_SCB->setLayout(layoutSC_SCB);


    groupboxPositionBody = new QGroupBox(tr("Position in Body [m]"));
    QHBoxLayout* layoutPositionBody = new QHBoxLayout;
    labelPositionBody1 = new QLabel(tr("x")+QString::fromUtf8("\u2081"));
    dblSpinBoxPositionBody1 = new QDoubleSpinBox();
    dblSpinBoxPositionBody1->setRange(-10000.0,10000.0);
    dblSpinBoxPositionBody1->setWrapping(true);
    labelPositionBody2 = new QLabel(tr("x")+QString::fromUtf8("\u2082"));
    dblSpinBoxPositionBody2 = new QDoubleSpinBox();
    dblSpinBoxPositionBody2->setRange(-10000.0,10000.0);
    dblSpinBoxPositionBody2->setWrapping(true);
    labelPositionBody3 = new QLabel(tr("x")+QString::fromUtf8("\u2083"));
    dblSpinBoxPositionBody3 = new QDoubleSpinBox();
    dblSpinBoxPositionBody3->setRange(-10000.0,10000.0);
    dblSpinBoxPositionBody3->setWrapping(true);
    layoutPositionBody->addWidget(labelPositionBody1);
    layoutPositionBody->addWidget(dblSpinBoxPositionBody1);
    layoutPositionBody->addWidget(labelPositionBody2);
    layoutPositionBody->addWidget(dblSpinBoxPositionBody2);
    layoutPositionBody->addWidget(labelPositionBody3);
    layoutPositionBody->addWidget(dblSpinBoxPositionBody3);
    layoutPositionBody->setStretch(0,1);
    layoutPositionBody->setStretch(1,2);
    layoutPositionBody->setStretch(2,1);
    layoutPositionBody->setStretch(3,2);
    layoutPositionBody->setStretch(4,1);
    layoutPositionBody->setStretch(5,2);
    groupboxPositionBody->setLayout(layoutPositionBody);

    groupboxEulerAngleSeq = new QGroupBox(tr("Euler Angles [deg] and Sequence"));
    QGridLayout* layoutEulerAngelSeq = new QGridLayout;
    labelEulerAngle1 = new QLabel(QString::fromUtf8("\u03B8\u2081"));
    dblSpinBoxEulerAngle1 = new QDoubleSpinBox;
    labelEulerAngle2 = new QLabel(QString::fromUtf8("\u03B8\u2082"));
    dblSpinBoxEulerAngle2 = new QDoubleSpinBox;
    labelEulerAngle3 = new QLabel(QString::fromUtf8("\u03B8\u2083"));
    dblSpinBoxEulerAngle3 = new QDoubleSpinBox;
    labelEulerSeq = new QLabel(tr("Euler Seq."));
    comboboxEulerSeq = new QComboBox();
    comboboxEulerSeq->clear();
    comboboxEulerSeq->addItems(list_EulerSeq);
    layoutEulerAngelSeq->addWidget(labelEulerAngle1, 0, 0, 1, 1);
    layoutEulerAngelSeq->addWidget(labelEulerAngle2, 0, 1, 1, 1);
    layoutEulerAngelSeq->addWidget(labelEulerAngle3, 0, 2, 1, 1);
    layoutEulerAngelSeq->addWidget(labelEulerSeq   , 0, 3, 1, 1);
    layoutEulerAngelSeq->addWidget(dblSpinBoxEulerAngle1, 1, 0, 1, 1);
    layoutEulerAngelSeq->addWidget(dblSpinBoxEulerAngle2, 1, 1, 1, 1);
    layoutEulerAngelSeq->addWidget(dblSpinBoxEulerAngle3, 1, 2, 1, 1);
    layoutEulerAngelSeq->addWidget(comboboxEulerSeq, 1, 3, 1, 1);
    groupboxEulerAngleSeq->setLayout(layoutEulerAngelSeq);

    QHBoxLayout* layoutBtnOk = new QHBoxLayout;
    btnEditOk = new QPushButton(tr("OK"));
    btnEditOk->setMaximumWidth(120);
    layoutBtnOk->addWidget(btnEditOk);
    layoutEdit1->addRow(labellabel, editLabel);
    layoutEdit1->addRow(groupboxSides);

    groupboxEdit1->setLayout(layoutEdit1);
    layoutPage1->addWidget(groupBoxDetails);
    layoutPage1->addWidget(groupboxFOV);
    layoutPage1->addWidget(groupboxEdit1);
    fovPage1->setLayout(layoutPage1);

    layoutEdit2->addRow(groupboxWidthHeight);
    layoutEdit2->addRow(groupboxRGB_ALPHA);
    layoutEdit2->addRow(labelDrawing, comboboxDrawing);
    layoutEdit2->addRow(groupboxDrawField);
    groupboxEdit2->setLayout(layoutEdit2);
    layoutPage2->addWidget(groupboxEdit2);
    fovPage2->setLayout(layoutPage2);


    layoutEdit3->addRow(groupboxSC_SCB);
    layoutEdit3->addRow(groupboxPositionBody);
    layoutEdit3->addRow(groupboxEulerAngleSeq);
    groupboxEdit3->setLayout(layoutEdit3);
    layoutPage3->addWidget(groupboxEdit3);
    fovPage3->setLayout(layoutPage3);

    tabWidgetFOV->addTab(fovPage1, tr("Details/Edit"));
    tabWidgetFOV->addTab(fovPage2, tr("Edit"));
    tabWidgetFOV->addTab(fovPage3, tr("Edit"));

    layoutTabWidgetDisplayLeft->addWidget(tabWidgetFOV);
    layoutTabWidgetDisplayLeft->addWidget(btnEditOk);

    layoutTabWidgetDisplay->addLayout(layoutTabWidgetDisplayLeft);
    layoutTabWidgetDisplay->addWidget(labelGraphicsDisplay);
    layoutTabWidgetDisplay->setStretch(0,1);
    layoutTabWidgetDisplay->setStretch(1,1);

    layoutDialog->addRow(layoutMissionFOVforDialog);
    layoutDialog->addRow(layoutTabWidgetDisplay);
    layoutDialog->addRow(m_buttonBox);
    setLayout(layoutDialog);
}

void FOVDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void FOVDialog::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);

    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Save),
            [=](){m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_undoAction, &QAction::triggered, this, [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(btnCreateFOV, &QPushButton::clicked, this, &FOVDialog::createFOV);
    connect(btnRemoveFOV, &QPushButton::clicked, this, &FOVDialog::removeFOV);
    connect(comboboxFOV, &QComboBox::currentTextChanged, this, &FOVDialog::renewLabelFOV);
    connect(comboboxFOV, &QComboBox::currentTextChanged, this, &FOVDialog::mapDataForSelectedFOV);
    connect(comboboxSC, &QComboBox::currentTextChanged, this, &FOVDialog::currentSC);
    connect(this, &FOVDialog::currentModelIndexSC, this, &FOVDialog::renewComboboxSCB);
    connect(btnEditOk, &QPushButton::clicked, this, &FOVDialog::editCurrentFOV);

    connect(editNumberOfFOV, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLabel, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinBoxNumberOfSides, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxLengthOfSides, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxXWidth, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxYHeight, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxRGB_R, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxRGB_G, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxRGB_B, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxRGB_Alpha, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxDrawing, &QComboBox::currentTextChanged,
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxDrawNearField, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxDrawFarField, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxSC, &QComboBox::currentTextChanged,
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxSCB, &QComboBox::currentTextChanged,
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxPositionBody1, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxPositionBody2, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxPositionBody3, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxEulerAngle1, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxEulerAngle2, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxEulerAngle3, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxEulerSeq, &QComboBox::currentTextChanged,
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(btnEditOk, &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void FOVDialog::createFOV()
{
    comboboxFOV->setEnabled(true);
    QString currentNameFOV = comboboxFOV->currentText().trimmed();
    m_FOVHeader.createFOV();
    comboboxSC->setCurrentIndex(0);
    renewComboboxFOV();
    comboboxFOV->setCurrentText(currentNameFOV);
    editNumberOfFOV->setText(QString::number(m_FOVHeader.numberOfFOV()));
}

void FOVDialog::removeFOV()
{
    if (comboboxFOV->currentText().trimmed().isEmpty())
        return;

    QString nameFOV = comboboxFOV->currentText().trimmed();
    for (int i = 0; i < m_FOVHeader.numberOfFOV(); ++i)
    {
        if (m_FOVHeader.qvecFieldsOfView[i].label().trimmed() == nameFOV)
        {
            m_FOVHeader.removeFOV(i);
            --i;
        }
    }
    renewComboboxFOV();
    comboboxFOV->setCurrentIndex(0);
    editNumberOfFOV->setText(QString::number(m_FOVHeader.numberOfFOV()));
}


void FOVDialog::renewLabelFOV(const QString& labelFOV)
{
    labelFOVForDialog->setText(tr("FOV: ") + labelFOV);
    labelFOVForDialog->setStyleSheet("QLabel {color: white;}");
}

void FOVDialog::mapDataFromModelToWidget()
{

}

void FOVDialog::mapDataFromWidgetToModel()
{
    QVariant newData = QVariant();
    newData.setValue(m_FOVHeader);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
}

void FOVDialog::currentSC(const QString& nameSC)
{
    QModelIndex modelIndexSCHeader = m_model->index(0,0,m_index.parent());
    //SpacecraftHeader sch = m_modelIndexSCHeader.data().value<SpacecraftHeader>();
    SpacecraftHeader sch = modelIndexSCHeader.data().value<SpacecraftHeader>();
    QModelIndex emittedModelIndex = QModelIndex();
    for (int i = 0; i < sch.numberOfSpacecraft(); ++i)
    {
        QModelIndex modelIndexSC = m_model->index(i, 0, m_modelIndexSCHeader);
        Spacecraft sc = modelIndexSC.data().value<Spacecraft>();
        if (nameSC.trimmed() == sc.name().trimmed())
        {
            emittedModelIndex = modelIndexSC;
            break;
        }
    }
    emit currentModelIndexSC(emittedModelIndex);
    return;
}

void FOVDialog::renewComboboxSCB(const QModelIndex& modelIndexSC)
{
    if (!m_index.data().canConvert<FOVHeader>())
        return;
    comboboxSCB->clear();
    list_SCB.clear();
    list_SCB.append(tr(""));
    Spacecraft SC = modelIndexSC.data().value<Spacecraft>();
    for (int i = 0; i < SC.numberOfBodies(); ++i)
    {
        QModelIndex modelIndexSCB = m_model->index(SC.rowSPACECRAFTBODY(), i, modelIndexSC);
        SpacecraftBody scb = modelIndexSCB.data().value<SpacecraftBody>();
        if (scb.includedInCalculation())
            list_SCB.append(scb.name().trimmed());
    }
    comboboxSCB->addItems(list_SCB);
    comboboxSCB->setCurrentText(tr(""));
}

void FOVDialog::renewComboboxSC()
{
    if (!m_index.data().canConvert<FOVHeader>())
        return;
    comboboxSC->clear();
    list_SC.clear();
    list_SC.append(tr(""));
    QModelIndex ModelIndexMission = m_index.parent();
    Mission m = ModelIndexMission.data().value<Mission>();
    QModelIndex ModelIndexSCH = m_model->index(0,0,ModelIndexMission);
    SpacecraftHeader sch = ModelIndexSCH.data().value<SpacecraftHeader>();
    for (int i = 0; i < sch.numberOfSpacecraft(); ++i)
    {
        QModelIndex ModelIndexSC = m_model->index(i,0,ModelIndexSCH);
        Spacecraft SC = ModelIndexSC.data().value<Spacecraft>();
        if (SC.includedInCalculation())
            list_SC.append(SC.name().trimmed());
    }
    comboboxSC->addItems(list_SC);
}

void FOVDialog::renewComboboxFOV()
{
    comboboxFOV->clear();
    list_FOVLabel.clear();
    list_FOVLabel.append(tr(""));
    for (FieldOfView f : m_FOVHeader.qvecFieldsOfView)
    {
        list_FOVLabel.append(f.label().trimmed());
    }
    comboboxFOV->addItems(list_FOVLabel);
}

void FOVDialog::mapDataForSelectedFOV(const QString& comboboxText)
{
    if (comboboxText.trimmed().isEmpty())
    {
        resetWidgets();
        btnRemoveFOV->setEnabled(false);
        groupboxEdit1->setEnabled(false);
        groupboxEdit2->setEnabled(false);
        groupboxEdit3->setEnabled(false);
        return;
    }
    groupboxEdit1->setEnabled(true);
    groupboxEdit2->setEnabled(true);
    groupboxEdit3->setEnabled(true);
    btnRemoveFOV->setEnabled(true);
    QString labelFOV = comboboxText.trimmed();
    if (labelFOV.isEmpty())
        return;
    FieldOfView fieldOfView;
    SpacecraftHeader sch = m_modelIndexSCHeader.data().value<SpacecraftHeader>();
    QString nameSC = tr("");
    Spacecraft sc;
    if (fieldOfView.indexSC() != -1)
    {
        m_modelIndexSC = m_model->index(fieldOfView.indexSC(), spacecraftColumn, m_modelIndexSCHeader);
        sc = m_modelIndexSC.data().value<Spacecraft>();
        nameSC = sc.name().trimmed();
    }

    QString nameSCB = tr("");
    SpacecraftBody scb;
    if (fieldOfView.indexSC() != -1 && fieldOfView.indexSCB() != -1)
    {
        QModelIndex modelIndexSCB = m_model->index(sc.rowSPACECRAFTBODY(), fieldOfView.indexSCB(),                                               m_modelIndexSC);
        scb = modelIndexSCB.data().value<SpacecraftBody>();
        nameSCB = scb.name().trimmed();
    }
    for (int i = 0; i < m_FOVHeader.numberOfFOV(); ++i)
    {
        if (m_FOVHeader.qvecFieldsOfView[i].label() == labelFOV)
        {
            fieldOfView = m_FOVHeader.qvecFieldsOfView[i];
            break;
        }
    }
    editLabel->setText(fieldOfView.label().trimmed());
    spinBoxNumberOfSides->setValue(fieldOfView.numberOfSides());
    dblSpinBoxLengthOfSides->setValue(fieldOfView.lengthOfSides());
    dblSpinBoxXWidth->setValue(fieldOfView.X_Width());
    dblSpinBoxYHeight->setValue(fieldOfView.Y_Height());
    dblSpinBoxRGB_R->setValue(fieldOfView.colorRGB_R());
    dblSpinBoxRGB_G->setValue(fieldOfView.colorRGB_G());
    dblSpinBoxRGB_B->setValue(fieldOfView.colorRGB_B());
    dblSpinBoxRGB_Alpha->setValue(fieldOfView.colorRGB_Alpha());
    QString drawing = fieldOfView.drawing().trimmed().toLower();
    drawing[0] = drawing[0].toUpper();
    comboboxDrawing->setCurrentText(drawing);
    chkbxDrawNearField->setChecked(fieldOfView.drawNearField());
    chkbxDrawFarField->setChecked(fieldOfView.drawFarField());
    comboboxSC->setCurrentText(nameSC);
    comboboxSCB->setCurrentText(nameSCB);
    dblSpinBoxPositionBody1->setValue(fieldOfView.qvecPositionInBody()[0]);
    dblSpinBoxPositionBody2->setValue(fieldOfView.qvecPositionInBody()[1]);
    dblSpinBoxPositionBody3->setValue(fieldOfView.qvecPositionInBody()[2]);
    dblSpinBoxEulerAngle1->setValue(fieldOfView.qvecEulerAngles()[0]);
    dblSpinBoxEulerAngle2->setValue(fieldOfView.qvecEulerAngles()[1]);
    dblSpinBoxEulerAngle3->setValue(fieldOfView.qvecEulerAngles()[2]);
    comboboxEulerSeq->setCurrentText(fieldOfView.EulerAngleSeq().trimmed());
}

void FOVDialog::resetWidgets()
{
    labelFOVForDialog->setText(tr("FOV: "));
    FieldOfView fieldOfView;
    editLabel->setText(fieldOfView.label().trimmed());
    spinBoxNumberOfSides->setValue(fieldOfView.numberOfSides());
    dblSpinBoxLengthOfSides->setValue(fieldOfView.lengthOfSides());
    dblSpinBoxXWidth->setValue(fieldOfView.X_Width());
    dblSpinBoxYHeight->setValue(fieldOfView.Y_Height());
    dblSpinBoxRGB_R->setValue(fieldOfView.colorRGB_R());
    dblSpinBoxRGB_G->setValue(fieldOfView.colorRGB_G());
    dblSpinBoxRGB_B->setValue(fieldOfView.colorRGB_B());
    dblSpinBoxRGB_Alpha->setValue(fieldOfView.colorRGB_Alpha());
    QString drawing = fieldOfView.drawing().trimmed().toLower();
    drawing[0] = drawing[0].toUpper();
    comboboxDrawing->setCurrentText(drawing);
    chkbxDrawNearField->setChecked(fieldOfView.drawNearField());
    chkbxDrawFarField->setChecked(fieldOfView.drawFarField());
    comboboxSC->setCurrentText(tr(""));
    comboboxSCB->setCurrentText(tr(""));
    dblSpinBoxPositionBody1->setValue(fieldOfView.qvecPositionInBody()[0]);
    dblSpinBoxPositionBody2->setValue(fieldOfView.qvecPositionInBody()[1]);
    dblSpinBoxPositionBody3->setValue(fieldOfView.qvecPositionInBody()[2]);
    dblSpinBoxEulerAngle1->setValue(fieldOfView.qvecEulerAngles()[0]);
    dblSpinBoxEulerAngle2->setValue(fieldOfView.qvecEulerAngles()[1]);
    dblSpinBoxEulerAngle3->setValue(fieldOfView.qvecEulerAngles()[2]);
    comboboxEulerSeq->setCurrentText(fieldOfView.EulerAngleSeq().trimmed());
}

void FOVDialog::editCurrentFOV()
{
    QString currentlabel = comboboxFOV->currentText().trimmed();
    if (currentlabel.isEmpty())
        return;
    int indexFOV = -1;
    for (int i = 0; i < m_FOVHeader.numberOfFOV(); ++i)
    {
        if (currentlabel == m_FOVHeader.qvecFieldsOfView[i].label().trimmed())
        {
            indexFOV = i;
            break;
        }
    }

    SpacecraftHeader sch = m_modelIndexSCHeader.data().value<SpacecraftHeader>();
    QString nameSC = comboboxSC->currentText().trimmed();
    QString nameSCB = comboboxSCB->currentText().trimmed();
    int indexSC = -1;
    int indexSCB = -1;
    QModelIndex modelIndexSC = QModelIndex();
    for (int i = 0; i < sch.numberOfSpacecraft();++i)
    {
        modelIndexSC = m_model->index(i,0,m_modelIndexSCHeader);
        Spacecraft SC = modelIndexSC.data().value<Spacecraft>();
        if (SC.name().trimmed() == nameSC)
        {
            indexSC = i;
            break;
        }
    }

    Spacecraft SC = modelIndexSC.data().value<Spacecraft>();
    for (int i = 0; i < SC.numberOfBodies(); ++i)
    {
        QModelIndex modelIndexSCB = m_model->index(SC.rowSPACECRAFTBODY(), i, modelIndexSC);
        SpacecraftBody scb = modelIndexSCB.data().value<SpacecraftBody>();
        if (scb.name().trimmed() == nameSCB)
        {
            indexSCB = i;
            break;
        }
    }
    QVector<double> vecPositionInBody{dblSpinBoxPositionBody1->value(),dblSpinBoxPositionBody2->value(), dblSpinBoxPositionBody3->value()};
    QVector<double> vecEulerAngles{dblSpinBoxEulerAngle1->value(),dblSpinBoxEulerAngle2->value(),dblSpinBoxEulerAngle3->value()};

    QString modifiedLabel = editLabel->text().trimmed();
    for (int i = 0; i < m_FOVHeader.numberOfFOV(); ++i)
    {
        QString label = m_FOVHeader.qvecFieldsOfView[i].label().trimmed();
        if (modifiedLabel == label && i != indexFOV)
        {
            modifiedLabel = currentlabel;
            QMessageBox* msg = new QMessageBox();
            msg->setWindowTitle(tr("FOV Already Exitsted"));
            msg->setIcon(QMessageBox::Information);
            msg->setStandardButtons(QMessageBox::Ok);
            msg->setText(tr("FOV \"")+modifiedLabel+tr("\"") + tr("\nalready existed."));
            msg->exec();
            editLabel->setText(currentlabel);
        }
    }
    m_FOVHeader.qvecFieldsOfView[indexFOV].edit(modifiedLabel,
                                                spinBoxNumberOfSides->value(),
                                                dblSpinBoxLengthOfSides->value(),
                                                dblSpinBoxXWidth->value(),
                                                dblSpinBoxYHeight->value(),
                                                dblSpinBoxRGB_R->value(),
                                                dblSpinBoxRGB_G->value(),
                                                dblSpinBoxRGB_B->value(),
                                                dblSpinBoxRGB_Alpha->value(),
                                                comboboxDrawing->currentText().trimmed().toUpper(),
                                                chkbxDrawNearField->isChecked(),
                                                chkbxDrawFarField->isChecked(),
                                                indexSC, indexSCB,
                                                vecPositionInBody,
                                                vecEulerAngles, comboboxEulerSeq->currentText().trimmed());

    if (currentlabel != modifiedLabel)
    {
        list_FOVLabel.replace(indexFOV+1, modifiedLabel);
        comboboxFOV->clear();
        comboboxFOV->addItems(list_FOVLabel);
        comboboxFOV->setCurrentIndex(indexFOV+1);
        labelFOVForDialog->setText(tr("FOV: ") + modifiedLabel);
    }
}
