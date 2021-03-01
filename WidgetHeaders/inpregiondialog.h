#ifndef INPREGIONDIALOG_H
#define INPREGIONDIALOG_H

#include "DataHeaders/qt42_headers.h"
#include <QDialog>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QKeyEvent>

class QUndoStack;
class QAction;
class QLabel;
class QLineEdit;
class QGroupBox;
class QComboBox;
class Qt42Model;
class QDialogButtonBox;
class QCheckBox;
class QDoubleSpinBox;
class QPushButton;
class QTabWidget;

class InpRegionDialog : public QDialog
{
public:
    InpRegionDialog(QWidget* parent = nullptr);
    ~InpRegionDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }


private slots:
    void addRegion();
    void removeRegion();
    void enablePOSW_LLA(const int& index);
    void mapDataToSelectedRegion(const int& index);
    void editQt42RegionWhenEditFinished();
    void openDirectoryDialog();
    void updateNameComboboxRegions();
private:
    RegionHeader m_regionHeader = RegionHeader();
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;
    void createWidgets();
    void createActions();
    void createConnections();
    void mapDataFromModelToWidget();
    void mapDataFromWidgetToModel();

    QTabWidget* tabWidgetParent;
    QDialogButtonBox* m_buttonBox;

    QGroupBox* groupboxDetails;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelNumberOfRegions;
    QLineEdit* editNumberOfRegions;
    QLabel* labelRegions;
    QComboBox* comboboxRegions;
    QPushButton* btnAddRegions;
    QPushButton* btnRemoveRegions;
    QLabel* labelNoteAsterisk;
    QLabel* labelNoteAsteriskAsterisk;


    QGroupBox* groupboxEdit;
    QCheckBox* chkbxExists;
    QLabel* labelName;
    QLineEdit* editName;
    QLabel* labelWorld;
    QComboBox* comboboxWorld;
    QLabel* labelPOWSLLA;
    QComboBox* comboboxPOWSLLA;

    QGroupBox* groupboxPositionInWorld;
    QLabel* labelPositionInWorld1;
    QDoubleSpinBox* dblSpinboxPositionInWorld1;
    QLabel* labelPositionInWorld2;
    QDoubleSpinBox* dblSpinboxPositionInWorld2;
    QLabel* labelPositionInWorld3;
    QDoubleSpinBox* dblSpinboxPositionInWorld3;

    QGroupBox* groupboxLngLatAlt;
    QLabel* labelLongitude;
    QDoubleSpinBox* dblSpinboxLongitude;
    QLabel* labelLatitude;
    QDoubleSpinBox* dblSpinboxLatitude;
    QLabel* labelAltitude;
    QDoubleSpinBox* dblSpinboxAltitude;

    QGroupBox* groupboxElasticityDampingFrictionCoef;
    QLabel* labelElasticity;
    QDoubleSpinBox* dblSpinboxElasticity;
    QLabel* labelDamping;
    QDoubleSpinBox* dblSpinboxDamping;
    QLabel* labelFrictionCoef;
    QDoubleSpinBox* dblSpinboxFrictionCoef;

    QPushButton* btnGeometryFileName;
    QLineEdit* editGeometryFileName;

};

#endif // INPREGIONDIALOG_H
