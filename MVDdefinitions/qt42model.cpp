#include "MVDheaders/qt42model.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "DataHeaders/missionholder.h"
#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/spacecraft.h"
#include "DataHeaders/orbittype.h"
#include "DataHeaders/spacecraftcomponents.h"
#include "DataHeaders/inpsimterms.h"
#include <QDebug>
#include <QIcon>
#include <typeinfo>

Qt42Model::Qt42Model()
{
    m_MissionHolder = new MissionHolder;
    setUpModel();
}

Qt42Model::~Qt42Model()
{
    delete m_MissionHolder;
}

QModelIndex Qt42Model::parent(const QModelIndex &index) const
{
    /*if (!index.isValid())
        return QModelIndex();
        */

    Qt42BaseClass* Qt42BC  = static_cast<Qt42BaseClass*>(index.internalPointer());

    return parentByType(Qt42BC);
}

QModelIndex Qt42Model::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        if (row < 0 || row > m_MissionHolder->numberOfMission() || column != missionColumn)
            return QModelIndex();
        return createIndex(row, 0, m_MissionHolder->mission(row));
    }
    Qt42BaseClass* Qt42BC = static_cast<Qt42BaseClass*>(parent.internalPointer());
    return indexByType(row, column, Qt42BC);
}

QVariant Qt42Model::data(const QModelIndex &index, int role) const
{
    //if (role != Qt::DisplayRole)
    //    return QVariant();
    if (!index.isValid())
    {
        QVariant V = QVariant();
        V.setValue(*m_MissionHolder);
        return V;
    }
    Qt42BaseClass* Qt42BC = static_cast<Qt42BaseClass*>(index.internalPointer());
    if (role == Qt::DisplayRole)
    {
        return dataByType(Qt42BC);
    }
    if (role == Qt::DecorationRole)
        return iconByType(Qt42BC);
    return QVariant();
}


QVariant Qt42Model::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    Q_UNUSED(section)
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QVariant();

    return QVariant();
}

int Qt42Model::rowCount(const QModelIndex &parent) const
{
     if (!parent.isValid())
        return m_MissionHolder->numberOfMission();
    Qt42BaseClass* Qt42BC = static_cast<Qt42BaseClass*>(parent.internalPointer());
    return rowCountByType(Qt42BC);
}

int Qt42Model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 1;
    Qt42BaseClass* Qt42BC = static_cast<Qt42BaseClass*>(parent.internalPointer());
    return columnCountByType(Qt42BC);

}

bool Qt42Model::setData(const QModelIndex &index, const QVariant &data, int role)
{
    if (role != Qt::EditRole || !index.isValid())
        return false;
    setDataByType(index, data);
    emit dataChanged(index,index, {Qt::EditRole, Qt::DisplayRole});
    return true;
}

Qt::ItemFlags Qt42Model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}


void Qt42Model::setUpModel()
{
    m_MissionHolder->createMission(); /*
    m_MissionHolder->createMission();
    m_MissionHolder->createMission();*/
    m_MissionHolder->mission(0)->createSpacecraft();/*
    m_MissionHolder->mission(2)->createSpacecraft();
    m_MissionHolder->mission(2)->createSpacecraft();
    m_MissionHolder->mission(2)->createSpacecraft();*/

    m_MissionHolder->mission(0)->spacecraft(0)->createSpacecraftBody();
    m_MissionHolder->mission(0)->spacecraft(0)->createSpacecraftBody();
    m_MissionHolder->mission(0)->spacecraft(0)->createSpacecraftBody();
    m_MissionHolder->mission(0)->spacecraft(0)->createSpacecraftBody();
    m_MissionHolder->mission(0)->spacecraft(0)->createSpacecraftBody();
    m_MissionHolder->mission(0)->spacecraft(0)->createJoint();
    m_MissionHolder->mission(0)->spacecraft(0)->createWheel();
    m_MissionHolder->mission(0)->spacecraft(0)->createMagTorquer();
    m_MissionHolder->mission(0)->spacecraft(0)->createThruster();
    m_MissionHolder->mission(0)->spacecraft(0)->createGyroAxis();
    m_MissionHolder->mission(0)->spacecraft(0)->createMagnetometerAxis();
    m_MissionHolder->mission(0)->spacecraft(0)->createCoarseSunSensor();
    m_MissionHolder->mission(0)->spacecraft(0)->createFineSunSensor();
    m_MissionHolder->mission(0)->spacecraft(0)->createStarTracker();
    m_MissionHolder->mission(0)->spacecraft(0)->createGPSReceiver();
    m_MissionHolder->mission(0)->spacecraft(0)->createAccelerometer();

/*
    m_MissionHolder->mission(2)->createOrbit();

    m_MissionHolder->mission(1)->createOrbit();
    m_MissionHolder->mission(1)->createOrbit();*/
}

