
#ifndef INPSIMTERMS_H
#define INPSIMTERMS_H

#include <QVariant>
#include <QVector>
#include <QDate>
#include <QTime>
#include <QDataStream>
#include <QDebug>
#include "qt42baseclass.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "spacecraft.h"
#include "orbittype.h"

class Mission;
class InpSimHeader;
class GroundStation;
class QTime;
class QDate;

class InpSimSimulationControl : public Qt42BaseClass
{
public:
    InpSimSimulationControl(InpSimHeader* inpsimheader = nullptr);
    InpSimSimulationControl(const InpSimSimulationControl& inpsimsimC);
    ~InpSimSimulationControl() override;
    InpSimSimulationControl& operator= (const InpSimSimulationControl& inpsimsimC);
    void duplicate(const InpSimSimulationControl& inpsimsimC);

    void edit(const QString& timeMode, const double& simDuration, const double& stepSize,
              const double& fileOuputInterval, const bool& graphicsFrontEnd);

    QString timeMode() const {return m_timeMode;}
    double simDuration() const {return m_simDuration;}
    double stepSize() const {return m_stepSize;}
    double fileOuputInterval() const {return m_fileOuputInterval;}
    bool graphicsFrontEnd() const {return m_graphicsFrontEnd;}

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}
    InpSimHeader* parentItem() const {return m_inpsimheader;}
    void setInpSimHeader(InpSimHeader* ish) {m_inpsimheader = ish;}

    friend QDataStream& operator<< (QDataStream& dataStream, const InpSimSimulationControl& ISSC);
    friend QDataStream& operator>> (QDataStream& dataStream, InpSimSimulationControl& ISSC);
    friend QDebug operator<< (QDebug dataStream, const InpSimSimulationControl& ISSC);

private:
    void changeType(const objectType &type = QT42BASECLASS) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = INPSIMSIMULATIONCONTROL;
    const QString m_name = "Simulation Control";
    const int m_index = 0;
    InpSimHeader* m_inpsimheader = nullptr;

    QString m_timeMode = "FAST";  // m_TimeMode could be "FAST", "REAL", "EXTERNAL", or "NOS3"
    double m_simDuration = 0.0;   // m_SimDuration unit: sec
    double m_stepSize = 0.0;      // m_StepSize unit : sec
    double m_fileOuputInterval = 0.0; // m_fileOuputInterval unit : sec
    bool m_graphicsFrontEnd = true;
};

class InpSimOrbitSCSet : public Qt42BaseClass
{
public:
    InpSimOrbitSCSet(InpSimHeader* inpsimheader = nullptr);
    InpSimOrbitSCSet(const InpSimOrbitSCSet& OandSC);
    ~InpSimOrbitSCSet() override;
    InpSimOrbitSCSet& operator=(const InpSimOrbitSCSet& OandSC);
    void duplicate(const InpSimOrbitSCSet& OandSC);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}
    InpSimHeader* parentItem() const {return m_inpsimheader;}
    void setInpSimHeader(InpSimHeader* ish) {m_inpsimheader = ish;}

    int numberOfOrbitTotal() const {return m_qvecOrbitAll.size();}
    int numberOfSCTotal() const {return m_qvecSCAll.size();}
    int numberOfOrbitSCpair() const {return m_qvecPair.size();}

    void createPair(const Orbit& O, const Spacecraft& SC);
    void createPair(const QPair<Orbit, Spacecraft> newPair);
    void removePair(const int& index);
    void removePair(const QPair<Orbit,Spacecraft> removedPair);
    void removePair(const Orbit& O);
    void removePair(const Spacecraft& SC);
    QVector<QPair<Orbit,Spacecraft>> qvecPair() const {return m_qvecPair;}
    QVector<Spacecraft> SCswithoutOrbits();
    void updateOrbitsSCs(const Mission& mission);

    friend QDataStream& operator<< (QDataStream& dataStream, const InpSimOrbitSCSet& OandSC);
    friend QDataStream& operator>> (QDataStream& dataStream, InpSimOrbitSCSet& OandSC);
    friend QDebug operator<< (QDebug dataStream, const InpSimOrbitSCSet& OandSC);

private:
    void changeType(const objectType &type = QT42BASECLASS) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = INPSIMORBITSCSET;
    const QString m_name = "Orbit-Spacecraft Set";
    const int m_index = 1;
    InpSimHeader* m_inpsimheader = nullptr;

    QVector<Orbit> m_qvecOrbitAll = QVector<Orbit>();
    QVector<Spacecraft> m_qvecSCAll = QVector<Spacecraft>();
    QVector<QPair<Orbit,Spacecraft>> m_qvecPair = QVector<QPair<Orbit,Spacecraft>>();
};




