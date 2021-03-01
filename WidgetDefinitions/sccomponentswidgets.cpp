#include "WidgetHeaders/sccomponentswidgets.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "MVDheaders/qt42model.h"
#include "DataHeaders/spacecraftcomponents.h"
#include "DataHeaders/spacecraft.h"
#include "DataHeaders/mission.h"
#include "ShareHeaders/qt42commands.h"
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDoubleValidator>
#include <QSplitter>
#include <QFileDialog>
#include <QTreeView>
#include <QTableView>
#include <QComboBox>
#include <QFormLayout>
#include <QStringListModel>
#include <QCheckBox>
#include <QDebug>
#include <QDialogButtonBox>
#include <QUndoStack>
#include <QMessageBox>
#include <QAction>
#include <math.h>

SpacecraftBodyWidget::SpacecraftBodyWidget(QWidget *parent) : QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    tabPage1 = new QWidget(tabWidget);
    tabPage2 = new QWidget(tabWidget);
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);

    createWidgets();
    createActions();
    createConnections();
    QString windowTitle = tr("Spacecraft Body");
    setWindowTitle(windowTitle);
}

SpacecraftBodyWidget::~SpacecraftBodyWidget()
{

}

SpacecraftBodyWidget::SpacecraftBodyWidget(const SpacecraftBodyWidget& SBW)
{
    Q_UNUSED(SBW)
}


void SpacecraftBodyWidget::createWidgets(){
    const QSize sizeLabelsEdits(120,30);
    const QSize sizeMaxEdit(180,30);
    const int spacingForLayout = 5;
    const QMargins contentMaeginForLayout(24,12,24,12);
    const int widthGroupBox = 380;

    QVBoxLayout* layoutDialog = new QVBoxLayout;
    QHBoxLayout* layoutWidgetAndDisplay = new QHBoxLayout;
    QVBoxLayout* layoutPage1 = new QVBoxLayout;
    QVBoxLayout* layoutPage2 = new QVBoxLayout;

    groupboxProperties = new QGroupBox(tr("Properties"));
    groupboxProperties->setAlignment(Qt::AlignCenter);
    QVBoxLayout* layoutProperties = new QVBoxLayout;
    groupboxPropertiesContinued = new QGroupBox(tr("Properies-Continued"));
    groupboxPropertiesContinued->setAlignment(Qt::AlignCenter);
    QVBoxLayout* layoutPropertiesContinued = new QVBoxLayout;

    labelDisplay = new QLabel(tr("For displaying CAD models."));

    chkbxIncluded = new QCheckBox(tr("Included in calculation."));
    groupBoxSCBodyDetails = new QGroupBox(tr("Details"));
    groupBoxSCBodyDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutSCBodyDetails = new QFormLayout;
    layoutSCBodyDetails->setSpacing(spacingForLayout);
    layoutSCBodyDetails->setContentsMargins(contentMaeginForLayout);
    btnGeometryFile = new QPushButton(tr("Geometry File"));
    connect(btnGeometryFile, &QPushButton::clicked, this, &SpacecraftBodyWidget::selectDirOBJfile);
    editGeometryFile  = new QLineEdit();
    editGeometryFile->setMaximumSize(sizeMaxEdit);
    editGeometryFile->setReadOnly(true);
    labelIndex = new QLabel(tr("Body Index"));
    editIndex = new QLineEdit;
    editIndex->setMaximumSize(sizeMaxEdit);
    editIndex->setReadOnly(true);
    labelName = new QLabel(tr("Name"));
    editName  = new QLineEdit;
    editName->setMaximumSize(sizeMaxEdit);
    editName->setReadOnly(true);
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setMaximumSize(sizeMaxEdit);
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setMaximumSize(sizeMaxEdit);
    editSpacecraft->setReadOnly(true);
    btnFlexFile = new QPushButton(tr("Flex File"));
    editFlexFile = new QLineEdit;
    editFlexFile->setMaximumSize(sizeMaxEdit);
    editFlexFile->setReadOnly(true);
    layoutSCBodyDetails->addRow(chkbxIncluded);
    layoutSCBodyDetails->addRow(btnGeometryFile, editGeometryFile);
    layoutSCBodyDetails->addRow(labelMission, editMission);
    layoutSCBodyDetails->addRow(labelSpacecraft, editSpacecraft);
    layoutSCBodyDetails->addRow(labelIndex, editIndex);
    layoutSCBodyDetails->addRow(labelName, editName);
    layoutSCBodyDetails->addRow(btnFlexFile, editFlexFile);
    groupBoxSCBodyDetails->setLayout(layoutSCBodyDetails);

    groupBoxMass = new QGroupBox();
    QFormLayout* layoutMass = new QFormLayout;
    labelMass = new QLabel(tr("Mass (kg?)"));
    editMass  = new QLineEdit;
    editMass->setValidator(new QDoubleValidator);
    layoutMass->addRow(labelMass, editMass);
    groupBoxMass->setLayout(layoutMass);
    groupBoxMass->setMaximumWidth(widthGroupBox);

    groupBoxMomentInertiaMatrix = new QGroupBox(tr("Moment of Inertial Matrix (kg-m^2)"));
     // unit: kg-m^2
    QGridLayout* layoutMomentInertiaMatrix = new QGridLayout();
    layoutMomentInertiaMatrix->setSpacing(spacingForLayout);
    layoutMomentInertiaMatrix->setContentsMargins(contentMaeginForLayout);
    labelMomentInertiaMatrixAxisX_Column = new QLabel(tr("x"));
    labelMomentInertiaMatrixAxisX_Column->setMaximumSize(sizeLabelsEdits);
    labelMomentInertiaMatrixAxisX_Column->setAlignment(Qt::AlignHCenter);
    labelMomentInertiaMatrixAxisX_Row = new QLabel(tr("x"));
    labelMomentInertiaMatrixAxisX_Row->setMaximumSize(sizeLabelsEdits);
    labelMomentInertiaMatrixAxisY_Column = new QLabel(tr("y"));
    labelMomentInertiaMatrixAxisY_Column->setMaximumSize(sizeLabelsEdits);
    labelMomentInertiaMatrixAxisY_Column->setAlignment(Qt::AlignHCenter);
    labelMomentInertiaMatrixAxisY_Row = new QLabel(tr("y"));
    labelMomentInertiaMatrixAxisY_Row->setMaximumSize(sizeLabelsEdits);
    labelMomentInertiaMatrixAxisZ_Column = new QLabel(tr("z"));
    labelMomentInertiaMatrixAxisZ_Column->setMaximumSize(sizeLabelsEdits);
    labelMomentInertiaMatrixAxisZ_Column->setAlignment(Qt::AlignHCenter);
    labelMomentInertiaMatrixAxisZ_Row = new QLabel(tr("z"));
    labelMomentInertiaMatrixAxisZ_Row->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisXX  = new QLineEdit;
    editMomentInertiaMatrixAxisXX->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisXX->setValidator(new QDoubleValidator);
    editMomentInertiaMatrixAxisXY  = new QLineEdit;
    editMomentInertiaMatrixAxisXY->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisXY->setValidator(new QDoubleValidator);
    editMomentInertiaMatrixAxisXZ  = new QLineEdit;
    editMomentInertiaMatrixAxisXZ->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisXZ->setValidator(new QDoubleValidator);
    editMomentInertiaMatrixAxisYX  = new QLineEdit;
    editMomentInertiaMatrixAxisYX->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisYX->setValidator(new QDoubleValidator);
    editMomentInertiaMatrixAxisYY  = new QLineEdit;
    editMomentInertiaMatrixAxisYY->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisYY->setValidator(new QDoubleValidator);
    editMomentInertiaMatrixAxisYZ  = new QLineEdit;
    editMomentInertiaMatrixAxisYZ->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisYZ->setValidator(new QDoubleValidator);
    editMomentInertiaMatrixAxisZX  = new QLineEdit;
    editMomentInertiaMatrixAxisZX->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisZX->setValidator(new QDoubleValidator);
    editMomentInertiaMatrixAxisZY  = new QLineEdit;
    editMomentInertiaMatrixAxisZY->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisZY->setValidator(new QDoubleValidator);
    editMomentInertiaMatrixAxisZZ  = new QLineEdit;
    editMomentInertiaMatrixAxisZZ->setMaximumSize(sizeLabelsEdits);
    editMomentInertiaMatrixAxisZZ->setValidator(new QDoubleValidator);

    layoutMomentInertiaMatrix->addWidget(new QLabel(tr("")), 0,0);
    layoutMomentInertiaMatrix->addWidget(labelMomentInertiaMatrixAxisX_Column,0,1);
    layoutMomentInertiaMatrix->addWidget(labelMomentInertiaMatrixAxisY_Column,0,2);
    layoutMomentInertiaMatrix->addWidget(labelMomentInertiaMatrixAxisZ_Column,0,3);
    layoutMomentInertiaMatrix->addWidget(labelMomentInertiaMatrixAxisX_Row , 1, 0);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisXX , 1, 1);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisXY , 1, 2);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisXZ , 1, 3);
    layoutMomentInertiaMatrix->addWidget(labelMomentInertiaMatrixAxisY_Row , 2, 0);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisYX , 2, 1);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisYY , 2, 2);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisYZ , 2, 3);
    layoutMomentInertiaMatrix->addWidget(labelMomentInertiaMatrixAxisZ_Row , 3, 0);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisZX , 3, 1);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisZY , 3, 2);
    layoutMomentInertiaMatrix->addWidget(editMomentInertiaMatrixAxisZZ , 3, 3);
    groupBoxMomentInertiaMatrix->setLayout(layoutMomentInertiaMatrix);
    groupBoxMomentInertiaMatrix->setMaximumWidth(widthGroupBox);

    groupBoxLocMassCenter = new QGroupBox(tr("Location of Mass Center (m)"));
           // location of mass center in meters
    QGridLayout* layoutLocMassCenter = new QGridLayout();
    layoutLocMassCenter->setSpacing(spacingForLayout);
    layoutLocMassCenter->setContentsMargins(contentMaeginForLayout);
    labelLocMassCenterX = new QLabel(tr("x"));
    labelLocMassCenterX->setMaximumSize(sizeLabelsEdits);
    labelLocMassCenterX->setAlignment(Qt::AlignHCenter);
    labelLocMassCenterY = new QLabel(tr("y"));
    labelLocMassCenterY->setMaximumSize(sizeLabelsEdits);
    labelLocMassCenterY->setAlignment(Qt::AlignHCenter);
    labelLocMassCenterZ = new QLabel(tr("z"));
    labelLocMassCenterZ->setMaximumSize(sizeLabelsEdits);
    labelLocMassCenterZ->setAlignment(Qt::AlignHCenter);
    editLocMassCenterX = new QLineEdit();
    editLocMassCenterX->setValidator(new QDoubleValidator);
    editLocMassCenterX->setMaximumSize(sizeLabelsEdits);
    editLocMassCenterY = new QLineEdit();
    editLocMassCenterY->setValidator(new QDoubleValidator);
    editLocMassCenterY->setMaximumSize(sizeLabelsEdits);
    editLocMassCenterZ = new QLineEdit();
    editLocMassCenterZ->setValidator(new QDoubleValidator);
    editLocMassCenterZ->setMaximumSize(sizeLabelsEdits);
    layoutLocMassCenter->addWidget(labelLocMassCenterX, 0, 0);
    layoutLocMassCenter->addWidget(labelLocMassCenterY, 0, 1);
    layoutLocMassCenter->addWidget(labelLocMassCenterZ, 0, 2);
    layoutLocMassCenter->addWidget(editLocMassCenterX,  1, 0);
    layoutLocMassCenter->addWidget(editLocMassCenterY,  1, 1);
    layoutLocMassCenter->addWidget(editLocMassCenterZ,  1, 2);
    groupBoxLocMassCenter->setLayout(layoutLocMassCenter);
    groupBoxLocMassCenter->setMaximumWidth(widthGroupBox);


    groupBoxConstEmbeddedMomentum = new QGroupBox(tr("Constant Embedded Momentum (Nms)"));  // constant embedded momentum; units: Nms
    QGridLayout* layoutConstEmbeddedMomentum = new QGridLayout();
    layoutConstEmbeddedMomentum->setSpacing(spacingForLayout);
    layoutConstEmbeddedMomentum->setContentsMargins(contentMaeginForLayout);
    labelConstEmbeddedMomentumX = new QLabel(tr("x"));
    labelConstEmbeddedMomentumX->setMaximumSize(sizeLabelsEdits);
    labelConstEmbeddedMomentumX->setAlignment(Qt::AlignHCenter);
    labelConstEmbeddedMomentumY = new QLabel(tr("y"));
    labelConstEmbeddedMomentumY->setMaximumSize(sizeLabelsEdits);
    labelConstEmbeddedMomentumY->setAlignment(Qt::AlignHCenter);
    labelConstEmbeddedMomentumZ = new QLabel(tr("z"));
    labelConstEmbeddedMomentumZ->setMaximumSize(sizeLabelsEdits);
    labelConstEmbeddedMomentumZ->setAlignment(Qt::AlignHCenter);
    editConstEmbeddedMomentumX = new QLineEdit();
    editConstEmbeddedMomentumX->setValidator(new QDoubleValidator);
    editConstEmbeddedMomentumX->setMaximumSize(sizeLabelsEdits);
    editConstEmbeddedMomentumY = new QLineEdit();
    editConstEmbeddedMomentumY->setValidator(new QDoubleValidator);
    editConstEmbeddedMomentumY->setMaximumSize(sizeLabelsEdits);
    editConstEmbeddedMomentumZ = new QLineEdit();
    editConstEmbeddedMomentumZ->setValidator(new QDoubleValidator);
    editConstEmbeddedMomentumZ->setMaximumSize(sizeLabelsEdits);
    layoutConstEmbeddedMomentum->addWidget(labelConstEmbeddedMomentumX, 0,0);
    layoutConstEmbeddedMomentum->addWidget(labelConstEmbeddedMomentumY, 0,1);
    layoutConstEmbeddedMomentum->addWidget(labelConstEmbeddedMomentumZ, 0,2);
    layoutConstEmbeddedMomentum->addWidget(editConstEmbeddedMomentumX , 1,0);
    layoutConstEmbeddedMomentum->addWidget(editConstEmbeddedMomentumY , 1,1);
    layoutConstEmbeddedMomentum->addWidget(editConstEmbeddedMomentumZ , 1,2);
    groupBoxConstEmbeddedMomentum->setLayout(layoutConstEmbeddedMomentum);
    groupBoxConstEmbeddedMomentum->setMaximumWidth(widthGroupBox);


    layoutProperties->addWidget(groupBoxMass);
    groupboxProperties->setLayout(layoutProperties);

    layoutPage1->addWidget(groupBoxSCBodyDetails);
    layoutPage1->addWidget(groupboxProperties);
    tabPage1->setLayout(layoutPage1);

    layoutPropertiesContinued->addWidget(groupBoxLocMassCenter);
    layoutPropertiesContinued->addWidget(groupBoxConstEmbeddedMomentum);
    layoutPropertiesContinued->addWidget(groupBoxMomentInertiaMatrix);
    groupboxPropertiesContinued->setLayout(layoutPropertiesContinued);
    layoutPage2->addWidget(groupboxPropertiesContinued);
    tabPage2->setLayout(layoutPage2);

    tabWidget->addTab(tabPage1, tr("Details/Properties"));
    tabWidget->addTab(tabPage2, tr("Properties-Continued"));

    layoutWidgetAndDisplay->addWidget(tabWidget,1);
    layoutWidgetAndDisplay->addWidget(labelDisplay,1);

    layoutDialog->addLayout(layoutWidgetAndDisplay);
    layoutDialog->addWidget(m_buttonBox);
    setLayout(layoutDialog);
}

void SpacecraftBodyWidget::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, this,
            [=](){this->mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
                                [=](){mapDataFromWidgetToModel();mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});

    connect(editMomentInertiaMatrixAxisXY, &QLineEdit::textChanged,
            editMomentInertiaMatrixAxisYX, &QLineEdit::setText);
    connect(editMomentInertiaMatrixAxisYX, &QLineEdit::textChanged,
            editMomentInertiaMatrixAxisXY, &QLineEdit::setText);

    connect(editMomentInertiaMatrixAxisXZ, &QLineEdit::textChanged,
            editMomentInertiaMatrixAxisZX, &QLineEdit::setText);
    connect(editMomentInertiaMatrixAxisZX, &QLineEdit::textChanged,
            editMomentInertiaMatrixAxisXZ, &QLineEdit::setText);

    connect(editMomentInertiaMatrixAxisYZ, &QLineEdit::textChanged,
            editMomentInertiaMatrixAxisZY, &QLineEdit::setText);
    connect(editMomentInertiaMatrixAxisZY, &QLineEdit::textChanged,
            editMomentInertiaMatrixAxisYZ, &QLineEdit::setText);


    connect(chkbxIncluded, &QCheckBox::stateChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMass, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});


    //connect(btnGeometryFile, &QPushButton::clicked,
    //        m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editGeometryFile, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    //connect(btnFlexFile, &QPushButton::clicked,
    //        m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexFile,  &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editLocMassCenterX, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLocMassCenterY, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLocMassCenterZ, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editConstEmbeddedMomentumX, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editConstEmbeddedMomentumY, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editConstEmbeddedMomentumZ, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editMomentInertiaMatrixAxisXX, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMomentInertiaMatrixAxisXY, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMomentInertiaMatrixAxisXZ, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMomentInertiaMatrixAxisYX, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMomentInertiaMatrixAxisYY, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMomentInertiaMatrixAxisYZ, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMomentInertiaMatrixAxisZX, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMomentInertiaMatrixAxisZY, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMomentInertiaMatrixAxisZZ, &QLineEdit::textChanged,
            m_buttonBox, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void SpacecraftBodyWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

bool SpacecraftBodyWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<SpacecraftBody>())
        return false;
    const int precision = 6;
    SpacecraftBody SCB = m_index.data().value<SpacecraftBody>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();
    QString scbName = SCB.name();

    setWindowTitle(scbName);
    chkbxIncluded->setChecked(SCB.includedInCalculation());
    editIndex->setText(QString::number(SCB.index()));
    editSpacecraft->setText(SC.name());
    editMission->setText(M.name());
    editName->setText(scbName);
    editMass->setText(QString::number(SCB.mass(), 'f', precision));
    editLocMassCenterX->setText(QString::number(SCB.locMassCenter()[0],'f',precision));
    editLocMassCenterY->setText(QString::number(SCB.locMassCenter()[1],'f',precision));
    editLocMassCenterZ->setText(QString::number(SCB.locMassCenter()[2],'f',precision));

    editConstEmbeddedMomentumX->setText(QString::number(SCB.constEmbeddedMomentum()[0],'f',precision));
    editConstEmbeddedMomentumY->setText(QString::number(SCB.constEmbeddedMomentum()[1],'f',precision));
    editConstEmbeddedMomentumZ->setText(QString::number(SCB.constEmbeddedMomentum()[2],'f',precision));

    editMomentInertiaMatrixAxisXX->setText(QString::number(SCB.momentInertiaMatrix()[0][0] ,'f',precision));
    editMomentInertiaMatrixAxisXY->setText(QString::number(SCB.momentInertiaMatrix()[0][1] ,'f',precision));
    editMomentInertiaMatrixAxisXZ->setText(QString::number(SCB.momentInertiaMatrix()[0][2] ,'f',precision));
    editMomentInertiaMatrixAxisYX->setText(QString::number(SCB.momentInertiaMatrix()[1][0] ,'f',precision));
    editMomentInertiaMatrixAxisYY->setText(QString::number(SCB.momentInertiaMatrix()[1][1] ,'f',precision));
    editMomentInertiaMatrixAxisYZ->setText(QString::number(SCB.momentInertiaMatrix()[1][2] ,'f',precision));
    editMomentInertiaMatrixAxisZX->setText(QString::number(SCB.momentInertiaMatrix()[2][0] ,'f',precision));
    editMomentInertiaMatrixAxisZY->setText(QString::number(SCB.momentInertiaMatrix()[2][1] ,'f',precision));
    editMomentInertiaMatrixAxisZZ->setText(QString::number(SCB.momentInertiaMatrix()[2][2] ,'f',precision));
    return true;
}

