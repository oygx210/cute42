#include "DataHeaders/inpsimterms.h"
#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/mission.h"

/** simulation control **/

InpSimSimulationControl::InpSimSimulationControl(InpSimHeader* inpsimheader) :
    m_inpsimheader(inpsimheader)
{
    changeType(m_type);
}

InpSimSimulationControl::~InpSimSimulationControl()
{

}

InpSimSimulationControl::InpSimSimulationControl(const InpSimSimulationControl& inpsimsimC) : Qt42BaseClass(inpsimsimC)
{
    m_inpsimheader = inpsimsimC.m_inpsimheader;
    m_timeMode = inpsimsimC.m_timeMode;
    m_simDuration = inpsimsimC.m_simDuration;
    m_stepSize = inpsimsimC.m_stepSize;
    m_fileOuputInterval = inpsimsimC.m_fileOuputInterval;
    m_graphicsFrontEnd = inpsimsimC.m_graphicsFrontEnd;

}

InpSimSimulationControl& InpSimSimulationControl::operator=(const InpSimSimulationControl &inpsimsimC)
{
    if (this == &inpsimsimC)
        return *this;
    m_inpsimheader = inpsimsimC.m_inpsimheader;
    m_timeMode = inpsimsimC.m_timeMode;
    m_simDuration = inpsimsimC.m_simDuration;
    m_stepSize = inpsimsimC.m_stepSize;
    m_fileOuputInterval = inpsimsimC.m_fileOuputInterval;
    m_graphicsFrontEnd = inpsimsimC.m_graphicsFrontEnd;
    return *this;
}

void InpSimSimulationControl::duplicate(const InpSimSimulationControl &inpsimsimC)
{
    m_timeMode = inpsimsimC.m_timeMode;
    m_simDuration = inpsimsimC.m_simDuration;
    m_stepSize = inpsimsimC.m_stepSize;
    m_fileOuputInterval = inpsimsimC.m_fileOuputInterval;
    m_graphicsFrontEnd = inpsimsimC.m_graphicsFrontEnd;
}

void InpSimSimulationControl::edit(const QString& timeMode, const double& simDuration,
                                   const double& stepSize, const double& fileOuputInterval,
                                   const bool& graphicsFrontEnd)
{
    m_timeMode = timeMode;
    m_simDuration = simDuration;
    m_stepSize = stepSize;
    m_fileOuputInterval = fileOuputInterval;
    m_graphicsFrontEnd = graphicsFrontEnd;
}

QDataStream& operator<< (QDataStream& dataStream, const InpSimSimulationControl& ISSC)
{
    dataStream << ISSC.m_timeMode
               << ISSC.m_simDuration
               << ISSC.m_stepSize
               << ISSC.m_fileOuputInterval
               << ISSC.m_graphicsFrontEnd;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, InpSimSimulationControl& ISSC)
{
    dataStream >> ISSC.m_timeMode
               >> ISSC.m_simDuration
               >> ISSC.m_stepSize
               >> ISSC.m_fileOuputInterval
               >> ISSC.m_graphicsFrontEnd;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const InpSimSimulationControl& ISSC)
{
    dataStream << ISSC.m_timeMode
               << ISSC.m_simDuration
               << ISSC.m_stepSize
               << ISSC.m_fileOuputInterval
               << ISSC.m_graphicsFrontEnd;
    return dataStream;
}

/** Orbit and Spacecraft sets **/

InpSimOrbitSCSet::InpSimOrbitSCSet(InpSimHeader* inpsimheader) : m_inpsimheader(inpsimheader)
{
    changeType(m_type);
}

InpSimOrbitSCSet::InpSimOrbitSCSet(const InpSimOrbitSCSet& OandSC) : Qt42BaseClass(OandSC)
{
    m_inpsimheader = OandSC.m_inpsimheader;
    m_qvecOrbitAll = OandSC.m_qvecOrbitAll;
    m_qvecSCAll = OandSC.m_qvecSCAll;
    m_qvecPair = OandSC.m_qvecPair;
}

InpSimOrbitSCSet::~InpSimOrbitSCSet()
{
}

InpSimOrbitSCSet& InpSimOrbitSCSet::operator=(const InpSimOrbitSCSet& OandSC)
{
    if (this == &OandSC)
        return *this;
    m_inpsimheader = OandSC.m_inpsimheader;
    m_qvecOrbitAll = OandSC.m_qvecOrbitAll;
    m_qvecSCAll = OandSC.m_qvecSCAll;
    m_qvecPair = OandSC.m_qvecPair;
    return *this;
}

