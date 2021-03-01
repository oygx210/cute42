#ifndef ORBIT_H
#define ORBIT_H

class Spacecraft;
class Mission;
#include <QString>
#include <QStringList>
#include <QVector>
class OrbitZERO
{
public:
    OrbitZERO();
    OrbitZERO(const OrbitZERO&);
    ~OrbitZERO();
    QString world = QString();  // "world" could be MINORBODY_1, MINORBODY_2, MINORBODY_3 and etc..
    bool UsePolyhedronGravity = false;
};

class OrbitFLIGHT
{
public:
    OrbitFLIGHT();
    OrbitFLIGHT(const OrbitFLIGHT&);
    ~OrbitFLIGHT();
    int RegionNumber = 0;
    bool UsePolyhedronGravity = false;
};

class OrbitCENTRAL
{
public:
    OrbitCENTRAL();
    OrbitCENTRAL(const OrbitCENTRAL&);
    ~OrbitCENTRAL();
    QString OrbitCenter = QString(); // "OrbitCenter" could be "MARS", "EARTH", "VENUS" and etc..
    bool SecularOrbitDriftDueToJ2 = false;
    const QStringList OrbitDeterminedby = {"KEP", "RV", "FILE"}; // "KEP" or "RV"  or "FILE"
    const QStringList OrbitKEPdeterminedby = {"PA", "AE"};  // Use Peri/Apoapsis (PA) or min alt/ecc (AE)
    QVector <double> PeriapsisApoapsis = {0.0, 0.0};
    QVector <double> MinAltitudeEccentricuty = {0.0, 0.0};
    double Inclination = 0.0;     // units: degree
    double RAAN = 0.0;            // Right Ascension of Ascending Node; unit: degree
    double AOP = 0.0;             // Argument of Periapsis; units: degree
    double TrueAnomaly = 0.0;     // True Anomaly; units: degree
    QVector <double>  RVInitialPosition = { 0.0, 0.0, 0.0}; // RV Initial Position (km)
    QVector <double>  RVInitialVelocity = { 0.0, 0.0, 0.0}; // RV Initial Velocity (km/sec)
    QString format = QString();      // "TLE" or "TRV"
    QString labelInFile ="ORB_ID";   // TLE or TRV format, Label to find in file
    QString fileName = "TRV.txt";    // File name
};

class OrbitTHREEBODY
{
public:
    OrbitTHREEBODY();
    OrbitTHREEBODY(const OrbitTHREEBODY&);
    ~OrbitTHREEBODY();
    QString LagrangeSystem = QString();    // This could be SOL, MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE, PLUTO, LUNA
    QString Propagation = QString();       // This could be LAGDOF_MODES or LAGDOF_COWELL or LAGDOF_SPLINE
    QString Initialization = QString();    //  Initialize with MODES or XYZ or FILE
    QString LibrationPoint = QString();    //  (L1, L2, L3, L4, L5)
    double XY_SemiMajorAxis = 0.0 ;        // unit: km
    double InitialXYPhase = 0.0;           // unit: degree
    QString SenseViewedfromZ = QString(); // CW or CCW
    double SecondXYModeSemiMajorAxisL4L5only = 0.0; // unit; km
    double SecondXYModeInitialPhaseL4L5only = 0.0;  // unit: degree
    QString SenseViewedfromZL4L5only = QString();   // CW or CCW
    double ZSemiAxis = 0.0;                        // unit: km
    double InitialZPhase = 0.0;                    // unit: degree
    QVector <double> InitialXYZ_NonDimensional = {1.05,  0.5,  0.0};
    QVector <double> InitialXdotYdotZdot_NonDimensional = {0.0, 0.0, 0.0};
    QString format = QString();           // "TLE" or "TRV" or "SPLINE"
    QString labelInFile ="ORB_ID";        // TLE or TRV format, Label to find in file
    QString fileName = "TRV.txt";         // File name
};

class Orbit
{
public:
    Orbit();
    Orbit(const Orbit&);
    ~Orbit();
    Mission* mission = nullptr;          // the pointer to the Mission object where the orbit is used.
    QVector <Spacecraft*> spacecraft = QVector<Spacecraft*>(); // the collection of pointers to Spacecraft objects that use this orbit.
    QString name = QString();
    QString Description = QString();
    QString FormationFrameFixedIn = QString();  //  Formation Frame Fixed in [NL]
    QVector <double> EulerAngles = {0.0,0.0,0.0};
    QString EulerSequence = QString(); // The sequence could 123, 132, 121, 131, 213, 231, 212, 232, 312, 321, 313, 323
    QString FormationOriginExpressedIn = QString(); //  Formation Origin expressed in [NL]
    QVector <double> FormationOriginRefOrbit = {0.0,0.0,0.0}; // Formation Origin wrt Ref Orbit (meter)
    OrbitZERO* orbitzero;
    OrbitFLIGHT* orbitflight;
    OrbitCENTRAL* orbitcentral;
    OrbitTHREEBODY* orbit3body;
};

#endif // ORBIT_H