bool SpacecraftBodyWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid())
        return false;
    SpacecraftBody newSCB = m_index.data().value<SpacecraftBody>();
    QVariant newData = QVariant();

    newSCB.edit(editMass->text().toDouble(),
    {{editMomentInertiaMatrixAxisXX->text().toDouble(), editMomentInertiaMatrixAxisXY->text().toDouble(), editMomentInertiaMatrixAxisXZ->text().toDouble()},
     {editMomentInertiaMatrixAxisYX->text().toDouble(), editMomentInertiaMatrixAxisYY->text().toDouble(), editMomentInertiaMatrixAxisYZ->text().toDouble()},
     {editMomentInertiaMatrixAxisZX->text().toDouble(), editMomentInertiaMatrixAxisZY->text().toDouble(), editMomentInertiaMatrixAxisZZ->text().toDouble()}},
    {editLocMassCenterX->text().toDouble(),editLocMassCenterY->text().toDouble(), editLocMassCenterZ->text().toDouble()},
    {editConstEmbeddedMomentumX->text().toDouble(), editConstEmbeddedMomentumY->text().toDouble(), editConstEmbeddedMomentumZ->text().toDouble()},
                editName->text(),editGeometryFile->text(),
                chkbxIncluded->isChecked());
    newData.setValue(newSCB);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}

void SpacecraftBodyWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftBodyWidget::setRootIndex(const QModelIndex& index)
{
    if (!index.isValid() || !index.data().canConvert<SpacecraftBody>())
        return;
    m_index = index;
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    mapDataFromModelToWidget();
}

void SpacecraftBodyWidget::selectDirOBJfile()
{
    QFileDialog* objFileDialog = new QFileDialog(this);
    geometryFileName = objFileDialog->getOpenFileName(this,
                       tr("Spacecraft Body obj File"), "", tr("CAD Files (*.obj)"));

    editGeometryFile->setText(geometryFileName);
}




/** Widget for Joint Data **/
SpacecraftJointWidget::SpacecraftJointWidget(QWidget *parent) : QDialog(parent)
{
    if (parent)
        parentTabWidget = static_cast<QTabWidget*>(parent);

    undoStack = new QUndoStack(this);
    createActions();
    setupModels();

    //const QSize minSize(800, 600);
    //setMinimumSize(minSize);
    mainTabWidget = new QTabWidget(this);
    msgBox = new QMessageBox;
    tabWidget0 = new QWidget(mainTabWidget);
    tabWidget1 = new QWidget(mainTabWidget);
    tabWidget2 = new QWidget(mainTabWidget);
    tabWidget3 = new QWidget(mainTabWidget);
    tabWidget4 = new QWidget(mainTabWidget);
    tabWidget5 = new QWidget(mainTabWidget);
    tabWidget6 = new QWidget(mainTabWidget);
    tabWidget7 = new QWidget(mainTabWidget);
    labelnameMission = new QLabel(tr("Mission: "));
    labelnameSpacecraft = new QLabel(tr("Spacecraft: "));
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Save  |
                                     QDialogButtonBox::Apply |
                                     QDialogButtonBox::Cancel);

    createWidgets();
    setTabs();
    createConnections();
}

SpacecraftJointWidget::~SpacecraftJointWidget()
{

}

SpacecraftJointWidget::SpacecraftJointWidget(const SpacecraftJointWidget& SJW)
{
    Q_UNUSED(SJW)
}

void SpacecraftJointWidget::setupModels()
{
    m_modelEulerSeqRot = new QStringListModel(list_EulerSeq);
    m_modelGimbalSpherical = new QStringListModel(list_GimbalSpherical);
    m_modelEulerSeqTrn = new QStringListModel(list_EulerSeq);
    m_modelBiGiStaticSeq = new QStringListModel(list_EulerSeq);
    m_modelGoBoStaticSeq = new QStringListModel(list_EulerSeq);
}

void SpacecraftJointWidget::createActions()
{
    m_redoAction = undoStack->createRedoAction(this);
    m_undoAction = undoStack->createUndoAction(this);
}

void SpacecraftJointWidget::createWidgets()
{
    labelJointName = new QLabel;
    const QSize sizelabelCombobox (120, 50);

    /** done **/
    groupBoxBodyIndices = new QGroupBox(tr("Bodies"));
    groupBoxBodyIndices->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutBodyIndices = new QFormLayout;
    layoutBodyIndices->setContentsMargins(30,10,30,10);
    chkbxIncluded = new QCheckBox(tr("Included in the calculation."));
    labelInnerBody = new QLabel(tr("Inner"));
    labelInnerBody->setMaximumSize(sizelabelCombobox);
    labelOuterBody = new QLabel(tr("Outer"));
    labelOuterBody->setMaximumSize(sizelabelCombobox);
    comboboxInnerBody = new QComboBox();
    comboboxInnerBody->setMaximumSize(sizelabelCombobox.width()+50, sizelabelCombobox.height());
    comboboxOuterBody = new QComboBox();
    comboboxOuterBody->setMaximumSize(sizelabelCombobox.width()+50, sizelabelCombobox.height());
    layoutBodyIndices->addRow(labelInnerBody, comboboxInnerBody);
    layoutBodyIndices->addRow(labelOuterBody, comboboxOuterBody);
    layoutBodyIndices->setAlignment(Qt::AlignCenter);
    groupBoxBodyIndices->setLayout(layoutBodyIndices);
    groupBoxBodyIndices->setMaximumSize(440, 120);


    /** done **/
    groupBoxRotTrnDOF = new QGroupBox(tr("Rotations and Translations"));
    groupBoxRotTrnDOF->setAlignment(Qt::AlignHCenter);
    QFormLayout* layoutRotTrnDOF = new QFormLayout;
    labelRotDOF = new QLabel(tr("Degree of Freedom (Rotation)"));
    editRotDOF = new QLineEdit();
    editRotDOF->setValidator(new QIntValidator);
    editRotDOF->setMaximumSize(sizelabelCombobox);
    labelEulerSeqRot = new QLabel(tr("Euler Sequence (Rotation)"));
    comboboxEulerSeqRot = new QComboBox();
    comboboxEulerSeqRot->setModel(m_modelEulerSeqRot);
    comboboxEulerSeqRot->setMaximumSize(sizelabelCombobox);
    labelGimbalSpherical = new QLabel(tr("Rotation Type"));
    comboboxGimbalSpherical = new QComboBox();
    comboboxGimbalSpherical->setMaximumSize(sizelabelCombobox);
    comboboxGimbalSpherical->setModel(m_modelGimbalSpherical);
    labelTrnDOF = new QLabel(tr("Degree of Freedom (Translation)"));
    editTrnDOF = new QLineEdit();
    editTrnDOF->setValidator(new QIntValidator);
    editTrnDOF->setMaximumSize(sizelabelCombobox);
    labelEulerSeqTrn = new QLabel(tr("Euler Sequence (Translation)"));
    comboboxEulerSeqTrn = new QComboBox();
    comboboxEulerSeqTrn->setModel(m_modelEulerSeqTrn);
    comboboxEulerSeqTrn->setMaximumSize(sizelabelCombobox);
    layoutRotTrnDOF->addRow(labelRotDOF, editRotDOF);
    layoutRotTrnDOF->addRow(labelEulerSeqRot, comboboxEulerSeqRot);
    layoutRotTrnDOF->addRow(labelGimbalSpherical, comboboxGimbalSpherical);
    layoutRotTrnDOF->addRow(labelTrnDOF, editTrnDOF);
    layoutRotTrnDOF->addRow(labelEulerSeqTrn, comboboxEulerSeqTrn);
    layoutRotTrnDOF->setSpacing(16);
    layoutRotTrnDOF->setContentsMargins(25,20,25,20);
    groupBoxRotTrnDOF->setLayout(layoutRotTrnDOF);
    groupBoxRotTrnDOF->setMaximumSize(440, 300);

    /** done **/
    groupBoxRotDOFLocked = new QGroupBox(tr("Rotation Lock"));
    groupBoxRotDOFLocked->setAlignment(Qt::AlignCenter);
    groupBoxRotDOFLocked->setMaximumSize(180,80);
    QHBoxLayout* layoutRotDOFLocked = new QHBoxLayout;
    chkbxRotDOFLocked0 = new QCheckBox(QString::fromUtf8("\u03B8\u2081"));
    chkbxRotDOFLocked1 = new QCheckBox(QString::fromUtf8("\u03B8\u2082"));
    chkbxRotDOFLocked2 = new QCheckBox(QString::fromUtf8("\u03B8\u2083"));
    layoutRotDOFLocked->addWidget(chkbxRotDOFLocked0);
    layoutRotDOFLocked->addWidget(chkbxRotDOFLocked1);
    layoutRotDOFLocked->addWidget(chkbxRotDOFLocked2);
    groupBoxRotDOFLocked->setLayout(layoutRotDOFLocked);

    /** done **/
    groupBoxTrnDOFLocked = new QGroupBox(tr("Translation Lock"));
    groupBoxTrnDOFLocked->setAlignment(Qt::AlignCenter);
    groupBoxTrnDOFLocked->setMaximumSize(180,80);
    QHBoxLayout* layoutTrnDOFLocked = new QHBoxLayout;
    chkbxTrnDOFLocked0 = new QCheckBox(tr("x") + QString::fromUtf8("\u2081"));
    chkbxTrnDOFLocked1 = new QCheckBox(tr("x") + QString::fromUtf8("\u2082"));
    chkbxTrnDOFLocked2 = new QCheckBox(tr("x") + QString::fromUtf8("\u2083"));
    layoutTrnDOFLocked->addWidget(chkbxTrnDOFLocked0);
    layoutTrnDOFLocked->addWidget(chkbxTrnDOFLocked1);
    layoutTrnDOFLocked->addWidget(chkbxTrnDOFLocked2);
    groupBoxTrnDOFLocked->setLayout(layoutTrnDOFLocked);

    const QSize sizeGroupBox(255, 180);
    const QSize sizeInitialAngles = sizeGroupBox;
    const int space = 14;
    groupBoxInitialAngles = new QGroupBox(tr("Initial Angles (deg)"));
    groupBoxInitialAngles->setAlignment(Qt::AlignCenter);
    groupBoxInitialAngles->setMaximumSize(sizeInitialAngles);
    QFormLayout* layoutInitialAngles = new QFormLayout;
    layoutInitialAngles->setSpacing(space);
    layoutInitialAngles->setContentsMargins(18,16,18,16);
    labelInitialAngle0 = new QLabel(QString::fromUtf8("\u03B8\u2081"));
    editInitialAngle0 = new QLineEdit;
    editInitialAngle0->setValidator(new QDoubleValidator);
    labelInitialAngle1 = new QLabel(QString::fromUtf8("\u03B8\u2082"));
    editInitialAngle1 = new QLineEdit;
    editInitialAngle1->setValidator(new QDoubleValidator);
    labelInitialAngle2 = new QLabel(QString::fromUtf8("\u03B8\u2083"));
    editInitialAngle2 = new QLineEdit;
    editInitialAngle2->setValidator(new QDoubleValidator);
    layoutInitialAngles->addRow(labelInitialAngle0, editInitialAngle0);
    layoutInitialAngles->addRow(labelInitialAngle1, editInitialAngle1);
    layoutInitialAngles->addRow(labelInitialAngle2, editInitialAngle2);
    groupBoxInitialAngles->setLayout(layoutInitialAngles);

    const QSize sizeInitialRates = sizeGroupBox;
    groupBoxInitialRates = new QGroupBox(tr("Initial Rates (deg/sec)"));
    groupBoxInitialRates->setAlignment(Qt::AlignCenter);
    groupBoxInitialRates->setMaximumSize(sizeInitialRates);
    QFormLayout* layoutInitialRates = new QFormLayout;
    layoutInitialRates->setSpacing(space);
    layoutInitialRates->setContentsMargins(18,16,18,16);
    labelInitialRate0 = new QLabel(QString::fromUtf8("\u03C9\u2081"));
    editInitialRate0 = new QLineEdit;
    editInitialRate0->setValidator(new QDoubleValidator);
    labelInitialRate1 = new QLabel(QString::fromUtf8("\u03C9\u2082"));
    editInitialRate1 = new QLineEdit;
    editInitialRate1->setValidator(new QDoubleValidator);
    labelInitialRate2 = new QLabel(QString::fromUtf8("\u03C9\u2083"));
    editInitialRate2 = new QLineEdit;
    editInitialRate2->setValidator(new QDoubleValidator);
    layoutInitialRates->addRow(labelInitialRate0, editInitialRate0);
    layoutInitialRates->addRow(labelInitialRate1, editInitialRate1);
    layoutInitialRates->addRow(labelInitialRate2, editInitialRate2);
    groupBoxInitialRates->setLayout(layoutInitialRates);


    /** done **/
    const QSize sizeInitialDisplacement = sizeGroupBox;
    groupBoxInitialDisplacement = new QGroupBox(tr("Initial Displacement (m))"));
    groupBoxInitialDisplacement->setAlignment(Qt::AlignCenter);
    groupBoxInitialDisplacement->setMaximumSize(sizeInitialDisplacement);
    QFormLayout* layoutInitialDisplacements = new QFormLayout;
    layoutInitialDisplacements->setSpacing(space);
    layoutInitialDisplacements->setContentsMargins(18,16,18,16);
    labelInitialDisplacement0 = new QLabel(tr("x") + QString::fromUtf8("\u2081"));
    editInitialDisplacement0 = new QLineEdit;
    editInitialDisplacement0->setValidator(new QDoubleValidator);
    labelInitialDisplacement1 = new QLabel(tr("x") + QString::fromUtf8("\u2082"));
    editInitialDisplacement1 = new QLineEdit;
    editInitialDisplacement1->setValidator(new QDoubleValidator);
    labelInitialDisplacement2 = new QLabel(tr("x") + QString::fromUtf8("\u2083"));
    editInitialDisplacement2 = new QLineEdit;
    editInitialDisplacement2->setValidator(new QDoubleValidator);
    layoutInitialDisplacements->addRow(labelInitialDisplacement0, editInitialDisplacement0);
    layoutInitialDisplacements->addRow(labelInitialDisplacement1, editInitialDisplacement1);
    layoutInitialDisplacements->addRow(labelInitialDisplacement2, editInitialDisplacement2);
    groupBoxInitialDisplacement->setLayout(layoutInitialDisplacements);


    /** done **/
    const QSize sizeInitialDisplacementRate = sizeGroupBox;
    groupBoxInitialDisplacementRate = new QGroupBox(tr("Initial Displacement Rate (m/sec)"));
    groupBoxInitialDisplacementRate->setAlignment(Qt::AlignCenter);
    groupBoxInitialDisplacementRate->setMaximumSize(sizeInitialDisplacementRate);
    QFormLayout* layoutInitialDisplacementRate = new QFormLayout;
    layoutInitialDisplacementRate->setSpacing(space);
    layoutInitialDisplacementRate->setContentsMargins(18,16,18,16);
    labelInitialDisplacementRate0 = new QLabel(tr("v") + QString::fromUtf8("\u2081"));
    editInitialDisplacementRate0 = new QLineEdit;
    editInitialDisplacementRate0->setValidator(new QDoubleValidator);
    labelInitialDisplacementRate1 = new QLabel(tr("v") + QString::fromUtf8("\u2082"));
    editInitialDisplacementRate1 = new QLineEdit;
    editInitialDisplacementRate1->setValidator(new QDoubleValidator);
    labelInitialDisplacementRate2 = new QLabel(tr("v") + QString::fromUtf8("\u2083"));
    editInitialDisplacementRate2 = new QLineEdit;
    editInitialDisplacementRate2->setValidator(new QDoubleValidator);
    layoutInitialDisplacementRate->addRow(labelInitialDisplacementRate0, editInitialDisplacementRate0);
    layoutInitialDisplacementRate->addRow(labelInitialDisplacementRate1, editInitialDisplacementRate1);
    layoutInitialDisplacementRate->addRow(labelInitialDisplacementRate2, editInitialDisplacementRate2);
    groupBoxInitialDisplacementRate->setLayout(layoutInitialDisplacementRate);

    /** done **/
    groupBoxBiGiStaticAngleSeq = new QGroupBox(tr("Static Angle: Inner Body-Joint (deg)"));
    groupBoxBiGiStaticAngleSeq->setMaximumSize(sizeGroupBox);
    groupBoxBiGiStaticAngleSeq->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutBiGiStaticAngleSeq = new QFormLayout;
    labelBiGiStaticAngle0 = new QLabel(QString::fromUtf8("\u03A6\u2081"));
    editBiGiStaticAngle0 = new QLineEdit();
    editBiGiStaticAngle0->setValidator(new QDoubleValidator);
    labelBiGiStaticAngle1 = new QLabel(QString::fromUtf8("\u03A6\u2082"));
    editBiGiStaticAngle1 = new QLineEdit();
    editBiGiStaticAngle1->setValidator(new QDoubleValidator);
    labelBiGiStaticAngle2 = new QLabel(QString::fromUtf8("\u03A6\u2083"));
    editBiGiStaticAngle2 = new QLineEdit();
    editBiGiStaticAngle2->setValidator(new QDoubleValidator);
    labelBiGiStaticSeq = new QLabel(tr("Euler \nSequence"));
    comboboxBiGiStaticSeq = new QComboBox;
    comboboxBiGiStaticSeq->setModel(m_modelBiGiStaticSeq);
    layoutBiGiStaticAngleSeq->addRow(labelBiGiStaticAngle0, editBiGiStaticAngle0);
    layoutBiGiStaticAngleSeq->addRow(labelBiGiStaticAngle1, editBiGiStaticAngle1);
    layoutBiGiStaticAngleSeq->addRow(labelBiGiStaticAngle2, editBiGiStaticAngle2);
    layoutBiGiStaticAngleSeq->addRow(labelBiGiStaticSeq, comboboxBiGiStaticSeq);
    groupBoxBiGiStaticAngleSeq->setLayout(layoutBiGiStaticAngleSeq);


    /** done **/
    groupBoxGoBoStaticAngleSeq = new QGroupBox(tr("Static Angle: Joint-Outer Body (deg)"));
    groupBoxGoBoStaticAngleSeq->setMaximumSize(sizeGroupBox);
    groupBoxGoBoStaticAngleSeq->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutGoBoStaticAngleSeq = new QFormLayout;
    labelGoBoStaticAngle0 = new QLabel(QString::fromUtf8("\u03B7\u2081"));
    editGoBoStaticAngle0 = new QLineEdit();
    editGoBoStaticAngle0->setValidator(new QDoubleValidator);
    labelGoBoStaticAngle1 = new QLabel(QString::fromUtf8("\u03B7\u2082"));
    editGoBoStaticAngle1 = new QLineEdit();
    editGoBoStaticAngle1->setValidator(new QDoubleValidator);
    labelGoBoStaticAngle2 = new QLabel(QString::fromUtf8("\u03B7\u2083"));
    editGoBoStaticAngle2 = new QLineEdit();
    editGoBoStaticAngle2->setValidator(new QDoubleValidator);
    labelGoBoStaticSeq = new QLabel(tr("Euler \nSequence"));
    comboboxGoBoStaticSeq = new QComboBox();
    comboboxGoBoStaticSeq->setModel(m_modelGoBoStaticSeq);
    layoutGoBoStaticAngleSeq->addRow(labelGoBoStaticAngle0, editGoBoStaticAngle0);
    layoutGoBoStaticAngleSeq->addRow(labelGoBoStaticAngle1, editGoBoStaticAngle1);
    layoutGoBoStaticAngleSeq->addRow(labelGoBoStaticAngle2, editGoBoStaticAngle2);
    layoutGoBoStaticAngleSeq->addRow(labelGoBoStaticSeq, comboboxGoBoStaticSeq);
    groupBoxGoBoStaticAngleSeq->setLayout(layoutGoBoStaticAngleSeq);

    /** done **/
    groupBoxPositionToInnerBodyOrigin = new QGroupBox(tr("Joint Position w.r.t inner body origin (m)"));
    groupBoxPositionToInnerBodyOrigin->setMaximumSize(sizeGroupBox.width()+35, sizeGroupBox.height());
    groupBoxPositionToInnerBodyOrigin->setAlignment(Qt::AlignCenter);
    groupBoxPositionToInnerBodyOrigin->setMaximumSize(350, 110);
    QHBoxLayout* layoutPositionToInnerBodyOrigin = new QHBoxLayout;
    labelPositionToInnerBodyOrigin0 = new QLabel(tr("i") + QString::fromUtf8("\u2081"));
    editPositionToInnerBodyOrigin0 = new QLineEdit();
    editPositionToInnerBodyOrigin0->setValidator(new QDoubleValidator);
    labelPositionToInnerBodyOrigin1 = new QLabel(tr("i") + QString::fromUtf8("\u2082"));
    editPositionToInnerBodyOrigin1 = new QLineEdit();
    editPositionToInnerBodyOrigin1->setValidator(new QDoubleValidator);
    labelPositionToInnerBodyOrigin2 = new QLabel(tr("i") + QString::fromUtf8("\u2083"));
    editPositionToInnerBodyOrigin2 = new QLineEdit();
    editPositionToInnerBodyOrigin2->setValidator(new QDoubleValidator);
    layoutPositionToInnerBodyOrigin->addWidget(labelPositionToInnerBodyOrigin0);
    layoutPositionToInnerBodyOrigin->addWidget(editPositionToInnerBodyOrigin0);
    layoutPositionToInnerBodyOrigin->addWidget(labelPositionToInnerBodyOrigin1);
    layoutPositionToInnerBodyOrigin->addWidget(editPositionToInnerBodyOrigin1);
    layoutPositionToInnerBodyOrigin->addWidget(labelPositionToInnerBodyOrigin2);
    layoutPositionToInnerBodyOrigin->addWidget(editPositionToInnerBodyOrigin2);
    groupBoxPositionToInnerBodyOrigin->setLayout(layoutPositionToInnerBodyOrigin);

    /** done **/
    groupBoxPositionToOuterBodyOrigin = new QGroupBox(tr("Joint Position w.r.t outer body origin (m)"));
    groupBoxPositionToOuterBodyOrigin->setAlignment(Qt::AlignCenter);
    groupBoxPositionToOuterBodyOrigin->setMaximumSize(350, 110);
    QHBoxLayout* layoutPositionToOuterBodyOrigin = new QHBoxLayout;
    labelPositionToOuterBodyOrigin0 = new QLabel(tr("o") + QString::fromUtf8("\u2081"));
    editPositionToOuterBodyOrigin0 = new QLineEdit();
    editPositionToOuterBodyOrigin0->setValidator(new QDoubleValidator);
    labelPositionToOuterBodyOrigin1 = new QLabel(tr("o") + QString::fromUtf8("\u2082"));
    editPositionToOuterBodyOrigin1 = new QLineEdit();
    editPositionToOuterBodyOrigin1->setValidator(new QDoubleValidator);
    labelPositionToOuterBodyOrigin2 = new QLabel(tr("o") + QString::fromUtf8("\u2083"));
    editPositionToOuterBodyOrigin2 = new QLineEdit();
    editPositionToOuterBodyOrigin2->setValidator(new QDoubleValidator);
    layoutPositionToOuterBodyOrigin->addWidget(labelPositionToOuterBodyOrigin0);
    layoutPositionToOuterBodyOrigin->addWidget(editPositionToOuterBodyOrigin0);
    layoutPositionToOuterBodyOrigin->addWidget(labelPositionToOuterBodyOrigin1);
    layoutPositionToOuterBodyOrigin->addWidget(editPositionToOuterBodyOrigin1);
    layoutPositionToOuterBodyOrigin->addWidget(labelPositionToOuterBodyOrigin2);
    layoutPositionToOuterBodyOrigin->addWidget(editPositionToOuterBodyOrigin2);
    groupBoxPositionToOuterBodyOrigin->setLayout(layoutPositionToOuterBodyOrigin);


    /** done **/
    groupBoxRotSpring = new QGroupBox(tr("Passive Spring Coefficients (Nm/rad)-Rotation"));
    groupBoxRotSpring->setAlignment(Qt::AlignCenter);
    groupBoxRotSpring->setMaximumSize(350, 110);
    QHBoxLayout* layoutRotSpring = new QHBoxLayout;
    labelRotSpring0 = new QLabel(tr("ka") + QString::fromUtf8("\u2081"));
    editRotSpring0 = new QLineEdit;
    editRotSpring0->setValidator(new QDoubleValidator);
    labelRotSpring1 = new QLabel(tr("ka") + QString::fromUtf8("\u2082"));
    editRotSpring1 = new QLineEdit;
    editRotSpring1->setValidator(new QDoubleValidator);
    labelRotSpring2 = new QLabel(tr("ka") + QString::fromUtf8("\u2083"));
    editRotSpring2 = new QLineEdit;
    editRotSpring2->setValidator(new QDoubleValidator);
    layoutRotSpring->addWidget(labelRotSpring0);
    layoutRotSpring->addWidget(editRotSpring0);
    layoutRotSpring->addWidget(labelRotSpring1);
    layoutRotSpring->addWidget(editRotSpring1);
    layoutRotSpring->addWidget(labelRotSpring2);
    layoutRotSpring->addWidget(editRotSpring2);
    groupBoxRotSpring->setLayout(layoutRotSpring);

    /** done **/
    groupBoxRotDamping = new QGroupBox(tr("Passive Damping Coefficients (Nms/rad)-Rotation"));
    groupBoxRotDamping->setAlignment(Qt::AlignCenter);
    groupBoxRotDamping->setMaximumSize(350, 110);
    QHBoxLayout* layoutRotDamping = new QHBoxLayout;
    labelRotDamping0 = new QLabel(tr("ca") + QString::fromUtf8("\u2081"));
    editRotDamping0 = new QLineEdit;
    editRotDamping0->setValidator(new QDoubleValidator);
    labelRotDamping1 = new QLabel(tr("ca") + QString::fromUtf8("\u2082"));
    editRotDamping1 = new QLineEdit;
    editRotDamping1->setValidator(new QDoubleValidator);
    labelRotDamping2 = new QLabel(tr("ca") + QString::fromUtf8("\u2083"));
    editRotDamping2 = new QLineEdit;
    editRotDamping2->setValidator(new QDoubleValidator);
    layoutRotDamping->addWidget(labelRotDamping0);
    layoutRotDamping->addWidget(editRotDamping0);
    layoutRotDamping->addWidget(labelRotDamping1);
    layoutRotDamping->addWidget(editRotDamping1);
    layoutRotDamping->addWidget(labelRotDamping2);
    layoutRotDamping->addWidget(editRotDamping2);
    groupBoxRotDamping->setLayout(layoutRotDamping);


    /** DONE **/
    groupBoxTrnSpring = new QGroupBox(tr("Passive Spring Coefficients (N/m)-Translation"));
    groupBoxTrnSpring->setAlignment(Qt::AlignCenter);
    groupBoxTrnSpring->setMaximumSize(350, 110);
    QHBoxLayout* layoutTrnSpring = new QHBoxLayout;
    labelTrnSpring0 = new QLabel(tr("k")+QString::fromUtf8("\u2081"));
    editTrnSpring0 = new QLineEdit;
    editTrnSpring0->setValidator(new QDoubleValidator);
    labelTrnSpring1 = new QLabel(tr("k")+QString::fromUtf8("\u2082"));
    editTrnSpring1 = new QLineEdit;
    editTrnSpring1->setValidator(new QDoubleValidator);
    labelTrnSpring2 = new QLabel(tr("k")+QString::fromUtf8("\u2083"));
    editTrnSpring2 = new QLineEdit;
    editTrnSpring2->setValidator(new QDoubleValidator);
    layoutTrnSpring->addWidget(labelTrnSpring0);
    layoutTrnSpring->addWidget(editTrnSpring0);
    layoutTrnSpring->addWidget(labelTrnSpring1);
    layoutTrnSpring->addWidget(editTrnSpring1);
    layoutTrnSpring->addWidget(labelTrnSpring2);
    layoutTrnSpring->addWidget(editTrnSpring2);
    groupBoxTrnSpring->setLayout(layoutTrnSpring);

    /** DONE **/
    groupBoxTrnDamping = new QGroupBox(tr("Passive Damping Coefficients (Ns/m)-Translation"));
    groupBoxTrnDamping->setAlignment(Qt::AlignCenter);
    groupBoxTrnDamping->setMaximumSize(350, 110);
    QHBoxLayout* layoutTrnDamping = new QHBoxLayout;
    labelTrnDamping0 = new QLabel(tr("c") + QString::fromUtf8("\u2081"));
    editTrnDamping0 = new QLineEdit;
    editTrnDamping0->setValidator(new QDoubleValidator);
    labelTrnDamping1 = new QLabel(tr("c") + QString::fromUtf8("\u2082"));
    editTrnDamping1 = new QLineEdit;
    editTrnDamping1->setValidator(new QDoubleValidator);
    labelTrnDamping2 = new QLabel(tr("c") + QString::fromUtf8("\u2083"));
    editTrnDamping2 = new QLineEdit;
    editTrnDamping2->setValidator(new QDoubleValidator);
    layoutTrnDamping->addWidget(labelTrnDamping0);
    layoutTrnDamping->addWidget(editTrnDamping0);
    layoutTrnDamping->addWidget(labelTrnDamping1);
    layoutTrnDamping->addWidget(editTrnDamping1);
    layoutTrnDamping->addWidget(labelTrnDamping2);
    layoutTrnDamping->addWidget(editTrnDamping2);
    groupBoxTrnDamping->setLayout(layoutTrnDamping);
}

