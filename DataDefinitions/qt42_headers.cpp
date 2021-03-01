#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/fieldofview.h"
#include "DataHeaders/mission.h"

#include <QDebug>

/*** SpacecraftHeader ***/

SpacecraftHeader::SpacecraftHeader(Mission* mission): m_mission(mission)
{
   changeType(m_type);
}

SpacecraftHeader::SpacecraftHeader(const SpacecraftHeader& SC_Header) : Qt42BaseClass(SC_Header)
{
    m_mission = SC_Header.m_mission;
    m_qvecSpacecraft = SC_Header.m_qvecSpacecraft;
    m_qvecSpacecraftObjects = SC_Header.m_qvecSpacecraftObjects;
}

SpacecraftHeader::~SpacecraftHeader()
{
   // qDeleteAll(m_qvecSpacecraft);
   // Poorly-defined destructor will cause QVariant::setValue(SpacecraftHeader) to fail;
}

SpacecraftHeader& SpacecraftHeader::operator=(const SpacecraftHeader &SC_Header)
{
    if (this == &SC_Header)
        return *this;
    m_mission = SC_Header.m_mission;
    m_qvecSpacecraft = SC_Header.m_qvecSpacecraft;
    m_qvecSpacecraftObjects = SC_Header.m_qvecSpacecraftObjects;
    return *this;
}

bool SpacecraftHeader::createSpacecraft()
{
    Spacecraft* SC = new Spacecraft(this);
    if (!m_qvecSpacecraft.contains(SC))
    {
        m_qvecSpacecraft.append(SC);
        for (Spacecraft* s : m_qvecSpacecraft)
            s->updateIndex();
        return true;
    }
    delete SC;
    return false;
}

bool SpacecraftHeader::removeSpacecraft(Spacecraft* SC)
{
    if (m_qvecSpacecraft.contains(SC))
    {
        m_qvecSpacecraft.removeAll(SC);
        //delete SC;   // Deleting the pointer casuses the application to crash.
        for (Spacecraft* sc: m_qvecSpacecraft)
            sc->updateIndex();
        return true;
    }
    return false;
}

bool SpacecraftHeader::hasSpacecraftNamedAs(const QString &name)
{
    bool hasName = false;
    for (Spacecraft* s : m_qvecSpacecraft)
    {
        if (s->name().trimmed() == name.trimmed())
            hasName = true;
    }
    return hasName;
}

int SpacecraftHeader::maxNumberDefaultSC() const
{
    int maxNumber = -1;
    for (Spacecraft* S : m_qvecSpacecraft)
    {
        QStringList list = S->name().trimmed().split("-");
        if (list[0]==S->defaultName)
        {
            if (maxNumber < list[1].toInt())
                maxNumber = list[1].toInt();
        }
    }
    return maxNumber;
}

Spacecraft* SpacecraftHeader::spacecraft(const int &index) const
{
    if (index > -1 && index < m_qvecSpacecraft.size())
        return m_qvecSpacecraft[index];
    return nullptr;
}

int SpacecraftHeader::indexSpacecraft(Spacecraft* SC)
{
    if (m_qvecSpacecraft.contains(SC))
        return m_qvecSpacecraft.indexOf(SC);
    return -1;
}


Mission* SpacecraftHeader::parentItem() const
{
    if (m_mission)
        return m_mission;
    else {
        return nullptr;
    }
}


void SpacecraftHeader::duplicate(const SpacecraftHeader &sch)
{
    m_qvecSpacecraftObjects.clear();
    int numberOfobjects = sch.m_qvecSpacecraftObjects.size();
    for (int i = 0; i < numberOfobjects; ++i)
    {
        Spacecraft scDuplicated = sch.m_qvecSpacecraftObjects[i];
        Spacecraft sc;
        sc.duplicate(scDuplicated);
        m_qvecSpacecraftObjects.append(sc);
    }
}

QDataStream& operator<< (QDataStream& dataStream, const SpacecraftHeader& sch)
{
    QVector<Spacecraft> qvecSC = QVector<Spacecraft>();
    for (Spacecraft* scp : sch.m_qvecSpacecraft)
    {
        Spacecraft sc = *scp;
        qvecSC.append(sc);
    }

    dataStream << qvecSC;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, SpacecraftHeader& sch)
{
    dataStream >> sch.m_qvecSpacecraftObjects;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const SpacecraftHeader& sch)
{
    QVector<Spacecraft> qvecSC = QVector<Spacecraft>();
    for (Spacecraft* scp : sch.m_qvecSpacecraft)
    {
        Spacecraft sc = *scp;
        qvecSC.append(sc);
    }

    dataStream << qvecSC;
    return dataStream;
}

/**     end     **/


OrbitHeader::OrbitHeader(Mission* mission): m_mission(mission)
{
    changeType(m_type);
}

OrbitHeader::OrbitHeader(const OrbitHeader& OH) : Qt42BaseClass(OH)
{
    m_mission = OH.m_mission;
    m_qvecOrbit = OH.m_qvecOrbit;
    m_qvecOrbitObjects = OH.m_qvecOrbitObjects;
}

OrbitHeader::~OrbitHeader()
{
}

OrbitHeader& OrbitHeader::operator=(const OrbitHeader &OH)
{
   if (this == &OH)
       return *this;
   m_mission = OH.m_mission;
   m_qvecOrbit = OH.m_qvecOrbit;
   m_qvecOrbitObjects = OH.m_qvecOrbitObjects;
   return *this;
}

bool OrbitHeader::createOrbit()
{
    Orbit* newOrbit = new Orbit(this);
    if (!m_qvecOrbit.contains(newOrbit)){
        m_qvecOrbit.append(newOrbit);
        for (Orbit* O : m_qvecOrbit)
            O->updateIndex();
        return true;
    }
    delete newOrbit;
    return false;
}
bool OrbitHeader::removeOrbit(Orbit* orbit)
{
    if (m_qvecOrbit.contains(orbit))
    {
        m_qvecOrbit.removeAll(orbit);
        //delete orbit;  // Deleting the pointer causes the application to crash.
        for (Orbit* o : m_qvecOrbit)
            o->updateIndex();
        return true;
    }
    return false;
}
bool OrbitHeader::hasOrbitNamedAs(const QString& name)
{
    bool hasName = false;
    for (Orbit* o : m_qvecOrbit)
    {
        if (o->name().trimmed() == name.trimmed())
            hasName = true;
    }
    return hasName;
}
int OrbitHeader::maxNumberDefaultOrbit() const
{
    int maxNumber = -1;
    for (Orbit* o : m_qvecOrbit)
    {
        if (o->name().trimmed().split("-")[0] == o->defaultName)
        {
            int defaultIndex = (o->name().trimmed().split("-")[1]).toInt();
            if (maxNumber < defaultIndex)
                maxNumber = defaultIndex;
        }
    }
    return maxNumber;
}

