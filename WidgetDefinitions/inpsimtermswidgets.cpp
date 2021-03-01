#include "WidgetHeaders/inpsimtermswidgets.h"
#include "MVDheaders/qt42model.h"
#include "ShareHeaders/qt42commands.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "DataHeaders/mission.h"
#include "DataHeaders/qt42_headers.h"
#include "WidgetHeaders/qt42dragwidget.h"
#include <QUndoStack>
#include <QDialogButtonBox>
#include <QAction>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QDoubleValidator>
#include <QTimeEdit>
#include <QDate>
#include <QTime>
#include <QDateEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDebug>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QStringListModel>
#include <QButtonGroup>
#include <QMessageBox>
#include <QTextEdit>

/** Widget for Simulation Controls Data **/
InpSimSimCtrlDialog::InpSimSimCtrlDialog(QWidget* parent) : QDialog(parent)
{
    if (parent)
        tabWidgetParent = static_cast<QTabWidget*>(parent);
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(pal);

}

InpSimSimCtrlDialog::~InpSimSimCtrlDialog()
{

}

void InpSimSimCtrlDialog::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    else
        m_model = nullptr;
}

void InpSimSimCtrlDialog::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<InpSimSimulationControl >()){
        m_index = QModelIndex();
        return;
    }
    m_index = index;
    mapDataFromModelToWidget();
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    QModelIndex modelIndexMission = m_index.parent().parent();
    Mission mission = modelIndexMission.data().value<Mission>();

    m_model->disconnect(editMission);
    mission = modelIndexMission.data().value<Mission>();
}

void InpSimSimCtrlDialog::createWidgets()
{
    labelMissionForDialog = new QLabel(tr("Mission: "));
    labelMissionForDialog->setStyleSheet("QLabel {Color: white;}");

    tabWidget = new QTabWidget;
    QBoxLayout* layoutDialog = new QVBoxLayout;
    widgetPage1 = new QWidget();
    QHBoxLayout* layoutWidgetPage1 = new QHBoxLayout;
    widgetPage2 = new QWidget();
    QVBoxLayout* layoutWidgetPage2 = new QVBoxLayout;

    groupboxDetails = new QGroupBox(tr("Details"));
    groupboxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit();
    editMission->setReadOnly(true);
    labelDirectory = new QLabel(tr("Directory"));
    editDirectory = new QLineEdit();
    editDirectory->setReadOnly(true);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelDirectory, editDirectory);
    groupboxDetails->setLayout(layoutDetails);

    groupboxEdit = new QGroupBox(tr("Edit"));
    groupboxEdit->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutEdit = new QFormLayout;
    labelTimeMode = new QLabel(tr("Time Mode"));
    comboboxTimeMode = new QComboBox();
    comboboxTimeMode->addItems(list_SimTimeMode);
    labelSimDuration = new QLabel(tr("Sim Duration [sec]"));
    dblSpinboxSimDuration = new QDoubleSpinBox();
    dblSpinboxSimDuration->setRange(0, maxSimDuration);
    labelStepSize = new QLabel(tr("Step Size [sec]"));
    dblSpinboxStepSize = new QDoubleSpinBox();
    labelFileOutputInterval = new QLabel(tr("File Output Interval [sec]"));
    dblSpinboxFileOutputInterval = new QDoubleSpinBox();
    chkbxGraphicsFrontEnd = new QCheckBox(tr("Graphics Front End"));

    layoutEdit->addRow(labelTimeMode, comboboxTimeMode);
    layoutEdit->addRow(labelSimDuration, dblSpinboxSimDuration);
    layoutEdit->addRow(labelStepSize, dblSpinboxStepSize);
    layoutEdit->addRow(labelFileOutputInterval, dblSpinboxFileOutputInterval);
    layoutEdit->addRow(chkbxGraphicsFrontEnd);
    groupboxEdit->setLayout(layoutEdit);

    layoutWidgetPage1->addWidget(groupboxDetails,1);
    layoutWidgetPage1->addWidget(groupboxEdit,1);

    editSimCommand = new QTextEdit;
    layoutWidgetPage2->addWidget(editSimCommand);

    widgetPage1->setLayout(layoutWidgetPage1);
    widgetPage2->setLayout(layoutWidgetPage2);

    tabWidget->addTab(widgetPage1, tr("Details/Edit"));
    tabWidget->addTab(widgetPage2, tr("Commands"));
    layoutDialog->addWidget(labelMissionForDialog);
    layoutDialog->addWidget(tabWidget);
    layoutDialog->addWidget(m_buttonBox);
    setLayout(layoutDialog);
}

void InpSimSimCtrlDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void InpSimSimCtrlDialog::createConnections()
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

    connect(comboboxTimeMode, &QComboBox::currentTextChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxSimDuration, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxStepSize, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(dblSpinboxFileOutputInterval, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(chkbxGraphicsFrontEnd, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

bool InpSimSimCtrlDialog::mapDataFromWidgetToModel()
{
    InpSimSimulationControl newISSC = m_index.data().value<InpSimSimulationControl>();
    QString timeModeFromNewISSC = comboboxTimeMode->currentText().trimmed();
    timeModeFromNewISSC = timeModeFromNewISSC.toUpper();
    newISSC.edit(timeModeFromNewISSC,
                 dblSpinboxSimDuration->value(), dblSpinboxStepSize->value(),
                 dblSpinboxFileOutputInterval->value(),
                 chkbxGraphicsFrontEnd->isChecked());
    QVariant newData = QVariant();
    newData.setValue(newISSC);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}

bool InpSimSimCtrlDialog::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<InpSimSimulationControl>())
        return false;

    InpSimSimulationControl issc = m_index.data().value<InpSimSimulationControl>();
    Mission mission = m_index.parent().parent().data().value<Mission>();
    QString timeModeFromModel = issc.timeMode().trimmed().toLower();
    timeModeFromModel[0] = timeModeFromModel[0].toUpper();
    if (timeModeFromModel == "Nos3")
        timeModeFromModel = timeModeFromModel.toUpper();
    editMission->setText(mission.name().trimmed());
    editDirectory->setText(mission.directory().trimmed());
    labelMissionForDialog->setText(tr("Mission: ")+mission.name());
    comboboxTimeMode->setCurrentText(timeModeFromModel);
    dblSpinboxSimDuration->setValue(issc.simDuration());
    dblSpinboxStepSize->setValue(issc.stepSize());
    dblSpinboxFileOutputInterval->setValue(issc.fileOuputInterval());
    chkbxGraphicsFrontEnd->setChecked(issc.graphicsFrontEnd());
    return true;
}

/** Widget for Orbit-Spacecraft Set Data **/
InpSimOrbitSCSetDialog::InpSimOrbitSCSetDialog(QWidget* parent) : QDialog(parent)
{
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save  |
                                       QDialogButtonBox::Apply |
                                       QDialogButtonBox::Cancel);

    createWidgets();
    createActions();
    createConnections();
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::gray);
    setAutoFillBackground(true);
    setPalette(pal);
}

InpSimOrbitSCSetDialog::~InpSimOrbitSCSetDialog()
{

}

void InpSimOrbitSCSetDialog::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    else
        m_model = nullptr;
}

void InpSimOrbitSCSetDialog::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<InpSimOrbitSCSet>()){
        m_index = QModelIndex();
        m_inpSimOrbitSCSet = InpSimOrbitSCSet();
        return;
    }

    m_index = index;
    //m_inpSimOrbitSCSet = index.data().value<InpSimOrbitSCSet>();
    mapDataFromModelToWidget();
}