QModelIndex Qt42Model::parentByType(Qt42BaseClass *Qt42BC) const{
    if (Qt42BC->type() == MISSION)
       return QModelIndex();

    else if (Qt42BC->type() == SPACECRAFTHEADER)
    {
        SpacecraftHeader* SCH = static_cast<SpacecraftHeader*>(Qt42BC);
        return createIndex(SCH->parentItem()->index(), 0, SCH->parentItem());
    }

    else if (Qt42BC->type() == SPACECRAFT)
    {
        Spacecraft* SC = static_cast<Spacecraft*>( Qt42BC);
        return createIndex(SC->parentItem()->index(), 0, SC->parentItem());
    }

    else if (Qt42BC->type() == SPACECRAFTBODY)
    {
        SpacecraftBody* SCB = static_cast<SpacecraftBody*>(Qt42BC);
        return createIndex(SCB->parentItem()->index(), 0, SCB->parentItem());
    }

    else if (Qt42BC->type() == JOINT)
    {
        Joint* JNT = static_cast<Joint*>(Qt42BC);
        return createIndex(JNT->parentItem()->index(), 0, JNT->parentItem());
    }

    else if (Qt42BC->type() == WHEEL)
    {
        Wheel* WHL = static_cast<Wheel*>(Qt42BC);
        return createIndex(WHL->parentItem()->index(), 0, WHL->parentItem());
    }

    else if (Qt42BC->type() == MAGTORQUER)
    {
        MagTorquer* MTB = static_cast<MagTorquer*>(Qt42BC);
        return createIndex(MTB->parentItem()->index(), 0, MTB->parentItem());
    }

    else if (Qt42BC->type() == THRUSTER)
    {
        Thruster* THR = static_cast<Thruster*>(Qt42BC);
        return createIndex(THR->parentItem()->index(), 0, THR->parentItem());
    }

    else if (Qt42BC->type() == GYROAXIS)
    {
        GyroAxis* gyro = static_cast<GyroAxis*>(Qt42BC);
        return createIndex(gyro->parentItem()->index(), 0, gyro->parentItem());
    }


    else if (Qt42BC->type() == MAGNETOMETERAXIS)
    {
        MagnetometerAxis* mtAxis = static_cast<MagnetometerAxis*>(Qt42BC);
        return createIndex(mtAxis->parentItem()->index(), 0, mtAxis->parentItem());
    }

    else if (Qt42BC->type() == COARSESUNSENSOR)
    {
        CoarseSunSensor* CSS = static_cast<CoarseSunSensor*>(Qt42BC);
        return createIndex(CSS->parentItem()->index(), 0, CSS->parentItem());
    }

    else if (Qt42BC->type() == FINESUNSENSOR)
    {
        FineSunSensor* FSS = static_cast<FineSunSensor*>(Qt42BC);
        return createIndex(FSS->parentItem()->index(), 0, FSS->parentItem());
    }

    else if (Qt42BC->type() == STARTRACKER)
    {
        StarTracker* ST = static_cast<StarTracker*>(Qt42BC);
        return createIndex(ST->parentItem()->index(), 0, ST->parentItem());
    }

    else if (Qt42BC->type() == GPSRECEIVER)
    {
        GPSReceiver* gpsr = static_cast<GPSReceiver*>(Qt42BC);
        return createIndex(gpsr->parentItem()->index(), 0, gpsr->parentItem());
    }


    else if (Qt42BC->type() == ACCELEROMETER)
    {
        Accelerometer* accl = static_cast<Accelerometer*>(Qt42BC);
        return createIndex(accl->parentItem()->index(), 0, accl->parentItem());
    }

    else if (Qt42BC->type() == ORBITHEADER)
    {
        OrbitHeader* oh = static_cast<OrbitHeader*>(Qt42BC);
        return createIndex(oh->parentItem()->index(), 0, oh->parentItem());
    }

    else if (Qt42BC->type() == ORBIT)
    {
        Orbit* orbit = static_cast<Orbit*>(Qt42BC);
        return createIndex(orbit->parentItem()->index(), 0, orbit->parentItem());
    }

    else if (Qt42BC->type() == INPSIMHEADER)
    {
        InpSimHeader* ish = static_cast<InpSimHeader*>(Qt42BC);
        return createIndex(ish->parentItem()->index(), 0 , ish->parentItem());
    }

    else if (Qt42BC->type() == INPSIMSIMULATIONCONTROL)
    {
        InpSimSimulationControl* ishs = static_cast<InpSimSimulationControl*>(Qt42BC);
        return createIndex(ishs->parentItem()->index(), 0 , ishs->parentItem());
    }

    else if (Qt42BC->type() == INPSIMORBITSCSET)
    {
        InpSimOrbitSCSet* iosc = static_cast<InpSimOrbitSCSet*>(Qt42BC);
        return createIndex(iosc->parentItem()->index(), 0, iosc->parentItem());
    }

    else if (Qt42BC->type() == INPSIMENVIRONMENT)
    {
        InpSimEnvironment* ishe = static_cast<InpSimEnvironment*>(Qt42BC);
        return createIndex(ishe->parentItem()->index(), 0 , ishe->parentItem());
    }
    else if (Qt42BC->type() == INPSIMCELESTIALBODY)
    {
        InpSimCelestialBody* ishc = static_cast<InpSimCelestialBody*>(Qt42BC);
        return createIndex(ishc->parentItem()->index(), 0 , ishc->parentItem());
    }

    else if (Qt42BC->type() == INPSIMLAGRANGEPOINTSYSTEM)
    {
        InpSimLagrangePointSystem* ishl = static_cast<InpSimLagrangePointSystem*>(Qt42BC);
        return createIndex(ishl->parentItem()->index(), 0 , ishl->parentItem());
    }

    else if (Qt42BC->type() == INPSIMGROUNDSTATION)
    {
        InpSimGroundStation* ishg = static_cast<InpSimGroundStation*>(Qt42BC);
        return createIndex(ishg->parentItem()->index(), 0 , ishg->parentItem());
    }

    else if (Qt42BC->type() == FOVHEADER)
    {
        FOVHeader* fovh = static_cast<FOVHeader*>(Qt42BC);
        return createIndex(fovh->parentItem()->index(), 0, fovh->parentItem());
    }

    else if (Qt42BC->type() == INPIPCHEADER)
    {
        InpIPCHeader* inpIpch = static_cast<InpIPCHeader*>(Qt42BC);
        return createIndex(inpIpch->parentItem()->index(), 0, inpIpch->parentItem());
    }

    else if (Qt42BC->type() == GRAPHICSHEADER)
    {
        GraphicsHeader* gh = static_cast<GraphicsHeader*>(Qt42BC);
        return createIndex(gh->parentItem()->index(), 0 , gh->parentItem());
    }

    else if (Qt42BC->type() == INPTDRS)
    {
        InpTDRs* inpdtrs = static_cast<InpTDRs*>(Qt42BC);
        return createIndex(inpdtrs->parentItem()->index(), 0, inpdtrs->parentItem());
    }

    else if (Qt42BC->type() == REGIONHEADER)
    {
        RegionHeader* rgnh = static_cast<RegionHeader*>(Qt42BC);
        return createIndex(rgnh->parentItem()->index(), 0, rgnh->parentItem());
    }
    else
        return QModelIndex();

}

