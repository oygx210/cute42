#ifndef SCCOMPONENTSWIDGETS_H
#define SCCOMPONENTSWIDGETS_H

#include <QWidget>
#include <QVector>
#include <QKeyEvent>
#include <QDialog>
#include <QModelIndex>
#include <QAction>

class QLabel;
class QLineEdit;
class QGroupBox;
class QPushButton;
class Spacecraft;
class Mission;
class QTreeView;
class QTableView;
class QSplitter;
class QComboBox;
class QCheckBox;
class QDialogButtonBox;
class SpacecraftJointWidget;
class QStringListModel;
class QUndoStack;
class QTabWidget;
class Qt42Model;
class QMessageBox;


class SpacecraftBodyWidget : public QDialog
{
    Q_OBJECT
public:
    explicit SpacecraftBodyWidget(QWidget *parent = nullptr);
    ~SpacecraftBodyWidget() override;
    SpacecraftBodyWidget(const SpacecraftBodyWidget&);
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}
signals:
    void includedStatusChanged();
public slots:

private:
    void createWidgets();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void createActions();

    Mission* mission = nullptr;
    Spacecraft* spacecraft = nullptr;
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QTabWidget* tabWidget;
    QWidget* tabPage1;
    QWidget* tabPage2;

    QDialogButtonBox* m_buttonBox;
    QLabel* labelDisplay;

    QGroupBox* groupboxProperties;
    QGroupBox* groupboxPropertiesContinued;

    QCheckBox* chkbxIncluded;
    QGroupBox* groupBoxSCBodyDetails;
    QPushButton* btnGeometryFile;
    QLineEdit* editGeometryFile;
    QLabel* labelIndex;
    QLineEdit* editIndex;
    QLabel* labelName;
    QLineEdit* editName;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;
    QPushButton* btnFlexFile;
    QLineEdit* editFlexFile;

    QGroupBox* groupBoxMass;
    QLabel* labelMass;
    QLineEdit* editMass;
    QGroupBox* groupBoxMomentInertiaMatrix;
     // unit: kg-m^2
    QLabel* labelMomentInertiaMatrixAxisX_Column;
    QLabel* labelMomentInertiaMatrixAxisX_Row;
    QLabel* labelMomentInertiaMatrixAxisY_Column;
    QLabel* labelMomentInertiaMatrixAxisY_Row;
    QLabel* labelMomentInertiaMatrixAxisZ_Column;
    QLabel* labelMomentInertiaMatrixAxisZ_Row;
    QLineEdit* editMomentInertiaMatrixAxisXX;
    QLineEdit* editMomentInertiaMatrixAxisXY;
    QLineEdit* editMomentInertiaMatrixAxisXZ;
    QLineEdit* editMomentInertiaMatrixAxisYX;
    QLineEdit* editMomentInertiaMatrixAxisYY;
    QLineEdit* editMomentInertiaMatrixAxisYZ;
    QLineEdit* editMomentInertiaMatrixAxisZX;
    QLineEdit* editMomentInertiaMatrixAxisZZ;
    QLineEdit* editMomentInertiaMatrixAxisZY;

    QGroupBox* groupBoxLocMassCenter;
           // location of mass center in meters
    QLabel* labelLocMassCenterX;
    QLabel* labelLocMassCenterY;
    QLabel* labelLocMassCenterZ;
    QLineEdit* editLocMassCenterX;
    QLineEdit* editLocMassCenterY;
    QLineEdit* editLocMassCenterZ;

    QGroupBox* groupBoxConstEmbeddedMomentum;  // constant embedded momentum; units: Nms
    QLabel* labelConstEmbeddedMomentumX;
    QLabel* labelConstEmbeddedMomentumY;
    QLabel* labelConstEmbeddedMomentumZ;
    QLineEdit* editConstEmbeddedMomentumX;
    QLineEdit* editConstEmbeddedMomentumY;
    QLineEdit* editConstEmbeddedMomentumZ;
    QString geometryFileName;                        // the geometry input file name (*.obj)
    QString geometryFileDir;

    void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
private slots:
    void selectDirOBJfile();
};





/** Widget for Joint Data **/

