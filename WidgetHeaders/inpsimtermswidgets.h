#ifndef INPSIMTERMSWIDGETS_H
#define INPSIMTERMSWIDGETS_H

#include <QDialog>
#include <QModelIndex>
#include <QKeyEvent>
#include "DataHeaders/inpsimterms.h"
class QGroupBox;
class QLabel;
class QLineEdit;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QPushButton;
class QDialogButtonBox;
class QUndoStack;
class QAction;
class QDateEdit;
class QTimeEdit;
class QCheckBox;
class QAbstractItemModel;
class Qt42Model;
class QTabWidget;
class InpSimEnvironment;
class QStringListModel;
class QTextEdit;
class Qt42DragWidget;

/** Widget for Simulation Control Data **/
class InpSimSimCtrlDialog : public QDialog
{
    Q_OBJECT
public:
    InpSimSimCtrlDialog(QWidget* parent = nullptr);
    ~InpSimSimCtrlDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }

signals:
private slots:
private:
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();

    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;

    QTabWidget* tabWidgetParent;
    QTabWidget* tabWidget;
    QWidget* widgetPage1;
    QWidget* widgetPage2;

    QLabel* labelMissionForDialog;
    QGroupBox* groupboxDetails;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelDirectory;
    QLineEdit* editDirectory;

    QGroupBox* groupboxEdit;
    QLabel* labelTimeMode;
    QComboBox* comboboxTimeMode;
    QLabel* labelSimDuration;
    QDoubleSpinBox* dblSpinboxSimDuration;
    QLabel* labelStepSize;
    QDoubleSpinBox* dblSpinboxStepSize;
    QLabel* labelFileOutputInterval;
    QDoubleSpinBox* dblSpinboxFileOutputInterval;
    QCheckBox* chkbxGraphicsFrontEnd;

    QTextEdit* editSimCommand;
    const double maxSimDuration = 1.0e+12;
};

/** Widget for Orbit-Spacecraft Set Data **/
class InpSimOrbitSCSetDialog : public QDialog
{
    Q_OBJECT
public:
    InpSimOrbitSCSetDialog(QWidget* parent = nullptr);
    ~InpSimOrbitSCSetDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

signals:

private slots:
    void getOrbitsFromSC(const QString& nameSC);
    void addOrbitSCPairs(const QString& orbit);
    void removeOrbitSCPairs(const QString& nameOrbit);
    void clearAllSelectedOrbits();
private:
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    InpSimOrbitSCSet m_inpSimOrbitSCSet = InpSimOrbitSCSet();
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void updateComboboxSC();
    void setAvailableOrbits();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;

    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelNumberOfSets;
    QLineEdit* editNumberOfSets;

    QPushButton* btnAlign;
    QPushButton* btnClearAll;

    QLabel* labelSC;
    QComboBox* comboboxSC;

    QGroupBox* groupboxOrbitDrag;
    Qt42DragWidget* OrbitDragWidget;
    QGroupBox* groupboxOrbitDrop;
    Qt42DragWidget* OrbitDropWidget;

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};


/** Widget for Environment Data **/
class InpSimEnvironmentDialog : public QDialog
{
    Q_OBJECT
public:
    InpSimEnvironmentDialog(QWidget* parent = nullptr);
    ~InpSimEnvironmentDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

signals:
    void IGRFselected(bool);
private slots:
    void IGRFisSelected(const QString& text);
    void enableGroupBoxIGRF(const bool& enable);

private:
    void setupModels();
    void createWidgets();
    void createConnections();
    void createActions();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    QStringListModel* model_SolarFluxAPvalues;
    QStringListModel* model_Magfield;

    QTabWidget* parentTabWidget = nullptr;
    QTabWidget* tabWidget;
    QWidget* widgetPage1;
    QWidget* widgetPage2;

    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;

    QGroupBox* groupboxDetails;
    QLabel* labelMission;
    QLineEdit* editMission;

    QGroupBox* groupboxTime;
    QLabel* labelDate;
    QDateEdit* editDate;

    QLabel* labelGreenwichMeanTime;
    QTimeEdit* editGreenwichMeanTime;

    QLabel* labelTimeOffset;
    QDoubleSpinBox* spinboxTimeOffset;

    QGroupBox* groupboxModelDataInterpolation;
    QLabel* labelModelDataInterpolationForSolarFluxAndAPvalues;
    QComboBox* comboboxModelDataInterpolationForSolarFluxAndAPvalues;  // could be TWOSIGMA_KP, NOMINAL or USER_DEFINED
    QLabel* labelUSER_DEFINED_F10_7;
    QLineEdit* editUSER_DEFINED_F10_7;
    QLabel* labelUSER_DEFINED_AP;
    QLineEdit* editUSER_DEFINED_AP;

    QGroupBox* groupboxMagfield;
    QLabel* labelMagfield;
    QComboBox* comboboxMagfield; // could be NONE, DIPOLE, or IGRF;

    QGroupBox* groupboxIGRF;
    QLabel* labelIGRF_Degree;
    QSpinBox* spinboxIGRF_Degree;
    QLabel* labelIGRF_Order;
    QSpinBox* spinboxIGRF_Order;

    QGroupBox* groupboxGravity;
    QGroupBox* groupboxEarthGravityModelNM;
    QLabel* labelEarthGravityModelN;
    QSpinBox* spinboxEarthGravityModelN;
    QLabel* labelEarthGravityModelM;
    QSpinBox* spinboxEarthGravityModelM;