QModelIndex Qt42Model::indexByType(int row, int column, Qt42BaseClass *Qt42BC) const
{
    if (Qt42BC->type() == MISSION)
    {
        Mission* mission = static_cast<Mission*>(Qt42BC);
        if (row == spacecraftHeaderRow && column == spacecraftColumn)
            return createIndex(row, column, mission->spacecraftheader());
        else if (row == orbitHeaderRow && column == orbitHeaderColumn)
            return createIndex(row, column, mission->orbitheader());
        else if (row == inpsimRow && column == inpsimColumn)
            return createIndex(row, column, mission->inpsimheader());
        else if (row == fovHeaderRow && column == fovHeaderColumn)
            return createIndex(row, column, mission->fOVHeader());
        else if (row == inpIPCHeaderRow && column == inpIPCHeaderColumn)
            return createIndex(row, column, mission->inpIpcHeader());
        else if (row == graphicsHeaderRow && column == graphicsHeaderColumn)
            return createIndex(row, column, mission->graphisHeader());
        else if (row == inpTDRsRow && column == inpTDRsColumn)
            return createIndex(row, column, mission->inpTDRs());
        else if (row == inpRegionRow && column == inpRegionColumn)
            return createIndex(row, column, mission->regionHeader());
    }

    else if  (Qt42BC->type() == SPACECRAFTHEADER)
    {
        SpacecraftHeader* SCH = static_cast<SpacecraftHeader*>(Qt42BC);
        if (row < 0 || row > SCH->numberOfSpacecraft() || column != spacecraftColumn)
        {
            return QModelIndex();
        }

        return createIndex(row, column, SCH->spacecraft(row));
    }

    else if  (Qt42BC->type() == SPACECRAFT)
    {
        Spacecraft* SC = static_cast<Spacecraft*>(Qt42BC);
        if ( SC->numberOfBodies() && row == SC->rowSPACECRAFTBODY()
             && column > -1 && column < SC->numberOfBodies())
        {
            return createIndex(row, column, SC->body(column));
        }

        else if ( SC->numberOfJoints() && row == SC->rowJOINT() && column > -1
                  && column < SC->numberOfJoints())
            return createIndex(row, column, SC->joint(column));

        else if (SC->numberOfWheels() && row == SC->rowWHEEL() && column > -1
                 && column < SC->numberOfWheels())
            return createIndex(row, column, SC->wheel(column));

        else if ( SC->numberOfMagTorquer() && row == SC->rowMAGTORQUER() && column > -1
                  && column < SC->numberOfMagTorquer())
            return createIndex(row, column, SC->magTorque(column));

        else if ( SC->numberOfThruster() && row == SC->rowTHRUSTER() && column > -1
                  && column < SC->numberOfThruster())
            return createIndex(row, column, SC->thruster(column));

        else if ( SC->numberOfGyroAxis() && row == SC->rowGYROAXIS() && column > -1
                  && column < SC->numberOfGyroAxis())
            return createIndex(row, column, SC->gyroAxis(column));

        else if ( SC->numberOfMMA() && row == SC->rowMAGNETOMETERAXIS() && column > -1
                  && column < SC->numberOfMMA())
            return createIndex(row, column, SC->MMA(column));

        else if ( SC->numberOfCoarseSunSensor() && row == SC->rowCOARSESUNSENSOR() && column > -1
                  && column < SC->numberOfCoarseSunSensor())
            return createIndex(row, column, SC->coarseSunSensor(column));

        else if ( SC->numberOfFineSunSensor() && row == SC->rowFINESUNSENSOR() && column > -1
                  && column < SC->numberOfFineSunSensor())
            return createIndex(row, column, SC->fineSunSensor(column));

        else if ( SC->numberOfStarTracker() && row == SC->rowSTARTRACKER() && column > -1
                  && column < SC->numberOfStarTracker())
            return createIndex(row, column, SC->starTracker(column));

        else if ( SC->numberOfGPSReceiver() && row == SC->rowGPSRECEIVER() && column > -1
                  && column < SC->numberOfGPSReceiver())
            return createIndex(row, column, SC->gPSReceiver(column));

        else if ( SC->numberOfAccelerometer() && row == SC->rowACCELEROMETER() && column > -1 && column < SC->numberOfAccelerometer())
            return createIndex(row, column, SC->accelerometer(column));

        return QModelIndex();
    }



    else if  (Qt42BC->type() == ORBITHEADER)
    {
        OrbitHeader* OH = static_cast<OrbitHeader*>(Qt42BC);
        if (row < OH->numberOfOrbit() && column == 0){
            return createIndex(row, column, OH->orbit(row));
        }
    }

    else if (Qt42BC->type() == INPSIMHEADER)
    {
        InpSimHeader* inpsim = static_cast<InpSimHeader*>(Qt42BC);
        if (row == inpsim->indexSimulationControl() && column == 0)
            return createIndex(row, column, inpsim->simulationcontrol());
        else if (row == inpsim->indexOrbitSCset() && column == 0)
            return createIndex(row, column, inpsim->orbitSCSet());
        else if (row == inpsim->indexEnvironment() && column == 0)
            return createIndex(row, column, inpsim->environment());
        else if (row == inpsim->indexCelestialBody() && column == 0)
            return createIndex(row, column, inpsim->celestialbody());
        else if (row == inpsim->indexLagrangePointSystem() && column == 0)
            return createIndex(row, column, inpsim->lagrangepointsystem());
        else if (row == inpsim->indexGroudStation() && column == 0)
            return createIndex(row, column,inpsim->groupstation());
    }

    return QModelIndex();
}