class SpacecraftJointWidget : public QDialog
{
    Q_OBJECT
public:
    explicit SpacecraftJointWidget(QWidget *parent = nullptr);
    ~SpacecraftJointWidget() override;
    SpacecraftJointWidget(const SpacecraftJointWidget&);
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

signals:

public slots:

private slots:
    void renewComboboxBody();
    void enableItemComboboxBody();
private:
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QUndoStack* undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    QMessageBox* msgBox;
    void createWidgets();
    bool checkWhetherCurrentSCB();  // this function checks whether current SC body is included (as a inner or outer body);
    void setupModels();
    void setTabs();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void createActions();
    void createConnections();

    QString m_nameJoint = QString();
    QString m_nameMission = QString();
    QString m_nameSpacecraft = QString();

    QLabel* labelnameMission;
    QLabel* labelnameSpacecraft;
    QDialogButtonBox* buttonBox;

    QTabWidget* parentTabWidget;
    QTabWidget* mainTabWidget;
    QWidget* tabWidget0;
    QWidget* tabWidget1;
    QWidget* tabWidget2;
    QWidget* tabWidget3;
    QWidget* tabWidget4;
    QWidget* tabWidget5;
    QWidget* tabWidget6;
    QWidget* tabWidget7;

    QStringListModel* m_modelEulerSeqRot;
    QStringListModel* m_modelEulerSeqTrn;
    QStringListModel* m_modelGimbalSpherical;
    QStringListModel* m_modelBiGiStaticSeq;
    QStringListModel* m_modelGoBoStaticSeq;

    QLabel* labelJointName;

    QCheckBox* chkbxIncluded;
    QGroupBox* groupBoxBodyIndices;
    QLabel* labelInnerBody;
    QLabel* labelOuterBody;
    QComboBox* comboboxInnerBody;
    QComboBox* comboboxOuterBody;

    QGroupBox* groupBoxRotTrnDOF;
    QLabel* labelRotDOF;
    QLineEdit* editRotDOF;
    QLabel* labelEulerSeqRot;
    QComboBox* comboboxEulerSeqRot;
    QLabel* labelGimbalSpherical;
    QComboBox* comboboxGimbalSpherical;
    QLabel* labelTrnDOF;
    QLineEdit* editTrnDOF;
    QLabel* labelEulerSeqTrn;
    QComboBox* comboboxEulerSeqTrn;

    QGroupBox* groupBoxRotDOFLocked;
    QCheckBox* chkbxRotDOFLocked0;
    QCheckBox* chkbxRotDOFLocked1;
    QCheckBox* chkbxRotDOFLocked2;

    QGroupBox* groupBoxTrnDOFLocked;
    QCheckBox* chkbxTrnDOFLocked0;
    QCheckBox* chkbxTrnDOFLocked1;
    QCheckBox* chkbxTrnDOFLocked2;

    QGroupBox* groupBoxInitialAngles;
    QLabel* labelInitialAngle0;
    QLineEdit* editInitialAngle0;
    QLabel* labelInitialAngle1;
    QLineEdit* editInitialAngle1;
    QLabel* labelInitialAngle2;
    QLineEdit* editInitialAngle2;

    QGroupBox* groupBoxInitialRates;
    QLabel* labelInitialRate0;
    QLineEdit* editInitialRate0;
    QLabel* labelInitialRate1;
    QLineEdit* editInitialRate1;
    QLabel* labelInitialRate2;
    QLineEdit* editInitialRate2;

    QGroupBox* groupBoxInitialDisplacement;
    QLabel* labelInitialDisplacement0;
    QLineEdit* editInitialDisplacement0;
    QLabel* labelInitialDisplacement1;
    QLineEdit* editInitialDisplacement1;
    QLabel* labelInitialDisplacement2;
    QLineEdit* editInitialDisplacement2;

    QGroupBox* groupBoxInitialDisplacementRate;
    QLabel* labelInitialDisplacementRate0;
    QLineEdit* editInitialDisplacementRate0;
    QLabel* labelInitialDisplacementRate1;
    QLineEdit* editInitialDisplacementRate1;
    QLabel* labelInitialDisplacementRate2;
    QLineEdit* editInitialDisplacementRate2;

