#ifndef REFERENCEORBITDIALOG_H
#define REFERENCEORBITDIALOG_H


#include <QDialog>
#include <QKeyEvent>
#include "ShareHeaders/qt42_sharedparameters.h"
#include "DataHeaders/qt42baseclass.h"

class QTabWidget;
class QGroupBox;
class QLineEdit;
class QLabel;
class QComboBox;
class QTextEdit;
class QCheckBox;
class QStringListModel;
class QVBoxLayout;
class QGridLayout;
class QUndoStack;
class QDialogButtonBox;

class ReferenceOrbitDialog : public QDialog
{
    Q_OBJECT

public:
    ReferenceOrbitDialog(QWidget* parent = nullptr);
    ~ReferenceOrbitDialog () override;
    void setModel(QAbstractItemModel *model);
    void setRootIndex(const QModelIndex &index);
    void moveToFirstPage() const;
    QModelIndex rootIndex() const {return m_rootIndex;}

signals:

private slots:
    void OrbitCentralKEP_parammeterSet(const QString&); // for determining PA or AE to use;
    void OrbitCentralSet_KEP_RV_FILE(const QString&);
    void OrbitTypeSelect(const QString&);

private:
    void setUpModels();
    void setWidgets();    
    void buildGroupBoxOrbitZERO();
    void buildGroupBoxOrbitFLIGHT();
    void buildGroupBoxOrbitCENTRAL();
    void buildGroupBoxOrbitTHREE_BODY();
    void buildTabDetailFormation();
    void buildTabOrbitTypeCentral();
    void buildTabOrbitType3Body();
    void buildTabOrbitTypeZero();
    void buildTabOrbitTypeFlight();
    void setTabs();
    bool mapDataFromModelToWidget(bool reset = false);
    bool mapDataFromWidgetToModel();
    bool orbitDataReset();
    void createActions();
    void createConnections();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* buttonBox;
    QCheckBox* chkbxIncluded;
    QLabel* labelDialogMissionOrbit;
    QTabWidget* parentTabWidget;
    QWidget*    TabDetailFormation;
    QWidget*    TabOrbitTypeZero;
    QWidget*    TabOrbitTypeFlight;
    QTabWidget* TabOrbitTypeCentral;
    QWidget*    OrbitTypeCentralBodyPage1;
    QWidget*    OrbitTypeCentralBodyPage2;
    QTabWidget* TabOrbitType3Body;
    QWidget*    OrbitType3BodyPage1;
    QWidget*    OrbitType3BodyPage2;



    QVBoxLayout* mainLayout;
    QTabWidget* RefOrbitTabs;


    /** Models **/
    QModelIndex m_rootIndex = QModelIndex();
    QAbstractItemModel* m_modelMain = nullptr;

    QStringListModel* m_modelFormationFrameFixedIn;
    QStringListModel* m_modelFormationFrameOriginIn;
    QStringListModel* m_modelEulerSeq;
    QStringListModel* m_modelRegions;    // "model_regions" is the model for "region" parameters in orbit type "FLIGHT"
                                        // and file "Inp_Region.txt"
    QStringListModel* m_modelOrbitCentralOrbitCenter_World;
    QStringListModel* m_modelOrbitCentralKEP_PA_AE;
    QStringListModel* m_modelOrbitCentral_KEP_RV_FILE;
    QStringListModel* m_modelOrbitCentral_TLE_TRV;
    QStringListModel* m_modelOrbit3BodyLagrangeSystem;
    QStringListModel* m_modelOrbit3BodyLagrangeDOF;
    QStringListModel* m_modelOrbit3BodyInitializing;
    QStringListModel* m_modelOrbit3BodyLibrationPoint;
    QStringListModel* m_modelOrbit3BodySensePositiveZview;
    QStringListModel* m_modelOrbit3BodySensePositiveZviewL4L5Only;
    QStringListModel* m_modelOrbit3Body_TLE_TRV_SPLINE;
    QStringListModel* m_modelOrbitType;

    /** Orbit file details **/
    QGroupBox* groupBoxDetails;
    QLabel* labelName;
    QLineEdit* editName;
    QLabel* labelMissionName;
    QLineEdit* editMissionName;
    QLabel* labelDirectory;
    QLineEdit* editDirectory;

