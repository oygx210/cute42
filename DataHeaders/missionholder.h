#ifndef MISSIONHOLDER_H
#define MISSIONHOLDER_H

#include <QVector>
#include <QVariant>
#include "ShareHeaders/qt42_sharedparameters.h"
#include "qt42baseclass.h"

class Mission;

class MissionHolder : public Qt42BaseClass
{
public:
    MissionHolder();
    MissionHolder(const MissionHolder& MH);
    ~MissionHolder() override;
    objectType type() const override {return m_type;}
    int indexOfMission(Mission* M) const;
    int numberOfMission()const {return m_qvecMissions.size();}
    int maxNumberDefaultMission() const;
    bool hasMissionNameAs(const QString& name);

    Mission* mission(const int& index);
    bool createMission();
    bool removeMission(Mission* M);

    MissionHolder& operator=(const MissionHolder& mh){return *this;}

private:
    const objectType m_type = MISSIONHOLDER;
    QVector<Mission*> m_qvecMissions;
};

Q_DECLARE_METATYPE(MissionHolder)
#endif // MISSIONHOLDER_H