void SpacecraftJointWidget::createConnections()
{
    connect(buttonBox, &QDialogButtonBox::accepted, this, [=](){this->mapDataFromWidgetToModel();});
    connect(buttonBox, &QDialogButtonBox::accepted, this, [=](){this->renewComboboxBody();});
    connect(buttonBox, &QDialogButtonBox::accepted, undoStack, &QUndoStack::clear);
    connect(buttonBox, &QDialogButtonBox::accepted, undoStack, &QUndoStack::setClean);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){this->mapDataFromWidgetToModel();});
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){this->mapDataFromModelToWidget();});
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){this->renewComboboxBody();});
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            buttonBox->button(QDialogButtonBox::Apply), &QPushButton::setEnabled);
    connect(buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(buttonBox, &QDialogButtonBox::rejected, this,
            [=](){this->mapDataFromModelToWidget();mapDataFromModelToWidget();});


    connect(chkbxIncluded, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(comboboxInnerBody, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxOuterBody, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editRotDOF, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxEulerSeqRot, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxGimbalSpherical, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editTrnDOF, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxEulerSeqTrn, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxRotDOFLocked0, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxRotDOFLocked1, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxRotDOFLocked2, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTrnDOFLocked0, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTrnDOFLocked1, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTrnDOFLocked2, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialAngle0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialAngle1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialAngle2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editInitialRate0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialRate1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialRate2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editInitialDisplacement0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialDisplacement1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialDisplacement2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editInitialDisplacementRate0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialDisplacementRate1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialDisplacementRate2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editBiGiStaticAngle0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editBiGiStaticAngle1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editBiGiStaticAngle2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(comboboxBiGiStaticSeq, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editGoBoStaticAngle0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editGoBoStaticAngle1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editGoBoStaticAngle2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(comboboxGoBoStaticSeq, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editPositionToInnerBodyOrigin0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPositionToInnerBodyOrigin1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPositionToInnerBodyOrigin2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editPositionToOuterBodyOrigin0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPositionToOuterBodyOrigin1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPositionToOuterBodyOrigin2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editRotSpring0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRotSpring1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRotSpring2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editRotDamping0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRotDamping1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRotDamping2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editTrnSpring0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editTrnSpring1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editTrnSpring2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editTrnDamping0, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editTrnDamping1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editTrnDamping2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
             [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void SpacecraftJointWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftJointWidget::setRootIndex(const QModelIndex &index)
{
    if (index.isValid() && index.data().canConvert<Joint>()){
        m_index = index;
        Joint jnt = m_index.data().value<Joint>();
        Spacecraft SC = m_index.parent().data().value<Spacecraft>();
        Mission mission = m_index.parent().parent().parent().data().value<Mission>();
        labelnameMission->setText(tr("Mission: ") + mission.name());
        labelnameSpacecraft->setText(tr("Spacecraft: ") + SC.name());
        setWindowTitle(jnt.name());
        /*
        m_qvecBodyInner.clear();
        m_qvecBodyOuter.clear();
        m_qvecBodyInner.append(tr(""));
        m_qvecBodyOuter.append(tr(""));
        comboboxInnerBody->clear();
        comboboxOuterBody->clear();

        for (int index = 0; index < SC.numberOfBodies(); ++index)
        {
            m_qvecBodyInner.append(SC.body(index)->name());
            m_qvecBodyOuter.append(SC.body(index)->name());
        }
        comboboxInnerBody->addItems(m_qvecBodyInner);
        comboboxOuterBody->addItems(m_qvecBodyOuter);
        */
        enableItemComboboxBody();
        mapDataFromModelToWidget();
    }
    else
        m_index = QModelIndex();
}

void SpacecraftJointWidget::renewComboboxBody()
{
    QString message = QString();
    QString title = QString();
    if (comboboxInnerBody->currentText() == comboboxOuterBody->currentText() ||
        comboboxInnerBody->currentText().isEmpty() || comboboxOuterBody->currentText().isEmpty())
    {
        if (comboboxInnerBody->currentText() == comboboxOuterBody->currentText() &&
                !comboboxInnerBody->currentText().isEmpty())
        {
            message = tr("This joint won't be included in the simulation since the inner body is the same as the outer body.");
            title = tr("Duplicated Spacecraft Bodies");
        }
        else if (comboboxInnerBody->currentText().isEmpty() || comboboxOuterBody->currentText().isEmpty())
        {
            message = tr("This joint won't be included in the simulation since at least one of the two bodies is missing.");
            title = tr("Missing Spacecraft Bodies");
        }
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setText(message);
        msgBox->setWindowTitle(title);
        msgBox->exec();
    }
    return;
}


void SpacecraftJointWidget::enableItemComboboxBody()
{
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    m_qvecBodyInner.clear();
    m_qvecBodyOuter.clear();
    m_qvecBodyInner.append(tr(""));
    m_qvecBodyOuter.append(tr(""));
    comboboxInnerBody->clear();
    comboboxOuterBody->clear();

    for (int index = 0; index < SC.numberOfBodies(); ++index)
    {
        if (SC.body(index)->includedInCalculation()){
            m_qvecBodyInner.append(SC.body(index)->name());
            m_qvecBodyOuter.append(SC.body(index)->name());
        }
    }
    comboboxInnerBody->addItems(m_qvecBodyInner);
    comboboxOuterBody->addItems(m_qvecBodyOuter);
}

bool SpacecraftJointWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<Joint>())
        return false;

    QVariant dataFromModel = QVariant();
    dataFromModel = m_index.data();
    Joint jointFromModel = dataFromModel.value<Joint>();
    Spacecraft SCfromModel = m_index.parent().data().value<Spacecraft>();

    const int precision = 6;

    chkbxIncluded->setChecked(jointFromModel.includedInCalculation());

    comboboxInnerBody->setCurrentText(jointFromModel.nameBodyInner());
    comboboxOuterBody->setCurrentText(jointFromModel.nameBodyOuter());

    editRotDOF->setText(QString::number(jointFromModel.RotDOF()));
    comboboxEulerSeqRot->setCurrentText(jointFromModel.RotSeq());
    comboboxGimbalSpherical->setCurrentText(map_GimbalSpherical.value(jointFromModel.jointType().toUpper()));

    editTrnDOF->setText(QString::number(jointFromModel.TrnDOF()));
    comboboxEulerSeqTrn->setCurrentText(jointFromModel.TrnSeq());

    chkbxRotDOFLocked0->setChecked(jointFromModel.RotLocked()[0]);
    chkbxRotDOFLocked1->setChecked(jointFromModel.RotLocked()[1]);
    chkbxRotDOFLocked2->setChecked(jointFromModel.RotLocked()[2]);

    chkbxTrnDOFLocked0->setChecked(jointFromModel.TrnLocked()[0]);
    chkbxTrnDOFLocked1->setChecked(jointFromModel.TrnLocked()[1]);
    chkbxTrnDOFLocked2->setChecked(jointFromModel.TrnLocked()[2]);

    editInitialAngle0->setText(QString::number(jointFromModel.initialAngles()[0], 'f', precision));
    editInitialAngle1->setText(QString::number(jointFromModel.initialAngles()[1], 'f', precision));
    editInitialAngle2->setText(QString::number(jointFromModel.initialAngles()[2], 'f', precision));

    editInitialRate0->setText(QString::number(jointFromModel.initialRates()[0], 'f', precision));
    editInitialRate1->setText(QString::number(jointFromModel.initialRates()[1], 'f', precision));
    editInitialRate2->setText(QString::number(jointFromModel.initialRates()[2], 'f', precision));

    editInitialDisplacement0->setText(QString::number(jointFromModel.initialDisplacement()[0], 'f', precision));
    editInitialDisplacement1->setText(QString::number(jointFromModel.initialDisplacement()[1], 'f', precision));
    editInitialDisplacement2->setText(QString::number(jointFromModel.initialDisplacement()[2], 'f', precision));

    editInitialDisplacementRate0->setText(QString::number(jointFromModel.initialDisplacementRate()[0], 'f', precision));
    editInitialDisplacementRate1->setText(QString::number(jointFromModel.initialDisplacementRate()[1], 'f', precision));
    editInitialDisplacementRate2->setText(QString::number(jointFromModel.initialDisplacementRate()[2], 'f', precision));

    editBiGiStaticAngle0->setText(QString::number(jointFromModel.StaticAngBiGi()[0],'f', precision));
    editBiGiStaticAngle1->setText(QString::number(jointFromModel.StaticAngBiGi()[1],'f', precision));
    editBiGiStaticAngle2->setText(QString::number(jointFromModel.StaticAngBiGi()[2],'f', precision));
    comboboxBiGiStaticSeq->setCurrentText(jointFromModel.BiGiSeq());

    editGoBoStaticAngle0->setText(QString::number(jointFromModel.StaticAngGoBo()[0],'f', precision));
    editGoBoStaticAngle1->setText(QString::number(jointFromModel.StaticAngGoBo()[1],'f', precision));
    editGoBoStaticAngle2->setText(QString::number(jointFromModel.StaticAngGoBo()[2],'f', precision));
    comboboxGoBoStaticSeq->setCurrentText(jointFromModel.GoBoSeq());

    editPositionToInnerBodyOrigin0->setText(QString::number(jointFromModel.jointPosInnerBody()[0],'f',precision));
    editPositionToInnerBodyOrigin1->setText(QString::number(jointFromModel.jointPosInnerBody()[1],'f',precision));
    editPositionToInnerBodyOrigin2->setText(QString::number(jointFromModel.jointPosInnerBody()[2],'f',precision));

    editPositionToOuterBodyOrigin0->setText(QString::number(jointFromModel.jointPosOuterBody()[0],'f',precision));
    editPositionToOuterBodyOrigin1->setText(QString::number(jointFromModel.jointPosOuterBody()[1],'f',precision));
    editPositionToOuterBodyOrigin2->setText(QString::number(jointFromModel.jointPosOuterBody()[2],'f',precision));

    editRotSpring0->setText(QString::number(jointFromModel.rotPassiveSpringCoeff()[0], 'f', precision));
    editRotSpring1->setText(QString::number(jointFromModel.rotPassiveSpringCoeff()[1], 'f', precision));
    editRotSpring2->setText(QString::number(jointFromModel.rotPassiveSpringCoeff()[2], 'f', precision));

    editRotDamping0->setText(QString::number(jointFromModel.rotPassiveDampingCoeff()[0],'f', precision));
    editRotDamping1->setText(QString::number(jointFromModel.rotPassiveDampingCoeff()[1],'f', precision));
    editRotDamping2->setText(QString::number(jointFromModel.rotPassiveDampingCoeff()[2],'f', precision));

    editTrnSpring0->setText(QString::number(jointFromModel.trnPassiveSpringCoeff()[0],'f', precision));
    editTrnSpring1->setText(QString::number(jointFromModel.trnPassiveSpringCoeff()[1],'f', precision));
    editTrnSpring2->setText(QString::number(jointFromModel.trnPassiveSpringCoeff()[2],'f', precision));

    editTrnDamping0->setText(QString::number(jointFromModel.trnPassiveDampingCoeff()[0],'f',precision));
    editTrnDamping1->setText(QString::number(jointFromModel.trnPassiveDampingCoeff()[1],'f',precision));
    editTrnDamping2->setText(QString::number(jointFromModel.trnPassiveDampingCoeff()[2],'f',precision));
    return true;
}

bool SpacecraftJointWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<Joint>())
        return false;
    QVariant dataFromWidget = QVariant();
    Joint jointFromWidget = m_index.data().value<Joint>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();

    int indexBodyInner = -1;
    int indexBodyOuter = -1;
    if (!comboboxInnerBody->currentText().isEmpty())
        indexBodyInner = comboboxInnerBody->currentText().split("-")[1].toInt();
    if (!comboboxOuterBody->currentText().isEmpty())
        indexBodyOuter = comboboxOuterBody->currentText().split("-")[1].toInt();


    if (comboboxInnerBody->currentText().isEmpty() || comboboxOuterBody->currentText().isEmpty() ||
        comboboxInnerBody->currentText() == comboboxOuterBody->currentText())
    {
        chkbxIncluded->setChecked(false);
    }


    jointFromWidget.edit(indexBodyInner, indexBodyOuter ,
                         editRotDOF->text().toUInt()  , comboboxEulerSeqRot->currentText(),
                         map_GimbalSpherical.value(comboboxGimbalSpherical->currentText()),
                         editTrnDOF->text().toUInt(), comboboxEulerSeqTrn->currentText(),
    {chkbxRotDOFLocked0->isChecked(), chkbxRotDOFLocked1->isChecked(), chkbxRotDOFLocked2->isChecked()},
    {chkbxTrnDOFLocked0->isChecked(), chkbxTrnDOFLocked1->isChecked(), chkbxTrnDOFLocked2->isChecked()},
    {editInitialAngle0->text().toDouble(),editInitialAngle1->text().toDouble(), editInitialAngle2->text().toDouble()},
    {editInitialRate0->text().toDouble(), editInitialRate1->text().toDouble(), editInitialRate2->text().toDouble()},
    {editInitialDisplacement0->text().toDouble(), editInitialDisplacement1->text().toDouble(), editInitialDisplacement2->text().toDouble()},
    {editInitialDisplacementRate0->text().toDouble(), editInitialDisplacementRate1->text().toDouble(), editInitialDisplacementRate2->text().toDouble()},
    {editBiGiStaticAngle0->text().toDouble(), editBiGiStaticAngle1->text().toDouble(), editBiGiStaticAngle2->text().toDouble()}, comboboxBiGiStaticSeq->currentText(),
    {editGoBoStaticAngle0->text().toDouble(), editGoBoStaticAngle1->text().toDouble(), editGoBoStaticAngle2->text().toDouble()}, comboboxGoBoStaticSeq->currentText(),
    {editPositionToInnerBodyOrigin0->text().toDouble(), editPositionToInnerBodyOrigin1->text().toDouble(), editPositionToInnerBodyOrigin2->text().toDouble()},
    {editPositionToOuterBodyOrigin0->text().toDouble(), editPositionToOuterBodyOrigin1->text().toDouble(), editPositionToOuterBodyOrigin2->text().toDouble()},
    {editRotSpring0->text().toDouble(), editRotSpring1->text().toDouble(), editRotSpring2->text().toDouble()},
    {editRotDamping0->text().toDouble(), editRotDamping1->text().toDouble(), editRotDamping2->text().toDouble()},
    {editTrnSpring0->text().toDouble(), editTrnSpring1->text().toDouble(), editTrnSpring2->text().toDouble()},
    {editTrnDamping0->text().toDouble(), editTrnDamping1->text().toDouble(), editTrnDamping2->text().toDouble()},
                         chkbxIncluded->isChecked());

    dataFromWidget.setValue(jointFromWidget);
    QUndoCommand* editCommand = new EditCommand(m_model , m_index, dataFromWidget);
    undoStack->push(editCommand);

    return true;
}

void SpacecraftJointWidget::setTabs()
{
    QHBoxLayout* layoutWidgetAndDisplay = new QHBoxLayout;
    QLabel* labelDisplay = new QLabel(tr("For CAD Model Display"));

    QVBoxLayout* layoutTabWidget0 = new QVBoxLayout;
    layoutTabWidget0->addWidget(chkbxIncluded);
    layoutTabWidget0->addWidget(groupBoxBodyIndices);
    layoutTabWidget0->setSpacing(18);
    tabWidget0->setLayout(layoutTabWidget0);

    QVBoxLayout* layoutTabWidget1 = new QVBoxLayout;
    QHBoxLayout* layoutTabWidget1RotationTranslationLock = new QHBoxLayout;
    layoutTabWidget1RotationTranslationLock->addWidget(groupBoxRotDOFLocked, 1, Qt::AlignCenter);
    layoutTabWidget1RotationTranslationLock->addWidget(groupBoxTrnDOFLocked, 1, Qt::AlignCenter);
    layoutTabWidget1->addWidget(groupBoxRotTrnDOF,0, Qt::AlignCenter);
    layoutTabWidget1->addLayout(layoutTabWidget1RotationTranslationLock,0);
    layoutTabWidget1->setSpacing(18);
    tabWidget1->setLayout(layoutTabWidget1);

    QVBoxLayout* layoutTabWidget2 = new QVBoxLayout;
    layoutTabWidget2->addWidget(groupBoxInitialAngles, 1, Qt::AlignCenter);
    layoutTabWidget2->addWidget(groupBoxInitialRates , 1, Qt::AlignCenter);
    layoutTabWidget2->setSpacing(18);
    tabWidget2->setLayout(layoutTabWidget2);

    QVBoxLayout* layoutTabWidget3 = new QVBoxLayout;
    layoutTabWidget3->addWidget(groupBoxInitialDisplacement, 1, Qt::AlignCenter);
    layoutTabWidget3->addWidget(groupBoxInitialDisplacementRate, 1, Qt::AlignCenter);
    layoutTabWidget3->setSpacing(18);
    tabWidget3->setLayout(layoutTabWidget3);

    QVBoxLayout* layoutTabWidget4 = new QVBoxLayout;
    layoutTabWidget4->addWidget(groupBoxBiGiStaticAngleSeq, 1, Qt::AlignCenter);
    layoutTabWidget4->addWidget(groupBoxGoBoStaticAngleSeq, 1, Qt::AlignCenter);
    layoutTabWidget4->setSpacing(18);
    tabWidget4->setLayout(layoutTabWidget4);

    QVBoxLayout* layoutTabWidget5 = new QVBoxLayout;
    layoutTabWidget5->addWidget(groupBoxPositionToInnerBodyOrigin, 1, Qt::AlignCenter);
    layoutTabWidget5->addWidget(groupBoxPositionToOuterBodyOrigin, 1, Qt::AlignCenter);
    layoutTabWidget5->setSpacing(18);
    tabWidget5->setLayout(layoutTabWidget5);

    QVBoxLayout* layoutTabWidget6 = new QVBoxLayout;
    layoutTabWidget6->addWidget(groupBoxRotSpring  , 1, Qt::AlignCenter);
    layoutTabWidget6->addWidget(groupBoxRotDamping , 1, Qt::AlignCenter);
    layoutTabWidget6->setSpacing(18);
    tabWidget6->setLayout(layoutTabWidget6);

    QVBoxLayout* layoutTabWidget7 = new QVBoxLayout;
    layoutTabWidget7->addWidget(groupBoxTrnSpring  , 1, Qt::AlignCenter);
    layoutTabWidget7->addWidget(groupBoxTrnDamping , 1, Qt::AlignCenter);
    layoutTabWidget7->setSpacing(18);
    tabWidget7->setLayout(layoutTabWidget7);

    mainTabWidget->addTab(tabWidget0, tr("Joint Setting 0"));
    mainTabWidget->addTab(tabWidget1, tr("Joint Setting 1"));
    mainTabWidget->addTab(tabWidget2, tr("Joint Setting 2"));
    mainTabWidget->addTab(tabWidget3, tr("Joint Setting 3"));
    mainTabWidget->addTab(tabWidget4, tr("Joint Setting 4"));
    mainTabWidget->addTab(tabWidget5, tr("Joint Setting 5"));
    mainTabWidget->addTab(tabWidget6, tr("Joint Setting 6"));
    mainTabWidget->addTab(tabWidget7, tr("Joint Setting 7"));

    layoutWidgetAndDisplay->addWidget(mainTabWidget,1);
    layoutWidgetAndDisplay->addWidget(labelDisplay,1);

    QVBoxLayout* layoutMainJointWidget = new QVBoxLayout;
    layoutMainJointWidget->addWidget(labelnameMission);
    layoutMainJointWidget->addWidget(labelnameSpacecraft);
    layoutMainJointWidget->addLayout(layoutWidgetAndDisplay);
    layoutMainJointWidget->addWidget(buttonBox);
    setLayout(layoutMainJointWidget);
}


/** Widget for Wheel Data **/

SpacecraftWheelWidget::SpacecraftWheelWidget(QWidget* parent) : QDialog(parent)
{
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    setWindowTitle(tr("Wheel"));
    createWidgets();
    createActions();
    createConnections();
}

SpacecraftWheelWidget::~SpacecraftWheelWidget()
{

}

void SpacecraftWheelWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftWheelWidget::createWidgets()
{
    const int spacingProperties = 18;
    QGridLayout* layoutAll = new QGridLayout;
    groupBoxDetails = new QGroupBox(tr("Wheel Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in the calculation."));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxProperties = new QGroupBox(tr("Properties"));
    groupBoxProperties->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutProperties = new QFormLayout;
    layoutProperties->setSpacing(spacingProperties);
    labelInitialMomentum = new QLabel(tr("Initial Momentum (N-m-sec)"));
    editInitialMomentum = new QLineEdit;
    editInitialMomentum->setValidator(new QDoubleValidator);

    groupBoxAxisComponent = new QGroupBox(tr("Wheel Axis Components"));
    QFormLayout* layoutAxisComponent = new QFormLayout;
    labelWheelAxisComponentX = new QLabel(tr("X"));
    editWheelAxisComponentX = new QLineEdit;
    editWheelAxisComponentX->setValidator(new QDoubleValidator);
    labelWheelAxisComponentY = new QLabel(tr("Y"));
    editWheelAxisComponentY = new QLineEdit;
    editWheelAxisComponentY->setValidator(new QDoubleValidator);
    labelWheelAxisComponentZ = new QLabel(tr("Z"));
    editWheelAxisComponentZ = new QLineEdit;
    editWheelAxisComponentZ->setValidator(new QDoubleValidator);
    btnNormalize = new QPushButton(tr("Normalize"));
    layoutAxisComponent->addRow(labelWheelAxisComponentX, editWheelAxisComponentX);
    layoutAxisComponent->addRow(labelWheelAxisComponentY, editWheelAxisComponentY);
    layoutAxisComponent->addRow(labelWheelAxisComponentZ, editWheelAxisComponentZ);
    layoutAxisComponent->addRow(new QLabel, btnNormalize);
    groupBoxAxisComponent->setLayout(layoutAxisComponent);

    labelMaxTorque = new QLabel(tr("Max Torque (N-m)"));
    editMaxTorque = new QLineEdit;
    editMaxTorque->setValidator(new QDoubleValidator);
    labelMaxMomentum = new QLabel(tr("Max Momentum (N-m-sec)"));
    editMaxMomentum = new QLineEdit;
    editMaxMomentum->setValidator(new QDoubleValidator);
    labelWheelRotorInertia = new QLabel(tr("Wheel Rotor Inertia (kg-m")+QString::fromUtf8("\u00B2")+tr(")"));
    editWheelRotorInertia = new QLineEdit;
    editWheelRotorInertia->setValidator(new QDoubleValidator);
    labelStaticImbalance = new QLabel(tr("Static Imbalance (g-cm)"));
    editStaticImbalance = new QLineEdit;
    editStaticImbalance->setValidator(new QDoubleValidator);
    labelDynamicImbalance = new QLabel(tr("Dynamic Imbalance (g-cm")+QString::fromUtf8("\u00B2")+tr(")"));
    editDynamicImbalance = new QLineEdit;
    editDynamicImbalance->setValidator(new QDoubleValidator);
    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);

    layoutProperties->addRow(labelInitialMomentum, editInitialMomentum);
    layoutProperties->addRow(groupBoxAxisComponent);
    layoutProperties->addRow(labelMaxTorque, editMaxTorque);
    layoutProperties->addRow(labelMaxMomentum, editMaxMomentum);
    layoutProperties->addRow(labelWheelRotorInertia, editWheelRotorInertia);
    layoutProperties->addRow(labelStaticImbalance, editStaticImbalance);
    layoutProperties->addRow(labelDynamicImbalance, editDynamicImbalance);
    layoutProperties->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxProperties->setLayout(layoutProperties);

    layoutAll->addWidget(groupBoxDetails, 0,0,1,1);
    layoutAll->addWidget(groupBoxProperties, 0,1,1,1);
    layoutAll->addWidget(m_buttonBox, 1,0,1,2);

    setLayout(layoutAll);

}

void SpacecraftWheelWidget::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this,
            [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, [=](){m_undoStack->clear();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, [=](){m_undoStack->setClean();});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, [=](){mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){mapDataFromWidgetToModel();mapDataFromModelToWidget();});

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialMomentum, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editWheelAxisComponentX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editWheelAxisComponentY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editWheelAxisComponentZ, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMaxTorque, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMaxMomentum, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editWheelRotorInertia, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editStaticImbalance, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDynamicImbalance, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(btnNormalize, &QPushButton::clicked, this, &SpacecraftWheelWidget::normalizeAxisVector);
}

