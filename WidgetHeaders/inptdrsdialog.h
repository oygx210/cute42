#ifndef INPTDRSDIALOG_H
#define INPTDRSDIALOG_H

#include "DataHeaders/qt42_headers.h"
#include <QDialog>
#include <QModelIndex>
#include <QAbstractItemModel>

class Qt42Model;
class QAction;
class QUndoStack;
class QLabel;
class QLineEdit;
class QCheckBox;
class QGroupBox;
class QDialogButtonBox;
class QTabWidget;

class InpTDRsDialog : public QDialog
{
    Q_OBJECT
public:
    InpTDRsDialog(QWidget* parent = nullptr);
    ~InpTDRsDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());
private:
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    InpTDRs m_inpTDRs = InpTDRs();

    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;

    void createWidgets();
    void createActions();
    void createConnections();
    void mapDataFromModelToWidget();
    void mapDataFromWidgetToModel();

    QTabWidget* m_tabWidgetParent;
    QDialogButtonBox* m_buttonBox;

    QLabel* labelMission;
    QGroupBox* groupboxEdit;

    QGroupBox* groupboxTDRS_1;
    QCheckBox* chkbxTDRS_1;
    QLabel* labelDesignationTDRS_1;
    QLineEdit* editDesignationTDRS_1;

    QGroupBox* groupboxTDRS_2;
    QCheckBox* chkbxTDRS_2;
    QLabel* labelDesignationTDRS_2;
    QLineEdit* editDesignationTDRS_2;

    QGroupBox* groupboxTDRS_3;
    QCheckBox* chkbxTDRS_3;
    QLabel* labelDesignationTDRS_3;
    QLineEdit* editDesignationTDRS_3;

    QGroupBox* groupboxTDRS_4;
    QCheckBox* chkbxTDRS_4;
    QLabel* labelDesignationTDRS_4;
    QLineEdit* editDesignationTDRS_4;

    QGroupBox* groupboxTDRS_5;
    QCheckBox* chkbxTDRS_5;
    QLabel* labelDesignationTDRS_5;
    QLineEdit* editDesignationTDRS_5;

    QGroupBox* groupboxTDRS_6;
    QCheckBox* chkbxTDRS_6;
    QLabel* labelDesignationTDRS_6;
    QLineEdit* editDesignationTDRS_6;

    QGroupBox* groupboxTDRS_7;
    QCheckBox* chkbxTDRS_7;
    QLabel* labelDesignationTDRS_7;
    QLineEdit* editDesignationTDRS_7;

    QGroupBox* groupboxTDRS_8;
    QCheckBox* chkbxTDRS_8;
    QLabel* labelDesignationTDRS_8;
    QLineEdit* editDesignationTDRS_8;

    QGroupBox* groupboxTDRS_9;
    QCheckBox* chkbxTDRS_9;
    QLabel* labelDesignationTDRS_9;
    QLineEdit* editDesignationTDRS_9;

    QGroupBox* groupboxTDRS_10;
    QCheckBox* chkbxTDRS_10;
    QLabel* labelDesignationTDRS_10;
    QLineEdit* editDesignationTDRS_10;

    QLabel* labelFootnoteAsterisk;
};

#endif // INPTDRSDIALOG_H
