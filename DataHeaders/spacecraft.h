#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QMap>
#include <QVariant>
#include <QDataStream>
#include <QDebug>
#include <QDataStream>
#include "spacecraftcomponents.h"
#include "qt42baseclass.h"

class Mission;
class SpacecraftHeader;



class Spacecraft : public Qt42BaseClass
{

public:
    Spacecraft(SpacecraftHeader* spacecraftheader = nullptr);
    Spacecraft(const Spacecraft&);  // the copy contructor
    ~Spacecraft() override;
    Spacecraft& operator=(const Spacecraft& s);


    void setSpacecraftHeader(SpacecraftHeader* sch) {m_spacecraftheader = sch;}
    objectType type () const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override;

    SpacecraftHeader* parentItem() const { return m_spacecraftheader; }
    Mission* mission() const {return m_mission;}

    void updateIndex(); // If the mission removes or adds new spacecrafts, update the index.
    void updateIndexComponents();   // Updates the index of the components of spacecraft.
    const QString defaultName = "Default Spacecraft";

    bool hasName (const QString& name) const;
    void rename(const QString& newName);  //for differentiating different spacecrafts through names    
    void editSCdescription(const QString& NAME, const QString& DESCRIPTION, const QString& LABEL,
                             const QString& SPRITEFILENAME, const QString& FSIDENTIFIER);

    void editOrbitParameter(const QString& orbitPropagation, const QString& referencePoint,
                            const QVector <double>& Pos, const QVector <double>& Vel);

    void editInitialAttitude(const QString& frame, const QString& angleForm,
                             const QVector <double>& angVel, const QVector <double>& qua,
                             const QVector <double>& eulerDeg, const QString& seq);

    bool createItem(objectType type);
    bool insertItem(const int& column, objectType type, Qt42BaseClass* Qt42BC);
    int columnOfComponent(objectType type) const;
    int rowOfComponent(objectType type) const;
    int numberOfComponentByRow(const int& row);
    bool reset();
    void updateSCcIncluded(const int& indexSCBEdited, const bool& included);
    // "void updateSCcIncluded(const int& indexSCB, const bool& included);" is called when a Spacecraft Body is
    // removed or excluded in calculation. All the components related to the removed or excluded body will be
    // excluded from the calculation.
    /** Spacecraft Description File **/
    QString description() const {return m_description;}
    QString label() const {return m_label;}
    QString spriteFileName() const {return m_spriteFileName;}
    QString FSIdentifier() const {return m_FSIdentifier;}
    double FSWSampleTime() const {return m_FSWSampleTime;}

    /** Orbit parameters  **/
    QString orbitProp() const {return m_orbitProp;}
    QString referncePoint() const {return m_referncePoint;}
    QVector <double> position() const {return m_qvecPosition;}
    QVector <double> velocity() const {return m_qvecVelocity;}

    /** Initial Attitude **/
    QString initialAttitudeSetting() const
    {
        QString settings = m_angularVelReferece+m_attitudeType+m_attitudeWithReference;
        return settings;
    }
    QString angularVelReferece() const {return m_angularVelReferece;}
    QString attitudeType() const {return m_attitudeType;}
    QString attitudeWithReference() const {return m_attitudeWithReference;}

    QVector<double> initialAngVel() const {return m_qvecInitialAngVel;}
    QVector<double> initialAngleQuaternion() const { return m_qvecInitialAngleQuaternion;}
    QVector<double> initialAngleDegree() const {return m_qvecInitialAngleDegree;}
    QString initialAngleEulerSeq() const {return m_initialAngleEulerSeq;}

    /** Dynamic Flags **/
    QString jointRotation() const {return m_jointRotation;}
    QString refMassProps() const {return m_refMassProps;}
    bool constMassProp() const {return m_constMassProp;}
    bool passiveJointForceTorqueEnabled() const {return m_passiveJointForceTorqueEnabled;}
    bool constraintForceTorqueComputing() const {return m_constraintForceTorqueComputing;}
    bool flexActiveEnabled() const {return m_flexActiveEnabled;}
    bool include2ndorderflexActive() const {return m_include2ndorderflexActive;}
    double dragCoefficient() const {return m_dragCoefficient;}