void InpSimOrbitSCSet::duplicate(const InpSimOrbitSCSet& OandSC)
{
    m_qvecOrbitAll = OandSC.m_qvecOrbitAll;
    m_qvecSCAll = OandSC.m_qvecSCAll;
    m_qvecPair = OandSC.m_qvecPair;
}

void InpSimOrbitSCSet::createPair(const Orbit& O, const Spacecraft& SC)
{
    bool pairExist = false;
    for (QPair<Orbit, Spacecraft> pair : m_qvecPair)
    {
        if (pair.first == O && pair.second == SC){
            pairExist = true;
            break;
        }
    }

    if (pairExist)
        return;
    else {
        QPair<Orbit, Spacecraft> newPair(O, SC);
        m_qvecPair.append(newPair);
    }
}

void InpSimOrbitSCSet::createPair(const QPair<Orbit, Spacecraft> newPair)
{
    bool pairExist = false;
    for(QPair<Orbit, Spacecraft> pair : m_qvecPair)
    {
        if (pair.first == newPair.first && pair.second == newPair.second)
            pairExist = true;
    }

    if (pairExist)
        return;
    else
        m_qvecPair.append(newPair);
}

void InpSimOrbitSCSet::removePair(const int& index)
{
    if (index > -1 && index < m_qvecPair.size())
        m_qvecPair.remove(index);
    else
        return;
}

void InpSimOrbitSCSet::removePair(const QPair<Orbit,Spacecraft> removedPair)
{
    QPair<Orbit, Spacecraft> pairToRemove = QPair<Orbit, Spacecraft>();
    bool existing = false;
    for (int i = 0; i < m_qvecPair.size(); ++i)
    {
        if (m_qvecPair[i].first.name().trimmed() == removedPair.first.name().trimmed() &&
                m_qvecPair[i].second.name().trimmed() == removedPair.second.name().trimmed())
        {
            pairToRemove = m_qvecPair[i];
            existing = true;
            break;
        }
    }
    if (existing)
        m_qvecPair.removeAll(pairToRemove);
}

void InpSimOrbitSCSet::removePair(const Orbit& O)
{
    for (int i = 0; i < m_qvecPair.size(); ++i)
    {
        if (m_qvecPair[i].first.name().trimmed() == O.name().trimmed())
        {
            m_qvecPair.remove(i);
            --i;
        }
    }
}

void InpSimOrbitSCSet::removePair(const Spacecraft& SC)
{
    for (int i = 0; i < m_qvecPair.size(); ++i)
    {
        if (m_qvecPair[i].second.name().trimmed() == SC.name().trimmed())
        {
            m_qvecPair.remove(i);
            --i;
        }
    }
}

QVector<Spacecraft> InpSimOrbitSCSet::SCswithoutOrbits()
{
    if (!parentItem() || !parentItem()->parentItem())
        return QVector<Spacecraft>();

    m_qvecSCAll.clear();
    Mission m = *(parentItem()->parentItem());
    for (int i = 0; i < m.numberOfSpacecraft(); ++i){
        m_qvecSCAll.append(*(m.spacecraft(i)));
    }

    QVector<Spacecraft> SCwoOrbits = QVector<Spacecraft>();
    for (Spacecraft sc : m_qvecSCAll)
    {
        bool hasOrbits = false;
        for (QPair<Orbit, Spacecraft> pair : m_qvecPair)
        {
            if (pair.second.name().trimmed() == sc.name().trimmed())
            {
                hasOrbits = true;
                break;
            }
        }
        if (sc.includedInCalculation() && !hasOrbits)
        {
            SCwoOrbits.append(sc);
        }
    }
    return SCwoOrbits;
}

void InpSimOrbitSCSet::updateOrbitsSCs(const Mission& mission)
{
    m_qvecOrbitAll.clear();
    m_qvecSCAll.clear();
    for (int i = 0; i < mission.numberOfOrbit(); ++i)
        m_qvecOrbitAll.append(*(mission.orbitheader()->orbit(i)));

    for (int i = 0; i < mission.numberOfSpacecraft(); ++i)
        m_qvecSCAll.append(*(mission.spacecraftheader()->spacecraft(i)));

    for (QPair<Orbit,Spacecraft> pair : m_qvecPair)
    {
        if (!m_qvecOrbitAll.contains(pair.first) || !m_qvecSCAll.contains(pair.second))
            m_qvecPair.removeAll(pair);
        if (m_qvecOrbitAll.contains(pair.first) &&
                !m_qvecOrbitAll[m_qvecOrbitAll.indexOf(pair.first)].includedInCalculation())
            m_qvecPair.removeAll(pair);
        if (m_qvecSCAll.contains(pair.second) &&
                !m_qvecSCAll[m_qvecSCAll.indexOf(pair.second)].includedInCalculation())
            m_qvecPair.removeAll(pair);
    }
}