QVariant Qt42Model::dataByType(Qt42BaseClass *Qt42BC) const
{
    QVariant V;
    if (Qt42BC->type() == MISSION)
    {
        Mission* mission = static_cast<Mission*>(Qt42BC);
        V.setValue(*mission);
        return V;
    }
    else if (Qt42BC->type() == SPACECRAFTHEADER)
    {
        SpacecraftHeader* SPH = static_cast<SpacecraftHeader*>(Qt42BC);
        V.setValue(*SPH);
        return V;
    }
    else if (Qt42BC->type() == SPACECRAFT)
    {
        Spacecraft* SC = static_cast<Spacecraft*>(Qt42BC);
        V.setValue(*SC);
        return V;
    }

    else if (Qt42BC->type() == SPACECRAFTBODY)
    {
        SpacecraftBody* SCB = static_cast<SpacecraftBody*>(Qt42BC);
        V.setValue(*SCB);
        return V;
    }
    else if (Qt42BC->type() == JOINT)
    {
        Joint* JNT = static_cast<Joint*>(Qt42BC);
        V.setValue(*JNT);
        return V;
    }
    else if (Qt42BC->type() == WHEEL)
    {
        Wheel* WHL = static_cast<Wheel*>(Qt42BC);
        V.setValue(*WHL);
        return V;
    }
    else if (Qt42BC->type() == MAGTORQUER)
    {
        MagTorquer* MT = static_cast<MagTorquer*>(Qt42BC);
        V.setValue(*MT);
        return V;
    }
    else if (Qt42BC->type() == THRUSTER)
    {
        Thruster* THR = static_cast<Thruster*>(Qt42BC);
        V.setValue(*THR);
        return V;

    }
    else if (Qt42BC->type() == GYROAXIS)
    {
        GyroAxis* gyro = static_cast<GyroAxis*>(Qt42BC);
        V.setValue(*gyro);
        return V;

    }
    else if (Qt42BC->type() == MAGNETOMETERAXIS)
    {
        MagnetometerAxis* MMA = static_cast<MagnetometerAxis*>(Qt42BC);
        V.setValue(*MMA);
        return V;

    }
    else if (Qt42BC->type() == COARSESUNSENSOR)
    {
        CoarseSunSensor* CSS = static_cast<CoarseSunSensor*>(Qt42BC);
        V.setValue(*CSS);
        return V;
    }
    else if (Qt42BC->type() == FINESUNSENSOR)
    {
        FineSunSensor* FSS = static_cast<FineSunSensor*>(Qt42BC);
        V.setValue(*FSS);
        return V;
    }
    else if (Qt42BC->type() == STARTRACKER)
    {
        StarTracker* ST = static_cast<StarTracker*>(Qt42BC);
        V.setValue(*ST);
        return V;
    }
    else if (Qt42BC->type() == GPSRECEIVER)
    {
        GPSReceiver* gpsr = static_cast<GPSReceiver*>(Qt42BC);
        V.setValue(*gpsr);
        return V;
    }
    else if (Qt42BC->type() == ACCELEROMETER)
    {
        Accelerometer* accl = static_cast<Accelerometer*>(Qt42BC);
        V.setValue(*accl);
        return V;
    }

    else if (Qt42BC->type() == ORBITHEADER)
    {
        OrbitHeader* oh = static_cast<OrbitHeader*>(Qt42BC);
        V.setValue(*oh);
        return V;
    }

    else if (Qt42BC->type() == ORBIT)
    {
        Orbit* o = static_cast<Orbit*>(Qt42BC);
        V.setValue(*o);
        return V;
    }

    else if (Qt42BC->type() == INPSIMHEADER)
    {
        InpSimHeader* inpsim = static_cast<InpSimHeader*>(Qt42BC);
        V.setValue(*inpsim);
        return V;
    }
    else if (Qt42BC->type() == INPSIMSIMULATIONCONTROL)
    {
        InpSimSimulationControl* inpsimS = static_cast<InpSimSimulationControl*>(Qt42BC);
        V.setValue(*inpsimS);
        return V;
    }
    else if (Qt42BC->type() == INPSIMORBITSCSET)
    {
        InpSimOrbitSCSet* inpsimOSC = static_cast<InpSimOrbitSCSet*>(Qt42BC);
        V.setValue(*inpsimOSC);
        return V;
    }
    else if (Qt42BC->type() == INPSIMENVIRONMENT)
    {
        InpSimEnvironment* inpsimEnvironment = static_cast<InpSimEnvironment*>(Qt42BC);
        V.setValue(*inpsimEnvironment);
        return V;
    }
    else if (Qt42BC->type() == INPSIMCELESTIALBODY)
    {
        InpSimCelestialBody* inpsimCelestialBody = static_cast<InpSimCelestialBody*>(Qt42BC);
        V.setValue(*inpsimCelestialBody);
        return V;
    }
    else if (Qt42BC->type() == INPSIMLAGRANGEPOINTSYSTEM)
    {
        InpSimLagrangePointSystem* inpsimlagrangepointsystem = static_cast<InpSimLagrangePointSystem*>(Qt42BC);
        V.setValue(*inpsimlagrangepointsystem);
        return V;
    }
    else if (Qt42BC->type() == INPSIMGROUNDSTATION)
    {
        InpSimGroundStation* inpsimgroundstation = static_cast<InpSimGroundStation*>(Qt42BC);
        V.setValue(*inpsimgroundstation);
        return V;
    }

    else if (Qt42BC->type() == FOVHEADER)
    {
        FOVHeader* fovheader = static_cast<FOVHeader*>(Qt42BC);
        V.setValue(*fovheader);
        return V;
    }

    else if (Qt42BC->type() == INPIPCHEADER)
    {
        InpIPCHeader* inpinch = static_cast<InpIPCHeader*>(Qt42BC);
        V.setValue(*inpinch);
        return V;
    }

    else if (Qt42BC->type() == GRAPHICSHEADER)
    {
        GraphicsHeader* gh = static_cast<GraphicsHeader*>(Qt42BC);
        V.setValue(*gh);
        return V;
    }

    else if (Qt42BC->type() == INPTDRS)
    {
        InpTDRs* inptdrs = static_cast<InpTDRs*>(Qt42BC);
        V.setValue(*inptdrs);
        return V;
    }

    else if (Qt42BC->type() == REGIONHEADER)
    {
        RegionHeader* rgnh = static_cast<RegionHeader*>(Qt42BC);
        V.setValue(*rgnh);
        return V;
    }

    else
    {
        return QVariant();
    }
}

QIcon Qt42Model::iconByType(Qt42BaseClass *Qt42BC) const
{
    if (Qt42BC->type() == MISSION)
        return QIcon("Qt42_Images/mission.png");
    else if (Qt42BC->type() == SPACECRAFTHEADER)
        return QIcon("Qt42_Images/Spacecraft.png");
    else if (Qt42BC->type() == ORBITHEADER)
        return QIcon("Qt42_Images/orbit.png");
    else if (Qt42BC->type() == INPSIMHEADER)
        return QIcon("Qt42_Images/SimulationSettings.png");
    else if (Qt42BC->type() == FOVHEADER)
        return QIcon("Qt42_Images/FieldOfView.png");
    else
        return QIcon();
}

int Qt42Model::rowCountByType(Qt42BaseClass *Qt42BC) const
{
    if (Qt42BC->type() == MISSION)
    {
        //Mission* mission = static_cast<Mission*>(Qt42BC);
        return 8;
    }

    else if (Qt42BC->type() == SPACECRAFTHEADER)
    {
        SpacecraftHeader* SCH = static_cast<SpacecraftHeader*>(Qt42BC);
        return SCH->numberOfSpacecraft();
    }
    else if (Qt42BC->type() == SPACECRAFT)
    {
        Spacecraft* SC = static_cast<Spacecraft*>(Qt42BC);
        return SC->numberOfRow();
    }

    else if (Qt42BC->type() == ORBITHEADER)
    {
        OrbitHeader* OH = static_cast<OrbitHeader*>(Qt42BC);
        return OH->numberOfOrbit();
    }

    else if (Qt42BC->type() == INPSIMHEADER)
    {
        return 6;
    }

    else
        return 0;
}

