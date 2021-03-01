#ifndef ORBITTYPE_H
#define ORBITTYPE_H


#include <QString>
#include <QStringList>
#include <QVector>
#include <QVariant>
#include <QDebug>
#include <QDataStream>
#include "qt42baseclass.h"
#include "ShareHeaders/qt42_sharedparameters.h"


class Mission;
class OrbitHeader;
class Spacecraft;
class Orbit;

class OrbitZERO : public Qt42BaseClass
{
public:
    OrbitZERO();
    OrbitZERO(const OrbitZERO& OrbitZ);
    ~OrbitZERO() override;
    OrbitZERO& operator= (const OrbitZERO& OrbitZ);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}

    QString world() const {return m_world;}
    bool usePolyhedronGravity() const {return m_UsePolyhedronGravity;}
    void edit(const QString& World, bool UsePolyhedronGRavity, const bool& included);
    bool includedInCalculation () const override {return m_includedInCalculation;}

    friend bool operator==(const OrbitZERO& z1, const OrbitZERO& z2);
    friend QDataStream& operator<< (QDataStream& dataStream, const OrbitZERO& oz);
    friend QDataStream& operator>> (QDataStream& dataStream, OrbitZERO& oz);
    friend QDebug operator<< (QDebug dataStream, const OrbitZERO& oz);

private:
    void changeType(const objectType &type) override
    { Qt42BaseClass::changeType(type); }
    const objectType m_type = ORBITZERO;
    const QString m_name = "Zero";
    const int m_index = 0;

    QString m_world = "MINORBODY_2";  // "world" could be MINORBODY_1, MINORBODY_2, MINORBODY_3 and etc..
    bool m_UsePolyhedronGravity = false;
    bool m_includedInCalculation = false;
};

class OrbitFLIGHT : public Qt42BaseClass
{
public:
    OrbitFLIGHT();
    OrbitFLIGHT(const OrbitFLIGHT& OrbitF);
    ~OrbitFLIGHT() override;
    OrbitFLIGHT& operator=(const OrbitFLIGHT& OrbitF);
    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}

    int regionNumber() const {return m_RegionNumber;}
    bool usePolyhedronGravity() const {return m_UsePolyhedronGravity;}
    void edit(const int& regionNumber, const bool& usePolyhedronGravity, const bool& included);
    bool includedInCalculation () const override {return m_includedInCalculation;}

    friend bool operator==(const OrbitFLIGHT& F1, const OrbitFLIGHT& F2);
    friend QDataStream& operator<< (QDataStream& dataStream, const OrbitFLIGHT& of);
    friend QDataStream& operator>> (QDataStream& dataStream, OrbitFLIGHT& of);
    friend QDebug operator<< (QDebug dataStream, const OrbitFLIGHT& of);

private:
    void changeType(const objectType &type) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = ORBITFLIGHT;
    const QString m_name = "Flight";
    const int m_index = 1;

    int m_RegionNumber = 0;
    bool m_UsePolyhedronGravity = false;
    bool m_includedInCalculation = false;
};

class OrbitCENTRAL : public Qt42BaseClass
{
public:
    OrbitCENTRAL();
    OrbitCENTRAL(const OrbitCENTRAL& OrbitC);
    ~OrbitCENTRAL() override;
    OrbitCENTRAL& operator=(const OrbitCENTRAL& OrbitC);
    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}

    QString orbitCenter() const {return m_OrbitCenter;}
    bool secularOrbitDriftDueToJ2() const {return m_SecularOrbitDriftDueToJ2;}
    QString orbitDeterminedby() const {return m_OrbitDeterminedby;}
    QString orbitKEPdeterminedby() const {return m_OrbitKEPdeterminedby;}
    QVector <double> periapsisApoapsis() const {return m_qvecPeriapsisApoapsis;}
    QVector <double> minAltitudeEccentricuty() const {return m_qvecMinAltitudeEccentricuty;}
    double inclination() const {return m_Inclination;}
    double RAAN() const {return m_RAAN;}
    double AOP() const {return m_AOP;}
    double trueAnomaly() const {return m_TrueAnomaly;}
    QVector <double> RVInitialPosition() const {return m_qvecRVInitialPosition;}
    QVector <double> RVInitialVelocity() const {return m_qvecRVInitialVelocity;}
    QString format() const {return m_format;}
    QString labelInFile() const {return m_labelInFile;}
    QString fileName() const {return m_fileName;}

    void edit(const QString& orbitCenter, const bool& secularOrbitDriftDueToJ2,
              const QString& orbitDeterminedby, const QString& orbitKEPdeterminedby ,
              const QVector <double>& periapsisApoapsis,
              const QVector <double>& minAltitudeEccentricuty,
              const double& inclination, const double& RAAN,
              const double& AOP, const double& trueAnomaly,
              const QVector <double>& RVInitialPosition,
              const QVector <double>& RVInitialVelocity,
              const QString& format, const QString& labelInFile,
              const QString& fileName, const bool& included);
    bool includedInCalculation () const override {return m_includedInCalculation;}

    friend bool operator==(const OrbitCENTRAL& C1, const OrbitCENTRAL& C2);
    friend QDataStream& operator<< (QDataStream& dataStream, const OrbitCENTRAL& oc);
    friend QDataStream& operator>> (QDataStream& dataStream, OrbitCENTRAL& oc);
    friend QDebug operator<< (QDebug dataStream, const OrbitCENTRAL& oc);