void InpSimOrbitSCSetDialog::createWidgets()
{
    QVBoxLayout* layoutAll = new QVBoxLayout;
    QHBoxLayout* layoutTop = new QHBoxLayout;
    QHBoxLayout* layoutMiddle = new QHBoxLayout;

    QFont fontMission("Arial", 14, QFont::Bold);
    labelMission = new QLabel(tr("Mission: "), this);
    labelMission->setFont(fontMission);

    QFormLayout* layoutNumberOfSC = new QFormLayout;
    labelNumberOfSets = new QLabel(tr("Number of Sets"), this);
    editNumberOfSets = new QLineEdit;
    editNumberOfSets->setValidator(new QIntValidator);
    editNumberOfSets->setReadOnly(true);
    editNumberOfSets->setMaximumWidth(200);
    layoutNumberOfSC->addRow(labelNumberOfSets, editNumberOfSets);

    layoutTop->addWidget(labelMission,1);

    QHBoxLayout* layoutSC = new QHBoxLayout;
    QFormLayout* layoutSCSelect = new QFormLayout;

    labelSC = new QLabel(tr("Spacecraft"), this);
    comboboxSC = new QComboBox(this);
    comboboxSC->setMaximumWidth(200);

    layoutSCSelect->addRow(labelSC, comboboxSC);
    layoutSC->addLayout(layoutSCSelect,1);
    layoutSC->addLayout(layoutNumberOfSC,1);

    QHBoxLayout* layoutDropWidgetBtns = new QHBoxLayout;
    layoutDropWidgetBtns->setAlignment(Qt::AlignLeft);
    btnAlign = new QPushButton(tr("A&lign"));
    btnAlign->setMaximumWidth(160);
    btnClearAll = new QPushButton(tr("Clear Selected Orbits"));
    btnClearAll->setMaximumWidth(160);
    layoutDropWidgetBtns->addWidget(btnAlign, 1);
    layoutDropWidgetBtns->addWidget(btnClearAll, 1);

    QVBoxLayout* layoutOrbitDrag = new QVBoxLayout;
    QVBoxLayout* layoutOrbitDrop = new QVBoxLayout;
    QFont fontGroupBox("Arial", 14, QFont::Bold);
    groupboxOrbitDrag = new QGroupBox(tr("Available Orbits"));
    groupboxOrbitDrag->setAlignment(Qt::AlignCenter);
    groupboxOrbitDrag->setFont(fontGroupBox);
    groupboxOrbitDrop = new QGroupBox(tr("Selected Orbits"));
    groupboxOrbitDrop->setAlignment(Qt::AlignCenter);
    groupboxOrbitDrop->setFont(fontGroupBox);
    OrbitDragWidget = new Qt42DragWidget(this);
    OrbitDragWidget->setObjectName(tr("OrbitDragWidget"));
    OrbitDropWidget = new Qt42DragWidget(this);
    OrbitDropWidget->setObjectName(tr("OrbitDropWidget"));
    OrbitDropWidget->enableDeleteLabelByDrag(true);
    OrbitDropWidget->enableDropFromOtherSources(true);
    OrbitDropWidget->setLimitedToOneLabel(true);

    layoutOrbitDrag->addWidget(OrbitDragWidget);
    layoutOrbitDrop->addWidget(OrbitDropWidget);
    groupboxOrbitDrag->setLayout(layoutOrbitDrag);
    groupboxOrbitDrop->setLayout(layoutOrbitDrop);

    layoutMiddle->addWidget(groupboxOrbitDrop, 1);
    layoutMiddle->addWidget(groupboxOrbitDrag, 1);

    OrbitDragWidget->createLabel("drag");
    OrbitDragWidget->alignLabels();

    OrbitDropWidget->createLabel("drop");
    OrbitDropWidget->alignLabels();

    layoutAll->addLayout(layoutTop,1);
    layoutAll->addLayout(layoutSC ,1);
    layoutAll->addLayout(layoutDropWidgetBtns,1);
    layoutAll->addLayout(layoutMiddle,3);
    layoutAll->addWidget(m_buttonBox,1);
    setLayout(layoutAll);
}

void InpSimOrbitSCSetDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void InpSimOrbitSCSetDialog::createConnections()
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


    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){mapDataFromWidgetToModel();});

    connect(btnAlign, &QPushButton::clicked, OrbitDragWidget, &Qt42DragWidget::alignLabels);
    connect(btnAlign, &QPushButton::clicked, OrbitDropWidget, &Qt42DragWidget::alignLabels);
    connect(btnClearAll, &QPushButton::clicked, this,
            &InpSimOrbitSCSetDialog::clearAllSelectedOrbits);
    connect(btnClearAll, &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxSC, &QComboBox::currentTextChanged, this, &InpSimOrbitSCSetDialog::getOrbitsFromSC);
    connect(OrbitDropWidget, &Qt42DragWidget::addLabelbyDropping, this, &InpSimOrbitSCSetDialog::addOrbitSCPairs);
    connect(OrbitDropWidget, &Qt42DragWidget::removeLabelbyDragging, this, &InpSimOrbitSCSetDialog::removeOrbitSCPairs);
    connect(OrbitDropWidget, &Qt42DragWidget::addLabelbyDropping, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(OrbitDropWidget, &Qt42DragWidget::removeLabelbyDragging, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void InpSimOrbitSCSetDialog::addOrbitSCPairs(const QString& nameOrbit)
{
    QModelIndex modelIndexMission = m_index.parent().parent();
    Mission mission = modelIndexMission.data().value<Mission>();
    QString nameSC = comboboxSC->currentText().trimmed();
    Spacecraft spacecraft = Spacecraft();
    Orbit orbit = Orbit();
    if (nameSC.isEmpty() || nameOrbit.trimmed().isEmpty())
        return;

    for (int i = 0; i < mission.numberOfSpacecraft(); ++i)
    {
        Spacecraft* SC = mission.spacecraft(i);
        if (SC->name().trimmed() == nameSC){
            spacecraft = *SC;
            break;
        }
    }

    for (int i = 0; i < mission.numberOfOrbit(); ++i)
    {
        Orbit* o = mission.orbit(i);
        if (o->name().trimmed() == nameOrbit){
            orbit = *o;
            break;
        }
    }
    m_inpSimOrbitSCSet.createPair(orbit, spacecraft);
    editNumberOfSets->setText(QString::number(m_inpSimOrbitSCSet.numberOfOrbitSCpair()));
}

void InpSimOrbitSCSetDialog::removeOrbitSCPairs(const QString& nameOrbit)
{
    QModelIndex modelIndexMission = m_index.parent().parent();
    Mission mission = modelIndexMission.data().value<Mission>();
    QString nameSC = comboboxSC->currentText().trimmed();
    Spacecraft spacecraft = Spacecraft();
    Orbit orbit = Orbit();
    if (nameSC.isEmpty() || nameOrbit.trimmed().isEmpty())
        return;

    for (int i = 0; i < mission.numberOfSpacecraft(); ++i)
    {
        Spacecraft* SC = mission.spacecraft(i);
        if (SC->name().trimmed() == nameSC){
            spacecraft = *SC;
            break;
        }
    }

    for (int i = 0; i < mission.numberOfOrbit(); ++i)
    {
        Orbit* o = mission.orbit(i);
        if (o->name().trimmed() == nameOrbit){
            orbit = *o;
            break;
        }
    }
    m_inpSimOrbitSCSet.removePair(QPair<Orbit, Spacecraft>(orbit,spacecraft));
    editNumberOfSets->setText(QString::number(m_inpSimOrbitSCSet.numberOfOrbitSCpair()));
}

void InpSimOrbitSCSetDialog::clearAllSelectedOrbits()
{
   QString nameSC = comboboxSC->currentText().trimmed();
   if (nameSC.isEmpty() || OrbitDropWidget->children().size() == 0)
       return;

   QModelIndex indexMission = m_index.parent().parent();
   Mission mission = indexMission.data().value<Mission>();
   Spacecraft SC = Spacecraft();
   for (int i = 0; i < mission.numberOfSpacecraft(); ++i)
   {
       if (nameSC == mission.spacecraft(i)->name().trimmed()){
           SC = *(mission.spacecraft(i));
           break;
       }
   }
   m_inpSimOrbitSCSet.removePair(SC);
   OrbitDropWidget->clearAllLabels();
   editNumberOfSets->setText(QString::number(m_inpSimOrbitSCSet.numberOfOrbitSCpair()));
}

void InpSimOrbitSCSetDialog::getOrbitsFromSC(const QString& nameSC)
{
    OrbitDropWidget->clearAllLabels();
    if (nameSC.trimmed().isEmpty())
    {
        OrbitDropWidget->setEnabled(false);
        return;
    }

    else
    {
        OrbitDropWidget->setEnabled(true);
        const QString SC = nameSC.trimmed();
        for (QPair<Orbit, Spacecraft> p : m_inpSimOrbitSCSet.qvecPair())
        {
            if (SC == p.second.name().trimmed())
            {
                QString orbit = p.first.name().trimmed();
                OrbitDropWidget->createLabel(orbit);
            }
        }
    }
    OrbitDropWidget->alignLabels();
}

void InpSimOrbitSCSetDialog::setAvailableOrbits()
{
    QStringList listOrbit;
    QModelIndex modelIndexMission = m_index.parent().parent();
    Mission mission = modelIndexMission.data().value<Mission>();
    for (int i = 0; i < mission.numberOfOrbit(); ++i)
    {
        Orbit* O = mission.orbit(i);
        if (O->includedInCalculation()){
            OrbitDragWidget->createLabel(O->name().trimmed());
            OrbitDragWidget->alignLabels();
        }
    }
}

void InpSimOrbitSCSetDialog::updateComboboxSC()
{
    QStringList listSC{""};
    comboboxSC->clear();
    QModelIndex modelIndexMission = m_index.parent().parent();
    Mission mission = modelIndexMission.data().value<Mission>();
    for (int i = 0; i < mission.numberOfSpacecraft(); ++i)
    {
        Spacecraft* sc = mission.spacecraft(i);
        if(sc->includedInCalculation())
            listSC.append(sc->name().trimmed());
    }
    comboboxSC->addItems(listSC);
    comboboxSC->setCurrentIndex(0);
    getOrbitsFromSC(comboboxSC->currentText().trimmed());
}

bool InpSimOrbitSCSetDialog::mapDataFromModelToWidget()
{
    m_inpSimOrbitSCSet = m_index.data().value<InpSimOrbitSCSet>();
    editNumberOfSets->setText(QString::number(m_inpSimOrbitSCSet.numberOfOrbitSCpair()));
    OrbitDragWidget->clearAllLabels();
    OrbitDropWidget->clearAllLabels();
    setAvailableOrbits();
    updateComboboxSC();
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    QModelIndex modelIndexMission = m_index.parent().parent();
    Mission mission = modelIndexMission.data().value<Mission>();
    labelMission->setText(tr("Mission: ") + mission.name().trimmed());
    return true;
}

bool InpSimOrbitSCSetDialog::mapDataFromWidgetToModel()
{
    QVector<Spacecraft> vecSCwoOrbits = m_inpSimOrbitSCSet.SCswithoutOrbits();
    if (vecSCwoOrbits.size() != 0)
    {
        QMessageBox* msg = new QMessageBox(this);
        msg->setWindowTitle(tr("SCs without Orbit Data"));
        msg->setIcon(QMessageBox::Information);
        QString text = QString();
        for (Spacecraft sc : vecSCwoOrbits)
        {
            QString nameSC = sc.name();
            text.append(nameSC + tr("\n"));
        }
        if (vecSCwoOrbits.size() == 1)
            text.append(tr("\nisn't paired with orbit data.\n"));
        else
            text.append(tr("\nare not paired with orbit data.\n"));
        text.append(tr("Data won't be applied."));
        msg->setText(text);
        msg->setStandardButtons(QMessageBox::Ok);
        int exc = msg->exec();
        if (exc == QMessageBox::Ok){
            msg->close();
            delete msg;
        }
        m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        return false;
    }
    QVariant newData = QVariant();
    newData.setValue(m_inpSimOrbitSCSet);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}



/** Widget for Environment Data **/
InpSimEnvironmentDialog::InpSimEnvironmentDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("Environment"));
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save  |
                                       QDialogButtonBox::Apply |
                                       QDialogButtonBox::Cancel);
    setupModels();
    createWidgets();
    createActions();
    createConnections();
    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(*pal);
}

InpSimEnvironmentDialog::~InpSimEnvironmentDialog()
{

}

void InpSimEnvironmentDialog::setupModels()
{
    model_SolarFluxAPvalues = new QStringListModel(list_SolarFluxAPvalues);
    model_Magfield = new QStringListModel(list_Magfield);
}