QDataStream& operator<< (QDataStream& dataStream, const InpSimOrbitSCSet& OandSC)
{
    dataStream << OandSC.m_qvecOrbitAll
               << OandSC.m_qvecSCAll
               << OandSC.m_qvecPair;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, InpSimOrbitSCSet& OandSC)
{
    dataStream >> OandSC.m_qvecOrbitAll
               >> OandSC.m_qvecSCAll
               >> OandSC.m_qvecPair;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const InpSimOrbitSCSet& OandSC)
{
    dataStream << OandSC.m_qvecOrbitAll
               << OandSC.m_qvecSCAll
               << OandSC.m_qvecPair;

    return dataStream;
}



/**  Environment **/

InpSimEnvironment::InpSimEnvironment(InpSimHeader* inpsimheader, Mission* mission) :
    m_inpsimheader(inpsimheader), m_mission(mission)
{
    changeType(m_type);
}

InpSimEnvironment::InpSimEnvironment(const InpSimEnvironment& E) : Qt42BaseClass(E)
{
    m_inpsimheader = E.m_inpsimheader;
    m_date = E.m_date;
    m_time = E.m_time;
    m_timeOffset = E.m_timeOffset; // unit: sec
    m_modelDateInterpolationSolarFlux_APValue = E.m_modelDateInterpolationSolarFlux_APValue; // could be TWOSIGMA_KP, NOMINAL or USER_DEFINED
    m_userDefined_F10_7 = E.m_userDefined_F10_7;
    m_userDefined_APvalue = E.m_userDefined_APvalue;
    m_magfield = E.m_magfield; // could be NONE, DIPOLE, IGRF
    m_IGRF_Degree = E.m_IGRF_Degree;
    m_IGRF_Order = E.m_IGRF_Order;  // note: <=10
    m_gravityModelEarth_N = E.m_gravityModelEarth_N;  // <=18
    m_gravityModelEarth_M = E.m_gravityModelEarth_M;  // <=18
    m_gravityModelMars_N = E.m_gravityModelMars_N;   // <=18
    m_gravityModelMars_M = E.m_gravityModelMars_M;   // <=18
    m_gravityModelLuna_N = E.m_gravityModelLuna_N;   // <=18
    m_gravityModelLuna_M = E.m_gravityModelLuna_M;   // <=18
    m_aerodynamicForces = E.m_aerodynamicForces;
    m_aerodynamicTorques = E.m_aerodynamicTorques;
    m_gravityGradientTorques = E.m_gravityGradientTorques;
    m_solarPressureForces = E.m_solarPressureForces;
    m_solarPressureTorques = E.m_solarPressureTorques;
    m_gravityPerturbationForces = E.m_gravityPerturbationForces;
    m_passiveJointForcesTorques = E.m_passiveJointForcesTorques;
    m_thrusterPlumeForcesTorques = E.m_thrusterPlumeForcesTorques;
    m_RWA_ImbalanceForcesTorques = E.m_RWA_ImbalanceForcesTorques;
    m_contactForcesTorques = E.m_contactForcesTorques;
    m_CFDsloshForceTorques = E.m_CFDsloshForceTorques;
    m_outPutEnvironmentalTorquesToFiles = E.m_outPutEnvironmentalTorquesToFiles;
}

InpSimEnvironment::~InpSimEnvironment()
{

}

InpSimEnvironment& InpSimEnvironment::operator=(const InpSimEnvironment &E)
{
   if(this == &E)
       return *this;
   m_inpsimheader = E.m_inpsimheader;
   m_date = E.m_date;
   m_time = E.m_time;
   m_timeOffset = E.m_timeOffset; // unit: sec
   m_modelDateInterpolationSolarFlux_APValue = E.m_modelDateInterpolationSolarFlux_APValue; // could be TWOSIGMA_KP, NOMINAL or USER_DEFINED
   m_userDefined_F10_7 = E.m_userDefined_F10_7;
   m_userDefined_APvalue = E.m_userDefined_APvalue;
   m_magfield = E.m_magfield; // could be NONE, DIPOLE, IGRF
   m_IGRF_Degree = E.m_IGRF_Degree;
   m_IGRF_Order = E.m_IGRF_Order;  // note: <=10
   m_gravityModelEarth_N = E.m_gravityModelEarth_N;  // <=18
   m_gravityModelEarth_M = E.m_gravityModelEarth_M;  // <=18
   m_gravityModelMars_N = E.m_gravityModelMars_N;   // <=18
   m_gravityModelMars_M = E.m_gravityModelMars_M;   // <=18
   m_gravityModelLuna_N = E.m_gravityModelLuna_N;   // <=18
   m_gravityModelLuna_M = E.m_gravityModelLuna_M;   // <=18
   m_aerodynamicForces = E.m_aerodynamicForces;
   m_aerodynamicTorques = E.m_aerodynamicTorques;
   m_gravityGradientTorques = E.m_gravityGradientTorques;
   m_solarPressureForces = E.m_solarPressureForces;
   m_solarPressureTorques = E.m_solarPressureTorques;
   m_gravityPerturbationForces = E.m_gravityPerturbationForces;
   m_passiveJointForcesTorques = E.m_passiveJointForcesTorques;
   m_thrusterPlumeForcesTorques = E.m_thrusterPlumeForcesTorques;
   m_RWA_ImbalanceForcesTorques = E.m_RWA_ImbalanceForcesTorques;
   m_contactForcesTorques = E.m_contactForcesTorques;
   m_CFDsloshForceTorques = E.m_CFDsloshForceTorques;
   m_outPutEnvironmentalTorquesToFiles = E.m_outPutEnvironmentalTorquesToFiles;
   return *this;
}