Orbit* OrbitHeader::orbit (const int& index) const
{
    if (index > -1 && index < m_qvecOrbit.size())
        return m_qvecOrbit[index];
    return nullptr;
}
int OrbitHeader::indexOrbit(Orbit* orbit)
{
    if (m_qvecOrbit.contains(orbit))
        return m_qvecOrbit.indexOf(orbit);
    return -1;
}

void OrbitHeader::duplicate(const OrbitHeader &oh)
{
    m_qvecOrbitObjects.clear();
    int numberOfObjects = oh.m_qvecOrbitObjects.size();
    for (int i = 0; i < numberOfObjects; ++i)
    {
        Orbit orbitDuplicated = oh.m_qvecOrbitObjects[i];
        Orbit o;
        o.duplicate(orbitDuplicated);
        m_qvecOrbitObjects.append(o);
    }
}

QDataStream& operator<< (QDataStream& dataStream, const OrbitHeader& oh)
{
    QVector<Orbit> qvecOrbit = QVector<Orbit>();
    for (int i = 0; i < oh.m_qvecOrbit.size(); ++i)
    {
        Orbit o = *oh.m_qvecOrbit[i];
        qvecOrbit.append(o);
    }
    dataStream << qvecOrbit;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, OrbitHeader& oh)
{
    dataStream >> oh.m_qvecOrbitObjects;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const OrbitHeader& oh)
{
    QVector<Orbit> qvecOrbit = QVector<Orbit>();
    for (int i = 0; i < oh.m_qvecOrbit.size(); ++i)
    {
        Orbit o = *oh.m_qvecOrbit[i];
        qvecOrbit.append(o);
    }
    dataStream << qvecOrbit;
    return dataStream;
}



/** InpSim Header **/
InpSimHeader::InpSimHeader(Mission* mission) : m_mission(mission)
{
    changeType(m_type);
    m_simulationcontrol = new InpSimSimulationControl(this);
    m_orbitSCSet = new InpSimOrbitSCSet(this);
    m_environment = new InpSimEnvironment(this, m_mission);
    m_celestialbody = new InpSimCelestialBody(this, m_mission);
    m_lagrangepointsystem = new InpSimLagrangePointSystem(this, m_mission);
    m_groupstation = new InpSimGroundStation(this, m_mission);
}

InpSimHeader::InpSimHeader(const InpSimHeader& inpsimheader) : Qt42BaseClass(inpsimheader)
{
    m_mission = inpsimheader.m_mission;
    m_simulationcontrol= inpsimheader.m_simulationcontrol;
    m_orbitSCSet = inpsimheader.m_orbitSCSet;
    m_environment = inpsimheader.m_environment;
    m_celestialbody = inpsimheader.m_celestialbody;
    m_lagrangepointsystem = inpsimheader.m_lagrangepointsystem;
    m_groupstation = inpsimheader.m_groupstation;
    m_simulationcontrolObject = inpsimheader.m_simulationcontrolObject;
    m_orbitSCSetObject = inpsimheader.m_orbitSCSetObject;
    m_environmentObject = inpsimheader.m_environmentObject;
    m_celestialbodyObject = inpsimheader.m_celestialbodyObject;
    m_lagrangepointsystemObject = inpsimheader.m_lagrangepointsystemObject;
    m_groupstationObject = inpsimheader.m_groupstationObject;
}

InpSimHeader& InpSimHeader::operator=(const InpSimHeader &inpsimheader)
{
    if (this == &inpsimheader)
        return *this;

    m_mission = inpsimheader.m_mission;
    m_simulationcontrol= inpsimheader.m_simulationcontrol;
    m_orbitSCSet = inpsimheader.m_orbitSCSet;
    m_environment = inpsimheader.m_environment;
    m_celestialbody = inpsimheader.m_celestialbody;
    m_lagrangepointsystem = inpsimheader.m_lagrangepointsystem;
    m_groupstation = inpsimheader.m_groupstation;
    m_simulationcontrolObject = inpsimheader.m_simulationcontrolObject;
    m_orbitSCSetObject = inpsimheader.m_orbitSCSetObject;
    m_environmentObject = inpsimheader.m_environmentObject;
    m_celestialbodyObject = inpsimheader.m_celestialbodyObject;
    m_lagrangepointsystemObject = inpsimheader.m_lagrangepointsystemObject;
    m_groupstationObject = inpsimheader.m_groupstationObject;
    return *this;
}

InpSimHeader::~InpSimHeader()
{

}

int InpSimHeader::indexSimulationControl() const
{
    if(m_simulationcontrol)
        return m_simulationcontrol->index();
    else
        return -1;
}

int InpSimHeader::indexOrbitSCset() const
{
    if (m_orbitSCSet)
        return m_orbitSCSet->index();
    else
        return -1;
}

int InpSimHeader::indexEnvironment() const
{
    if (m_environment)
        return m_environment->index();
    else
        return -1;
}
int InpSimHeader::indexCelestialBody() const
{
    if (m_celestialbody)
        return m_celestialbody->index();
    else
        return -1;
}
int InpSimHeader::indexLagrangePointSystem() const
{
    if (m_lagrangepointsystem)
        return m_lagrangepointsystem->index();
    else
        return -1;
}

int InpSimHeader::indexGroudStation() const
{
    if (m_groupstation)
        return m_groupstation->index();
    else
        return -1;
}

QDataStream& operator<< (QDataStream& dataStream, const InpSimHeader& ish)
{
    dataStream << *ish.m_simulationcontrol
               << *ish.m_orbitSCSet
               << *ish.m_environment
               << *ish.m_celestialbody
               << *ish.m_lagrangepointsystem
               << *ish.m_groupstation;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, InpSimHeader& ish)
{

    dataStream >> ish.m_simulationcontrolObject
               >> ish.m_orbitSCSetObject
               >> ish.m_environmentObject
               >> ish.m_celestialbodyObject
               >> ish.m_lagrangepointsystemObject
               >> ish.m_groupstationObject;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const InpSimHeader& ish)
{
    dataStream << *ish.m_simulationcontrol
               << *ish.m_orbitSCSet
               << *ish.m_environment
               << *ish.m_celestialbody
               << *ish.m_lagrangepointsystem
               << *ish.m_groupstation;
    return dataStream;
}


