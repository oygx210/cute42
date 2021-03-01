#include "WidgetHeaders/referenceorbitdialog.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "DataHeaders/mission.h"
#include "DataHeaders/orbittype.h"
#include "DataHeaders/qt42_headers.h"
#include "ShareHeaders/qt42commands.h"
#include <QUndoStack>
#include <QStringListModel>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QStringListModel>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QScrollArea>
#include <QPushButton>
#include <QAction>



ReferenceOrbitDialog::ReferenceOrbitDialog(QWidget* parent): QDialog (parent)
{
    if (parent)
        parentTabWidget = static_cast<QTabWidget*>(parent);
    m_undoStack = new QUndoStack(this);
    createActions();
    setUpModels();
    setTabs();
    mainLayout = new QVBoxLayout();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Save   |
                                                       QDialogButtonBox::Apply  |
                                                       QDialogButtonBox::Cancel |
                                                       QDialogButtonBox::Reset);
    labelDialogMissionOrbit = new QLabel;
    mainLayout->addWidget(labelDialogMissionOrbit);
    mainLayout->addWidget(RefOrbitTabs);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(*pal);
    //QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    //setSizePolicy(sizePolicy);
    setMinimumWidth(900);
    createConnections();


}

ReferenceOrbitDialog::~ReferenceOrbitDialog()
{

}

void ReferenceOrbitDialog::moveToFirstPage() const
{
    RefOrbitTabs->setCurrentIndex(0);
}

void ReferenceOrbitDialog::setUpModels()
{
    m_modelFormationFrameFixedIn = new QStringListModel(list_ReferenceFrame, this);
    m_modelFormationFrameOriginIn = new QStringListModel(list_ReferenceFrame, this);
    m_modelEulerSeq = new QStringListModel(list_EulerSeq, this);
    m_modelRegions = new QStringListModel(list_regions, this);
    /** "model_regions" is the model for "region" parameters in orbit type "FLIGHT"
    and file "Inp_Region.txt". **/   
    m_modelOrbitCentralOrbitCenter_World = new QStringListModel(list_orbitCenter_World);
    m_modelOrbitCentralKEP_PA_AE = new QStringListModel(list_OrbitCentralKEP_PA_AE, this);
    m_modelOrbitCentral_KEP_RV_FILE = new QStringListModel(list_OrbitCentral_KEP_RV_FILE, this);
    m_modelOrbitCentral_TLE_TRV = new QStringListModel(list_OrbitCentral_TLE_TRV, this);
    m_modelOrbit3BodyLagrangeSystem = new QStringListModel(list_Orbit3BodyLagrangeSystem, this);
    // in "42defines.h" , these are defined: EARTHMOON as 0, SUNEARTH as 1 SUNJUPITER as 2.
    m_modelOrbit3BodyLagrangeDOF = new QStringListModel(list_Orbit3BodyLagrangeDOF, this);
    m_modelOrbit3BodyInitializing = new QStringListModel(list_Orbit3BodyInitializing, this);
    m_modelOrbit3BodyLibrationPoint = new QStringListModel(list_Orbit3BodyLibrationPoint, this);
    m_modelOrbit3BodySensePositiveZview = new QStringListModel(list_Orbit3BodySense, this);
    m_modelOrbit3BodySensePositiveZviewL4L5Only = new QStringListModel(
                list_Orbit3BodySense, this);
    m_modelOrbit3Body_TLE_TRV_SPLINE = new QStringListModel(list_Orbit3Body_TLE_TRV_SPLINE, this);
    m_modelOrbitType = new QStringListModel(list_OrbitType, this);
}

void ReferenceOrbitDialog::setModel(QAbstractItemModel *model)
{
    m_modelMain = model;
}

void ReferenceOrbitDialog::setRootIndex(const QModelIndex &index)
{
    if (m_modelMain && index.model() == m_modelMain){
        connect(m_modelMain, &QAbstractItemModel::dataChanged,
                this, [=](){this->mapDataFromModelToWidget();});
        if (m_rootIndex == index)
            return;
        m_rootIndex = index;
        mapDataFromModelToWidget();
    }

}

bool ReferenceOrbitDialog::mapDataFromModelToWidget(bool reset)
{
    const int precision = 6;  // precision definition for QString::number() conversion.
    Orbit orbitFromModel;
    Mission missionFromModel;
    if (m_modelMain && m_rootIndex.isValid() && m_rootIndex.data().canConvert<Orbit>())
    {
        QVariant dataFromModel = m_rootIndex.data();
        orbitFromModel = dataFromModel.value<Orbit>();
        missionFromModel = m_rootIndex.parent().parent().data().value<Mission>();

        editName->setText(orbitFromModel.name());
        editMissionName->setText(orbitFromModel.mission()->name());
        editDirectory->setText(missionFromModel.directory());
        labelDialogMissionOrbit->setText(tr("Mission: ") + missionFromModel.name() +
                                   tr("      ") +
                                   tr("Orbit: ") + orbitFromModel.name());
        labelDialogMissionOrbit->setStyleSheet("QLabel {color : white; }");

        if (reset) // this is for using reset orbit data; mapping data from a empty Orbit object to the widgets.
        {
            Orbit* newOrbit = new Orbit;
            orbitFromModel = *newOrbit;
            delete newOrbit;
        }
        chkbxIncluded->setChecked(orbitFromModel.includedInCalculation());
        comboboxOrbitType->setCurrentText(map_OrbitType.value(orbitFromModel.orbitType(),
                                                              QString()));
        comboboxFormationFrame->setCurrentText(map_RefernceFrame.value(orbitFromModel.formationFrameFixedIn(), QString()));
        editEulerAngle1->setText(QString::number(orbitFromModel.eulerAngles()[0],'f', precision));
        editEulerAngle2->setText(QString::number(orbitFromModel.eulerAngles()[1],'f', precision));
        editEulerAngle3->setText(QString::number(orbitFromModel.eulerAngles()[2],'f', precision));
        comboboxEulerSeq->setCurrentText(orbitFromModel.eulerSequence());
        comboboxFormationOrigin->setCurrentText(map_RefernceFrame.value(orbitFromModel.formationOriginExpressedIn(), QString()));
        editFormationOriginComponent1->setText(QString::number(orbitFromModel.formationOriginRefOrbit()[0],'f', precision));
        editFormationOriginComponent2->setText(QString::number(orbitFromModel.formationOriginRefOrbit()[1],'f', precision));
        editFormationOriginComponent3->setText(QString::number(orbitFromModel.formationOriginRefOrbit()[2],'f', precision));


/** Orbit Type: Zero **/
        comboboxWorld->setCurrentText(orbitCenter_World(orbitFromModel.orbitZero().world().trimmed()));
        chkbxUsePolyhedronGravityZero->setChecked(orbitFromModel.orbitZero().usePolyhedronGravity());

/** Orbit Type: Flight **/
        comboboxRegionNumber->setCurrentText(QString::number(orbitFromModel.orbitFlight().regionNumber()));
        chkbxUsePolyhedronGravityFlight->setChecked(orbitFromModel.orbitFlight().usePolyhedronGravity());

/** Orbit Type: Central **/
        comboboxOrbitCenter->setCurrentText(orbitCenter_World(orbitFromModel.orbitCentral().orbitCenter().trimmed()));
        chkbxSecularOrbitDriftJ2->setChecked(orbitFromModel.orbitCentral().secularOrbitDriftDueToJ2());
        comboboxParameter->setCurrentText(map_OrbitCentral_KEP_RV_FILE.value(orbitFromModel.orbitCentral().orbitDeterminedby()));
        comboboxKEP_PA_AE->setCurrentText(map_OrbitCentralKEP_PA_AE.value(orbitFromModel.orbitCentral().orbitKEPdeterminedby()));
        editPeriapsis->setText(QString::number(orbitFromModel.orbitCentral().periapsisApoapsis()[0],'f', precision));
        editApoapsis->setText(QString::number(orbitFromModel.orbitCentral().periapsisApoapsis()[1],'f', precision));
        editMinALtitude->setText(QString::number(orbitFromModel.orbitCentral().minAltitudeEccentricuty()[0], 'f', precision));
        editECC->setText(QString::number(orbitFromModel.orbitCentral().minAltitudeEccentricuty()[1],'f', precision));
        editInclination->setText(QString::number(orbitFromModel.orbitCentral().inclination(),'f', precision));
        editRightAscensionOfAscendingNode->setText(QString::number(orbitFromModel.orbitCentral().RAAN(),'f', precision));
        editAOP->setText(QString::number(orbitFromModel.orbitCentral().AOP(),'f', precision));
        editTrueAnomaly->setText(QString::number(orbitFromModel.orbitCentral().trueAnomaly(),'f', precision));
        editRVInitialPos1->setText(QString::number(orbitFromModel.orbitCentral().RVInitialPosition()[0],'f', precision));
        editRVInitialPos2->setText(QString::number(orbitFromModel.orbitCentral().RVInitialPosition()[1],'f', precision));
        editRVInitialPos3->setText(QString::number(orbitFromModel.orbitCentral().RVInitialPosition()[2],'f', precision));
        editRVInitialVel1->setText(QString::number(orbitFromModel.orbitCentral().RVInitialVelocity()[0],'f', precision));
        editRVInitialVel2->setText(QString::number(orbitFromModel.orbitCentral().RVInitialVelocity()[1],'f', precision));
        editRVInitialVel3->setText(QString::number(orbitFromModel.orbitCentral().RVInitialVelocity()[2],'f', precision));

        comboboxFormat_Central->setCurrentText(orbitFromModel.orbitCentral().format());
        editLabel_Central->setText(orbitFromModel.orbitCentral().labelInFile());
        editFileName_Central->setText(orbitFromModel.orbitCentral().fileName());

/** Orbit Type: Three-Body **/
        comboboxLagrangeSystem->setCurrentIndex(orbitFromModel.orbit3body().LagrangeSystem());
        comboboxPropagate->setCurrentText(map_Orbit3BodyLagrangeDOF.value(orbitFromModel.orbit3body().propagation()));
        comboboxInitialize->setCurrentText(map_Orbit3BodyInitializing.value(orbitFromModel.orbit3body().initialization()));
        comboboxLibrationPoint->setCurrentIndex(orbitFromModel.orbit3body().LibrationPoint());
        editXYSemiMajorAxis->setText(QString::number(orbitFromModel.orbit3body().XY_SemiMajorAxis(),'f', precision));
        editInitialXYPhase->setText(QString::number(orbitFromModel.orbit3body().initialXYPhase(),'f', precision));
        comboboxSenseFromPositiveZ->setCurrentText(map_Orbit3BodySense.value(orbitFromModel.orbit3body().senseViewedfromZ()));
        edit2ndXYModeSemiMajorAxis->setText(QString::number(orbitFromModel.orbit3body().secondXYModeSemiMajorAxisL4L5only(),'f', precision));
        edit2ndXYModeInitialPhase->setText(QString::number(orbitFromModel.orbit3body().secondXYModeInitialPhaseL4L5only(),'f', precision));
        comboboxSenseFromPositiveZL4L5->setCurrentText(map_Orbit3BodySense.value(orbitFromModel.orbit3body().SenseViewedfromZL4L5only()));
        edit_Z_SemiAxis->setText(QString::number(orbitFromModel.orbit3body().ZSemiAxis(),'f', precision));
        editInitialZPhase->setText(QString::number(orbitFromModel.orbit3body().initialZPhase(),'f', precision));
        editInitialX->setText(QString::number(orbitFromModel.orbit3body().InitialXYZ_NonDimensional()[0],'f', precision));
        editInitialY->setText(QString::number(orbitFromModel.orbit3body().InitialXYZ_NonDimensional()[1],'f', precision));
        editInitialZ->setText(QString::number(orbitFromModel.orbit3body().InitialXYZ_NonDimensional()[2],'f', precision));
        editInitialXdot->setText(QString::number(orbitFromModel.orbit3body().InitialXdotYdotZdot_NonDimensional()[0],'f', precision));
        editInitialYdot->setText(QString::number(orbitFromModel.orbit3body().InitialXdotYdotZdot_NonDimensional()[1],'f', precision));
        editInitialZdot->setText(QString::number(orbitFromModel.orbit3body().InitialXdotYdotZdot_NonDimensional()[2],'f', precision));
        comboboxFormat_3Body->setCurrentText(orbitFromModel.orbit3body().format());
        editLabel_3Body->setText(orbitFromModel.orbit3body().labelInFile());
        editFileName_3Body->setText(orbitFromModel.orbit3body().fileName());

        return true;
    }
    return false;
}

void ReferenceOrbitDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}


void ReferenceOrbitDialog::createConnections()
{
    connect(buttonBox, &QDialogButtonBox::accepted,
            this, &ReferenceOrbitDialog::mapDataFromWidgetToModel);
    connect(buttonBox, &QDialogButtonBox::accepted, buttonBox->button(QDialogButtonBox::Cancel),
            [=](){buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);
    //connect(buttonBox, &QDialogButtonBox::accepted,
    //        parentTabWidget, [=](){parentTabWidget->removeTab(parentTabWidget->indexOf(this));});
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, &ReferenceOrbitDialog::mapDataFromWidgetToModel);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setDisabled(true);});
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, buttonBox->button(QDialogButtonBox::Cancel),
            [=](){buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    //connect(buttonBox, &QDialogButtonBox::rejected,
    //        parentTabWidget, [=](){parentTabWidget->removeTab(parentTabWidget->indexOf(this));});
    connect(buttonBox, &QDialogButtonBox::rejected, buttonBox->button(QDialogButtonBox::Cancel),
            [=](){buttonBox->button(QDialogButtonBox::Cancel)->setDisabled(true);});
    connect(buttonBox, &QDialogButtonBox::rejected, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(buttonBox, &QDialogButtonBox::rejected, this, [=](){this->mapDataFromModelToWidget();});
    /*
     * We have to do this; otherwise even though we reset the data,
     * but press the cancel button to cancel the reset operation,
     * the data in the model will still be resetted. Guess: maybe the "&QDialogButtonBox::rejected"
     * has the same effect ad that of "&QDialogButtonBox::accepted", and it call "mapDataFromWidgetToModel()".
    */
    connect(buttonBox, &QDialogButtonBox::rejected,
            this, [=](){this->mapDataFromModelToWidget(false);});
    // Comment ends.
    connect(buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked,
            this, [=](){this->orbitDataReset();});

/** Tab: Formation Frame Parameters **/
    connect(chkbxIncluded, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxOrbitType, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxFormationFrame, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editEulerAngle1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editEulerAngle2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editEulerAngle3, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxEulerSeq, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxFormationOrigin, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFormationOriginComponent1, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFormationOriginComponent2, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFormationOriginComponent3, &QLineEdit::textEdited, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

/** Tab: ZERO **/
    connect(comboboxWorld, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(chkbxUsePolyhedronGravityZero, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

/** Tab: FLIGHT **/
    connect(comboboxRegionNumber, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxUsePolyhedronGravityFlight, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

/** Tab: Body-Centered **/
    connect(comboboxOrbitCenter, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxSecularOrbitDriftJ2, &QCheckBox::stateChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxParameter, &QComboBox::currentTextChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxKEP_PA_AE, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editPeriapsis, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editApoapsis, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMinALtitude, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editECC, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInclination, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRightAscensionOfAscendingNode, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editAOP, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editTrueAnomaly, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxFormat_Central, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLabel_Central, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFileName_Central, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRVInitialPos1, &QLineEdit::textChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRVInitialPos2, &QLineEdit::textChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRVInitialPos3, &QLineEdit::textChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRVInitialVel1, &QLineEdit::textChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRVInitialVel2, &QLineEdit::textChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editRVInitialVel3, &QLineEdit::textChanged,buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

/** Tab: Three-Body **/
    connect(comboboxLagrangeSystem, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPropagate, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxInitialize, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxLibrationPoint, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editXYSemiMajorAxis, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialXYPhase, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxSenseFromPositiveZ, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(edit2ndXYModeSemiMajorAxis, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(edit2ndXYModeInitialPhase, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxSenseFromPositiveZL4L5, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(edit_Z_SemiAxis, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialZPhase, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialX, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialY, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialZ, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialXdot, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialYdot, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editInitialZdot, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxFormat_3Body, &QComboBox::currentTextChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editLabel_3Body, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editFileName_3Body, &QLineEdit::textChanged, buttonBox->button(QDialogButtonBox::Apply),
            [=](){buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

}

bool ReferenceOrbitDialog::mapDataFromWidgetToModel()
{
    if (m_modelMain && m_rootIndex.isValid() && m_rootIndex.data().canConvert<Orbit>())
    {
        QVariant dataFromModel = m_rootIndex.data();
        Orbit orbitFromModel = dataFromModel.value<Orbit>();

        QVariant dataFromWidget = QVariant();
        Orbit orbitFromWidget;

        orbitFromWidget = orbitFromModel; // Copies the old orbit to the new one, then
                                          // modifies the new orbit from widget.

        orbitFromWidget.rename(editName->text());
        orbitFromWidget.mission()->rename(editMissionName->text());
        orbitFromWidget.edit(map_OrbitType.value(comboboxOrbitType->currentText()), "",
                             map_RefernceFrame.value(comboboxFormationFrame->currentText()),
                             {editEulerAngle1->text().toDouble(), editEulerAngle2->text().toDouble(), editEulerAngle3->text().toDouble()},
                             comboboxEulerSeq->currentText(),
                             map_RefernceFrame.value(comboboxFormationOrigin->currentText()),
                             {editFormationOriginComponent1->text().toDouble(),
                              editFormationOriginComponent2->text().toDouble(),
                              editFormationOriginComponent3->text().toDouble()},
                             chkbxIncluded->isChecked());


/** Orbit Type: Zero **/
        orbitFromWidget.orbitZeroEdit(orbitCenter_World(comboboxWorld->currentText().trimmed()),
                                      chkbxUsePolyhedronGravityZero->isChecked(),
                                      comboboxOrbitType->currentText() == "Zero");

/** Orbit Type: Flight **/
        orbitFromWidget.orbitFlightEdit(comboboxRegionNumber->currentText().toInt(),
                                        chkbxUsePolyhedronGravityFlight->isChecked(),
                                        comboboxOrbitType->currentText() == "Flight");

/** Orbit Type: Central **/
        orbitFromWidget.orbitCentralEdit(orbitCenter_World(comboboxOrbitCenter->currentText()),
                                        chkbxSecularOrbitDriftJ2->isChecked(),
                                        map_OrbitCentral_KEP_RV_FILE.value(comboboxParameter->currentText()),
                                        map_OrbitCentralKEP_PA_AE.value(comboboxKEP_PA_AE->currentText()),
                                        {editPeriapsis->text().toDouble(), editApoapsis->text().toDouble()},
                                        {editMinALtitude->text().toDouble(), editECC->text().toDouble()},
                                        editInclination->text().toDouble(),
                                        editRightAscensionOfAscendingNode->text().toDouble(),
                                        editAOP->text().toDouble(), editTrueAnomaly->text().toDouble(),
                                        {editRVInitialPos1->text().toDouble(), editRVInitialPos2->text().toDouble(), editRVInitialPos3->text().toDouble()},
                                        {editRVInitialVel1->text().toDouble(), editRVInitialVel2->text().toDouble(), editRVInitialVel3->text().toDouble()},
                                        comboboxFormat_Central->currentText(), editLabel_Central->text(),
                                        editFileName_Central->text(),
                                        comboboxOrbitType->currentText() == "Body-Centered");


/** Orbit Type: Three-Body **/
        orbitFromWidget.orbit3bodyEdit(comboboxLagrangeSystem->currentIndex(),
                                      map_Orbit3BodyLagrangeDOF.value(comboboxPropagate->currentText()),
                                      map_Orbit3BodyInitializing.value(comboboxInitialize->currentText()),
                                      comboboxLagrangeSystem->currentIndex(),
                                      editXYSemiMajorAxis->text().toDouble(),
                                      editInitialXYPhase->text().toDouble(),
                                      map_Orbit3BodySense.value(comboboxSenseFromPositiveZ->currentText()),
                                      edit2ndXYModeSemiMajorAxis->text().toDouble(),
                                      edit2ndXYModeInitialPhase->text().toDouble(),
                                      map_Orbit3BodySense.value(comboboxSenseFromPositiveZL4L5->currentText()),
                                      edit_Z_SemiAxis->text().toDouble(),
                                      editInitialZPhase->text().toDouble(),
                                      {editInitialX->text().toDouble(), editInitialY->text().toDouble(), editInitialZ->text().toDouble()},
                                      {editInitialXdot->text().toDouble(), editInitialYdot->text().toDouble(), editInitialZdot->text().toDouble()},
                                      comboboxFormat_3Body->currentText(),
                                      editLabel_3Body->text(),
                                      editFileName_3Body->text(),
                                      comboboxOrbitType->currentText() == "Three-Body");

        QVariant newData = QVariant();
        newData.setValue(orbitFromWidget);
        QUndoCommand* editCommand = new EditCommand(m_modelMain, m_rootIndex, newData);
        m_undoStack->push(editCommand);
        return true;
    }
    return false;
}


bool ReferenceOrbitDialog::orbitDataReset()
{
    bool reset = true;
    mapDataFromModelToWidget(reset);
    return true;
   // mapDataFromWidgetToModel();
}

void ReferenceOrbitDialog::buildGroupBoxOrbitZERO()
{
    /** Orbit Type: ZERO **/
    QGridLayout* layoutOrbitZERO = new QGridLayout;
    //groupBoxOrbitZERO = new QGroupBox(tr("Orbit Type: Zero"), this);
    groupBoxOrbitZERO = new QGroupBox(tr(""),this);
    labelWorld = new QLabel(tr("World"),groupBoxOrbitZERO);
    comboboxWorld = new QComboBox(groupBoxOrbitZERO);
    comboboxWorld->setModel(m_modelOrbitCentralOrbitCenter_World);
    comboboxWorld->setCurrentIndex(3);
    chkbxUsePolyhedronGravityZero = new QCheckBox(tr("Use Polyhedron Gravity"),
                                                  groupBoxOrbitZERO);

    layoutOrbitZERO->addWidget(labelWorld , 0, 0, 1, 1);
    layoutOrbitZERO->addWidget(comboboxWorld, 0 ,1, 1, 3);
    layoutOrbitZERO->addWidget(chkbxUsePolyhedronGravityZero,1, 0, 1, 4);
    groupBoxOrbitZERO->setLayout(layoutOrbitZERO);
    groupBoxOrbitZERO->setMaximumHeight(240);
    groupBoxOrbitZERO->setContentsMargins(30,30,30,30);
}

void ReferenceOrbitDialog::buildGroupBoxOrbitFLIGHT()
{
    /** Orbit Type: FLIGHT **/
    QGridLayout* layoutOrbitFLIGHT = new QGridLayout;
    //groupBoxOrbitFLIGHT = new QGroupBox(tr("Orbit Type: Flight"), this);
    groupBoxOrbitFLIGHT = new QGroupBox(tr(""), this);
    labelRegionNumber = new QLabel(tr("Region Number"), groupBoxOrbitFLIGHT);
    comboboxRegionNumber = new QComboBox(groupBoxOrbitFLIGHT);
    chkbxUsePolyhedronGravityFlight = new QCheckBox(tr("Use Polyhedron Gravity"),
                                                    groupBoxOrbitFLIGHT);
    layoutOrbitFLIGHT->addWidget(labelRegionNumber, 0,0,1,1);
    layoutOrbitFLIGHT->addWidget(comboboxRegionNumber, 0,1,1,2);
    layoutOrbitFLIGHT->addWidget(chkbxUsePolyhedronGravityFlight,1,0,1,4);
    groupBoxOrbitFLIGHT->setLayout(layoutOrbitFLIGHT);
    groupBoxOrbitFLIGHT->setMaximumHeight(240);
    groupBoxOrbitFLIGHT->setContentsMargins(30,30,30,30);
}

void ReferenceOrbitDialog::buildGroupBoxOrbitCENTRAL()
{
    /** Orbit Type: CENTRAL **/
    const int orbitCENTRAL_editMaxWidth = 180;
    QSizePolicy sizePolicyMinimum (QSizePolicy::Minimum, QSizePolicy::Minimum);
    labelOrbitCenter = new QLabel(tr("Orbit Center"));
    comboboxOrbitCenter = new QComboBox();
    comboboxOrbitCenter->setModel(m_modelOrbitCentralOrbitCenter_World);
    comboboxOrbitCenter->setMaximumWidth(190);
    chkbxSecularOrbitDriftJ2 = new QCheckBox(tr("Secular Orbit Drift Due to J2"));
    labelCentralOrbitParameterSet = new QLabel(tr("Central Orbit Parameter Set"));
    comboboxParameter = new QComboBox();
    comboboxParameter->setMaximumWidth(190);
    comboboxParameter->setModel(m_modelOrbitCentral_KEP_RV_FILE);
    connect(comboboxParameter, &QComboBox::currentTextChanged, this, &ReferenceOrbitDialog::OrbitCentralSet_KEP_RV_FILE);
    /* This item could be Keplerian ("KEP"), initial position/velocity ("RV") or "FILE" */

    /*********************  KEP GroupBox *******************/
    groupBoxKEP = new QGroupBox(tr("Keplerian elements"));
    groupBoxKEP->setAlignment(Qt::AlignCenter);
    groupBoxKEP->setMinimumSize(450,300);
    //groupBoxFILE = new QGroupBox(tr("File"), groupBoxOrbitCENTRAL);
    QGridLayout* layoutKEP = new QGridLayout;

    labelKEP_PA_AE = new QLabel(tr("Keplerian Elements Set"));
    comboboxKEP_PA_AE = new QComboBox();
    comboboxKEP_PA_AE->setModel(m_modelOrbitCentralKEP_PA_AE);
    // Use Peri/Apoapsis (PA) or min alt/ecc (AE)

    QFormLayout* layoutKEP_PA = new QFormLayout;
    groupBoxPA = new QGroupBox(tr("Peri/Apoapsis Settings"));
    groupBoxPA->setMaximumHeight(100);
    labelPeriapsis = new QLabel(tr("Periapsis (km)"));
    editPeriapsis = new QLineEdit();
    editPeriapsis->setValidator(new QDoubleValidator);
    editPeriapsis->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelApoapsis = new QLabel(tr("Apoapsis (km)"));
    editApoapsis = new QLineEdit();
    editApoapsis->setValidator(new QDoubleValidator);
    editApoapsis->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    layoutKEP_PA->addRow(labelPeriapsis, editPeriapsis);
    layoutKEP_PA->addRow(labelApoapsis, editApoapsis);
    layoutKEP_PA->setAlignment(Qt::AlignVCenter);
    //layoutKEP_PA->setContentsMargins(30,18,30,3);
    groupBoxPA->setLayout(layoutKEP_PA);

    QFormLayout* layoutKEP_AE = new QFormLayout;
    groupBoxAE = new QGroupBox(tr("Min Altitude (km), Eccentricity"));
    groupBoxAE->setMaximumHeight(100);
    labelMinAltitude = new QLabel(tr("Min Altitude (km)"));
    editMinALtitude = new QLineEdit();
    editMinALtitude->setValidator(new QDoubleValidator);
    editMinALtitude->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelECC= new QLabel(tr("Eccentricity"));
    editECC = new QLineEdit();
    editECC->setValidator(new QDoubleValidator);
    editECC->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    layoutKEP_AE->addRow(labelMinAltitude, editMinALtitude);
    layoutKEP_AE->addRow(labelECC, editECC);
    layoutKEP_AE->setAlignment(Qt::AlignVCenter);
    //layoutKEP_AE->setContentsMargins(30,18,30,3);
    groupBoxAE->setLayout(layoutKEP_AE);

    connect(comboboxKEP_PA_AE, &QComboBox::currentTextChanged, this,
             &ReferenceOrbitDialog::OrbitCentralKEP_parammeterSet);

    labelInclination = new QLabel(tr("Inclination (deg)"));
    editInclination = new QLineEdit();
    editInclination->setValidator(new QDoubleValidator);
    editInclination->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelRightAscensionOfAscendingNode = new QLabel(tr("Right Ascension of\nAscending Node (deg)"));
    editRightAscensionOfAscendingNode = new QLineEdit();
    editRightAscensionOfAscendingNode->setValidator(new QDoubleValidator);
    editRightAscensionOfAscendingNode->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelAOP = new QLabel(tr("Argument of Periapsis\n(deg)"));
    editAOP = new QLineEdit();
    editAOP->setValidator(new QDoubleValidator);
    editAOP->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelTrueAnomaly = new QLabel(tr("True Anomaly (deg)"));
    editTrueAnomaly = new QLineEdit();
    editTrueAnomaly->setValidator(new QDoubleValidator);
    editTrueAnomaly->setMaximumWidth(orbitCENTRAL_editMaxWidth);

    layoutKEP->addWidget(labelKEP_PA_AE   , 0, 0, 1, 1);
    layoutKEP->addWidget(comboboxKEP_PA_AE, 0, 1, 1, 3);
    layoutKEP->addWidget(groupBoxPA, 1, 0, 1, 4);
    layoutKEP->addWidget(groupBoxAE, 1, 0, 1, 4);
    layoutKEP->addWidget(labelInclination , 3, 0, 1, 1);
    layoutKEP->addWidget(editInclination  , 3, 1, 1, 3);
    layoutKEP->addWidget(labelRightAscensionOfAscendingNode, 4, 0, 1, 1);
    layoutKEP->addWidget(editRightAscensionOfAscendingNode , 4, 1, 1, 3);
    layoutKEP->addWidget(labelAOP , 5, 0, 1, 1);
    layoutKEP->addWidget(editAOP  , 5, 1, 1, 3);
    layoutKEP->addWidget(labelTrueAnomaly , 6, 0, 1, 1);
    layoutKEP->addWidget(editTrueAnomaly  , 6, 1, 1, 3);
    OrbitCentralKEP_parammeterSet(comboboxKEP_PA_AE->currentText());
    groupBoxKEP->setLayout(layoutKEP);


    /****************** RV GroupBox *********************/
    QHBoxLayout* layoutRV = new QHBoxLayout;
    groupBoxRV = new QGroupBox(tr("Initial Position/Velocity")); // RV Initial Position (km)

    QFormLayout* layoutRVInitialPos = new QFormLayout;
    layoutRVInitialPos->setSpacing(25);
    groupBoxRVInitialPos = new QGroupBox(tr("Initial Position (km)"));
    groupBoxRVInitialPos->setMaximumHeight(180);
    labelRVInitialPos1 = new QLabel(tr("x1"));
    editRVInitialPos1  = new QLineEdit();
    editRVInitialPos1->setValidator(new QDoubleValidator);
    editRVInitialPos1->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelRVInitialPos2 = new QLabel(tr("x2"));
    editRVInitialPos2  = new QLineEdit();
    editRVInitialPos2->setValidator(new QDoubleValidator);
    editRVInitialPos2->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelRVInitialPos3 = new QLabel(tr("x3"));
    editRVInitialPos3  = new QLineEdit();
    editRVInitialPos3->setValidator(new QDoubleValidator);
    editRVInitialPos3->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    layoutRVInitialPos->addRow(labelRVInitialPos1, editRVInitialPos1);
    layoutRVInitialPos->addRow(labelRVInitialPos2, editRVInitialPos2);
    layoutRVInitialPos->addRow(labelRVInitialPos3, editRVInitialPos3);
    groupBoxRVInitialPos->setLayout(layoutRVInitialPos);
    groupBoxRVInitialPos->setSizePolicy(sizePolicyMinimum);

    QFormLayout* layoutRVInitialVel = new QFormLayout;
    layoutRVInitialVel->setSpacing(25);
    groupBoxRVInitialVel = new QGroupBox(tr("Initial Velocity (km/sec)"));  // RV Initial Velocity (km/sec)
    groupBoxRVInitialVel->setMaximumHeight(180);
    labelRVInitialVel1 = new QLabel(tr("v1"));
    editRVInitialVel1 = new QLineEdit();
    editRVInitialVel1->setValidator(new QDoubleValidator);
    editRVInitialVel1->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelRVInitialVel2 = new QLabel(tr("v2"));
    editRVInitialVel2 = new QLineEdit();
    editRVInitialVel2->setValidator(new QDoubleValidator);
    editRVInitialVel2->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelRVInitialVel3 = new QLabel(tr("v3"));
    editRVInitialVel3 = new QLineEdit();
    editRVInitialVel3->setValidator(new QDoubleValidator);
    editRVInitialVel3->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    layoutRVInitialVel->addRow(labelRVInitialVel1, editRVInitialVel1);
    layoutRVInitialVel->addRow(labelRVInitialVel2, editRVInitialVel2);
    layoutRVInitialVel->addRow(labelRVInitialVel3, editRVInitialVel3);
    groupBoxRVInitialVel->setLayout(layoutRVInitialVel);
    groupBoxRVInitialVel->setSizePolicy(sizePolicyMinimum);

    QFormLayout* layoutTLE_TRV_Central = new QFormLayout;
    groupBoxTLE_TRV_Central = new QGroupBox(tr("TLE or TRV format"));
    labelFormat_Central = new QLabel(tr("Format"));
    comboboxFormat_Central = new QComboBox(); // This item could be "TLE" or "TRV".
    comboboxFormat_Central->setModel(m_modelOrbitCentral_TLE_TRV);
    comboboxFormat_Central->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelLabel_Central = new QLabel(tr("Label to find in file"));
    //editLabel_Central = new QLineEdit(tr("ORB_ID")); // Label to find in file
    editLabel_Central = new QLineEdit();
    editLabel_Central->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    labelFileName_Central = new QLabel(tr("File Name"));
    //editFileName_Central = new QLineEdit(tr("TRV.txt"));  // File name.
    editFileName_Central = new QLineEdit();
    editFileName_Central->setMaximumWidth(orbitCENTRAL_editMaxWidth);
    layoutTLE_TRV_Central->addRow(labelFormat_Central, comboboxFormat_Central);
    layoutTLE_TRV_Central->addRow(labelLabel_Central, editLabel_Central);
    layoutTLE_TRV_Central->addRow(labelFileName_Central, editFileName_Central);
    groupBoxTLE_TRV_Central->setLayout(layoutTLE_TRV_Central);
    groupBoxTLE_TRV_Central->setSizePolicy(sizePolicyMinimum);

    QSizePolicy RVLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    RVLeft.setHorizontalStretch(1);
    groupBoxRVInitialPos->setSizePolicy(RVLeft);
    QSizePolicy RVRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    RVRight.setHorizontalStretch(1);
    groupBoxRVInitialVel->setSizePolicy(RVRight);
    layoutRV->addWidget(groupBoxRVInitialPos);
    layoutRV->addWidget(groupBoxRVInitialVel);
    groupBoxRV->setLayout(layoutRV);
    groupBoxRV->setMaximumHeight(250);
    groupBoxRV->setSizePolicy(sizePolicyMinimum);

    OrbitCentralSet_KEP_RV_FILE(comboboxParameter->currentText());


}

void ReferenceOrbitDialog::OrbitCentralSet_KEP_RV_FILE(const QString& text)
{
  groupBoxKEP -> setEnabled(false);
  groupBoxKEP -> setVisible(false);
  groupBoxRV  -> setEnabled(false);
  groupBoxRV  -> setVisible(false);
  //groupBoxFILE-> setEnabled(false);
  //groupBoxFILE-> setVisible(false);

  if (text == m_modelOrbitCentral_KEP_RV_FILE -> stringList()[0])
  {
      groupBoxKEP -> setEnabled(true);
      groupBoxKEP -> setVisible(true);
  }
  else if (text == m_modelOrbitCentral_KEP_RV_FILE -> stringList()[1])
  {
      groupBoxRV -> setEnabled(true);
      groupBoxRV -> setVisible(true);
  }
  /*
  else if (text == model_OrbitCentral_KEP_RV_FILE -> stringList()[2])
  {
      groupBoxFILE -> setEnabled(true);
      groupBoxFILE -> setVisible(true);
  }
  */
  else {
      return;
  }
}

void ReferenceOrbitDialog::OrbitCentralKEP_parammeterSet(const QString& text)
{
    if (text == m_modelOrbitCentralKEP_PA_AE->stringList()[0])
    {
      groupBoxPA->setEnabled(true);
      groupBoxPA->setVisible(true);
      groupBoxAE->setEnabled(false);
      groupBoxAE->setVisible(false);
    }
    else if (text == m_modelOrbitCentralKEP_PA_AE->stringList()[1])
    {
      groupBoxAE->setEnabled(true);
      groupBoxAE->setVisible(true);
      groupBoxPA->setEnabled(false);
      groupBoxPA->setVisible(false);
    }

}

void ReferenceOrbitDialog::buildGroupBoxOrbitTHREE_BODY()
{
    const int maxWidgetWidth = 150;
    groupBox3bodyPage1Left = new QGroupBox(tr(""));
    groupBox3bodyPage2Left = new QGroupBox(tr(""));

    QFormLayout* Layout3BodyPage1Left = new QFormLayout;
    QGridLayout* Layout3BodyPage2Left = new QGridLayout;
    Layout3BodyPage1Left->setContentsMargins(15,15,15,15);
    Layout3BodyPage1Left->setSpacing(12);
    Layout3BodyPage2Left->setContentsMargins(15,15,15,15);
    Layout3BodyPage2Left->setSpacing(12);


    labelLagrangeSystem = new QLabel(tr("Lagrange System"));
    comboboxLagrangeSystem = new QComboBox();
    comboboxLagrangeSystem->setModel(m_modelOrbit3BodyLagrangeSystem);
    comboboxLagrangeSystem->setMaximumWidth(maxWidgetWidth);
    labelPropagate = new QLabel(tr("Propagation"));
    comboboxPropagate = new QComboBox(); // Propagate using LAGDOF_MODES or LAGDOF_COWELL or LAGDOF_SPLINE
    comboboxPropagate->setModel(m_modelOrbit3BodyLagrangeDOF);
    comboboxPropagate->setMaximumWidth(maxWidgetWidth);
    labelInitialize = new QLabel(tr("Initialization"));
    comboboxInitialize = new QComboBox(); // Initialize with MODES or XYZ or FILE
    comboboxInitialize->setModel(m_modelOrbit3BodyInitializing);
    comboboxInitialize->setMaximumWidth(maxWidgetWidth);
    labelLibrationPoint = new QLabel(tr("Libration Points"));
    comboboxLibrationPoint = new QComboBox();  // Libration point (L1, L2, L3, L4, L5)
    comboboxLibrationPoint->setModel(m_modelOrbit3BodyLibrationPoint);
    comboboxLibrationPoint->setCurrentIndex(1);
    comboboxLibrationPoint->setMaximumWidth(maxWidgetWidth);
    labelXYSemiMajorAxis = new QLabel(tr("XY Semi-major axis (km)"));  // unit: km
    editXYSemiMajorAxis = new QLineEdit();
    editXYSemiMajorAxis->setValidator(new QDoubleValidator);
    editXYSemiMajorAxis->setMaximumWidth(maxWidgetWidth);
    labelInitialXYPhase = new QLabel(tr("Initial XY Phase (deg)")); // unit: degree
    editInitialXYPhase = new QLineEdit();
    editInitialXYPhase->setValidator(new QDoubleValidator);
    editInitialXYPhase->setMaximumWidth(maxWidgetWidth);
    labelSenseFromPositiveZ = new QLabel(tr("Sense (viewed from +Z)"));
    comboboxSenseFromPositiveZ = new QComboBox();  // Sense (CW, CCW), viewed from +Z
    comboboxSenseFromPositiveZ->setModel(m_modelOrbit3BodySensePositiveZview);
    comboboxSenseFromPositiveZ->setMaximumWidth(maxWidgetWidth);
    label2ndXYModeSemiMajorAxis = new QLabel(tr("Second XY Mode Semi-major \nAxis (km) (L4, L5 only)")); // Second XY Mode Semi-major Axis, km (L4, L5 only)
    edit2ndXYModeSemiMajorAxis = new QLineEdit();
    edit2ndXYModeSemiMajorAxis->setValidator(new QDoubleValidator);
    edit2ndXYModeSemiMajorAxis->setMaximumWidth(maxWidgetWidth);
    label2ndXYModeInitialPhase = new QLabel(tr("Second XY Mode Initial Phase \n(deg) (L4, L5 only)")); // Second XY Mode Initial Phase, deg (L4, L5 only)
    edit2ndXYModeInitialPhase = new QLineEdit();
    edit2ndXYModeInitialPhase->setValidator(new QDoubleValidator);
    edit2ndXYModeInitialPhase->setMaximumWidth(maxWidgetWidth);
    labelSenseFromPositiveZL4L5 = new QLabel(tr("Sense viewed from +Z\n(L4, L5 only)"));  // Sense (CW, CCW), viewed from +Z (L4, L5 only)
    comboboxSenseFromPositiveZL4L5 = new QComboBox();
    comboboxSenseFromPositiveZL4L5->setModel(m_modelOrbit3BodySensePositiveZviewL4L5Only);
    comboboxSenseFromPositiveZL4L5->setMaximumWidth(maxWidgetWidth);
    groupBoxZ_SemiAxis_InitialPhase = new QGroupBox(tr(""));
    QFormLayout* layoutZ_SemiAxis_InitialPhase = new QFormLayout;
    layoutZ_SemiAxis_InitialPhase->setSpacing(20);
    label_Z_SemiAxis = new QLabel(tr("Z Semi-axis (km)"));
    edit_Z_SemiAxis = new QLineEdit(groupBoxZ_SemiAxis_InitialPhase);
    edit_Z_SemiAxis->setValidator(new QDoubleValidator());
    edit_Z_SemiAxis->setMaximumWidth(maxWidgetWidth-25);
    labelInitialZPhase = new QLabel(tr("Initial Z Phase (degree)"));
    editInitialZPhase = new QLineEdit();
    editInitialZPhase->setValidator(new QDoubleValidator);
    editInitialZPhase->setMaximumWidth(maxWidgetWidth-25);
    layoutZ_SemiAxis_InitialPhase->addRow(label_Z_SemiAxis, edit_Z_SemiAxis);
    layoutZ_SemiAxis_InitialPhase->addRow(labelInitialZPhase, editInitialZPhase);
    groupBoxZ_SemiAxis_InitialPhase->setLayout(layoutZ_SemiAxis_InitialPhase);
    groupBoxZ_SemiAxis_InitialPhase->setMaximumWidth(360);
    groupBoxZ_SemiAxis_InitialPhase->setMaximumHeight(120);

    Layout3BodyPage1Left->addRow(labelLagrangeSystem         , comboboxLagrangeSystem);
    Layout3BodyPage1Left->addRow(labelPropagate              , comboboxPropagate);
    Layout3BodyPage1Left->addRow(labelInitialize             , comboboxInitialize);
    Layout3BodyPage1Left->addRow(labelLibrationPoint         , comboboxLibrationPoint);
    Layout3BodyPage1Left->addRow(labelXYSemiMajorAxis        , editXYSemiMajorAxis);
    Layout3BodyPage1Left->addRow(labelInitialXYPhase         , editInitialXYPhase);
    Layout3BodyPage1Left->addRow(labelSenseFromPositiveZ     , comboboxSenseFromPositiveZ);
    Layout3BodyPage1Left->addRow(label2ndXYModeSemiMajorAxis , edit2ndXYModeSemiMajorAxis);
    Layout3BodyPage1Left->addRow(label2ndXYModeInitialPhase  , edit2ndXYModeInitialPhase);
    Layout3BodyPage1Left->addRow(labelSenseFromPositiveZL4L5 , comboboxSenseFromPositiveZL4L5);
    groupBox3bodyPage1Left->setLayout(Layout3BodyPage1Left);
    groupBox3bodyPage1Left->setMaximumWidth(430);
    groupBox3bodyPage1Left->setMaximumHeight(470);

    const int maxWidgetWidthInitialXYZandXYZdot = 160;
    groupBoxInitialXYZ = new QGroupBox(tr("Initial X Y Z (Non-dimensional)"));
    QFormLayout* layoutInitialXYZ = new QFormLayout;
    layoutInitialXYZ->setSpacing(15);
    labelInitialX = new QLabel(tr("X"));
    editInitialX = new QLineEdit();
    editInitialX->setValidator(new QDoubleValidator);
    editInitialX->setMaximumWidth(maxWidgetWidthInitialXYZandXYZdot);
    labelInitialY = new QLabel(tr("Y"));
    editInitialY = new QLineEdit();
    editInitialY->setValidator(new QDoubleValidator);
    editInitialY->setMaximumWidth(maxWidgetWidthInitialXYZandXYZdot);
    labelInitialZ = new QLabel(tr("Z"));
    editInitialZ = new QLineEdit();
    editInitialZ->setValidator(new QDoubleValidator);
    editInitialZ->setMaximumWidth(maxWidgetWidthInitialXYZandXYZdot);
    layoutInitialXYZ->addRow(labelInitialX, editInitialX);
    layoutInitialXYZ->addRow(labelInitialY, editInitialY);
    layoutInitialXYZ->addRow(labelInitialZ, editInitialZ);
    groupBoxInitialXYZ->setLayout(layoutInitialXYZ);
    groupBoxInitialXYZ->setMaximumHeight(180);
    groupBoxInitialXYZ->setMaximumWidth(250);

    groupBoxInitialXYZdot = new QGroupBox(QString("Initial ")
                                          + QString::fromUtf8("\u1E8A") + QString(" ")
                                          + QString::fromUtf8("\u1E8E") + QString(" ")
                                          + QString::fromUtf8("\u017B") + QString(" (Non-dimensional)")
                                          , groupBox3bodyPage2Left);  // Initial Xdot, Ydot, Zdot

    QFormLayout* layoutInitialXYZdot = new QFormLayout;
    layoutInitialXYZdot->setSpacing(15);
    labelInitialXdot = new QLabel(QString::fromUtf8("\u1E8A"));
    editInitialXdot  = new QLineEdit();
    editInitialXdot -> setValidator(new QDoubleValidator);
    editInitialXdot -> setMaximumWidth(maxWidgetWidthInitialXYZandXYZdot);
    labelInitialYdot = new QLabel(QString::fromUtf8("\u1E8E"));
    editInitialYdot  = new QLineEdit();
    editInitialYdot -> setValidator(new QDoubleValidator);
    editInitialYdot -> setMaximumWidth(maxWidgetWidthInitialXYZandXYZdot);
    labelInitialZdot = new QLabel(QString::fromUtf8("\u017B"));
    editInitialZdot  = new QLineEdit();
    editInitialZdot -> setValidator(new QDoubleValidator);
    editInitialZdot -> setMaximumWidth(maxWidgetWidthInitialXYZandXYZdot);
    layoutInitialXYZdot->addRow(labelInitialXdot, editInitialXdot);
    layoutInitialXYZdot->addRow(labelInitialYdot, editInitialYdot);
    layoutInitialXYZdot->addRow(labelInitialZdot, editInitialZdot);
    groupBoxInitialXYZdot->setLayout(layoutInitialXYZdot);
    groupBoxInitialXYZdot->setMaximumHeight(180);
    groupBoxInitialXYZdot->setMaximumWidth(250);

    groupBoxTLE_TRV_SPLINE_3Body = new QGroupBox(tr("TLE, TRV or SPLINE format"));
    QFormLayout* layoutTLE_TRV_SPLINE_3Body = new QFormLayout;
    labelFormat_3Body    = new QLabel(tr("Format"));
    comboboxFormat_3Body = new QComboBox(); // This item could be "TLE" or "TRV".
    comboboxFormat_3Body -> setModel(m_modelOrbit3Body_TLE_TRV_SPLINE);
    comboboxFormat_3Body -> setMaximumWidth(maxWidgetWidth-22);
    labelLabel_3Body     = new QLabel(tr("Label"));
    editLabel_3Body      = new QLineEdit(); // Label to find in file
    editLabel_3Body -> setMaximumWidth(maxWidgetWidth-22);
    labelFileName_3Body  = new QLabel(tr("File Name"));
    editFileName_3Body   = new QLineEdit();  // File name.
    editFileName_3Body -> setMaximumWidth(maxWidgetWidth-22);
    layoutTLE_TRV_SPLINE_3Body->addRow(labelFormat_3Body, comboboxFormat_3Body);
    layoutTLE_TRV_SPLINE_3Body->addRow(labelLabel_3Body, editLabel_3Body);
    layoutTLE_TRV_SPLINE_3Body->addRow(labelFileName_3Body, editFileName_3Body);
    groupBoxTLE_TRV_SPLINE_3Body->setLayout(layoutTLE_TRV_SPLINE_3Body);
    groupBoxTLE_TRV_SPLINE_3Body->setMaximumHeight(150);
    groupBoxTLE_TRV_SPLINE_3Body->setMaximumWidth(270);

    Layout3BodyPage2Left->addWidget(groupBoxInitialXYZ    , 0, 0, 1, 2);
    Layout3BodyPage2Left->addWidget(groupBoxInitialXYZdot , 1, 0, 1, 2);
    Layout3BodyPage2Left->setAlignment(Qt::AlignHCenter);
    groupBox3bodyPage2Left->setLayout(Layout3BodyPage2Left);
    groupBox3bodyPage2Left->setMaximumWidth(400);

}

void ReferenceOrbitDialog::buildTabOrbitTypeZero()
{
    buildGroupBoxOrbitZERO();
    TabOrbitTypeZero = new QWidget();
    QHBoxLayout* layoutOrbitTypeZero = new QHBoxLayout;
    layoutOrbitTypeZero->addWidget(groupBoxOrbitZERO);
    layoutOrbitTypeZero->addWidget(new QLabel(tr("Left blank")));
    layoutOrbitTypeZero->setContentsMargins(50,100,50,100);
    layoutOrbitTypeZero->setSpacing(50);
    TabOrbitTypeZero->setLayout(layoutOrbitTypeZero);
}

void ReferenceOrbitDialog::buildTabOrbitTypeFlight()
{
    buildGroupBoxOrbitFLIGHT();
    TabOrbitTypeFlight = new QWidget();
    QHBoxLayout* layoutOrbitTypeFlight = new QHBoxLayout;
    layoutOrbitTypeFlight->addWidget(groupBoxOrbitFLIGHT);
    layoutOrbitTypeFlight->addWidget(new QLabel(tr("Left blank")));
    //layoutOrbitTypeFlight->setAlignment(Qt::AlignVCenter);
    layoutOrbitTypeFlight->setContentsMargins(50,100,50,100);
    layoutOrbitTypeFlight->setSpacing(50);
    TabOrbitTypeFlight->setLayout(layoutOrbitTypeFlight);
}


void ReferenceOrbitDialog::buildTabOrbitTypeCentral()
{
    buildGroupBoxOrbitCENTRAL();
    TabOrbitTypeCentral = new QTabWidget(this);
    OrbitTypeCentralBodyPage1 = new QWidget(TabOrbitTypeCentral);
    OrbitTypeCentralBodyPage2 = new QWidget(TabOrbitTypeCentral);
    QHBoxLayout* layoutCentralBodyPage1 = new QHBoxLayout;
    QHBoxLayout* layoutCentralBodyPage2 = new QHBoxLayout;
    QFormLayout* layoutCentralBodyPage1_Left = new QFormLayout;
    QFormLayout* layoutCentralBodyPage1_Right = new QFormLayout;
    QGridLayout* layoutCentralBodyPage2_Left = new QGridLayout;
    QFormLayout* layoutCentralBodyPage2_Right = new QFormLayout;

    layoutCentralBodyPage1_Left->addRow(labelOrbitCenter, comboboxOrbitCenter);
    layoutCentralBodyPage1_Left->addRow(chkbxSecularOrbitDriftJ2);
    layoutCentralBodyPage1_Left->addRow(groupBoxTLE_TRV_Central);
    layoutCentralBodyPage1->addLayout(layoutCentralBodyPage1_Left);
    layoutCentralBodyPage1->addLayout(layoutCentralBodyPage1_Right);

    layoutCentralBodyPage2_Left->addWidget(labelCentralOrbitParameterSet, 0, 0, 1, 1);
    layoutCentralBodyPage2_Left->addWidget(comboboxParameter, 0, 1, 1, 1);
    layoutCentralBodyPage2_Left->addWidget(groupBoxKEP, 1, 0, 2, 2);
    layoutCentralBodyPage2_Left->addWidget(groupBoxRV,  1, 0, 2 ,2);
    layoutCentralBodyPage2->addLayout(layoutCentralBodyPage2_Left);
    layoutCentralBodyPage2->addLayout(layoutCentralBodyPage2_Right);

    layoutCentralBodyPage1->setStretch(0,1);
    layoutCentralBodyPage1->setStretch(1,1);
    layoutCentralBodyPage2->setStretch(0,1);
    layoutCentralBodyPage2->setStretch(1,1);

    OrbitTypeCentralBodyPage1->setLayout(layoutCentralBodyPage1);
    OrbitTypeCentralBodyPage2->setLayout(layoutCentralBodyPage2);
    TabOrbitTypeCentral->addTab(OrbitTypeCentralBodyPage1, tr("Details/TLE or TRV format"));
    TabOrbitTypeCentral->addTab(OrbitTypeCentralBodyPage2, tr("Parameter Settings"));

    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Window, Qt::gray);
    TabOrbitTypeCentral->setAutoFillBackground(true);
    TabOrbitTypeCentral->setPalette(*pal);
}


void ReferenceOrbitDialog::buildTabOrbitType3Body()
{
    buildGroupBoxOrbitTHREE_BODY();
    TabOrbitType3Body = new QTabWidget(this);
    OrbitType3BodyPage1 = new QWidget(TabOrbitType3Body);
    OrbitType3BodyPage2 = new QWidget(TabOrbitType3Body);
    QHBoxLayout* layoutOrbitType3BodyPage1 = new QHBoxLayout;
    QVBoxLayout* layoutOrbitType3BodyPage1Left = new QVBoxLayout;
    QVBoxLayout* layoutOrbitType3BodyPage1Right= new QVBoxLayout;
    layoutOrbitType3BodyPage1Left->addWidget(groupBox3bodyPage1Left);
    //layoutOrbitType3BodyPage1Left->setContentsMargins(30,layoutOrbitType3BodyPage1Left->margin(), layoutOrbitType3BodyPage1Left->margin(), layoutOrbitType3BodyPage1Left->margin());
    layoutOrbitType3BodyPage1Right->addWidget(new QLabel(tr("Left blank for OpenGL visualization.")));
    layoutOrbitType3BodyPage1Right->addWidget(groupBoxZ_SemiAxis_InitialPhase);
    layoutOrbitType3BodyPage1->addLayout(layoutOrbitType3BodyPage1Left);
    layoutOrbitType3BodyPage1->addLayout(layoutOrbitType3BodyPage1Right);
    layoutOrbitType3BodyPage1->setSpacing(40);
    layoutOrbitType3BodyPage1->setAlignment(Qt::AlignTop);
    OrbitType3BodyPage1->setLayout(layoutOrbitType3BodyPage1);

    QHBoxLayout* layoutOrbitType3BodyPage2 = new QHBoxLayout;
    QVBoxLayout* layoutOrbitType3BodyPage2Left = new QVBoxLayout;
    QVBoxLayout* layoutOrbitType3BodyPage2Right= new QVBoxLayout;

    layoutOrbitType3BodyPage2Left->addWidget(groupBox3bodyPage2Left);
    layoutOrbitType3BodyPage2Right->addWidget(new QLabel(tr("Left blank for OpenGL visualization.")));
    layoutOrbitType3BodyPage2Right->addWidget(groupBoxTLE_TRV_SPLINE_3Body);
    layoutOrbitType3BodyPage2->addLayout(layoutOrbitType3BodyPage2Left);
    layoutOrbitType3BodyPage2->addLayout(layoutOrbitType3BodyPage2Right);
    layoutOrbitType3BodyPage2->setAlignment(Qt::AlignTop);
    layoutOrbitType3BodyPage2->setSpacing(50);
    layoutOrbitType3BodyPage2->setContentsMargins(50,50,50,50);
    OrbitType3BodyPage2->setLayout(layoutOrbitType3BodyPage2);
    TabOrbitType3Body->addTab(OrbitType3BodyPage1, tr("Lagrange System/ Progagation Settings"));
    TabOrbitType3Body->addTab(OrbitType3BodyPage2, tr("Initial XYZ/")+
                              QString::fromUtf8("\u1E8A")+
                              QString::fromUtf8("\u1E8E")+
                              QString::fromUtf8("\u017B")+tr("/TLE or TRV format"));
    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Window, Qt::gray);
    TabOrbitType3Body->setAutoFillBackground(true);
    TabOrbitType3Body->setPalette(*pal);
}

void ReferenceOrbitDialog::buildTabDetailFormation()
{
    /** Orbit file details **/
    const int editDetailTabMaxWidth = 180;
    groupBoxDetails = new QGroupBox(this);
    QFormLayout* layoutDetails = new QFormLayout;
    layoutDetails->setSpacing(20);
    chkbxIncluded = new QCheckBox(tr("included in the calculation."));
    labelName = new QLabel(tr("Name"));
    editName = new QLineEdit(groupBoxDetails);
    editName->setReadOnly(true);
    editName->setMaximumWidth(editDetailTabMaxWidth);
    labelMissionName = new QLabel(tr("Mission"));
    editMissionName = new QLineEdit(groupBoxDetails);
    editMissionName->setReadOnly(true);
    editMissionName->setMaximumWidth(editDetailTabMaxWidth);
    labelDirectory = new QLabel(tr("Directory"));
    editDirectory = new QLineEdit();
    editDirectory->setReadOnly(true);
    editDirectory->setMaximumWidth(editDetailTabMaxWidth);
    labelOrbitType = new QLabel(tr("Orbit Type"));
    comboboxOrbitType = new QComboBox();
    comboboxOrbitType->setModel(m_modelOrbitType);
    comboboxOrbitType->setMaximumWidth(editDetailTabMaxWidth);
    labelOrbitTypeWarningLine1 = new QLabel(tr("(Warning: only the paramters of the orbit type"));
    labelOrbitTypeWarningLine2 = new QLabel(tr(" you select will be used in the calculation.)"));
    connect(comboboxOrbitType, &QComboBox::currentTextChanged, this, &ReferenceOrbitDialog::OrbitTypeSelect);
    layoutDetails->addRow(chkbxIncluded);
    layoutDetails->addRow(labelName, editName);
    layoutDetails->addRow(labelMissionName, editMissionName);
    layoutDetails->addRow(labelDirectory, editDirectory);
    layoutDetails->addRow(labelOrbitType, comboboxOrbitType);
    layoutDetails->addRow(labelOrbitTypeWarningLine1);
    layoutDetails->addRow(labelOrbitTypeWarningLine2);
    layoutDetails->setContentsMargins(50,40,40,40);
    groupBoxDetails->setLayout(layoutDetails);

    /** Formation Frame Parameters **/

    QGridLayout* mainlayoutFormationFrame = new QGridLayout;
    mainlayoutFormationFrame->setSpacing(20);
    groupBoxFormationFrame = new QGroupBox(this);

    labelFormationFrame = new QLabel(tr("Formation Frame"), groupBoxFormationFrame);   // Formation Frame Fixed in [NL]
    comboboxFormationFrame = new QComboBox(groupBoxFormationFrame);
    comboboxFormationFrame->setModel(m_modelFormationFrameFixedIn);
    comboboxFormationFrame->setMaximumWidth(editDetailTabMaxWidth);
    QFormLayout* layoutEulerAngleSeq = new QFormLayout;
    // Euler Angles (deg) and Sequence
    groupBoxEulerAngleSeq = new QGroupBox(tr("Euler Angles (degree) and Sequence"), groupBoxFormationFrame);
    // Euler angle1; unit: degree
    labelEulerAngle1 = new QLabel(QString::fromUtf8("\u03B8")+QString::number(1), groupBoxEulerAngleSeq);
    editEulerAngle1  = new QLineEdit(groupBoxEulerAngleSeq);
    editEulerAngle1->setValidator(new QDoubleValidator);
    editEulerAngle1->setMaximumWidth(editDetailTabMaxWidth);
    // Euler angle2; unit: degree
    labelEulerAngle2 = new QLabel(QString::fromUtf8("\u03B8")+QString::number(2), groupBoxEulerAngleSeq);
    editEulerAngle2  = new QLineEdit(groupBoxEulerAngleSeq);
    editEulerAngle2->setValidator(new QDoubleValidator);
    editEulerAngle2->setMaximumWidth(editDetailTabMaxWidth);
    // Euler angle3; unit: degree
    labelEulerAngle3 = new QLabel(QString::fromUtf8("\u03B8")+QString::number(3), groupBoxEulerAngleSeq);
    editEulerAngle3  = new QLineEdit(groupBoxEulerAngleSeq);
    editEulerAngle3->setValidator(new QDoubleValidator);
    editEulerAngle3->setMaximumWidth(editDetailTabMaxWidth);
    labelEulerSeq = new QLabel(tr("Euler Sequence"), groupBoxEulerAngleSeq);
    comboboxEulerSeq = new QComboBox(groupBoxEulerAngleSeq);
    comboboxEulerSeq->setModel(m_modelEulerSeq);
    comboboxEulerSeq->setMaximumWidth(editDetailTabMaxWidth);
    layoutEulerAngleSeq->addRow(labelEulerAngle1, editEulerAngle1);
    layoutEulerAngleSeq->addRow(labelEulerAngle2, editEulerAngle2);
    layoutEulerAngleSeq->addRow(labelEulerAngle3, editEulerAngle3);
    layoutEulerAngleSeq->addRow(labelEulerSeq, comboboxEulerSeq);
    layoutEulerAngleSeq->setHorizontalSpacing(15);
    layoutEulerAngleSeq->setContentsMargins(30,20,30,20);
    groupBoxEulerAngleSeq->setLayout(layoutEulerAngleSeq);

    labelFormationOrigin = new QLabel(tr("Formation Origin"), groupBoxFormationFrame);   // Formation Origin expressed in [NL]
    comboboxFormationOrigin = new QComboBox(groupBoxFormationFrame);
    comboboxFormationOrigin->setModel(m_modelFormationFrameOriginIn);
    comboboxFormationOrigin->setMaximumWidth(editDetailTabMaxWidth);
    groupBoxFormationOrigin = new QGroupBox(tr("Formation Origin wrt Ref Orbit (m)"), groupBoxFormationFrame);
    QFormLayout* layoutFormationOriginComponents = new QFormLayout;
    labelFormationOriginComponent1 = new QLabel(tr("x"), groupBoxFormationOrigin);   // Formation Origin wrt Ref Orbit; unit: meter
    editFormationOriginComponent1  = new QLineEdit(groupBoxFormationOrigin);
    editFormationOriginComponent1->setValidator(new QDoubleValidator);
    editFormationOriginComponent1->setMaximumWidth(editDetailTabMaxWidth);
    labelFormationOriginComponent2 = new QLabel(tr("y"), groupBoxFormationOrigin);
    editFormationOriginComponent2  = new QLineEdit(groupBoxFormationOrigin);
    editFormationOriginComponent2->setValidator(new QDoubleValidator);
    editFormationOriginComponent2->setMaximumWidth(editDetailTabMaxWidth);
    labelFormationOriginComponent3 = new QLabel(tr("z"), groupBoxFormationOrigin);
    editFormationOriginComponent3  = new QLineEdit(groupBoxFormationOrigin);
    editFormationOriginComponent3->setValidator(new QDoubleValidator);
    editFormationOriginComponent3->setMaximumWidth(editDetailTabMaxWidth);
    layoutFormationOriginComponents->addRow(labelFormationOriginComponent1, editFormationOriginComponent1);
    layoutFormationOriginComponents->addRow(labelFormationOriginComponent2, editFormationOriginComponent2);
    layoutFormationOriginComponents->addRow(labelFormationOriginComponent3, editFormationOriginComponent3);
    layoutFormationOriginComponents->setHorizontalSpacing(110);
    layoutFormationOriginComponents->setContentsMargins(30,30,30,10);
    groupBoxFormationOrigin->setLayout(layoutFormationOriginComponents);
    groupBoxFormationOrigin->setMaximumHeight(200);

    mainlayoutFormationFrame->addWidget(labelFormationFrame,     0, 0, 1, 1);
    mainlayoutFormationFrame->addWidget(comboboxFormationFrame,  0, 1, 1, 4);
    mainlayoutFormationFrame->addWidget(groupBoxEulerAngleSeq,   1, 0, 4, 5);
    mainlayoutFormationFrame->addWidget(labelFormationOrigin ,   5, 0, 1, 1);
    mainlayoutFormationFrame->addWidget(comboboxFormationOrigin, 5, 1, 1, 4);
    mainlayoutFormationFrame->addWidget(groupBoxFormationOrigin, 6, 0 ,4, 5);

    groupBoxFormationFrame->setLayout(mainlayoutFormationFrame);

    TabDetailFormation = new QWidget(this);
    QHBoxLayout* layoutFormationFrameParameterTab = new QHBoxLayout;
    QSizePolicy DFLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    DFLeft.setHorizontalStretch(1);
    groupBoxDetails->setSizePolicy(DFLeft);
    QSizePolicy DFRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    DFRight.setHorizontalStretch(1);
    groupBoxFormationFrame->setSizePolicy(DFRight);
    layoutFormationFrameParameterTab->addWidget(groupBoxDetails);
    layoutFormationFrameParameterTab->addWidget(groupBoxFormationFrame);
    layoutFormationFrameParameterTab->setSpacing(30);
    TabDetailFormation->setLayout(layoutFormationFrameParameterTab);

}

void ReferenceOrbitDialog::setTabs()
{
   buildTabDetailFormation();
   buildTabOrbitTypeZero();
   buildTabOrbitTypeFlight();
   buildTabOrbitTypeCentral();
   buildTabOrbitType3Body();
   RefOrbitTabs = new QTabWidget(this); 
   RefOrbitTabs->addTab(TabDetailFormation  , tr("Formation Frame Parameters"));
   RefOrbitTabs->addTab(TabOrbitTypeZero    , tr("Orbit Type: Zero"));
   RefOrbitTabs->addTab(TabOrbitTypeFlight  , tr("Orbit Type: Flight"));
   RefOrbitTabs->addTab(TabOrbitTypeCentral , tr("Orbit Type: Body-Centered"));
   RefOrbitTabs->addTab(TabOrbitType3Body   , tr("Orbit Type: Three-Body"));
   OrbitTypeSelect(comboboxOrbitType->currentText());
   //RefOrbitTabs->setCurrentWidget(TabDetailFormation);
}

void ReferenceOrbitDialog::OrbitTypeSelect(const QString& currentText)
{

    RefOrbitTabs->setTabEnabled(1, false);
    RefOrbitTabs->setTabEnabled(2, false);
    RefOrbitTabs->setTabEnabled(3, false);
    RefOrbitTabs->setTabEnabled(4, false);
    if (currentText == m_modelOrbitType->stringList()[0])
    {
        RefOrbitTabs->setTabEnabled(1, true);
        //RefOrbitTabs->setCurrentWidget(TabOrbitTypeZero);
    }
    else if (currentText == m_modelOrbitType->stringList()[1])
    {
        RefOrbitTabs->setTabEnabled(2, true);
        //RefOrbitTabs->setCurrentWidget(TabOrbitTypeFlight);
    }
    else if (currentText == m_modelOrbitType->stringList()[2])
    {
        RefOrbitTabs->setTabEnabled(3, true);
        //RefOrbitTabs->setCurrentWidget(TabOrbitTypeCentral);
    }
    else if (currentText == m_modelOrbitType->stringList()[3])
    {
        RefOrbitTabs->setTabEnabled(4, true);
        //RefOrbitTabs->setCurrentWidget(TabOrbitType3Body);
    }

    else return;
}