void SpacecraftWheelWidget::normalizeAxisVector()
{
    const int precision = 6;
    using std::sqrt;
    double componentX = editWheelAxisComponentX->text().toDouble();
    double componentY = editWheelAxisComponentY->text().toDouble();
    double componentZ = editWheelAxisComponentZ->text().toDouble();
    double norm = sqrt(componentX*componentX + componentY*componentY + componentZ*componentZ);
    if (abs(norm - 0.0) < 0.000001)
        return;
    componentX = componentX/norm;
    componentY = componentY/norm;
    componentZ = componentZ/norm;
    editWheelAxisComponentX->setText(QString::number(componentX,'f', precision));
    editWheelAxisComponentY->setText(QString::number(componentY,'f', precision));
    editWheelAxisComponentZ->setText(QString::number(componentZ,'f', precision));
    return;
}

bool SpacecraftWheelWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<Wheel>())
        return false;
    const int precision = 6;
    Wheel whlFromModel = m_index.data().value<Wheel>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();

    setWindowTitle(whlFromModel.name());
    chkbxIncluded->setChecked(whlFromModel.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());

    editInitialMomentum->setText(QString::number(whlFromModel.initialMomentum(),'f', precision));
    editWheelAxisComponentX->setText(QString::number(whlFromModel.wheelAxisComp()[0],'f', precision));
    editWheelAxisComponentY->setText(QString::number(whlFromModel.wheelAxisComp()[1],'f', precision));
    editWheelAxisComponentZ->setText(QString::number(whlFromModel.wheelAxisComp()[2],'f', precision));

    editMaxTorque->setText(QString::number(whlFromModel.maxTorque(),'f', precision));
    editMaxMomentum->setText(QString::number(whlFromModel.maxMomentum(),'f', precision));
    editWheelRotorInertia->setText(QString::number(whlFromModel.wheelRotorInertia(),'f', precision));
    editStaticImbalance->setText(QString::number(whlFromModel.staticImbalance(),'f', precision));
    editDynamicImbalance->setText(QString::number(whlFromModel.dynamicImbalance(),'f', precision));
    editFlexNodeIndex->setText(QString::number(whlFromModel.flexNodeIndex()));
    return true;
}

bool SpacecraftWheelWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<Wheel>())
        return false;

    QVariant newData = QVariant();
    Wheel newWhl = m_index.data().value<Wheel>();
    newWhl.edit(editInitialMomentum->text().toDouble(),
    {editWheelAxisComponentX->text().toDouble(), editWheelAxisComponentY->text().toDouble(), editWheelAxisComponentZ->text().toDouble()},
                editMaxTorque->text().toDouble(), editMaxMomentum->text().toDouble(),
                editWheelRotorInertia->text().toDouble(), editStaticImbalance->text().toDouble(),
                editDynamicImbalance->text().toDouble(), editFlexNodeIndex->text().toUInt(),
                chkbxIncluded->isChecked());

    newData.setValue(newWhl);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}

void SpacecraftWheelWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftWheelWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<Wheel>())
        return;
    m_index = index;
    mapDataFromModelToWidget();
}


/** Widget for Magnetic Torquer Bar Data **/

SpacecraftMTBWidget::SpacecraftMTBWidget(QWidget* parent) : QDialog(parent)
{
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
    setWindowTitle(tr("Magnetic Torquer Bar"));
}

SpacecraftMTBWidget::~SpacecraftMTBWidget()
{
}

void SpacecraftMTBWidget::setModel(QAbstractItemModel* model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}
void SpacecraftMTBWidget::setRootIndex(const QModelIndex& index)
{
    if (!index.isValid() || !index.data().canConvert<MagTorquer>())
        return;
    m_index = index;
    mapDataFromModelToWidget();
}