void InpSimEnvironmentDialog::createWidgets()
{
    const int maxWidthGroupBoxForcesToruesLarge = 650;

    tabWidget = new QTabWidget;
    widgetPage1 = new QWidget;
    widgetPage2 = new QWidget;

    QGridLayout* layoutPage1 = new QGridLayout;
    QGridLayout* layoutPage2 = new QGridLayout;
    QVBoxLayout* layoutAll = new QVBoxLayout;

    groupboxDetails = new QGroupBox(tr("Details"));
    groupboxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    layoutDetails->addRow(labelMission, editMission);
    groupboxDetails->setLayout(layoutDetails);

    groupboxTime = new QGroupBox(tr("Time Settings"));
    groupboxTime->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutTime = new QFormLayout;
    labelDate = new QLabel(tr("Date (Month/Day/Year)"));
    editDate = new QDateEdit;
    labelGreenwichMeanTime = new QLabel(tr("Greenwich Mean Time (Hr, Min, Sec)"));
    editGreenwichMeanTime = new QTimeEdit;
    labelTimeOffset = new QLabel(tr("Time Offset (sec)"));
    spinboxTimeOffset = new QDoubleSpinBox;
    layoutTime->addRow(labelDate, editDate);
    layoutTime->addRow(labelGreenwichMeanTime, editGreenwichMeanTime);
    layoutTime->addRow(labelTimeOffset, spinboxTimeOffset);
    groupboxTime->setLayout(layoutTime);

    groupboxModelDataInterpolation = new QGroupBox(tr("Solar Flux and AP values"));
    groupboxModelDataInterpolation->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutModelDataInterpolation = new QFormLayout;
    labelModelDataInterpolationForSolarFluxAndAPvalues = new QLabel(tr("Model Data Interpolation"));
    comboboxModelDataInterpolationForSolarFluxAndAPvalues = new QComboBox;
    comboboxModelDataInterpolationForSolarFluxAndAPvalues->setModel(model_SolarFluxAPvalues);

    // could be TWOSIGMA_KP, NOMINAL or USER_DEFINED

    labelUSER_DEFINED_F10_7 = new QLabel(tr("F10.7"));
    editUSER_DEFINED_F10_7 = new QLineEdit;
    editUSER_DEFINED_F10_7->setValidator(new QDoubleValidator);
    labelUSER_DEFINED_AP = new QLabel(tr("AP"));
    editUSER_DEFINED_AP = new QLineEdit;
    editUSER_DEFINED_AP->setValidator(new QDoubleValidator);

    layoutModelDataInterpolation->addRow(labelModelDataInterpolationForSolarFluxAndAPvalues,
                                         comboboxModelDataInterpolationForSolarFluxAndAPvalues);
    layoutModelDataInterpolation->addRow(labelUSER_DEFINED_F10_7, editUSER_DEFINED_F10_7);
    layoutModelDataInterpolation->addRow(labelUSER_DEFINED_AP, editUSER_DEFINED_AP);
    groupboxModelDataInterpolation->setLayout(layoutModelDataInterpolation);

    groupboxMagfield = new QGroupBox(tr("Magnetic Field"));
    groupboxMagfield->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutMagfield = new QFormLayout;
    labelMagfield = new QLabel(tr("Magnetic Field"));
    comboboxMagfield = new QComboBox; // could be NONE, DIPOLE, or IGRF;
    comboboxMagfield->setModel(model_Magfield);
    groupboxIGRF = new QGroupBox(tr("IGRF Degree/Order (<=10)")); // IGRF: International Geomagnetic Reference Field
    QFormLayout* layoutIGRF = new QFormLayout;
    labelIGRF_Degree = new QLabel(tr("Degree"));
    spinboxIGRF_Degree = new QSpinBox;
    spinboxIGRF_Degree->setRange(0,10);
    labelIGRF_Order = new QLabel(tr("Order"));
    spinboxIGRF_Order = new QSpinBox;
    spinboxIGRF_Order->setRange(0,10);
    layoutIGRF->addRow(labelIGRF_Degree, spinboxIGRF_Degree);
    layoutIGRF->addRow(labelIGRF_Order, spinboxIGRF_Order);
    groupboxIGRF->setLayout(layoutIGRF);
    layoutMagfield->addRow(labelMagfield, comboboxMagfield);
    layoutMagfield->addRow(groupboxIGRF);
    groupboxMagfield->setLayout(layoutMagfield);

    groupboxGravity = new QGroupBox(tr("Gravity Models"));
    groupboxGravity->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutGravity = new QFormLayout;
    groupboxEarthGravityModelNM = new QGroupBox(tr("Earth Gravity Model (<=18)"));
    QHBoxLayout* layoutEarthGravityModelNM = new QHBoxLayout;
    labelEarthGravityModelN = new QLabel(tr("N"));
    spinboxEarthGravityModelN = new QSpinBox;
    spinboxEarthGravityModelN->setRange(0,18);
    labelEarthGravityModelM = new QLabel(tr("M"));
    spinboxEarthGravityModelM = new QSpinBox;
    spinboxEarthGravityModelM->setRange(0,18);
    layoutEarthGravityModelNM->addWidget(labelEarthGravityModelN);
    layoutEarthGravityModelNM->addWidget(spinboxEarthGravityModelN);
    layoutEarthGravityModelNM->addWidget(labelEarthGravityModelM);
    layoutEarthGravityModelNM->addWidget(spinboxEarthGravityModelM);
    groupboxEarthGravityModelNM->setLayout(layoutEarthGravityModelNM);
    groupboxMarsGravityModelNM = new QGroupBox(tr("Mars Gravity Model (<=18)"));
    QHBoxLayout* layoutMarsGravityModelNM = new QHBoxLayout;
    labelMarsGravityModelN = new QLabel(tr("N"));
    spinboxMarsGravityModelN = new QSpinBox;
    spinboxMarsGravityModelN->setRange(0,18);
    labelMarsGravityModelM = new QLabel(tr("M"));
    spinboxMarsGravityModelM = new QSpinBox;
    spinboxMarsGravityModelM->setRange(0,18);
    layoutMarsGravityModelNM->addWidget(labelMarsGravityModelN);
    layoutMarsGravityModelNM->addWidget(spinboxMarsGravityModelN);
    layoutMarsGravityModelNM->addWidget(labelMarsGravityModelM);
    layoutMarsGravityModelNM->addWidget(spinboxMarsGravityModelM);
    groupboxMarsGravityModelNM->setLayout(layoutMarsGravityModelNM);
    groupboxLunaGravityModelNM = new QGroupBox(tr("Luna Gravity Model (<=18)"));
    QHBoxLayout* layoutLunaGravityModelNM = new QHBoxLayout;
    labelLunaGravityModelN = new QLabel(tr("N"));
    spinboxLunaGravityModelN = new QSpinBox;
    spinboxLunaGravityModelN->setRange(0,18);
    labelLunaGravityModelM = new QLabel(tr("M"));
    spinboxLunaGravityModelM = new QSpinBox;
    spinboxLunaGravityModelM->setRange(0,18);
    layoutLunaGravityModelNM->addWidget(labelLunaGravityModelN);
    layoutLunaGravityModelNM->addWidget(spinboxLunaGravityModelN);
    layoutLunaGravityModelNM->addWidget(labelLunaGravityModelM);
    layoutLunaGravityModelNM->addWidget(spinboxLunaGravityModelM);
    groupboxLunaGravityModelNM->setLayout(layoutLunaGravityModelNM);

    layoutGravity->addRow(groupboxEarthGravityModelNM);
    layoutGravity->addRow(groupboxMarsGravityModelNM);
    layoutGravity->addRow(groupboxLunaGravityModelNM);
    groupboxGravity->setLayout(layoutGravity);

    groupBoxForcesTorques = new QGroupBox(tr("Forces and Torques"));
    groupBoxForcesTorques->setAlignment(Qt::AlignCenter);
    groupBoxForcesTorques->setMaximumWidth(maxWidthGroupBoxForcesToruesLarge);
    QFormLayout* layoutForcesTorques = new QFormLayout;
    groupboxAerodynamicForcesTorques = new QGroupBox(tr("Aerodynamic Forces and Torques (shadows)"));
    QHBoxLayout* layoutAerodynamicForcesTorques = new QHBoxLayout;
    chkbxAerodynamicForces = new QCheckBox(tr("Forces"));
    chkbxAerodynamicTorques = new QCheckBox(tr("Torques"));
    layoutAerodynamicForcesTorques->addWidget(chkbxAerodynamicForces);
    layoutAerodynamicForcesTorques->addWidget(chkbxAerodynamicTorques);
    groupboxAerodynamicForcesTorques->setLayout(layoutAerodynamicForcesTorques);

    chkbxGravityGradientTorques = new QCheckBox(tr("Gravity Gradient Torques"));
    groupboxSolarPressureForcesTorques = new QGroupBox(tr("Solar Pressure Forces/Torques (shadows)"));
    QHBoxLayout* layoutSolarPressureForcesTorques = new QHBoxLayout;
    chkbxSolarPressureForces = new QCheckBox(tr("Forces"));
    chkbxSolarPressureTorques = new QCheckBox(tr("Torques"));
    layoutSolarPressureForcesTorques->addWidget(chkbxSolarPressureForces);
    layoutSolarPressureForcesTorques->addWidget(chkbxSolarPressureTorques);
    groupboxSolarPressureForcesTorques->setLayout(layoutSolarPressureForcesTorques);
    chkbxGravityPerturbationForces = new QCheckBox(tr("Perturbation Forces"));

    chkbxPassiveJointForcesTorques = new QCheckBox(tr("Passive Joint Forces/Torques"));
    chkbxThrusterPlumeForcesTorques = new QCheckBox(tr("Thruster Plume Force/Torques"));
    chkbxRWAimbalanceForcesTorques = new QCheckBox(tr("RWA Imbalance Forces/Torques"));
    chkbxContactForcesTorques = new QCheckBox(tr("Contact Forces/Torques"));
    chkbxCFDsloshForcesTorques = new QCheckBox(tr("CFD Slosh Forces/Torques"));
    chkbxOutputEnvironmentalTorquesToFiles = new QCheckBox(tr("Output Environmental Torques to Files"));
    layoutForcesTorques->addRow(groupboxAerodynamicForcesTorques);
    layoutForcesTorques->addRow(chkbxGravityGradientTorques);
    layoutForcesTorques->addRow(groupboxSolarPressureForcesTorques);
    layoutForcesTorques->addRow(chkbxGravityPerturbationForces);
    layoutForcesTorques->addRow(chkbxPassiveJointForcesTorques);
    layoutForcesTorques->addRow(chkbxThrusterPlumeForcesTorques);
    layoutForcesTorques->addRow(chkbxRWAimbalanceForcesTorques);
    layoutForcesTorques->addRow(chkbxContactForcesTorques);
    layoutForcesTorques->addRow(chkbxCFDsloshForcesTorques);
    layoutForcesTorques->addRow(chkbxOutputEnvironmentalTorquesToFiles);
    groupBoxForcesTorques->setLayout(layoutForcesTorques);


    layoutPage1->addWidget(groupboxDetails, 0, 0, 1, 1);
    layoutPage1->addWidget(groupboxTime, 1, 0, 1, 1);
    layoutPage1->addWidget(groupboxModelDataInterpolation, 2, 0 ,1,1);
    layoutPage1->addWidget(groupboxMagfield, 0,1,1,1);
    layoutPage1->addWidget(groupboxGravity, 1,1,2,1);
    layoutPage1->setColumnStretch(0,1);
    layoutPage1->setColumnStretch(1,1);

    layoutPage2->addWidget(groupBoxForcesTorques, 0,0);


    widgetPage1->setLayout(layoutPage1);
    widgetPage2->setLayout(layoutPage2);

    tabWidget->addTab(widgetPage1, tr("Details/ Time/ Magnetic Fields/ Gravity Models"));
    tabWidget->addTab(widgetPage2, tr("Forces/ Torques"));

    layoutAll->addWidget(tabWidget);
    layoutAll->addWidget(m_buttonBox);

    setLayout(layoutAll);

}

void InpSimEnvironmentDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void InpSimEnvironmentDialog::createConnections()
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

    //connect(editDate, &QDateEdit::editingFinished, m_buttonBox->button(QDialogButtonBox::Apply),
    //        [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    //connect(editGreenwichMeanTime, &QTimeEdit::editingFinished, m_buttonBox->button(QDialogButtonBox::Apply),
    //        [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDate, &QDateEdit::dateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editGreenwichMeanTime, &QTimeEdit::timeChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(spinboxTimeOffset, QOverload<double>::of(&QDoubleSpinBox::valueChanged), m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxModelDataInterpolationForSolarFluxAndAPvalues, &QComboBox::currentTextChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editUSER_DEFINED_F10_7, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editUSER_DEFINED_AP, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxMagfield, &QComboBox::currentTextChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxIGRF_Degree, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxIGRF_Order, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxEarthGravityModelN, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxEarthGravityModelM, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxMarsGravityModelN, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxMarsGravityModelM, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxLunaGravityModelN, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxLunaGravityModelM, QOverload<int>::of(&QSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect (chkbxAerodynamicForces, &QCheckBox::stateChanged,
             m_buttonBox->button(QDialogButtonBox::Apply),
             [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(chkbxAerodynamicTorques, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(chkbxGravityGradientTorques, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxSolarPressureForces, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxSolarPressureTorques, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxGravityPerturbationForces, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxPassiveJointForcesTorques, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxThrusterPlumeForcesTorques, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxRWAimbalanceForcesTorques, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxContactForcesTorques, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxCFDsloshForcesTorques, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxOutputEnvironmentalTorquesToFiles, &QCheckBox::stateChanged,
            m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxMagfield, &QComboBox::currentTextChanged,
            this, &InpSimEnvironmentDialog::IGRFisSelected);
    connect(this, &InpSimEnvironmentDialog::IGRFselected,
            this, &InpSimEnvironmentDialog::enableGroupBoxIGRF);
}

void InpSimEnvironmentDialog::IGRFisSelected(const QString& text)
{
    emit IGRFselected(text == list_Magfield[2]);
}

void InpSimEnvironmentDialog::enableGroupBoxIGRF(const bool& selected)
{
    groupboxIGRF->setEnabled(selected);
}

void InpSimEnvironmentDialog::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    else
        m_model = nullptr;
}

void InpSimEnvironmentDialog::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<InpSimEnvironment>()){
        m_index = QModelIndex();
        return;
    }
    m_index = index;
    connect(m_model, &Qt42Model::dataChanged,
            this, &InpSimEnvironmentDialog::mapDataFromModelToWidget);
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    mapDataFromModelToWidget();
}

bool InpSimEnvironmentDialog::mapDataFromModelToWidget()
{
    const int precision = 6;
    if (!m_index.isValid() || !m_index.data().canConvert<InpSimEnvironment>())
        return false;
    InpSimEnvironment env = m_index.data().value<InpSimEnvironment>();
    Mission mission = m_index.parent().parent().data().value<Mission>();
    editMission->setText(mission.name());
    editDate->setDate(env.date());
    editGreenwichMeanTime->setTime(env.time());
    spinboxTimeOffset->setValue(env.timeOffset());
    comboboxModelDataInterpolationForSolarFluxAndAPvalues->setCurrentText(
                map_SolarFluxAPvalues.value(env.solarFluxAPValues()));
    editUSER_DEFINED_F10_7->setText(QString::number(env.userDefined_F10_7(),'f',precision));
    editUSER_DEFINED_AP->setText(QString::number(env.userDefined_F10_7(),'f',precision));
    comboboxMagfield->setCurrentText(
                map_Magfield.value(env.magField()));
    spinboxIGRF_Degree->setValue(env.IGRF_Degree());
    spinboxIGRF_Order->setValue(env.IGRF_Order());
    spinboxEarthGravityModelN->setValue(env.gravityModelEarth_N());
    spinboxEarthGravityModelM->setValue(env.gravityModelEarth_M());
    spinboxMarsGravityModelN->setValue(env.gravityModelMars_N());
    spinboxMarsGravityModelM->setValue(env.gravityModelMars_M());
    spinboxLunaGravityModelN->setValue(env.gravityModelLuna_N());
    spinboxLunaGravityModelM->setValue(env.gravityModelLuna_M());
    chkbxAerodynamicForces->setChecked(env.aerodynamicForces());
    chkbxAerodynamicTorques->setChecked(env.aerodynamicTorques());
    chkbxGravityGradientTorques->setChecked(env.gravityGradientTorques());
    chkbxSolarPressureForces->setChecked(env.solarPressureForces());
    chkbxSolarPressureTorques->setChecked(env.solarPressureTorques());
    chkbxGravityPerturbationForces->setChecked(env.gravityPerturbationForces());
    chkbxPassiveJointForcesTorques->setChecked(env.passiveJointForcesTorques());
    chkbxThrusterPlumeForcesTorques->setChecked(env.thrusterPlumeForcesTorques());
    chkbxRWAimbalanceForcesTorques->setChecked(env.RWA_ImbalanceForcesTorques());
    chkbxContactForcesTorques->setChecked(env.contactForcesTorques());
    chkbxCFDsloshForcesTorques->setChecked(env.CFDsloshForceTorques());
    chkbxOutputEnvironmentalTorquesToFiles->setChecked(env.outPutEnvironmentalTorquesToFiles());
    return true;

}