    QGroupBox* groupBoxBiGiStaticAngleSeq;
    QLabel* labelBiGiStaticAngle0;
    QLineEdit* editBiGiStaticAngle0;
    QLabel* labelBiGiStaticAngle1;
    QLineEdit* editBiGiStaticAngle1;
    QLabel* labelBiGiStaticAngle2;
    QLineEdit* editBiGiStaticAngle2;
    QLabel* labelBiGiStaticSeq;
    QComboBox* comboboxBiGiStaticSeq;

    QGroupBox* groupBoxGoBoStaticAngleSeq;
    QLabel* labelGoBoStaticAngle0;
    QLineEdit* editGoBoStaticAngle0;
    QLabel* labelGoBoStaticAngle1;
    QLineEdit* editGoBoStaticAngle1;
    QLabel* labelGoBoStaticAngle2;
    QLineEdit* editGoBoStaticAngle2;
    QLabel* labelGoBoStaticSeq;
    QComboBox* comboboxGoBoStaticSeq;

    QGroupBox* groupBoxPositionToInnerBodyOrigin;
    QLabel* labelPositionToInnerBodyOrigin0;
    QLineEdit* editPositionToInnerBodyOrigin0;
    QLabel* labelPositionToInnerBodyOrigin1;
    QLineEdit* editPositionToInnerBodyOrigin1;
    QLabel* labelPositionToInnerBodyOrigin2;
    QLineEdit* editPositionToInnerBodyOrigin2;

    QGroupBox* groupBoxPositionToOuterBodyOrigin;
    QLabel* labelPositionToOuterBodyOrigin0;
    QLineEdit* editPositionToOuterBodyOrigin0;
    QLabel* labelPositionToOuterBodyOrigin1;
    QLineEdit* editPositionToOuterBodyOrigin1;
    QLabel* labelPositionToOuterBodyOrigin2;
    QLineEdit* editPositionToOuterBodyOrigin2;

    QGroupBox* groupBoxRotSpring;
    QLabel* labelRotSpring0;
    QLineEdit* editRotSpring0;
    QLabel* labelRotSpring1;
    QLineEdit* editRotSpring1;
    QLabel* labelRotSpring2;
    QLineEdit* editRotSpring2;

    QGroupBox* groupBoxRotDamping;
    QLabel* labelRotDamping0;
    QLineEdit* editRotDamping0;
    QLabel* labelRotDamping1;
    QLineEdit* editRotDamping1;
    QLabel* labelRotDamping2;
    QLineEdit* editRotDamping2;

    QGroupBox* groupBoxTrnSpring;
    QLabel* labelTrnSpring0;
    QLineEdit* editTrnSpring0;
    QLabel* labelTrnSpring1;
    QLineEdit* editTrnSpring1;
    QLabel* labelTrnSpring2;
    QLineEdit* editTrnSpring2;

    QGroupBox* groupBoxTrnDamping;
    QLabel* labelTrnDamping0;
    QLineEdit* editTrnDamping0;
    QLabel* labelTrnDamping1;
    QLineEdit* editTrnDamping1;
    QLabel* labelTrnDamping2;
    QLineEdit* editTrnDamping2;
    QStringList m_qvecBodyInner;
    QStringList m_qvecBodyOuter;

\
    void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};


/** Widget for Wheel Data **/
class SpacecraftWheelWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftWheelWidget(QWidget* parent = nullptr);
    ~SpacecraftWheelWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void normalizeAxisVector();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();

    QDialogButtonBox* m_buttonBox;
    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxProperties;
    QLabel* labelInitialMomentum;
    QLineEdit* editInitialMomentum;
    QGroupBox* groupBoxAxisComponent;
    QLabel* labelWheelAxisComponentX;
    QLineEdit* editWheelAxisComponentX;
    QLabel* labelWheelAxisComponentY;
    QLineEdit* editWheelAxisComponentY;
    QLabel* labelWheelAxisComponentZ;
    QLineEdit* editWheelAxisComponentZ;
    QPushButton* btnNormalize;
    QLabel* labelMaxTorque;
    QLineEdit* editMaxTorque;
    QLabel* labelMaxMomentum;
    QLineEdit* editMaxMomentum;
    QLabel* labelWheelRotorInertia;
    QLineEdit* editWheelRotorInertia;
    QLabel* labelStaticImbalance;
    QLineEdit* editStaticImbalance;
    QLabel* labelDynamicImbalance;
    QLineEdit* editDynamicImbalance;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};

