#include "WidgetHeaders/spacecraftdialog.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "MVDheaders/qt42delegate.h"
#include "WidgetHeaders/sccomponentswidgets.h"
#include "DataHeaders/mission.h"
#include "MVDheaders/qt42model.h"
#include "ShareHeaders/qt42commands.h"
#include <QtWidgets>
#include <QUndoStack>

SpacecraftDialog::SpacecraftDialog(QWidget* parent): QDialog (parent)
{
    if (parent)
        parentTabWidget = static_cast<QTabWidget*>(parent);

    m_undoStack = new QUndoStack(this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Save   |
                                     QDialogButtonBox::Apply  |
                                     QDialogButtonBox::Cancel |
                                     QDialogButtonBox::Reset);
    resize(700,400);
    setMinimumSize(100,100);
    createActions();
    setUpModels();
    setWidgets();
    setTabs();
    mainLayout = new QVBoxLayout();

    labelDialogMissionSpacecraft = new QLabel();
    mainLayout->addWidget(labelDialogMissionSpacecraft);
    mainLayout->addWidget(SpacecraftTabs);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(*pal);
    createConnections();

}


SpacecraftDialog::~SpacecraftDialog(){

}

SpacecraftDialog::SpacecraftDialog(const SpacecraftDialog& SC_Dialog)
{
    Q_UNUSED(SC_Dialog)
}

void SpacecraftDialog::setUpModels(){
    model_OrbitProp = new QStringListModel(list_OrbitProp, this);
    model_ReferncePoint = new QStringListModel(list_ReferencePoint, this);
    model_AngVelRefernceFrame = new QStringListModel(list_ReferenceFrame, this);
    model_AtttdSttType  = new QStringListModel(list_AttitudeType, this);
    model_AtttdRefFrame = new QStringListModel(list_ReferenceFrameWithFormationFrame, this);
    model_EulerSeq = new QStringListModel(list_EulerSeq, this);
    model_jointRotation = new QStringListModel(list_jointRotation,this);
    model_massPropRef = new QStringListModel(list_massPropRef,this);
    model_SCcomponent = new QStringListModel(list_SCcomponents, this);
}

void SpacecraftDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this, tr("&Undo"));
    m_redoAction = m_undoStack->createRedoAction(this, tr("&Redo"));
}

void SpacecraftDialog::moveToFirstPage() const
{
    SpacecraftTabs->setCurrentIndex(0);
}