    /** edit functions **/
    void edit(const QString& description, const QString& label,
              const QString& spriteFileName, const QString& FSIdentifier,
              const double& FSWSampleTime, const QString& orbitProp,
              const QString& referncePoint, const QVector <double>& position,
              const QVector <double>& velocity, const QString& angularVelReferece,
              const QString& attitudeType, const QString& attitudeWithReference,
              const QVector<double>& initialAngVel, const QVector<double>& initialAngleQuaternion,
              const QVector<double>& initialAngleDegree,
              const QString& initialAngleEulerSeq, const QString& jointRotation,
              const QString& refMassProps, const bool& constMassProp,
              const bool& passiveJointForceTorqueEnabled,
              const bool& constraintForceTorqueComputing,
              const bool& flexActiveEnabled,
              const bool& include2ndorderflexActive,
              const double& dragCoefficient,
              const bool& included);



    /**   Spacecraft Body   **/
    bool createSpacecraftBody();
    bool insertSpacecraftBody(int i, SpacecraftBody* SCB);
    bool removeSpacecraftBody(SpacecraftBody* SCB);
    SpacecraftBody* body(const int& index = -1);
    int numberOfBodies() const { return m_qvecSCBs.size();}
    bool hasSpacecraftBody (SpacecraftBody* scb) {return m_qvecSCBs.contains(scb);}

    /**    Joints    **/
    bool createJoint();
    bool insertJoint(int i, Joint* JNT);
    bool removeJoint(Joint* joint);
    Joint* joint(const int& index = -1);
    int numberOfJoints() const { return m_qvecJoints.size(); }

    /**    Wheels   **/
    bool createWheel();
    bool insertWheel(int i, Wheel* WHL);
    bool removeWheel (Wheel* whl);
    Wheel* wheel(const int& index = -1);
    int numberOfWheels() const {return m_qvecWheels.size();}

    /**   MagTorquer  **/
    bool createMagTorquer();
    bool insertMagTorquer(int i, MagTorquer* MTB);
    bool removeMagTorquer(MagTorquer* magTorque);
    MagTorquer* magTorque(const int& index = -1);
    int numberOfMagTorquer() const {return m_qvecMagTrqs.size();}

/**  Thruster **/
    bool createThruster();
    bool insertThruster(int, Thruster* THR);
    bool removeThruster(Thruster* th);
    Thruster* thruster(const int& index = -1);
    int numberOfThruster() const {return m_qvecThrusters.size();}


/**    GyroAxis   **/
    bool createGyroAxis();
    bool insertGyroAxis(int i, GyroAxis* GYO);
    bool removeGyroAxis(GyroAxis* G);
    GyroAxis* gyroAxis(const int& index = -1);
    int numberOfGyroAxis() const {return m_qvecGyros.size();}

/**   MagnetometerAxis  **/
    bool createMagnetometerAxis();
    bool insertMagnetometerAxis(int i, MagnetometerAxis* MMA);
    bool removeMagnetometerAxis(MagnetometerAxis* MMA);
    MagnetometerAxis* MMA(const int& index = -1);
    int numberOfMMA() const {return m_qvecMMAs.size();}


/**   CoarseSunSensor  **/
    bool createCoarseSunSensor();
    bool insertCoarseSunSensor(int i, CoarseSunSensor* CSS);
    bool removeCoarseSunSensor(CoarseSunSensor* CSS);
    CoarseSunSensor* coarseSunSensor(const int& index = -1);
    int numberOfCoarseSunSensor() const {return m_qvecCSSs.size();}


/**  FineSunSensor  **/
    bool createFineSunSensor();
    bool insertFineSunSensor(int i, FineSunSensor* FSS);
    bool removeFineSunSensor(FineSunSensor* FSS);
    FineSunSensor* fineSunSensor(const int& index = -1);
    int numberOfFineSunSensor() const {return m_qvecFSSs.size();}

/**  Star Tracker **/
    bool createStarTracker();
    bool insertStarTracker(int i, StarTracker* ST);
    bool removeStarTracker(StarTracker* ST);
    StarTracker* starTracker(const int& index = -1);
    int numberOfStarTracker() const {return m_qvecSTs.size();}

/**  GPSReceiver  **/
    bool createGPSReceiver();
    bool insertGPSReceiver(int i, GPSReceiver* GPSR);
    bool removeGPSReceiver(GPSReceiver* gpsr);
    GPSReceiver* gPSReceiver(const int& index = -1);
    int numberOfGPSReceiver() const {return m_qvecGPSRs.size();}



/**   Accelerometer  **/
    bool createAccelerometer();
    bool insertAccelerometer(int i, Accelerometer* ACCL);
    bool removeAccelerometer(Accelerometer* ACCL);
    Accelerometer* accelerometer(const int& index = -1);
    int numberOfAccelerometer() const {return m_qvecAccels.size();}


