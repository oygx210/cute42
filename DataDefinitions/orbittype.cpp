#include "DataHeaders/orbittype.h"
#include <QDebug>
#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/mission.h"
#include "ShareHeaders/qt42_sharedparameters.h"


/*******  Orbit Type: Zero *******/
OrbitZERO::OrbitZERO()
{
    changeType(m_type);
}

OrbitZERO::OrbitZERO(const OrbitZERO& OrbitZ) : Qt42BaseClass(OrbitZ)
{
    m_world = OrbitZ.m_world;
    m_UsePolyhedronGravity = OrbitZ.m_UsePolyhedronGravity;
    m_includedInCalculation = OrbitZ.m_includedInCalculation;
}

OrbitZERO::~OrbitZERO()
{

}


OrbitZERO& OrbitZERO::operator=(const OrbitZERO& OrbitZ)
{
    if (*this == OrbitZ)
        return *this;

    m_world = OrbitZ.m_world;
    m_UsePolyhedronGravity = OrbitZ.m_UsePolyhedronGravity;
    m_includedInCalculation = OrbitZ.m_includedInCalculation;
    return *this;
}

void OrbitZERO::edit(const QString &World, bool UsePolyhedronGRavity, const bool &included)
{
    m_world = World;
    m_UsePolyhedronGravity = UsePolyhedronGRavity;
    m_includedInCalculation = included;
}

bool operator==(const OrbitZERO& z1, const OrbitZERO& z2)
{
    return  z1.m_world == z2.m_world &&
            z1.m_UsePolyhedronGravity == z2.m_UsePolyhedronGravity &&
            z1.m_includedInCalculation == z2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const OrbitZERO& oz)
{
    dataStream << oz.m_world
               << oz.m_UsePolyhedronGravity
               << oz.m_includedInCalculation;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, OrbitZERO& oz)
{
    dataStream >> oz.m_world
               >> oz.m_UsePolyhedronGravity
               >> oz.m_includedInCalculation;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const OrbitZERO& oz)
{
    dataStream << oz.m_world
               << oz.m_UsePolyhedronGravity
               << oz.m_includedInCalculation;
    return dataStream;
}


/********     Orbit Type: Flight  *******/
OrbitFLIGHT::OrbitFLIGHT()
{
    changeType(m_type);
}

OrbitFLIGHT::OrbitFLIGHT(const OrbitFLIGHT& OrbitF) : Qt42BaseClass(OrbitF)
{
    m_RegionNumber = OrbitF.m_RegionNumber;
    m_UsePolyhedronGravity = OrbitF.m_UsePolyhedronGravity;
    m_includedInCalculation = OrbitF.m_includedInCalculation;
}

OrbitFLIGHT::~OrbitFLIGHT()
{

}

OrbitFLIGHT& OrbitFLIGHT::operator=(const OrbitFLIGHT &OrbitF)
{
    if (*this == OrbitF)
        return *this;
    m_RegionNumber = OrbitF.m_RegionNumber;
    m_UsePolyhedronGravity = OrbitF.m_UsePolyhedronGravity;
    m_includedInCalculation = OrbitF.m_includedInCalculation;
    return *this;
}

void OrbitFLIGHT::edit(const int &regionNumber, const bool &usePolyhedronGravity, const bool &included)
{
    m_RegionNumber = regionNumber;
    m_UsePolyhedronGravity = usePolyhedronGravity;
    m_includedInCalculation = included;
}

bool operator==(const OrbitFLIGHT& F1, const OrbitFLIGHT& F2)
{
    return  F1.m_RegionNumber == F2.m_RegionNumber &&
            F1.m_UsePolyhedronGravity == F2.m_UsePolyhedronGravity &&
            F1.m_includedInCalculation == F2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const OrbitFLIGHT& of)
{
    dataStream << of.m_RegionNumber
               << of.m_UsePolyhedronGravity
               << of.m_includedInCalculation;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, OrbitFLIGHT& of)
{
    dataStream >> of.m_RegionNumber
               >> of.m_UsePolyhedronGravity
               >> of.m_includedInCalculation;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const OrbitFLIGHT& of)
{
    dataStream << of.m_RegionNumber
               << of.m_UsePolyhedronGravity
               << of.m_includedInCalculation;
    return dataStream;
}