private:
    void changeType(const objectType &type) override
    { Qt42BaseClass::changeType(type);}
    const objectType m_type = ORBITCENTRAL;
    const QString m_name = "Body-Centered Orbit";
    const int m_index = 2;

    QString m_OrbitCenter = "EARTH"; // "OrbitCenter" could be "MARS", "EARTH", "VENUS" and etc..
    bool m_SecularOrbitDriftDueToJ2 = false;
    QString m_OrbitDeterminedby = "KEP"; // "KEP" or "RV"  or "FILE"
    QString m_OrbitKEPdeterminedby = "PA";  // Use Peri/Apoapsis (PA) or min alt/ecc (AE)
    QVector <double> m_qvecPeriapsisApoapsis= QVector <double> (2, 0.0);
    QVector <double> m_qvecMinAltitudeEccentricuty = QVector <double> (2, 0.0);
    double m_Inclination = 0.0;     // units: degree
    double m_RAAN = 0.0;            // Right Ascension of Ascending Node; unit: degree
    double m_AOP = 0.0;             // Argument of Periapsis; units: degree
    double m_TrueAnomaly = 0.0;     // True Anomaly; units: degree
    QVector <double> m_qvecRVInitialPosition = QVector <double> (3,0.0); // RV Initial Position (km)
    QVector <double> m_qvecRVInitialVelocity = QVector <double> (3,0.0); // RV Initial Velocity (km/sec)
    QString m_format = "TRV";        // "TLE" or "TRV"
    QString m_labelInFile ="ORB_ID";   // TLE or TRV format, Label to find in file
    QString m_fileName = "TRV.txt";    // File name
    bool m_includedInCalculation = false;
};

class OrbitTHREEBODY : public Qt42BaseClass
{
public:
    OrbitTHREEBODY();
    OrbitTHREEBODY(const OrbitTHREEBODY& O3body);
    ~OrbitTHREEBODY() override;
    OrbitTHREEBODY& operator=(const OrbitTHREEBODY& O3body);
    friend bool operator==(const OrbitTHREEBODY& O3body1, const OrbitTHREEBODY& O3body2);
    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}

    int LagrangeSystem() const {return m_LagrangeSystem;}
    QString propagation() const {return m_Propagation;}
    QString initialization() const {return m_Initialization;}
    int LibrationPoint() const {return m_LibrationPoint;}
    double XY_SemiMajorAxis() const {return m_XY_SemiMajorAxis;}
    double initialXYPhase() const {return m_InitialXYPhase;}
    QString senseViewedfromZ() const {return m_SenseViewedfromZ;}
    double secondXYModeSemiMajorAxisL4L5only() const {return m_SecondXYModeSemiMajorAxisL4L5only;}
    double secondXYModeInitialPhaseL4L5only() const {return m_SecondXYModeInitialPhaseL4L5only;}
    QString SenseViewedfromZL4L5only() const {return m_SenseViewedfromZL4L5only;}
    double ZSemiAxis() const {return m_ZSemiAxis;}
    double initialZPhase() const {return m_InitialZPhase;}
    QVector <double> InitialXYZ_NonDimensional() const {return m_qvecInitialXYZ_NonDimensional;}
    QVector <double> InitialXdotYdotZdot_NonDimensional() const {return m_qvecInitialXdotYdotZdot_NonDimensional;}
    QString format() const {return m_format;}
    QString labelInFile() const {return m_labelInFile;}
    QString fileName() const {return m_fileName;}

    void edit(const int& LagrangeSystem, const QString& propagation,
              const QString& initialization, const int& LibrationPoint,
              const double& XY_SemiMajorAxis, const double& initialXYPhase,
              const QString& senseViewedfromZ,
              const double& secondXYModeSemiMajorAxisL4L5only,
              const double& secondXYModeInitialPhaseL4L5only,
              const QString& SenseViewedfromZL4L5only,
              const double& ZSemiAxis, const double& initialZPhase,
              const QVector <double>& qvecInitialXYZ_NonDimensional,
              const QVector <double>& qvecInitialXdotYdotZdot_NonDimensional,
              const QString& format, const QString& labelInFile,
              const QString& fileName, const bool& included);
    bool includedInCalculation () const override {return m_includedInCalculation;}

    friend bool operator==(const OrbitTHREEBODY& O3body1, const OrbitTHREEBODY& O3body2);
    friend QDataStream& operator<< (QDataStream& dataStream, const OrbitTHREEBODY& o3);
    friend QDataStream& operator>> (QDataStream& dataStream, OrbitTHREEBODY& o3);
    friend QDebug operator<< (QDebug dataStream, const OrbitTHREEBODY& o3);