void SpacecraftDialog::setWidgets()
{
    /** Spacecraft Editing Details **/
    QFormLayout* layoutDetails = new QFormLayout;
    layoutDetails->setSpacing(26);
    groupBoxDetails = new QGroupBox(tr("Details"), this);
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    chkbxIncluded = new QCheckBox(tr("Included in calculation."));
    labelSC_Name    = new QLabel(tr("Name"), groupBoxDetails);
    editSC_Name     = new QLineEdit(groupBoxDetails);
    editSC_Name->setReadOnly(true);
    editSC_Name->setMaximumWidth(320);
    labelMissionName = new QLabel(tr("Mission"),groupBoxDetails);
    editMissionName  = new QLineEdit(groupBoxDetails);
    editMissionName->setReadOnly(true);
    editMissionName->setMaximumWidth(320);
    labelSC_Directory = new QLabel(tr("Directory"), groupBoxDetails);
    editSC_Directory  = new QLineEdit(groupBoxDetails);
    editSC_Directory->setReadOnly(true);
    editSC_Directory->setMaximumWidth(320);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelSC_Name, editSC_Name);
    layoutDetails->addRow(labelMissionName, editMissionName);
    layoutDetails->addRow(labelSC_Directory, editSC_Directory);
    layoutDetails->setContentsMargins(30,40,30,30);
    groupBoxDetails->setLayout(layoutDetails);

    /** Spacecraft Description Items **/
    QGridLayout* layoutDescriptions = new QGridLayout;
    layoutDescriptions->setContentsMargins(15,15,15,15);
    groupBoxDescription = new QGroupBox(tr("Spacecraft Description File"), this);
    groupBoxDescription->setAlignment(Qt::AlignCenter);
    labelDescription    = new QLabel(tr("Description"), groupBoxDescription);
    editDescription     = new QTextEdit(groupBoxDescription);
    labelLabel          = new QLabel(tr("Label"), groupBoxDescription);
    editLabel           = new QLineEdit(groupBoxDescription);
    labelSpriteFileName = new QLabel(tr("Sprite File Name"), groupBoxDescription);
    editSPriteFileName  = new QLineEdit(groupBoxDescription);
    labelFSWIdentifier  = new QLabel(tr("Flight Software Identifier"),
                                     groupBoxDescription);    // Flight Software Identifier
    editFSWIdentifier   = new QLineEdit(groupBoxDescription);
    labelFSWSampleTime  = new QLabel(tr("Flight Software Sample Time (sec)"),
                                     groupBoxDescription); //FSW Sample Time, sec
    editFSWSampleTime   = new QLineEdit(groupBoxDescription);
    editFSWSampleTime->setValidator(new QDoubleValidator);

    layoutDescriptions->addWidget(labelDescription, 0, 0, 1, 2);
    layoutDescriptions->addWidget(editDescription,  1, 0, 2, 2);
    layoutDescriptions->addWidget(labelLabel, 3, 0, 1, 1);
    layoutDescriptions->addWidget(editLabel , 4, 0, 1, 2);
    layoutDescriptions->addWidget(labelSpriteFileName,5, 0, 1, 1);
    layoutDescriptions->addWidget(editSPriteFileName, 6, 0, 1, 2);
    layoutDescriptions->addWidget(labelFSWIdentifier, 7, 0, 1, 1);
    layoutDescriptions->addWidget(editFSWIdentifier, 8, 0, 1, 2);
    layoutDescriptions->addWidget(labelFSWSampleTime, 9, 0, 1, 1);
    layoutDescriptions->addWidget(editFSWSampleTime, 10, 0, 1, 2);
    groupBoxDescription->setLayout(layoutDescriptions);

    /**  Orbit Parameters  (in the same tab where "Initial Attitude" is)**/
    QGridLayout* layoutOrbitParameters = new QGridLayout;
    groupBoxOrbitParameter = new QGroupBox(tr("Orbit Parameters"), this);
    groupBoxOrbitParameter->setAlignment(Qt::AlignCenter);
    labelOrbitProp         = new QLabel(tr("Orbit Propagation Method"),
                                        groupBoxOrbitParameter);
    comboboxOrbitProp      = new QComboBox(groupBoxOrbitParameter);  // could be FIXED, EULER_HILL, or ENCKE
    comboboxOrbitProp->setModel(model_OrbitProp);
    labelReferncePoint    = new QLabel(tr("Reference Point"), groupBoxOrbitParameter) ;
                           // could be CM or ORIGIN, wrt F.
    comboboxReferncePoint = new QComboBox(groupBoxOrbitParameter);  // could be CM or ORIGIN, wrt F.
    comboboxReferncePoint->setModel(model_ReferncePoint);
    groupBoxPosition = new QGroupBox(tr("Position Vector (m)"), groupBoxOrbitParameter);
    QGridLayout* layoutPosition = new QGridLayout;
    labelPosition1 = new QLabel(tr("p1"), groupBoxPosition);
    labelPosition2 = new QLabel(tr("p2"), groupBoxPosition);
    labelPosition3 = new QLabel(tr("p3"), groupBoxPosition);
    editPosition1 = new QLineEdit(groupBoxPosition);
    editPosition1->setValidator(new QDoubleValidator);
    editPosition2 = new QLineEdit(groupBoxPosition);
    editPosition2->setValidator(new QDoubleValidator);
    editPosition3 = new QLineEdit(groupBoxPosition);
    editPosition3->setValidator(new QDoubleValidator);
    layoutPosition->addWidget(labelPosition1, 0, 0, 1, 2);
    layoutPosition->addWidget(editPosition1 , 0, 2, 1, 2);
    layoutPosition->addWidget(labelPosition2, 1, 0, 1, 2);
    layoutPosition->addWidget(editPosition2,  1, 2, 1, 2);
    layoutPosition->addWidget(labelPosition3, 2, 0, 1, 2);
    layoutPosition->addWidget(editPosition3,  2, 2, 1, 2);
    groupBoxPosition->setLayout(layoutPosition);

    groupBoxVelocity = new QGroupBox(tr("Velocity Vector (m/s)"), groupBoxOrbitParameter);
    QGridLayout* layoutVelocity = new QGridLayout;
    labelVelocity1 = new QLabel(tr("v1"), groupBoxVelocity);
    labelVelocity2 = new QLabel(tr("v2"), groupBoxVelocity);
    labelVelocity3 = new QLabel(tr("v3"), groupBoxVelocity);
    editVelocity1 = new QLineEdit(groupBoxVelocity);
    editVelocity1->setValidator(new QDoubleValidator);
    editVelocity2 = new QLineEdit(groupBoxVelocity);
    editVelocity2->setValidator(new QDoubleValidator);
    editVelocity3 = new QLineEdit(groupBoxVelocity);
    editVelocity3->setValidator(new QDoubleValidator);
    layoutVelocity->addWidget(labelVelocity1, 0, 0, 1, 2);
    layoutVelocity->addWidget(editVelocity1,  0, 2, 1, 2);
    layoutVelocity->addWidget(labelVelocity2, 1, 0, 1, 2);
    layoutVelocity->addWidget(editVelocity2,  1, 2, 1, 2);
    layoutVelocity->addWidget(labelVelocity3, 2, 0, 1, 2);
    layoutVelocity->addWidget(editVelocity3,  2, 2, 1, 2);
    groupBoxVelocity->setLayout(layoutVelocity);
    layoutOrbitParameters->addWidget(labelOrbitProp,     0, 0, 1, 1);
    layoutOrbitParameters->addWidget(comboboxOrbitProp,  0, 1, 1, 1);
    layoutOrbitParameters->addWidget(labelReferncePoint, 1, 0, 1, 1);
    layoutOrbitParameters->addWidget(comboboxReferncePoint, 1, 1, 1, 1);
    layoutOrbitParameters->addWidget(groupBoxPosition, 2,0,2,2);
    layoutOrbitParameters->addWidget(groupBoxVelocity, 4,0,2,2);
    groupBoxOrbitParameter->setLayout(layoutOrbitParameters);


    /** Initial Attitude (in the same tab where "Orbit Parameters" is)**/
    groupBoxInitAttitude  = new QGroupBox(tr("Initial Attitudes"), this);
    groupBoxInitAttitude->setAlignment(Qt::AlignCenter);
    layoutInitialAttitude = new QVBoxLayout();
    QGridLayout* layoutInitAttiFrames = new QGridLayout();
    groupBoxInitAttiFrames   = new QGroupBox(groupBoxInitAttitude);
    labelAngVelRefernceFrame = new QLabel(tr("Angular Velocity Reference Frame"),
                                          groupBoxInitAttitude);
    comboboxAngVelRefernceFrame = new QComboBox(groupBoxInitAttitude);
    comboboxAngVelRefernceFrame->setModel(model_AngVelRefernceFrame);
    labelAtttdSttType = new QLabel(tr("Attitude State Type"));
    comboboxAtttdSttType = new QComboBox(groupBoxInitAttitude);
    comboboxAtttdSttType->setModel(model_AtttdSttType);
    connect(comboboxAtttdSttType, &QComboBox::currentTextChanged,this, &SpacecraftDialog::showAttitudeStateType);
    labelAtttdRefFrame = new QLabel(tr("Attitude Reference Frame"));
    comboboxAtttdRefFrame = new QComboBox(groupBoxInitAttitude);
    comboboxAtttdRefFrame->setModel(model_AtttdRefFrame);
    layoutInitAttiFrames->addWidget(labelAngVelRefernceFrame,0,0,1,2);
    layoutInitAttiFrames->addWidget(comboboxAngVelRefernceFrame, 0,2,1,2);
    layoutInitAttiFrames->addWidget(labelAtttdSttType, 1,0,1,2);
    layoutInitAttiFrames->addWidget(comboboxAtttdSttType, 1, 2,1,2);
    layoutInitAttiFrames->addWidget(labelAtttdRefFrame, 2, 0, 1,2);
    layoutInitAttiFrames->addWidget(comboboxAtttdRefFrame,2,2,1,2);
    groupBoxInitAttiFrames->setLayout(layoutInitAttiFrames);
    QGridLayout* layoutAngVel = new QGridLayout();
    groupBoxAngVel = new QGroupBox(tr("Angular Velocity (deg/sec)"), groupBoxInitAttitude);
    labelAngVel1 = new QLabel(QString::fromUtf8("\u03C9")+QString::number(1), groupBoxAngVel);
    editAngVel1  = new QLineEdit(groupBoxAngVel);
    editAngVel1->setValidator(new QDoubleValidator);
    labelAngVel2 = new QLabel(QString::fromUtf8("\u03C9")+QString::number(2), groupBoxAngVel);
    editAngVel2  = new QLineEdit(groupBoxAngVel);
    editAngVel2->setValidator(new QDoubleValidator);
    labelAngVel3 = new QLabel(QString::fromUtf8("\u03C9")+QString::number(3), groupBoxAngVel);
    editAngVel3  = new QLineEdit(groupBoxAngVel);
    editAngVel3->setValidator(new QDoubleValidator);
    layoutAngVel->addWidget(labelAngVel1 , 0 ,0, 1, 2);
    layoutAngVel->addWidget(editAngVel1  , 0, 2, 1, 2);
    layoutAngVel->addWidget(labelAngVel2 , 1 ,0, 1, 2);
    layoutAngVel->addWidget(editAngVel2  , 1, 2, 1, 2);
    layoutAngVel->addWidget(labelAngVel3 , 2 ,0, 1, 2);
    layoutAngVel->addWidget(editAngVel3  , 2, 2, 1, 2);
    groupBoxAngVel->setLayout(layoutAngVel);

    QGridLayout* layoutQuaternion = new QGridLayout();
    groupBoxQuaternion = new QGroupBox(tr("Quaternion"), groupBoxInitAttitude);
    labelQuaternion1 = new QLabel(tr("q1"), groupBoxQuaternion);
    editQuaternion1  = new QLineEdit(groupBoxQuaternion);
    editQuaternion1->setValidator(new QDoubleValidator);
    labelQuaternion2 = new QLabel(tr("q2"), groupBoxQuaternion);
    editQuaternion2 = new QLineEdit(groupBoxQuaternion);
    editQuaternion2->setValidator(new QDoubleValidator);
    labelQuaternion3 = new QLabel(tr("q3"), groupBoxQuaternion);
    editQuaternion3 = new QLineEdit(groupBoxQuaternion);
    editQuaternion3->setValidator(new QDoubleValidator);
    labelQuaternion4 = new QLabel(tr("q4"), groupBoxQuaternion);
    editQuaternion4 = new QLineEdit(groupBoxQuaternion);
    editQuaternion4->setValidator(new QDoubleValidator);
    layoutQuaternion->addWidget(labelQuaternion1, 0,0,1,2);
    layoutQuaternion->addWidget(editQuaternion1, 0,2,1,2);
    layoutQuaternion->addWidget(labelQuaternion2, 1,0,1,2);
    layoutQuaternion->addWidget(editQuaternion2, 1,2,1,2);
    layoutQuaternion->addWidget(labelQuaternion3, 2,0,1,2);
    layoutQuaternion->addWidget(editQuaternion3, 2,2,1,2);
    layoutQuaternion->addWidget(labelQuaternion4, 3,0,1,2);
    layoutQuaternion->addWidget(editQuaternion4, 3,2,1,2);
    groupBoxQuaternion->setLayout(layoutQuaternion);

    QGridLayout* layoutEulerAngle = new QGridLayout();
    groupBoxEulerAngle = new QGroupBox(tr("Euler Angles (degree)"), groupBoxInitAttitude);
    labelAngle1 = new QLabel(QString::fromUtf8("\u03B8")+QString::number(1),
                             groupBoxEulerAngle);
    editAngle1  = new QLineEdit(groupBoxEulerAngle);
    editAngle1->setValidator(new QDoubleValidator);
    labelAngle2 = new QLabel(QString::fromUtf8("\u03B8")+QString::number(2),
                             groupBoxEulerAngle);
    editAngle2  = new QLineEdit(groupBoxEulerAngle);
    editAngle2->setValidator(new QDoubleValidator);
    labelAngle3 = new QLabel(QString::fromUtf8("\u03B8")+QString::number(3), groupBoxEulerAngle);
    editAngle3  = new QLineEdit(groupBoxEulerAngle);
    editAngle3->setValidator(new QDoubleValidator);
    labelEulerSeq    = new QLabel(tr("Euler Sequence"), groupBoxEulerAngle);
    comboboxEulerSeq = new QComboBox(groupBoxEulerAngle);
    comboboxEulerSeq->setModel(model_EulerSeq);

    layoutEulerAngle->addWidget(labelAngle1, 0,0,1,2);
    layoutEulerAngle->addWidget(editAngle1, 0,2,1,2);
    layoutEulerAngle->addWidget(labelAngle2, 1,0,1,2);
    layoutEulerAngle->addWidget(editAngle2, 1,2,1,2);
    layoutEulerAngle->addWidget(labelAngle3, 2,0,1,2);
    layoutEulerAngle->addWidget(editAngle3, 2,2,1,2);
    layoutEulerAngle->addWidget(labelEulerSeq, 3,0,1,2);
    layoutEulerAngle->addWidget(comboboxEulerSeq, 3,2,1,2);
    groupBoxEulerAngle->setLayout(layoutEulerAngle);

    layoutInitialAttitude->addWidget(groupBoxInitAttiFrames);
    layoutInitialAttitude->addWidget(groupBoxAngVel);
    layoutInitialAttitude->addWidget(groupBoxQuaternion);
    layoutInitialAttitude->addWidget(groupBoxEulerAngle);
    showAttitudeStateType(comboboxAtttdSttType->currentText());
    //layoutInitialAttitude->setSizeConstraint(QLayout::SetMinimumSize);
    groupBoxInitAttitude->setLayout(layoutInitialAttitude);

    /** Dynamics Flags **/
    groupBoxDynamicsFlags = new QGroupBox(tr("Dynamics Flags"), this);
    groupBoxDynamicsFlags->setAlignment(Qt::AlignCenter);
    QGridLayout* layoutDynamicsFlags = new QGridLayout;
    labelJointRotation = new QLabel(tr("Joint Rotation"), groupBoxDynamicsFlags);
    comboboxJointRotation = new QComboBox(groupBoxDynamicsFlags);
    comboboxJointRotation->setModel(model_jointRotation);
    labelMassPropsRef = new QLabel(tr("Mass Properties Reference"),
                                   groupBoxDynamicsFlags);  // Mass Props referenced to REFPT_CM or REFPT_JOINT
    comboboxMassPropsRef = new QComboBox(groupBoxDynamicsFlags); // This could be REFPT_CM or REFPT_JOINT
    comboboxMassPropsRef->setModel(model_massPropRef);
    labelDragCoefficient = new QLabel(tr("Drag Coefficient"), groupBoxDynamicsFlags);
    editDragCoefficient  = new QLineEdit(groupBoxDynamicsFlags);
    editDragCoefficient->setValidator(new QDoubleValidator);
    chkbxConstMassProps = new QCheckBox(tr("Assume constant mass properties"),groupBoxDynamicsFlags);
    chkbxPJForceTorque = new QCheckBox(tr("Passive Joint Forces and Torques Enabled"),
                                       groupBoxDynamicsFlags);  //Passive Joint Forces and Torques Enabled
    chkbxCCForceTorque = new QCheckBox(tr("Compute Constraint Forces and Torques"),
                                       groupBoxDynamicsFlags);
    chkbxFlexActive    = new QCheckBox("Flex Active Enabled", groupBoxDynamicsFlags); // Flex Active
    chkbxInclude2ndFlexTerm = new QCheckBox(tr("Include 2nd Order Flex Terms"),
                                            groupBoxDynamicsFlags); //Include 2nd Order Flex Terms
    layoutDynamicsFlags->addWidget(labelJointRotation      , 0, 0, 1, 2);
    layoutDynamicsFlags->addWidget(comboboxJointRotation   , 0, 2, 1, 2);
    layoutDynamicsFlags->addWidget(labelMassPropsRef       , 1, 0, 1, 2);
    layoutDynamicsFlags->addWidget(comboboxMassPropsRef    , 1, 2, 1, 2);
    layoutDynamicsFlags->addWidget(labelDragCoefficient    , 2, 0, 1, 2);
    layoutDynamicsFlags->addWidget(editDragCoefficient     , 2, 2, 1, 2);
    layoutDynamicsFlags->addWidget(chkbxConstMassProps     , 3, 0, 1, 4);
    layoutDynamicsFlags->addWidget(chkbxPJForceTorque      , 4, 0, 1, 4);
    layoutDynamicsFlags->addWidget(chkbxCCForceTorque      , 5, 0, 1, 4);
    layoutDynamicsFlags->addWidget(chkbxFlexActive         , 6, 0, 1, 4);
    layoutDynamicsFlags->addWidget(chkbxInclude2ndFlexTerm , 7, 0, 1, 4);
    groupBoxDynamicsFlags->setLayout(layoutDynamicsFlags);

    /** Spacecraft Components **/

    const QSize sizeMaxTableView(650,400);
    const int widthMaxBtnComboboxSCC = 100;
    groupBoxSCcomponents = new QGroupBox(tr("Spacecraft Components"), this);
    groupBoxSCcomponents->setAlignment(Qt::AlignCenter);

    tableViewSCcomponents = new QTableView();
    tableViewSCcomponents->setMaximumSize(sizeMaxTableView);


    QHBoxLayout* layoutSCcomponents = new QHBoxLayout;

    layoutSCcomponents->addWidget(tableViewSCcomponents);

    groupBoxSCcomponents->setLayout(layoutSCcomponents);
    groupBoxSCCedit = new QGroupBox(tr(""), this);
    QHBoxLayout* layoutBtnComboboxSCc = new QHBoxLayout;

    groupBoxSCCcreate = new QGroupBox(tr(""), this);
    groupBoxSCCcreate->setMaximumWidth(400);
    QHBoxLayout* layoutSCcomponentCretae = new QHBoxLayout;
    btnCreateNewSCcomponent = new QPushButton(tr("Create"));
    btnCreateNewSCcomponent->setMaximumWidth(widthMaxBtnComboboxSCC);
    comboboxSCcomponents = new QComboBox();
    comboboxSCcomponents->setMaximumWidth(widthMaxBtnComboboxSCC+20);
    comboboxSCcomponents->setModel(model_SCcomponent);
    layoutSCcomponentCretae->addWidget(btnCreateNewSCcomponent);
    layoutSCcomponentCretae->addWidget(comboboxSCcomponents);
    groupBoxSCCcreate->setLayout(layoutSCcomponentCretae);

    groupBoxSCCremoveEdit = new QGroupBox(tr(""), this);
    groupBoxSCCremoveEdit->setMaximumWidth(400);
    QHBoxLayout* layoutSCcomponentRemoveEdit = new QHBoxLayout;
    btnRemoveSCcomponent = new QPushButton(tr("Remove"));
    btnRemoveSCcomponent->setMaximumWidth(widthMaxBtnComboboxSCC);
    btnEditSCcomponent = new QPushButton(tr("Edit"));
    btnEditSCcomponent->setMaximumWidth(widthMaxBtnComboboxSCC);
    layoutSCcomponentRemoveEdit->addWidget(btnRemoveSCcomponent);
    layoutSCcomponentRemoveEdit->addWidget(btnEditSCcomponent);
    groupBoxSCCremoveEdit->setLayout(layoutSCcomponentRemoveEdit);

    layoutBtnComboboxSCc->addWidget(groupBoxSCCremoveEdit);
    layoutBtnComboboxSCc->addWidget(groupBoxSCCcreate);
    groupBoxSCCedit->setLayout(layoutBtnComboboxSCc);

    m_SCcDialogSpacecraftBody = new SpacecraftBodyWidget;
    m_SCcDialogJoint = new SpacecraftJointWidget;
    m_SCcDialogWheel = new SpacecraftWheelWidget;
    m_SCcDialogMTB = new SpacecraftMTBWidget;
    m_SCcDialogThruster = new SpacecraftThrusterWidget;
    m_SCcDialogGyro = new SpacecraftGyroscopeWidget;
    m_SCcDialogMMA = new SpacecraftMMAWidget;
    m_SCcDialogCSS = new SpacecraftCSSWidget;
    m_SCcDialogFSS = new SpacecraftFSSWidget;
    m_SCcDialogST = new SpacecraftStarTrackerWidget;
    m_SCcDialogGPSR = new SpacecraftGPSRWidget;
    m_SCcDialogACCL = new SpacecraftAccelerometerWidget;
}