/** Widget for Magnetic Torquer Bar Data **/

class SpacecraftMTBWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftMTBWidget(QWidget* parent = nullptr);
    ~SpacecraftMTBWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void normalizeAxisVector();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();

    QDialogButtonBox* m_buttonBox;
    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxProperties;
    QLabel* labelSaturation;
    QLineEdit* editSaturation;
    QGroupBox* groupBoxMTBAxisComponent;
    QLabel* labelMTBAxisComponentX;
    QLineEdit* editMTBAxisComponentX;
    QLabel* labelMTBAxisComponentY;
    QLineEdit* editMTBAxisComponentY;
    QLabel* labelMTBAxisComponentZ;
    QLineEdit* editMTBAxisComponentZ;
    QPushButton* btnNormalize;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }

};



/** Widget for Thruster data **/
class SpacecraftThrusterWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftThrusterWidget(QWidget* parent = nullptr);
    ~SpacecraftThrusterWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

signals:

private slots:
    void renewCombobox(const QModelIndex& index = QModelIndex());
    void renewGroupBoxBodyIndex(QString bodyName);
private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void normalizeAxisVector();


    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    QDialogButtonBox* m_buttonBox;

    QGroupBox* groupBoxAll;
    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxProperties;

    QLabel* labelThrusterForce;
    QLineEdit* editThrusterForce;
    QLabel* labelBody;
    QComboBox* comboboxBody;

    QGroupBox* groupBoxThrustAxis;
    QLabel* labelThrustAxisX;
    QLineEdit* editThrustAxisX;
    QLabel* labelThrustAxisY;
    QLineEdit* editThrustAxisY;
    QLabel* labelThrustAxisZ;
    QLineEdit* editThrustAxisZ;
    QPushButton* btnNormalize;

    QGroupBox* groupBoxLocationInBody;
    QLabel* labelLocationInBodyX;
    QLineEdit* editLocationInBodyX;
    QLabel* labelLocationInBodyY;
    QLineEdit* editLocationInBodyY;
    QLabel* labelLocationInBodyZ;
    QLineEdit* editLocationInBodyZ;

    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent* event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }

};

/** Widget for GyroAxis data **/
class SpacecraftGyroscopeWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftGyroscopeWidget(QWidget* parent = nullptr);
    ~SpacecraftGyroscopeWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void normalizeAxisComponents();
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    QDialogButtonBox* m_buttonBox;

    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxProperties;
    QLabel* labelSampleTime;
    QLineEdit* editSampleTime;

    QGroupBox* groupBoxAxisInBodyFrame;
    QLabel* labelAxisX;
    QLineEdit* editAxisX;
    QLabel* labelAxisY;
    QLineEdit* editAxisY;
    QLabel* labelAxisZ;
    QLineEdit* editAxisZ;
    QPushButton* btnNormalize;

    QLabel* labelMaxRate;
    QLineEdit* editMaxRate;
    QLabel* labelScaleFactorError;
    QLineEdit* editScaleFactorError;
    QLabel* labelQuantization;
    QLineEdit* editQuantization;
    QLabel* labelAngleRandomWalk;
    QLineEdit* editAngleRandomWalk;
    QLabel* labelBiasStability;
    QLineEdit* editBiasStability;
    QLabel* labelTimeSpan;
    QLineEdit* editTimeSpan;
    QLabel* labelAngleNoise;
    QLineEdit* editAngleNoise;
    QLabel* labelInitialBias;
    QLineEdit* editInitialBias;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};