    /** Formation Frame Parameters **/
    QGroupBox* groupBoxFormationFrame;
    QLabel* labelFormationFrame;   // Formation Frame Fixed in [NL]
    QComboBox* comboboxFormationFrame;
    QGroupBox* groupBoxEulerAngleSeq;  // Euler Angles (deg) and Sequence
    QLabel* labelEulerAngle1;   // Euler angle1; unit: degree
    QLineEdit* editEulerAngle1;
    QLabel* labelEulerAngle2;   // Euler angle2; unit: degree
    QLineEdit* editEulerAngle2;
    QLabel* labelEulerAngle3;   // Euler angle3; unit: degree
    QLineEdit* editEulerAngle3;
    QLabel* labelEulerSeq;
    QComboBox* comboboxEulerSeq;

    QLabel* labelFormationOrigin;   // Formation Origin expressed in [NL]
    QComboBox* comboboxFormationOrigin;
    QGroupBox* groupBoxFormationOrigin;
    QLabel* labelFormationOriginComponent1;   // Formation Origin wrt Ref Orbit; unit: meter
    QLineEdit* editFormationOriginComponent1;
    QLabel* labelFormationOriginComponent2;
    QLineEdit* editFormationOriginComponent2;
    QLabel* labelFormationOriginComponent3;
    QLineEdit* editFormationOriginComponent3;

   /** Orbit Description File **/
    QLabel* labelOrbitFileDescription;
    QTextEdit* editOrbitFileDescription;
    QLabel* labelOrbitType;
    QComboBox* comboboxOrbitType; // This item could be  ZERO, FLIGHT, CENTRAL, THREE_BODY;
    QLabel* labelOrbitTypeWarningLine1;
    QLabel* labelOrbitTypeWarningLine2;

   /** Orbit Type: ZERO **/
   QGroupBox* groupBoxOrbitZERO;
   QLabel* labelWorld;
   QComboBox* comboboxWorld;
   QCheckBox* chkbxUsePolyhedronGravityZero;

   /** Orbit Type: FLIGHT **/
   QGroupBox* groupBoxOrbitFLIGHT;
   QLabel* labelRegionNumber;
   QComboBox* comboboxRegionNumber;
   QCheckBox* chkbxUsePolyhedronGravityFlight;

   /** Orbit Type: CENTRAL **/   
   QLabel* labelOrbitCenter;
   QComboBox* comboboxOrbitCenter;
   QCheckBox* chkbxSecularOrbitDriftJ2;
   QLabel* labelCentralOrbitParameterSet;
   QComboBox* comboboxParameter;  // This item could be Keplerian ("KEP"), initial position/velocity ("RV")
                                  // or "FILE"
   QGroupBox* groupBoxKEP;
   QGroupBox* groupBoxFILE;
   QLabel* labelKEP_PA_AE; // Use Peri/Apoapsis (PA) or min alt/ecc (AE)
   QComboBox* comboboxKEP_PA_AE;
   QGroupBox* groupBoxPA;
   QLabel* labelPeriapsis;
   QLineEdit* editPeriapsis;
   QLabel* labelApoapsis;
   QLineEdit* editApoapsis;
   QGroupBox* groupBoxAE;
   QLabel* labelMinAltitude;
   QLineEdit* editMinALtitude;
   QLabel* labelECC;
   QLineEdit* editECC;
   QLabel* labelInclination;
   QLineEdit* editInclination;
   QLabel* labelRightAscensionOfAscendingNode;  //Right Ascension of Ascending Node (deg)
   QLineEdit* editRightAscensionOfAscendingNode;
   QLabel* labelAOP; // Argument of Periapsis (deg)
   QLineEdit* editAOP;
   QLabel* labelTrueAnomaly;
   QLineEdit* editTrueAnomaly;

   QGroupBox* groupBoxRV; // RV Initial Position (km)
   QGroupBox* groupBoxRVInitialPos;
   QLabel* labelRVInitialPos1;
   QLineEdit* editRVInitialPos1;
   QLabel* labelRVInitialPos2;
   QLineEdit* editRVInitialPos2;
   QLabel* labelRVInitialPos3;
   QLineEdit* editRVInitialPos3;

