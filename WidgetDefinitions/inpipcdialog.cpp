#include "WidgetHeaders/inpipcdialog.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "MVDheaders/qt42model.h"
#include "DataHeaders/qt42_headers.h"
#include "ShareHeaders/qt42commands.h"
#include <QAbstractItemModel>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QUndoStack>
#include <QPushButton>
#include <QAction>
#include <QSpinBox>
#include <QTabWidget>
#include <QDebug>

InpIpcDialog::InpIpcDialog(QWidget* parent) : QDialog(parent)
{
    if (parent)
        tabWidgetParent = static_cast<QTabWidget*>(parent);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    m_undoStack = new QUndoStack(this);
    createWidgets();
    createActions();
    createConnections();
}

InpIpcDialog::~InpIpcDialog()
{

}


void InpIpcDialog::createWidgets()
{
    QHBoxLayout* layoutWidget = new QHBoxLayout;
    QVBoxLayout* layoutDialog = new QVBoxLayout;
    const QSize maxSizeGroupBox(380, 350);
    groupBoxDetails = new QGroupBox(tr("Details"));
    groupBoxDetails->setAlignment(Qt::AlignCenter);
    groupBoxDetails->setMaximumSize(maxSizeGroupBox);
    QFormLayout* layoutDetails = new QFormLayout;
    labelMission = new QLabel(tr("Mission"));
    editMission = new QLineEdit();
    editMission->setReadOnly(true);
    labelDirectory = new QLabel(tr("Directory"));
    editDirectory = new QLineEdit();
    editDirectory->setReadOnly(true);
    labelNumberOfSockets = new QLabel(tr("Number of Sockets"));
    editNumberOfSockets = new QLineEdit;
    editNumberOfSockets->setReadOnly(true);
    labelSockets = new QLabel(tr("Socket"));
    comboboxSockets = new QComboBox;
    QHBoxLayout* layoutBtnSockets = new QHBoxLayout;
    btnCreateSocket = new QPushButton(tr("Create"));
    btnRemoveSocket = new QPushButton(tr("Remove"));
    layoutBtnSockets->addWidget(btnCreateSocket,1);
    layoutBtnSockets->addWidget(btnRemoveSocket,1);
    layoutDetails->addRow(labelMission, editMission);
    layoutDetails->addRow(labelDirectory, editDirectory);
    layoutDetails->addRow(labelNumberOfSockets, editNumberOfSockets);
    layoutDetails->addRow(labelSockets, comboboxSockets);
    layoutDetails->addRow(layoutBtnSockets);
    groupBoxDetails->setLayout(layoutDetails);

    groupBoxEdit1 = new QGroupBox(tr("Edit"));
    groupBoxEdit1->setAlignment(Qt::AlignCenter);
    groupBoxEdit1->setMaximumSize(maxSizeGroupBox);
    QFormLayout* layoutEdit1 = new QFormLayout;
    groupBoxEdit2 = new QGroupBox(tr("Edit-Continued"));
    groupBoxEdit2->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutEdit2 = new QFormLayout;
    groupBoxEdit2->setMaximumSize(maxSizeGroupBox);

    labelIpcMode = new QLabel(tr("IPC Mode"));
    comboboxIpcMode = new QComboBox();
    comboboxIpcMode->addItems(list_IPCMode);
    groupboxACID = new QGroupBox(tr("AC.ID for ACS mode"));
    QHBoxLayout* layoutACID = new QHBoxLayout;
    labelACID = new QLabel(tr("ACID"));
    spinboxACID = new QSpinBox;
    layoutACID->addWidget(labelACID, 1);
    layoutACID->addWidget(spinboxACID, 1);
    groupboxACID->setLayout(layoutACID);

    groupboxFileNameForWriteRead = new QGroupBox(tr("File name for Write or Read"));
    QFormLayout* layoutFileNameForWriteRead= new QFormLayout;
    labelFileNameForWriteRead = new QLabel(tr("File Name"));
    editFileNameForWriteRead = new QLineEdit;
    layoutFileNameForWriteRead->addRow(labelFileNameForWriteRead, editFileNameForWriteRead);
    groupboxFileNameForWriteRead->setLayout(layoutFileNameForWriteRead);

    labelSocketRole = new QLabel(tr("Socket Role"));
    comboboxSocketRole = new QComboBox();
    comboboxSocketRole->addItems(list_SocketRole);
    labelServerHostName = new QLabel(tr("Server Host Name"));
    editServerHostName = new QLineEdit;
    labelServerPort = new QLabel(tr("Port"));
    spinBoxServerPort = new QSpinBox();
    spinBoxServerPort->setMaximum(10000000);
    chkbxAllowingBlock = new QCheckBox(tr("Allow Blocking (i.e. wait on RX)"));
    chkbxEchoToStdout = new QCheckBox(tr("Echo to stdout (Show message in a window)"));

    groupboxPrefix = new QGroupBox(tr("Prefix"));
    QFormLayout* layoutPrefix = new QFormLayout;
    QHBoxLayout* layoutComboboxEditPrefix = new QHBoxLayout;
    QHBoxLayout* layoutbtn = new QHBoxLayout;
    labelNumberOfTXprefixes = new QLabel(tr("Number of TX Prefixes"));
    editNumberOfTXprefixes = new QLineEdit;
    editNumberOfTXprefixes->setReadOnly(true);
    comboboxPrefix = new QComboBox;
    editNamePrefix = new QLineEdit;
    layoutComboboxEditPrefix->addWidget(comboboxPrefix,1);
    layoutComboboxEditPrefix->addWidget(editNamePrefix,1);
    btnCreatePrefix = new QPushButton(tr("Create"));
    btnRemovePrefix = new QPushButton(tr("Remove"));
    layoutbtn->addWidget(btnCreatePrefix,1);
    layoutbtn->addWidget(btnRemovePrefix,1);
    layoutPrefix->addRow(labelNumberOfTXprefixes, editNumberOfTXprefixes);
    layoutPrefix->addRow(layoutComboboxEditPrefix);
    layoutPrefix->addRow(layoutbtn);
    groupboxPrefix->setLayout(layoutPrefix);

    layoutEdit1->addRow(labelIpcMode, comboboxIpcMode);
    layoutEdit1->addRow(groupboxACID);
    layoutEdit1->addRow(groupboxFileNameForWriteRead);
    groupBoxEdit1->setLayout(layoutEdit1);

    layoutEdit2->addRow(labelSocketRole, comboboxSocketRole);
    layoutEdit2->addRow(labelServerHostName, editServerHostName);
    layoutEdit2->addRow(labelServerPort, spinBoxServerPort);
    layoutEdit2->addRow(chkbxAllowingBlock);
    layoutEdit2->addRow(chkbxEchoToStdout);
    layoutEdit2->addRow(groupboxPrefix);
    groupBoxEdit2->setLayout(layoutEdit2);

    QVBoxLayout* layoutWidgetLeft = new QVBoxLayout;
    layoutWidgetLeft->addWidget(groupBoxDetails,1);
    layoutWidgetLeft->addWidget(groupBoxEdit1,1);
    layoutWidget->addLayout(layoutWidgetLeft,1);
    layoutWidget->addWidget(groupBoxEdit2,1);

    layoutDialog->addLayout(layoutWidget);
    layoutDialog->addWidget(m_buttonBox);
    setLayout(layoutDialog);
}

void InpIpcDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void InpIpcDialog::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
}

void InpIpcDialog::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<InpIPCHeader>())
        return;
    m_index = index;
    m_inpIpch = m_index.data().value<InpIPCHeader>();
    mapDataFromModelToWidget();
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    QStringList StringListSockets;
    StringListSockets.append(QString());
    for (int i = 0; i < m_inpIpch.numberOfInpIpc(); ++i)
    {
        StringListSockets.append(m_inpIpch.qvecInpIpc()[i].name().trimmed());
    }

    comboboxSockets->clear();
    comboboxSockets->addItems(StringListSockets);
    comboboxSockets->setCurrentIndex(0);
    groupBoxEdit1->setEnabled(false);
    groupBoxEdit2->setEnabled(false);
}

void InpIpcDialog::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);

    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Save),
            [=](){m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_undoAction, &QAction::triggered, this, [=](){mapDataFromModelToWidget();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(comboboxIpcMode, &QComboBox::currentTextChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxSocketRole, &QComboBox::currentTextChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editServerHostName, &QLineEdit::textChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinBoxServerPort, QOverload<int>::of(&QSpinBox::valueChanged), m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxAllowingBlock, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxAllowingBlock, &QCheckBox::stateChanged, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});

    connect(comboboxIpcMode, &QComboBox::currentTextChanged, this, &InpIpcDialog::enableAcidWriteOrRead);
    connect(btnCreateSocket, &QPushButton::clicked, this, &InpIpcDialog::createSockets);
    connect(btnRemoveSocket, &QPushButton::clicked, this, &InpIpcDialog::removeSockets);
    connect(btnCreatePrefix, &QPushButton::clicked, this, &InpIpcDialog::createPrefix);
    connect(btnRemovePrefix, &QPushButton::clicked, this, &InpIpcDialog::removePrefix);
    connect(comboboxSockets, &QComboBox::currentTextChanged,
            this, &InpIpcDialog::mapDataFromSelectedIPCtoWidget);

    connect(comboboxPrefix, &QComboBox::currentTextChanged, this, &InpIpcDialog::whenPrefixSelected);

    connect(comboboxIpcMode, &QComboBox::currentTextChanged, this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(spinboxACID, QOverload<int>::of(&QSpinBox::valueChanged), this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(editFileNameForWriteRead, &QLineEdit::textChanged, this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(comboboxSocketRole, &QComboBox::currentTextChanged, this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(editServerHostName, &QLineEdit::textChanged, this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(spinBoxServerPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(chkbxAllowingBlock, &QCheckBox::stateChanged, this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(chkbxEchoToStdout, &QCheckBox::stateChanged, this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(editNumberOfTXprefixes, &QLineEdit::textChanged, this, &InpIpcDialog::mapDataForCurrentSockets);
    connect(editNamePrefix, &QLineEdit::editingFinished, this, &InpIpcDialog::mapDataForCurrentSockets);
}

void InpIpcDialog::mapDataForCurrentSockets()
{
    int indexIPC = -1;
    for (int i = 0; i < m_inpIpch.numberOfInpIpc(); ++i)
    {
        if (comboboxSockets->currentText().trimmed().toUpper() ==
                m_inpIpch.ipc(i).name().trimmed().toUpper())
        {
            indexIPC = i;
        }
    }
    if (indexIPC <= -1)
        return;

    QPair<int, QString> prefixIndexValue (comboboxPrefix->currentIndex()-1, editNamePrefix->text().trimmed());
    m_inpIpch.ipc(indexIPC).edit(map_IPCMode.value(comboboxIpcMode->currentText().trimmed()),
                                 spinboxACID->value(),
                                 editFileNameForWriteRead->text().trimmed(),
                                 map_SocketRole.value(comboboxSocketRole->currentText().trimmed()),
                                 editServerHostName->text().trimmed(), spinBoxServerPort->value(),
                                 chkbxAllowingBlock->isChecked(), chkbxEchoToStdout->isChecked(),
                                 prefixIndexValue);
    mapDataFromSelectedIPCtoWidget(m_inpIpch.ipc(indexIPC).name().trimmed());
    comboboxPrefix->setCurrentText(prefixIndexValue.second.trimmed());
}

void InpIpcDialog::createSockets()
{
    QString currentSocket = comboboxSockets->currentText().trimmed();
    m_inpIpch.createNewIPC();
    editNumberOfSockets->setText(QString::number(m_inpIpch.qvecInpIpc().size()));
    updateComboboxSockets();
    comboboxSockets->setCurrentText(currentSocket);
    if (comboboxSockets->currentText().trimmed().isEmpty())
    {
        groupBoxEdit1->setEnabled(false);
        groupBoxEdit2->setEnabled(false);
    }
}


void InpIpcDialog::removeSockets()
{
    if (comboboxSockets->currentText().trimmed().isEmpty())
        return;

    for (int i = 0; i < m_inpIpch.qvecInpIpc().size(); ++i)
    {
        if (m_inpIpch.qvecInpIpc()[i].name().trimmed() == comboboxSockets->currentText().trimmed())
        {
            m_inpIpch.removeIPC(i);
            --i;
        }
    }
    editNumberOfSockets->setText(QString::number(m_inpIpch.numberOfInpIpc()));
    updateComboboxSockets();
    comboboxSockets->setCurrentIndex(0);
}

void InpIpcDialog::updateComboboxSockets()
{
    QStringList stringListSockets{""};
    comboboxSockets->clear();
    for (int i = 0; i < m_inpIpch.qvecInpIpc().size(); ++i)
    {
        stringListSockets.append(m_inpIpch.qvecInpIpc()[i].name().trimmed());
    }
    comboboxSockets->addItems(stringListSockets);
}

void InpIpcDialog::createPrefix()
{
    QString currentText = comboboxPrefix->currentText().trimmed();
    int index = 0;
    QString currentIpcName = comboboxSockets->currentText().trimmed();
    for (int i = 0; i < m_inpIpch.qvecInpIpc().size(); ++i)
    {
        if(currentIpcName == m_inpIpch.qvecInpIpc()[i].name().trimmed())
            index = i;
    }

    m_inpIpch.ipc(index).createPrefix();
    editNumberOfTXprefixes->setText(QString::number(m_inpIpch.ipc(index).qvecPrefix().size()));
    updateComboboxPrefix();
    comboboxPrefix->setCurrentText(currentText);
}

void InpIpcDialog::removePrefix()
{
    QString currentPrefix = comboboxPrefix->currentText().trimmed();
    if (currentPrefix.isEmpty())
        return;
    int index = 0;
    QString currentIpcName = comboboxSockets->currentText().trimmed();
    for (int i = 0; i < m_inpIpch.qvecInpIpc().size(); ++i)
    {
        if(currentIpcName == m_inpIpch.qvecInpIpc()[i].name().trimmed())
            index = i;
    }

    m_inpIpch.ipc(index).removePrefix(currentPrefix);
    updateComboboxPrefix();
    comboboxPrefix->setCurrentText("");
    editNumberOfTXprefixes->setText(QString::number(m_inpIpch.ipc(index).numberOfTXPrefix()));
}

void InpIpcDialog::updateComboboxPrefix()
{
    comboboxPrefix->clear();
    QStringList stringListPrefix{""};
    Inp_IPC currentIpc;
    for (int i = 0; i < m_inpIpch.qvecInpIpc().size(); ++i)
    {
        if (comboboxSockets->currentText().trimmed() == m_inpIpch.qvecInpIpc()[i].name().trimmed())
        {
            currentIpc = m_inpIpch.ipc(i);
            break;
        }
    }
    for (int i = 0; i < currentIpc.qvecPrefix().size(); ++i)
    {
        QString prefix = currentIpc.qvecPrefix()[i].trimmed();
        stringListPrefix.append(prefix);
    }
    comboboxPrefix->addItems(stringListPrefix);
}

void InpIpcDialog::whenPrefixSelected(const QString& currentText)
{
    if (currentText.trimmed().isEmpty())
    {
        editNamePrefix->clear();
        return;
    }

    else
        editNamePrefix->setText(currentText.trimmed());
}

bool InpIpcDialog::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<InpIPCHeader>())
        return false;
    QModelIndex modelIndexParent = m_index.parent();
    Mission mission = modelIndexParent.data().value<Mission>();
    editMission->setText(mission.name().trimmed());
    editDirectory->setText(mission.directory().trimmed());
    editNumberOfSockets->setText(QString::number(m_inpIpch.numberOfInpIpc()));
    return true;
}

bool InpIpcDialog::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<InpIPCHeader>())
        return false;
    QVariant newData = QVariant();

    newData.setValue(m_inpIpch);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);

    return true;
}

void InpIpcDialog::mapDataFromSelectedIPCtoWidget(const QString& currentText)
{
    Inp_IPC ippc;
    if (currentText.trimmed().isEmpty())
    {
        ippc = Inp_IPC();
        groupBoxEdit1->setEnabled(false);
        groupBoxEdit2->setEnabled(false);
    }

    else
    {
        groupBoxEdit1->setEnabled(true);
        groupBoxEdit2->setEnabled(true);
        enableAcidWriteOrRead(comboboxIpcMode->currentText().trimmed());
    }
    for (int i = 0; i < m_inpIpch.qvecInpIpc().size(); ++i)
    {
        if (m_inpIpch.qvecInpIpc()[i].name().trimmed() == currentText.trimmed())
            ippc = m_inpIpch.qvecInpIpc()[i];
    }
    comboboxIpcMode->setCurrentText(map_IPCMode.value(ippc.IpcMode().trimmed()));
    spinboxACID->setValue(ippc.ACID());
    editFileNameForWriteRead->setText(ippc.FileNameForWriteRead().trimmed());
    comboboxSocketRole->setCurrentText(map_SocketRole.value(ippc.SocketRole().trimmed()));
    editServerHostName->setText(ippc.ServerHostName().trimmed());
    spinBoxServerPort->setValue(ippc.port());
    chkbxAllowingBlock->setChecked(ippc.allowBlocking());
    chkbxEchoToStdout->setChecked(ippc.echoToStdout());
    editNumberOfTXprefixes->setText(QString::number(ippc.numberOfTXPrefix()));
    comboboxPrefix->clear();
    QStringList stringListPrefixes{""};
    for (int i = 0; i < ippc.qvecPrefix().size(); ++i)
    {
        QString prefix = ippc.qvecPrefix()[i].trimmed();
        stringListPrefixes.append(prefix);
    }
    comboboxPrefix->addItems(stringListPrefixes);
}

void InpIpcDialog::enableAcidWriteOrRead(const QString& currentText)
{
    if (currentText.trimmed() == map_IPCMode.value("ACS").trimmed())
        groupboxACID->setEnabled(true);
    else
        groupboxACID->setEnabled(false);

    if (currentText.trimmed() == map_IPCMode.value("WRITEFILE").trimmed() ||
            currentText.trimmed() == map_IPCMode.value("READFILE").trimmed())
        groupboxFileNameForWriteRead->setEnabled(true);
    else
        groupboxFileNameForWriteRead->setEnabled(false);
}