/** Widget for Magnetometer data **/
class SpacecraftMMAWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftMMAWidget(QWidget* parent = nullptr);
    ~SpacecraftMMAWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void normalizeAxisComponents();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();


    QDialogButtonBox* m_buttonBox;
    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxProperties;

    QLabel* labelSampleTime;
    QLineEdit* editSampleTime;
    QGroupBox* groupBoxAxisInBodyFrame;
    QLabel* labelAxisX;
    QLineEdit* editAxisX;
    QLabel* labelAxisY;
    QLineEdit* editAxisY;
    QLabel* labelAxisZ;
    QLineEdit* editAxisZ;
    QPushButton* btnNormalize;

    QLabel* labelSaturation;
    QLineEdit* editSaturation;
    QLabel* labelScaleFactorError;
    QLineEdit* editScaleFactorError;
    QLabel* labelQuantization;
    QLineEdit* editQuantization;
    QLabel* labelNoise;
    QLineEdit* editNoise;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};

/** Widget for Coarse Sun Sensor **/
class SpacecraftCSSWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftCSSWidget(QWidget* parent = nullptr);
    ~SpacecraftCSSWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private slots:
    void renewComboboxBody();
    void changegroupBoxAxisExpressedInBodyFrameTitle(const QString&);
    void disableChkbxIncludedWhenNoBody();

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void normalizeAxisComponents();

    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;
    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxProperties;
    QLabel* labelSampleTime;
    QLineEdit* editSampleTime;

    QGroupBox* groupBoxAxisExpressedInBodyFrame;
    QLabel* labelBody;
    QComboBox* comboboxBody;
    QLabel* labelAxisX;
    QLineEdit* editAxisX;
    QLabel* labelAxisY;
    QLineEdit* editAxisY;
    QLabel* labelAxisZ;
    QLineEdit* editAxisZ;
    QPushButton* btnNormalize;

    QLabel* labelHalfConeAngle;
    QLineEdit* editHalfConeAngle;
    QLabel* labelScaleFactor;
    QLineEdit* editScaleFactor;
    QLabel* labelQuantization;
    QLineEdit* editQuantization;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};


/** Widget for Fine Sun Sensor Data **/
class SpacecraftFSSWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftFSSWidget(QWidget* parent = nullptr);
    ~SpacecraftFSSWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void normalizeAxisComponents();

    QStringListModel* m_modelMountingAngleSeq;
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;

    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxProperties;
    QLabel* labelSampleTime;
    QLineEdit* editSampleTime;
    QGroupBox* groupBoxMountingAngle;
    QLabel* labelMountingAngle1;
    QLineEdit* editMountingAngle1;
    QLabel* labelMountingAngle2;
    QLineEdit* editMountingAngle2;
    QLabel* labelMountingAngle3;
    QLineEdit* editMountingAngle3;
    QLabel* labelMountingAngleSeqInBody;
    QComboBox* comboboxMountingAngleSeqInBody;

    QGroupBox* groupBoxFOV;
    QLabel* labelFOVSizeX;
    QLineEdit* editFOVSizeX;
    QLabel* labelFOVSizeY;
    QLineEdit* editFOVSizeY;

    QLabel* labelNoiseEquivalentAngle;
    QLineEdit* editNoiseEquivalentAngle;

    QLabel* labelQuantization;
    QLineEdit* editQuantization;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;




    void keyPressEvent(QKeyEvent* event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};