bool InpSimEnvironmentDialog::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<InpSimEnvironment>())
        return false;
    QVariant newData = QVariant();
    InpSimEnvironment newEnv = m_index.data().value<InpSimEnvironment>();

    newEnv.edit(editDate->date(), editGreenwichMeanTime->time(), spinboxTimeOffset->value(),
                map_SolarFluxAPvalues.value(comboboxModelDataInterpolationForSolarFluxAndAPvalues->currentText()),
                editUSER_DEFINED_F10_7->text().toDouble(), editUSER_DEFINED_AP->text().toDouble(),
                map_Magfield.value(comboboxMagfield->currentText()),spinboxIGRF_Degree->value(), spinboxIGRF_Order->value(),
                spinboxEarthGravityModelN->value(), spinboxEarthGravityModelM->value(),
                spinboxMarsGravityModelN->value(), spinboxMarsGravityModelM->value(),
                spinboxLunaGravityModelN->value(), spinboxLunaGravityModelM->value(),
                chkbxAerodynamicForces->isChecked(), chkbxAerodynamicTorques->isChecked(),
                chkbxGravityGradientTorques->isChecked(), chkbxSolarPressureForces->isChecked(),
                chkbxSolarPressureTorques->isChecked(), chkbxGravityPerturbationForces->isChecked(),
                chkbxPassiveJointForcesTorques->isChecked(), chkbxThrusterPlumeForcesTorques->isChecked(),
                chkbxRWAimbalanceForcesTorques->isChecked(), chkbxContactForcesTorques->isChecked(),
                chkbxCFDsloshForcesTorques->isChecked(), chkbxOutputEnvironmentalTorquesToFiles->isChecked());
    newData.setValue(newEnv);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}


/** Widgets for Celestial Bodies **/
InpSimCelestialBodyDialog::InpSimCelestialBodyDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("Celestial Bodies"));
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save  |
                                       QDialogButtonBox::Apply |
                                       QDialogButtonBox::Cancel);
    m_undoStack = new QUndoStack(this);
    setupModels();
    createWidgets();
    createActions();
    createConnections();
}

InpSimCelestialBodyDialog::~InpSimCelestialBodyDialog()
{

}

void InpSimCelestialBodyDialog::setupModels()
{
    model_Ephemerides = new QStringListModel(list_EphemeridesOptions);
}


void InpSimCelestialBodyDialog::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    else
        m_model = nullptr;
}

void InpSimCelestialBodyDialog::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<InpSimCelestialBody>()){
        m_index = QModelIndex();
        return;
    }
    m_index = index;
    connect(m_model, &Qt42Model::dataChanged,
            this, &InpSimCelestialBodyDialog::mapDataFromModelToWidget);
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    mapDataFromModelToWidget();
}

void InpSimCelestialBodyDialog::createWidgets()
{
    const int maxWidthCombobox = 150;
    const int maxWidthLineEdit = 200;
    QVBoxLayout* layoutAll = new QVBoxLayout;
    QFormLayout* layoutLeft = new QFormLayout;
    QHBoxLayout* layoutWidgets = new QHBoxLayout;
    groupboxDetails = new QGroupBox(tr("Details"));
    groupboxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    editMission->setMaximumWidth(maxWidthLineEdit);
    layoutDetails->addRow(labelMission, editMission);
    groupboxDetails->setLayout(layoutDetails);

    groupboxCelestialBodies = new QGroupBox(tr("Celestial Bodies"));
    groupboxCelestialBodies->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutCelestialBodies= new QFormLayout;
    labelEphemOption = new QLabel(tr("Ephemeride Option"));
    comboboxEphemOption = new QComboBox;
    comboboxEphemOption->setModel(model_Ephemerides);
    comboboxEphemOption->setMaximumWidth(maxWidthCombobox);
    chkbxMercury = new QCheckBox(tr("Mercury"));
    chkbxVenus = new QCheckBox(tr("Venus"));
    chkbxEarthAndLuna = new QCheckBox(tr("Earth and Luna"));
    chkbxMarsAndMoons = new QCheckBox(tr("Mars and its moons"));
    chkbxJupiterAndMoons = new QCheckBox(tr("Jupiter and its moons"));
    chkbxSaturnAndMoons = new QCheckBox(tr("Saturn and its moons"));
    chkbxUranusAndMoons = new QCheckBox(tr("Uranus and its moons"));
    chkbxNeptuneAnsMoons = new QCheckBox(tr("Neptune and its moons"));
    chkbxPlutoAndMoons = new QCheckBox(tr("Pluto and it moons"));
    chkbxAsteroidsAndComets = new QCheckBox(tr("Asteroid and Comets"));
    layoutCelestialBodies->addRow(labelEphemOption, comboboxEphemOption);
    layoutCelestialBodies->addRow(chkbxMercury);
    layoutCelestialBodies->addRow(chkbxVenus);
    layoutCelestialBodies->addRow(chkbxEarthAndLuna);
    layoutCelestialBodies->addRow(chkbxMarsAndMoons);
    layoutCelestialBodies->addRow(chkbxJupiterAndMoons);
    layoutCelestialBodies->addRow(chkbxSaturnAndMoons);
    layoutCelestialBodies->addRow(chkbxUranusAndMoons);
    layoutCelestialBodies->addRow(chkbxNeptuneAnsMoons);
    layoutCelestialBodies->addRow(chkbxPlutoAndMoons);
    layoutCelestialBodies->addRow(chkbxAsteroidsAndComets);
    groupboxCelestialBodies->setLayout(layoutCelestialBodies);

    layoutLeft->addRow(groupboxDetails);

    layoutWidgets->addLayout(layoutLeft);
    layoutWidgets->addWidget(groupboxCelestialBodies);
    layoutWidgets->setStretch(0,1);
    layoutWidgets->setStretch(1,1);

    layoutAll->addLayout(layoutWidgets);
    layoutAll->addWidget(m_buttonBox);
    setLayout(layoutAll);
}

void InpSimCelestialBodyDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}



void InpSimCelestialBodyDialog::createConnections()
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

    connect(comboboxEphemOption, &QComboBox::currentTextChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxMercury, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxVenus, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxEarthAndLuna, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxMarsAndMoons, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxJupiterAndMoons, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxSaturnAndMoons, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxUranusAndMoons, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxNeptuneAnsMoons, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxPlutoAndMoons, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxAsteroidsAndComets, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

bool InpSimCelestialBodyDialog::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<InpSimCelestialBody>())
        return false;
    InpSimCelestialBody CB = m_index.data().value<InpSimCelestialBody>();
    Mission mission = m_index.parent().parent().data().value<Mission>();

    editMission->setText(mission.name());
    comboboxEphemOption->setCurrentText(map_EphemeridesOptions.value(CB.ephemerides()));
    chkbxMercury->setChecked(CB.MercuryIncluded());
    chkbxVenus->setChecked(CB.VenusIncluded());
    chkbxEarthAndLuna->setChecked(CB.EarthAndLunaIncluded());
    chkbxMarsAndMoons->setChecked(CB.MarsAndMoonsIncluded());
    chkbxJupiterAndMoons->setChecked(CB.JupiterAndMoonsIncluded());
    chkbxSaturnAndMoons->setChecked(CB.SaturnAndMoonsIncluded());
    chkbxUranusAndMoons->setChecked(CB.UranusAndMoonsIncluded());
    chkbxNeptuneAnsMoons->setChecked(CB.NeptuneAndMoonsIncluded());
    chkbxPlutoAndMoons->setChecked(CB.PlutoAndMoonsIncluded());
    chkbxAsteroidsAndComets->setChecked(CB.AsteroidsAndCometsIncluded());
    return true;
}

bool InpSimCelestialBodyDialog::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<InpSimCelestialBody>())
        return false;
    QVariant newData = QVariant();
    InpSimCelestialBody newCB = m_index.data().value<InpSimCelestialBody>();

    newCB.edit(map_EphemeridesOptions.value(comboboxEphemOption->currentText()),
               chkbxMercury->isChecked(), chkbxVenus->isChecked(),
               chkbxEarthAndLuna->isChecked(), chkbxMarsAndMoons->isChecked(),
               chkbxJupiterAndMoons->isChecked(), chkbxSaturnAndMoons->isChecked(),
               chkbxUranusAndMoons->isChecked(), chkbxNeptuneAnsMoons->isChecked(),
               chkbxPlutoAndMoons->isChecked(), chkbxAsteroidsAndComets->isChecked());

    newData.setValue(newCB);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}