int Qt42Model::columnCountByType(Qt42BaseClass *Qt42BC) const
{
    if (Qt42BC->type()==SPACECRAFT)
    {
        int maxNumberOfColumn = 0;
        Spacecraft* SC = static_cast<Spacecraft*>(Qt42BC);
        QVector <int> qvecNumberOfColumn = {
            SC->numberOfBodies()        , SC->numberOfJoints()          ,
            SC->numberOfWheels()        , SC->numberOfMagTorquer()      ,
            SC->numberOfThruster()      , SC->numberOfGyroAxis()        ,
            SC->numberOfMMA()           , SC->numberOfCoarseSunSensor() ,
            SC->numberOfFineSunSensor() , SC->numberOfStarTracker()     ,
            SC->numberOfGPSReceiver()   , SC->numberOfAccelerometer()
        };
        for (int N: qvecNumberOfColumn){
            if (maxNumberOfColumn < N)
                maxNumberOfColumn = N;
        }
        return maxNumberOfColumn;

    }
    else
        return 1;
}

void Qt42Model::setDataByType(const QModelIndex& index, const QVariant &data)
{
    if (index.data().canConvert<Mission>() && data.canConvert<Mission>())
    {
        Mission* mission = static_cast<Mission*>(index.internalPointer());
        Mission dataMission = data.value<Mission>();
        *mission = dataMission;
        //loadMission(mission, dataMission);
    }

    else if (index.data().canConvert<Spacecraft>() && data.canConvert<Spacecraft>())
    {
        Spacecraft* spacecraft = static_cast<Spacecraft*>(index.internalPointer());
        Spacecraft dataSpacecraft = data.value<Spacecraft>();
        *spacecraft = dataSpacecraft;
    }

    else if (index.data().canConvert<Orbit>() && data.canConvert<Orbit>())
    {
        Orbit* orbit = static_cast<Orbit*>(index.internalPointer());
        Orbit dataOrbit = data.value<Orbit>();
        *orbit = dataOrbit;
    }

    else if (index.data().canConvert<SpacecraftBody>())
    {

        Spacecraft* SC = static_cast<Spacecraft*>(index.parent().internalPointer());
        SpacecraftBody* SCB = static_cast<SpacecraftBody*>(index.internalPointer());
        SpacecraftBody dataSCB = data.value<SpacecraftBody>();
        *SCB = dataSCB;
        if (!SCB->includedInCalculation())
            SC->updateSCcIncluded(SCB->index(),false);

    }

    else if (index.data().canConvert<Joint>())
    {
        Joint* JNT = static_cast<Joint*>(index.internalPointer());
        Joint dataJoint = data.value<Joint>();
        *JNT = dataJoint;
    }

    else if (index.data().canConvert<Wheel>())
    {
        Wheel* WHL = static_cast<Wheel*>(index.internalPointer());
        Wheel dataWheel = data.value<Wheel>();
        *WHL = dataWheel;

    }

    else if (index.data().canConvert<MagTorquer>())
    {
        MagTorquer* MTB = static_cast<MagTorquer*>(index.internalPointer());
        MagTorquer dataMTB = data.value<MagTorquer>();
        *MTB = dataMTB;
    }

    else if (index.data().canConvert<Thruster>())
    {
        Thruster* THR = static_cast<Thruster*>(index.internalPointer());
        Thruster dataTHR = data.value<Thruster>();
        *THR = dataTHR;
    }

    else if (index.data().canConvert<GyroAxis>())
    {
        GyroAxis* GYRO = static_cast<GyroAxis*>(index.internalPointer());
        GyroAxis dataGYRO = data.value<GyroAxis>();
        *GYRO = dataGYRO;
    }

    else if (index.data().canConvert<MagnetometerAxis>())
    {
        MagnetometerAxis* MMA = static_cast<MagnetometerAxis*>(index.internalPointer());
        MagnetometerAxis dataMMA = data.value<MagnetometerAxis>();
        *MMA  = dataMMA;
    }

    else if (index.data().canConvert<CoarseSunSensor>())
    {
        CoarseSunSensor* CSS = static_cast<CoarseSunSensor*>(index.internalPointer());
        CoarseSunSensor dataCSS = data.value<CoarseSunSensor>();
        *CSS = dataCSS;
    }

    else if (index.data().canConvert<FineSunSensor>())
    {
        FineSunSensor* FSS = static_cast<FineSunSensor*>(index.internalPointer());
        FineSunSensor dataFSS = data.value<FineSunSensor>();
        *FSS = dataFSS;
    }

    else if (index.data().canConvert<StarTracker>())
    {
        StarTracker* ST = static_cast<StarTracker*>(index.internalPointer());
        StarTracker dataST = data.value<StarTracker>();
        *ST = dataST;
    }

    else if (index.data().canConvert<GPSReceiver>())
    {
        GPSReceiver* GPSR = static_cast<GPSReceiver*>(index.internalPointer());
        GPSReceiver dataGPSR = data.value<GPSReceiver>();
        *GPSR = dataGPSR;
    }

    else if (index.data().canConvert<Accelerometer>())
    {
        Accelerometer* ACCL = static_cast<Accelerometer*>(index.internalPointer());
        Accelerometer dataACCL = data.value<Accelerometer>();
        *ACCL = dataACCL;
    }
    else if (index.data().canConvert<InpSimSimulationControl>())
    {
        InpSimSimulationControl* SimC = static_cast<InpSimSimulationControl*>(index.internalPointer());
        InpSimSimulationControl dataSimC = data.value<InpSimSimulationControl>();
        *SimC = dataSimC;
    }

    else if (index.data().canConvert<InpSimOrbitSCSet>())
    {
        InpSimOrbitSCSet* simOSC = static_cast<InpSimOrbitSCSet*>(index.internalPointer());
        InpSimOrbitSCSet dataSimOSC = data.value<InpSimOrbitSCSet>();
        *simOSC = dataSimOSC;
    }
    else if (index.data().canConvert<InpSimEnvironment>())
    {
        InpSimEnvironment* E = static_cast<InpSimEnvironment*>(index.internalPointer());
        InpSimEnvironment dataE = data.value<InpSimEnvironment>();
        *E = dataE;
    }
    else if (index.data().canConvert<InpSimCelestialBody>())
    {
        InpSimCelestialBody* C = static_cast<InpSimCelestialBody*>(index.internalPointer());
        InpSimCelestialBody dataC = data.value<InpSimCelestialBody>();
        *C = dataC;
    }
    else if (index.data().canConvert<InpSimLagrangePointSystem>())
    {
        InpSimLagrangePointSystem* L = static_cast<InpSimLagrangePointSystem*>(index.internalPointer());
        InpSimLagrangePointSystem dataL = data.value<InpSimLagrangePointSystem>();
        *L = dataL;
    }
    else if (index.data().canConvert<InpSimGroundStation>())
    {
        InpSimGroundStation* G = static_cast<InpSimGroundStation*>(index.internalPointer());
        InpSimGroundStation dataG = data.value<InpSimGroundStation>();
        *G = dataG;
    }
    else if (index.data().canConvert<GroundStation>())
    {
        GroundStation* GS = static_cast<GroundStation*>(index.internalPointer());
        GroundStation dataGS = data.value<GroundStation>();
        *GS = dataGS;
    }
    else if (index.data().canConvert<FOVHeader>())
    {
        FOVHeader* F = static_cast<FOVHeader*>(index.internalPointer());
        FOVHeader dataF = data.value<FOVHeader>();
        *F = dataF;
    }
    else if (index.data().canConvert<Inp_IPC>())
    {
        Inp_IPC* inpipc = static_cast<Inp_IPC*>(index.internalPointer());
        Inp_IPC dataI = data.value<Inp_IPC>();
        *inpipc = dataI;
    }
    else if (index.data().canConvert<InpIPCHeader>())
    {
        InpIPCHeader* inpipch = static_cast<InpIPCHeader*>(index.internalPointer());
        InpIPCHeader dataIIH = data.value<InpIPCHeader>();
        *inpipch = dataIIH;
    }
    else if (index.data().canConvert<GraphicsHeader>())
    {
        GraphicsHeader* gh = static_cast<GraphicsHeader*>(index.internalPointer());
        GraphicsHeader dataGH = data.value<GraphicsHeader>();
        *gh = dataGH;
    }
    else if (index.data().canConvert<InpTDRs>())
    {
        InpTDRs* inptdrs = static_cast<InpTDRs*>(index.internalPointer());
        InpTDRs dataInpdtrs = data.value<InpTDRs>();
        *inptdrs = dataInpdtrs;
    }
    else if (index.data().canConvert<RegionHeader>())
    {
        RegionHeader* rgnh = static_cast<RegionHeader*>(index.internalPointer());
        RegionHeader dataRgnh = data.value<RegionHeader>();
        *rgnh = dataRgnh;
    }

}

