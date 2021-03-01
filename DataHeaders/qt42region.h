#ifndef QT42REGION_H
#define QT42REGION_H

#include <QDataStream>
#include <QDebug>

class Qt42Region
{
public:
    Qt42Region();
    ~Qt42Region();
    Qt42Region(const Qt42Region& qt42rgn);
    Qt42Region& operator=(const Qt42Region& qt42rgn);
    void edit(const bool& exists,
              const QString& name,
              const QString& world,
              const QString& PoswLla,
              const QVector<double>& positionInWorld,
              const QVector<double>& lngLatAlt,
              const QVector<double>& ElasticityDampingFrictionCoef,
              const QString& geometryFileName);

    bool exists() const {return m_exists;}
    QString name() const {return m_name;}
    QString world() const {return m_world;}
    QString PoswLla() const {return m_PoswLla;}
    QVector<double> positionInWorld() const {return m_positionInWorld;}
    QVector<double> lngLatAlt() const {return m_lngLatAlt;}
    QVector<double> ElasticityDampingFrictionCoef() const
    {return m_ElasticityDampingFrictionCoef;}
    QString geometryFileName() const {return m_geometryFileName;}


    friend bool operator==(const Qt42Region& qt42rgn1, const Qt42Region& qt42rgn2);
    friend QDataStream& operator<<(QDataStream& dataStream, const Qt42Region& qt42rgn);
    friend QDataStream& operator>>(QDataStream& dataStream, Qt42Region& qt42rgn);
    friend QDebug operator<<(QDebug dataStream, const Qt42Region& qt42rgn);

private:
    bool m_exists = true;
    QString m_name = QString();
    QString m_world = "EARTH";
    QString m_PoswLla = "POSW";
    QVector<double> m_positionInWorld = QVector<double>(3, 0.0);
    QVector<double> m_lngLatAlt = QVector<double>(3, 0.0);
    QVector<double> m_ElasticityDampingFrictionCoef = QVector<double>(3, 0.0);
    QString m_geometryFileName = QString();
};

#endif // QT42REGION_H