/** FOV header **/
FOVHeader::FOVHeader(Mission* mission) : m_mission(mission)
{
    changeType(m_type);
}

FOVHeader::~FOVHeader()
{

}

FOVHeader::FOVHeader(const FOVHeader& fovh) : Qt42BaseClass(fovh)
{
    m_mission = fovh.m_mission;
    qvecFieldsOfView = fovh.qvecFieldsOfView;
}

FOVHeader& FOVHeader::operator=(const FOVHeader &fovh)
{
    if (this == &fovh)
        return *this;
    m_mission = fovh.m_mission;
    qvecFieldsOfView = fovh.qvecFieldsOfView;
    return *this;
}

void FOVHeader::createFOV()
{
    FieldOfView fov;
    int index = 0;
    for (FieldOfView f : qvecFieldsOfView)
    {
        QString label = f.label().trimmed();
        QStringList stringListLabel = label.split("-");
        if (stringListLabel[0].trimmed()==fov.defaultName)
        {
            if (index <= stringListLabel[1].toInt())
                index = stringListLabel[1].toInt() + 1;
        }

    }
    fov.rename(fov.defaultName+"-"+QString::number(index));
    qvecFieldsOfView.append(fov);
}

QDataStream& operator<<(QDataStream& dataStream, const FOVHeader& fovh)
{
    dataStream << fovh.qvecFieldsOfView;
    return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, FOVHeader& fovh)
{
    fovh.qvecFieldsOfView.clear();
    dataStream >> fovh.qvecFieldsOfView;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const FOVHeader& fovh)
{
    dataStream << fovh.qvecFieldsOfView;
    return dataStream;
}



/** InpIPCHeader **/
InpIPCHeader::InpIPCHeader(Mission* mission) : m_mission(mission)
{
    changeType(m_type);
}

InpIPCHeader::~InpIPCHeader()
{

}

InpIPCHeader::InpIPCHeader(const InpIPCHeader& iiph) : Qt42BaseClass(iiph)
{
    m_mission = iiph.m_mission;
    m_qvecInpIpc = iiph.m_qvecInpIpc;
}

InpIPCHeader& InpIPCHeader::operator=(const InpIPCHeader& iiph)
{
    if (this == &iiph)
        return *this;
    m_mission = iiph.m_mission;
    m_qvecInpIpc = iiph.m_qvecInpIpc;
    return *this;
}

void InpIPCHeader::createNewIPC()
{
    int maxIndex = 0;
    for (int i = 0; i < m_qvecInpIpc.size(); ++i)
    {
        QStringList nameList = m_qvecInpIpc[i].name().trimmed().split(" ");
        int index = nameList[1].toInt();
        if (maxIndex <= index){
            maxIndex = index+1;
        }
    }
    Inp_IPC newInp_Ipc;
    newInp_Ipc.setIndex(maxIndex);
    m_qvecInpIpc.append(newInp_Ipc);


}

void InpIPCHeader::removeIPC(const QString& name)
{
    for (int i = 0; i < m_qvecInpIpc.size(); ++i)
    {
        Inp_IPC& inpipc = m_qvecInpIpc[i];
        if (inpipc.name().trimmed() == name.trimmed())
        {
            m_qvecInpIpc.remove(i);
            --i;
        }
    }
}

void InpIPCHeader::removeIPC(const int &index)
{
    if (index<= -1 || index >= m_qvecInpIpc.size())
        return;
    m_qvecInpIpc.remove(index);
}

void InpIPCHeader::editIPC(const QString& name, const Inp_IPC& newInp_IPC)
{
    for (int i = 0; i < m_qvecInpIpc.size(); ++i)
    {
        if (m_qvecInpIpc[i].name().trimmed() == name.trimmed())
            m_qvecInpIpc[i] = newInp_IPC;
    }
}

void InpIPCHeader::editIPC(const int& index, const Inp_IPC& newInp_IPC)
{
    if (index <= -1 || index >= m_qvecInpIpc.size())
        return;
    m_qvecInpIpc[index] = newInp_IPC;
}

QDataStream& operator<<(QDataStream& dataStream, const InpIPCHeader& iiph)
{
    dataStream << iiph.m_qvecInpIpc;
    return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, InpIPCHeader& iiph)
{
    dataStream >> iiph.m_qvecInpIpc;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const InpIPCHeader& iiph)
{
    dataStream << iiph.m_qvecInpIpc;
    return dataStream;
}

/** Graphics Header **/
GraphicsHeader::GraphicsHeader(Mission* mission) : m_mission(mission)
{
    changeType(m_type);
}

GraphicsHeader::~GraphicsHeader()
{

}