bool Qt42Model::insertColumns(int position, int columns, const QModelIndex &parent)
{
    if (!parent.isValid())
        return false;
    if (parent.data().canConvert<Spacecraft>())
    {
        beginInsertColumns(parent, position, position + columns - 1);
        endInsertColumns();
    return true;
    }
    return false;
}

bool Qt42Model::removeRows(int position, int rows, const QModelIndex &parent)
{
    if (!parent.isValid() || parent.data().canConvert<MissionHolder>())
    {
        beginRemoveRows(parent, position, rows);
        bool success = m_MissionHolder->removeMission(m_MissionHolder->mission(position));
        endRemoveRows();
        return success;
    }
    if (parent.data().canConvert<SpacecraftHeader>())
    {
        /** for some unknown reasons the application will crash if we remove the last SC,
         * The solution is to reduce the "position" by one if the sc is the last one.
         * This doesn't happen to orbit objects.
         */

        int p = rowCount(parent)-1 ? position-1 : position;
        if (p < 0)
            p = 0;
        beginRemoveRows(parent, p, p + rows-1);
        SpacecraftHeader* sch = static_cast<SpacecraftHeader*>(parent.internalPointer());
        bool success = sch->removeSpacecraft(sch->spacecraft(position));
        endRemoveRows();
        return success;
    }

    if (parent.data().canConvert<OrbitHeader>())
    {
        beginRemoveRows(parent, position, position+rows-1);
        OrbitHeader* oh = static_cast<OrbitHeader*>(parent.internalPointer());
        bool success = oh->removeOrbit(oh->orbit(position));
        endRemoveRows();
        return success;
    }

    if (parent.data().canConvert<Spacecraft>())
    {
        beginRemoveRows(parent, position, position+rows-1);
        Spacecraft* SC = static_cast<Spacecraft*>(parent.internalPointer());
        if (position == SC->rowSPACECRAFTBODY())
            for (int i = SC->numberOfBodies()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowJOINT())
            for (int i = SC->numberOfJoints()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowWHEEL())
            for (int i = SC->numberOfWheels()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowMAGTORQUER())
            for (int i = SC->numberOfMagTorquer()-1; i> -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowTHRUSTER())
            for (int i = SC->numberOfThruster()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowGYROAXIS())
            for (int i = SC->numberOfGyroAxis()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowMAGNETOMETERAXIS())
            for (int i = SC->numberOfMMA()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowCOARSESUNSENSOR())
            for (int i = SC->numberOfCoarseSunSensor()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowFINESUNSENSOR())
            for (int i = SC->numberOfFineSunSensor()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowSTARTRACKER())
            for (int i = SC->numberOfStarTracker()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowGPSRECEIVER())
            for (int i = SC->numberOfGPSReceiver()-1; i > -1; --i)
                removeItem(position, i, parent);
        else if (position == SC->rowACCELEROMETER())
            for (int i = SC->numberOfAccelerometer()-1; i > -1; --i)
                removeItem(position, i, parent);
        endRemoveRows();
        return true;
    }

    return false;
}

bool Qt42Model::insertRows(int position, int rows, const QModelIndex &parent)
{
    if (!parent.isValid() || parent.data().canConvert<MissionHolder>())
    {
        beginInsertRows(parent, position, rows);
        bool success = m_MissionHolder->createMission();
        endInsertRows();
        return success;
    }

    if (parent.data().canConvert<SpacecraftHeader>())
    {
        SpacecraftHeader* sch = static_cast<SpacecraftHeader*>(parent.internalPointer());
        beginInsertRows(parent, position+1, 1+position + rows -1);
        bool success = sch->createSpacecraft();
        endInsertRows();
        return success;
    }

    if (parent.data().canConvert<OrbitHeader>())
    {
        OrbitHeader* oh = static_cast<OrbitHeader*>(parent.internalPointer());
        beginInsertRows(parent, position, position + rows -1);
        bool success = oh->createOrbit();
        endInsertRows();
        return success;
    }
    return false;
}

