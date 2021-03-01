#ifndef GRAPHICSDIALOG_H
#define GRAPHICSDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QKeyEvent>
#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/spacecraft.h"

class QAbstractItemModel;
class QLabel;
class QDoubleSpinBox;
class QPushButton;
class QLineEdit;
class QCheckBox;
class QGroupBox;
class QComboBox;
class QSpinBox;
class QAction;
class QUndoStack;
class QDialogButtonBox;
class QTabWidget;

class Qt42Model;

class GraphicsDialog : public QDialog
{
    Q_OBJECT
public:
    GraphicsDialog(QWidget* parent = nullptr);
    ~GraphicsDialog() override;
    GraphicsDialog(const GraphicsDialog& gd);
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }

signals:

private slots:
    void mapDataFromModelToWidget();
    void mapDataFromWidgetToModel();
    void updateInitalHostSCB(Spacecraft& sc);
    void updateInitalTargetSCB(Spacecraft& sc);
    void enableDisablePOVScScb();
private:
    void createWidgets();
    void createActions();
    void createConnections();

    QDialogButtonBox* m_buttonBox;

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;


    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    GraphicsHeader m_graphicsHeader = GraphicsHeader();

    QTabWidget* tabWidget;
    QWidget* widgetPage1;
    QWidget* widgetPage2;
    QWidget* widgetPage3;

    QLabel* labelMission;

    QGroupBox* groupboxConfiguration;
    QLabel* labelGLOuputInterval;
    QDoubleSpinBox* dblSpinboxGLOuputInterval;
    QPushButton* btnStarCatalogFileName;
    QLineEdit* editStarCatalogFileName;
    QCheckBox* chkbxMapWindowExists;
    QCheckBox* chkbxOrreyWindowExists;
    QCheckBox* chkbxUnitSphereWindowExists;

    QGroupBox* groupboxPOV;
    QCheckBox* chkbxPauseAtStartup;
    QLabel* labelPOVMode;
    QComboBox* comboboxPOVMode;

    QGroupBox* groupboxPOVInitialHost;
    QLabel* labelHostType;
    QComboBox* comboboxHostType;
    QLabel* labelPOVInitialHostSC;
    QComboBox* comboboxPOVInitialHostSC;
    QLabel* labelPOVInitialHostSCB;
    QComboBox* comboboxPOVInitialHostSCB;
    QLabel* labelPOVInitialHostPOVFrame;
    QComboBox* comboboxPOVInitialHostPOVFrame;

    QGroupBox* groupboxPOVInitialTarget;
    QLabel* labelTargetType;
    QComboBox* comboboxTargetType;
    QLabel* labelPOVInitialTargetSC;
    QComboBox* comboboxPOVInitialTargetSC;
    QLabel* labelPOVInitialTargetSCB;
    QComboBox* comboboxPOVInitialTargetSCB;
    QLabel* labelPOVInitialTargetPOVFrame;
    QComboBox* comboboxPOVInitialTargetPOVFrame;
    QLabel* labelBoresightAxis;
    QComboBox* comboboxBoresightAxis;
    QLabel* labelUpAxis;
    QComboBox* comboboxUpAxis;
    QLabel* labelInitialPOVRangeFromTarget;
    QDoubleSpinBox* dblSpinboxInitialPOVRangeFromTarget;
    QLabel* labelPOVAngleVertical;
    QDoubleSpinBox* dblSpinboxPOVAngleVertical;
    QGroupBox* groupboxPOVPositionHost;
    QLabel* labelPOVPositionHostX1;
    QDoubleSpinBox* dblSpinboxPOVPositionHostX1;
    QLabel* labelPOVPositionHostX2;
    QDoubleSpinBox* dblSpinboxPOVPositionHostX2;
    QLabel* labelPOVPositionHostX3;
    QDoubleSpinBox* dblSpinboxPOVPositionHostX3;
    QLabel* labelInitialPOVView;
    QComboBox* comboboxInitialPOVView;

    QGroupBox* groupboxCAM;
    QLabel* labelCamTitle;
    QLineEdit* editCamTitle;
    QGroupBox* groupboxCAMWidthHeight;
    QLabel* labelCAMWidth;
    QSpinBox* spinboxCAMWidth;
    QLabel* labelCAMHeight;
    QSpinBox* spinboxCAMHeight;
    QLabel* labelMouseScaleFactor;
    QDoubleSpinBox* dblSpinboxMouseScaleFactor;
    QLabel* labelDisplayGammaExponent;
    QDoubleSpinBox* dblSpinboxDisplayGammaExponent;

    QGroupBox* groupboxCamShowMenu;
    QCheckBox* chkbx_N_axes;
    QCheckBox* chkbx_L_axes;
    QCheckBox* chkbx_F_axes;
    QCheckBox* chkbx_B_axes;
    QCheckBox* chkbx_N_grid;
    QCheckBox* chkbx_L_grid;
    QCheckBox* chkbx_F_grid;
    QCheckBox* chkbx_B_grid;
    QCheckBox* chkbx_Gal_Grid;
    QCheckBox* chkbx_FOVs;
    QCheckBox* chkbx_ProxOps;
    QCheckBox* chkbx_TDRS;
    QCheckBox* chkbx_Shadows;
    QCheckBox* chkbx_AstroLabels;
    QCheckBox* chkbx_TruthVectors;
    QCheckBox* chkbx_FSWVectors;
    QCheckBox* chkbx_MilkyWay;
    QCheckBox* chkbx_FermiSky;

    QGroupBox* groupboxMap;
    QLabel* labelMapTitle;
    QLineEdit* editMapTitle;
    QGroupBox* groupboxMapWidthHeight;
    QLabel* labelMapWidth;
    QSpinBox* spinboxMapWidth;
    QLabel* labelMapHeight;
    QSpinBox* spinboxMapHeight;

    QGroupBox* groupboxMapShowMenu;
    QCheckBox* chkbxClock;
    QCheckBox* chkbxTlmClock;
    QCheckBox* chkbxCredits;
    QCheckBox* chkbxNight;

    QGroupBox* groupboxUnitSphereShowMenu;
    QCheckBox* chkbxShowMajorConstellations;
    QCheckBox* chkbxShowZodiacConstellations;
    QCheckBox* chkbxShowMinorConstellations;
};

#endif // GRAPHICSDIALOG_H