   QGroupBox* groupBoxRVInitialVel; // RV Initial Velocity (km/sec)
   QLabel* labelRVInitialVel1;
   QLineEdit* editRVInitialVel1;
   QLabel* labelRVInitialVel2;
   QLineEdit* editRVInitialVel2;
   QLabel* labelRVInitialVel3;
   QLineEdit* editRVInitialVel3;

   QGroupBox* groupBoxTLE_TRV_Central;
   QLabel* labelFormat_Central;
   QComboBox* comboboxFormat_Central; // This item could be "TLE" or "TRV".
   QLabel* labelLabel_Central;
   QLineEdit* editLabel_Central; // Label to find in file
   QLabel* labelFileName_Central;
   QLineEdit* editFileName_Central;  // File name.

   /** Orbit Type: THREE_BODY **/
   QGroupBox* groupBox3bodyPage1Left;
   QGroupBox* groupBox3bodyPage2Left;
   QLabel* labelLagrangeSystem;
   QComboBox* comboboxLagrangeSystem;
   QLabel* labelPropagate;
   QComboBox* comboboxPropagate; // Propagate using LAGDOF_MODES or LAGDOF_COWELL or LAGDOF_SPLINE
   QLabel* labelInitialize;
   QComboBox* comboboxInitialize; // Initialize with MODES or XYZ or FILE
   QLabel* labelLibrationPoint;
   QComboBox* comboboxLibrationPoint;  // Libration point (L1, L2, L3, L4, L5)
   QLabel* labelXYSemiMajorAxis;  // unit: km
   QLineEdit* editXYSemiMajorAxis;
   QLabel* labelInitialXYPhase; // unit: degree
   QLineEdit* editInitialXYPhase;
   QLabel* labelSenseFromPositiveZ;
   QComboBox* comboboxSenseFromPositiveZ;  // Sense (CW, CCW), viewed from +Z
   QLabel* label2ndXYModeSemiMajorAxis; // Second XY Mode Semi-major Axis, km (L4, L5 only)
   QLineEdit* edit2ndXYModeSemiMajorAxis;
   QLabel* label2ndXYModeInitialPhase; // Second XY Mode Initial Phase, deg (L4, L5 only)
   QLineEdit* edit2ndXYModeInitialPhase;
   QLabel* labelSenseFromPositiveZL4L5;   // Sense (CW, CCW), viewed from +Z (L4, L5 only)
   QComboBox* comboboxSenseFromPositiveZL4L5;

   QGroupBox* groupBoxZ_SemiAxis_InitialPhase;
   QLabel* label_Z_SemiAxis;  // Z Semi-axis, km
   QLineEdit* edit_Z_SemiAxis;
   QLabel* labelInitialZPhase;   // Initial Z Phase, degree
   QLineEdit* editInitialZPhase;

   QGroupBox* groupBoxInitialXYZ;  // Initial X, Y, Z (Non-dimensional)
   QLabel* labelInitialX;
   QLineEdit* editInitialX;
   QLabel* labelInitialY;
   QLineEdit* editInitialY;
   QLabel* labelInitialZ;
   QLineEdit* editInitialZ;
   QGroupBox* groupBoxInitialXYZdot;  // Initial Xdot, Ydot, Zdot
   QLabel* labelInitialXdot;
   QLineEdit* editInitialXdot;
   QLabel* labelInitialYdot;
   QLineEdit* editInitialYdot;
   QLabel* labelInitialZdot;
   QLineEdit* editInitialZdot;
   QGroupBox* groupBoxTLE_TRV_SPLINE_3Body;
   QLabel* labelFormat_3Body;
   QComboBox* comboboxFormat_3Body; // This item could be "TLE" or "TRV".
   QLabel* labelLabel_3Body;
   QLineEdit* editLabel_3Body; // Label to find in file
   QLabel* labelFileName_3Body;
   QLineEdit* editFileName_3Body;  // File name.
   void keyPressEvent(QKeyEvent *event) override
   {
       if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
           QDialog::focusNextChild();
       else
           QDialog::keyPressEvent(event);
   }
   // this keyPressEvent handling is for preventing the dialog from being closed by pressing enter key.

};

#endif // REFERENCEORBITDIALOG_H