/**     Orbit Type: Central-Body **/

OrbitCENTRAL::OrbitCENTRAL()
{
    changeType(m_type);
}
OrbitCENTRAL::OrbitCENTRAL(const OrbitCENTRAL& OrbitC) : Qt42BaseClass(OrbitC)
{

    m_OrbitCenter = OrbitC.m_OrbitCenter;
    m_SecularOrbitDriftDueToJ2 = OrbitC.m_SecularOrbitDriftDueToJ2;
    m_OrbitDeterminedby = OrbitC.m_OrbitKEPdeterminedby;
    m_OrbitKEPdeterminedby = OrbitC.m_OrbitKEPdeterminedby;
    m_qvecPeriapsisApoapsis= OrbitC.m_qvecPeriapsisApoapsis;
    m_qvecMinAltitudeEccentricuty = OrbitC.m_qvecMinAltitudeEccentricuty;
    m_Inclination = OrbitC.m_Inclination;
    m_RAAN = OrbitC.m_RAAN;
    m_AOP = OrbitC.m_AOP;
    m_TrueAnomaly = OrbitC.trueAnomaly();
    m_qvecRVInitialPosition = OrbitC.m_qvecRVInitialPosition;
    m_qvecRVInitialVelocity = OrbitC.m_qvecRVInitialVelocity;
    m_format = OrbitC.m_format;
    m_labelInFile = OrbitC.m_labelInFile;
    m_fileName = OrbitC.m_fileName;
    m_includedInCalculation = OrbitC.m_includedInCalculation;
}

OrbitCENTRAL::~OrbitCENTRAL()
{

}
OrbitCENTRAL& OrbitCENTRAL::operator=(const OrbitCENTRAL& OrbitC)
{
    if (*this == OrbitC)
        return *this;
    m_OrbitCenter = OrbitC.m_OrbitCenter;
    m_SecularOrbitDriftDueToJ2 = OrbitC.m_SecularOrbitDriftDueToJ2;
    m_OrbitDeterminedby = OrbitC.m_OrbitKEPdeterminedby;
    m_OrbitKEPdeterminedby = OrbitC.m_OrbitKEPdeterminedby;
    m_qvecPeriapsisApoapsis= OrbitC.m_qvecPeriapsisApoapsis;
    m_qvecMinAltitudeEccentricuty = OrbitC.m_qvecMinAltitudeEccentricuty;
    m_Inclination = OrbitC.m_Inclination;
    m_RAAN = OrbitC.m_RAAN;
    m_AOP = OrbitC.m_AOP;
    m_TrueAnomaly = OrbitC.m_TrueAnomaly;
    m_qvecRVInitialPosition = OrbitC.m_qvecRVInitialPosition;
    m_qvecRVInitialVelocity = OrbitC.m_qvecRVInitialVelocity;
    m_format = OrbitC.m_format;
    m_labelInFile = OrbitC.m_labelInFile;
    m_fileName = OrbitC.m_fileName;
    m_includedInCalculation = OrbitC.m_includedInCalculation;
    return *this;

}

