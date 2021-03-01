#include "DataHeaders/qt42region.h"

Qt42Region::Qt42Region()
{

}

Qt42Region::~Qt42Region()
{

}

Qt42Region::Qt42Region(const Qt42Region& qt42rgn)
{
    m_exists = qt42rgn.m_exists;
    m_name = qt42rgn.m_name;
    m_world = qt42rgn.m_world;
    m_PoswLla = qt42rgn.m_PoswLla;
    m_positionInWorld = qt42rgn.m_positionInWorld;
    m_lngLatAlt = qt42rgn.m_lngLatAlt;
    m_ElasticityDampingFrictionCoef = qt42rgn.m_ElasticityDampingFrictionCoef;
    m_geometryFileName = qt42rgn.m_geometryFileName;
}

Qt42Region& Qt42Region::operator=(const Qt42Region& qt42rgn)
{
    if (this == &qt42rgn)
        return *this;
    m_exists = qt42rgn.m_exists;
    m_name = qt42rgn.m_name;
    m_world = qt42rgn.m_world;
    m_PoswLla = qt42rgn.m_PoswLla;
    m_positionInWorld = qt42rgn.m_positionInWorld;
    m_lngLatAlt = qt42rgn.m_lngLatAlt;
    m_ElasticityDampingFrictionCoef = qt42rgn.m_ElasticityDampingFrictionCoef;
    m_geometryFileName = qt42rgn.m_geometryFileName;
    return *this;
}

void Qt42Region::edit(const bool& exists,
                      const QString& name,
                      const QString& world,
                      const QString& PoswLla,
                      const QVector<double>& positionInWorld,
                      const QVector<double>& lngLatAlt,
                      const QVector<double>& ElasticityDampingFrictionCoef,
                      const QString& geometryFileName)
{
    m_exists = exists;
    m_name = name;
    m_world = world;
    m_PoswLla = PoswLla;
    m_positionInWorld = positionInWorld;
    m_lngLatAlt = lngLatAlt;
    m_ElasticityDampingFrictionCoef = ElasticityDampingFrictionCoef;
    m_geometryFileName = geometryFileName;
}


bool operator==(const Qt42Region& qt42rgn1, const Qt42Region& qt42rgn2)
{
    return qt42rgn1.m_exists == qt42rgn2.m_exists &&
            qt42rgn1.m_name == qt42rgn2.m_name &&
            qt42rgn1.m_world == qt42rgn2.m_world &&
            qt42rgn1.m_PoswLla == qt42rgn2.m_PoswLla &&
            qt42rgn1.m_positionInWorld == qt42rgn2.m_positionInWorld &&
            qt42rgn1.m_lngLatAlt == qt42rgn2.m_lngLatAlt &&
            qt42rgn1.m_ElasticityDampingFrictionCoef == qt42rgn2.m_ElasticityDampingFrictionCoef &&
            qt42rgn1.m_geometryFileName == qt42rgn2.m_geometryFileName;
}

QDataStream& operator<<(QDataStream& dataStream, const Qt42Region& qt42rgn)
{
    dataStream << qt42rgn.m_exists
               << qt42rgn.m_name
               << qt42rgn.m_world
               << qt42rgn.m_PoswLla
               << qt42rgn.m_positionInWorld
               << qt42rgn.m_lngLatAlt
               << qt42rgn.m_ElasticityDampingFrictionCoef
               << qt42rgn.m_geometryFileName;
    return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, Qt42Region& qt42rgn)
{
    dataStream >> qt42rgn.m_exists
               >> qt42rgn.m_name
               >> qt42rgn.m_world
               >> qt42rgn.m_PoswLla
               >> qt42rgn.m_positionInWorld
               >> qt42rgn.m_lngLatAlt
               >> qt42rgn.m_ElasticityDampingFrictionCoef
               >> qt42rgn.m_geometryFileName;
    return dataStream;
}

QDebug operator<<(QDebug dataStream, const Qt42Region& qt42rgn)
{
    dataStream << qt42rgn.m_exists
               << qt42rgn.m_name
               << qt42rgn.m_world
               << qt42rgn.m_PoswLla
               << qt42rgn.m_positionInWorld
               << qt42rgn.m_lngLatAlt
               << qt42rgn.m_ElasticityDampingFrictionCoef
               << qt42rgn.m_geometryFileName;
    return dataStream;
}