bool Qt42Model::removeItem(int row, int column, const QModelIndex &parent)
{
    if (!hasIndex(row, column, parent))
        return false;
    if (!parent.isValid() || !index(row, column, parent).isValid())
        return false;

    int oldNumberOfRow = rowCount(parent);
    int oldNumberOfColumn = columnCount(parent);
    if (parent.data().canConvert<Spacecraft>())
    {
        beginRemoveColumns(parent, column, column);
        Spacecraft* SC = static_cast<Spacecraft*>(parent.internalPointer());

        if (row == SC->rowSPACECRAFTBODY()){
            SC->updateSCcIncluded(column, false);
            SC->removeSpacecraftBody(SC->body(column));
        }

        else if (row == SC->rowJOINT())
        {
            SC->removeJoint(SC->joint(column));
        }

        else if (row == SC->rowWHEEL())
        {
            SC->removeWheel(SC->wheel(column));
        }

        else if (row == SC->rowMAGTORQUER())
        {
            SC->removeMagTorquer(SC->magTorque(column));
        }

        else if (row == SC->rowTHRUSTER())
        {
            SC->removeThruster(SC->thruster(column));
        }

        else if (row == SC->rowGYROAXIS())
        {
            SC->removeGyroAxis(SC->gyroAxis(column));
        }

        else if (row == SC->rowMAGNETOMETERAXIS())
        {
            SC->removeMagnetometerAxis(SC->MMA(column));
        }

        else if (row == SC->rowCOARSESUNSENSOR())
        {
            SC->removeCoarseSunSensor(SC->coarseSunSensor(column));
        }

        else if (row == SC->rowFINESUNSENSOR())
        {
            SC->removeFineSunSensor(SC->fineSunSensor(column));
        }

        else if (row == SC->rowSTARTRACKER())
        {
            SC->removeStarTracker(SC->starTracker(column));
        }

        else if (row == SC->rowGPSRECEIVER())
        {
            SC->removeGPSReceiver(SC->gPSReceiver(column));
        }

        else if (row == SC->rowACCELEROMETER())
        {
            SC->removeAccelerometer(SC->accelerometer(column));
        }
        endRemoveColumns();

        //if (column < columnCount(parent))
        if (oldNumberOfColumn <= columnCount(parent))
        {
            beginInsertColumns(parent, columnCount(parent), columnCount(parent));
            endInsertColumns();
        }
        if (rowCount(parent) < oldNumberOfRow)
        {
            beginRemoveRows(parent, rowCount(parent),rowCount(parent));
            endRemoveRows();
        }
        return true;
    }
    return false;
}

bool Qt42Model::createItem(const QModelIndex& parent, objectType componentType)
{    
    if (parent.data().canConvert<Spacecraft>())
    {
        Spacecraft* SC = static_cast<Spacecraft*>(parent.internalPointer());
        if (SC->columnOfComponent(componentType) < columnCount(parent)){
            beginInsertColumns(parent, columnCount(parent), columnCount(parent));
            if (SC->numberOfRow() <= rowCount(parent) &&
                    SC->rowOfComponent(componentType) > -1){
                SC->createItem(componentType);
                emit dataChanged(parent, parent, {Qt::EditRole, Qt::DisplayRole});
            }
            else
            {
                beginInsertRows(parent, rowCount(parent), rowCount(parent));
                SC->createItem(componentType);
                endInsertRows();
            }
            endInsertColumns();
            beginRemoveColumns(parent, columnCount(parent), columnCount(parent));
            endRemoveColumns();
        }
        else if (SC->columnOfComponent(componentType) >= columnCount(parent)){
            beginInsertColumns(parent, columnCount(parent), columnCount(parent));
            if (SC->numberOfRow() <= rowCount(parent) &&
                    SC->rowOfComponent(componentType) > -1){
                SC->createItem(componentType);
            }
            else
            {
                beginInsertRows(parent, rowCount(parent), rowCount(parent));
                SC->createItem(componentType);
                endInsertRows();
            }
            endInsertColumns();
        }
        return true;
    }
    return false;
}

bool Qt42Model::insertItem(const QModelIndex &parent, objectType componentType,
                           const int &row, const int &column, Qt42BaseClass *Qt42BC)
{
    if (parent.data().canConvert<Spacecraft>())
    {
        Spacecraft* SC = static_cast<Spacecraft*>(parent.internalPointer());
        if (SC->columnOfComponent(componentType) < columnCount(parent)){
            beginInsertColumns(parent, columnCount(parent), columnCount(parent));
            if (SC->numberOfRow() <= rowCount(parent) &&
                    SC->rowOfComponent(componentType) > -1)
            {
                SC->insertItem(column,componentType,Qt42BC);
                emit dataChanged(parent, parent, {Qt::EditRole, Qt::DisplayRole});
            }
            else
            {
                beginInsertRows(parent, rowCount(parent), rowCount(parent));
                SC->insertItem(column,componentType,Qt42BC);
                endInsertRows();
            }
            endInsertColumns();
            beginRemoveColumns(parent, columnCount(parent), columnCount(parent));
            endRemoveColumns();
        }
        else if (SC->columnOfComponent(componentType) >= columnCount(parent))
        {
            beginInsertColumns(parent, columnCount(parent), columnCount(parent));
            if (SC->numberOfRow() <= rowCount(parent) &&
                    SC->rowOfComponent(componentType) > -1)
            {
                SC->insertItem(column,componentType,Qt42BC);
            }
            else
            {
                beginInsertRows(parent, rowCount(parent), rowCount(parent));
                SC->createItem(componentType);
                endInsertRows();
            }
            endInsertColumns();
        }
        return true;
    }
    return false;
}




bool Qt42Model::resetData(const QModelIndex &index)
{
    if (!index.isValid())
        return false;
    if (index.data().canConvert<Spacecraft>())
    {
        Spacecraft SC = index.data().value<Spacecraft>();
        for (int row = SC.numberOfRow()-1; row > -1; --row)
            removeRows(row,row,index);
        SC.reset();
        QVariant V = QVariant();
        V.setValue(SC);
        setData(index, V, Qt::EditRole);
        return true;
   }
    else
        return false;
}

int Qt42Model::numberOfMission() const
{
    return m_MissionHolder->numberOfMission();
}