    int indexSCBs(SpacecraftBody*) const;
    int indexJoint(Joint*) const;
    int indexWheel(Wheel*) const;
    int indexMagTorquer(MagTorquer*) const;
    int indexThruster(Thruster*) const;
    int indexGyroAxis(GyroAxis*) const;
    int indexMagnetometerAxis(MagnetometerAxis*) const;
    int indexCoarseSunSensor(CoarseSunSensor*) const;
    int indexFineSunSensor(FineSunSensor*) const;
    int indexStarTracker (StarTracker*) const;
    int indexGPSReceiver(GPSReceiver*) const;
    int indexAccelerometer(Accelerometer*) const;


    int numberOfRow () const {return m_numberOfTypeOfComponents;}
    int numberOfColumn() const {return m_numberOfColumn;}

    int rowSPACECRAFTBODY() const {return m_rowSPACECRAFTBODY;}
    int rowJOINT() const {return m_rowJOINT;}
    int rowWHEEL() const {return m_rowWHEEL;}
    int rowMAGTORQUER() const {return m_rowMAGTORQUER;}
    int rowTHRUSTER() const {return m_rowTHRUSTER;}
    int rowGYROAXIS() const {return m_rowGYROAXIS;}
    int rowMAGNETOMETERAXIS() const {return m_rowMAGNETOMETERAXIS;}
    int rowCOARSESUNSENSOR() const {return m_rowCOARSESUNSENSOR;}
    int rowFINESUNSENSOR () const {return m_rowFINESUNSENSOR;}
    int rowSTARTRACKER() const {return m_rowSTARTRACKER;}
    int rowGPSRECEIVER() const {return m_rowGPSRECEIVER;}
    int rowACCELEROMETER() const {return m_rowACCELEROMETER;}

    void clearAllComponents();
    void deletePointAllComponents();
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation() const override {return m_includedInCalculation;}

    /** These QVectors are for "QDataStream& operator<<" and QDataStream& operator>>". **/
    QVector <SpacecraftBody> m_qvecScbObjects = QVector <SpacecraftBody>();
    QVector <Joint> m_qvecJointObjects = QVector <Joint>();
    QVector <Wheel> m_qvecWheelObjects = QVector <Wheel>();
    QVector <MagTorquer> m_qvecMagTrqObjects = QVector <MagTorquer> ();
    QVector <Thruster> m_qvecThrusterObjects = QVector <Thruster>();
    QVector <GyroAxis> m_qvecGyroObjects = QVector <GyroAxis>();
    QVector <MagnetometerAxis> m_qvecMMAObjects = QVector <MagnetometerAxis>();
    QVector <CoarseSunSensor> m_qvecCSSObjects = QVector <CoarseSunSensor>();
    QVector <FineSunSensor> m_qvecFSSObjects = QVector <FineSunSensor>();
    QVector <StarTracker> m_qvecSTObjects = QVector <StarTracker>();
    QVector <GPSReceiver> m_qvecGPSRObjects = QVector <GPSReceiver>();
    QVector <Accelerometer> m_qvecAccelObjects= QVector <Accelerometer>();
    void duplicate(const Spacecraft& s);
    void setMission(Mission* m) {m_mission = m;}

    friend bool operator==(const Spacecraft& sc1, const Spacecraft& sc2);
    friend QDataStream& operator<< (QDataStream& dataStream, const Spacecraft& sc);
    friend QDataStream& operator>> (QDataStream& dataStream, Spacecraft& sc);
    friend QDebug operator<< (QDebug dataStream, const Spacecraft& sc);
signals:


private:
    void updateNumberOfRow();
    void updateNumberOfColumn();
    void changeType(const objectType &type) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = SPACECRAFT;
    Mission* m_mission = nullptr;  // This item serves as the parent of spacecraft in the qt model/view.
    SpacecraftHeader* m_spacecraftheader;

    QString m_name = QString();   // name of the spacecraft; for differentiating different spacecrafts through names
    int m_index = -1;
    /** Spacecraft Description File **/