void SpacecraftMTBWidget::createWidgets()
{
    const int spacingAll = 25;
    const int spaceingProperties = 18;
    QFormLayout* layoutAll = new QFormLayout;
    layoutAll->setSpacing(spacingAll);
    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in the calculation."));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxProperties = new QGroupBox(tr("Properties"));
    groupBoxProperties->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutProperties = new QFormLayout;
    layoutProperties->setSpacing(spaceingProperties);
    labelSaturation = new QLabel(tr("Saturation (A-m") + QString::fromUtf8("\u00B2")+tr(")"));
    editSaturation = new QLineEdit;
    editSaturation->setValidator(new QDoubleValidator);
    groupBoxMTBAxisComponent = new QGroupBox(tr("MTB Axis Components"));
    QFormLayout* layoutMTBAxisComponebt = new QFormLayout;
    labelMTBAxisComponentX = new QLabel(tr("X"));
    editMTBAxisComponentX = new QLineEdit;
    editMTBAxisComponentX->setValidator(new QDoubleValidator);
    labelMTBAxisComponentY = new QLabel(tr("Y"));
    editMTBAxisComponentY = new QLineEdit;
    editMTBAxisComponentY->setValidator(new QDoubleValidator);
    labelMTBAxisComponentZ = new QLabel(tr("Z"));
    editMTBAxisComponentZ = new QLineEdit;
    editMTBAxisComponentZ->setValidator(new QDoubleValidator);
    btnNormalize = new QPushButton(tr("Normalize"));
    layoutMTBAxisComponebt->addRow(labelMTBAxisComponentX, editMTBAxisComponentX);
    layoutMTBAxisComponebt->addRow(labelMTBAxisComponentY, editMTBAxisComponentY);
    layoutMTBAxisComponebt->addRow(labelMTBAxisComponentZ, editMTBAxisComponentZ);
    layoutMTBAxisComponebt->addRow(new QLabel, btnNormalize);
    groupBoxMTBAxisComponent->setLayout(layoutMTBAxisComponebt);
    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);
    layoutProperties->addRow(labelSaturation, editSaturation);
    layoutProperties->addRow(groupBoxMTBAxisComponent);
    layoutProperties->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxProperties->setLayout(layoutProperties);

    layoutAll->addRow(groupBoxDetails);
    layoutAll->addRow(groupBoxProperties);
    layoutAll->addRow(m_buttonBox);
    setLayout(layoutAll);
}

void SpacecraftMTBWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftMTBWidget::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this,
            [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, [=](){m_undoStack->clear();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, [=](){m_undoStack->setClean();});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, [=](){mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){mapDataFromWidgetToModel();mapDataFromModelToWidget();});

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSaturation, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMTBAxisComponentX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMTBAxisComponentY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMTBAxisComponentZ, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(btnNormalize, &QPushButton::clicked, this, &SpacecraftMTBWidget::normalizeAxisVector);
}

void SpacecraftMTBWidget::normalizeAxisVector()
{
    const int precision = 6;
    using std::sqrt;
    double componentX = editMTBAxisComponentX->text().toDouble();
    double componentY = editMTBAxisComponentY->text().toDouble();
    double componentZ = editMTBAxisComponentZ->text().toDouble();
    double norm = sqrt(componentX*componentX + componentY*componentY + componentZ*componentZ);
    if (abs(norm - 0.0) < 0.000001)
        return;
    componentX = componentX/norm;
    componentY = componentY/norm;
    componentZ = componentZ/norm;
    editMTBAxisComponentX->setText(QString::number(componentX,'f', precision));
    editMTBAxisComponentY->setText(QString::number(componentY,'f', precision));
    editMTBAxisComponentZ->setText(QString::number(componentZ,'f', precision));
    return;
}


bool SpacecraftMTBWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<MagTorquer>())
        return false;
    const int precision = 6;
    MagTorquer MTBfromModel = m_index.data().value<MagTorquer>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();

    setWindowTitle(MTBfromModel.name());
    chkbxIncluded->setChecked(MTBfromModel.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());

    editSaturation->setText(QString::number(MTBfromModel.saturation(),'f',precision));
    editMTBAxisComponentX->setText(QString::number(MTBfromModel.MTBaxis()[0],'f',precision));
    editMTBAxisComponentY->setText(QString::number(MTBfromModel.MTBaxis()[1],'f',precision));
    editMTBAxisComponentZ->setText(QString::number(MTBfromModel.MTBaxis()[2],'f',precision));
    editFlexNodeIndex->setText(QString::number(MTBfromModel.flexNodeIndex()));
    return true;
}

bool SpacecraftMTBWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<MagTorquer>())
        return false;
    QVariant newData = QVariant();
    MagTorquer newMTB = m_index.data().value<MagTorquer>();

    newMTB.edit(editSaturation->text().toDouble(),
    {editMTBAxisComponentX->text().toDouble(), editMTBAxisComponentY->text().toDouble(), editMTBAxisComponentZ->text().toDouble()},
                editFlexNodeIndex->text().toUInt(),
                chkbxIncluded->isChecked());

    newData.setValue(newMTB);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}


/** Widget for Thruster Data **/
SpacecraftThrusterWidget::SpacecraftThrusterWidget(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Thruster");
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save|
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}

SpacecraftThrusterWidget::~SpacecraftThrusterWidget()
{

}

void SpacecraftThrusterWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftThrusterWidget::renewCombobox(const QModelIndex& index)
{
    if (!index.isValid() || !index.data().canConvert<Thruster>())
        return;

    Spacecraft SC = index.parent().data().value<Spacecraft>();
    QStringList list_SpacecraftBody;
    list_SpacecraftBody.append("");
    for (int i = 0; i < SC.numberOfBodies(); ++i)
    {
        if (SC.body(i)->includedInCalculation())
            list_SpacecraftBody.append(SC.body(i)->name());
    }
    comboboxBody->clear();
    comboboxBody->addItems(list_SpacecraftBody);
}

void SpacecraftThrusterWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<Thruster>())
        return;
    m_index = index;
    renewCombobox(m_index);
    mapDataFromModelToWidget();
}

void SpacecraftThrusterWidget::createWidgets()
{
    const QSize sizeGroupBoxAll(310, 700);
    QVBoxLayout* layoutAll = new QVBoxLayout;
    QVBoxLayout* layoutAllRight = new QVBoxLayout;
    QFormLayout* layoutAllLeft = new QFormLayout;
    QHBoxLayout* layoutMiddle = new QHBoxLayout;
    groupBoxAll = new QGroupBox(tr(""));
    groupBoxAll->setMaximumSize(sizeGroupBoxAll);


    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in the calculation"));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxProperties = new QGroupBox(tr("Properties"));
    groupBoxProperties->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutProperties = new QFormLayout;
    labelThrusterForce = new QLabel(tr("Thrust Force (N)"));
    editThrusterForce = new QLineEdit;
    editThrusterForce->setValidator(new QDoubleValidator);
    layoutProperties->addRow(labelThrusterForce, editThrusterForce);

    groupBoxThrustAxis = new QGroupBox(tr("Thruster Axis"));
    QFormLayout* layoutThrustAxis = new QFormLayout;
    labelBody = new QLabel(tr("Body"));
    comboboxBody = new QComboBox();
    labelThrustAxisX = new QLabel(tr("X"));
    editThrustAxisX = new QLineEdit;
    editThrustAxisX->setValidator(new QDoubleValidator);
    labelThrustAxisY = new QLabel(tr("Y"));
    editThrustAxisY = new QLineEdit;
    editThrustAxisY->setValidator(new QDoubleValidator);
    labelThrustAxisZ = new QLabel(tr("Z"));
    editThrustAxisZ = new QLineEdit;
    editThrustAxisZ->setValidator(new QDoubleValidator);
    btnNormalize = new QPushButton(tr("Normalize"));
    layoutThrustAxis->addRow(labelBody, comboboxBody);
    layoutThrustAxis->addRow(labelThrustAxisX, editThrustAxisX);
    layoutThrustAxis->addRow(labelThrustAxisY, editThrustAxisY);
    layoutThrustAxis->addRow(labelThrustAxisZ, editThrustAxisZ);
    layoutThrustAxis->addRow(new QLabel, btnNormalize);
    groupBoxThrustAxis->setLayout(layoutThrustAxis);

    groupBoxLocationInBody = new QGroupBox(tr("Location in Body (m)"));
    QFormLayout* layoutLocationInB0 = new QFormLayout;
    labelLocationInBodyX = new QLabel(tr("X"));
    editLocationInBodyX = new QLineEdit;
    editLocationInBodyX->setValidator(new QDoubleValidator);
    labelLocationInBodyY = new QLabel(tr("Y"));
    editLocationInBodyY = new QLineEdit;
    editLocationInBodyY->setValidator(new QDoubleValidator);
    labelLocationInBodyZ = new QLabel(tr("Z"));
    editLocationInBodyZ = new QLineEdit;
    editLocationInBodyZ->setValidator(new QDoubleValidator);
    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);
    layoutLocationInB0->addRow(labelLocationInBodyX, editLocationInBodyX);
    layoutLocationInB0->addRow(labelLocationInBodyY, editLocationInBodyY);
    layoutLocationInB0->addRow(labelLocationInBodyZ, editLocationInBodyZ);
    groupBoxLocationInBody->setLayout(layoutLocationInB0);

    layoutLocationInB0->addRow(labelLocationInBodyX, editLocationInBodyX);
    layoutLocationInB0->addRow(labelLocationInBodyY, editLocationInBodyY);
    layoutLocationInB0->addRow(labelLocationInBodyZ, editLocationInBodyZ);
    groupBoxLocationInBody->setLayout(layoutLocationInB0);
    layoutAllLeft->addRow(groupBoxDetails);
    layoutAllLeft->addRow(labelThrusterForce, editThrusterForce);
    layoutAllLeft->addRow(groupBoxThrustAxis);
    layoutAllLeft->addRow(groupBoxLocationInBody);
    layoutAllLeft->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxAll->setLayout(layoutAllLeft);

    QLabel* tempLabel = new QLabel(tr("For CAD Model Display."));
    layoutAllRight->addWidget(tempLabel);

    layoutMiddle->addWidget(groupBoxAll);
    layoutMiddle->addLayout(layoutAllRight);
    layoutAll->addLayout(layoutMiddle);
    layoutAll->addWidget(m_buttonBox);
    setLayout(layoutAll);
}

void SpacecraftThrusterWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftThrusterWidget::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){this->mapDataFromWidgetToModel();mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, this,
            [=](){mapDataFromModelToWidget();});

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editThrusterForce, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxBody, &QComboBox::currentTextChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editThrustAxisX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editThrustAxisY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editThrustAxisZ, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLocationInBodyX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLocationInBodyY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLocationInBodyZ, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(btnNormalize, &QPushButton::clicked, this, &SpacecraftThrusterWidget::normalizeAxisVector);
    connect(comboboxBody, &QComboBox::currentTextChanged,
            this, &SpacecraftThrusterWidget::renewGroupBoxBodyIndex);
}

void SpacecraftThrusterWidget::renewGroupBoxBodyIndex(QString bodyName)
{
    QString bodyIndexFormer = tr("Location in ");
    if (bodyName.isEmpty())
    {
        groupBoxLocationInBody->setTitle(bodyIndexFormer+tr("body (m)"));
        groupBoxLocationInBody->setEnabled(false);
        editThrustAxisX->setEnabled(false);
        editThrustAxisY->setEnabled(false);
        editThrustAxisZ->setEnabled(false);
        btnNormalize->setEnabled(false);
        chkbxIncluded->setChecked(false);
    }
    else
    {
        QString title = bodyIndexFormer + bodyName + tr(" (m)");
        groupBoxLocationInBody->setTitle(title);
        groupBoxLocationInBody->setEnabled(true);
        editThrustAxisX->setEnabled(true);
        editThrustAxisY->setEnabled(true);
        editThrustAxisZ->setEnabled(true);
        btnNormalize->setEnabled(true);
    }
}

void SpacecraftThrusterWidget::normalizeAxisVector()
{
    const int precision = 6;
    using std::sqrt;
    double componentX = editThrustAxisX->text().toDouble();
    double componentY = editThrustAxisY->text().toDouble();
    double componentZ = editThrustAxisZ->text().toDouble();
    double norm = sqrt(componentX*componentX + componentY*componentY + componentZ*componentZ);
    if (abs(norm - 0.0) < 0.000001)
        return;
    componentX = componentX/norm;
    componentY = componentY/norm;
    componentZ = componentZ/norm;
    editThrustAxisX->setText(QString::number(componentX,'f', precision));
    editThrustAxisY->setText(QString::number(componentY,'f', precision));
    editThrustAxisZ->setText(QString::number(componentZ,'f', precision));
    return;
}

bool SpacecraftThrusterWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<Thruster>())
        return false;
    Thruster THR = m_index.data().value<Thruster>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();
    setWindowTitle(THR.name());

    const int precision = 6;
    chkbxIncluded->setChecked(THR.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());

    editThrusterForce->setText(QString::number(THR.thrustForce(),'f', precision));

    comboboxBody->setCurrentText(THR.bodyName());
    editThrustAxisX->setText(QString::number(THR.thrustAxis()[0],'f',precision));
    editThrustAxisY->setText(QString::number(THR.thrustAxis()[1],'f',precision));
    editThrustAxisZ->setText(QString::number(THR.thrustAxis()[2],'f',precision));

    editLocationInBodyX->setText(QString::number(THR.locationBody()[0],'f', precision));
    editLocationInBodyY->setText(QString::number(THR.locationBody()[1],'f', precision));
    editLocationInBodyZ->setText(QString::number(THR.locationBody()[2],'f', precision));
    editFlexNodeIndex->setText(QString::number(THR.flexNodeIndex()));
    return true;
}

bool SpacecraftThrusterWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<Thruster>())
        return false;

    QVariant newData = QVariant();
    Thruster newTHR = m_index.data().value<Thruster>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    SpacecraftBody* body;
    int indexBody = -1;

    if (comboboxBody->currentText().isEmpty())
    {
        chkbxIncluded->setChecked(false);
        QMessageBox* msgBox = new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setWindowTitle(tr("No body is selected."));
        msgBox->setText(newTHR.name() + tr(" will not be included in \ncalculation, since no spacecraft body is selected."));
        msgBox->exec();
    }

    if (!comboboxBody->currentText().isEmpty())
        indexBody = comboboxBody->currentText().split("-")[1].toInt();

    newTHR.edit(editThrusterForce->text().toDouble(), indexBody,
    {editThrustAxisX->text().toDouble(), editThrustAxisY->text().toDouble(), editThrustAxisZ->text().toDouble()},
    {editLocationInBodyX->text().toDouble(), editLocationInBodyY->text().toDouble(), editLocationInBodyZ->text().toDouble()},
                editFlexNodeIndex->text().toUInt(), chkbxIncluded->isChecked());
    newData.setValue(newTHR);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}


/** Widget for Gyroscope Data **/

SpacecraftGyroscopeWidget::SpacecraftGyroscopeWidget(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("Gyro Axis"));
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}

SpacecraftGyroscopeWidget::~SpacecraftGyroscopeWidget()
{

}

void SpacecraftGyroscopeWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftGyroscopeWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<GyroAxis>())
        return;
    m_index = index;
    mapDataFromModelToWidget();

}

void SpacecraftGyroscopeWidget::createWidgets()
{
    const int maxWidthGroupBox = 400;
    const int minWidthGroupBox = 380;
    QFormLayout* layoutLeft = new QFormLayout;
    QVBoxLayout* layoutRight = new QVBoxLayout;
    QHBoxLayout* layoutMiddle = new QHBoxLayout;
    QVBoxLayout* layoutAll = new QVBoxLayout;
    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    groupBoxDetails->setMaximumWidth(maxWidthGroupBox);
    groupBoxDetails->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in the calculation."));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxProperties = new QGroupBox(tr("Properties"));
    groupBoxProperties->setAlignment(Qt::AlignCenter);
    groupBoxProperties->setMaximumWidth(maxWidthGroupBox);
    groupBoxProperties->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutProperties = new QFormLayout;
    labelSampleTime = new QLabel(tr("Sample Time (sec)"));
    editSampleTime = new QLineEdit;
    editSampleTime->setValidator(new QDoubleValidator);
    groupBoxAxisInBodyFrame = new QGroupBox(tr("Axis expressed in Body Frame (Properties-Continued)"));
    QFormLayout* layoutAxisInBodyFrame = new QFormLayout;
    labelAxisX = new QLabel(tr("X"));
    editAxisX = new QLineEdit;
    editAxisX->setValidator(new QDoubleValidator);
    labelAxisY = new QLabel(tr("Y"));
    editAxisY = new QLineEdit;
    editAxisY->setValidator(new QDoubleValidator);
    labelAxisZ = new QLabel(tr("Z"));
    editAxisZ = new QLineEdit;
    editAxisZ->setValidator(new QDoubleValidator);
    btnNormalize = new QPushButton(tr("Normalize"));
    layoutAxisInBodyFrame->addRow(labelAxisX, editAxisX);
    layoutAxisInBodyFrame->addRow(labelAxisY, editAxisY);
    layoutAxisInBodyFrame->addRow(labelAxisZ, editAxisZ);
    layoutAxisInBodyFrame->addRow(new QLabel, btnNormalize);
    groupBoxAxisInBodyFrame->setLayout(layoutAxisInBodyFrame);

    labelMaxRate = new QLabel(tr("Max Rate (deg/sec)"));
    editMaxRate = new QLineEdit;
    editMaxRate->setValidator(new QDoubleValidator);

    labelScaleFactorError = new QLabel(tr("Scale Factor Error (ppm)"));
    editScaleFactorError = new QLineEdit;
    editScaleFactorError->setValidator(new QDoubleValidator);

    labelQuantization = new QLabel(tr("Quantization (arcsec)"));
    editQuantization = new QLineEdit;
    editQuantization->setValidator(new QDoubleValidator);

    labelAngleRandomWalk = new QLabel(tr("Angle Random Walk (deg/rt-hr)"));
    editAngleRandomWalk = new QLineEdit;
    editAngleRandomWalk->setValidator(new QDoubleValidator);

    QGridLayout* layoutBiasStability = new QGridLayout;
    labelBiasStability = new QLabel(tr("Bias Stability (deg/hr)"));
    editBiasStability = new QLineEdit;
    editBiasStability->setValidator(new QDoubleValidator);
    labelTimeSpan = new QLabel(tr("Timespan (hr)"));
    editTimeSpan = new QLineEdit;
    editTimeSpan->setValidator(new QDoubleValidator);
    layoutBiasStability->addWidget(labelBiasStability, 0 ,0, 1, 1);
    layoutBiasStability->addWidget(labelTimeSpan, 0, 1, 1, 1);
    layoutBiasStability->addWidget(editBiasStability, 1, 0, 1, 1);
    layoutBiasStability->addWidget(editTimeSpan,1, 1, 1,1);

    labelAngleNoise = new QLabel(tr("Angle Noise (arcsec RMS)"));
    editAngleNoise = new QLineEdit;
    editAngleNoise->setValidator(new QDoubleValidator);
    labelInitialBias = new QLabel(tr("Initial Bias (deg/hr)"));
    editInitialBias = new QLineEdit;
    editInitialBias->setValidator(new QDoubleValidator);

    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);


    layoutProperties->addRow(labelSampleTime, editSampleTime);
    layoutProperties->addRow(labelMaxRate, editMaxRate);
    layoutProperties->addRow(labelScaleFactorError, editScaleFactorError);
    layoutProperties->addRow(labelQuantization, editQuantization);
    layoutProperties->addRow(labelAngleRandomWalk, editAngleRandomWalk);
    layoutProperties->addRow(labelBiasStability, editBiasStability);
    layoutProperties->addRow(labelAngleNoise, editAngleNoise);
    layoutProperties->addRow(labelInitialBias, editInitialBias);
    layoutProperties->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxProperties->setLayout(layoutProperties);

    layoutLeft->addRow(groupBoxDetails);
    layoutLeft->addRow(groupBoxProperties);
    layoutRight->addWidget(new QLabel(tr("For CAD model Display.")));
    layoutRight->addWidget(groupBoxAxisInBodyFrame);
    layoutRight->setStretch(0,2);
    layoutRight->setStretch(1,1);

    layoutMiddle->addLayout(layoutLeft);
    layoutMiddle->addLayout(layoutRight);
    layoutAll->addLayout(layoutMiddle);
    layoutAll->addWidget(m_buttonBox);
    setLayout(layoutAll);

}

void SpacecraftGyroscopeWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftGyroscopeWidget::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);

    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, this,
            [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){mapDataFromWidgetToModel();mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSampleTime, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisZ, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMaxRate , &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editScaleFactorError, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editQuantization, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAngleRandomWalk, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editBiasStability, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAngleNoise, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialBias, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(btnNormalize, &QPushButton::clicked, this, &SpacecraftGyroscopeWidget::normalizeAxisComponents);
}

void SpacecraftGyroscopeWidget::normalizeAxisComponents()
{
    const int precision = 6;
    double AxisX = editAxisX->text().toDouble();
    double AxisY = editAxisY->text().toDouble();
    double AxisZ = editAxisZ->text().toDouble();
    double norm = sqrt(AxisX*AxisX + AxisY*AxisY + AxisZ*AxisZ);
    if (abs(norm-0.0) < 0.0000001)
        return;
    AxisX = AxisX/norm;
    AxisY = AxisY/norm;
    AxisZ = AxisZ/norm;
    editAxisX->setText(QString::number(AxisX, 'f', precision));
    editAxisY->setText(QString::number(AxisY, 'f', precision));
    editAxisZ->setText(QString::number(AxisZ, 'f', precision));
}

bool SpacecraftGyroscopeWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<GyroAxis>())
        return false;
    const int precision = 6;
    GyroAxis GYRO = m_index.data().value<GyroAxis>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();
    setWindowTitle(GYRO.name());

    chkbxIncluded->setChecked(GYRO.includedInCalculation());
    editSpacecraft->setText(SC.name());
    editMission->setText(M.name());

    editSampleTime->setText(QString::number(GYRO.sampleTime(),'f', precision));
    editAxisX->setText(QString::number(GYRO.axisInBodyFrame()[0], 'f', precision));
    editAxisY->setText(QString::number(GYRO.axisInBodyFrame()[1], 'f', precision));
    editAxisZ->setText(QString::number(GYRO.axisInBodyFrame()[2], 'f', precision));
    editMaxRate->setText(QString::number(GYRO.maxRate(), 'f', precision));
    editScaleFactorError->setText(QString::number(GYRO.scaleFactorError(),'f', precision));
    editQuantization->setText(QString::number(GYRO.quantization(),'f', precision));
    editAngleRandomWalk->setText(QString::number(GYRO.angRandomWalk(), 'f', precision));
    editBiasStability->setText(QString::number(GYRO.biasStability(),'f',precision));
    editAngleNoise->setText(QString::number(GYRO.angleNoise(), 'f', precision));
    editInitialBias->setText(QString::number(GYRO.initialBias(),'f',precision));
    editFlexNodeIndex->setText(QString::number(GYRO.flexNodeIndex(),'f',precision));
    return true;
}

bool SpacecraftGyroscopeWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<GyroAxis>())
        return false;
    QVariant newData = QVariant();
    GyroAxis newGyro = m_index.data().value<GyroAxis>();

    newGyro.edit(editSampleTime->text().toDouble(),
    {editAxisX->text().toDouble(), editAxisY->text().toDouble(), editAxisZ->text().toDouble()},
                 editMaxRate->text().toDouble(), editScaleFactorError->text().toDouble(),
                 editQuantization->text().toDouble(),
                 editAngleRandomWalk->text().toDouble(), editBiasStability->text().toDouble(),
                 editTimeSpan->text().toDouble(),editAngleNoise->text().toDouble(),
                 editInitialBias->text().toDouble(), editFlexNodeIndex->text().toUInt(),
                 chkbxIncluded->isChecked());

    newData.setValue(newGyro);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}

/** Widget for Magnetometer data **/

SpacecraftMMAWidget::SpacecraftMMAWidget(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("Magnetometer"));
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}

SpacecraftMMAWidget::~SpacecraftMMAWidget()
{

}

void SpacecraftMMAWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftMMAWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<MagnetometerAxis>())
        return;
    m_index = index;
    mapDataFromModelToWidget();
}

void SpacecraftMMAWidget::createWidgets()
{

    const int maxGroupBoxWidth = 400;
    const int minGroupBoxWidth = 380;
    QFormLayout* layoutLeft = new QFormLayout;
    QHBoxLayout* layoutMiddle = new QHBoxLayout;
    QVBoxLayout* layoutAll = new QVBoxLayout;


    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    groupBoxDetails->setMaximumWidth(maxGroupBoxWidth);
    groupBoxDetails->setMinimumWidth(minGroupBoxWidth);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in calculation."));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxProperties = new QGroupBox(tr("Properties"));
    groupBoxProperties->setAlignment(Qt::AlignCenter);
    groupBoxProperties->setMaximumWidth(maxGroupBoxWidth);
    groupBoxProperties->setMinimumWidth(minGroupBoxWidth);
    QFormLayout* layoutProperties = new QFormLayout;

    labelSampleTime = new QLabel(tr("Sample Time (sec)"));
    editSampleTime = new QLineEdit;
    editSampleTime->setValidator(new QDoubleValidator);

    groupBoxAxisInBodyFrame = new QGroupBox(tr("Axis expressed in Body Frame"));
    QFormLayout* layoutAxisInBodyFrame = new QFormLayout;
    labelAxisX = new QLabel(tr("X"));
    editAxisX = new QLineEdit;
    editAxisX->setValidator(new QDoubleValidator);
    labelAxisY = new QLabel(tr("Y"));
    editAxisY = new QLineEdit;
    editAxisY->setValidator(new QDoubleValidator);
    labelAxisZ = new QLabel(tr("Z"));
    editAxisZ = new QLineEdit;
    editAxisZ->setValidator(new QDoubleValidator);
    btnNormalize = new QPushButton(tr("Normalize"));
    layoutAxisInBodyFrame->addRow(labelAxisX, editAxisX);
    layoutAxisInBodyFrame->addRow(labelAxisY, editAxisY);
    layoutAxisInBodyFrame->addRow(labelAxisZ, editAxisZ);
    layoutAxisInBodyFrame->addRow(new QLabel, btnNormalize);
    groupBoxAxisInBodyFrame->setLayout(layoutAxisInBodyFrame);

    labelSaturation = new QLabel(tr("Saturation (Tesla)"));
    editSaturation = new QLineEdit;
    editSaturation->setValidator(new QDoubleValidator);
    labelScaleFactorError = new QLabel(tr("Scale Factor Error (ppm)"));
    editScaleFactorError = new QLineEdit;
    editScaleFactorError->setValidator(new QDoubleValidator);
    labelQuantization = new QLabel(tr("Quantization (Tesla)"));
    editQuantization = new QLineEdit;
    editQuantization->setValidator(new QDoubleValidator);
    labelNoise = new QLabel(tr("Noise (Tesla RMS)"));
    editNoise = new QLineEdit;
    editNoise->setValidator(new QDoubleValidator);
    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);

    layoutProperties->addRow(labelSampleTime, editSampleTime);
    layoutProperties->addRow(groupBoxAxisInBodyFrame);
    layoutProperties->addRow(labelSaturation, editSaturation);
    layoutProperties->addRow(labelScaleFactorError, editScaleFactorError);
    layoutProperties->addRow(labelQuantization, editQuantization);
    layoutProperties->addRow(labelNoise, editNoise);
    layoutProperties->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxProperties->setLayout(layoutProperties);

    layoutLeft->addRow(groupBoxDetails);
    layoutLeft->addRow(groupBoxProperties);

    layoutMiddle->addLayout(layoutLeft);
    layoutMiddle->addWidget(new QLabel(tr("For CAD Model Display")));

    layoutAll->addLayout(layoutMiddle);
    layoutAll->addWidget(m_buttonBox);

    setLayout(layoutAll);
}

void SpacecraftMMAWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftMMAWidget::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);

    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){mapDataFromWidgetToModel();mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSampleTime, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisZ, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSaturation, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editScaleFactorError, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editQuantization, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editNoise, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(btnNormalize, &QPushButton::clicked, this, &SpacecraftMMAWidget::normalizeAxisComponents);

}

void SpacecraftMMAWidget::normalizeAxisComponents()
{
    double AxisX = editAxisX->text().toDouble();
    double AxisY = editAxisY->text().toDouble();
    double AxisZ = editAxisZ->text().toDouble();
    double norm = sqrt(AxisX*AxisX + AxisY*AxisY + AxisZ*AxisZ);
    if (abs(norm-0.0) < 0.0000001)
        return;
    const int precision = 6;
    AxisX = AxisX/norm;
    AxisY = AxisY/norm;
    AxisZ = AxisZ/norm;
    editAxisX->setText(QString::number(AxisX, 'f', precision));
    editAxisY->setText(QString::number(AxisY, 'f', precision));
    editAxisZ->setText(QString::number(AxisZ, 'f', precision));
}

bool SpacecraftMMAWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<MagnetometerAxis>())
        return false;
    const int precision = 6;
    MagnetometerAxis MMA = m_index.data().value<MagnetometerAxis>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();

    setWindowTitle(MMA.name());
    chkbxIncluded->setChecked(MMA.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());

    editSampleTime->setText(QString::number(MMA.sampleTime(), 'f', precision));
    editAxisX->setText(QString::number(MMA.axisInBodyFrame()[0], 'f', precision));
    editAxisY->setText(QString::number(MMA.axisInBodyFrame()[1], 'f', precision));
    editAxisZ->setText(QString::number(MMA.axisInBodyFrame()[2], 'f', precision));

    editSaturation->setText(QString::number(MMA.saturation(),'f', precision));
    editScaleFactorError->setText(QString::number(MMA.scaleFactorError(),'f',precision));
    editQuantization->setText(QString::number(MMA.quantization(), 'f', precision));
    editNoise->setText(QString::number(MMA.noise(), 'f', precision));
    editFlexNodeIndex->setText(QString::number(MMA.flexNodeIndex()));

    return true;
}

bool SpacecraftMMAWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<MagnetometerAxis>())
        return false;

    QVariant newData = QVariant();
    MagnetometerAxis newMMA = m_index.data().value<MagnetometerAxis>();
    newMMA.edit(editSampleTime->text().toDouble(),
    {editAxisX->text().toDouble(), editAxisY->text().toDouble(), editAxisZ->text().toDouble()},
                editSaturation->text().toDouble(), editScaleFactorError->text().toDouble(),
                editQuantization->text().toDouble(), editNoise->text().toDouble(),
                editFlexNodeIndex->text().toUInt(), chkbxIncluded->isChecked());

    newData.setValue(newMMA);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}

/** Widget for Coarse Sun Sensor **/
SpacecraftCSSWidget::SpacecraftCSSWidget(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("Coarse Sun Sensor"));
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}

SpacecraftCSSWidget::~SpacecraftCSSWidget()
{

}

void SpacecraftCSSWidget::createWidgets()
{
    const int maxWidthGroupBox = 400;
    const int minWidthGroupBox = 380;
    QFormLayout* layoutLeft = new QFormLayout;
    QHBoxLayout* layoutMiddle = new QHBoxLayout;
    QVBoxLayout* layoutAll = new QVBoxLayout;

    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    groupBoxDetails->setMaximumWidth(maxWidthGroupBox);
    groupBoxDetails->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in the calculation"));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxProperties = new QGroupBox(tr("Properties"));
    groupBoxProperties->setAlignment(Qt::AlignCenter);
    groupBoxProperties->setMaximumWidth(maxWidthGroupBox);
    groupBoxProperties->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutProperties = new QFormLayout;
    labelSampleTime = new QLabel(tr("Sample Time (sec)"));
    editSampleTime = new QLineEdit;
    editSampleTime->setValidator(new QDoubleValidator);
    groupBoxAxisExpressedInBodyFrame = new QGroupBox(tr("Axis expressed in Body Frame"));
    QFormLayout* layoutAxisExpressedInBodyFrame = new QFormLayout;
    labelAxisX = new QLabel(tr("X"));
    editAxisX = new QLineEdit;
    editAxisX->setValidator(new QDoubleValidator);
    labelAxisY = new QLabel(tr("Y"));
    editAxisY = new QLineEdit;
    editAxisY->setValidator(new QDoubleValidator);
    labelAxisZ = new QLabel(tr("Z"));
    editAxisZ = new QLineEdit;
    editAxisZ->setValidator(new QDoubleValidator);
    btnNormalize = new QPushButton(tr("Normalize"));
    layoutAxisExpressedInBodyFrame->addRow(labelAxisX, editAxisX);
    layoutAxisExpressedInBodyFrame->addRow(labelAxisY, editAxisY);
    layoutAxisExpressedInBodyFrame->addRow(labelAxisZ, editAxisZ);
    layoutAxisExpressedInBodyFrame->addRow(new QLabel, btnNormalize);
    groupBoxAxisExpressedInBodyFrame->setLayout(layoutAxisExpressedInBodyFrame);
    labelBody = new QLabel(tr("Spacecraft Body"));
    comboboxBody = new QComboBox;
    labelHalfConeAngle = new QLabel(tr("Half-cone Angle (deg)"));
    editHalfConeAngle = new QLineEdit;
    editHalfConeAngle->setValidator(new QDoubleValidator);
    labelScaleFactor = new QLabel(tr("Scale Factor"));
    editScaleFactor = new QLineEdit;
    editScaleFactor->setValidator(new QDoubleValidator);
    labelQuantization = new QLabel(tr("Quantization"));
    editQuantization = new QLineEdit;
    editQuantization->setValidator(new QDoubleValidator);
    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);
    layoutProperties->addRow(labelSampleTime, editSampleTime);
    layoutProperties->addRow(labelBody, comboboxBody);
    layoutProperties->addRow(groupBoxAxisExpressedInBodyFrame);
    layoutProperties->addRow(labelHalfConeAngle, editHalfConeAngle);
    layoutProperties->addRow(labelScaleFactor, editScaleFactor);
    layoutProperties->addRow(labelQuantization, editQuantization);
    layoutProperties->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxProperties->setLayout(layoutProperties);

    layoutLeft->addRow(groupBoxDetails);
    layoutLeft->addRow(groupBoxProperties);

    layoutMiddle->addLayout(layoutLeft);
    layoutMiddle->addWidget(new QLabel(tr("For CAD Model Display.")));
    layoutAll->addLayout(layoutMiddle);
    layoutAll->addWidget(m_buttonBox);
    setLayout(layoutAll);
}

void SpacecraftCSSWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftCSSWidget::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this,
            &SpacecraftCSSWidget::disableChkbxIncludedWhenNoBody);
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);


    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, &SpacecraftCSSWidget::disableChkbxIncludedWhenNoBody);
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){mapDataFromWidgetToModel();mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(btnNormalize, &QPushButton::clicked, this,
            &SpacecraftCSSWidget::normalizeAxisComponents);

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSampleTime, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxBody, &QComboBox::currentTextChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisZ, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editHalfConeAngle, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editScaleFactor, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editQuantization, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxBody, &QComboBox::currentTextChanged, this,
            &SpacecraftCSSWidget::changegroupBoxAxisExpressedInBodyFrameTitle);
}

void SpacecraftCSSWidget::renewComboboxBody()
{
    QStringList listBody = QStringList();
    comboboxBody->clear();
    listBody.append(tr(""));
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    for (int i = 0; i < SC.numberOfBodies(); ++i)
    {
        if(SC.body(i)->includedInCalculation())
            listBody.append(SC.body(i)->name());
    }
    comboboxBody->addItems(listBody);
}
void SpacecraftCSSWidget::disableChkbxIncludedWhenNoBody()
{
    if (comboboxBody->currentText().isEmpty())
    {
        chkbxIncluded->setChecked(false);
        CoarseSunSensor css = m_index.data().value<CoarseSunSensor>();
        QString name = css.name();
        QString text =  name + tr(" will not be included in the calculation,\n") + tr("since no spacecraft body is selected.");
        QMessageBox* msgNoBodySelected = new QMessageBox(this);
        msgNoBodySelected->setWindowTitle(tr("Spacecraft Body Missing."));
        msgNoBodySelected->setIcon(QMessageBox::Warning);
        msgNoBodySelected->setText(text);
        msgNoBodySelected->setStandardButtons(QMessageBox::Ok);
        msgNoBodySelected->exec();
        return;
    }
    return;
}

void SpacecraftCSSWidget::changegroupBoxAxisExpressedInBodyFrameTitle(const QString& s)
{
    QString title = QString();
    if (s.isEmpty())
    {
        title = tr("Axis expressed in Body Frame");
        groupBoxAxisExpressedInBodyFrame->setEnabled(false);
    }
    else
    {
        title = tr("Axis expressed in Frame of ") + s;
        groupBoxAxisExpressedInBodyFrame->setEnabled(true);
    }
    groupBoxAxisExpressedInBodyFrame->setTitle(title);
}

bool SpacecraftCSSWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<CoarseSunSensor>())
        return false;
    const int precision = 6;
    CoarseSunSensor CSS = m_index.data().value<CoarseSunSensor>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();

    setWindowTitle(CSS.name());
    chkbxIncluded->setChecked(CSS.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());
    comboboxBody->setCurrentText(CSS.bodyName());
    editSampleTime->setText(QString::number(CSS.sampleTime(), 'f', precision));
    editAxisX->setText(QString::number(CSS.axisInBodyFrame()[0], 'f', precision));
    editAxisY->setText(QString::number(CSS.axisInBodyFrame()[1], 'f', precision));
    editAxisZ->setText(QString::number(CSS.axisInBodyFrame()[2], 'f', precision));

    editHalfConeAngle->setText(QString::number(CSS.halfConeAngle(), 'f', precision));
    editScaleFactor->setText(QString::number(CSS.scaleFactor(),'f', precision));
    editQuantization->setText(QString::number(CSS.quantization(), 'f', precision));
    editFlexNodeIndex->setText(QString::number(CSS.flexNodeIndex()));
    return true;
}

bool SpacecraftCSSWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<CoarseSunSensor>())
        return false;
    QVariant newData = QVariant();
    CoarseSunSensor newCSS = m_index.data().value<CoarseSunSensor>();
    int indexBody = -1;
    if (!comboboxBody->currentText().isEmpty())
        indexBody = comboboxBody->currentText().split("-")[1].toInt();


    newCSS.edit(editSampleTime->text().toDouble(), indexBody,
    {editAxisX->text().toDouble(), editAxisY->text().toDouble(), editAxisZ->text().toDouble()},
             editHalfConeAngle->text().toDouble(), editScaleFactor->text().toDouble(),
             editQuantization->text().toDouble(), editFlexNodeIndex->text().toUInt(),
             chkbxIncluded->isChecked());
    newData.setValue(newCSS);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}

void SpacecraftCSSWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftCSSWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<CoarseSunSensor>())
        return;
    m_index = index;
    renewComboboxBody();
    mapDataFromModelToWidget();
    changegroupBoxAxisExpressedInBodyFrameTitle(comboboxBody->currentText());
}