class InpSimEnvironment : public Qt42BaseClass
{
public:
    InpSimEnvironment(InpSimHeader* inpsimheader = nullptr, Mission* mission = nullptr);
    InpSimEnvironment(const InpSimEnvironment& E);
    ~InpSimEnvironment() override;
    InpSimEnvironment& operator= (const InpSimEnvironment& E);
    void duplicate(const InpSimEnvironment& E);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}
    Mission* mission() const {return m_mission;}
    InpSimHeader* parentItem() const {return m_inpsimheader;}
    void setInpSimHeader(InpSimHeader* ish) {m_inpsimheader = ish;}
    void edit(const QDate& date,
              const QTime& time,
              const double& timeOffset,
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
              const bool& CFDsloshForceTorques, const bool& outPutEnvironmentalTorquesToFiles);

    QDate date() const {return m_date;}
    int dateMonth() const {return m_date.month();}
    int dateDay() const {return m_date.day();}
    int dateYear() const {return m_date.year();}
    QTime time() const {return m_time;}
    int timeHr() const {return m_time.hour();}
    int timeMin() const {return m_time.minute();}
    double timeMicroSec() const {return m_time.msec();}
    double timeSec() const {double sec = m_time.msec()/1000; return sec;}
    double timeOffset() const {return m_timeOffset;}
    QString solarFluxAPValues () const {return m_modelDateInterpolationSolarFlux_APValue;}
    double userDefined_F10_7() const {return m_userDefined_F10_7;}
    double userDefined_APvalue() const {return m_userDefined_APvalue;}
    QString magField() const {return m_magfield;}
    int IGRF_Degree() const {return m_IGRF_Degree;}
    int IGRF_Order() const {return m_IGRF_Order;}
    int gravityModelEarth_N() const {return m_gravityModelEarth_N;}
    int gravityModelEarth_M() const {return m_gravityModelEarth_M;}
    int gravityModelMars_N() const {return m_gravityModelMars_N;}
    int gravityModelMars_M() const {return m_gravityModelMars_M;}
    int gravityModelLuna_N() const {return m_gravityModelLuna_N;}
    int gravityModelLuna_M() const {return m_gravityModelLuna_M;}

    bool aerodynamicForces() const {return m_aerodynamicForces;}
    bool aerodynamicTorques() const {return m_aerodynamicTorques;}
    bool gravityGradientTorques() const {return m_gravityGradientTorques;}
    bool solarPressureForces() const {return m_solarPressureForces;}
    bool solarPressureTorques() const {return m_solarPressureTorques;}
    bool gravityPerturbationForces() const {return m_gravityPerturbationForces;}
    bool passiveJointForcesTorques() const {return m_passiveJointForcesTorques;}
    bool thrusterPlumeForcesTorques() const {return m_thrusterPlumeForcesTorques;}
    bool RWA_ImbalanceForcesTorques() const {return m_RWA_ImbalanceForcesTorques;}
    bool contactForcesTorques() const {return m_contactForcesTorques;}
    bool CFDsloshForceTorques() const {return m_CFDsloshForceTorques;}
    bool outPutEnvironmentalTorquesToFiles() const {return m_outPutEnvironmentalTorquesToFiles;}

    friend QDataStream& operator<< (QDataStream& dataStream, const InpSimEnvironment& E);
    friend QDataStream& operator>> (QDataStream& dataStream, InpSimEnvironment& E);
    friend QDebug operator<< (QDebug dataStream, const InpSimEnvironment& E);

