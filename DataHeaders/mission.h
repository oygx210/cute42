#ifndef MISSION_H
#define MISSION_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QDataStream>
#include <QDebug>
#include "qt42baseclass.h"
#include "qt42_headers.h"

class SpacecraftHeader;
class OrbitHeader;
class MissionHolder;
class Spacecraft;
class Orbit;




class Mission : public Qt42BaseClass
{
public:
    Mission(MissionHolder* MH = nullptr);
    Mission(const Mission& otherMission);
    ~Mission() override;
    Mission& operator=(const Mission& otherMission);
    bool operator==(const Mission& otherMission) const;
    objectType type() const override { return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}

    void updateIndex();
    int numberOfSpacecraft() const;
    int numberOfOrbit() const;
    bool hasName(const QString& name);

    bool createSpacecraft();
    bool removeSpacecraft(Spacecraft* SC);
    Spacecraft* spacecraft(const int& index);

    bool createOrbit();
    bool removeOrbit(Orbit* SC);
    Orbit* orbit(const int& index);

    int numberOfHeaders() const {return m_numberOfHeaders;}

    const QString defaultName = "Default Mission";

    void rename(const QString& newName);
    void setDirectroy(const QString& dir) {m_directory = dir;}
    QString directory() const {return m_directory;}

    SpacecraftHeader* spacecraftheader() const {return m_SpacecraftHeader;}
    OrbitHeader* orbitheader() const {return m_OrbitHeader;}
    InpSimHeader* inpsimheader() const {return m_InpSimHeader;}
    FOVHeader* fOVHeader() {return m_FOVHeader;}
    InpIPCHeader* inpIpcHeader() const {return m_InpIPCHeader;}
    GraphicsHeader* graphisHeader() const {return m_graphisHeader;}
    InpTDRs* inpTDRs() const {return m_inpTDRs;}
    RegionHeader* regionHeader() const {return m_regionHeader;}

    /** void  "setMissionHolder(MissionHolder* mh)" and "void setIndex(const int& index)" are
     * for data seriaization (operator << and operator >>) **/
    void setMissionHolder(MissionHolder* mh) {m_MissionHolder = mh;}
    void setIndex(const int& index) {m_index = index;}
    SpacecraftHeader m_SpacecraftHeaderObject = SpacecraftHeader();
    OrbitHeader m_OrbitHeaderObejct = OrbitHeader();
    InpSimHeader m_InpSimHeaderObject = InpSimHeader();
    FOVHeader m_FOVHeaderObject = FOVHeader();
    InpIPCHeader m_InpIPCHeaderObject = InpIPCHeader();
    GraphicsHeader m_GraphisHeaderObject = GraphicsHeader();
    InpTDRs m_inpTDRsObject = InpTDRs();
    RegionHeader m_regionHeaderObject = RegionHeader();
    /** end **/

    friend QDataStream& operator<< (QDataStream& dataStream, const Mission& m);
    friend QDataStream& operator>> (QDataStream& dataStream, Mission& m);
    friend QDebug operator<< (QDebug dataStream, const Mission& m);


private:
    void changeType(const objectType& type) override
    {Qt42BaseClass::changeType(type);}

    const objectType m_type = MISSION;
    QString m_name  = "Mission"; // the name of the mission;
    QString m_directory = QString();
    int m_index = -1;  // the index of the mission;
    MissionHolder* m_MissionHolder = nullptr;
    SpacecraftHeader* m_SpacecraftHeader = nullptr;
    OrbitHeader* m_OrbitHeader = nullptr;
    InpSimHeader* m_InpSimHeader = nullptr;
    FOVHeader* m_FOVHeader = nullptr;
    InpIPCHeader* m_InpIPCHeader = nullptr;
    GraphicsHeader* m_graphisHeader = nullptr;
    InpTDRs* m_inpTDRs = nullptr;
    RegionHeader* m_regionHeader = nullptr;
    int m_numberOfHeaders = 5;



};

Q_DECLARE_METATYPE(Mission);

#endif // MISSION_H