GraphicsHeader::GraphicsHeader(const GraphicsHeader& gh) : Qt42BaseClass(gh)
{
    m_mission = gh.m_mission;
    m_GLOutputInterval = gh.m_GLOutputInterval;
    m_starCatalogFileName = gh.m_starCatalogFileName;
    m_mapWindowExists = gh.m_mapWindowExists;
    m_orreryWindowExists = gh.m_orreryWindowExists;
    m_unitSphereWindowExists = gh.m_unitSphereWindowExists;
    m_pauseAtStartup = gh.m_pauseAtStartup;
    m_povMode = gh.m_povMode;
    m_hostType = gh.m_hostType;
    m_initialHostSC = gh.m_initialHostSC;
    m_initialHostBody = gh.m_initialHostBody;
    m_initialHostPOVFrame = gh.m_initialHostPOVFrame;
    m_targetType = gh.m_targetType;
    m_initialTargetSC = gh.m_initialTargetSC;
    m_initialTargetBody = gh.m_initialTargetBody;
    m_initialTargetPOVFrame = gh.m_initialTargetPOVFrame;
    m_boresightAxis = gh.m_boresightAxis;
    m_upAxis = gh.m_upAxis;
    m_initialPOVrangeFromTarget = gh.m_initialPOVrangeFromTarget;
    m_povAngleVertical = gh.m_povAngleVertical;
    m_povPositionInHost = gh.m_povPositionInHost;
    m_InitialPOVView = gh.m_InitialPOVView;
    m_camTitle = gh.m_camTitle;
    m_camWidthHeight = gh.m_camWidthHeight;
    m_camMouseScaleFactor = gh.m_camMouseScaleFactor;
    m_displayGammaExponent = gh.m_displayGammaExponent;
    m_camShowMenu_N_Axes = gh.m_camShowMenu_N_Axes;
    m_camShowMenu_L_Axes = gh.m_camShowMenu_L_Axes;
    m_camShowMenu_F_Axes = gh.m_camShowMenu_F_Axes;
    m_camShowMenu_B_Axes = gh.m_camShowMenu_B_Axes;
    m_camShowMenu_N_Grid = gh.m_camShowMenu_N_Grid;
    m_camShowMenu_L_Grid = gh.m_camShowMenu_L_Grid;
    m_camShowMenu_F_Grid = gh.m_camShowMenu_F_Grid;
    m_camShowMenu_B_Grid = gh.m_camShowMenu_B_Grid;
    m_camShowMenu_Gal_Grid = gh.m_camShowMenu_Gal_Grid;
    m_camShowMenu_FOVs = gh.m_camShowMenu_FOVs;
    m_camShowMenu_ProxOps = gh.m_camShowMenu_ProxOps;
    m_camShowMenu_TDRS = gh.m_camShowMenu_TDRS;
    m_camShowMenu_Shadows = gh.m_camShowMenu_Shadows;
    m_camShowMenu_AstroLabels = gh.m_camShowMenu_AstroLabels;
    m_camShowMenu_TruthVectors = gh.m_camShowMenu_TruthVectors;
    m_camShowMenu_FSWVectors = gh.m_camShowMenu_FSWVectors;
    m_camShowMenu_MilkyWay = gh.m_camShowMenu_MilkyWay;
    m_camShowMenu_FermiSky = gh.m_camShowMenu_FermiSky;
    m_mapMapTitle = gh.m_mapMapTitle;
    m_mapWidthHeight = gh.m_mapWidthHeight;
    m_mapShowMenuClock = gh.m_mapShowMenuClock;
    m_mapShowMenuTlmClock = gh.m_mapShowMenuTlmClock;
    m_mapShowMenuCredits = gh.m_mapShowMenuCredits;
    m_mapShowMenuNight = gh.m_mapShowMenuNight;
    m_unitSphereShowMenuMajor = gh.m_unitSphereShowMenuMajor;
    m_unitSphereShowMenuZodiac = gh.m_unitSphereShowMenuZodiac;
    m_unitShpereShowMenuMinor = gh.m_unitShpereShowMenuMinor;
}

GraphicsHeader& GraphicsHeader::operator=(const GraphicsHeader& gh)
{
    if (this == &gh)
        return *this;
    m_mission = gh.m_mission;
    m_GLOutputInterval = gh.m_GLOutputInterval;
    m_starCatalogFileName = gh.m_starCatalogFileName;
    m_mapWindowExists = gh.m_mapWindowExists;
    m_orreryWindowExists = gh.m_orreryWindowExists;
    m_unitSphereWindowExists = gh.m_unitSphereWindowExists;
    m_pauseAtStartup = gh.m_pauseAtStartup;
    m_povMode = gh.m_povMode;
    m_hostType = gh.m_hostType;
    m_initialHostSC = gh.m_initialHostSC;
    m_initialHostBody = gh.m_initialHostBody;
    m_initialHostPOVFrame = gh.m_initialHostPOVFrame;
    m_targetType = gh.m_targetType;
    m_initialTargetSC = gh.m_initialTargetSC;
    m_initialTargetBody = gh.m_initialTargetBody;
    m_initialTargetPOVFrame = gh.m_initialTargetPOVFrame;
    m_boresightAxis = gh.m_boresightAxis;
    m_upAxis = gh.m_upAxis;
    m_initialPOVrangeFromTarget = gh.m_initialPOVrangeFromTarget;
    m_povAngleVertical = gh.m_povAngleVertical;
    m_povPositionInHost = gh.m_povPositionInHost;
    m_InitialPOVView = gh.m_InitialPOVView;
    m_camTitle = gh.m_camTitle;
    m_camWidthHeight = gh.m_camWidthHeight;
    m_camMouseScaleFactor = gh.m_camMouseScaleFactor;
    m_displayGammaExponent = gh.m_displayGammaExponent;
    m_camShowMenu_N_Axes = gh.m_camShowMenu_N_Axes;
    m_camShowMenu_L_Axes = gh.m_camShowMenu_L_Axes;
    m_camShowMenu_F_Axes = gh.m_camShowMenu_F_Axes;
    m_camShowMenu_B_Axes = gh.m_camShowMenu_B_Axes;
    m_camShowMenu_N_Grid = gh.m_camShowMenu_N_Grid;
    m_camShowMenu_L_Grid = gh.m_camShowMenu_L_Grid;
    m_camShowMenu_F_Grid = gh.m_camShowMenu_F_Grid;
    m_camShowMenu_B_Grid = gh.m_camShowMenu_B_Grid;
    m_camShowMenu_Gal_Grid = gh.m_camShowMenu_Gal_Grid;
    m_camShowMenu_FOVs = gh.m_camShowMenu_FOVs;
    m_camShowMenu_ProxOps = gh.m_camShowMenu_ProxOps;
    m_camShowMenu_TDRS = gh.m_camShowMenu_TDRS;
    m_camShowMenu_Shadows = gh.m_camShowMenu_Shadows;
    m_camShowMenu_AstroLabels = gh.m_camShowMenu_AstroLabels;
    m_camShowMenu_TruthVectors = gh.m_camShowMenu_TruthVectors;
    m_camShowMenu_FSWVectors = gh.m_camShowMenu_FSWVectors;
    m_camShowMenu_MilkyWay = gh.m_camShowMenu_MilkyWay;
    m_camShowMenu_FermiSky = gh.m_camShowMenu_FermiSky;
    m_mapMapTitle = gh.m_mapMapTitle;
    m_mapWidthHeight = gh.m_mapWidthHeight;
    m_mapShowMenuClock = gh.m_mapShowMenuClock;
    m_mapShowMenuTlmClock = gh.m_mapShowMenuTlmClock;
    m_mapShowMenuCredits = gh.m_mapShowMenuCredits;
    m_mapShowMenuNight = gh.m_mapShowMenuNight;
    m_unitSphereShowMenuMajor = gh.m_unitSphereShowMenuMajor;
    m_unitSphereShowMenuZodiac = gh.m_unitSphereShowMenuZodiac;
    m_unitShpereShowMenuMinor = gh.m_unitShpereShowMenuMinor;
    return *this;
}