bool operator==(const OrbitCENTRAL& C1, const OrbitCENTRAL& C2)
{
    using std::abs;
    double epsilon = 0.0000001;
    return  C1.m_OrbitCenter == C2.m_OrbitCenter &&
            C1.m_SecularOrbitDriftDueToJ2 == C2.m_SecularOrbitDriftDueToJ2 &&
            C1.m_OrbitDeterminedby == C2.m_OrbitKEPdeterminedby &&
            C1.m_OrbitKEPdeterminedby == C2.m_OrbitKEPdeterminedby &&
            compareVector(C1.m_qvecPeriapsisApoapsis,
                          C2.m_qvecPeriapsisApoapsis,
                          epsilon) &&
            compareVector(C1.m_qvecMinAltitudeEccentricuty,
                          C2.m_qvecMinAltitudeEccentricuty,
                          epsilon) &&
            abs(C1.m_Inclination-C2.m_Inclination) < epsilon &&
            abs(C1.m_RAAN - C2.m_RAAN) < epsilon &&
            abs(C1.m_AOP - C2.m_AOP) < epsilon &&
            abs(C1.m_TrueAnomaly - C2.m_TrueAnomaly) < epsilon &&
            C1.m_qvecRVInitialPosition == C2.m_qvecRVInitialPosition &&
            compareVector(C1.m_qvecRVInitialVelocity,
                          C2.m_qvecRVInitialVelocity,
                          epsilon) &&
            C1.m_format == C2.m_format &&
            C1.m_labelInFile == C2.m_labelInFile &&
            C1.m_fileName == C2.m_fileName &&
            C1.m_includedInCalculation == C2.m_includedInCalculation;
}



void OrbitCENTRAL::edit(const QString &orbitCenter, const bool &secularOrbitDriftDueToJ2,
                        const QString &orbitDeterminedby,
                        const QString &orbitKEPdeterminedby,
                        const QVector<double> &periapsisApoapsis,
                        const QVector<double> &minAltitudeEccentricuty,
                        const double &inclination, const double &RAAN,
                        const double &AOP, const double &trueAnomaly,
                        const QVector<double> &RVInitialPosition,
                        const QVector<double> &RVInitialVelocity,
                        const QString &format, const QString &labelInFile,
                        const QString &fileName, const bool& included)
{
    m_OrbitCenter = orbitCenter;
    m_SecularOrbitDriftDueToJ2 = secularOrbitDriftDueToJ2;
    m_OrbitDeterminedby = orbitDeterminedby;
    m_OrbitKEPdeterminedby = orbitKEPdeterminedby;
    m_qvecPeriapsisApoapsis = periapsisApoapsis;
    m_qvecMinAltitudeEccentricuty = minAltitudeEccentricuty;
    m_Inclination = inclination;
    m_RAAN = RAAN;
    m_AOP = AOP;
    m_TrueAnomaly = trueAnomaly;
    m_qvecRVInitialPosition = RVInitialPosition;
    m_qvecRVInitialVelocity = RVInitialVelocity;
    m_format = format;
    m_labelInFile = labelInFile;
    m_fileName = fileName;
    m_includedInCalculation = included;
}

QDataStream& operator<< (QDataStream& dataStream, const OrbitCENTRAL& oc)
{
    dataStream << oc.m_OrbitCenter
               << oc.m_SecularOrbitDriftDueToJ2
               << oc.m_OrbitDeterminedby
               << oc.m_OrbitKEPdeterminedby
               << oc.m_qvecPeriapsisApoapsis
               << oc.m_qvecMinAltitudeEccentricuty
               << oc.m_Inclination
               << oc.m_RAAN
               << oc.m_AOP
               << oc.m_TrueAnomaly
               << oc.m_qvecRVInitialPosition
               << oc.m_qvecRVInitialVelocity
               << oc.m_format
               << oc.m_labelInFile
               << oc.m_fileName
               << oc.m_includedInCalculation;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, OrbitCENTRAL& oc)
{
    dataStream >> oc.m_OrbitCenter
               >> oc.m_SecularOrbitDriftDueToJ2
               >> oc.m_OrbitDeterminedby
               >> oc.m_OrbitKEPdeterminedby
               >> oc.m_qvecPeriapsisApoapsis
               >> oc.m_qvecMinAltitudeEccentricuty
               >> oc.m_Inclination
               >> oc.m_RAAN
               >> oc.m_AOP
               >> oc.m_TrueAnomaly
               >> oc.m_qvecRVInitialPosition
               >> oc.m_qvecRVInitialVelocity
               >> oc.m_format
               >> oc.m_labelInFile
               >> oc.m_fileName
               >> oc.m_includedInCalculation;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const OrbitCENTRAL& oc)
{
    dataStream << oc.m_OrbitCenter
               << oc.m_SecularOrbitDriftDueToJ2
               << oc.m_OrbitDeterminedby
               << oc.m_OrbitKEPdeterminedby
               << oc.m_qvecPeriapsisApoapsis
               << oc.m_qvecMinAltitudeEccentricuty
               << oc.m_Inclination
               << oc.m_RAAN
               << oc.m_AOP
               << oc.m_TrueAnomaly
               << oc.m_qvecRVInitialPosition
               << oc.m_qvecRVInitialVelocity
               << oc.m_format
               << oc.m_labelInFile
               << oc.m_fileName
               << oc.m_includedInCalculation;
    return dataStream;
}