private:
    void changeType(const objectType &type) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = ORBITTHREEBODY;
    const QString m_name = "Three-Body Orbit";
    const int m_index = 3;

    int m_LagrangeSystem = 0;    // This could be "EARTHMOON", "SUNEARTH", or "SUNJUPITER"
    QString m_Propagation = "LAGDOF_MODES";       // This could be "LAGDOF_MODES" or "LAGDOF_COWELL" or "LAGDOF_SPLINE"
    QString m_Initialization = "MODES";    //  Initialize with "MODES" or "XYZ" or "FILE"
    int m_LibrationPoint = 1;    //  (L1, L2, L3, L4, L5)
    double  m_XY_SemiMajorAxis = 0.0 ;        // unit: km
    double  m_InitialXYPhase = 0.0;           // unit: degree
    QString m_SenseViewedfromZ = "CW"; // CW or CCW
    double  m_SecondXYModeSemiMajorAxisL4L5only = 0.0; // unit; km
    double  m_SecondXYModeInitialPhaseL4L5only = 0.0;  // unit: degree
    QString m_SenseViewedfromZL4L5only = "CW";   // CW or CCW
    double  m_ZSemiAxis = 0.0;                        // unit: km
    double  m_InitialZPhase = 0.0;                    // unit: degree
    QVector <double> m_qvecInitialXYZ_NonDimensional = {1.05,  0.5,  0.0};
    QVector <double> m_qvecInitialXdotYdotZdot_NonDimensional = {0.0, 0.0, 0.0};
    QString m_format = "TRV";           // "TLE" or "TRV" or "SPLINE"
    QString m_labelInFile ="ORB_ID";        // TLE or TRV format, Label to find in file
    QString m_fileName = "TRV.txt";         // File name
    bool m_includedInCalculation = false;
};

class Orbit : public Qt42BaseClass
{
public:
    Orbit(OrbitHeader* OH = nullptr);
    ~Orbit() override;
    Orbit(const Orbit& orbit);
    Orbit& operator= (const Orbit& OtherOrbit);

    objectType type() const override {return m_type;}
    QString name() const override {return  m_name;}
    int index() const override {return m_index;}

    void duplicate(const Orbit& OtherOrbit);

    OrbitHeader* parentItem() const {return m_orbitHeader;}
    Mission* mission() const {return m_mission;}

    void updateIndex();
    bool hasName (const QString& name) const;
    void rename(const QString& newName);
    const QString defaultName = "Default Orbit";

    void setOrbitHeader(OrbitHeader* oh){m_orbitHeader = oh;}

    QString orbitType() const {return m_orbitType;}
    QString description () const { return m_Description; }
    QString formationFrameFixedIn () const { return m_FormationFrameFixedIn; }
    QVector <double> eulerAngles() const { return m_qvecEulerAngles;}
    QString eulerSequence() const { return m_EulerSequence;}
    QString formationOriginExpressedIn() const {return m_FormationOriginExpressedIn;}
    QVector <double> formationOriginRefOrbit() const { return m_qvecFormationOriginRefOrbit;}
    OrbitZERO orbitZero() const {return m_orbitzero;}
    OrbitFLIGHT orbitFlight() const {return m_orbitflight;}
    OrbitCENTRAL orbitCentral() const {return m_orbitcentral;}
    OrbitTHREEBODY orbit3body() const {return m_orbit3body;}

    void orbitZeroEdit(const QString& World, bool UsePolyhedronGRavity, const bool& included)
    {
        m_orbitzero.edit(World, UsePolyhedronGRavity, included);
    }