void GraphicsHeader::duplicate(const GraphicsHeader &gh)
{
    m_GLOutputInterval = gh.m_GLOutputInterval;
    m_starCatalogFileName = gh.m_starCatalogFileName;
    m_mapWindowExists = gh.m_mapWindowExists;
    m_orreryWindowExists = gh.m_orreryWindowExists;
    m_unitSphereWindowExists = gh.m_unitSphereWindowExists;
    m_pauseAtStartup = gh.m_pauseAtStartup;
    m_povMode = gh.m_povMode;
    m_hostType = gh.m_hostType;
    m_initialHostSC = gh.m_initialHostSC;
    m_initialHostBody = gh.m_initialHostBody;
    m_initialHostPOVFrame = gh.m_initialHostPOVFrame;
    m_targetType = gh.m_targetType;
    m_initialTargetSC = gh.m_initialTargetSC;
    m_initialTargetBody = gh.m_initialTargetBody;
    m_initialTargetPOVFrame = gh.m_initialTargetPOVFrame;
    m_boresightAxis = gh.m_boresightAxis;
    m_upAxis = gh.m_upAxis;
    m_initialPOVrangeFromTarget = gh.m_initialPOVrangeFromTarget;
    m_povAngleVertical = gh.m_povAngleVertical;
    m_povPositionInHost = gh.m_povPositionInHost;
    m_InitialPOVView = gh.m_InitialPOVView;
    m_camTitle = gh.m_camTitle;
    m_camWidthHeight = gh.m_camWidthHeight;
    m_camMouseScaleFactor = gh.m_camMouseScaleFactor;
    m_displayGammaExponent = gh.m_displayGammaExponent;
    m_camShowMenu_N_Axes = gh.m_camShowMenu_N_Axes;
    m_camShowMenu_L_Axes = gh.m_camShowMenu_L_Axes;
    m_camShowMenu_F_Axes = gh.m_camShowMenu_F_Axes;
    m_camShowMenu_B_Axes = gh.m_camShowMenu_B_Axes;
    m_camShowMenu_N_Grid = gh.m_camShowMenu_N_Grid;
    m_camShowMenu_L_Grid = gh.m_camShowMenu_L_Grid;
    m_camShowMenu_F_Grid = gh.m_camShowMenu_F_Grid;
    m_camShowMenu_B_Grid = gh.m_camShowMenu_B_Grid;
    m_camShowMenu_Gal_Grid = gh.m_camShowMenu_Gal_Grid;
    m_camShowMenu_FOVs = gh.m_camShowMenu_FOVs;
    m_camShowMenu_ProxOps = gh.m_camShowMenu_ProxOps;
    m_camShowMenu_TDRS = gh.m_camShowMenu_TDRS;
    m_camShowMenu_Shadows = gh.m_camShowMenu_Shadows;
    m_camShowMenu_AstroLabels = gh.m_camShowMenu_AstroLabels;
    m_camShowMenu_TruthVectors = gh.m_camShowMenu_TruthVectors;
    m_camShowMenu_FSWVectors = gh.m_camShowMenu_FSWVectors;
    m_camShowMenu_MilkyWay = gh.m_camShowMenu_MilkyWay;
    m_camShowMenu_FermiSky = gh.m_camShowMenu_FermiSky;
    m_mapMapTitle = gh.m_mapMapTitle;
    m_mapWidthHeight = gh.m_mapWidthHeight;
    m_mapShowMenuClock = gh.m_mapShowMenuClock;
    m_mapShowMenuTlmClock = gh.m_mapShowMenuTlmClock;
    m_mapShowMenuCredits = gh.m_mapShowMenuCredits;
    m_mapShowMenuNight = gh.m_mapShowMenuNight;
    m_unitSphereShowMenuMajor = gh.m_unitSphereShowMenuMajor;
    m_unitSphereShowMenuZodiac = gh.m_unitSphereShowMenuZodiac;
    m_unitShpereShowMenuMinor = gh.m_unitShpereShowMenuMinor;
}