/** Widget for Star Tracker data **/
class SpacecraftStarTrackerWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftStarTrackerWidget(QWidget* parent = nullptr);
    ~SpacecraftStarTrackerWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    QTabWidget* tabWidget;
    QWidget* tabPage1;
    QWidget* tabPage2;
    QStringListModel* m_modelMountingAngleSeq;
    QDialogButtonBox* m_buttonBox;

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    Qt42Model* m_model = nullptr;
    QModelIndex m_index  = QModelIndex();

    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxPropertiesPage1;
    QGroupBox* groupBoxPropertiesPage2;
    QLabel* labelSampleTime;
    QLineEdit* editSampleTime;
    QGroupBox* groupBoxMountingAngles;
    QLabel* labelMountingAngle1;
    QLineEdit* editMountingAngle1;
    QLabel* labelMountingAngle2;
    QLineEdit* editMountingAngle2;
    QLabel* labelMountingAngle3;
    QLineEdit* editMountingAngle3;
    QLabel* labelMountingAngleSeq;
    QComboBox* comboboxMountingAngleSeq;
    QGroupBox* groupBoxFOVsize;
    QLabel* labelFOVsizeX;
    QLineEdit* editFOVsizeX;
    QLabel* labelFOVsizeY;
    QLineEdit* editFOVsizeY;
    QGroupBox* groupBoxSunEarthMoonExclusionAngles;
    QLabel* labelExclusionSun;
    QLineEdit* editExclusionSun;
    QLabel* labelExclusionEarth;
    QLineEdit* editExclusionEarth;
    QLabel* labelExclusionMoon;
    QLineEdit* editExclusionMoon;
    QGroupBox* groupBoxNoiseEquivalentAngles;
    QLabel* labelNoiseEquivalentAngle1;
    QLineEdit* editNoiseEquivalentAngle1;
    QLabel* labelNoiseEquivalentAngle2;
    QLineEdit* editNoiseEquivalentAngle2;
    QLabel* labelNoiseEquivalentAngle3;
    QLineEdit* editNoiseEquivalentAngle3;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};

/** Widget for GPS data **/

class SpacecraftGPSRWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftGPSRWidget(QWidget* parent = nullptr);
    ~SpacecraftGPSRWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();

    QDialogButtonBox* m_buttonBox;
    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxProperties;
    QLabel* labelSampleTime;
    QLineEdit* editSampleTime;
    QLabel* labelPositionNoise;
    QLineEdit* editPositionNoise;
    QLabel* labelVelocityNoise;
    QLineEdit* editVelocityNoise;
    QLabel* labelTimeNoise;
    QLineEdit* editTimeNoise;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};



/** Widget for Accelerometer data **/
class SpacecraftAccelerometerWidget : public QDialog
{
    Q_OBJECT
public:
    SpacecraftAccelerometerWidget(QWidget* parent = nullptr);
    ~SpacecraftAccelerometerWidget() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void normalizeAxisComponents();

    QTabWidget* tabWidget;
    QWidget* tabPage1;
    QWidget* tabPage2;

    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;
    QGroupBox* groupBoxDetails;
    QCheckBox* chkbxIncluded;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelSpacecraft;
    QLineEdit* editSpacecraft;

    QGroupBox* groupBoxPropertiesPage1;
    QGroupBox* groupBoxPropertiesPage2;
    QLabel* labelSampleTime;
    QLineEdit* editSampleTime;
    QGroupBox* groupBoxPositionInBody0;
    QLabel* labelPositionInBody0_X;
    QLineEdit* editPositionInBody0_X;
    QLabel* labelPositionInBody0_Y;
    QLineEdit* editPositionInBody0_Y;
    QLabel* labelPositionInBody0_Z;
    QLineEdit* editPositionInBody0_Z;
    QGroupBox* groupBoxAxisExpressedInBodyFrame;
    QLabel* labelAxisExpressedInBodyFrameX;
    QLineEdit* editAxisExpressedInBodyFrameX;
    QLabel* labelAxisExpressedInBodyFrameY;
    QLineEdit* editAxisExpressedInBodyFrameY;
    QLabel* labelAxisExpressedInBodyFrameZ;
    QLineEdit* editAxisExpressedInBodyFrameZ;
    QPushButton* btnNormalize;
    QLabel* labelMaxAcceleration;
    QLineEdit* editMaxAcceleration;
    QLabel* labelScaleFactorError;
    QLineEdit* editScaleFactorError;
    QLabel* labelQuantization;
    QLineEdit* editQuantization;
    QLabel* labelRandomWalk;
    QLineEdit* editRandomWalk;
    QGroupBox* groupboxBiasStabilityTimespan;
    QLabel* labelBiasStability;
    QLineEdit* editBiasStability;
    QLabel* labelTimeSpan;
    QLineEdit* editTimeSpan;
    QLabel* labelDVNoise;
    QLineEdit* editDVNoise;
    QLabel* labelInitialBias;
    QLineEdit* editInitialBias;
    QLabel* labelFlexNodeIndex;
    QLineEdit* editFlexNodeIndex;

    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }


};




#endif // SCCOMPONENTSWIDGETS_H