void Qt42Model::loadMission(Mission*& missionToModify, Mission missionLoaded)
{
    missionToModify->rename(missionLoaded.name());
    missionToModify->setDirectroy(missionLoaded.directory());
    const int numberOfSpacecraftOJT = missionLoaded.m_SpacecraftHeaderObject.numberOfSpacecraftObject();
    const int numberOfOrbitOJT = missionLoaded.m_OrbitHeaderObejct.numberOfOrbitObject();

    for (int i = 0; i < numberOfSpacecraftOJT; ++i)
    {
        Spacecraft scLoaded = missionLoaded.m_SpacecraftHeaderObject.m_qvecSpacecraftObjects[i];
        missionToModify->createSpacecraft();

        missionToModify->spacecraft(i)->duplicate(scLoaded);
        for (int j = 0; j < scLoaded.m_qvecScbObjects.size(); ++j)
        {
            SpacecraftBody scbLoaded = scLoaded.m_qvecScbObjects[j];
            missionToModify->spacecraft(i)->createSpacecraftBody();
            missionToModify->spacecraft(i)->body(j)->duplicate(scbLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecJointObjects.size(); ++j)
        {
            Joint jntLoaded = scLoaded.m_qvecJointObjects[j];
            missionToModify->spacecraft(i)->createJoint();
            missionToModify->spacecraft(i)->joint(j)->duplicate(jntLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecWheelObjects.size(); ++j)
        {
            Wheel whlLoaded = scLoaded.m_qvecWheelObjects[j];
            missionToModify->spacecraft(i)->createWheel();
            missionToModify->spacecraft(i)->wheel(j)->duplicate(whlLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecMagTrqObjects.size(); ++j)
        {
            MagTorquer mtbLoaded = scLoaded.m_qvecMagTrqObjects[j];
            missionToModify->spacecraft(i)->createMagTorquer();
            missionToModify->spacecraft(i)->magTorque(j)->duplicate(mtbLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecThrusterObjects.size(); ++j)
        {
            Thruster thrLoaded = scLoaded.m_qvecThrusterObjects[j];
            missionToModify->spacecraft(i)->createThruster();
            missionToModify->spacecraft(i)->thruster(j)->duplicate(thrLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecGyroObjects.size(); ++j)
        {
            GyroAxis gyoLoaded = scLoaded.m_qvecGyroObjects[j];
            missionToModify->spacecraft(i)->createGyroAxis();
            missionToModify->spacecraft(i)->gyroAxis(j)->duplicate(gyoLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecMMAObjects.size(); ++j)
        {
            MagnetometerAxis mmaLoaded = scLoaded.m_qvecMMAObjects[j];
            missionToModify->spacecraft(i)->createMagnetometerAxis();
            missionToModify->spacecraft(i)->MMA(j)->duplicate(mmaLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecCSSObjects.size(); ++j)
        {
            CoarseSunSensor cssLoaded = scLoaded.m_qvecCSSObjects[j];
            missionToModify->spacecraft(i)->createCoarseSunSensor();
            missionToModify->spacecraft(i)->coarseSunSensor(j)->duplicate(cssLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecFSSObjects.size(); ++j)
        {
            FineSunSensor fssLoaded = scLoaded.m_qvecFSSObjects[j];
            missionToModify->spacecraft(i)->createFineSunSensor();
            missionToModify->spacecraft(i)->fineSunSensor(j)->duplicate(fssLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecSTObjects.size(); ++j)
        {
            StarTracker stLoaded = scLoaded.m_qvecSTObjects[j];
            missionToModify->spacecraft(i)->createStarTracker();
            missionToModify->spacecraft(i)->starTracker(j)->duplicate(stLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecGPSRObjects.size();++j)
        {
            GPSReceiver gpsrLoaded = scLoaded.m_qvecGPSRObjects[j];
            missionToModify->spacecraft(i)->createGPSReceiver();
            missionToModify->spacecraft(i)->gPSReceiver(j)->duplicate(gpsrLoaded);
        }

        for (int j = 0; j < scLoaded.m_qvecAccelObjects.size(); ++j)
        {
            Accelerometer acclLoaded = scLoaded.m_qvecAccelObjects[j];
            missionToModify->spacecraft(i)->createAccelerometer();
            missionToModify->spacecraft(i)->accelerometer(j)->duplicate(acclLoaded);
        }
    }

    for (int i = 0; i < numberOfOrbitOJT; ++i)
    {
        Orbit oLoaded = missionLoaded.m_OrbitHeaderObejct.m_qvecOrbitObjects[i];
        missionToModify->createOrbit();
        missionToModify->orbit(i)->duplicate(oLoaded);
    }

    InpSimSimulationControl inpsscLoaded =
            missionLoaded.m_InpSimHeaderObject.m_simulationcontrolObject;
    InpSimOrbitSCSet oscLoaded = missionLoaded.m_InpSimHeaderObject.m_orbitSCSetObject;
    InpSimEnvironment envLoaded = missionLoaded.m_InpSimHeaderObject.m_environmentObject;
    InpSimCelestialBody cbLoaded = missionLoaded.m_InpSimHeaderObject.m_celestialbodyObject;
    InpSimLagrangePointSystem lLoaded = missionLoaded.m_InpSimHeaderObject.m_lagrangepointsystemObject;
    InpSimGroundStation gsLoaded = missionLoaded.m_InpSimHeaderObject.m_groupstationObject;
    missionToModify->inpsimheader()->simulationcontrol()->duplicate(inpsscLoaded);
    missionToModify->inpsimheader()->orbitSCSet()->duplicate(oscLoaded);
    missionToModify->inpsimheader()->environment()->duplicate(envLoaded);
    missionToModify->inpsimheader()->celestialbody()->duplicate(cbLoaded);
    missionToModify->inpsimheader()->lagrangepointsystem()->duplicate(lLoaded);
    missionToModify->inpsimheader()->groupstation()->duplicate(gsLoaded);

    FOVHeader fovhLoaded = missionLoaded.m_FOVHeaderObject;
    missionToModify->fOVHeader()->duplicate(fovhLoaded);

    InpIPCHeader iochLoaded = missionLoaded.m_InpIPCHeaderObject;
    missionToModify->inpIpcHeader()->duplicate(iochLoaded);

    GraphicsHeader graphicsLoaded = missionLoaded.m_GraphisHeaderObject;
    missionToModify->graphisHeader()->duplicate(graphicsLoaded);

    InpTDRs inptdrsLoaded = missionLoaded.m_inpTDRsObject;
    missionToModify->inpTDRs()->duplicate(inptdrsLoaded);

    RegionHeader rgnhLoaded = missionLoaded.m_regionHeaderObject;
    missionToModify->regionHeader()->duplicate(rgnhLoaded);
}

void Qt42Model::loadMission(const QModelIndex& modelIndexMission, const QVariant& newData)
{
    if (!modelIndexMission.isValid() ||
            !modelIndexMission.data().canConvert<Mission>() ||
            !newData.canConvert<Mission>())
        return;
    Mission* m = static_cast<Mission*>(modelIndexMission.internalPointer());
    Mission missionLoaded = newData.value<Mission>();
    loadMission(m, missionLoaded);
}