void GraphicsHeader::edit(const double &GLOutputInterval,
                          const QString &starCatalogFileName,
                          const bool &mapWindowExists,
                          const bool &orreryWindowExists,
                          const bool &unitSphereWindowExists,
                          const bool &pauseAtStartup,
                          const QString &povMode,
                          const QString &hostType,
                          const int &initialHostSC,
                          const int &initialHostBody,
                          const QString &initialHostPOVFrame,
                          const QString &targetType,
                          const int &initialTargetSC,
                          const int &initialTargetBody,
                          const QString &initialTargetPOVFrame,
                          const QString &boresightAxis,
                          const QString &upAxis,
                          const double &initialPOVrangeFromTarget,
                          const double &povAngleVertical,
                          const QVector<double> &povPositionInHost,
                          const QString &InitialPOVView,
                          const QString &camTitle,
                          const QPair<int,int> &camWidthHeight,
                          const double &camMouseScaleFactor,
                          const double &displayGammaExponent,
                          const bool &camShowMenu_N_Axes,
                          const bool &camShowMenu_L_Axes,
                          const bool &camShowMenu_F_Axes,
                          const bool &camShowMenu_B_Axes,
                          const bool &camShowMenu_N_Grid,
                          const bool &camShowMenu_L_Grid,
                          const bool &camShowMenu_F_Grid,
                          const bool &camShowMenu_B_Grid,
                          const bool &camShowMenu_Gal_Grid,
                          const bool &camShowMenu_FOVs,
                          const bool &camShowMenu_ProxOps,
                          const bool &camShowMenu_TDRS,
                          const bool &camShowMenu_Shadows,
                          const bool &camShowMenu_AstroLabels,
                          const bool &camShowMenu_TruthVectors,
                          const bool &camShowMenu_FSWVectors,
                          const bool &camShowMenu_MilkyWay,
                          const bool &camShowMenu_FermiSky,
                          const QString &mapMapTitle,
                          const QPair <int,int> &mapWidthHeight,
                          const bool &mapShowMenuClock,
                          const bool &mapShowMenuTlmClock,
                          const bool &mapShowMenuCredits,
                          const bool &mapShowMenuNight,
                          const bool &unitSphereShowMenuMajor,
                          const bool &unitSphereShowMenuZodiac,
                          const bool &unitShpereShowMenuMinor)
{
    m_povPositionInHost.clear();

    m_GLOutputInterval = GLOutputInterval;
    m_starCatalogFileName = starCatalogFileName;
    m_mapWindowExists = mapWindowExists;
    m_orreryWindowExists = orreryWindowExists;
    m_unitSphereWindowExists = unitSphereWindowExists;
    m_pauseAtStartup = pauseAtStartup;
    m_povMode = povMode;
    m_hostType = hostType;
    m_initialHostSC = initialHostSC;
    m_initialHostBody = initialHostBody;
    m_initialHostPOVFrame = initialHostPOVFrame;
    m_targetType = targetType;
    m_initialTargetSC = initialTargetSC;
    m_initialTargetBody = initialTargetBody;
    m_initialTargetPOVFrame = initialTargetPOVFrame;
    m_boresightAxis = boresightAxis;
    m_upAxis = upAxis;
    m_initialPOVrangeFromTarget = initialPOVrangeFromTarget;
    m_povAngleVertical = povAngleVertical;
    m_povPositionInHost = povPositionInHost;
    m_InitialPOVView = InitialPOVView;
    m_camTitle = camTitle;
    m_camWidthHeight = camWidthHeight;
    m_camMouseScaleFactor = camMouseScaleFactor;
    m_displayGammaExponent = displayGammaExponent;
    m_camShowMenu_N_Axes = camShowMenu_N_Axes;
    m_camShowMenu_L_Axes = camShowMenu_L_Axes;
    m_camShowMenu_F_Axes = camShowMenu_F_Axes;
    m_camShowMenu_B_Axes = camShowMenu_B_Axes;
    m_camShowMenu_N_Grid = camShowMenu_N_Grid;
    m_camShowMenu_L_Grid = camShowMenu_L_Grid;
    m_camShowMenu_F_Grid = camShowMenu_F_Grid;
    m_camShowMenu_B_Grid = camShowMenu_B_Grid;
    m_camShowMenu_Gal_Grid = camShowMenu_Gal_Grid;
    m_camShowMenu_FOVs = camShowMenu_FOVs;
    m_camShowMenu_ProxOps = camShowMenu_ProxOps;
    m_camShowMenu_TDRS = camShowMenu_TDRS;
    m_camShowMenu_Shadows = camShowMenu_Shadows;
    m_camShowMenu_AstroLabels = camShowMenu_AstroLabels;
    m_camShowMenu_TruthVectors = camShowMenu_TruthVectors;
    m_camShowMenu_FSWVectors = camShowMenu_FSWVectors;
    m_camShowMenu_MilkyWay = camShowMenu_MilkyWay;
    m_camShowMenu_FermiSky = camShowMenu_FermiSky;
    m_mapMapTitle = mapMapTitle;
    m_mapWidthHeight = mapWidthHeight;
    m_mapShowMenuClock = mapShowMenuClock;
    m_mapShowMenuTlmClock = mapShowMenuTlmClock;
    m_mapShowMenuCredits = mapShowMenuCredits;
    m_mapShowMenuNight = mapShowMenuNight;
    m_unitSphereShowMenuMajor = unitSphereShowMenuMajor;
    m_unitSphereShowMenuZodiac = unitSphereShowMenuZodiac;
    m_unitShpereShowMenuMinor = unitShpereShowMenuMinor;
}