/**  Orbit Type: Three-Body   **/

OrbitTHREEBODY::OrbitTHREEBODY()
{
    changeType(m_type);
}

OrbitTHREEBODY::OrbitTHREEBODY(const OrbitTHREEBODY& O3body) : Qt42BaseClass(O3body)
{
    m_LagrangeSystem = O3body.m_LagrangeSystem;
    m_Propagation = O3body.m_Propagation;
    m_Initialization = O3body.m_Initialization;
    m_LibrationPoint = O3body.m_LibrationPoint;
    m_XY_SemiMajorAxis = O3body.m_XY_SemiMajorAxis;
    m_InitialXYPhase = O3body.m_InitialXYPhase;
    m_SenseViewedfromZ = O3body.m_SenseViewedfromZ;
    m_SecondXYModeSemiMajorAxisL4L5only = O3body.m_SecondXYModeSemiMajorAxisL4L5only;
    m_SecondXYModeInitialPhaseL4L5only = O3body.m_SecondXYModeInitialPhaseL4L5only;
    m_SenseViewedfromZL4L5only = O3body.m_SenseViewedfromZL4L5only;
    m_ZSemiAxis = O3body.m_ZSemiAxis;
    m_InitialZPhase = O3body.m_InitialZPhase;
    m_qvecInitialXYZ_NonDimensional = O3body.m_qvecInitialXYZ_NonDimensional;
    m_qvecInitialXdotYdotZdot_NonDimensional = O3body.m_qvecInitialXdotYdotZdot_NonDimensional;
    m_format = O3body.m_format;
    m_labelInFile = O3body.m_labelInFile;
    m_fileName = O3body.m_fileName;
    m_includedInCalculation = O3body.m_includedInCalculation;
}

OrbitTHREEBODY::~OrbitTHREEBODY()
{

}

OrbitTHREEBODY& OrbitTHREEBODY::operator=(const OrbitTHREEBODY &O3body)
{
    if (*this == O3body)
        return *this;
    m_LagrangeSystem = O3body.m_LagrangeSystem;
    m_Propagation = O3body.m_Propagation;
    m_Initialization = O3body.m_Initialization;
    m_LibrationPoint = O3body.m_LibrationPoint;
    m_XY_SemiMajorAxis = O3body.m_XY_SemiMajorAxis;
    m_InitialXYPhase = O3body.m_InitialXYPhase;
    m_SenseViewedfromZ = O3body.m_SenseViewedfromZ;
    m_SecondXYModeSemiMajorAxisL4L5only = O3body.m_SecondXYModeSemiMajorAxisL4L5only;
    m_SecondXYModeInitialPhaseL4L5only = O3body.m_SecondXYModeInitialPhaseL4L5only;
    m_SenseViewedfromZL4L5only = O3body.m_SenseViewedfromZL4L5only;
    m_ZSemiAxis = O3body.m_ZSemiAxis;
    m_InitialZPhase = O3body.m_InitialZPhase;
    m_qvecInitialXYZ_NonDimensional = O3body.m_qvecInitialXYZ_NonDimensional;
    m_qvecInitialXdotYdotZdot_NonDimensional = O3body.m_qvecInitialXdotYdotZdot_NonDimensional;
    m_format = O3body.m_format;
    m_labelInFile = O3body.m_labelInFile;
    m_fileName = O3body.m_fileName;
    m_includedInCalculation = O3body.m_includedInCalculation;
    return *this;
}