private:
    void changeType(const objectType &type = QT42BASECLASS) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = INPSIMENVIRONMENT;
    const QString m_name = "Environment";
    const int m_index = 2;
    InpSimHeader* m_inpsimheader = nullptr;
    Mission* m_mission = nullptr;

    QDate m_date = *(new QDate(QDate::currentDate()));
    QTime m_time = *(new QTime(QTime::currentTime()));
    double m_timeOffset = 0.0; // unit: sec
    QString m_modelDateInterpolationSolarFlux_APValue = "USER_DEFINED"; // could be TWOSIGMA_KP, NOMINAL or USER_DEFINED
    double m_userDefined_F10_7 = 0.0;
    double m_userDefined_APvalue = 0.0;
    QString m_magfield = "IGRF"; // could be NONE, DIPOLE, IGRF
    int m_IGRF_Degree = 8;
    int m_IGRF_Order = 8;  // note: <=10
    int m_gravityModelEarth_N = 8;  // <=18
    int m_gravityModelEarth_M = 8;  // <=18
    int m_gravityModelMars_N = 2;   // <=18
    int m_gravityModelMars_M = 0;   // <=18
    int m_gravityModelLuna_N = 2;   // <=18
    int m_gravityModelLuna_M = 0;   // <=18
    bool m_aerodynamicForces = false;
    bool m_aerodynamicTorques = false;
    bool m_gravityGradientTorques = false;
    bool m_solarPressureForces = false;
    bool m_solarPressureTorques = false;
    bool m_gravityPerturbationForces = false;
    bool m_passiveJointForcesTorques = false;
    bool m_thrusterPlumeForcesTorques = false;
    bool m_RWA_ImbalanceForcesTorques = false;
    bool m_contactForcesTorques = false;
    bool m_CFDsloshForceTorques = false;
    bool m_outPutEnvironmentalTorquesToFiles = false;
};

class InpSimCelestialBody : public Qt42BaseClass
{
public:
    InpSimCelestialBody(InpSimHeader* inpsimheader = nullptr, Mission* mission = nullptr);
    InpSimCelestialBody(const InpSimCelestialBody& C);
    ~InpSimCelestialBody() override;
    InpSimCelestialBody& operator=(const InpSimCelestialBody& C);
    void duplicate(const InpSimCelestialBody& C);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}
    Mission* mission() const {return m_mission;}
    InpSimHeader* parentItem() const {return m_inpsimheader;}
    void setInpSimHeader(InpSimHeader* ish) {m_inpsimheader = ish;}

    QString ephemerides () const {return m_EphemOption;}
    bool MercuryIncluded() const {return m_Mercury;}
    bool VenusIncluded() const {return m_Venus;}
    bool EarthAndLunaIncluded() const {return m_EarthLuna;}
    bool MarsAndMoonsIncluded() const {return m_MarsAndMoons;}
    bool JupiterAndMoonsIncluded() const {return m_JupiterAndMoons;}
    bool SaturnAndMoonsIncluded() const {return m_SaturnAndMoons;}
    bool UranusAndMoonsIncluded() const {return m_UranusAndMoons;}
    bool NeptuneAndMoonsIncluded() const {return m_NeptuneAndMoons;}
    bool PlutoAndMoonsIncluded() const {return m_PlutoAndMoons;}
    bool AsteroidsAndCometsIncluded() const {return m_AsteroidsAndComets;}

    void edit(const QString& EphemOption, const bool& Mercury, const bool& Venus,
    const bool& EarthLuna, const bool& MarsAndMoons, const bool& JupiterAndMoons,
    const bool& SaturnAndMoons, const bool& UranusAndMoons,
    const bool& NeptuneAndMoons, const bool& PlutoAndMoons,
    const bool& AsteroidsAndComets);

    friend QDataStream& operator<< (QDataStream& dataStream, const InpSimCelestialBody& CB);
    friend QDataStream& operator>> (QDataStream& dataStream, InpSimCelestialBody& CB);
    friend QDebug operator<< (QDebug dataStream, const InpSimCelestialBody& CB);
private:
    void changeType(const objectType &type = QT42BASECLASS) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = INPSIMCELESTIALBODY;
    const QString m_name = "Celestial Bodies of Interest";
    const int m_index = 3;
    InpSimHeader* m_inpsimheader = nullptr;
    Mission* m_mission = nullptr;


    QString m_EphemOption = "MEAN"; // could be MEAN or DE430
    bool m_Mercury = false;
    bool m_Venus = false;
    bool m_EarthLuna = false;
    bool m_MarsAndMoons = false;
    bool m_JupiterAndMoons = false;
    bool m_SaturnAndMoons = false;
    bool m_UranusAndMoons = false;
    bool m_NeptuneAndMoons = false;
    bool m_PlutoAndMoons = false;
    bool m_AsteroidsAndComets = false;
};

