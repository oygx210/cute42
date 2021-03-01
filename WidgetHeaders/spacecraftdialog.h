#ifndef SPACECRAFTDIALOG_H
#define SPACECRAFTDIALOG_H

#include <QDialog>
#include <QVector>
#include <QKeyEvent>
#include <QModelIndex>
#include "ShareHeaders/qt42_sharedparameters.h"
#include "DataHeaders/spacecraft.h"

QT_BEGIN_NAMESPACE
class QTextEdit;
class QLineEdit;
class QLabel;
class QComboBox;
class QGroupBox;
class QButtonGroup;
class QCheckBox;
class QStringListModel;
class QVBoxLayout;
class QButtonGroup;
class QTabWidget;
class QScrollArea;
class QAbstractItemModel;
class QTableView;
class QTreeView;
class QUndoStack;
class Qt42Delegate;
class Spacecraft;
class SpacecraftBodyWidget;
class SpacecraftJointWidget;
class SpacecraftWheelWidget;
class SpacecraftMTBWidget;
class SpacecraftThrusterWidget;
class SpacecraftGyroscopeWidget;
class SpacecraftMMAWidget;
class SpacecraftCSSWidget;
class SpacecraftFSSWidget;
class SpacecraftStarTrackerWidget;
class SpacecraftGPSRWidget;
class SpacecraftAccelerometerWidget;
class QDialogButtonBox;
QT_END_NAMESPACE

class SpacecraftDialog : public QDialog
{
    Q_OBJECT
public:
    SpacecraftDialog(QWidget* parent = nullptr);
    ~SpacecraftDialog () override;
    SpacecraftDialog(const SpacecraftDialog&);
    void setModel(QAbstractItemModel* model);
    void setRootIndex(const QModelIndex& index);
    void moveToFirstPage() const;
    QModelIndex rootIndex() const {return m_rootIndex;}
signals:

private slots:
    void showAttitudeStateType(const QString& currentText);

private:    
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    bool resetThroughCommand();
    bool removeItemThroughCommand(QAbstractItemModel* model, const QModelIndex& index);
    bool createItemThroughCommand(QAbstractItemModel* model, const QModelIndex& index, objectType type);
    bool clearAllCommands();
    /** Models **/
    QModelIndex m_rootIndex = QModelIndex();
    QAbstractItemModel* m_modelMain = nullptr;

    void setUpModels();
    void setWidgets();   // This method declares all the widgets.
    void setTabs();
    void createActions();
    void createDialogSCc(QAbstractItemModel* model = nullptr, const QModelIndex& index = QModelIndex());
    void createConnections();
    SpacecraftBodyWidget* m_SCcDialogSpacecraftBody;
    SpacecraftJointWidget* m_SCcDialogJoint;
    SpacecraftWheelWidget* m_SCcDialogWheel;
    SpacecraftMTBWidget* m_SCcDialogMTB;
    SpacecraftThrusterWidget* m_SCcDialogThruster;
    SpacecraftGyroscopeWidget* m_SCcDialogGyro;
    SpacecraftMMAWidget* m_SCcDialogMMA;
    SpacecraftCSSWidget* m_SCcDialogCSS;
    SpacecraftFSSWidget* m_SCcDialogFSS;
    SpacecraftStarTrackerWidget* m_SCcDialogST;
    SpacecraftGPSRWidget* m_SCcDialogGPSR;
    SpacecraftAccelerometerWidget* m_SCcDialogACCL;

    QDialogButtonBox* buttonBox;
    QVBoxLayout *mainLayout;
    QTabWidget* SpacecraftTabs;

    QLabel* labelDialogMissionSpacecraft;
    /** Spacecraft Editing Details **/
    QTabWidget* parentTabWidget;
    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelSC_Name;
    QLineEdit* editSC_Name;
    QLabel* labelMissionName;
    QLineEdit* editMissionName;
    QLabel* labelSC_Directory;
    QLineEdit* editSC_Directory;

    /** Spacecraft Description Items **/
    QGroupBox* groupBoxDescription;
    QLabel* labelDescription;
    QTextEdit* editDescription;
    QLabel* labelLabel;
    QLineEdit* editLabel;
    QLabel* labelSpriteFileName;
    QLineEdit* editSPriteFileName;
    QLabel* labelFSWIdentifier;    // Flight Software Identifier
    QLineEdit* editFSWIdentifier;
    QLabel* labelFSWSampleTime; //FSW Sample Time, sec
    QLineEdit* editFSWSampleTime;

    /**  Orbit Parameters  **/
    QGroupBox* groupBoxOrbitParameter;
    QLabel* labelOrbitProp;
    QComboBox* comboboxOrbitProp;  // could be FIXED, EULER_HILL, or ENCKE
    QLabel* labelReferncePoint; // could be CM or ORIGIN, wrt F.
    QComboBox* comboboxReferncePoint;  // could be CM or ORIGIN, wrt F.
    QGroupBox* groupBoxPosition;
    QLabel* labelPositionVector;
    QLabel* labelPosition1;
    QLineEdit* editPosition1;
    QLabel* labelPosition2;
    QLineEdit* editPosition2;
    QLabel* labelPosition3;
    QLineEdit* editPosition3;
    QGroupBox* groupBoxVelocity;
    QLabel* labelVelocityVector;
    QLabel* labelVelocity1;
    QLineEdit* editVelocity1;
    QLabel* labelVelocity2;
    QLineEdit* editVelocity2;
    QLabel* labelVelocity3;
    QLineEdit* editVelocity3;

