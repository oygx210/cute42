#include "DataHeaders/inp_ipc.h"
#include <QDataStream>
#include <QDebug>

Inp_IPC::Inp_IPC(){
    changeType(m_type);
}

Inp_IPC::~Inp_IPC()
{

}

Inp_IPC::Inp_IPC(const Inp_IPC& iic) : Qt42BaseClass(iic)
{
    m_name = iic.m_name;
    m_indexIPC = iic.m_indexIPC;
    m_IpcMode = iic.m_IpcMode;
    m_ACID = iic.m_ACID;
    m_FileNameForWriteRead = iic.m_FileNameForWriteRead;
    m_SocketRole = iic.m_SocketRole;
    m_ServerHostName = iic.m_ServerHostName;
    m_port = iic.m_port;
    m_allowBlocking = iic.m_allowBlocking;
    m_echoToStdout = iic.m_echoToStdout;
    m_qvecPrefix = iic.m_qvecPrefix;
}

Inp_IPC& Inp_IPC::operator=(const Inp_IPC &iic)
{
    if (this == &iic)
        return *this;
    m_name = iic.m_name;
    m_indexIPC = iic.m_indexIPC;
    m_IpcMode = iic.m_IpcMode;
    m_ACID = iic.m_ACID;
    m_FileNameForWriteRead = iic.m_FileNameForWriteRead;
    m_SocketRole = iic.m_SocketRole;
    m_ServerHostName = iic.m_ServerHostName;
    m_port = iic.m_port;
    m_allowBlocking = iic.m_allowBlocking;
    m_echoToStdout = iic.m_echoToStdout;
    m_qvecPrefix = iic.m_qvecPrefix;
    return *this;
}

void Inp_IPC::duplicate(const Inp_IPC &iic)
{
    m_name = iic.m_name;
    m_indexIPC = iic.m_indexIPC;
    m_IpcMode = iic.m_IpcMode;
    m_ACID = iic.m_ACID;
    m_FileNameForWriteRead = iic.m_FileNameForWriteRead;
    m_SocketRole = iic.m_SocketRole;
    m_ServerHostName = iic.m_ServerHostName;
    m_port = iic.m_port;
    m_allowBlocking = iic.m_allowBlocking;
    m_echoToStdout = iic.m_echoToStdout;
    m_qvecPrefix = iic.m_qvecPrefix;
}

void Inp_IPC::edit(const QString& IpcMode, const int& ACID,
                   const QString& FileNameForWriteRead,
                   const QString& SocketRole,
                   const QString& ServerHostName, const int& port,
                   const bool& allowBlocking, const bool& echoToStdout,
                   const QPair<int, QString> modifiedPrefix,
                   const QVector<QString>& qvecPrefix)
{
    m_IpcMode = IpcMode;
    m_ACID = ACID;
    m_FileNameForWriteRead = FileNameForWriteRead;
    m_SocketRole = SocketRole;
    m_ServerHostName = ServerHostName;
    m_port = port;
    m_allowBlocking = allowBlocking;
    m_echoToStdout = echoToStdout;

    if (modifiedPrefix.first > -1 && modifiedPrefix.first < m_qvecPrefix.size()
            && !modifiedPrefix.second.isEmpty())
    {
        m_qvecPrefix.replace(modifiedPrefix.first, modifiedPrefix.second);
    }
    if (qvecPrefix.size() > 0)
        m_qvecPrefix = qvecPrefix;
}

void Inp_IPC::createPrefix()
{
    int maxIndex = 0;
    QString defaultPrefix = "Default Prefix";
    for(QString prefix : m_qvecPrefix)
    {
        prefix = prefix.trimmed();
        QStringList l = prefix.split("-");
        if (l[0].trimmed() == defaultPrefix)
        {
            int index = l[1].toInt();
            if (maxIndex <= index)
                maxIndex = index + 1;
        }
    }
    m_qvecPrefix.append(defaultPrefix + "-" + QString::number(maxIndex));
}

void Inp_IPC::createPrefix(const QString &prefix)
{
    if (!m_qvecPrefix.contains(prefix.trimmed()))
        m_qvecPrefix.append(prefix.trimmed());
}

void Inp_IPC::removePrefix(const QString& prefix)
{
    if (m_qvecPrefix.contains(prefix.trimmed()))
        m_qvecPrefix.removeAll(prefix.trimmed());
}

void Inp_IPC::removePrefix(const int& index)
{
    if (index <= -1 || index >= m_qvecPrefix.size())
        return;

}


QDataStream& operator<<(QDataStream& dataStream, const Inp_IPC& inpipc)
{
    dataStream << inpipc.m_name
               << inpipc.m_IpcMode
               << inpipc.m_ACID
               << inpipc.m_FileNameForWriteRead
               << inpipc.m_SocketRole
               << inpipc.m_ServerHostName
               << inpipc.m_port
               << inpipc.m_allowBlocking
               << inpipc.m_echoToStdout
               << inpipc.m_qvecPrefix;
    return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, Inp_IPC& inpipc)
{
    dataStream >> inpipc.m_name
               >> inpipc.m_IpcMode
               >> inpipc.m_ACID
               >> inpipc.m_FileNameForWriteRead
               >> inpipc.m_SocketRole
               >> inpipc.m_ServerHostName
               >> inpipc.m_port
               >> inpipc.m_allowBlocking
               >> inpipc.m_echoToStdout
               >> inpipc.m_qvecPrefix;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const Inp_IPC& inpipc)
{
    dataStream << inpipc.m_name
               << inpipc.m_IpcMode
               << inpipc.m_ACID
               << inpipc.m_FileNameForWriteRead
               << inpipc.m_SocketRole
               << inpipc.m_ServerHostName
               << inpipc.m_port
               << inpipc.m_allowBlocking
               << inpipc.m_echoToStdout
               << inpipc.m_qvecPrefix;
    return dataStream;
}