void SpacecraftCSSWidget::normalizeAxisComponents()
{
    const int precision = 6;
    double AxisX = editAxisX->text().toDouble();
    double AxisY = editAxisY->text().toDouble();
    double AxisZ = editAxisZ->text().toDouble();
    double norm = sqrt(AxisX*AxisX + AxisY*AxisY + AxisZ*AxisZ);
    if (norm < 0.00000001)
        return;
    AxisX = AxisX/norm;
    AxisY = AxisY/norm;
    AxisZ = AxisZ/norm;
    editAxisX->setText(QString::number(AxisX, 'f', precision));
    editAxisY->setText(QString::number(AxisY, 'f', precision));
    editAxisZ->setText(QString::number(AxisZ, 'f', precision));
}


/** Widget for Fine Sun Sensor data **/
SpacecraftFSSWidget::SpacecraftFSSWidget(QWidget* parent) : QDialog(parent)
{
    const int maxWidth = 420;
    setMaximumWidth(maxWidth);
    setWindowTitle(tr("Fine Sun Sensor"));
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}

SpacecraftFSSWidget::~SpacecraftFSSWidget()
{

}

void SpacecraftFSSWidget::createWidgets()
{
    QFormLayout* layoutAll = new QFormLayout;
    m_modelMountingAngleSeq = new QStringListModel(list_EulerSeq);
    const int maxWidthGroupBox = 400;
    const int minWidthGroupBox = 380;
    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    groupBoxDetails->setMaximumWidth(maxWidthGroupBox);
    groupBoxDetails->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in the calculation."));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxProperties = new QGroupBox(tr("Properties"));
    groupBoxProperties->setAlignment(Qt::AlignCenter);
    groupBoxProperties->setMaximumWidth(maxWidthGroupBox);
    groupBoxProperties->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutProperties = new QFormLayout;
    labelSampleTime = new QLabel(tr("Sample Time (sec)"));
    editSampleTime = new QLineEdit;
    editSampleTime->setValidator(new QDoubleValidator);
    groupBoxMountingAngle = new QGroupBox(tr("Mounting Angles (deg) and Seq in Body"));
    QFormLayout* layoutMountingAngle = new QFormLayout;
    labelMountingAngle1 = new QLabel(QString::fromUtf8("\u03B8\u2081"));
    editMountingAngle1 = new QLineEdit;
    editMountingAngle1->setValidator(new QDoubleValidator);
    labelMountingAngle2 = new QLabel(QString::fromUtf8("\u03B8\u2082"));
    editMountingAngle2 = new QLineEdit;
    editMountingAngle2->setValidator(new QDoubleValidator);
    labelMountingAngle3 = new QLabel(QString::fromUtf8("\u03B8\u2083"));
    editMountingAngle3 = new QLineEdit;
    editMountingAngle3->setValidator(new QDoubleValidator);
    labelMountingAngleSeqInBody = new QLabel(tr("Seq in Body"));
    comboboxMountingAngleSeqInBody = new QComboBox;
    comboboxMountingAngleSeqInBody->setModel(m_modelMountingAngleSeq);
    layoutMountingAngle->addRow(labelMountingAngle1, editMountingAngle1);
    layoutMountingAngle->addRow(labelMountingAngle2, editMountingAngle2);
    layoutMountingAngle->addRow(labelMountingAngle3, editMountingAngle3);
    layoutMountingAngle->addRow(labelMountingAngleSeqInBody, comboboxMountingAngleSeqInBody);
    groupBoxMountingAngle->setLayout(layoutMountingAngle);

    groupBoxFOV = new QGroupBox(tr("FOV Size (deg)"));
    QFormLayout* layoutFOV = new QFormLayout;
    labelFOVSizeX = new QLabel(tr("X"));
    editFOVSizeX = new QLineEdit;
    editFOVSizeX->setValidator(new QDoubleValidator);
    labelFOVSizeY = new QLabel(tr("Y"));
    editFOVSizeY = new QLineEdit;
    editFOVSizeY->setValidator(new QDoubleValidator);
    layoutFOV->addRow(labelFOVSizeX, editFOVSizeX);
    layoutFOV->addRow(labelFOVSizeY, editFOVSizeY);
    groupBoxFOV->setLayout(layoutFOV);

    labelNoiseEquivalentAngle = new QLabel(tr("Noise Equivalent Angle (deg RMS)"));
    editNoiseEquivalentAngle = new QLineEdit;
    editNoiseEquivalentAngle->setValidator(new QDoubleValidator);
    labelQuantization = new QLabel(tr("Quantization (deg)"));
    editQuantization = new QLineEdit;
    editQuantization->setValidator(new QDoubleValidator);

    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);

    layoutProperties->addRow(labelSampleTime, editSampleTime);
    layoutProperties->addRow(groupBoxMountingAngle);
    layoutProperties->addRow(groupBoxFOV);
    layoutProperties->addRow(labelNoiseEquivalentAngle, editNoiseEquivalentAngle);
    layoutProperties->addRow(labelQuantization, editQuantization);
    layoutProperties->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxProperties->setLayout(layoutProperties);

    layoutAll->addWidget(groupBoxDetails);
    layoutAll->addWidget(groupBoxProperties);
    layoutAll->addWidget(m_buttonBox);
    setLayout(layoutAll);

}

void SpacecraftFSSWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftFSSWidget::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, [=](){mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){mapDataFromWidgetToModel();mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSampleTime, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMountingAngle1, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMountingAngle2, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMountingAngle3, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxMountingAngleSeqInBody, &QComboBox::currentTextChanged,m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFOVSizeX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFOVSizeY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editNoiseEquivalentAngle, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editQuantization, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void SpacecraftFSSWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftFSSWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<FineSunSensor>())
        return;
    m_index = index;
    mapDataFromModelToWidget();
}

bool SpacecraftFSSWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<FineSunSensor>())
        return false;
    const int precision = 6;
    FineSunSensor FSS = m_index.data().value<FineSunSensor>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();
    setWindowTitle(FSS.name());
    chkbxIncluded->setChecked(FSS.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());
    editSampleTime->setText(QString::number(FSS.sampleTime(), 'f', precision));
    editMountingAngle1->setText(QString::number(FSS.mountingAngles()[0],'f',precision));
    editMountingAngle2->setText(QString::number(FSS.mountingAngles()[1],'f',precision));
    editMountingAngle3->setText(QString::number(FSS.mountingAngles()[2],'f',precision));
    comboboxMountingAngleSeqInBody->setCurrentText(FSS.mountingAnglesSeq());
    editFOVSizeX->setText(QString::number(FSS.FOV_Size()[0], 'f', precision));
    editFOVSizeY->setText(QString::number(FSS.FOV_Size()[1], 'f', precision));
    editNoiseEquivalentAngle->setText(QString::number(FSS.noiseEquivalentAngle(),'f', precision));
    editQuantization->setText(QString::number(FSS.quantization(),'f', precision));
    editFlexNodeIndex->setText(QString::number(FSS.flexNodeIndex()));
    return true;
}

bool SpacecraftFSSWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<FineSunSensor>())
        return false;
    QVariant newData = QVariant();
    FineSunSensor newFSS = m_index.data().value<FineSunSensor>();
    newFSS.edit(editSampleTime->text().toDouble(),
    {editMountingAngle1->text().toDouble(), editMountingAngle2->text().toDouble(), editMountingAngle3->text().toDouble()},
             comboboxMountingAngleSeqInBody->currentText(),
    {editFOVSizeX->text().toDouble(), editFOVSizeY->text().toDouble()},
             editNoiseEquivalentAngle->text().toDouble(), editQuantization->text().toDouble(),
             editFlexNodeIndex->text().toUInt(), chkbxIncluded->isChecked());

    newData.setValue(newFSS);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}


/** Widget for Star Tracker data **/
SpacecraftStarTrackerWidget::SpacecraftStarTrackerWidget(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("Star Tracker"));
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(*pal);
}

SpacecraftStarTrackerWidget::~SpacecraftStarTrackerWidget()
{

}

void SpacecraftStarTrackerWidget::createWidgets()
{
    const int maxWidthGroupBox = 400;
    const int minWidthGroupBox = 380;
    QVBoxLayout* layoutSTDialog = new QVBoxLayout;
    m_modelMountingAngleSeq = new QStringListModel(list_EulerSeq);
    tabWidget = new QTabWidget;
    tabPage1 = new QWidget;
    tabPage2 = new QWidget;


    QHBoxLayout* layoutWidgetAndDisplay = new QHBoxLayout;
    QVBoxLayout* layoutTabPage1 = new QVBoxLayout;
    QVBoxLayout* layoutTabPage2 = new QVBoxLayout;

    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    groupBoxDetails->setMaximumWidth(maxWidthGroupBox);
    groupBoxDetails->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in the calculation."));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxPropertiesPage1 = new QGroupBox(tr("Properties"));
    groupBoxPropertiesPage1->setAlignment(Qt::AlignCenter);
    groupBoxPropertiesPage1->setMaximumWidth(maxWidthGroupBox);
    groupBoxPropertiesPage1->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutPropertiesPage1 = new QFormLayout;
    labelSampleTime = new QLabel(tr("Sample Time (sec)"));
    editSampleTime = new QLineEdit;
    editSampleTime->setValidator(new QDoubleValidator);
    groupBoxMountingAngles = new QGroupBox(tr("Mounting Angles (deg) and Seq in Body"));
    QFormLayout* layoutgroupBoxMountingAngles = new QFormLayout;
    labelMountingAngle1 = new QLabel(QString::fromUtf8("\u03B8\u2081"));
    editMountingAngle1 = new QLineEdit;
    editMountingAngle1->setValidator(new QDoubleValidator);
    labelMountingAngle2 = new QLabel(QString::fromUtf8("\u03B8\u2082"));
    editMountingAngle2 = new QLineEdit;
    editMountingAngle2->setValidator(new QDoubleValidator);
    labelMountingAngle3 = new QLabel(QString::fromUtf8("\u03B8\u2083"));
    editMountingAngle3 = new QLineEdit;
    editMountingAngle3->setValidator(new QDoubleValidator);
    labelMountingAngleSeq = new QLabel(tr("Seq"));
    comboboxMountingAngleSeq = new QComboBox;
    comboboxMountingAngleSeq->setModel(m_modelMountingAngleSeq);
    layoutgroupBoxMountingAngles->addRow(labelMountingAngle1, editMountingAngle1);
    layoutgroupBoxMountingAngles->addRow(labelMountingAngle2, editMountingAngle2);
    layoutgroupBoxMountingAngles->addRow(labelMountingAngle3, editMountingAngle3);
    layoutgroupBoxMountingAngles->addRow(labelMountingAngleSeq, comboboxMountingAngleSeq);
    groupBoxMountingAngles->setLayout(layoutgroupBoxMountingAngles);
    groupBoxFOVsize = new QGroupBox(tr("FOV Size (deg)"));
    QGridLayout* layoutFOVsize = new QGridLayout;
    labelFOVsizeX = new QLabel(tr("X"));
    editFOVsizeX = new QLineEdit;
    editFOVsizeX->setValidator(new QDoubleValidator);
    labelFOVsizeY = new QLabel(tr("Y"));
    editFOVsizeY = new QLineEdit;
    editFOVsizeY->setValidator(new QDoubleValidator);
    layoutFOVsize->addWidget(labelFOVsizeX, 0,0,1,2);
    layoutFOVsize->addWidget(labelFOVsizeY, 0,2,1,2);
    layoutFOVsize->addWidget(editFOVsizeX, 1,0,1,2);
    layoutFOVsize->addWidget(editFOVsizeY, 1,2,1,2);

    groupBoxPropertiesPage2 = new QGroupBox(tr("Properties-continued"));
    groupBoxPropertiesPage2->setAlignment(Qt::AlignCenter);
    groupBoxPropertiesPage2->setMaximumWidth(maxWidthGroupBox);
    groupBoxPropertiesPage2->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutPropertiesPage2 = new QFormLayout;
    groupBoxFOVsize->setLayout(layoutFOVsize);
    groupBoxSunEarthMoonExclusionAngles = new QGroupBox(tr("Sun, Earth, Moon Exclusion Angles (deg)"));
    QGridLayout* layoutSunEarthMoonExclusionAngles = new QGridLayout;
    labelExclusionSun = new QLabel(tr("Sun"));
    editExclusionSun = new QLineEdit;
    editExclusionSun->setValidator(new QDoubleValidator);
    labelExclusionEarth = new QLabel(tr("Earth"));
    editExclusionEarth= new QLineEdit;
    editExclusionEarth->setValidator(new QDoubleValidator);
    labelExclusionMoon = new QLabel(tr("Moon"));
    editExclusionMoon = new QLineEdit;
    editExclusionMoon->setValidator(new QDoubleValidator);
    layoutSunEarthMoonExclusionAngles->addWidget(labelExclusionSun, 0,0,1,1);
    layoutSunEarthMoonExclusionAngles->addWidget(labelExclusionEarth, 0,1,1,1);
    layoutSunEarthMoonExclusionAngles->addWidget(labelExclusionMoon, 0,2,1,1);
    layoutSunEarthMoonExclusionAngles->addWidget(editExclusionSun, 1,0,1,1);
    layoutSunEarthMoonExclusionAngles->addWidget(editExclusionEarth, 1,1,1,1);
    layoutSunEarthMoonExclusionAngles->addWidget(editExclusionMoon, 1,2,1,1);
    groupBoxSunEarthMoonExclusionAngles->setLayout(layoutSunEarthMoonExclusionAngles);
    groupBoxNoiseEquivalentAngles = new QGroupBox(tr("Noise Equivalent Angles (arcsec RMS)"));
    QFormLayout* layoutNoiseEquivalentAngles = new QFormLayout;
    labelNoiseEquivalentAngle1 = new QLabel(QString::fromUtf8("\u03D5\u2081"));
    editNoiseEquivalentAngle1 = new QLineEdit;
    editNoiseEquivalentAngle1->setValidator(new QDoubleValidator);
    labelNoiseEquivalentAngle2 = new QLabel(QString::fromUtf8("\u03D5\u2082"));
    editNoiseEquivalentAngle2 = new QLineEdit;
    editNoiseEquivalentAngle2->setValidator(new QDoubleValidator);
    labelNoiseEquivalentAngle3 = new QLabel(QString::fromUtf8("\u03D5\u2083"));
    editNoiseEquivalentAngle3 = new QLineEdit;
    editNoiseEquivalentAngle3->setValidator(new QDoubleValidator);
    layoutNoiseEquivalentAngles->addRow(labelNoiseEquivalentAngle1, editNoiseEquivalentAngle1);
    layoutNoiseEquivalentAngles->addRow(labelNoiseEquivalentAngle2, editNoiseEquivalentAngle2);
    layoutNoiseEquivalentAngles->addRow(labelNoiseEquivalentAngle3, editNoiseEquivalentAngle3);
    groupBoxNoiseEquivalentAngles->setLayout(layoutNoiseEquivalentAngles);

    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);

    layoutPropertiesPage1->addRow(labelSampleTime, editSampleTime);
    layoutPropertiesPage1->addRow(groupBoxMountingAngles);
    layoutPropertiesPage2->addRow(groupBoxFOVsize);
    layoutPropertiesPage2->addRow(groupBoxSunEarthMoonExclusionAngles);
    layoutPropertiesPage2->addRow(groupBoxNoiseEquivalentAngles);
    layoutPropertiesPage2->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxPropertiesPage1->setLayout(layoutPropertiesPage1);
    groupBoxPropertiesPage2->setLayout(layoutPropertiesPage2);
    layoutTabPage1->addWidget(groupBoxDetails,0,Qt::AlignCenter);
    layoutTabPage1->addWidget(groupBoxPropertiesPage1,0,Qt::AlignCenter);
    tabPage1->setLayout(layoutTabPage1);
    layoutTabPage2->addWidget(groupBoxPropertiesPage2);
    tabPage2->setLayout(layoutTabPage2);
    tabWidget->addTab(tabPage1, tr("Details/Properties"));
    tabWidget->addTab(tabPage2, tr("Properties-continued"));

    layoutWidgetAndDisplay->addWidget(tabWidget,1,Qt::AlignCenter);
    layoutWidgetAndDisplay->addWidget(new QLabel(tr("For CAD Model Display")),2, Qt::AlignCenter);

    layoutSTDialog->addLayout(layoutWidgetAndDisplay,0);
    layoutSTDialog->addWidget(m_buttonBox);
    setLayout(layoutSTDialog);
}

void SpacecraftStarTrackerWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftStarTrackerWidget::createConnections()
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
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){this->mapDataFromWidgetToModel();});

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSampleTime, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMountingAngle1, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMountingAngle2, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMountingAngle3, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFOVsizeX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFOVsizeY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxMountingAngleSeq, &QComboBox::currentTextChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editExclusionSun, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editExclusionEarth, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editExclusionMoon, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editNoiseEquivalentAngle1, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editNoiseEquivalentAngle2, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editNoiseEquivalentAngle3, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void SpacecraftStarTrackerWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftStarTrackerWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<StarTracker>())
        return;
    m_index = index;
    mapDataFromModelToWidget();
}

bool SpacecraftStarTrackerWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<StarTracker>())
        return false;
    StarTracker ST = m_index.data().value<StarTracker>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();
    setWindowTitle(ST.name());

    const int precision = 6;
    chkbxIncluded->setChecked(ST.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());
    editSampleTime->setText(QString::number(ST.sampleTime(),'f',precision));
    editMountingAngle1->setText(QString::number(ST.mountingAngles()[0],'f',precision));
    editMountingAngle2->setText(QString::number(ST.mountingAngles()[1],'f',precision));
    editMountingAngle3->setText(QString::number(ST.mountingAngles()[2],'f',precision));
    comboboxMountingAngleSeq->setCurrentText(ST.mountingAnglesSeq());
    editFOVsizeX->setText(QString::number(ST.FOV_Size()[0],'f', precision));
    editFOVsizeY->setText(QString::number(ST.FOV_Size()[1],'f', precision));
    editExclusionSun->setText(QString::number(ST.SunMoonEarthExclusionAngles()[0],'f',precision));
    editExclusionEarth->setText(QString::number(ST.SunMoonEarthExclusionAngles()[1],'f',precision));
    editExclusionMoon->setText(QString::number(ST.SunMoonEarthExclusionAngles()[2],'f',precision));
    editNoiseEquivalentAngle1->setText(QString::number(ST.noiseEquivAng()[0],'f',precision));
    editNoiseEquivalentAngle2->setText(QString::number(ST.noiseEquivAng()[1],'f',precision));
    editNoiseEquivalentAngle3->setText(QString::number(ST.noiseEquivAng()[2],'f',precision));
    editFlexNodeIndex->setText(QString::number(ST.flexNodeIndex()));
    return true;


}

bool SpacecraftStarTrackerWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<StarTracker>())
        return false;
    QVariant newData = QVariant();
    StarTracker newST = m_index.data().value<StarTracker>();

    newST.edit(editSampleTime->text().toDouble(),
    {editMountingAngle1->text().toDouble(), editMountingAngle2->text().toDouble(), editMountingAngle3->text().toDouble()},
               comboboxMountingAngleSeq->currentText(),
    {editFOVsizeX->text().toDouble(), editFOVsizeY->text().toDouble()},
    {editExclusionSun->text().toDouble(), editExclusionEarth->text().toDouble(), editExclusionMoon->text().toDouble()},
    {editNoiseEquivalentAngle1->text().toDouble(), editNoiseEquivalentAngle2->text().toDouble(), editNoiseEquivalentAngle3->text().toDouble()},
               editFlexNodeIndex->text().toUInt(), chkbxIncluded->isChecked());

    newData.setValue(newST);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}


/** Widget for GPS data **/