bool operator==(const OrbitTHREEBODY& O3body1, const OrbitTHREEBODY& O3body2)
{
    using std::abs;
    double epsilon = 0.0000001;
    return
    O3body1.m_LagrangeSystem == O3body2.m_LagrangeSystem &&
    O3body1.m_Propagation == O3body2.m_Propagation &&
    O3body1.m_Initialization == O3body2.m_Initialization &&
    O3body1.m_LibrationPoint == O3body2.m_LibrationPoint &&
    abs(O3body1.m_XY_SemiMajorAxis - O3body2.m_XY_SemiMajorAxis) < epsilon &&
    abs(O3body1.m_InitialXYPhase - O3body2.m_InitialXYPhase) < epsilon &&
    O3body1.m_SenseViewedfromZ == O3body2.m_SenseViewedfromZ &&
    abs(O3body1.m_SecondXYModeSemiMajorAxisL4L5only-O3body2.m_SecondXYModeSemiMajorAxisL4L5only) < epsilon &&
    abs(O3body1.m_SecondXYModeInitialPhaseL4L5only-O3body2.m_SecondXYModeInitialPhaseL4L5only) < epsilon &&
    O3body1.m_SenseViewedfromZL4L5only == O3body2.m_SenseViewedfromZL4L5only &&
    abs(O3body1.m_ZSemiAxis-O3body2.m_ZSemiAxis) < epsilon &&
    abs(O3body1.m_InitialZPhase-O3body2.m_InitialZPhase) < epsilon &&
    compareVector(O3body1.m_qvecInitialXYZ_NonDimensional, O3body2.m_qvecInitialXYZ_NonDimensional, epsilon) &&
    compareVector(O3body1.m_qvecInitialXdotYdotZdot_NonDimensional, O3body2.m_qvecInitialXdotYdotZdot_NonDimensional, epsilon) &&
    O3body1.m_format == O3body2.m_format &&
    O3body1.m_labelInFile == O3body2.m_labelInFile &&
    O3body1.m_fileName == O3body2.m_fileName &&
    O3body1.m_includedInCalculation == O3body2.m_includedInCalculation;
}

void OrbitTHREEBODY::edit(const int &LagrangeSystem,
                          const QString &propagation,
                          const QString &initialization,
                          const int &LibrationPoint,
                          const double &XY_SemiMajorAxis,
                          const double &initialXYPhase,
                          const QString &senseViewedfromZ,
                          const double &secondXYModeSemiMajorAxisL4L5only,
                          const double &secondXYModeInitialPhaseL4L5only,
                          const QString &SenseViewedfromZL4L5only,
                          const double &ZSemiAxis,
                          const double &initialZPhase,
                          const QVector<double> &qvecInitialXYZ_NonDimensional,
                          const QVector<double> &qvecInitialXdotYdotZdot_NonDimensional,
                          const QString &format,
                          const QString &labelInFile,
                          const QString &fileName,
                          const bool& included)
{
    m_LagrangeSystem = LagrangeSystem;
    m_Propagation = propagation;
    m_Initialization = initialization;
    m_LibrationPoint = LibrationPoint;
    m_XY_SemiMajorAxis = XY_SemiMajorAxis;
    m_InitialXYPhase = initialXYPhase;
    m_SenseViewedfromZ = senseViewedfromZ;
    m_SecondXYModeSemiMajorAxisL4L5only = secondXYModeSemiMajorAxisL4L5only;
    m_SecondXYModeInitialPhaseL4L5only = secondXYModeInitialPhaseL4L5only;
    m_SenseViewedfromZL4L5only = SenseViewedfromZL4L5only;
    m_ZSemiAxis = ZSemiAxis;
    m_InitialZPhase = initialZPhase;
    m_qvecInitialXYZ_NonDimensional = qvecInitialXYZ_NonDimensional;
    m_qvecInitialXdotYdotZdot_NonDimensional = qvecInitialXdotYdotZdot_NonDimensional;
    m_format = format;
    m_labelInFile = labelInFile;
    m_fileName = fileName;
    m_includedInCalculation = included;
}