void InpSimEnvironment::duplicate(const InpSimEnvironment& E)
{
    m_date = E.m_date;
    m_time = E.m_time;
    m_timeOffset = E.m_timeOffset; // unit: sec
    m_modelDateInterpolationSolarFlux_APValue = E.m_modelDateInterpolationSolarFlux_APValue; // could be TWOSIGMA_KP, NOMINAL or USER_DEFINED
    m_userDefined_F10_7 = E.m_userDefined_F10_7;
    m_userDefined_APvalue = E.m_userDefined_APvalue;
    m_magfield = E.m_magfield; // could be NONE, DIPOLE, IGRF
    m_IGRF_Degree = E.m_IGRF_Degree;
    m_IGRF_Order = E.m_IGRF_Order;  // note: <=10
    m_gravityModelEarth_N = E.m_gravityModelEarth_N;  // <=18
    m_gravityModelEarth_M = E.m_gravityModelEarth_M;  // <=18
    m_gravityModelMars_N = E.m_gravityModelMars_N;   // <=18
    m_gravityModelMars_M = E.m_gravityModelMars_M;   // <=18
    m_gravityModelLuna_N = E.m_gravityModelLuna_N;   // <=18
    m_gravityModelLuna_M = E.m_gravityModelLuna_M;   // <=18
    m_aerodynamicForces = E.m_aerodynamicForces;
    m_aerodynamicTorques = E.m_aerodynamicTorques;
    m_gravityGradientTorques = E.m_gravityGradientTorques;
    m_solarPressureForces = E.m_solarPressureForces;
    m_solarPressureTorques = E.m_solarPressureTorques;
    m_gravityPerturbationForces = E.m_gravityPerturbationForces;
    m_passiveJointForcesTorques = E.m_passiveJointForcesTorques;
    m_thrusterPlumeForcesTorques = E.m_thrusterPlumeForcesTorques;
    m_RWA_ImbalanceForcesTorques = E.m_RWA_ImbalanceForcesTorques;
    m_contactForcesTorques = E.m_contactForcesTorques;
    m_CFDsloshForceTorques = E.m_CFDsloshForceTorques;
    m_outPutEnvironmentalTorquesToFiles = E.m_outPutEnvironmentalTorquesToFiles;
}

