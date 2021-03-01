#include "DataHeaders/missionholder.h"
#include "DataHeaders/mission.h"
#include <QDebug>
MissionHolder::MissionHolder()
{
    Qt42BaseClass::changeType(m_type);
}

MissionHolder::MissionHolder(const MissionHolder& MH) : Qt42BaseClass(MH)
{
    m_qvecMissions = MH.m_qvecMissions;
}

MissionHolder::~MissionHolder()
{
    //qDeleteAll(m_qvecMissions);
}


int MissionHolder::indexOfMission(Mission* M) const
{
    if (m_qvecMissions.contains(M))
        return m_qvecMissions.indexOf(M);
    else
        return -1;
}

int MissionHolder::maxNumberDefaultMission() const
{
    int maxNumber = -1;
    for (Mission* M : m_qvecMissions)
    {
        QStringList list = M->name().trimmed().split("-");
        if (list[0]==M->defaultName)
        {
            if (maxNumber < list[1].toInt())
                maxNumber = list[1].toInt();
        }
    }
    return maxNumber;
}

bool MissionHolder::hasMissionNameAs(const QString &name)
{
    bool hasName = false;
    for (Mission* M: m_qvecMissions){
        if (M->name().trimmed() == name.trimmed()){
            hasName = true;
        }
    }
    return hasName;

}

Mission* MissionHolder::mission(const int &index)
{
    if (index > -1 && index < m_qvecMissions.size())
        return m_qvecMissions[index];
    return nullptr;
}

bool MissionHolder::createMission()
{
    Mission* M = new Mission(this);
    if (!m_qvecMissions.contains(M))
    {
        m_qvecMissions.append(M);
        for (Mission* M : m_qvecMissions)
            M->updateIndex();
        return true;
    }
    delete M;
    return false;
}

bool MissionHolder::removeMission(Mission* M)
{
    if(m_qvecMissions.contains(M)){
        m_qvecMissions.removeAll(M);
        for (Mission* M: m_qvecMissions)
            M->updateIndex();
        //delete M;
        return true;
    }
    return false;
}