    void orbitFlightEdit(const int& regionNumber, const bool& usePolyhedronGravity, const bool& included)
    {
        m_orbitflight.edit(regionNumber, usePolyhedronGravity, included);
    }

    void orbitCentralEdit(const QString& orbitCenter, const bool& secularOrbitDriftDueToJ2,
                          const QString& orbitDeterminedby, const QString& orbitKEPdeterminedby ,
                          const QVector <double>& periapsisApoapsis,
                          const QVector <double>& minAltitudeEccentricuty,
                          const double& inclination, const double& RAAN,
                          const double& AOP, const double& trueAnomaly,
                          const QVector <double>& RVInitialPosition,
                          const QVector <double>& RVInitialVelocity,
                          const QString& format, const QString& labelInFile,
                          const QString& fileName, const bool& included)
    {
        m_orbitcentral.edit(orbitCenter, secularOrbitDriftDueToJ2,
                            orbitDeterminedby, orbitKEPdeterminedby ,
                            periapsisApoapsis,
                            minAltitudeEccentricuty,
                            inclination, RAAN,
                            AOP, trueAnomaly,
                            RVInitialPosition,
                            RVInitialVelocity,
                            format, labelInFile,
                            fileName, included);
    }

    void orbit3bodyEdit(const int& LagrangeSystem, const QString& propagation,
                        const QString& initialization, const int& LibrationPoint,
                        const double& XY_SemiMajorAxis, const double& initialXYPhase,
                        const QString& senseViewedfromZ,
                        const double& secondXYModeSemiMajorAxisL4L5only,
                        const double& secondXYModeInitialPhaseL4L5only,
                        const QString& SenseViewedfromZL4L5only,
                        const double& ZSemiAxis, const double& initialZPhase,
                        const QVector <double>& qvecInitialXYZ_NonDimensional,
                        const QVector <double>& qvecInitialXdotYdotZdot_NonDimensional,
                        const QString& format, const QString& labelInFile,
                        const QString& fileName, const bool& included)
    {
        m_orbit3body.edit(LagrangeSystem, propagation,
                          initialization, LibrationPoint,
                          XY_SemiMajorAxis, initialXYPhase,
                          senseViewedfromZ,
                          secondXYModeSemiMajorAxisL4L5only,
                          secondXYModeInitialPhaseL4L5only,
                          SenseViewedfromZL4L5only,
                          ZSemiAxis, initialZPhase,
                          qvecInitialXYZ_NonDimensional,
                          qvecInitialXdotYdotZdot_NonDimensional,
                          format, labelInFile,
                          fileName, included);
    }

    void edit(const QString& orbitType, const QString& description,
              const QString& formationFrameFixedIn,const QVector <double>& eulerAngles,
              const QString& eulerSequence, const QString& formationOriginExpressedIn,
              const QVector <double>& formationOriginRefOrbit,
              const bool& included);
    void setIncludedInCalculation(const bool &included = true) override
    {m_includedInCalculation = included;}
    bool includedInCalculation() const override {return m_includedInCalculation;}
    friend bool operator== (const Orbit& OtherOrbit1, const Orbit& OtherOrbit2);
    friend QDataStream& operator<< (QDataStream& dataStream, const Orbit& o);
    friend QDataStream& operator>> (QDataStream& dataStream, Orbit& o);
    friend QDebug operator<< (QDebug dataStream, const Orbit& o);

private:
    void changeType(const objectType &type) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = ORBIT;
    QString m_name = QString();
    OrbitHeader* m_orbitHeader = nullptr;
    Mission* m_mission = nullptr;

    int m_index = -1;
    QString m_orbitType = "ZERO";
    QString m_Description = QString();
    QString m_FormationFrameFixedIn = "N";  //  Formation Frame Fixed in [NL]
    QVector <double> m_qvecEulerAngles = QVector <double> (3, 0.0);
    QString m_EulerSequence = "123"; // The sequence could 123, 132, 121, 131, 213, 231, 212, 232, 312, 321, 313, 323
    QString m_FormationOriginExpressedIn = "N"; //  Formation Origin expressed in [NL]
    QVector <double> m_qvecFormationOriginRefOrbit = QVector <double> (3, 0.0); // Formation Origin wrt Ref Orbit (meter)

    OrbitZERO      m_orbitzero;
    OrbitFLIGHT    m_orbitflight;
    OrbitCENTRAL   m_orbitcentral;
    OrbitTHREEBODY m_orbit3body;
    bool m_includedInCalculation = false;
};

Q_DECLARE_METATYPE(Orbit)





#endif // ORBITTYPE_H