void InpSimEnvironment::edit(const QDate& date, const QTime& time, const double& timeOffset,
                             const QString& modelDateInterpolationSolarFlux_APValue,
                             const double& userDefined_F10_7, const double& userDefined_APvalue,
                             const QString& magfield,
                             const int& IGRF_Degree, const int& IGRF_Order,
                             const int& gravityModelEarth_N , const int& gravityModelEarth_M ,
                             const int& gravityModelMars_N  , const int& gravityModelMars_M ,
                             const int& gravityModelLuna_N  , const int& gravityModelLuna_M ,
                             const bool& aerodynamicForces, const bool& aerodynamicTorques,
                             const bool& gravityGradientTorques,
                             const bool& solarPressureForces,  const bool& solarPressureTorques,
                             const bool& gravityPerturbationForces, const bool& passiveJointForcesTorques,
                             const bool& thrusterPlumeForcesTorques,
                             const bool& RWA_ImbalanceForcesTorques, const bool& contactForcesTorques,
                             const bool& CFDsloshForceTorques, const bool& outPutEnvironmentalTorquesToFiles)
{
    m_date = date;
    m_time = time;
    m_timeOffset = timeOffset; // unit: sec
    m_modelDateInterpolationSolarFlux_APValue = modelDateInterpolationSolarFlux_APValue.trimmed();
    // could be TWOSIGMA_KP, NOMINAL or USER_DEFINED
    m_userDefined_F10_7 = userDefined_F10_7;
    m_userDefined_APvalue = userDefined_APvalue;
    m_magfield = magfield.trimmed(); // could be NONE, DIPOLE, IGRF
    m_IGRF_Degree = IGRF_Degree;
    m_IGRF_Order = IGRF_Order;  // note: <=10
    m_gravityModelEarth_N = gravityModelEarth_N;  // <=18
    m_gravityModelEarth_M = gravityModelEarth_M;  // <=18
    m_gravityModelMars_N = gravityModelMars_N;   // <=18
    m_gravityModelMars_M = gravityModelMars_M;   // <=18
    m_gravityModelLuna_N = gravityModelLuna_N;   // <=18
    m_gravityModelLuna_M = gravityModelLuna_M;   // <=18
    m_aerodynamicForces = aerodynamicForces;
    m_aerodynamicTorques = aerodynamicTorques;
    m_gravityGradientTorques = gravityGradientTorques;
    m_solarPressureForces = solarPressureForces;
    m_solarPressureTorques = solarPressureTorques;
    m_gravityPerturbationForces = gravityPerturbationForces;
    m_passiveJointForcesTorques = passiveJointForcesTorques;
    m_thrusterPlumeForcesTorques = thrusterPlumeForcesTorques;
    m_RWA_ImbalanceForcesTorques = RWA_ImbalanceForcesTorques;
    m_contactForcesTorques = contactForcesTorques;
    m_CFDsloshForceTorques = CFDsloshForceTorques;
    m_outPutEnvironmentalTorquesToFiles = outPutEnvironmentalTorquesToFiles;
}

QDataStream& operator<< (QDataStream& dataStream, const InpSimEnvironment& E)
{
    dataStream << E.m_date
               << E.m_time
               << E.m_timeOffset
               << E.m_modelDateInterpolationSolarFlux_APValue
               << E.m_userDefined_F10_7
               << E.m_userDefined_APvalue
               << E.m_magfield
               << E.m_IGRF_Degree
               << E.m_IGRF_Order
               << E.m_gravityModelEarth_N
               << E.m_gravityModelEarth_M
               << E.m_gravityModelMars_N
               << E.m_gravityModelMars_M
               << E.m_gravityModelLuna_N
               << E.m_gravityModelLuna_M
               << E.m_aerodynamicForces
               << E.m_aerodynamicTorques
               << E.m_gravityGradientTorques
               << E.m_solarPressureForces
               << E.m_solarPressureTorques
               << E.m_gravityPerturbationForces
               << E.m_passiveJointForcesTorques
               << E.m_thrusterPlumeForcesTorques
               << E.m_RWA_ImbalanceForcesTorques
               << E.m_contactForcesTorques
               << E.m_CFDsloshForceTorques
               << E.m_outPutEnvironmentalTorquesToFiles;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, InpSimEnvironment& E)
{
    dataStream >> E.m_date
               >> E.m_time
               >> E.m_timeOffset
               >> E.m_modelDateInterpolationSolarFlux_APValue
               >> E.m_userDefined_F10_7
               >> E.m_userDefined_APvalue
               >> E.m_magfield
               >> E.m_IGRF_Degree
               >> E.m_IGRF_Order
               >> E.m_gravityModelEarth_N
               >> E.m_gravityModelEarth_M
               >> E.m_gravityModelMars_N
               >> E.m_gravityModelMars_M
               >> E.m_gravityModelLuna_N
               >> E.m_gravityModelLuna_M
               >> E.m_aerodynamicForces
               >> E.m_aerodynamicTorques
               >> E.m_gravityGradientTorques
               >> E.m_solarPressureForces
               >> E.m_solarPressureTorques
               >> E.m_gravityPerturbationForces
               >> E.m_passiveJointForcesTorques
               >> E.m_thrusterPlumeForcesTorques
               >> E.m_RWA_ImbalanceForcesTorques
               >> E.m_contactForcesTorques
               >> E.m_CFDsloshForceTorques
               >> E.m_outPutEnvironmentalTorquesToFiles;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const InpSimEnvironment& E)
{
    dataStream << E.m_date
               << E.m_time
               << E.m_timeOffset
               << E.m_modelDateInterpolationSolarFlux_APValue
               << E.m_userDefined_F10_7
               << E.m_userDefined_APvalue
               << E.m_magfield
               << E.m_IGRF_Degree
               << E.m_IGRF_Order
               << E.m_gravityModelEarth_N
               << E.m_gravityModelEarth_M
               << E.m_gravityModelMars_N
               << E.m_gravityModelMars_M
               << E.m_gravityModelLuna_N
               << E.m_gravityModelLuna_M
               << E.m_aerodynamicForces
               << E.m_aerodynamicTorques
               << E.m_gravityGradientTorques
               << E.m_solarPressureForces
               << E.m_solarPressureTorques
               << E.m_gravityPerturbationForces
               << E.m_passiveJointForcesTorques
               << E.m_thrusterPlumeForcesTorques
               << E.m_RWA_ImbalanceForcesTorques
               << E.m_contactForcesTorques
               << E.m_CFDsloshForceTorques
               << E.m_outPutEnvironmentalTorquesToFiles;

    return dataStream;
}