void SpacecraftDialog::setTabs(){
     SpacecraftTabs = new QTabWidget();
     QWidget* DescriptionTab = new QWidget();  // "DescriptionTab" holds descriptions widgets.
     QWidget* OrbitParameterTab = new QWidget();   // holds orbit parameters
     QWidget* InitialAttitudeTab = new QWidget();  // holds initial attitude data
     QWidget* DynamicsFlagsTab = new QWidget();  // "DynamicsFlagsTab" holds dynamics flag data.
     QWidget* SCcomponentsTab = new QWidget();

     QHBoxLayout *layoutDescriptionTab = new QHBoxLayout;
     QSizePolicy DDLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
     DDLeft.setHorizontalStretch(1);
     groupBoxDetails->setSizePolicy(DDLeft);
     QSizePolicy DDRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
     DDRight.setHorizontalStretch(1);
     groupBoxDescription->setSizePolicy(DDRight);

     layoutDescriptionTab->addWidget(groupBoxDetails);
     layoutDescriptionTab->addWidget(groupBoxDescription);
     DescriptionTab->setLayout(layoutDescriptionTab);

     QHBoxLayout *layoutOrbitParameterTab = new QHBoxLayout;
     layoutOrbitParameterTab->addWidget(groupBoxOrbitParameter);
     layoutOrbitParameterTab->addWidget(new QLabel(tr("For showing the CAD model")));
     OrbitParameterTab->setLayout(layoutOrbitParameterTab);

     QHBoxLayout *layoutInitialAttitudeTab = new QHBoxLayout;
     layoutInitialAttitudeTab->addWidget(groupBoxInitAttitude);
     layoutInitialAttitudeTab->addWidget(new QLabel(tr("For showing the CAD model")));
     InitialAttitudeTab->setLayout(layoutInitialAttitudeTab);

     QHBoxLayout *layoutDynamicsFlagsTab = new QHBoxLayout;
     layoutDynamicsFlagsTab->addWidget(groupBoxDynamicsFlags);
     layoutDynamicsFlagsTab->addWidget(new QLabel());
     DynamicsFlagsTab->setLayout(layoutDynamicsFlagsTab);

     QVBoxLayout *layoutSCcomponentTab = new QVBoxLayout;
     layoutSCcomponentTab->addWidget(groupBoxSCcomponents);
     layoutSCcomponentTab->addWidget(groupBoxSCCedit);
     SCcomponentsTab->setLayout(layoutSCcomponentTab);

     SpacecraftTabs->addTab(DescriptionTab   , tr("Descriptions"));
     SpacecraftTabs->addTab(OrbitParameterTab , tr("Orbit Parameters"));
     SpacecraftTabs->addTab(InitialAttitudeTab, tr("Initial Attitudes"));
     SpacecraftTabs->addTab(DynamicsFlagsTab , tr("Dynamics Flags"));
     SpacecraftTabs->addTab(SCcomponentsTab  , tr("Spacecraft Components"));

}