/** Widget for Lagrange Point System data **/
InpSimLagrangePointSystemsDialog::InpSimLagrangePointSystemsDialog(QWidget* parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Lagrange Point Systems"));
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}


InpSimLagrangePointSystemsDialog::~InpSimLagrangePointSystemsDialog()
{

}

void InpSimLagrangePointSystemsDialog::createWidgets()
{
    const QSize maxSizeGroupBoxDetails (400, 150);
    const QSize maxSizeGroupBoxLagrangePointSystem (400, 250);
    QVBoxLayout* layoutAll = new QVBoxLayout;
    QVBoxLayout* layoutWidget = new QVBoxLayout;
    groupboxDetails = new QGroupBox(tr("Details"));
    groupboxDetails->setMaximumSize(maxSizeGroupBoxDetails);
    groupboxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->setAlignment(Qt::AlignVCenter);
    groupboxDetails->setLayout(layoutDetails);

    groupboxLagrangeSystems = new QGroupBox(tr("Lagrange Point Systems"));
    groupboxLagrangeSystems->setAlignment(Qt::AlignCenter);
    groupboxLagrangeSystems->setMaximumSize(maxSizeGroupBoxLagrangePointSystem);
    QVBoxLayout* layoutLagrangeSystems = new QVBoxLayout;
    chkbxEarthMoon = new QCheckBox(tr("Earth-Moon"));
    chkbxSunEarth = new QCheckBox(tr("Sun-Earth"));
    chkbxSunJupiter = new QCheckBox(tr("Sun-Jupiter"));
    layoutLagrangeSystems->addWidget(chkbxEarthMoon);
    layoutLagrangeSystems->addWidget(chkbxSunEarth);
    layoutLagrangeSystems->addWidget(chkbxSunJupiter);
    groupboxLagrangeSystems->setLayout(layoutLagrangeSystems);

    layoutWidget->addWidget(groupboxDetails);
    layoutWidget->addWidget(groupboxLagrangeSystems);
    layoutWidget->setStretch(0,1);
    layoutWidget->setStretch(1,1);
    layoutWidget->setAlignment(Qt::AlignHCenter);
    layoutAll->addLayout(layoutWidget);
    layoutAll->addWidget(m_buttonBox);

    setLayout(layoutAll);
}

void InpSimLagrangePointSystemsDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void InpSimLagrangePointSystemsDialog::createConnections()
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

    connect(chkbxEarthMoon, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxSunEarth, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxSunJupiter, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void InpSimLagrangePointSystemsDialog::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    else
        m_model = nullptr;
}

void InpSimLagrangePointSystemsDialog::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<InpSimLagrangePointSystem>()){
        m_index = QModelIndex();
        return;
    }
    m_index = index;
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    mapDataFromModelToWidget();
    if (m_model){
        connect(m_model, &Qt42Model::dataChanged,
                this, &InpSimLagrangePointSystemsDialog::mapDataFromModelToWidget);
    }
}

bool InpSimLagrangePointSystemsDialog::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<InpSimLagrangePointSystem>())
        return false;

    InpSimLagrangePointSystem inpsimL = m_index.data().value<InpSimLagrangePointSystem>();
    Mission mission = m_index.parent().parent().data().value<Mission>();
    editMission->setText(mission.name());
    chkbxEarthMoon->setChecked(inpsimL.EarthMoonIncluded());
    chkbxSunEarth->setChecked(inpsimL.SunEarthIncluded());
    chkbxSunJupiter->setChecked(inpsimL.SunJupiterIncluded());
    return true;
}

bool InpSimLagrangePointSystemsDialog::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<InpSimLagrangePointSystem>())
        return false;

    QVariant newData = QVariant();
    InpSimLagrangePointSystem newL = m_index.data().value<InpSimLagrangePointSystem>();
    newL.edit(chkbxEarthMoon->isChecked(), chkbxSunEarth->isChecked(), chkbxSunJupiter->isChecked());
    newData.setValue(newL);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}


/** Widget for Ground Station data **/
InpSimGroundStationDialog::InpSimGroundStationDialog(QWidget* parent) : QDialog(parent)
{
    if (parent)
        parentTabWidget = static_cast<QTabWidget*>(parent);

    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save  |
                                       QDialogButtonBox::Apply |
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnecetions();
}

InpSimGroundStationDialog::~InpSimGroundStationDialog()
{

}

void InpSimGroundStationDialog::setModel(QAbstractItemModel* model)
{
    if (model)
    {
        m_model = static_cast<Qt42Model*>(model);
        connect(m_model, &QAbstractItemModel::dataChanged, this, [=](){mapDataFromModelToWidget();});
    }
}

void InpSimGroundStationDialog::setRootIndex(const QModelIndex& index)
{
    if (!index.isValid() || !index.data().canConvert<InpSimGroundStation>()){
        m_index = QModelIndex();
        return;
    }
    m_index = index;
    m_isgs = m_index.data().value<InpSimGroundStation>();
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    mapDataFromModelToWidget();
    comboboxGS->setCurrentIndex(0);
    mapDataForSelectedGS(comboboxGS->currentIndex());
}

void InpSimGroundStationDialog::setupModels()
{

}