/** InpSimCelestialBody **/
InpSimCelestialBody::InpSimCelestialBody(InpSimHeader* inpsimheader, Mission* mission) :
    m_inpsimheader(inpsimheader), m_mission(mission)
{
    changeType(m_type);
}



InpSimCelestialBody::~InpSimCelestialBody()
{
}

InpSimCelestialBody::InpSimCelestialBody(const InpSimCelestialBody& C) : Qt42BaseClass(C)
{
    m_inpsimheader = C.m_inpsimheader;
    m_mission = C.m_mission;
    m_EphemOption = C.m_EphemOption;
    m_Mercury = C.m_Mercury;
    m_Venus = C.m_Venus;
    m_EarthLuna = C.m_EarthLuna;
    m_MarsAndMoons = C.m_MarsAndMoons;
    m_JupiterAndMoons = C.m_JupiterAndMoons;
    m_SaturnAndMoons = C.m_SaturnAndMoons;
    m_UranusAndMoons = C.m_UranusAndMoons;
    m_NeptuneAndMoons = C.m_NeptuneAndMoons;
    m_PlutoAndMoons = C.m_PlutoAndMoons;
    m_AsteroidsAndComets = C.m_AsteroidsAndComets;
}

InpSimCelestialBody& InpSimCelestialBody::operator=(const InpSimCelestialBody &C)
{
    if (this == &C)
        return *this;
    m_inpsimheader = C.m_inpsimheader;
    m_mission = C.m_mission;
    m_EphemOption = C.m_EphemOption;
    m_Mercury = C.m_Mercury;
    m_Venus = C.m_Venus;
    m_EarthLuna = C.m_EarthLuna;
    m_MarsAndMoons = C.m_MarsAndMoons;
    m_JupiterAndMoons = C.m_JupiterAndMoons;
    m_SaturnAndMoons = C.m_SaturnAndMoons;
    m_UranusAndMoons = C.m_UranusAndMoons;
    m_NeptuneAndMoons = C.m_NeptuneAndMoons;
    m_PlutoAndMoons = C.m_PlutoAndMoons;
    m_AsteroidsAndComets = C.m_AsteroidsAndComets;
    return *this;
}

void InpSimCelestialBody::duplicate(const InpSimCelestialBody &C)
{
    m_EphemOption = C.m_EphemOption;
    m_Mercury = C.m_Mercury;
    m_Venus = C.m_Venus;
    m_EarthLuna = C.m_EarthLuna;
    m_MarsAndMoons = C.m_MarsAndMoons;
    m_JupiterAndMoons = C.m_JupiterAndMoons;
    m_SaturnAndMoons = C.m_SaturnAndMoons;
    m_UranusAndMoons = C.m_UranusAndMoons;
    m_NeptuneAndMoons = C.m_NeptuneAndMoons;
    m_PlutoAndMoons = C.m_PlutoAndMoons;
    m_AsteroidsAndComets = C.m_AsteroidsAndComets;
}

void InpSimCelestialBody::edit(const QString &EphemOption, const bool &Mercury,
                               const bool &Venus, const bool &EarthLuna,
                               const bool &MarsAndMoons, const bool &JupiterAndMoons,
                               const bool &SaturnAndMoons, const bool &UranusAndMoons,
                               const bool &NeptuneAndMoons, const bool &PlutoAndMoons,
                               const bool &AsteroidsAndComets)
{
    m_EphemOption = EphemOption.trimmed();
    m_Mercury = Mercury;
    m_Venus = Venus;
    m_EarthLuna = EarthLuna;
    m_MarsAndMoons = MarsAndMoons;
    m_JupiterAndMoons = JupiterAndMoons;
    m_SaturnAndMoons = SaturnAndMoons;
    m_UranusAndMoons = UranusAndMoons;
    m_NeptuneAndMoons = NeptuneAndMoons;
    m_PlutoAndMoons = PlutoAndMoons;
    m_AsteroidsAndComets = AsteroidsAndComets;
}