QDataStream& operator<<(QDataStream& dataStream, const GraphicsHeader& gh)
{
    dataStream << gh.m_GLOutputInterval
               << gh.m_starCatalogFileName
               << gh.m_mapWindowExists
               << gh.m_orreryWindowExists
               << gh.m_unitSphereWindowExists
               << gh.m_pauseAtStartup
               << gh.m_povMode
               << gh.m_hostType
               << gh.m_initialHostSC
               << gh.m_initialHostBody
               << gh.m_initialHostPOVFrame
               << gh.m_targetType
               << gh.m_initialTargetSC
               << gh.m_initialTargetBody
               << gh.m_initialTargetPOVFrame
               << gh.m_boresightAxis
               << gh.m_upAxis
               << gh.m_initialPOVrangeFromTarget
               << gh.m_povAngleVertical
               << gh.m_povPositionInHost
               << gh.m_InitialPOVView
               << gh.m_camTitle
               << gh.m_camWidthHeight
               << gh.m_camMouseScaleFactor
               << gh.m_displayGammaExponent
               << gh.m_camShowMenu_N_Axes
               << gh.m_camShowMenu_L_Axes
               << gh.m_camShowMenu_F_Axes
               << gh.m_camShowMenu_B_Axes
               << gh.m_camShowMenu_N_Grid
               << gh.m_camShowMenu_L_Grid
               << gh.m_camShowMenu_F_Grid
               << gh.m_camShowMenu_B_Grid
               << gh.m_camShowMenu_Gal_Grid
               << gh.m_camShowMenu_FOVs
               << gh.m_camShowMenu_ProxOps
               << gh.m_camShowMenu_TDRS
               << gh.m_camShowMenu_Shadows
               << gh.m_camShowMenu_AstroLabels
               << gh.m_camShowMenu_TruthVectors
               << gh.m_camShowMenu_FSWVectors
               << gh.m_camShowMenu_MilkyWay
               << gh.m_camShowMenu_FermiSky
               << gh.m_mapMapTitle
               << gh.m_mapWidthHeight
               << gh.m_mapShowMenuClock
               << gh.m_mapShowMenuTlmClock
               << gh.m_mapShowMenuCredits
               << gh.m_mapShowMenuNight
               << gh.m_unitSphereShowMenuMajor
               << gh.m_unitSphereShowMenuZodiac
               << gh.m_unitShpereShowMenuMinor;
    return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, GraphicsHeader& gh)
{
    dataStream >> gh.m_GLOutputInterval
               >> gh.m_starCatalogFileName
               >> gh.m_mapWindowExists
               >> gh.m_orreryWindowExists
               >> gh.m_unitSphereWindowExists
               >> gh.m_pauseAtStartup
               >> gh.m_povMode
               >> gh.m_hostType
               >> gh.m_initialHostSC
               >> gh.m_initialHostBody
               >> gh.m_initialHostPOVFrame
               >> gh.m_targetType
               >> gh.m_initialTargetSC
               >> gh.m_initialTargetBody
               >> gh.m_initialTargetPOVFrame
               >> gh.m_boresightAxis
               >> gh.m_upAxis
               >> gh.m_initialPOVrangeFromTarget
               >> gh.m_povAngleVertical
               >> gh.m_povPositionInHost
               >> gh.m_InitialPOVView
               >> gh.m_camTitle
               >> gh.m_camWidthHeight
               >> gh.m_camMouseScaleFactor
               >> gh.m_displayGammaExponent
               >> gh.m_camShowMenu_N_Axes
               >> gh.m_camShowMenu_L_Axes
               >> gh.m_camShowMenu_F_Axes
               >> gh.m_camShowMenu_B_Axes
               >> gh.m_camShowMenu_N_Grid
               >> gh.m_camShowMenu_L_Grid
               >> gh.m_camShowMenu_F_Grid
               >> gh.m_camShowMenu_B_Grid
               >> gh.m_camShowMenu_Gal_Grid
               >> gh.m_camShowMenu_FOVs
               >> gh.m_camShowMenu_ProxOps
               >> gh.m_camShowMenu_TDRS
               >> gh.m_camShowMenu_Shadows
               >> gh.m_camShowMenu_AstroLabels
               >> gh.m_camShowMenu_TruthVectors
               >> gh.m_camShowMenu_FSWVectors
               >> gh.m_camShowMenu_MilkyWay
               >> gh.m_camShowMenu_FermiSky
               >> gh.m_mapMapTitle
               >> gh.m_mapWidthHeight
               >> gh.m_mapShowMenuClock
               >> gh.m_mapShowMenuTlmClock
               >> gh.m_mapShowMenuCredits
               >> gh.m_mapShowMenuNight
               >> gh.m_unitSphereShowMenuMajor
               >> gh.m_unitSphereShowMenuZodiac
               >> gh.m_unitShpereShowMenuMinor;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const GraphicsHeader& gh)
{
    dataStream << gh.m_GLOutputInterval
               << gh.m_starCatalogFileName
               << gh.m_mapWindowExists
               << gh.m_orreryWindowExists
               << gh.m_unitSphereWindowExists
               << gh.m_pauseAtStartup
               << gh.m_povMode
               << gh.m_hostType
               << gh.m_initialHostSC
               << gh.m_initialHostBody
               << gh.m_initialHostPOVFrame
               << gh.m_targetType
               << gh.m_initialTargetSC
               << gh.m_initialTargetBody
               << gh.m_initialTargetPOVFrame
               << gh.m_boresightAxis
               << gh.m_upAxis
               << gh.m_initialPOVrangeFromTarget
               << gh.m_povAngleVertical
               << gh.m_povPositionInHost
               << gh.m_InitialPOVView
               << gh.m_camTitle
               << gh.m_camWidthHeight
               << gh.m_camMouseScaleFactor
               << gh.m_displayGammaExponent
               << gh.m_camShowMenu_N_Axes
               << gh.m_camShowMenu_L_Axes
               << gh.m_camShowMenu_F_Axes
               << gh.m_camShowMenu_B_Axes
               << gh.m_camShowMenu_N_Grid
               << gh.m_camShowMenu_L_Grid
               << gh.m_camShowMenu_F_Grid
               << gh.m_camShowMenu_B_Grid
               << gh.m_camShowMenu_Gal_Grid
               << gh.m_camShowMenu_FOVs
               << gh.m_camShowMenu_ProxOps
               << gh.m_camShowMenu_TDRS
               << gh.m_camShowMenu_Shadows
               << gh.m_camShowMenu_AstroLabels
               << gh.m_camShowMenu_TruthVectors
               << gh.m_camShowMenu_FSWVectors
               << gh.m_camShowMenu_MilkyWay
               << gh.m_camShowMenu_FermiSky
               << gh.m_mapMapTitle
               << gh.m_mapWidthHeight
               << gh.m_mapShowMenuClock
               << gh.m_mapShowMenuTlmClock
               << gh.m_mapShowMenuCredits
               << gh.m_mapShowMenuNight
               << gh.m_unitSphereShowMenuMajor
               << gh.m_unitSphereShowMenuZodiac
               << gh.m_unitShpereShowMenuMinor;
    return dataStream;
}


/** Data for Inp TDRs **/

InpTDRs::InpTDRs(Mission* mission) : m_mission(mission)
{
    changeType(m_type);
}

InpTDRs::~InpTDRs()
{

}

InpTDRs::InpTDRs(const InpTDRs& inptdrs) : Qt42BaseClass(inptdrs)
{
    m_mission = inptdrs.m_mission;
    m_TDRS1 = inptdrs.m_TDRS1;
    m_TDRS2 = inptdrs.m_TDRS2;
    m_TDRS3 = inptdrs.m_TDRS3;
    m_TDRS4 = inptdrs.m_TDRS4;
    m_TDRS5 = inptdrs.m_TDRS5;
    m_TDRS6 = inptdrs.m_TDRS6;
    m_TDRS7 = inptdrs.m_TDRS7;
    m_TDRS8 = inptdrs.m_TDRS8;
    m_TDRS9 = inptdrs.m_TDRS9;
    m_TDRS10 = inptdrs.m_TDRS10;
}

InpTDRs& InpTDRs::operator=(const InpTDRs& inptdrs)
{
    if (this == &inptdrs)
        return *this;
    m_mission = inptdrs.m_mission;
    m_TDRS1 = inptdrs.m_TDRS1;
    m_TDRS2 = inptdrs.m_TDRS2;
    m_TDRS3 = inptdrs.m_TDRS3;
    m_TDRS4 = inptdrs.m_TDRS4;
    m_TDRS5 = inptdrs.m_TDRS5;
    m_TDRS6 = inptdrs.m_TDRS6;
    m_TDRS7 = inptdrs.m_TDRS7;
    m_TDRS8 = inptdrs.m_TDRS8;
    m_TDRS9 = inptdrs.m_TDRS9;
    m_TDRS10 = inptdrs.m_TDRS10;

    return *this;
}