    /** Initial Attitude **/
    QGroupBox* groupBoxInitAttitude;
    QVBoxLayout* layoutInitialAttitude;

    QGroupBox* groupBoxInitAttiFrames;
    QLabel* labelAngVelRefernceFrame;
    QComboBox* comboboxAngVelRefernceFrame;
    // This could be "N" or "L";
    // "N" for inertial frame; "L" for LVLH (Local Vertical Local Horizontal )
    QLabel* labelAtttdSttType;
    QComboBox* comboboxAtttdSttType;   // Attitude State Type; this could be "Q" or "A";
                                       // "Q" for quaternion; "A" for Euler angle.
    QLabel* labelAtttdRefFrame;
    QComboBox* comboboxAtttdRefFrame;  // the reference frame the attitude references to;
                                       // this could be "N", "L" or "F"
                                       // "N" for inertial frame; "L" for LVLH; "F" for formation
    QGroupBox* groupBoxAngVel;
    QLabel* labelAngVel;
    QLabel* labelAngVel1;
    QLineEdit* editAngVel1;
    QLabel* labelAngVel2;
    QLineEdit* editAngVel2;
    QLabel* labelAngVel3;
    QLineEdit* editAngVel3;

    QGroupBox* groupBoxQuaternion;
    QLabel* labelQuaternion;
    QLabel* labelQuaternion1;
    QLineEdit* editQuaternion1;
    QLabel* labelQuaternion2;
    QLineEdit* editQuaternion2;
    QLabel* labelQuaternion3;
    QLineEdit* editQuaternion3;
    QLabel* labelQuaternion4;
    QLineEdit* editQuaternion4;

    QGroupBox* groupBoxEulerAngle;
    QLabel* labelAngle1;
    QLineEdit* editAngle1;
    QLabel* labelAngle2;
    QLineEdit* editAngle2;
    QLabel* labelAngle3;
    QLineEdit* editAngle3;
    QLabel* labelEulerSeq;
    QComboBox* comboboxEulerSeq;

    /** Dynamics Flags **/
    QGroupBox* groupBoxDynamicsFlags;
    QButtonGroup* btnGroupDynamicsFlags;
    QLabel* labelJointRotation;  //Rotation STEADY, KIN_JOINT, or DYN_JOINT
    QComboBox* comboboxJointRotation;
    QLabel* labelMassPropsRef;  // Mass Props referenced to REFPT_CM or REFPT_JOINT
    QComboBox* comboboxMassPropsRef; // This could be REFPT_CM or REFPT_JOINT
    QCheckBox* chkbxConstMassProps;  // Assume constant mass properties
    QCheckBox* chkbxPJForceTorque;   // Passive Joint Forces and Torques Enabled
    QCheckBox* chkbxCCForceTorque;   // Compute Constraint Forces and Torques
    QCheckBox* chkbxFlexActive;      // Flex Active
    QCheckBox* chkbxInclude2ndFlexTerm; //Include 2nd Order Flex Terms
    QLabel* labelDragCoefficient;
    QLineEdit* editDragCoefficient;

    /** Spacecraft Components **/
    QGroupBox* groupBoxSCcomponents;
    QGroupBox* groupBoxSCCedit;
    QGroupBox* groupBoxSCCcreate;
    QGroupBox* groupBoxSCCremoveEdit;
    QPushButton* btnCreateNewSCcomponent;
    QPushButton* btnRemoveSCcomponent;
    QPushButton* btnEditSCcomponent;
    QComboBox* comboboxSCcomponents;
    QTableView* tableViewSCcomponents;
    Qt42Delegate* qt42delegate;
    QTreeView* treeViewSCcomponents;


    /** Models **/   
    QStringListModel* model_OrbitProp;
    QStringListModel* model_ReferncePoint;
    QStringListModel* model_AngVelRefernceFrame;
    QStringListModel* model_AtttdSttType;
    QStringListModel* model_AtttdRefFrame;
    QStringListModel* model_EulerSeq;
    QStringListModel* model_jointRotation;
    QStringListModel* model_massPropRef;
    QStringListModel* model_SCcomponent;

    /** Spacecraft Body Widgets **/
    SpacecraftBodyWidget* SCBWidget0;
    QVector <SpacecraftBodyWidget*> qvectorSCBWidgets;

    void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QDialog::focusNextChild();
        else
            QDialog::keyPressEvent(event);
    }
    // this keyPressEvent handling is for preventing the dialog from being closed by pressing enter key.


    /** Qt Undo Framework **/
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
};

#endif // SPACECRAFTDIALOG_H