    QString m_description = QString();
    QString m_label = QString();
    QString m_spriteFileName = QString();  //"Sprite is a computer graphics term for a two-dimensional bitmap that is integrated into a larger scene, most often in a 2D video game." from  https://en.wikipedia.org/wiki/Sprite_(computer_graphics)
    QString m_FSIdentifier = QString();   // Flight Software Identifier
    double m_FSWSampleTime = 0.0;

    /** Orbit parameters  **/
    QString m_orbitProp = "FIXED";     // Orbit Prop; could be FIXED, EULER_HILL, or ENCKE;
    QString m_referncePoint = "CM"; // coulf be CM or ORIGIN, wrt F.
    QVector <double> m_qvecPosition = QVector<double>(3, 0.0);  // Pos wrt Formation (m), expressed in F
    QVector <double> m_qvecVelocity = QVector<double>(3, 0.0);  // Vel wrt Formation (m/s), expressed in F

    /** Initial Attitude **/
    QString m_angularVelReferece = "N"; //Angular Vel wrt [NL]
    QString m_attitudeType = "Q"; // Att [QA]
    QString m_attitudeWithReference = "N"; // this could be [NLF]
    QVector<double> m_qvecInitialAngVel = QVector<double>(3, 0.0);      // angular velocity in degree/second
    QVector<double> m_qvecInitialAngleQuaternion = QVector<double>(4, 0.0);  // angles in terms of quaternion
    QVector<double> m_qvecInitialAngleDegree = QVector<double>(3, 0.0);  // angles in degree
    QString m_initialAngleEulerSeq = "123";         // Euler Sequence; could be "123"

    /** Dynamic Flags **/
    QString m_jointRotation = "STEADY";   // Rotation STEADY, KIN_JOINT, or DYN_JOINT;
    bool m_constMassProp = true;     // If true, then the mass properties are assumed to be constant.
    bool m_passiveJointForceTorqueEnabled = false;  // If true, then the passive joint forces and torques are enabled.
    bool m_constraintForceTorqueComputing = false;   // If true, then the constraint forces and torques are to be computed.
    QString m_refMassProps = "REFPT_CM";    // the reference to which the mass props reference to; could be REFPT_CM or REFPT_JOINT. try enum
    bool m_flexActiveEnabled = false;  // if true, the flex active is enabled.
    bool m_include2ndorderflexActive = false;  // if true, 2nd order flex terms are included.
    double m_dragCoefficient = 0.0;

    /**  Spacecraft components **/
    QVector <SpacecraftBody*> m_qvecSCBs = QVector <SpacecraftBody*>();
    QVector <Joint*> m_qvecJoints = QVector <Joint*>();
    QVector <Wheel*> m_qvecWheels = QVector <Wheel*>();
    QVector <MagTorquer*> m_qvecMagTrqs = QVector <MagTorquer*> ();
    QVector <Thruster*> m_qvecThrusters = QVector <Thruster*>();
    QVector <GyroAxis*> m_qvecGyros = QVector <GyroAxis*>();
    QVector <MagnetometerAxis*> m_qvecMMAs = QVector <MagnetometerAxis*>();
    QVector <CoarseSunSensor*> m_qvecCSSs = QVector <CoarseSunSensor*>();
    QVector <FineSunSensor*> m_qvecFSSs = QVector <FineSunSensor*>();
    QVector <StarTracker*> m_qvecSTs = QVector <StarTracker*>();
    QVector <GPSReceiver*> m_qvecGPSRs = QVector <GPSReceiver*>();
    QVector <Accelerometer*> m_qvecAccels= QVector <Accelerometer*>();

    int m_numberOfColumn = 0;
    int m_numberOfTypeOfComponents = 0;
    int m_rowSPACECRAFTBODY = -1;
    int m_rowJOINT = -1;
    int m_rowWHEEL= -1;
    int m_rowMAGTORQUER = -1;
    int m_rowTHRUSTER = -1;
    int m_rowGYROAXIS = -1;
    int m_rowMAGNETOMETERAXIS = -1;
    int m_rowCOARSESUNSENSOR = -1;
    int m_rowFINESUNSENSOR = -1;
    int m_rowSTARTRACKER = -1;
    int m_rowGPSRECEIVER = -1;
    int m_rowACCELEROMETER = -1;
    bool m_includedInCalculation = false;
};




Q_DECLARE_METATYPE(Spacecraft)

#endif // SPACECRAFT_H