QDataStream& operator<< (QDataStream& dataStream, const InpSimCelestialBody& CB)
{
    dataStream << CB.m_EphemOption
               << CB.m_Mercury
               << CB.m_Venus
               << CB.m_EarthLuna
               << CB.m_MarsAndMoons
               << CB.m_JupiterAndMoons
               << CB.m_SaturnAndMoons
               << CB.m_UranusAndMoons
               << CB.m_NeptuneAndMoons
               << CB.m_PlutoAndMoons
               << CB.m_AsteroidsAndComets;
    return dataStream;
}
QDataStream& operator>> (QDataStream& dataStream, InpSimCelestialBody& CB)
{
    dataStream >> CB.m_EphemOption
               >> CB.m_Mercury
               >> CB.m_Venus
               >> CB.m_EarthLuna
               >> CB.m_MarsAndMoons
               >> CB.m_JupiterAndMoons
               >> CB.m_SaturnAndMoons
               >> CB.m_UranusAndMoons
               >> CB.m_NeptuneAndMoons
               >> CB.m_PlutoAndMoons
               >> CB.m_AsteroidsAndComets;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const InpSimCelestialBody& CB)
{
    dataStream << CB.m_EphemOption
               << CB.m_Mercury
               << CB.m_Venus
               << CB.m_EarthLuna
               << CB.m_MarsAndMoons
               << CB.m_JupiterAndMoons
               << CB.m_SaturnAndMoons
               << CB.m_UranusAndMoons
               << CB.m_NeptuneAndMoons
               << CB.m_PlutoAndMoons
               << CB.m_AsteroidsAndComets;
    return dataStream;
}

/** InpSimLagrangePointSystem **/
InpSimLagrangePointSystem::InpSimLagrangePointSystem(InpSimHeader* inpsimheader, Mission* mission):
    m_inpsimheader(inpsimheader), m_mission(mission)
{
    changeType(m_type);
}

InpSimLagrangePointSystem::~InpSimLagrangePointSystem()
{

}

InpSimLagrangePointSystem::InpSimLagrangePointSystem(const InpSimLagrangePointSystem& L) : Qt42BaseClass(L)
{
    m_inpsimheader = L.m_inpsimheader;
    m_mission = L.m_mission;
    m_EarthMoon = L.m_EarthMoon;
    m_SunEarth = L.m_SunEarth;
    m_SunJupiter = L.m_SunJupiter;
}

InpSimLagrangePointSystem& InpSimLagrangePointSystem::operator=(const InpSimLagrangePointSystem &L)
{
    if (this == &L)
        return *this;
    m_inpsimheader = L.m_inpsimheader;
    m_mission = L.m_mission;
    m_EarthMoon = L.m_EarthMoon;
    m_SunEarth = L.m_SunEarth;
    m_SunJupiter = L.m_SunJupiter;
    return *this;
}

void InpSimLagrangePointSystem::duplicate(const InpSimLagrangePointSystem &L)
{
    m_EarthMoon = L.m_EarthMoon;
    m_SunEarth = L.m_SunEarth;
    m_SunJupiter = L.m_SunJupiter;
}

void InpSimLagrangePointSystem::edit(const bool &EarthMoon, const bool &SunEarth,
                                     const bool &SunJupiter)
{
    m_EarthMoon = EarthMoon;
    m_SunEarth = SunEarth;
    m_SunJupiter = SunJupiter;
}

QDataStream& operator<< (QDataStream& dataStream, const InpSimLagrangePointSystem& LPS)
{
    dataStream << LPS.m_EarthMoon
               << LPS.m_SunEarth
               << LPS.m_SunJupiter;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, InpSimLagrangePointSystem& LPS)
{
    dataStream >> LPS.m_EarthMoon
               >> LPS.m_SunEarth
               >> LPS.m_SunJupiter;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const InpSimLagrangePointSystem& LPS)
{
    dataStream << LPS.m_EarthMoon
               << LPS.m_SunEarth
               << LPS.m_SunJupiter;
    return dataStream;
}

/** Ground Station **/
InpSimGroundStation::InpSimGroundStation(InpSimHeader* inpsimheader, Mission* mission) :
    m_inpsimheader(inpsimheader), m_mission(mission)
{
    changeType(m_type);
    createGroundStation();
    createGroundStation();
    createGroundStation();

    groundStation(0).edit(false, "Mars", 100.0, -10.0, "LABEL0");
    groundStation(1).edit(false, "Venus", 120.0,  20.0, "LABEL1");
    groundStation(2).edit(false, "Jupiter", 130.0, -30.0, "LABEL2");
}

InpSimGroundStation::InpSimGroundStation(const InpSimGroundStation& G) : Qt42BaseClass(G)
{
    m_inpsimheader = G.m_inpsimheader;
    m_mission = G.m_mission;
    m_qvecGroundStation = G.m_qvecGroundStation;
}

