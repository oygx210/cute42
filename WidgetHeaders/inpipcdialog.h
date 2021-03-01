#ifndef INPIPCDIALOG_H
#define INPIPCDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QKeyEvent>
#include "DataHeaders/qt42_headers.h"

class QAbstractItemModel;
class Qt42Model;
class QUndoStack;
class QAction;
class QGroupBox;
class QCheckBox;
class QTextEdit;
class QLabel;
class QLineEdit;
class QDialogButtonBox;
class QComboBox;
class QSpinBox;
class QTabWidget;

class InpIpcDialog : public QDialog
{
    Q_OBJECT
public:
    InpIpcDialog(QWidget* parent = nullptr);
    ~InpIpcDialog() override;
    void setModel(QAbstractItemModel* model = nullptr);
    void setRootIndex(const QModelIndex& index = QModelIndex());

private slots:
    void createSockets();
    void removeSockets();
    void updateComboboxSockets();
    void createPrefix();
    void removePrefix();
    void updateComboboxPrefix();
    void mapDataFromSelectedIPCtoWidget(const QString& currentText);
    void whenPrefixSelected(const QString& currentText);
    void enableAcidWriteOrRead(const QString& currentText);
    void mapDataForCurrentSockets();   // "Socket" means the same as "IPC".

private:
    void createWidgets();
    void createActions();
    void createConnections();
    bool mapDataFromModelToWidget();
    bool mapDataFromWidgetToModel();

    QTabWidget* tabWidgetParent;

    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    InpIPCHeader m_inpIpch;
    QUndoStack* m_undoStack;
    QAction* m_undoAction;
    QAction* m_redoAction;


    QDialogButtonBox* m_buttonBox;
    QGroupBox* groupBoxDetails;
    QLabel* labelMission;
    QLineEdit* editMission;
    QLabel* labelDirectory;
    QLineEdit* editDirectory;
    QLabel* labelNumberOfSockets;
    QLineEdit* editNumberOfSockets;
    QLabel* labelSockets;
    QComboBox* comboboxSockets;
    QPushButton* btnCreateSocket;
    QPushButton* btnRemoveSocket;


    QGroupBox* groupBoxEdit1;
    QGroupBox* groupBoxEdit2;
    QLabel* labelIpcMode;     // IPC Mode (OFF,TX,RX,WRITEFILE,READFILE)
    QComboBox* comboboxIpcMode;
    QGroupBox* groupboxACID;
    QLabel* labelACID;        // AC.ID for ACS Mode
    QSpinBox* spinboxACID;
    QGroupBox* groupboxFileNameForWriteRead;
    QLabel* labelFileNameForWriteRead;
    QLineEdit* editFileNameForWriteRead;
    QLabel* labelSocketRole;  // Socket Role (SERVER,CLIENT,GMSEC_CLIENT)
    QComboBox* comboboxSocketRole;
    QLabel* labelServerHostName;
    QLineEdit* editServerHostName;
    QLabel* labelServerPort;
    QSpinBox* spinBoxServerPort;
    QCheckBox* chkbxAllowingBlock;  // waiting on RX
    QCheckBox* chkbxEchoToStdout;

    QGroupBox* groupboxPrefix;
    QLabel* labelNumberOfTXprefixes;
    QLineEdit* editNumberOfTXprefixes;
    QComboBox* comboboxPrefix;
    QLineEdit* editNamePrefix;
    QPushButton* btnCreatePrefix;
    QPushButton* btnRemovePrefix;

    void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
            QWidget::focusNextChild();
        else
            QWidget::keyPressEvent(event);
    }
};

#endif // INPIPCDIALOG_H
