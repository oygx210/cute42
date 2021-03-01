#include "DataHeaders/mission.h"
#include "DataHeaders/spacecraft.h"
#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/missionholder.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include <QDebug>

Mission::Mission(MissionHolder* MH) : m_MissionHolder(MH)
{
    if (m_MissionHolder)
    {
        m_name = defaultName+"-"+QString::number(MH->maxNumberDefaultMission()+1);
    }
    m_SpacecraftHeader = new SpacecraftHeader(this);
    m_OrbitHeader = new OrbitHeader(this);
    m_InpSimHeader = new InpSimHeader(this);
    m_FOVHeader = new FOVHeader(this);
    m_InpIPCHeader = new InpIPCHeader(this);
    m_graphisHeader = new GraphicsHeader(this);
    m_inpTDRs = new InpTDRs(this);
    m_regionHeader = new RegionHeader(this);
    changeType(m_type);
}

Mission::Mission(const Mission& otherMission) : Qt42BaseClass(otherMission)
{
    m_directory = otherMission.m_directory;
    m_MissionHolder = otherMission.m_MissionHolder;
    m_index = otherMission.m_index;
    m_name = otherMission.m_name;
    m_SpacecraftHeader = otherMission.m_SpacecraftHeader;
    m_OrbitHeader = otherMission.m_OrbitHeader;
    m_InpSimHeader = otherMission.m_InpSimHeader;
    m_FOVHeader = otherMission.m_FOVHeader;
    m_InpIPCHeader = otherMission.m_InpIPCHeader;
    m_graphisHeader = otherMission.m_graphisHeader;
    m_inpTDRs = otherMission.m_inpTDRs;
    m_regionHeader = otherMission.m_regionHeader;
    m_SpacecraftHeaderObject = otherMission.m_SpacecraftHeaderObject;
    m_OrbitHeaderObejct = otherMission.m_OrbitHeaderObejct;
    m_InpSimHeaderObject = otherMission.m_InpSimHeaderObject;
    m_FOVHeaderObject = otherMission.m_FOVHeaderObject;
    m_InpIPCHeaderObject = otherMission.m_InpIPCHeaderObject;
    m_GraphisHeaderObject = otherMission.m_GraphisHeaderObject;
    m_inpTDRsObject = otherMission.m_inpTDRsObject;
    m_regionHeaderObject = otherMission.m_regionHeaderObject;
}

Mission::~Mission()
{
    // Poorly-defined destructor will cause QVariant::setValue(Mission) to fail;
}

Mission& Mission::operator=(const Mission &otherMission)
{
    if (this == &otherMission)
        return *this;
    m_directory = otherMission.m_directory;
    m_MissionHolder = otherMission.m_MissionHolder;
    m_index = otherMission.m_index;
    m_name = otherMission.m_name;
    m_SpacecraftHeader = otherMission.m_SpacecraftHeader;
    m_OrbitHeader = otherMission.m_OrbitHeader;
    m_InpSimHeader = otherMission.m_InpSimHeader;
    m_FOVHeader = otherMission.m_FOVHeader;
    m_InpIPCHeader = otherMission.m_InpIPCHeader;
    m_graphisHeader = otherMission.m_graphisHeader;
    m_inpTDRs = otherMission.m_inpTDRs;
    m_regionHeader = otherMission.m_regionHeader;
    m_SpacecraftHeaderObject = otherMission.m_SpacecraftHeaderObject;
    m_OrbitHeaderObejct = otherMission.m_OrbitHeaderObejct;
    m_InpSimHeaderObject = otherMission.m_InpSimHeaderObject;
    m_FOVHeaderObject = otherMission.m_FOVHeaderObject;
    m_InpIPCHeaderObject = otherMission.m_InpIPCHeaderObject;
    m_GraphisHeaderObject = otherMission.m_GraphisHeaderObject;
    m_inpTDRsObject = otherMission.m_inpTDRsObject;
    m_regionHeaderObject = otherMission.m_regionHeaderObject;
    return *this;
}

bool Mission::operator==(const Mission &otherMission) const
{
    return
            m_directory == otherMission.m_directory &&
            m_name == otherMission.m_name &&
            m_index == otherMission.m_index &&
            m_SpacecraftHeader == otherMission.m_SpacecraftHeader &&
            m_OrbitHeader == otherMission.m_OrbitHeader &&
            m_InpSimHeader == otherMission.m_InpSimHeader &&
            m_FOVHeader == otherMission.m_FOVHeader &&
            m_InpIPCHeader == otherMission.m_InpIPCHeader &&
            m_graphisHeader == otherMission.m_graphisHeader &&
            m_inpTDRs == otherMission.m_inpTDRs &&
            m_regionHeader == otherMission.m_regionHeader;
}

void Mission::updateIndex()
{
    if (m_MissionHolder)
        m_index = m_MissionHolder->indexOfMission(this);
}

int Mission::numberOfSpacecraft() const
{
    if (m_SpacecraftHeader)
        return m_SpacecraftHeader->numberOfSpacecraft();
    return 0;
}

int Mission::numberOfOrbit() const
{
    if (m_OrbitHeader)
        return m_OrbitHeader->numberOfOrbit();
    return 0;
}

bool Mission::hasName(const QString &name)
{
    if (m_MissionHolder)
        return m_MissionHolder->hasMissionNameAs(name.trimmed());
    return false;
}

void Mission::rename(const QString &newName)
{
    if (!hasName(newName.trimmed())){
        m_name = newName.trimmed();
    }
}

bool Mission::createSpacecraft()
{
    return m_SpacecraftHeader->createSpacecraft();
}

bool Mission::removeSpacecraft(Spacecraft *SC)
{
    return m_SpacecraftHeader->removeSpacecraft(SC);
}

Spacecraft* Mission::spacecraft(const int &index)
{
    return m_SpacecraftHeader->spacecraft(index);
}

bool Mission::createOrbit()
{
    return m_OrbitHeader->createOrbit();
}

bool Mission::removeOrbit(Orbit* o)
{
    return m_OrbitHeader->removeOrbit(o);
}

Orbit* Mission::orbit(const int &index)
{
    return m_OrbitHeader->orbit(index);
}

QDataStream& operator<< (QDataStream& dataStream, const Mission& m)
{
    dataStream << m.m_name
               << *m.m_SpacecraftHeader
               << *m.m_OrbitHeader
               << *m.m_InpSimHeader
               << *m.m_FOVHeader
               << *m.m_InpIPCHeader
               << *m.m_graphisHeader
               << *m.m_inpTDRs
               << *m.m_regionHeader;
    return dataStream;
}
QDataStream& operator>> (QDataStream& dataStream, Mission& m)
{
    dataStream >> m.m_name
            >> m.m_SpacecraftHeaderObject
            >> m.m_OrbitHeaderObejct
            >> m.m_InpSimHeaderObject
            >> m.m_FOVHeaderObject
            >> m.m_InpIPCHeaderObject
            >> m.m_GraphisHeaderObject
            >> m.m_inpTDRsObject
            >> m.m_regionHeaderObject;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const Mission& m)
{
    dataStream << m.m_name
               << *m.m_SpacecraftHeader
               << *m.m_OrbitHeader
               << *m.m_InpSimHeader
               << *m.m_FOVHeader
               << *m.m_InpIPCHeader
               << *m.m_graphisHeader
               << *m.m_inpTDRs
               << *m.m_regionHeader;
    return dataStream;
}