void InpSimGroundStationDialog::createWidgets()
{
    QVBoxLayout* layoutAll = new QVBoxLayout;
    QFormLayout* layoutWidgets = new QFormLayout;
    QVBoxLayout* layoutMapDisplay = new QVBoxLayout;
    QHBoxLayout* layoutMiddle = new QHBoxLayout;

    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelNumberOfGS = new QLabel(tr("Number Of GS"));
    editNumberOfGS = new QLineEdit;
    editNumberOfGS->setReadOnly(true);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelNumberOfGS, editNumberOfGS);
    groupBoxDetails->setLayout(layoutDetails);
    groupBoxDetails->setMaximumHeight(100);

    groupBoxCreateRemoveGS = new QGroupBox(tr(""));
    QVBoxLayout* layoutCreateRemoveGS_V= new QVBoxLayout;
    QHBoxLayout* layoutCreateRemoveGS_H = new QHBoxLayout;
    comboboxGS = new QComboBox;
    btnCreateGS = new QPushButton(tr("Create"));
    btnRemoveGS = new QPushButton(tr("Remove"));
    layoutCreateRemoveGS_H->addWidget(btnCreateGS);
    layoutCreateRemoveGS_H->addWidget(btnRemoveGS);
    layoutCreateRemoveGS_V->addWidget(comboboxGS);
    layoutCreateRemoveGS_V->addLayout(layoutCreateRemoveGS_H);
    layoutCreateRemoveGS_H->setStretch(0,1);
    layoutCreateRemoveGS_H->setStretch(1,1);
    layoutCreateRemoveGS_V->setStretch(0,1);
    layoutCreateRemoveGS_V->setStretch(1,1);
    groupBoxCreateRemoveGS->setLayout(layoutCreateRemoveGS_V);

    groupBoxEditGS = new QGroupBox(tr("Edit"));
    groupBoxEditGS->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutEditGS = new QFormLayout;

    chkbxExist = new QCheckBox(tr("Exist"));
    labelWorld = new QLabel(tr("World"));
    comboboxWorld = new QComboBox;
    comboboxWorld->addItems(list_orbitCenter_World);
    comboboxWorld->setCurrentText("Earth");

    groupBoxLongitudeLatitude = new QGroupBox(tr("Longitude/Latitude (degree)"));
    QHBoxLayout* layoutLongitudeLatitude = new QHBoxLayout;
    labelLongitude = new QLabel(tr("Longitude"));
    dblSpinBoxLongitude = new QDoubleSpinBox;
    dblSpinBoxLongitude->setRange(-180.0, 180.0);
    labelLatitude = new QLabel(tr("Latitude"));
    dblSpinBoxLatitude = new QDoubleSpinBox;
    dblSpinBoxLatitude->setRange(-90.0, 90.0);
    layoutLongitudeLatitude->addWidget(labelLongitude);
    layoutLongitudeLatitude->addWidget(dblSpinBoxLongitude);
    layoutLongitudeLatitude->addWidget(labelLatitude);
    layoutLongitudeLatitude->addWidget(dblSpinBoxLatitude);
    layoutLongitudeLatitude->setStretch(0,2);
    layoutLongitudeLatitude->setStretch(1,1);
    layoutLongitudeLatitude->setStretch(2,2);
    layoutLongitudeLatitude->setStretch(3,1);
    groupBoxLongitudeLatitude->setLayout(layoutLongitudeLatitude);

    labelLabel = new QLabel(tr("Label"));
    editLabel = new QLineEdit;
    btnOK = new QPushButton(tr("&OK"));
    btnOK->setMaximumWidth(150);
    layoutEditGS->addRow(chkbxExist);
    layoutEditGS->addRow(labelWorld, comboboxWorld);
    layoutEditGS->addRow(groupBoxLongitudeLatitude);
    layoutEditGS->addRow(labelLabel, editLabel);
    QHBoxLayout* layoutBtnOK = new QHBoxLayout;
    layoutBtnOK->setAlignment(Qt::AlignCenter);
    layoutBtnOK->addWidget(btnOK);
    layoutEditGS->addRow(layoutBtnOK);
    layoutEditGS->setSpacing(18);
    groupBoxEditGS->setLayout(layoutEditGS);

    layoutWidgets->addRow(groupBoxDetails);
    layoutWidgets->addRow(groupBoxCreateRemoveGS);
    layoutWidgets->addRow(groupBoxEditGS);

    layoutMiddle->addLayout(layoutWidgets);
    layoutMiddle->addLayout(layoutMapDisplay);
    layoutMiddle->setStretch(0,1);
    layoutMiddle->setStretch(1,2);

    layoutAll->addLayout(layoutMiddle);
    layoutAll->addWidget(m_buttonBox);

    setLayout(layoutAll);
}

void InpSimGroundStationDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void InpSimGroundStationDialog::createConnecetions()
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
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});


    connect(btnCreateGS, &QPushButton::clicked, this,
            [=](){m_isgs.createGroundStation(); renewComboboxGS();
        editNumberOfGS->setText(QString::number(m_isgs.numberOfGroundStation()));});
    connect(btnRemoveGS, &QPushButton::clicked, this, &InpSimGroundStationDialog::removeGS);

    connect(chkbxExist, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxWorld, &QComboBox::currentTextChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxLongitude, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinBoxLatitude, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_buttonBox->button(QDialogButtonBox::Apply), [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLabel, &QLineEdit::textEdited, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(comboboxGS, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &InpSimGroundStationDialog::mapDataForSelectedGS);

    connect(btnOK, &QPushButton::clicked, this, [=](){tempEdit_GS_Data();});



}

bool InpSimGroundStationDialog::mapDataFromModelToWidget()
{
    InpSimHeader ish = m_index.parent().data().value<InpSimHeader>();
    Mission m = m_index.parent().parent().data().value<Mission>();
    editMission->setText(m.name());
    editNumberOfGS->setText(QString::number(m_isgs.numberOfGroundStation()));
    renewComboboxGS();
    return true;
}

void InpSimGroundStationDialog::renewComboboxGS()
{

    comboboxGS->blockSignals(true);

    int currentIndex = comboboxGS->currentIndex();
    comboboxGS->clear();
    m_listGS = QStringList();
    m_listGS.append(tr(""));
    for (int index = 0; index < m_isgs.numberOfGroundStation(); ++index)
    {
        QString Name = m_isgs.groundStation(index).label().trimmed();
        m_listGS.append(Name);
    }
    comboboxGS->addItems(m_listGS);
    if (currentIndex != -1)
        comboboxGS->setCurrentIndex(currentIndex);


    comboboxGS->blockSignals(false);
}


bool InpSimGroundStationDialog::mapDataFromWidgetToModel()
{
    QVariant newData = QVariant();
    newData.setValue(m_isgs);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);

    return true;
}

void InpSimGroundStationDialog::mapDataForSelectedGS(const int& index)
{
    if (index <= 0){
        resetGS_Widgets();
        btnRemoveGS->setEnabled(false);
        groupBoxEditGS->setEnabled(false);
        return;
    }
    btnRemoveGS->setEnabled(true);
    groupBoxEditGS->setEnabled(true);

    GroundStation& gs = m_isgs.groundStation(index-1);
    QString worldName = gs.world().trimmed();
    {
        worldName = worldName.toLower();
        worldName[0] = worldName[0].toUpper();
    }

    chkbxExist->setChecked(gs.existed());
    comboboxWorld->setCurrentText(worldName);
    dblSpinBoxLatitude->setValue(gs.latitude());
    dblSpinBoxLongitude->setValue(gs.longitude());
    editLabel->setText(gs.label());

}


void InpSimGroundStationDialog::tempEdit_GS_Data()
{
    if (comboboxGS->currentIndex() == 0 || comboboxGS->currentText().isEmpty())
        return;
    int indexGS = comboboxGS->currentIndex() - 1;
    QString labelGS = editLabel->text().trimmed();
    for (int i = 0; i < m_isgs.numberOfGroundStation(); ++i)
    {
        if (labelGS.trimmed() == m_isgs.groundStation(i).label().trimmed() && i != indexGS)
        {
            QMessageBox* msg = new QMessageBox;
            msg->setWindowTitle(tr("Duplicated Ground Stations"));
            msg->setText(labelGS.trimmed() + tr(" already exists.")
                         + tr("\n") + tr("The label will not be modified."));
            msg->setIcon(QMessageBox::Information);
            msg->setStandardButtons(QMessageBox::Ok);
            msg->exec();
            labelGS = m_isgs.groundStation(indexGS).label().trimmed();
            break;
        }
    }

    m_isgs.groundStation(indexGS).edit(chkbxExist->isChecked(),
                                       comboboxWorld->currentText().trimmed().toUpper(),
                                       dblSpinBoxLongitude->value(),
                                       dblSpinBoxLatitude->value(),
                                       labelGS);
    renewComboboxGS();
    mapDataForSelectedGS(comboboxGS->currentIndex());


}

void InpSimGroundStationDialog::resetGS_Widgets()
{
    chkbxExist->setChecked(false);
    comboboxWorld->setCurrentText("Earth");
    dblSpinBoxLongitude->setValue(0.0);
    dblSpinBoxLatitude->setValue(0.0);
    editLabel->clear();
}

void InpSimGroundStationDialog::removeGS(bool pseudo)
{
    Q_UNUSED(pseudo)
    QString GStoRemove = comboboxGS->currentText().trimmed();
    if (GStoRemove.isEmpty() || GStoRemove.isNull())
        return;
    for (int i = 0; i < m_isgs.numberOfGroundStation(); ++i)
    {
        QString name = m_isgs.groundStation(i).label().trimmed();
        if (name == GStoRemove)
        {
            m_isgs.removeGroundStation(i);
            --i;
        }
    }

    comboboxGS->setCurrentIndex(0);
    renewComboboxGS();
    editNumberOfGS->setText(QString::number(m_isgs.numberOfGroundStation()));
}