InpSimGroundStation::~InpSimGroundStation()
{

}

InpSimGroundStation& InpSimGroundStation::operator=(const InpSimGroundStation &G)
{
    if (this == &G)
        return *this;
    m_inpsimheader = G.m_inpsimheader;
    m_mission = G.m_mission;
    m_qvecGroundStation = G.m_qvecGroundStation;
    return *this;

}

void InpSimGroundStation::duplicate(const InpSimGroundStation &G)
{
    m_qvecGroundStation = G.m_qvecGroundStation;
}

GroundStation& InpSimGroundStation::groundStation(const int &index)
{
        return m_qvecGroundStation[index];
}

bool InpSimGroundStation::createGroundStation(const int& index, const GroundStation& GS)
{
    if (index < -1 || index > m_qvecGroundStation.size())
        return false;
    m_qvecGroundStation.insert(index, GS);
    for (int i = 0; i < m_qvecGroundStation.size(); ++i)
        m_qvecGroundStation[i].setIndex(i);
    return true;
}

bool InpSimGroundStation::createGroundStation()
{
    int indexOfDefaultGS = 0;
    for (GroundStation gs : m_qvecGroundStation)
    {
        QString label = gs.label().trimmed();
        QStringList list = label.split("-");
        if (list[0].trimmed() == gs.defaultName())
        {
            if (indexOfDefaultGS <= list[1].toInt())
                indexOfDefaultGS = list[1].toInt() + 1;
        }
    }
    GroundStation GS;
    GS.rename(GS.defaultName()+"-"+QString::number(indexOfDefaultGS));
    m_qvecGroundStation.append(GS);
    for (int i = 0; i < m_qvecGroundStation.size(); ++i)
        m_qvecGroundStation[i].setIndex(i);
    return true;
}


bool InpSimGroundStation::removeGroundStation(const int& index)
{
    if (index < -1 || index > m_qvecGroundStation.size())
        return false;
    m_qvecGroundStation.remove(index);
    for (int i = 0; i < m_qvecGroundStation.size(); ++i)
        m_qvecGroundStation[i].setIndex(i);
    return true;
}

QDataStream& operator<< (QDataStream& dataStream, const InpSimGroundStation& IGS)
{
    dataStream << IGS.m_qvecGroundStation;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, InpSimGroundStation& IGS)
{
    dataStream >> IGS.m_qvecGroundStation;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const InpSimGroundStation& IGS)
{
    dataStream << IGS.m_qvecGroundStation;
    return dataStream;
}


/** Ground Station Object **/
GroundStation::GroundStation()
{
}

GroundStation::GroundStation(const GroundStation& GS)
{
    m_index = GS.m_index;
    m_existed = GS.m_existed;
    m_world = GS.m_world;
    m_longitude = GS.m_longitude;
    m_latitude = GS.m_latitude;
    m_label = GS.m_label;
}

GroundStation::~GroundStation()
{

}

GroundStation& GroundStation::operator=(const GroundStation &GS)
{
    if (this == &GS)
        return *this;
    m_index = GS.m_index;
    m_existed = GS.m_existed;
    m_world = GS.m_world;
    m_longitude = GS.m_longitude;
    m_latitude = GS.m_latitude;
    m_label = GS.m_label;
    return *this;
}



void GroundStation::edit(const bool &existed, const QString &world,
                         const double &longitude, const double& latitude,
                         const QString &label)
{
    m_existed = existed;
    m_world = world.trimmed().toUpper();
    m_longitude = longitude;
    m_latitude = latitude;
    m_label = label;
}

QDataStream& operator<< (QDataStream& dataStream, const GroundStation& GS)
{
    dataStream << GS.m_existed
               << GS.m_world.toUpper()
               << GS.m_longitude
               << GS.m_latitude
               << GS.m_label;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, GroundStation& GS)
{
    dataStream >> GS.m_existed
               >> GS.m_world
               >> GS.m_longitude
               >> GS.m_latitude
               >> GS.m_label;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const GroundStation& GS)
{
    dataStream << GS.m_existed
               << GS.m_world.toUpper()
               << GS.m_longitude
               << GS.m_latitude
               << GS.m_label;
    return dataStream;
}

bool GroundStation::operator==(const GroundStation &gs) const
{
    const double epsilon = 0.0000001;

    return
    m_index == gs.m_index &&
    m_existed == gs.m_existed &&
    m_world.toUpper() == gs.m_world.toUpper() &&
    std::abs(m_longitude - gs.m_longitude) < epsilon &&
    std::abs(m_latitude - gs.m_latitude) < epsilon &&
    m_label == gs.m_label;
}
