#ifndef FOVDIALOG_H
#define FOVDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QKeyEvent>
#include "DataHeaders/qt42_headers.h"

class Qt42Model;
class QTabWidget;
class QGroupBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QAbstractItemModel;
class QAction;
class QUndoStack;
class QCheckBox;

class FOVDialog : public QDialog
{
    Q_OBJECT
public:
    FOVDialog(QWidget* parent = nullptr);
    ~FOVDialog();
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
    QModelIndex rootIndex() const {return m_index;}
signals:
    void currentModelIndexSC(const QModelIndex& modelIndexSC);
private slots:
    void renewLabelFOV(const QString& labelFOV);
    void renewComboboxFOV();
    void mapDataForSelectedFOV(const QString& comboboxText);
    void renewComboboxSC();
    void renewComboboxSCB(const QModelIndex& modelIndexSC);
    void currentSC(const QString& nameSC = QString());
    void createFOV();
    void removeFOV();
    void editCurrentFOV();

private:
    void createWidgets();
    void createActions();
    void createConnections();
    void mapDataFromModelToWidget();
    void mapDataFromWidgetToModel();
    void resetWidgets();
    QStringList list_FOVLabel;
    QStringList list_SC;
    QStringList list_SCB;

    const QString labelMissionName = tr("Mission: ");
    QString missionName = QString();
    QTabWidget* parentTabWidget;

    QLabel* labelMissionForDialog;
    QLabel* labelFOVForDialog;
    QTabWidget* tabWidgetFOV;
    QWidget* fovPage1;
    QWidget* fovPage2;
    QWidget* fovPage3;

    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    FOVHeader m_FOVHeader;
    QModelIndex m_modelIndexMission = QModelIndex();
    QModelIndex m_modelIndexSCHeader = QModelIndex();
    QModelIndex m_modelIndexSC = QModelIndex();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    QDialogButtonBox* m_buttonBox;

    QGroupBox* groupBoxDetails;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelDirectory;
    QLineEdit* editDirectory;
    QLabel* labelNumberOfFOV;
    QLineEdit* editNumberOfFOV;

    QGroupBox* groupboxFOV;
    QLabel* labelFOV;
    QComboBox* comboboxFOV;
    QPushButton* btnCreateFOV;
    QPushButton* btnRemoveFOV;

    QGroupBox* groupboxEdit1;
    QGroupBox* groupboxEdit2;
    QGroupBox* groupboxEdit3;
    QLabel* labellabel;
    QLineEdit* editLabel;
    QGroupBox* groupboxSides;
    QLabel* labelNumberOfSides;
    QSpinBox* spinBoxNumberOfSides;
    QLabel* labelLengthOfSides;
    QDoubleSpinBox* dblSpinBoxLengthOfSides;

    QGroupBox* groupboxWidthHeight;
    QLabel* labelXWidth;
    QDoubleSpinBox* dblSpinBoxXWidth;
    QLabel* labelYHeight;
    QDoubleSpinBox* dblSpinBoxYHeight;

    QGroupBox* groupboxRGB_ALPHA;
    QLabel* labelRGB_R;
    QDoubleSpinBox* dblSpinBoxRGB_R;
    QLabel* labelRGB_G;
    QDoubleSpinBox* dblSpinBoxRGB_G;
    QLabel* labelRGB_B;
    QDoubleSpinBox* dblSpinBoxRGB_B;
    QLabel* labelRGB_Alpha;
    QDoubleSpinBox* dblSpinBoxRGB_Alpha;
    QLabel* labelDrawing;
    QComboBox* comboboxDrawing;

    QGroupBox* groupboxDrawField;
    QCheckBox* chkbxDrawNearField;
    QCheckBox* chkbxDrawFarField;

    QGroupBox* groupboxSC_SCB;
    QLabel* labelSC;
    QComboBox* comboboxSC;
    QLabel* labelSCB;
    QComboBox* comboboxSCB;

    QGroupBox* groupboxPositionBody;
    QLabel* labelPositionBody1;
    QDoubleSpinBox* dblSpinBoxPositionBody1;
    QLabel* labelPositionBody2;
    QDoubleSpinBox* dblSpinBoxPositionBody2;
    QLabel* labelPositionBody3;
    QDoubleSpinBox* dblSpinBoxPositionBody3;

    QGroupBox* groupboxEulerAngleSeq;
    QLabel* labelEulerAngle1;
    QDoubleSpinBox* dblSpinBoxEulerAngle1;
    QLabel* labelEulerAngle2;
    QDoubleSpinBox* dblSpinBoxEulerAngle2;
    QLabel* labelEulerAngle3;
    QDoubleSpinBox* dblSpinBoxEulerAngle3;
    QLabel* labelEulerSeq;
    QComboBox* comboboxEulerSeq;
    QPushButton* btnEditOk;


    void keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};

#endif // FOVDIALOG_H