QDataStream& operator<< (QDataStream& dataStream, const OrbitTHREEBODY& o3)
{
    dataStream << o3.m_LagrangeSystem
               << o3.m_Propagation
               << o3.m_Initialization
               << o3.m_LibrationPoint
               << o3.m_XY_SemiMajorAxis
               << o3.m_InitialXYPhase
               << o3.m_SenseViewedfromZ
               << o3.m_SecondXYModeSemiMajorAxisL4L5only
               << o3.m_SecondXYModeInitialPhaseL4L5only
               << o3.m_SenseViewedfromZL4L5only
               << o3.m_ZSemiAxis
               << o3.m_InitialZPhase
               << o3.m_qvecInitialXYZ_NonDimensional
               << o3.m_qvecInitialXdotYdotZdot_NonDimensional
               << o3.m_format
               << o3.m_labelInFile
               << o3.m_fileName
               << o3.m_includedInCalculation;

    return dataStream;

}

QDataStream& operator>> (QDataStream& dataStream, OrbitTHREEBODY& o3)
{
    dataStream >> o3.m_LagrangeSystem
               >> o3.m_Propagation
               >> o3.m_Initialization
               >> o3.m_LibrationPoint
               >> o3.m_XY_SemiMajorAxis
               >> o3.m_InitialXYPhase
               >> o3.m_SenseViewedfromZ
               >> o3.m_SecondXYModeSemiMajorAxisL4L5only
               >> o3.m_SecondXYModeInitialPhaseL4L5only
               >> o3.m_SenseViewedfromZL4L5only
               >> o3.m_ZSemiAxis
               >> o3.m_InitialZPhase
               >> o3.m_qvecInitialXYZ_NonDimensional
               >> o3.m_qvecInitialXdotYdotZdot_NonDimensional
               >> o3.m_format
               >> o3.m_labelInFile
               >> o3.m_fileName
               >> o3.m_includedInCalculation;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const OrbitTHREEBODY& o3)
{
    dataStream << o3.m_LagrangeSystem
               << o3.m_Propagation
               << o3.m_Initialization
               << o3.m_LibrationPoint
               << o3.m_XY_SemiMajorAxis
               << o3.m_InitialXYPhase
               << o3.m_SenseViewedfromZ
               << o3.m_SecondXYModeSemiMajorAxisL4L5only
               << o3.m_SecondXYModeInitialPhaseL4L5only
               << o3.m_SenseViewedfromZL4L5only
               << o3.m_ZSemiAxis
               << o3.m_InitialZPhase
               << o3.m_qvecInitialXYZ_NonDimensional
               << o3.m_qvecInitialXdotYdotZdot_NonDimensional
               << o3.m_format
               << o3.m_labelInFile
               << o3.m_fileName
               << o3.m_includedInCalculation;
    return dataStream;
}

/****       Orbit        ****/

Orbit::Orbit(OrbitHeader* OH) : m_orbitHeader(OH)
{
    changeType(m_type);
    if (m_orbitHeader)
    {
        if (m_orbitHeader->parentItem())
            m_mission = m_orbitHeader->parentItem();
        QString defaultNumber = QString::number(m_orbitHeader->maxNumberDefaultOrbit()+1);
        m_name = defaultName+"-"+defaultNumber;
    }
}