    QGroupBox* groupboxMarsGravityModelNM;
    QLabel* labelMarsGravityModelN;
    QSpinBox* spinboxMarsGravityModelN;
    QLabel* labelMarsGravityModelM;
    QSpinBox* spinboxMarsGravityModelM;

    QGroupBox* groupboxLunaGravityModelNM;
    QLabel* labelLunaGravityModelN;
    QSpinBox* spinboxLunaGravityModelN;
    QLabel* labelLunaGravityModelM;
    QSpinBox* spinboxLunaGravityModelM;

    QGroupBox* groupBoxForcesTorques;

    QGroupBox* groupboxAerodynamicForcesTorques;
    QCheckBox* chkbxAerodynamicForces;
    QCheckBox* chkbxAerodynamicTorques;

    QCheckBox* chkbxGravityGradientTorques;

    QGroupBox* groupboxSolarPressureForcesTorques;
    QCheckBox* chkbxSolarPressureForces;
    QCheckBox* chkbxSolarPressureTorques;

    QCheckBox* chkbxGravityPerturbationForces;

    QCheckBox* chkbxPassiveJointForcesTorques;
    QCheckBox* chkbxThrusterPlumeForcesTorques;
    QCheckBox* chkbxRWAimbalanceForcesTorques;
    QCheckBox* chkbxContactForcesTorques;
    QCheckBox* chkbxCFDsloshForcesTorques;
    QCheckBox* chkbxOutputEnvironmentalTorquesToFiles;
    void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QDialog::focusNextChild();
        else
            QDialog::keyPressEvent(event);
    }

};


/** Widget for Celestial Bodies **/
class InpSimCelestialBodyDialog : public QDialog
{
    Q_OBJECT
public:
    InpSimCelestialBodyDialog(QWidget* parent = nullptr);
    ~InpSimCelestialBodyDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

signals:


private slots:


private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void setupModels();

    QTabWidget* parentTabWidget = nullptr;
    QStringListModel* model_Ephemerides;
    QAbstractItemModel* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;
    QGroupBox* groupboxDetails;
    QLabel* labelMission;
    QLineEdit* editMission;

    QGroupBox* groupboxCelestialBodies;

    QLabel* labelEphemOption;
    QComboBox* comboboxEphemOption;  // could be MEAN or DE430
    QCheckBox* chkbxMercury;
    QCheckBox* chkbxVenus;
    QCheckBox* chkbxEarthAndLuna;
    QCheckBox* chkbxMarsAndMoons;
    QCheckBox* chkbxJupiterAndMoons;
    QCheckBox* chkbxSaturnAndMoons;
    QCheckBox* chkbxUranusAndMoons;
    QCheckBox* chkbxNeptuneAnsMoons;
    QCheckBox* chkbxPlutoAndMoons;
    QCheckBox* chkbxAsteroidsAndComets;


    void keyPressEvent(QKeyEvent* event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};


/** Widgets for Lagrange Point Systems of Inerest **/

class InpSimLagrangePointSystemsDialog : public QDialog
{
    Q_OBJECT
public:
    InpSimLagrangePointSystemsDialog(QWidget* parent = nullptr);
    ~InpSimLagrangePointSystemsDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();

    QTabWidget* parentTabWidget = nullptr;
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QDialogButtonBox* m_buttonBox;
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QGroupBox* groupboxDetails;
    QLabel* labelMission;
    QLineEdit* editMission;

    QGroupBox* groupboxLagrangeSystems;
    QCheckBox* chkbxEarthMoon;
    QCheckBox* chkbxSunEarth;
    QCheckBox* chkbxSunJupiter;

    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};


/** Widgets for Ground Stations **/

class InpSimGroundStationDialog : public QDialog
{
    Q_OBJECT
public:
    InpSimGroundStationDialog(QWidget* parent = nullptr);
    ~InpSimGroundStationDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}
signals:

private slots:
    void mapDataForSelectedGS(const int& index);
    void tempEdit_GS_Data();
    // "tempEdit_GS_Data()" is called when the Ground Station object data in the widgets is editted;
    void removeGS(bool pseudo = false);

private:
    void setupModels();
    void createWidgets();
    void createActions();
    void createConnecetions();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();
    void resetGS_Widgets();
    void renewComboboxGS();

    QTabWidget* parentTabWidget = nullptr;
    InpSimGroundStation m_isgs;
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;

    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();

    QGroupBox* groupBoxDetails;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelNumberOfGS;
    QLineEdit* editNumberOfGS;

    QGroupBox* groupBoxCreateRemoveGS;
    QComboBox* comboboxGS;
    QPushButton* btnCreateGS;
    QPushButton* btnRemoveGS;

    QGroupBox* groupBoxEditGS;
    QCheckBox* chkbxExist;
    QLabel* labelWorld;
    QComboBox* comboboxWorld;

    QGroupBox* groupBoxLongitudeLatitude;
    QLabel* labelLongitude;
    QDoubleSpinBox* dblSpinBoxLongitude;
    QLabel* labelLatitude;
    QDoubleSpinBox* dblSpinBoxLatitude;
    QLabel* labelLabel;
    QLineEdit* editLabel;
    QPushButton* btnOK;

    QStringList m_listGS;

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }

};


#endif // INPSIMTERMSWIDGETS_H