class InpSimLagrangePointSystem : public Qt42BaseClass
{
public:
    InpSimLagrangePointSystem(InpSimHeader* inpsimheader = nullptr, Mission* mission = nullptr);
    InpSimLagrangePointSystem(const InpSimLagrangePointSystem& L);
    ~InpSimLagrangePointSystem() override;
    InpSimLagrangePointSystem& operator=(const InpSimLagrangePointSystem& L);
    void duplicate(const InpSimLagrangePointSystem& L);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}
    Mission* mission() const {return m_mission;}
    InpSimHeader* parentItem() const {return m_inpsimheader;}
    void edit(const bool& EarthMoon, const bool& SunEarth, const bool& SunJupiter);
    void setInpSimHeader(InpSimHeader* ish) {m_inpsimheader = ish;}

    bool EarthMoonIncluded() const {return m_EarthMoon;}
    bool SunEarthIncluded() const {return m_SunEarth;}
    bool SunJupiterIncluded() const {return m_SunJupiter;}

    friend QDataStream& operator<< (QDataStream& dataStream, const InpSimLagrangePointSystem& LPS);
    friend QDataStream& operator>> (QDataStream& dataStream, InpSimLagrangePointSystem& LPS);
    friend QDebug operator<< (QDebug dataStream, const InpSimLagrangePointSystem& LPS);
private:
    void changeType(const objectType &type = QT42BASECLASS) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = INPSIMLAGRANGEPOINTSYSTEM;
    const QString m_name = "Lagrange Point Systems of Interest";
    const int m_index = 4;
    InpSimHeader* m_inpsimheader = nullptr;
    Mission* m_mission = nullptr;

    bool m_EarthMoon = false;
    bool m_SunEarth = false;
    bool m_SunJupiter = false;
};


class InpSimGroundStation : public Qt42BaseClass
{
public:
    InpSimGroundStation(InpSimHeader* inpsimheader = nullptr, Mission* mission = nullptr);
    InpSimGroundStation(const InpSimGroundStation& G);
    ~InpSimGroundStation() override;
    InpSimGroundStation& operator= (const InpSimGroundStation& G);
    void duplicate(const InpSimGroundStation& G);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}
    Mission* mission() const {return m_mission;}
    InpSimHeader* parentItem() const {return m_inpsimheader;}
    GroundStation& groundStation(const int& index = -1);
    int numberOfGroundStation() const {return m_qvecGroundStation.size();}
    bool createGroundStation(const int& index, const GroundStation& gs);
    bool createGroundStation();
    bool removeGroundStation(const int& index = -1);
    void setInpSimHeader(InpSimHeader* ish) {m_inpsimheader = ish;}

    friend QDataStream& operator<< (QDataStream& dataStream, const InpSimGroundStation& IGS);
    friend QDataStream& operator>> (QDataStream& dataStream, InpSimGroundStation& IGS);
    friend QDebug operator<< (QDebug dataStream, const InpSimGroundStation& IGS);
private:
    void changeType(const objectType &type = QT42BASECLASS) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = INPSIMGROUNDSTATION;
    const QString m_name = "Ground Stations";
    const int m_index = 5;
    InpSimHeader* m_inpsimheader = nullptr;
    Mission* m_mission = nullptr;
    QVector <GroundStation> m_qvecGroundStation;
};

class GroundStation
{
public:
    GroundStation();
    GroundStation(const GroundStation& G);
    ~GroundStation();
    GroundStation& operator= (const GroundStation& G);
    bool operator==(const GroundStation& gs) const;
    void edit(const bool& existed, const QString& world, const double& longitude,
              const double& latitude, const QString& label);
    void setIndex(const int& index = -1) {m_index = index;}
    int index() const {return m_index;}
    bool existed() const {return m_existed;}
    QString world() const {return m_world;}
    double longitude() const {return m_longitude;}
    double latitude() const {return m_latitude;}
    QString label() const {return m_label;}
    void rename(const QString& newName) {m_label = newName.trimmed();}
    QString defaultName() const {return m_defaultName;}

    friend QDataStream& operator<< (QDataStream& dataStream, const GroundStation& GS);
    friend QDataStream& operator>> (QDataStream& dataStream, GroundStation& GS);
    friend QDebug operator<< (QDebug dataStream, const GroundStation& GS);

private:
    int m_index = -1;
    bool m_existed = true;
    QString m_world = "EARTH";
    double m_longitude = 0.0;
    double m_latitude = 0.0;
    QString m_label = QString();
    const QString m_defaultName = "Default Ground Station";
};


Q_DECLARE_METATYPE(InpSimSimulationControl);
Q_DECLARE_METATYPE(InpSimOrbitSCSet);
Q_DECLARE_METATYPE(InpSimEnvironment);
Q_DECLARE_METATYPE(InpSimCelestialBody);
Q_DECLARE_METATYPE(InpSimLagrangePointSystem);
Q_DECLARE_METATYPE(InpSimGroundStation);
Q_DECLARE_METATYPE(GroundStation);

#endif // INPSIMTERMS_H