Orbit::Orbit(const Orbit& OtherOrbit) : Qt42BaseClass(OtherOrbit)
{
    m_name = OtherOrbit.m_name;
    m_index = OtherOrbit.m_index;
    m_orbitHeader = OtherOrbit.m_orbitHeader;
    m_mission = OtherOrbit.m_mission;
    m_orbitType = OtherOrbit.m_orbitType;

    m_Description = OtherOrbit.m_Description;
    m_FormationFrameFixedIn = OtherOrbit.m_FormationFrameFixedIn;
    m_qvecEulerAngles = OtherOrbit.m_qvecEulerAngles;
    m_EulerSequence = OtherOrbit.m_EulerSequence;
    m_FormationOriginExpressedIn = OtherOrbit.m_FormationOriginExpressedIn;
    m_qvecFormationOriginRefOrbit = OtherOrbit.m_qvecFormationOriginRefOrbit;

    m_orbitzero = OtherOrbit.m_orbitzero;
    m_orbitflight = OtherOrbit.m_orbitflight;
    m_orbitcentral = OtherOrbit.m_orbitcentral;
    m_orbit3body = OtherOrbit.m_orbit3body;
    m_includedInCalculation = OtherOrbit.m_includedInCalculation;

}

Orbit::~Orbit()
{
}

Orbit& Orbit::operator=(const Orbit &OtherOrbit)
{
    if (*this == OtherOrbit)
        return *this;
    m_name = OtherOrbit.m_name;
    m_index = OtherOrbit.m_index;
    m_orbitHeader = OtherOrbit.m_orbitHeader;
    m_mission = OtherOrbit.m_mission;
    m_orbitType = OtherOrbit.m_orbitType;

    m_Description = OtherOrbit.m_Description;
    m_FormationFrameFixedIn = OtherOrbit.m_FormationFrameFixedIn;
    m_qvecEulerAngles = OtherOrbit.m_qvecEulerAngles;
    m_EulerSequence = OtherOrbit.m_EulerSequence;
    m_FormationOriginExpressedIn = OtherOrbit.m_FormationOriginExpressedIn;
    m_qvecFormationOriginRefOrbit = OtherOrbit.m_qvecFormationOriginRefOrbit;

    m_orbitzero = OtherOrbit.m_orbitzero;
    m_orbitflight = OtherOrbit.m_orbitflight;
    m_orbitcentral = OtherOrbit.m_orbitcentral;
    m_orbit3body = OtherOrbit.m_orbit3body;
    m_includedInCalculation = OtherOrbit.m_includedInCalculation;
    return *this;
}

bool operator== (const Orbit& OtherOrbit1, const Orbit& OtherOrbit2)
{
    double epsilon = 0.00001;
    return

    OtherOrbit1.m_includedInCalculation == OtherOrbit2.m_includedInCalculation &&
    OtherOrbit1.m_name == OtherOrbit2.m_name &&
    OtherOrbit1.m_index == OtherOrbit2.m_index &&
    OtherOrbit1.m_orbitHeader == OtherOrbit2.m_orbitHeader &&
    OtherOrbit1.m_mission == OtherOrbit2.m_mission &&
    OtherOrbit1.m_orbitType == OtherOrbit2.m_orbitType &&
    OtherOrbit1.m_Description == OtherOrbit2.m_Description &&
    OtherOrbit1.m_FormationFrameFixedIn == OtherOrbit2.m_FormationFrameFixedIn &&
    compareVector(OtherOrbit1.m_qvecEulerAngles, OtherOrbit2.m_qvecEulerAngles, epsilon) &&
    OtherOrbit1.m_EulerSequence == OtherOrbit2.m_EulerSequence &&
    OtherOrbit1.m_FormationOriginExpressedIn == OtherOrbit2.m_FormationOriginExpressedIn &&
    compareVector(OtherOrbit1.m_qvecFormationOriginRefOrbit, OtherOrbit2.m_qvecFormationOriginRefOrbit, epsilon) &&
    OtherOrbit1.m_orbitzero == OtherOrbit2.m_orbitzero &&
    OtherOrbit1.m_orbitflight == OtherOrbit2.m_orbitflight &&
    OtherOrbit1.m_orbitcentral == OtherOrbit2.m_orbitcentral &&
    OtherOrbit1.m_orbit3body == OtherOrbit2.m_orbit3body &&
    OtherOrbit1.m_includedInCalculation == OtherOrbit2.m_includedInCalculation;
}