void InpTDRs::duplicate(const InpTDRs& inptdrs)
{
    m_TDRS1 = inptdrs.m_TDRS1;
    m_TDRS2 = inptdrs.m_TDRS2;
    m_TDRS3 = inptdrs.m_TDRS3;
    m_TDRS4 = inptdrs.m_TDRS4;
    m_TDRS5 = inptdrs.m_TDRS5;
    m_TDRS6 = inptdrs.m_TDRS6;
    m_TDRS7 = inptdrs.m_TDRS7;
    m_TDRS8 = inptdrs.m_TDRS8;
    m_TDRS9 = inptdrs.m_TDRS9;
    m_TDRS10 = inptdrs.m_TDRS10;
}

void InpTDRs::edit(const QPair<bool,QString>& TDRS1,
                   const QPair<bool,QString>& TDRS2,
                   const QPair<bool,QString>& TDRS3,
                   const QPair<bool,QString>& TDRS4,
                   const QPair<bool,QString>& TDRS5,
                   const QPair<bool,QString>& TDRS6,
                   const QPair<bool,QString>& TDRS7,
                   const QPair<bool,QString>& TDRS8,
                   const QPair<bool,QString>& TDRS9,
                   const QPair<bool,QString>& TDRS10)
{
    m_TDRS1 = TDRS1;
    m_TDRS2 = TDRS2;
    m_TDRS3 = TDRS3;
    m_TDRS4 = TDRS4;
    m_TDRS5 = TDRS5;
    m_TDRS6 = TDRS6;
    m_TDRS7 = TDRS7;
    m_TDRS8 = TDRS8;
    m_TDRS9 = TDRS9;
    m_TDRS10 = TDRS10;
}

QDataStream& operator<<(QDataStream& dataStream, const InpTDRs& inptdrs)
{
    dataStream << inptdrs.m_TDRS1
               << inptdrs.m_TDRS2
               << inptdrs.m_TDRS3
               << inptdrs.m_TDRS4
               << inptdrs.m_TDRS5
               << inptdrs.m_TDRS6
               << inptdrs.m_TDRS7
               << inptdrs.m_TDRS8
               << inptdrs.m_TDRS9
               << inptdrs.m_TDRS10;
    return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, InpTDRs& inptdrs)
{
    dataStream >> inptdrs.m_TDRS1
               >> inptdrs.m_TDRS2
               >> inptdrs.m_TDRS3
               >> inptdrs.m_TDRS4
               >> inptdrs.m_TDRS5
               >> inptdrs.m_TDRS6
               >> inptdrs.m_TDRS7
               >> inptdrs.m_TDRS8
               >> inptdrs.m_TDRS9
               >> inptdrs.m_TDRS10;
    return dataStream;
}

QDebug operator<<(QDebug dataStream, const InpTDRs& inptdrs)
{
    dataStream << inptdrs.m_TDRS1
               << inptdrs.m_TDRS2
               << inptdrs.m_TDRS3
               << inptdrs.m_TDRS4
               << inptdrs.m_TDRS5
               << inptdrs.m_TDRS6
               << inptdrs.m_TDRS7
               << inptdrs.m_TDRS8
               << inptdrs.m_TDRS9
               << inptdrs.m_TDRS10;
    return dataStream;
}

/** end of Inp TDRs **/

/** Regions for Qt42 **/
RegionHeader::RegionHeader(Mission* mission) : m_mission(mission)
{
    changeType(m_type);
}

RegionHeader::~RegionHeader()
{

}

RegionHeader::RegionHeader(const RegionHeader& rgnh) : Qt42BaseClass(rgnh)
{
    m_mission = rgnh.m_mission;
    m_qvecRegions = rgnh.m_qvecRegions;
}

RegionHeader& RegionHeader::operator=(const RegionHeader &rgnh)
{
    if (this == &rgnh)
        return *this;
    m_mission = rgnh.m_mission;
    m_qvecRegions = rgnh.m_qvecRegions;
    return *this;
}

void RegionHeader::duplicate(const RegionHeader &rgnh)
{
    m_qvecRegions = rgnh.m_qvecRegions;
}

void RegionHeader::removeRegion(const int& index)
{
    if (index > -1 && index < m_qvecRegions.size()){
        m_qvecRegions.remove(index);
    }
    else
    {
        return;
    }
}

void RegionHeader::removeRegion(const QString& name)
{
    Qt42Region qt42r;
    for (Qt42Region rgn : m_qvecRegions)
    {
        if (rgn.name().trimmed() == name.trimmed()){
            qt42r = rgn;
            break;
        }
    }
    if (m_qvecRegions.contains(qt42r))
        m_qvecRegions.removeAll(qt42r);
    else
        return;
}

void RegionHeader::addRegion()
{
    Qt42Region qt42r;
    if (!numberOfRegions())
    {
        qt42r.edit(qt42r.exists() ,"Default Region-0", qt42r.world(), qt42r.PoswLla(),
                   qt42r.positionInWorld(), qt42r.lngLatAlt(), qt42r.ElasticityDampingFrictionCoef(),
                   qt42r.geometryFileName().trimmed());
        m_qvecRegions.append(qt42r);
        return;
    }

    else{
        int maxIndex = 0;
        for (int i = 0; i < numberOfRegions(); ++i)
        {
            if (this->region(i).name().trimmed().contains("Default Region-",Qt::CaseInsensitive))
            {
                QStringList list = this->region(i).name().trimmed().split("-");
                int index = list[1].toUInt();
                if (maxIndex <= index)
                    maxIndex = index+1;
            }
        }
        QString name = "Default Region-" + QString::number(maxIndex);
        qt42r.edit(qt42r.exists() , name , qt42r.world(), qt42r.PoswLla(),
                   qt42r.positionInWorld(), qt42r.lngLatAlt(), qt42r.ElasticityDampingFrictionCoef(),
                   qt42r.geometryFileName().trimmed());
        m_qvecRegions.append(qt42r);
        return;
    }

}

Qt42Region& RegionHeader::region(const int& index)
{
    return m_qvecRegions[index];
}

QDataStream& operator<< (QDataStream& dataStream, const RegionHeader& rgnh)
{
    dataStream << rgnh.m_qvecRegions;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, RegionHeader& rgnh)
{
    dataStream >> rgnh.m_qvecRegions;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const RegionHeader& rgnh)
{
    dataStream << rgnh.m_qvecRegions;
    return dataStream;
}

