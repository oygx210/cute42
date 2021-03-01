#ifndef INP_IPC_H
#define INP_IPC_H
#include "qt42baseclass.h"
#include <QVector>
#include <QDebug>

class Inp_IPC : public Qt42BaseClass
{
public:
    Inp_IPC();
    ~Inp_IPC() override;
    Inp_IPC(const Inp_IPC& iic);
    Inp_IPC& operator=(const Inp_IPC& iic);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}

    QString IpcMode() const {return m_IpcMode;}
    int ACID() const {return m_ACID;}
    QString FileNameForWriteRead() const {return m_FileNameForWriteRead;}
    QString SocketRole() const {return m_SocketRole;}
    QString ServerHostName() const {return m_ServerHostName;}
    int port() const {return m_port;}
    bool allowBlocking() const {return m_allowBlocking;}
    bool echoToStdout() const {return m_echoToStdout;}
    int numberOfTXPrefix() const {return m_qvecPrefix.size();}
    QVector<QString> qvecPrefix() const {return m_qvecPrefix;}
    void createPrefix(const QString& prefix);
    void createPrefix();
    void removePrefix(const QString& prefix);
    void removePrefix(const int& index);

    void setIndex(const int& indexIPC)
    {m_indexIPC = indexIPC; m_name = m_namePrefix+QString::number(m_indexIPC);}

    int indexIPC() const {return m_indexIPC;}

    void edit(const QString& IpcMode, const int& ACID,
              const QString& FileNameForWriteRead,
              const QString& SocketRole,
              const QString& ServerHostName, const int& port,
              const bool& allowBlocking, const bool& echoToStdout,
              const QPair <int, QString> modifiedPrefix = QPair<int,QString>(-1,""),
              const QVector<QString>& qvecPrefix = QVector<QString>());

    void duplicate(const Inp_IPC& inpIpc);
    void renamePrefix(const QString& oldPrefix, const QString& newPrefix)
    {
        m_qvecPrefix.replace(m_qvecPrefix.indexOf(oldPrefix.trimmed()), newPrefix.trimmed());
    }

    friend QDataStream& operator<<(QDataStream& dataStream, const Inp_IPC& inpipc);
    friend QDataStream& operator>>(QDataStream& dataStream, Inp_IPC& inpipc);
    friend QDebug operator<< (QDebug dataStream, const Inp_IPC& inpipc);
private:
    void changeType(const objectType &type) override {Qt42BaseClass::changeType(type);}
    const QString m_namePrefix = "IPC ";
    const objectType m_type = INPIPC;
    int m_indexIPC = -1;

    QString m_name = m_namePrefix + QString::number(m_indexIPC);
    QString m_IpcMode = "OFF";
    int m_ACID = -1;
    QString m_FileNameForWriteRead = QString();
    QString m_SocketRole = "SERVER";
    QString m_ServerHostName = "localhost";
    int m_port = 0;
    bool m_allowBlocking = true;
    bool m_echoToStdout = true;
    QVector <QString> m_qvecPrefix = QVector <QString>();
};


Q_DECLARE_METATYPE(Inp_IPC)
#endif // INP_IPC_H