void Orbit::updateIndex()
{
    if (m_orbitHeader)
        m_index = m_orbitHeader->indexOrbit(this);
    else
        m_index = -1;
}

bool Orbit::hasName (const QString& name) const
{
    if (m_orbitHeader)
    {
        return m_orbitHeader->hasOrbitNamedAs(name.trimmed());
    }
    return false;
}
void Orbit::rename(const QString& newName)
{
    if (!hasName(newName))
        m_name = newName;
}

void Orbit::edit(const QString& orbitType, const QString &description,
                 const QString &formationFrameFixedIn, const QVector<double> &eulerAngles,
                 const QString &eulerSequence, const QString &formationOriginExpressedIn,
                 const QVector<double> &formationOriginRefOrbit,
                 const bool& included)
{
    m_orbitType = orbitType;
    m_Description = description;
    m_FormationFrameFixedIn = formationFrameFixedIn;
    m_qvecEulerAngles = eulerAngles;
    m_EulerSequence = eulerSequence;
    m_FormationOriginExpressedIn = formationOriginExpressedIn;
    m_qvecFormationOriginRefOrbit = formationOriginRefOrbit;
    m_includedInCalculation = included;
}

void Orbit::duplicate(const Orbit &OtherOrbit)
{
    m_name = OtherOrbit.m_name;
    m_index = OtherOrbit.m_index;
    m_orbitType = OtherOrbit.m_orbitType;
    m_Description = OtherOrbit.m_Description;
    m_FormationFrameFixedIn = OtherOrbit.m_FormationFrameFixedIn;
    m_qvecEulerAngles = OtherOrbit.m_qvecEulerAngles;
    m_EulerSequence = OtherOrbit.m_EulerSequence;
    m_FormationOriginExpressedIn = OtherOrbit.m_FormationOriginExpressedIn;
    m_qvecFormationOriginRefOrbit = OtherOrbit.m_qvecFormationOriginRefOrbit;
    m_orbitzero = OtherOrbit.m_orbitzero;
    m_orbitflight = OtherOrbit.m_orbitflight;
    m_orbitcentral = OtherOrbit.m_orbitcentral;
    m_orbit3body = OtherOrbit.m_orbit3body;
    m_includedInCalculation = OtherOrbit.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const Orbit& o)
{
    dataStream << o.m_name
               << o.m_index
               << o.m_orbitType
               << o.m_Description
               << o.m_FormationFrameFixedIn
               << o.m_qvecEulerAngles
               << o.m_EulerSequence
               << o.m_FormationOriginExpressedIn
               << o.m_qvecFormationOriginRefOrbit
               << o.m_includedInCalculation
               << o.m_orbitzero
               << o.m_orbitflight
               << o.m_orbitcentral
               << o.m_orbit3body;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, Orbit& o)
{
    dataStream >> o.m_name
               >> o.m_index
               >> o.m_orbitType
               >> o.m_Description
               >> o.m_FormationFrameFixedIn
               >> o.m_qvecEulerAngles
               >> o.m_EulerSequence
               >> o.m_FormationOriginExpressedIn
               >> o.m_qvecFormationOriginRefOrbit
               >> o.m_includedInCalculation
               >> o.m_orbitzero
               >> o.m_orbitflight
               >> o.m_orbitcentral
               >> o.m_orbit3body;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const Orbit& o)
{
    dataStream << o.m_name
               << o.m_index
               << o.m_orbitType
               << o.m_Description
               << o.m_FormationFrameFixedIn
               << o.m_qvecEulerAngles
               << o.m_EulerSequence
               << o.m_FormationOriginExpressedIn
               << o.m_qvecFormationOriginRefOrbit
               << o.m_includedInCalculation
               << o.m_orbitzero
               << o.m_orbitflight
               << o.m_orbitcentral
               << o.m_orbit3body;

    return dataStream;
}