SpacecraftGPSRWidget::SpacecraftGPSRWidget(QWidget* parent) : QDialog(parent)
{
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save  |
                                       QDialogButtonBox::Apply |
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}

SpacecraftGPSRWidget::~SpacecraftGPSRWidget()
{

}

void SpacecraftGPSRWidget::createWidgets()
{
    QFormLayout* layoutLeft = new QFormLayout;
    QFormLayout* layoutRight = new QFormLayout;
    QHBoxLayout* layoutMiddle = new QHBoxLayout;
    QVBoxLayout* layoutAll = new QVBoxLayout;
    const int maxWidthGroupBox = 400;
    const int minWidthGroupBox = 380;
    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    groupBoxDetails->setMaximumWidth(maxWidthGroupBox);
    groupBoxDetails->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutDetails = new QFormLayout;
    chkbxIncluded = new QCheckBox(tr("Included in the calculation"));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxProperties = new QGroupBox(tr("Properties"));
    groupBoxProperties->setAlignment(Qt::AlignCenter);
    groupBoxProperties->setMaximumWidth(maxWidthGroupBox);
    groupBoxProperties->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutProperties = new QFormLayout;
    labelSampleTime = new QLabel(tr("Sample time (sec)"));
    editSampleTime = new QLineEdit;
    editSampleTime->setValidator(new QDoubleValidator);
    labelPositionNoise = new QLabel(tr("Position Noise (m RMS)"));
    editPositionNoise = new QLineEdit;
    editPositionNoise->setValidator(new QDoubleValidator);
    labelVelocityNoise = new QLabel(tr("Velocity Noise (m/sec RMS)"));
    editVelocityNoise = new QLineEdit;
    editVelocityNoise->setValidator(new QDoubleValidator);
    labelTimeNoise = new QLabel(tr("Time Noise (sec RMS)"));
    editTimeNoise = new QLineEdit;
    editTimeNoise->setValidator(new QDoubleValidator);
    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);
    layoutProperties->addRow(labelSampleTime, editSampleTime);
    layoutProperties->addRow(labelPositionNoise, editPositionNoise);
    layoutProperties->addRow(labelVelocityNoise, editVelocityNoise);
    layoutProperties->addRow(labelTimeNoise, editTimeNoise);
    layoutProperties->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    groupBoxProperties->setLayout(layoutProperties);

    layoutLeft->addRow(groupBoxDetails);
    layoutLeft->addRow(groupBoxProperties);
    layoutRight->addRow(new QLabel(tr("For CAD model display.")));
    layoutMiddle->addLayout(layoutLeft);
    layoutMiddle->addLayout(layoutRight);
    layoutAll->addLayout(layoutMiddle);
    layoutAll->addWidget(m_buttonBox);

    setLayout(layoutAll);
}

void SpacecraftGPSRWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftGPSRWidget::createConnections()
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
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){this->mapDataFromWidgetToModel();});

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSampleTime, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPositionNoise, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editVelocityNoise, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editTimeNoise, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void SpacecraftGPSRWidget::setModel(QAbstractItemModel *model)
{
    if(model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftGPSRWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<GPSReceiver>())
        return;
    m_index = index;
    mapDataFromModelToWidget();
}

bool SpacecraftGPSRWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<GPSReceiver>())
        return false;
    const int precision = 6;
    GPSReceiver GPSR = m_index.data().value<GPSReceiver>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();

    setWindowTitle(GPSR.name());
    chkbxIncluded->setChecked(GPSR.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());

    editSampleTime->setText(QString::number(GPSR.sampleTime(), 'f', precision));
    editPositionNoise->setText(QString::number(GPSR.posNoise(), 'f', precision));
    editVelocityNoise->setText(QString::number(GPSR.velNoise(), 'f', precision));
    editTimeNoise->setText(QString::number(GPSR.timeNoise(), 'f', precision));
    editFlexNodeIndex->setText(QString::number(GPSR.flexNodeIndex()));
    return true;
}

bool SpacecraftGPSRWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<GPSReceiver>())
        return false;
    QVariant newData = QVariant();
    GPSReceiver newGPSR = m_index.data().value<GPSReceiver>();

    newGPSR.edit(editSampleTime->text().toDouble(), editPositionNoise->text().toDouble(),
                 editVelocityNoise->text().toDouble(), editTimeNoise->text().toDouble(),
                 editFlexNodeIndex->text().toUInt(), chkbxIncluded->isChecked());

    newData.setValue(newGPSR);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}


/** Widget for Accelerometer data **/
SpacecraftAccelerometerWidget::SpacecraftAccelerometerWidget(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("Accelerometer"));
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save  |
                                       QDialogButtonBox::Apply |
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}

SpacecraftAccelerometerWidget::~SpacecraftAccelerometerWidget()
{

}

void SpacecraftAccelerometerWidget::createWidgets()
{
    const int maxWidthGroupBox = 450;
    const int minWidthGroupBox = 400;

    tabWidget = new QTabWidget;
    tabPage1 = new QWidget;
    tabPage2 = new QWidget;

    QVBoxLayout* layoutACCLDialog = new QVBoxLayout;
    QHBoxLayout* layoutWidgetAndDisplay = new QHBoxLayout;
    QVBoxLayout* layoutTabPage1 = new QVBoxLayout;
    QVBoxLayout* layoutTabPage2 = new QVBoxLayout;


    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    groupBoxDetails->setMaximumWidth(maxWidthGroupBox);
    groupBoxDetails->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutDetails = new QFormLayout;

    chkbxIncluded = new QCheckBox(tr("Included in the calculation"));
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelSpacecraft = new QLabel(tr("Spacecraft"));
    editSpacecraft = new QLineEdit;
    editSpacecraft->setReadOnly(true);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelSpacecraft, editSpacecraft);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxPropertiesPage1 = new QGroupBox(tr("Properties"));
    groupBoxPropertiesPage1->setAlignment(Qt::AlignCenter);
    groupBoxPropertiesPage1->setMaximumWidth(maxWidthGroupBox);
    groupBoxPropertiesPage1->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutPropertiesPage1 = new QFormLayout;
    groupBoxPropertiesPage2 = new QGroupBox(tr("Properties-continued"));
    groupBoxPropertiesPage2->setAlignment(Qt::AlignCenter);
    groupBoxPropertiesPage2->setMaximumWidth(maxWidthGroupBox);
    groupBoxPropertiesPage2->setMinimumWidth(minWidthGroupBox);
    QFormLayout* layoutPropertiesPage2 = new QFormLayout;


    labelSampleTime = new QLabel(tr("Sample Time (sec)"));
    editSampleTime = new QLineEdit;
    editSampleTime->setValidator(new QDoubleValidator);
    groupBoxPositionInBody0 = new QGroupBox(tr("Position in Body 0 (m)"));
    QHBoxLayout* layoutPositionInBody0 = new QHBoxLayout;
    labelPositionInBody0_X = new QLabel(tr("X"));
    editPositionInBody0_X = new QLineEdit;
    editPositionInBody0_X->setValidator(new QDoubleValidator);
    labelPositionInBody0_Y = new QLabel(tr("Y"));
    editPositionInBody0_Y = new QLineEdit;
    editPositionInBody0_Y->setValidator(new QDoubleValidator);
    labelPositionInBody0_Z = new QLabel(tr("Z"));
    editPositionInBody0_Z = new QLineEdit;
    editPositionInBody0_Z->setValidator(new QDoubleValidator);
    layoutPositionInBody0->addWidget(labelPositionInBody0_X, 1);
    layoutPositionInBody0->addWidget(editPositionInBody0_X, 2);
    layoutPositionInBody0->addWidget(labelPositionInBody0_Y, 1);
    layoutPositionInBody0->addWidget(editPositionInBody0_Y, 2);
    layoutPositionInBody0->addWidget(labelPositionInBody0_Z, 1);
    layoutPositionInBody0->addWidget(editPositionInBody0_Z, 2);
    groupBoxPositionInBody0->setLayout(layoutPositionInBody0);

    groupBoxAxisExpressedInBodyFrame = new QGroupBox(tr("Axis expressed in Body Frame"));
    QVBoxLayout* layoutAxisExpressedInBodyFrame = new QVBoxLayout;
    QHBoxLayout* layoutAxisExpressedInBodyFrameComponents = new QHBoxLayout;
    labelAxisExpressedInBodyFrameX = new QLabel(tr("X"));
    editAxisExpressedInBodyFrameX = new QLineEdit;
    editAxisExpressedInBodyFrameX->setValidator(new QDoubleValidator);
    labelAxisExpressedInBodyFrameY = new QLabel(tr("Y"));
    editAxisExpressedInBodyFrameY = new QLineEdit;
    editAxisExpressedInBodyFrameY->setValidator(new QDoubleValidator);
    labelAxisExpressedInBodyFrameZ = new QLabel(tr("Z"));
    editAxisExpressedInBodyFrameZ = new QLineEdit;
    editAxisExpressedInBodyFrameZ->setValidator(new QDoubleValidator);
   // QHBoxLayout* layoutBtnNormalize = new QHBoxLayout;
    btnNormalize = new QPushButton(tr("Normalize"));
    btnNormalize->setMaximumWidth(150);
    //layoutBtnNormalize->addWidget(btnNormalize,0,Qt::AlignCenter);

    layoutAxisExpressedInBodyFrameComponents->addWidget(labelAxisExpressedInBodyFrameX, 1);
    layoutAxisExpressedInBodyFrameComponents->addWidget(editAxisExpressedInBodyFrameX, 2);
    layoutAxisExpressedInBodyFrameComponents->addWidget(labelAxisExpressedInBodyFrameY, 1);
    layoutAxisExpressedInBodyFrameComponents->addWidget(editAxisExpressedInBodyFrameY, 2);
    layoutAxisExpressedInBodyFrameComponents->addWidget(labelAxisExpressedInBodyFrameZ, 1);
    layoutAxisExpressedInBodyFrameComponents->addWidget(editAxisExpressedInBodyFrameZ, 2);

    layoutAxisExpressedInBodyFrame->addLayout(layoutAxisExpressedInBodyFrameComponents);
    layoutAxisExpressedInBodyFrame->addWidget(btnNormalize, 0, Qt::AlignCenter);

    groupBoxAxisExpressedInBodyFrame->setLayout(layoutAxisExpressedInBodyFrame);

    labelMaxAcceleration = new QLabel(tr("Max Acceleration (m/s") + QString::fromUtf8("\u00B2") + tr(")"));
    editMaxAcceleration = new QLineEdit;
    editMaxAcceleration->setValidator(new QDoubleValidator);
    labelScaleFactorError = new QLabel(tr("Scale Factor Error (ppm)"));
    editScaleFactorError = new QLineEdit;
    editScaleFactorError->setValidator(new QDoubleValidator);
    labelQuantization = new QLabel(tr("Quantization (m/s") + QString::fromUtf8("\u00B2") + tr(")"));
    editQuantization = new QLineEdit;
    editQuantization -> setValidator(new QDoubleValidator);
    labelRandomWalk = new QLabel(tr("DV Random Walk (m/s/rt-hr)"));
    editRandomWalk = new QLineEdit;
    editRandomWalk->setValidator(new QDoubleValidator);

    groupboxBiasStabilityTimespan = new QGroupBox(tr("Bias Stability over Timespan"));
    QFormLayout* layoutBiasStabilityTimespan = new QFormLayout;
    labelBiasStability = new QLabel(tr("Bias Stability ")+tr("(m/s") + QString::fromUtf8("\u00B2") + tr(")"));
    editBiasStability = new QLineEdit;
    editBiasStability->setValidator(new QDoubleValidator);
    labelTimeSpan = new QLabel(tr("Timespan (hr)"));
    editTimeSpan = new QLineEdit;
    editTimeSpan->setValidator(new QDoubleValidator);
    layoutBiasStabilityTimespan->addRow(labelBiasStability, editBiasStability);
    layoutBiasStabilityTimespan->addRow(labelTimeSpan, editTimeSpan);
    groupboxBiasStabilityTimespan->setLayout(layoutBiasStabilityTimespan);
    labelDVNoise =  new QLabel(tr("DV Noise (m/s)"));
    editDVNoise = new QLineEdit;
    editDVNoise->setValidator(new QDoubleValidator);
    labelInitialBias = new QLabel(tr("Initial Bias (m/s") + QString::fromUtf8("\u00B2") + tr(")"));
    editInitialBias = new QLineEdit;
    editInitialBias->setValidator(new QDoubleValidator);
    labelFlexNodeIndex = new QLabel(tr("Flex Node Index"));
    editFlexNodeIndex = new QLineEdit;
    editFlexNodeIndex->setValidator(new QIntValidator);

    layoutPropertiesPage1->addRow(labelSampleTime, editSampleTime);
    layoutPropertiesPage1->addRow(groupBoxPositionInBody0);
    layoutPropertiesPage1->addRow(groupBoxAxisExpressedInBodyFrame);
    layoutPropertiesPage1->addRow(labelMaxAcceleration, editMaxAcceleration);
    layoutPropertiesPage2->addRow(labelScaleFactorError, editScaleFactorError);
    layoutPropertiesPage2->addRow(labelQuantization, editQuantization);
    layoutPropertiesPage2->addRow(labelRandomWalk, editRandomWalk);
    layoutPropertiesPage2->addRow(groupboxBiasStabilityTimespan);
    layoutPropertiesPage2->addRow(labelDVNoise, editDVNoise);
    layoutPropertiesPage2->addRow(labelInitialBias, editInitialBias);
    layoutPropertiesPage2->addRow(labelFlexNodeIndex, editFlexNodeIndex);
    layoutPropertiesPage2->setSpacing(26);

    groupBoxPropertiesPage1->setLayout(layoutPropertiesPage1);
    groupBoxPropertiesPage2->setLayout(layoutPropertiesPage2);
    layoutTabPage1->addWidget(groupBoxDetails, 0, Qt::AlignCenter);
    layoutTabPage1->addWidget(groupBoxPropertiesPage1, 0, Qt::AlignCenter);
    tabPage1->setLayout(layoutTabPage1);

    layoutTabPage2->addWidget(groupBoxPropertiesPage2,0,Qt::AlignCenter);
    tabPage2->setLayout(layoutTabPage2);

    tabWidget->addTab(tabPage1,tr("Details/Properties"));
    tabWidget->addTab(tabPage2,tr("Properties-continued"));

    layoutWidgetAndDisplay->addWidget(tabWidget,1,Qt::AlignCenter);
    layoutWidgetAndDisplay->addWidget(new QLabel(tr("For CAD Model Display")), 2, Qt::AlignCenter);
    layoutACCLDialog->addLayout(layoutWidgetAndDisplay);
    layoutACCLDialog->addWidget(m_buttonBox);

    setLayout(layoutACCLDialog);
}

void SpacecraftAccelerometerWidget::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void SpacecraftAccelerometerWidget::createConnections()
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
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){this->mapDataFromWidgetToModel();});

    connect(chkbxIncluded, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSampleTime, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPositionInBody0_X, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPositionInBody0_Y, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPositionInBody0_Z, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisExpressedInBodyFrameX, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisExpressedInBodyFrameY, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAxisExpressedInBodyFrameZ, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMaxAcceleration, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editScaleFactorError, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editQuantization, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRandomWalk, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editBiasStability, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editTimeSpan, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDVNoise, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialBias, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFlexNodeIndex, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(btnNormalize, &QPushButton::clicked, this,
            &SpacecraftAccelerometerWidget::normalizeAxisComponents);
}

void SpacecraftAccelerometerWidget::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void SpacecraftAccelerometerWidget::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<Accelerometer>())
        return;
    m_index = index;
    mapDataFromModelToWidget();
}

bool SpacecraftAccelerometerWidget::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<Accelerometer>())
        return false;

    const int precision = 6;
    Accelerometer ACCL = m_index.data().value<Accelerometer>();
    Spacecraft SC = m_index.parent().data().value<Spacecraft>();
    Mission M = m_index.parent().parent().parent().data().value<Mission>();

    setWindowTitle(ACCL.name());
    chkbxIncluded->setChecked(ACCL.includedInCalculation());
    editMission->setText(M.name());
    editSpacecraft->setText(SC.name());

    editSampleTime->setText(QString::number(ACCL.sampleTime(), 'f', precision));
    editPositionInBody0_X->setText(QString::number(ACCL.posBody0()[0],'f',precision));
    editPositionInBody0_Y->setText(QString::number(ACCL.posBody0()[1],'f',precision));
    editPositionInBody0_Z->setText(QString::number(ACCL.posBody0()[2],'f',precision));
    editAxisExpressedInBodyFrameX->setText(QString::number(ACCL.axisInBodyFrame()[0],'f',precision));
    editAxisExpressedInBodyFrameY->setText(QString::number(ACCL.axisInBodyFrame()[1],'f',precision));
    editAxisExpressedInBodyFrameZ->setText(QString::number(ACCL.axisInBodyFrame()[2],'f',precision));
    editMaxAcceleration->setText(QString::number(ACCL.maxAcceleration(), 'f', precision));
    editScaleFactorError->setText(QString::number(ACCL.scaleFactorError(), 'f', precision));
    editQuantization->setText(QString::number(ACCL.quantization(), 'f', precision));
    editRandomWalk->setText(QString::number(ACCL.randomWalk(), 'f', precision));
    editBiasStability->setText(QString::number(ACCL.biasStability(), 'f', precision));
    editTimeSpan->setText(QString::number(ACCL.timeSpan(),'f', precision));
    editDVNoise->setText(QString::number(ACCL.DVNoise(), 'f', precision));
    editInitialBias->setText(QString::number(ACCL.initialBias(), 'f', precision));
    editFlexNodeIndex->setText(QString::number(ACCL.flexNodeIndex(), 'f', precision));
    return true;
}

bool SpacecraftAccelerometerWidget::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<Accelerometer>())
        return false;

    QVariant newData = QVariant();
    Accelerometer newACCL = m_index.data().value<Accelerometer>();

    newACCL.edit(editSampleTime->text().toDouble(),
    {editPositionInBody0_X->text().toDouble(), editPositionInBody0_Y->text().toDouble(), editPositionInBody0_Z->text().toDouble()},
    {editAxisExpressedInBodyFrameX->text().toDouble(), editAxisExpressedInBodyFrameY->text().toDouble(), editAxisExpressedInBodyFrameZ->text().toDouble()},
                 editMaxAcceleration->text().toDouble(),
                 editScaleFactorError->text().toDouble(), editQuantization->text().toDouble(),
                 editRandomWalk->text().toDouble(),
                 editBiasStability->text().toDouble(), editTimeSpan->text().toDouble(),
                 editDVNoise->text().toDouble(), editInitialBias->text().toDouble(),
                 editFlexNodeIndex->text().toUInt(), chkbxIncluded->isChecked());

    newData.setValue(newACCL);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
    return true;
}

void SpacecraftAccelerometerWidget::normalizeAxisComponents()
{
    const double epsilon = 0.000001;
    double X = editAxisExpressedInBodyFrameX->text().toDouble();
    double Y = editAxisExpressedInBodyFrameY->text().toDouble();
    double Z = editAxisExpressedInBodyFrameZ->text().toDouble();

    if (std::abs(X) < epsilon && std::abs(Y) < epsilon && std::abs(Z) < epsilon)
        return;

    const double norm = std::sqrt(X*X + Y*Y + Z*Z);
    X = X/norm;
    Y = Y/norm;
    Z = Z/norm;

    editAxisExpressedInBodyFrameX->setText(QString::number(X));
    editAxisExpressedInBodyFrameY->setText(QString::number(Y));
    editAxisExpressedInBodyFrameZ->setText(QString::number(Z));

}