void SpacecraftDialog::createConnections()
{
    connect(buttonBox, &QDialogButtonBox::accepted,
            this, &SpacecraftDialog::mapDataFromWidgetToModel);
    //connect(buttonBox, &QDialogButtonBox::accepted,
    //         parentTabWidget, [=](){parentTabWidget->removeTab(parentTabWidget->indexOf(this));});
    connect(buttonBox, &QDialogButtonBox::accepted, this, [=](){m_undoStack->clear();});
    connect(buttonBox, &QDialogButtonBox::accepted, this, [=](){m_undoStack->setClean();});
    connect(buttonBox, &QDialogButtonBox::accepted,
            this, [=](){buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, &SpacecraftDialog::mapDataFromWidgetToModel);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, buttonBox->button(QDialogButtonBox::Cancel),
            [=](){buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(buttonBox, &QDialogButtonBox::rejected,
            this, [=](){buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SpacecraftDialog::clearAllCommands);

   //connect(buttonBox, &QDialogButtonBox::rejected,
   //         parentTabWidget, [=](){parentTabWidget->removeTab(parentTabWidget->indexOf(this));});

     /*
      * We have to do this; otherwise even though we reset the data,
      * but press the cancel button to cancel the reset operation,
      * the data in the model will still be resetted. Guess: maybe the "&QDialogButtonBox::rejected"
      * has the same effect ad that of "&QDialogButtonBox::accepted", and it call "mapDataFromWidgetToModel()".
     */
     //connect(buttonBox, &QDialogButtonBox::rejected,
     //        this, [=](){this->mapDataFromModelToWidget();});
     // Comment ends.
    connect(buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked,
             this, [=](){this->resetThroughCommand();});
    connect(buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked,
             this, [=](){buttonBox->button(QDialogButtonBox::Cancel)->setDisabled(false);});
    connect(btnCreateNewSCcomponent, &QPushButton::clicked, buttonBox->button(QDialogButtonBox::Cancel),
             &QDialogButtonBox::setDisabled);
    connect(btnRemoveSCcomponent, &QPushButton::clicked, buttonBox->button(QDialogButtonBox::Cancel),
             &QDialogButtonBox::setDisabled);
    connect(editDescription, &QTextEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLabel, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLabel, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editSPriteFileName, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFSWIdentifier, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFSWSampleTime, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(comboboxOrbitProp, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxReferncePoint, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPosition1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPosition2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPosition3, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editVelocity1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editVelocity2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editVelocity3, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(comboboxAngVelRefernceFrame, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxAtttdSttType, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxAtttdRefFrame, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editAngVel1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAngVel2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAngVel3, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editQuaternion1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editQuaternion2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editQuaternion3, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editQuaternion4, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(editAngle1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAngle2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAngle3, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxEulerSeq, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(comboboxJointRotation, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxMassPropsRef, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDragCoefficient, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(chkbxConstMassProps, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxPJForceTorque, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxCCForceTorque, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxFlexActive, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxInclude2ndFlexTerm, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

bool SpacecraftDialog::clearAllCommands()
{
    /*const int undoCount = m_undoStack->count();
    for (int i = 0; i < undoCount; ++i)
          m_undoAction->trigger();*/
    m_undoAction->trigger();
    return true;
}

void SpacecraftDialog::showAttitudeStateType(const QString& currentText)
{
    QString attitudeStateType = currentText.toUpper();
    QStringList stringList = attitudeStateType.split(" ");
    attitudeStateType.clear();
    for (QString i:stringList)
    {
        attitudeStateType += i;
    }

    if (attitudeStateType == "QUATERNION")
    {
       groupBoxEulerAngle->setEnabled(false);
       groupBoxEulerAngle->setVisible(false);
       groupBoxQuaternion->setEnabled(true);
       groupBoxQuaternion->setVisible(true);
    }

    if (attitudeStateType == "EULERANGLES"){
        groupBoxQuaternion->setEnabled(false);
        groupBoxQuaternion->setVisible(false);
        groupBoxEulerAngle->setEnabled(true);
        groupBoxEulerAngle->setVisible(true);

    }
}

void SpacecraftDialog::setModel(QAbstractItemModel *model)
{
    m_modelMain = model;
}

void SpacecraftDialog::setRootIndex(const QModelIndex &index)
{
    if (m_modelMain && index.model() == m_modelMain){
        buttonBox->button(QDialogButtonBox::Cancel)->setDisabled(true);
        connect(m_modelMain, &QAbstractItemModel::dataChanged,
                this, [=](){this->mapDataFromModelToWidget();});
        m_rootIndex = index;
        mapDataFromModelToWidget();
        qt42delegate = new Qt42Delegate;
        Qt42Model* m_modelMainQt42 = static_cast<Qt42Model*>(m_modelMain);

        tableViewSCcomponents->setModel(m_modelMainQt42);
        tableViewSCcomponents->setRootIndex(m_rootIndex);
        tableViewSCcomponents->setItemDelegate(qt42delegate);


        /*
        btnCreateNewSCcomponent->disconnect(m_modelMainQt42);
        connect(btnCreateNewSCcomponent, &QPushButton::clicked,
                m_modelMainQt42,
                [=](){m_modelMainQt42->createItem(m_rootIndex, map_SCc_StrEnum.value(comboboxSCcomponents->currentText()));
        mapDataFromModelToWidget();});
        */
        btnCreateNewSCcomponent->disconnect(this);
        connect(btnCreateNewSCcomponent, &QPushButton::clicked, this,
                [=](){this->createItemThroughCommand(m_modelMain, m_rootIndex,
                                                     map_SCc_StrEnum.value(comboboxSCcomponents->currentText()));});

        btnRemoveSCcomponent->disconnect(this);
        connect(btnRemoveSCcomponent, &QPushButton::clicked, this,
                [=](){this->removeItemThroughCommand(this->m_modelMain,tableViewSCcomponents->selectionModel()->currentIndex());
        tableViewSCcomponents->selectionModel()->clear();});


        btnEditSCcomponent->disconnect(m_undoAction);
        connect(btnEditSCcomponent, &QPushButton::clicked,
                this, [=](){this->createDialogSCc(m_modelMainQt42, tableViewSCcomponents->selectionModel()->currentIndex());
        tableViewSCcomponents->selectionModel()->clear();});
    }
}

void SpacecraftDialog::createDialogSCc(QAbstractItemModel *model, const QModelIndex &index)
{
    if (!index.isValid())
        return;

    else if (index.data().canConvert<SpacecraftBody>())
    {
        m_SCcDialogSpacecraftBody->setModel(model);
        m_SCcDialogSpacecraftBody->setRootIndex(index);
        m_SCcDialogSpacecraftBody->exec();
        return;
    }

    else if (index.data().canConvert<Joint>())
    {
        m_SCcDialogJoint->setModel(model);
        m_SCcDialogJoint->setRootIndex(index);
        m_SCcDialogJoint->exec();
        return;
    }

    else if (index.data().canConvert<Wheel>())
    {
        m_SCcDialogWheel->setModel(model);
        m_SCcDialogWheel->setRootIndex(index);
        m_SCcDialogWheel->exec();
        return;
    }

    else if (index.data().canConvert<MagTorquer>())
    {
        m_SCcDialogMTB->setModel(model);
        m_SCcDialogMTB->setRootIndex(index);
        m_SCcDialogMTB->exec();
        return;
    }

    else if (index.data().canConvert<Thruster>())
    {
        m_SCcDialogThruster->setModel(model);
        m_SCcDialogThruster->setRootIndex(index);
        m_SCcDialogThruster->exec();
        return;
    }

    else if (index.data().canConvert<GyroAxis>())
    {
        m_SCcDialogGyro->setModel(model);
        m_SCcDialogGyro->setRootIndex(index);
        m_SCcDialogGyro->exec();
        return;
    }

    else if (index.data().canConvert<MagnetometerAxis>())
    {
        m_SCcDialogMMA->setModel(model);
        m_SCcDialogMMA->setRootIndex(index);
        m_SCcDialogMMA->exec();
        return;
    }

    else if (index.data().canConvert<CoarseSunSensor>())
    {
        m_SCcDialogCSS->setModel(model);
        m_SCcDialogCSS->setRootIndex(index);
        m_SCcDialogCSS->exec();
        return;
    }

    else if (index.data().canConvert<FineSunSensor>())
    {
        m_SCcDialogFSS->setModel(model);
        m_SCcDialogFSS->setRootIndex(index);
        m_SCcDialogFSS->exec();
        return;
    }

    else if (index.data().canConvert<StarTracker>())
    {
        m_SCcDialogST->setModel(model);
        m_SCcDialogST->setRootIndex(index);
        m_SCcDialogST->exec();
        return;
    }

    else if (index.data().canConvert<GPSReceiver>())
    {
        m_SCcDialogGPSR->setModel(model);
        m_SCcDialogGPSR->setRootIndex(index);
        m_SCcDialogGPSR->exec();
        return;
    }

    else if (index.data().canConvert<Accelerometer>())
    {
        m_SCcDialogACCL->setModel(model);
        m_SCcDialogACCL->setRootIndex(index);
        m_SCcDialogACCL->exec();
    }
    return;
}

bool SpacecraftDialog::removeItemThroughCommand(QAbstractItemModel *model, const QModelIndex& index)
{
    if (!index.isValid())
        return false;


    QString title = QString();
    QString name = QString();
    QMessageBox* msgBox = new QMessageBox;
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    msgBox->setDefaultButton(QMessageBox::No);

    if (index.data().canConvert<SpacecraftBody>())
    {
        SpacecraftBody oldSCB = index.data().value<SpacecraftBody>();
        title = tr("Remove Spacecraft Body");
        name = oldSCB.name();
    }

    else if (index.data().canConvert<Joint>())
    {
        Joint oldJNT = index.data().value<Joint>();
        title = tr("Remove Joint");
        name = oldJNT.name();
    }

    else if (index.data().canConvert<Wheel>())
    {
        Wheel oldWHL = index.data().value<Wheel>();
        title = tr("Remove Wheel");
        name = oldWHL.name();
    }

    else if (index.data().canConvert<MagTorquer>())
    {
        MagTorquer oldMTB = index.data().value<MagTorquer>();
        title = tr("Remove Magnetic Torquer Bar");
        name = oldMTB.name();
    }

    else if (index.data().canConvert<Thruster>())
    {
        Thruster oldTHR = index.data().value<Thruster>();
        title = tr("Remove Thruster");
        name = oldTHR.name();
    }

    else if (index.data().canConvert<GyroAxis>())
    {
        GyroAxis oldGYO = index.data().value<GyroAxis>();
        title = tr("Remove Gyroscope");
        name = oldGYO.name();
    }

    else if (index.data().canConvert<MagnetometerAxis>())
    {
        MagnetometerAxis oldMMA = index.data().value<MagnetometerAxis>();
        title = tr("Remove Magnetometer Axis");
        name = oldMMA.name();
    }

    else if (index.data().canConvert<CoarseSunSensor>())
    {
        CoarseSunSensor oldCSS = index.data().value<CoarseSunSensor>();
        title = tr("Remove Coarse Sun Sensor");
        name = oldCSS.name();
    }

    else if (index.data().canConvert<FineSunSensor>())
    {
        FineSunSensor oldFSS = index.data().value<FineSunSensor>();
        title = tr("Remove Fine Sun Sensor");
        name = oldFSS.name();
    }

    else if (index.data().canConvert<StarTracker>())
    {
        StarTracker oldST = index.data().value<StarTracker>();
        title = tr("Remove Star Tracker");
        name = oldST.name();
    }

    else if (index.data().canConvert<GPSReceiver>())
    {
        GPSReceiver oldGPSR = index.data().value<GPSReceiver>();
        title = tr("Remove GPS Receiver");
        name = oldGPSR.name();
    }

    else if (index.data().canConvert<Accelerometer>())
    {
        Accelerometer oldACCL = index.data().value<Accelerometer>();
        title = tr("Remove Accelerometer");
        name = oldACCL.name();
    }

    msgBox->setWindowTitle(title);
    msgBox->setText(tr("\"") + name + tr("\" will be removed.\nContinue?"));

    QUndoCommand* removeCommand = new RemoveCommand(model, index);
    int ret = msgBox->exec();
    switch (ret) {
    case QMessageBox::Ok:
        m_undoStack->push(removeCommand);
        break;
    case QMessageBox::No:
        break;
    default:
        break;
    }
    return true;
}


bool SpacecraftDialog::createItemThroughCommand(QAbstractItemModel *model,
                                                const QModelIndex& parentIndex,
                                                objectType type)
{
    if (!parentIndex.isValid())
        return false;
    QUndoCommand* createCommand = new CreateCommand(type, model, parentIndex);
    m_undoStack->push(createCommand);
    return true;
}


bool SpacecraftDialog::mapDataFromModelToWidget()
{
    const int precision = 6;
    Spacecraft SCFromModel;
    Mission missionFromModel;

    if (m_modelMain && m_rootIndex.isValid() && m_rootIndex.data().canConvert<Spacecraft>())
    {

        QVariant dataFromModel = m_rootIndex.data();
        SCFromModel = dataFromModel.value<Spacecraft>();
        missionFromModel = m_rootIndex.parent().parent().data().value<Mission>();
        labelDialogMissionSpacecraft->setText(tr("Mission: ") + missionFromModel.name() +
                                              tr("        ") +
                                              tr("Spacecraft: ") + SCFromModel.name());
        labelDialogMissionSpacecraft->setStyleSheet("QLabel { color : white; }");

        chkbxIncluded->setChecked(SCFromModel.includedInCalculation());
        editSC_Name->setText(SCFromModel.name());
        editMissionName->setText(missionFromModel.name());
        editSC_Directory->setText(missionFromModel.directory());
        editDescription->setText(SCFromModel.description());

        editLabel->setText(SCFromModel.label());
        editSPriteFileName->setText(SCFromModel.spriteFileName());
        editFSWIdentifier->setText(SCFromModel.FSIdentifier());
        editFSWSampleTime->setText(QString::number(SCFromModel.FSWSampleTime() ,'f', precision));

/** Tab: Orbit Parameters/ Initial Attitudes **/
        comboboxOrbitProp->setCurrentText(map_orbitalPara.value(SCFromModel.orbitProp()));
        comboboxReferncePoint->setCurrentText(map_orbitalPara.value(SCFromModel.referncePoint()));
        editPosition1->setText(QString::number(SCFromModel.position()[0],'f', precision));
        editPosition2->setText(QString::number(SCFromModel.position()[1],'f', precision));
        editPosition3->setText(QString::number(SCFromModel.position()[2],'f', precision));
        editVelocity1->setText(QString::number(SCFromModel.velocity()[0],'f',precision));
        editVelocity2->setText(QString::number(SCFromModel.velocity()[1],'f',precision));
        editVelocity3->setText(QString::number(SCFromModel.velocity()[2],'f',precision));
        comboboxAngVelRefernceFrame ->setCurrentText(map_RefernceFrame.value(SCFromModel.angularVelReferece()));
        comboboxAtttdSttType->setCurrentText(map_AttitudeType.value(SCFromModel.attitudeType()));
        comboboxAtttdRefFrame->setCurrentText(map_RefernceFrame.value(SCFromModel.attitudeWithReference()));

        editAngVel1->setText(QString::number(SCFromModel.initialAngVel()[0] ,'f', precision));
        editAngVel2->setText(QString::number(SCFromModel.initialAngVel()[1] ,'f', precision));
        editAngVel3->setText(QString::number(SCFromModel.initialAngVel()[2] ,'f', precision));
        editQuaternion1->setText(QString::number(SCFromModel.initialAngleQuaternion()[0] , 'f', precision));
        editQuaternion2->setText(QString::number(SCFromModel.initialAngleQuaternion()[1] , 'f', precision));
        editQuaternion3->setText(QString::number(SCFromModel.initialAngleQuaternion()[2] , 'f', precision));
        editQuaternion4->setText(QString::number(SCFromModel.initialAngleQuaternion()[3] , 'f', precision));
        editAngle1->setText(QString::number(SCFromModel.initialAngleDegree()[0] ,'f', precision));
        editAngle2->setText(QString::number(SCFromModel.initialAngleDegree()[1] ,'f', precision));
        editAngle3->setText(QString::number(SCFromModel.initialAngleDegree()[2] ,'f', precision));
        comboboxEulerSeq->setCurrentText(SCFromModel.initialAngleEulerSeq());

/** Tab: Dynamic Flags **/
        comboboxJointRotation->setCurrentText(map_jointRotation.value(SCFromModel.jointRotation()));
        comboboxMassPropsRef->setCurrentText(map_massPropRef.value(SCFromModel.refMassProps()));
        editDragCoefficient->setText(QString::number(SCFromModel.dragCoefficient() ,'f', precision));
        chkbxConstMassProps->setChecked(SCFromModel.constMassProp());
        chkbxPJForceTorque->setChecked(SCFromModel.passiveJointForceTorqueEnabled());
        chkbxCCForceTorque->setChecked(SCFromModel.constraintForceTorqueComputing());
        chkbxFlexActive->setChecked(SCFromModel.flexActiveEnabled());
        chkbxInclude2ndFlexTerm->setChecked(SCFromModel.include2ndorderflexActive());

        return true;
    }
    return false;
}

bool SpacecraftDialog::mapDataFromWidgetToModel()
{
    if (m_modelMain && m_rootIndex.isValid() && m_rootIndex.data().canConvert<Spacecraft>())
    {

        //QVariant dataFromModel = m_rootIndex.data();
        //Spacecraft SCFromModel = dataFromModel.value<Spacecraft>();

        QVariant dataFromWidget = QVariant();
        Spacecraft SCFromWidget;

        SCFromWidget = m_rootIndex.data().value<Spacecraft>();
        // Copies the old orbit to the new one, then modifies the new spacecraft from widget.

        SCFromWidget.edit(editDescription->toPlainText(),
                          editLabel->text(),
                          editSPriteFileName->text(),
                          editFSWIdentifier->text(),
                          editFSWSampleTime->text().toDouble(),
                          map_orbitalPara.value(comboboxOrbitProp->currentText()),
                          map_orbitalPara.value(comboboxReferncePoint->currentText()),
        {editPosition1->text().toDouble(), editPosition2->text().toDouble(), editPosition3->text().toDouble()},
        {editVelocity1->text().toDouble(), editVelocity2->text().toDouble(), editVelocity3->text().toDouble()},
                          map_RefernceFrame.value(comboboxAngVelRefernceFrame->currentText()),
                          map_AttitudeType.value(comboboxAtttdSttType->currentText()),
                          map_RefernceFrame.value(comboboxAtttdRefFrame->currentText()),
        {editAngVel1->text().toDouble(), editAngVel2->text().toDouble(), editAngVel3->text().toDouble()},
        {editQuaternion1->text().toDouble(), editQuaternion2->text().toDouble(), editQuaternion3->text().toDouble(),editQuaternion4->text().toDouble()},
        {editAngle1->text().toDouble(), editAngle2->text().toDouble(), editAngle3->text().toDouble()},
                          comboboxEulerSeq->currentText(),
                          map_jointRotation.value(comboboxJointRotation->currentText()),
                          map_massPropRef.value(comboboxMassPropsRef->currentText()),
                          chkbxConstMassProps->isChecked(),
                          chkbxPJForceTorque->isChecked(),
                          chkbxCCForceTorque->isChecked(),
                          chkbxFlexActive->isChecked(),
                          chkbxInclude2ndFlexTerm->isChecked(),
                          editDragCoefficient->text().toDouble(),
                          chkbxIncluded->isChecked());
        QVariant newData = QVariant();
        newData.setValue(SCFromWidget);

        //m_modelMain->setData(m_rootIndex, newData, Qt::EditRole);
        QUndoCommand* editCommand = new EditCommand(m_modelMain, m_rootIndex, newData);
        m_undoStack->push(editCommand);
        return true;
    }
    return false;
}

bool SpacecraftDialog::resetThroughCommand()
{
    //model42->resetData(m_rootIndex);
    //tableViewSCcomponents->viewport()->update();

    Qt42Model* model42 = static_cast<Qt42Model*>(m_modelMain);
    Spacecraft SC = m_rootIndex.data().value<Spacecraft>();

    m_undoStack->beginMacro(tr("Reset Spacecraft"));
    if (SC.numberOfRow() > 0)
    {
        int numberOfRow = SC.numberOfRow();
        for (int row = numberOfRow-1; row > -1; --row)
        {
            int numberOfColumn = SC.numberOfComponentByRow(row);
            for (int column = numberOfColumn-1; column > -1; --column)
            {
                QModelIndex index = model42->index(row, column, m_rootIndex);
                QUndoCommand* removeCommand = new RemoveCommand(model42, index);
                m_undoStack->push(removeCommand);
            }
        }
    }
    QUndoCommand* resetCommand = new ResetCommand(m_modelMain, m_rootIndex);
    m_undoStack->push(resetCommand);
    m_undoStack->endMacro();

    return true;
}

