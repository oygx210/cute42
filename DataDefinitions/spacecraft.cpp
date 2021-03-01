#include "DataHeaders/spacecraft.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/mission.h"
#include <QDebug>

Spacecraft::Spacecraft(SpacecraftHeader* spacecraftheader): m_spacecraftheader(spacecraftheader)
{
    changeType(m_type);
    if (m_spacecraftheader)
    {
        if (m_spacecraftheader->parentItem())
            m_mission = m_spacecraftheader->parentItem();
        QString defaultNumber = QString::number(m_spacecraftheader->maxNumberDefaultSC()+1);
        m_name = defaultName+"-"+defaultNumber;
    }
}



Spacecraft::Spacecraft(const Spacecraft& s) : Qt42BaseClass(s)
{
    m_index = s.m_index;
    m_mission = s.m_mission;
    m_spacecraftheader = s.m_spacecraftheader;
    m_name = s.m_name;
    m_description = s.m_description;
    m_label = s.m_label;
    m_spriteFileName = s.m_spriteFileName;
    m_FSIdentifier = s.m_FSIdentifier;
    m_FSWSampleTime = s.m_FSWSampleTime;
    /** Orbit parameters  **/
    m_orbitProp = s.m_orbitProp;
    m_referncePoint = s.m_referncePoint;
    m_qvecPosition = s.m_qvecPosition;
    m_qvecVelocity = s.m_qvecVelocity;
    m_includedInCalculation = s.m_includedInCalculation;


    /** Initial Attitude **/
    m_angularVelReferece = s.m_angularVelReferece;
    m_attitudeType = s.m_attitudeType;
    m_attitudeWithReference = s.m_attitudeWithReference;
    m_qvecInitialAngVel = s.m_qvecInitialAngVel;
    m_qvecInitialAngleDegree = s.m_qvecInitialAngleDegree;
    m_qvecInitialAngleQuaternion = s.m_qvecInitialAngleQuaternion;
    m_initialAngleEulerSeq = s.m_initialAngleEulerSeq;

    /** Dynamic Flags **/
    m_jointRotation = s.m_jointRotation;
    m_constMassProp = s.m_constMassProp;
    m_passiveJointForceTorqueEnabled = s.m_passiveJointForceTorqueEnabled;
    m_constraintForceTorqueComputing = s.m_constraintForceTorqueComputing;
    m_refMassProps = s.m_refMassProps;
    m_flexActiveEnabled = s.m_flexActiveEnabled;
    m_include2ndorderflexActive = s.m_include2ndorderflexActive;
    m_dragCoefficient = s.m_dragCoefficient;


    //m_qvecSCBs = s.m_qvecSCBs;
    for (int i = 0; i < s.m_qvecSCBs.size(); ++i)
    {
        SpacecraftBody* scb = new SpacecraftBody(*s.m_qvecSCBs[i]);
        m_qvecSCBs.append(scb);
    }

    m_qvecJoints = s.m_qvecJoints;
    m_qvecWheels = s.m_qvecWheels;
    m_qvecMagTrqs = s.m_qvecMagTrqs;
    m_qvecThrusters = s.m_qvecThrusters;
    m_qvecGyros = s.m_qvecGyros;
    m_qvecMMAs = s.m_qvecMMAs;
    m_qvecCSSs = s.m_qvecCSSs;
    m_qvecFSSs = s.m_qvecFSSs;
    m_qvecSTs = s.m_qvecSTs;
    m_qvecGPSRs = s.m_qvecGPSRs;
    m_qvecAccels = s.m_qvecAccels;

    m_numberOfColumn = s.m_numberOfColumn;
    m_numberOfTypeOfComponents = s.m_numberOfTypeOfComponents;
    m_rowSPACECRAFTBODY = s.m_rowSPACECRAFTBODY;
    m_rowJOINT = s.m_rowJOINT;
    m_rowWHEEL = s.m_rowWHEEL;
    m_rowMAGTORQUER = s.m_rowMAGTORQUER;
    m_rowTHRUSTER = s.m_rowTHRUSTER;
    m_rowGYROAXIS = s.m_rowGYROAXIS;
    m_rowMAGNETOMETERAXIS = s.m_rowMAGNETOMETERAXIS;
    m_rowCOARSESUNSENSOR = s.m_rowCOARSESUNSENSOR;
    m_rowFINESUNSENSOR = s.m_rowFINESUNSENSOR;
    m_rowSTARTRACKER = s.m_rowSTARTRACKER;
    m_rowGPSRECEIVER = s.m_rowGPSRECEIVER;
    m_rowACCELEROMETER = s.m_rowACCELEROMETER;

    m_qvecScbObjects = s.m_qvecScbObjects;
    m_qvecJointObjects = s.m_qvecJointObjects;
    m_qvecWheelObjects = s.m_qvecWheelObjects;
    m_qvecMagTrqObjects = s.m_qvecMagTrqObjects;
    m_qvecThrusterObjects = s.m_qvecThrusterObjects;
    m_qvecGyroObjects = s.m_qvecGyroObjects;
    m_qvecMMAObjects = s.m_qvecMMAObjects;
    m_qvecCSSObjects = s.m_qvecCSSObjects;
    m_qvecFSSObjects = s.m_qvecFSSObjects;
    m_qvecSTObjects = s.m_qvecSTObjects;
    m_qvecGPSRObjects = s.m_qvecGPSRObjects;
    m_qvecAccelObjects= s.m_qvecAccelObjects;
}

Spacecraft::~Spacecraft()
{
    // Poorly-defined destructor will cause QVariant::setValue(Spacecraft) to fail;

    /*
    qDeleteAll(m_qvecSCBs);
    qDeleteAll(m_qvecJoints);
    qDeleteAll(m_qvecWheels);
    qDeleteAll(m_qvecMagTrqs);
    qDeleteAll(m_qvecThrusters);
    qDeleteAll(m_qvecGyros);
    qDeleteAll(m_qvecMMAs);
    qDeleteAll(m_qvecCSSs);
    qDeleteAll(m_qvecFSSs);
    qDeleteAll(m_qvecSTs);
    qDeleteAll(m_qvecGPSRs);
    qDeleteAll(m_qvecAccels);
    */
}

Spacecraft& Spacecraft::operator=(const Spacecraft &s)
{
  if (this == &s)
      return *this;
  m_index = s.m_index;
  m_mission = s.m_mission;
  m_spacecraftheader = s.m_spacecraftheader;
  m_name = s.m_name;
  m_description = s.m_description;
  m_label = s.m_label;
  m_spriteFileName = s.m_spriteFileName;
  m_FSIdentifier = s.m_FSIdentifier;
  m_FSWSampleTime = s.m_FSWSampleTime;
  m_includedInCalculation = s.m_includedInCalculation;

  /** Orbit parameters  **/
  m_orbitProp = s.m_orbitProp;
  m_referncePoint = s.m_referncePoint;
  m_qvecPosition = s.m_qvecPosition;
  m_qvecVelocity = s.m_qvecVelocity;


  /** Initial Attitude **/
  m_angularVelReferece = s.m_angularVelReferece;
  m_attitudeType = s.m_attitudeType;
  m_attitudeWithReference = s.m_attitudeWithReference;
  m_qvecInitialAngVel = s.m_qvecInitialAngVel;
  m_qvecInitialAngleDegree = s.m_qvecInitialAngleDegree;
  m_qvecInitialAngleQuaternion = s.m_qvecInitialAngleQuaternion;
  m_initialAngleEulerSeq = s.m_initialAngleEulerSeq;

  /** Dynamic Flags **/
  m_jointRotation = s.m_jointRotation;
  m_constMassProp = s.m_constMassProp;
  m_passiveJointForceTorqueEnabled = s.m_passiveJointForceTorqueEnabled;
  m_constraintForceTorqueComputing = s.m_constraintForceTorqueComputing;
  m_refMassProps = s.m_refMassProps;
  m_flexActiveEnabled = s.m_flexActiveEnabled;
  m_include2ndorderflexActive = s.m_include2ndorderflexActive;
  m_dragCoefficient = s.m_dragCoefficient;


  //clearAllComponents();
  m_qvecSCBs = s.m_qvecSCBs;
  m_qvecJoints = s.m_qvecJoints;
  m_qvecWheels = s.m_qvecWheels;
  m_qvecMagTrqs = s.m_qvecMagTrqs;
  m_qvecThrusters = s.m_qvecThrusters;
  m_qvecGyros = s.m_qvecGyros;
  m_qvecMMAs = s.m_qvecMMAs;
  m_qvecCSSs = s.m_qvecCSSs;
  m_qvecFSSs = s.m_qvecFSSs;
  m_qvecSTs = s.m_qvecSTs;
  m_qvecGPSRs = s.m_qvecGPSRs;
  m_qvecAccels = s.m_qvecAccels;

  m_numberOfColumn = s.m_numberOfColumn;
  m_numberOfTypeOfComponents = s.m_numberOfTypeOfComponents;
  m_rowSPACECRAFTBODY = s.m_rowSPACECRAFTBODY;
  m_rowJOINT = s.m_rowJOINT;
  m_rowWHEEL = s.m_rowWHEEL;
  m_rowMAGTORQUER = s.m_rowMAGTORQUER;
  m_rowTHRUSTER = s.m_rowTHRUSTER;
  m_rowGYROAXIS = s.m_rowGYROAXIS;
  m_rowMAGNETOMETERAXIS = s.m_rowMAGNETOMETERAXIS;
  m_rowCOARSESUNSENSOR = s.m_rowCOARSESUNSENSOR;
  m_rowFINESUNSENSOR = s.m_rowFINESUNSENSOR;
  m_rowSTARTRACKER = s.m_rowSTARTRACKER;
  m_rowGPSRECEIVER = s.m_rowGPSRECEIVER;
  m_rowACCELEROMETER = s.m_rowACCELEROMETER;

  m_qvecScbObjects = s.m_qvecScbObjects;
  m_qvecJointObjects = s.m_qvecJointObjects;
  m_qvecWheelObjects = s.m_qvecWheelObjects;
  m_qvecMagTrqObjects = s.m_qvecMagTrqObjects;
  m_qvecThrusterObjects = s.m_qvecThrusterObjects;
  m_qvecGyroObjects = s.m_qvecGyroObjects;
  m_qvecMMAObjects = s.m_qvecMMAObjects;
  m_qvecCSSObjects = s.m_qvecCSSObjects;
  m_qvecFSSObjects = s.m_qvecFSSObjects;
  m_qvecSTObjects = s.m_qvecSTObjects;
  m_qvecGPSRObjects = s.m_qvecGPSRObjects;
  m_qvecAccelObjects= s.m_qvecAccelObjects;

  return *this;
}

bool operator==(const Spacecraft& sc1, const Spacecraft& sc2)
{
    double epsilon = 0.00001;
    using std::abs;
    return
    sc1.m_index == sc2.m_index  &&
    sc1.m_mission == sc2.m_mission &&
    sc1.m_spacecraftheader == sc2.m_spacecraftheader &&
    sc1.m_name == sc2.m_name &&
    sc1.m_description == sc2.m_description &&
    sc1.m_label == sc2.m_label &&
    sc1.m_spriteFileName == sc2.m_spriteFileName &&
    sc1.m_FSIdentifier == sc2.m_FSIdentifier &&

    sc1.m_orbitProp == sc2.m_orbitProp &&
    sc1.m_referncePoint == sc2.m_referncePoint &&
    compareVector(sc1.m_qvecPosition , sc2.m_qvecPosition, epsilon) &&
    compareVector(sc1.m_qvecVelocity, sc2.m_qvecVelocity, epsilon) &&
    sc1.m_qvecInitialAngVel == sc2.m_qvecInitialAngVel &&
    sc1.m_qvecInitialAngleDegree == sc2.m_qvecInitialAngleDegree &&
    sc1.m_qvecInitialAngleQuaternion == sc2.m_qvecInitialAngleQuaternion &&
    sc1.m_initialAngleEulerSeq == sc2.m_initialAngleEulerSeq &&
    sc1.m_jointRotation == sc2.m_jointRotation &&
    sc1.m_constMassProp == sc2.m_constMassProp &&
    sc1.m_passiveJointForceTorqueEnabled == sc2.m_passiveJointForceTorqueEnabled &&
    sc1.m_constraintForceTorqueComputing == sc2.m_constraintForceTorqueComputing &&
    sc1.m_refMassProps == sc2.m_refMassProps &&
    sc1.m_flexActiveEnabled == sc2.m_flexActiveEnabled &&
    sc1.m_include2ndorderflexActive == sc2.m_include2ndorderflexActive &&
    (abs(sc1.m_dragCoefficient - sc2.m_dragCoefficient) < epsilon) &&
    sc1.m_qvecSCBs == sc2.m_qvecSCBs &&
    sc1.m_qvecJoints == sc2.m_qvecJoints &&
    sc1.m_qvecWheels == sc2.m_qvecWheels &&
    sc1.m_qvecMagTrqs == sc2.m_qvecMagTrqs &&
    sc1.m_qvecThrusters == sc2.m_qvecThrusters &&
    sc1.m_qvecGyros == sc2.m_qvecGyros &&
    sc1.m_qvecMMAs == sc2.m_qvecMMAs &&
    sc1.m_qvecCSSs == sc2.m_qvecCSSs &&
    sc1.m_qvecFSSs == sc2.m_qvecFSSs &&
    sc1.m_qvecSTs == sc2.m_qvecSTs &&
    sc1.m_qvecGPSRs == sc2.m_qvecGPSRs &&
    sc1.m_qvecAccels == sc2.m_qvecAccels &&
    sc1.m_numberOfTypeOfComponents == sc2.m_numberOfTypeOfComponents &&
    sc1.m_rowSPACECRAFTBODY == sc2.m_rowSPACECRAFTBODY &&
    sc1.m_rowJOINT == sc2.m_rowJOINT &&
    sc1.m_rowWHEEL == sc2.m_rowWHEEL &&
    sc1.m_rowMAGTORQUER == sc2.m_rowMAGTORQUER &&
    sc1.m_rowTHRUSTER == sc2.m_rowTHRUSTER &&
    sc1.m_rowGYROAXIS == sc2.m_rowGYROAXIS &&
    sc1.m_rowMAGNETOMETERAXIS == sc2.m_rowMAGNETOMETERAXIS &&
    sc1.m_rowCOARSESUNSENSOR == sc2.m_rowCOARSESUNSENSOR &&
    sc1.m_rowFINESUNSENSOR == sc2.m_rowFINESUNSENSOR &&
    sc1.m_rowSTARTRACKER == sc2.m_rowSTARTRACKER &&
    sc1.m_rowGPSRECEIVER == sc2.m_rowGPSRECEIVER &&
    sc1.m_rowACCELEROMETER == sc2.m_rowACCELEROMETER;
}

void Spacecraft::clearAllComponents()
{
    m_qvecSCBs = QVector<SpacecraftBody*>();
    m_qvecJoints = QVector<Joint*>();
    m_qvecWheels = QVector<Wheel*>();
    m_qvecMagTrqs = QVector<MagTorquer*>();
    m_qvecThrusters = QVector <Thruster*>();
    m_qvecGyros = QVector<GyroAxis*>();
    m_qvecMMAs = QVector<MagnetometerAxis*>();
    m_qvecCSSs = QVector<CoarseSunSensor*>();
    m_qvecFSSs = QVector<FineSunSensor*>();
    m_qvecSTs = QVector<StarTracker*>();
    m_qvecGPSRs = QVector<GPSReceiver*>();
    m_qvecAccels = QVector<Accelerometer*>();


}


int Spacecraft::index() const
{
    if (m_mission)
       return m_index;
    return -1;
}

bool Spacecraft::createItem(objectType type)
{
    if (type == SPACECRAFTBODY)
        return createSpacecraftBody();

    else if (type == JOINT)
        return createJoint();

    else if (type == WHEEL)
        return createWheel();

    else if (type == MAGTORQUER)
        return createMagTorquer();

    else if (type == THRUSTER)
        return createThruster();

    else if (type == GYROAXIS)
        return createGyroAxis();

    else if (type == MAGNETOMETERAXIS)
        return createMagnetometerAxis();

    else if (type == COARSESUNSENSOR)
        return createCoarseSunSensor();

    else if (type == FINESUNSENSOR)
        return createFineSunSensor();

    else if (type == STARTRACKER)
        return createStarTracker();

    else if (type == GPSRECEIVER)
        return createGPSReceiver();

    else if (type == ACCELEROMETER)
        return createAccelerometer();

    else
        return false;
}

bool Spacecraft::insertItem(const int &column, objectType type,
                            Qt42BaseClass *Qt42BC)

{
    if (type == SPACECRAFTBODY)
    {
        SpacecraftBody* SCB = static_cast<SpacecraftBody*>(Qt42BC);
        insertSpacecraftBody(column, SCB);
        return true;
    }
    else if (type == JOINT)
    {
        Joint* JNT = static_cast<Joint*>(Qt42BC);
        insertJoint(column, JNT);
        return true;
    }
    else if (type == WHEEL)
    {
        Wheel* WHL = static_cast<Wheel*>(Qt42BC);
        insertWheel(column, WHL);
    }
    else if (type == MAGTORQUER)
    {
        MagTorquer* MTB = static_cast<MagTorquer*>(Qt42BC);
        insertMagTorquer(column, MTB);
    }
    else if (type == THRUSTER)
    {
        Thruster* THR = static_cast<Thruster*>(Qt42BC);
        insertThruster(column, THR);
    }
    else if (type == GYROAXIS)
    {
        GyroAxis* GYO = static_cast<GyroAxis*>(Qt42BC);
        insertGyroAxis(column, GYO);
    }
    else if (type == MAGNETOMETERAXIS)
    {
        MagnetometerAxis* MMA = static_cast<MagnetometerAxis*>(Qt42BC);
        insertMagnetometerAxis(column, MMA);
    }
    else if (type == COARSESUNSENSOR)
    {
        CoarseSunSensor* CSS = static_cast<CoarseSunSensor*>(Qt42BC);
        insertCoarseSunSensor(column, CSS);
    }
    else if (type == FINESUNSENSOR)
    {
        FineSunSensor* FSS = static_cast<FineSunSensor*>(Qt42BC);
        insertFineSunSensor(column, FSS);
    }
    else if (type == STARTRACKER)
    {
        StarTracker* ST = static_cast<StarTracker*>(Qt42BC);
        insertStarTracker(column, ST);
    }
    else if (type == GPSRECEIVER)
    {
        GPSReceiver* GPSR = static_cast<GPSReceiver*>(Qt42BC);
        insertGPSReceiver(column, GPSR);
     }
    else if (type == ACCELEROMETER)
    {
        Accelerometer* ACCL = static_cast<Accelerometer*>(Qt42BC);
        insertAccelerometer(column, ACCL);
    }
    return false;
}

int Spacecraft::columnOfComponent(objectType type) const
{
    if (type == SPACECRAFTBODY)
        return m_qvecSCBs.size();

    else if (type == JOINT)
        return m_qvecJoints.size();

    else if (type == WHEEL)
        return m_qvecWheels.size();

    else if (type == MAGTORQUER)
        return m_qvecMagTrqs.size();

    else if (type == THRUSTER)
        return m_qvecThrusters.size();

    else if (type == GYROAXIS)
        return m_qvecGyros.size();

    else if (type == MAGNETOMETERAXIS)
        return m_qvecMMAs.size();

    else if (type == COARSESUNSENSOR)
        return m_qvecCSSs.size();

    else if (type == FINESUNSENSOR)
        return m_qvecFSSs.size();

    else if (type == STARTRACKER)
        return m_qvecSTs.size();

    else if (type == GPSRECEIVER)
        return m_qvecGPSRs.size();

    else if (type == ACCELEROMETER)
        return m_qvecAccels.size();

    else
        return -1;
}

int Spacecraft::rowOfComponent(objectType type) const
{
    if (type == SPACECRAFTBODY)
        return m_rowSPACECRAFTBODY;

    else if (type == JOINT)
        return m_rowJOINT;

    else if (type == WHEEL)
        return m_rowWHEEL;

    else if (type == MAGTORQUER)
        return m_rowMAGTORQUER;

    else if (type == THRUSTER)
        return m_rowTHRUSTER;

    else if (type == GYROAXIS)
        return m_rowGYROAXIS;

    else if (type == MAGNETOMETERAXIS)
        return m_rowMAGNETOMETERAXIS;

    else if (type == COARSESUNSENSOR)
        return m_rowCOARSESUNSENSOR;

    else if (type == FINESUNSENSOR)
        return m_rowFINESUNSENSOR;

    else if (type == STARTRACKER)
        return m_rowSTARTRACKER;

    else if (type == GPSRECEIVER)
        return m_rowGPSRECEIVER;

    else if (type == ACCELEROMETER)
        return m_rowACCELEROMETER;

    else
        return -1;
}

void Spacecraft::updateIndex()
{
    if (m_spacecraftheader){
        m_index = m_spacecraftheader->indexSpacecraft(this);
    }
    else {
        m_index = -1;
    }

}

void Spacecraft::updateIndexComponents()
{
    for (auto e : m_qvecSCBs){
        e->updateIndex();
    }
    for (auto e : m_qvecJoints){
        e->updateIndex();
    }

    for (auto e : m_qvecWheels){
        e->updateIndex();
    }

    for (auto e : m_qvecMagTrqs){
        e->updateIndex();
    }

    for (auto e : m_qvecThrusters){
        e->updateIndex();
    }

    for (auto e : m_qvecThrusters){
        e->updateIndex();
    }

    for (auto e : m_qvecGyros){
        e->updateIndex();
    }

    for (auto e : m_qvecMMAs){
        e->updateIndex();
    }

    for (auto e : m_qvecCSSs){
        e->updateIndex();
    }

    for (auto e : m_qvecFSSs){
        e->updateIndex();
    }

    for (auto e : m_qvecSTs){
        e->updateIndex();
    }

    for (auto e : m_qvecGPSRs){
        e->updateIndex();
    }

    for (auto e : m_qvecAccels){
        e->updateIndex();
    }
    updateNumberOfRow();
    updateNumberOfColumn();
}

bool Spacecraft::hasName(const QString &name) const
{
    if (m_spacecraftheader)
        return m_spacecraftheader->hasSpacecraftNamedAs(name.trimmed());

    return false;
}

void Spacecraft::rename(const QString &newName)
{
   if (!hasName(newName.trimmed()))
       m_name = newName.trimmed();
}

void Spacecraft::editSCdescription(const QString& NAME, const QString& DESCRIPTION, const QString& LABEL,
                         const QString& SPRITEFILENAME, const QString& FSIDENTIFIER)
{
    m_name = NAME;
    m_description = DESCRIPTION;
    m_label = LABEL;
    m_spriteFileName = SPRITEFILENAME;
    m_FSIdentifier = FSIDENTIFIER;
}

void Spacecraft::editOrbitParameter(const QString& orbitPropagation, const QString& referencePoint,
                                    const QVector <double>& Pos, const QVector <double>& Vel)
{
    m_orbitProp     = map_orbitalPara[orbitPropagation];
    m_referncePoint = map_orbitalPara[referencePoint];
    m_qvecPosition = Pos;
    m_qvecVelocity = Vel;
}

void Spacecraft::editInitialAttitude(const QString& frame, const QString& angleForm,
                         const QVector<double> &angVel, const QVector<double> &qua,
                         const QVector<double> &eulerDeg, const QString& seq)

{
    m_qvecInitialAngVel = angVel;
    m_qvecInitialAngleQuaternion = qua;
    m_qvecInitialAngleDegree = eulerDeg;
    m_initialAngleEulerSeq = seq;
}

/**     Spacecraft Body        **/

bool Spacecraft::createSpacecraftBody()
{
    SpacecraftBody* scb = new SpacecraftBody(this);

    if (!m_qvecSCBs.contains(scb))
    {
        m_qvecSCBs.append(scb);
        for (SpacecraftBody* e : m_qvecSCBs)
            e->updateIndex();
        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }

    else
    {
        delete scb;
        return false;
    }

}

bool Spacecraft::insertSpacecraftBody(int i, SpacecraftBody *SCB)
{
    if (i < 0 || i > m_qvecSCBs.size())
        return false;
    m_qvecSCBs.insert(i, SCB);
    for (SpacecraftBody* e : m_qvecSCBs)
        e->updateIndex();
    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}


void Spacecraft::edit(const QString &description,
                      const QString &label,
                      const QString &spriteFileName,
                      const QString &FSIdentifier,
                      const double &FSWSampleTime,
                      const QString &orbitProp,
                      const QString &referncePoint,
                      const QVector<double> &position,
                      const QVector<double> &velocity,
                      const QString &angularVelReferece,
                      const QString &attitudeType,
                      const QString &attitudeWithReference,
                      const QVector<double> &initialAngVel,
                      const QVector<double> &initialAngleQuaternion,
                      const QVector<double> &initialAngleDegree,
                      const QString &initialAngleEulerSeq,
                      const QString &jointRotation,
                      const QString &refMassProps,
                      const bool &constMassProp,
                      const bool &passiveJointForceTorqueEnabled,
                      const bool &constraintForceTorqueComputing,
                      const bool &flexActiveEnabled,
                      const bool &include2ndorderflexActive,
                      const double &dragCoefficient,
                      const bool& included)
{
    m_description = description;
    m_label = label;
    m_spriteFileName = spriteFileName;
    m_FSIdentifier = FSIdentifier;
    m_FSWSampleTime = FSWSampleTime;
    m_includedInCalculation = included;


    /** Orbit parameters  **/
    m_orbitProp = orbitProp;
    m_referncePoint = referncePoint;
    m_qvecPosition = position;
    m_qvecVelocity = velocity;

    /** Initial Attitude **/
    m_angularVelReferece = angularVelReferece;
    m_attitudeType = attitudeType;
    m_attitudeWithReference = attitudeWithReference;
    m_qvecInitialAngVel = initialAngVel;
    m_qvecInitialAngleQuaternion = initialAngleQuaternion;
    m_qvecInitialAngleDegree = initialAngleDegree;
    m_initialAngleEulerSeq = initialAngleEulerSeq;

    /** Dynamic Flags **/
    m_jointRotation = jointRotation;
    m_constMassProp = constMassProp;
    m_passiveJointForceTorqueEnabled = passiveJointForceTorqueEnabled;
    m_constraintForceTorqueComputing = constraintForceTorqueComputing;
    m_refMassProps = refMassProps;
    m_flexActiveEnabled = flexActiveEnabled;
    m_include2ndorderflexActive = include2ndorderflexActive;
    m_dragCoefficient = dragCoefficient;
}



bool Spacecraft::removeSpacecraftBody(SpacecraftBody* SCB)
{
    if (m_qvecSCBs.contains(SCB)){
        m_qvecSCBs.removeAll(SCB);
        //SCB = nullptr;
        //delete SCB;
        for (auto e : m_qvecSCBs)
            e->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    return false;
}


SpacecraftBody* Spacecraft::body(const int& index)
{
    if (index > -1 && index < m_qvecSCBs.size())
        return m_qvecSCBs[index];
    return nullptr;
}




/**     Joints        **/

bool Spacecraft::createJoint()
{
    Joint* j = new Joint(this);

    if (!m_qvecJoints.contains(j))
    {
        m_qvecJoints.append(j);
        for (Joint* j : m_qvecJoints)
            j->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete j;
        return false;
    }


}

bool Spacecraft::insertJoint(int i, Joint *JNT)
{
    if (i < 0 || i > m_qvecJoints.size())
        return false;
    m_qvecJoints.insert(i, JNT);
    for (Joint* j : m_qvecJoints)
        j->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}


bool Spacecraft::removeJoint(Joint *joint)
{
    if (m_qvecJoints.contains(joint))
    {
        m_qvecJoints.removeAll(joint);
        //joint = nullptr;
        //delete joint;
        for (Joint* j : m_qvecJoints)
            j->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    return false;
}

Joint* Spacecraft::joint(const int &index)
{
    if (index > -1 && index < m_qvecJoints.size())
        return m_qvecJoints[index];
    return nullptr;
}

/***  Wheels ***/
bool Spacecraft::createWheel()
{
    Wheel* whl = new Wheel(this);

    if (!m_qvecWheels.contains(whl))
    {
        m_qvecWheels.append(whl);
        for (Wheel* w : m_qvecWheels)
            w->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete whl;
        return false;
    }

}

bool Spacecraft::insertWheel(int i, Wheel *WHL)
{
    if (i < 0 || i > m_qvecWheels.size())
        return false;
    m_qvecWheels.insert(i, WHL);
    for (Wheel* w : m_qvecWheels)
        w->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}

bool Spacecraft::removeWheel (Wheel* whl)
{
    if (m_qvecWheels.contains(whl))
    {
        m_qvecWheels.removeAll(whl);
        //whl = nullptr;
        //delete whl;
        for (Wheel* w : m_qvecWheels)
             w -> updateIndex();
        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    return false;
}

Wheel* Spacecraft::wheel(const int& index)
{
    if (index > -1 && index < m_qvecWheels.size())
        return m_qvecWheels[index];
    return nullptr;
}


/**   Mag Torquer  **/
bool Spacecraft::createMagTorquer()
{
    MagTorquer* M = new MagTorquer(this);

    if (!m_qvecMagTrqs.contains(M))
    {
        m_qvecMagTrqs.append(M);
        for (MagTorquer* e : m_qvecMagTrqs)
            e->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete M;
        return false;
    }

}

bool Spacecraft::insertMagTorquer(int i, MagTorquer *MTB)
{
    if (i < 0 || i > m_qvecMagTrqs.size())
        return false;
    m_qvecMagTrqs.insert(i, MTB);
    for (MagTorquer* e : m_qvecMagTrqs)
        e->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}


bool Spacecraft::removeMagTorquer(MagTorquer* magTorque)
{
    if (m_qvecMagTrqs.contains(magTorque))
    {
        m_qvecMagTrqs.removeAll(magTorque);
        //magTorque = nullptr;
        //delete magTorque;
        for (MagTorquer* M: m_qvecMagTrqs)
            M->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    return false;
}

MagTorquer* Spacecraft::magTorque(const int& index)
{
    if (index > -1 && index < m_qvecMagTrqs.size())
    {
        return m_qvecMagTrqs[index];
    }
    return nullptr;
}


/**  Thruster **/
bool Spacecraft::createThruster()
{
    Thruster* th = new Thruster(this);
    if (!m_qvecThrusters.contains(th))
    {
        m_qvecThrusters.append(th);
        for (Thruster* t : m_qvecThrusters)
            t->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete th;
        return false;
    }

}

bool Spacecraft::insertThruster(int i, Thruster *THR)
{
    if (i < 0 || i > m_qvecThrusters.size())
        return false;
    m_qvecThrusters.insert(i, THR);
    for (Thruster* t : m_qvecThrusters)
        t->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}


bool Spacecraft::removeThruster(Thruster* th)
{
    if (m_qvecThrusters.contains(th))
    {
        m_qvecThrusters.removeAll(th);
        //th = nullptr;
        //delete th;
        for (Thruster* t : m_qvecThrusters)
            t->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    return false;
}
Thruster* Spacecraft::thruster(const int& index)
{
    if (index > -1 && index < m_qvecThrusters.size())
        return m_qvecThrusters[index];
    return nullptr;
}


/**      GyroAxis      **/
bool Spacecraft::createGyroAxis()
{
    GyroAxis* G = new GyroAxis(this);

    if (!m_qvecGyros.contains(G))
    {
        m_qvecGyros.append(G);
        for (GyroAxis* g : m_qvecGyros)
            g->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete G;
        return false;
    }
}

bool Spacecraft::insertGyroAxis(int i, GyroAxis *GYO)
{
    if (i < 0 || i > m_qvecGyros.size())
        return false;
    m_qvecGyros.insert(i, GYO);
    for (GyroAxis* g : m_qvecGyros)
        g->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}


bool Spacecraft::removeGyroAxis(GyroAxis* G)
{
    if (m_qvecGyros.contains(G))
    {
        m_qvecGyros.removeAll(G);
        //G = nullptr;
        //delete G;
        for (GyroAxis* g: m_qvecGyros)
            g->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        return false;
    }
}

GyroAxis* Spacecraft::gyroAxis(const int& index)
{
    if (index > -1 && index < m_qvecGyros.size())
        return (m_qvecGyros[index]);
    return nullptr;
}

/**    MagnetometerAxis   **/
bool Spacecraft::createMagnetometerAxis()
{
    MagnetometerAxis* MMA = new MagnetometerAxis(this);

    if (!m_qvecMMAs.contains(MMA))
    {
        m_qvecMMAs.append(MMA);
        for (MagnetometerAxis* M: m_qvecMMAs)
            M->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete MMA;
        return false;
    }
}

bool Spacecraft::insertMagnetometerAxis(int i, MagnetometerAxis *MMA)
{
    if (i < 0 || i > m_qvecMMAs.size())
        return false;
    m_qvecMMAs.insert(i, MMA);
    for (MagnetometerAxis* M: m_qvecMMAs)
        M->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}

bool Spacecraft::removeMagnetometerAxis(MagnetometerAxis* MMA)
{
    if (m_qvecMMAs.contains(MMA))
    {
        m_qvecMMAs.removeAll(MMA);
        //MMA = nullptr;
        //delete MMA;
        for (MagnetometerAxis* M: m_qvecMMAs)
            M->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    return false;
}

MagnetometerAxis* Spacecraft::MMA(const int& index)
{
    if (index > -1 && index < m_qvecMMAs.size())
        return m_qvecMMAs[index];
    return nullptr;
}



/**     CoarseSunSensor  **/

bool Spacecraft::createCoarseSunSensor()
{
    CoarseSunSensor* CSS = new CoarseSunSensor(this);

    if (!m_qvecCSSs.contains(CSS))
    {
        m_qvecCSSs.append(CSS);
        for (CoarseSunSensor* css : m_qvecCSSs)
            css->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete CSS;
        return false;
    }

}

bool Spacecraft::insertCoarseSunSensor(int i, CoarseSunSensor *CSS)
{
    if (i < 0 || i > m_qvecCSSs.size())
        return false;
    m_qvecCSSs.insert(i, CSS);
    for (CoarseSunSensor* css : m_qvecCSSs)
        css->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}



bool Spacecraft::removeCoarseSunSensor(CoarseSunSensor* CSS)
{
    if (m_qvecCSSs.contains(CSS))
    {
        m_qvecCSSs.removeAll(CSS);
        //CSS = nullptr;
        //delete CSS;
        for (CoarseSunSensor* css : m_qvecCSSs)
            css->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    return false;
}
CoarseSunSensor* Spacecraft::coarseSunSensor(const int& index)
{
    if (index > -1 && index < m_qvecCSSs.size())
        return m_qvecCSSs[index];
    else
        return nullptr;
}


/**  FineSunSensoe   **/

bool Spacecraft::createFineSunSensor()
{
    FineSunSensor* FSS = new FineSunSensor(this);

    if (!m_qvecFSSs.contains(FSS))
    {
        m_qvecFSSs.append(FSS);
        for (FineSunSensor* f : m_qvecFSSs)
            f->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else
    {
        delete FSS;
        return false;
    }
}

bool Spacecraft::insertFineSunSensor(int i, FineSunSensor *FSS)
{
    if (i < 0 || i > m_qvecFSSs.size())
        return false;
    m_qvecFSSs.insert(i, FSS);
    for (FineSunSensor* f : m_qvecFSSs)
        f->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}

bool Spacecraft::removeFineSunSensor(FineSunSensor* FSS)
{
    if (m_qvecFSSs.contains(FSS))
    {
        m_qvecFSSs.removeAll(FSS);
        //FSS = nullptr;
        //delete FSS;
        for (FineSunSensor* F : m_qvecFSSs)
            F->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        return false;
    }
}

FineSunSensor* Spacecraft::fineSunSensor(const int& index)
{
    if (index > -1 && index < m_qvecFSSs.size())
        return m_qvecFSSs[index];
    return nullptr;
}


/**  Star Tracker **/

bool Spacecraft::createStarTracker()
{
    StarTracker* ST = new StarTracker(this);

    if (!m_qvecSTs.contains(ST))
    {
        m_qvecSTs.append(ST);
        for (StarTracker* s: m_qvecSTs)
            s->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    delete ST;
    return false;
}

bool Spacecraft::insertStarTracker(int i, StarTracker *ST)
{
    if (i < 0 || i > m_qvecSTs.size())
        return false;
    m_qvecSTs.insert(i, ST);
    for (StarTracker* s: m_qvecSTs)
        s->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}

bool Spacecraft::removeStarTracker(StarTracker* ST)
{
    if (m_qvecSTs.contains(ST))
    {
        m_qvecSTs.removeAll(ST);
        //ST = nullptr;
        //delete ST;
        for (StarTracker* s: m_qvecSTs)
            s->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    return false;
}
StarTracker* Spacecraft::starTracker(const int& index)
{
    if (index > -1 && index < m_qvecSTs.size())
        return m_qvecSTs[index];
    return nullptr;
}


/**   GPS Receiver **/

bool Spacecraft::createGPSReceiver()
{
    GPSReceiver* GPSR = new GPSReceiver(this);
    if (!m_qvecGPSRs.contains(GPSR))
    {
        m_qvecGPSRs.append(GPSR);
        for (GPSReceiver* g: m_qvecGPSRs)
            g->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete GPSR;
        return false;
    }
}

bool Spacecraft::insertGPSReceiver(int i, GPSReceiver *GPSR)
{
    if (i < 0 || i > m_qvecGPSRs.size())
        return false;
    m_qvecGPSRs.insert(i, GPSR);
    for (GPSReceiver* g: m_qvecGPSRs)
        g->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}


bool Spacecraft::removeGPSReceiver(GPSReceiver* gpsr)
{
    if (m_qvecGPSRs.contains(gpsr)){
        m_qvecGPSRs.removeAll(gpsr);
        //gpsr = nullptr;
        //delete gpsr;
        for (GPSReceiver* g: m_qvecGPSRs)
            g->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        return false;
    }
}
GPSReceiver* Spacecraft::gPSReceiver(const int& index)
{
    if (index > -1 && index < m_qvecGPSRs.size())
        return m_qvecGPSRs[index];
    else {
        return nullptr;
    }
}

/**  Accelerometer  **/
bool Spacecraft::createAccelerometer()
{
    Accelerometer* accl = new Accelerometer(this);
    if (!m_qvecAccels.contains(accl))
    {
        m_qvecAccels.append(accl);
        for (Accelerometer* a : m_qvecAccels)
            a->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        delete accl;
        return false;
    }
}

bool Spacecraft::insertAccelerometer(int i, Accelerometer *ACCL)
{
    if (i < 0 || i > m_qvecAccels.size())
        return false;
    m_qvecAccels.insert(i, ACCL);
    for (Accelerometer* a : m_qvecAccels)
        a->updateIndex();

    updateNumberOfRow();
    updateNumberOfColumn();
    return true;
}

bool Spacecraft::removeAccelerometer(Accelerometer* ACCL)
{
    if (m_qvecAccels.contains(ACCL))
    {
        m_qvecAccels.removeAll(ACCL);
        //ACCL = nullptr;
        //delete ACCL;
        for (Accelerometer* a : m_qvecAccels)
            a->updateIndex();

        updateNumberOfRow();
        updateNumberOfColumn();
        return true;
    }
    else {
        return  false;
    }
}

Accelerometer* Spacecraft::accelerometer(const int& index)
{
    if (index > -1 && index < m_qvecAccels.size())
        return m_qvecAccels[index];
    else {
        return nullptr;
    }
}



/** Component indexed **/

int Spacecraft::indexSCBs(SpacecraftBody* SCB) const
{
    if(m_qvecSCBs.contains(SCB))
        return m_qvecSCBs.indexOf(SCB);
    return -1;
}

int Spacecraft::indexJoint(Joint* joint) const
{
    if(m_qvecJoints.contains(joint))
        return m_qvecJoints.indexOf(joint);
    return -1;
}

int Spacecraft::indexWheel(Wheel* wheel) const
{
    if (m_qvecWheels.contains(wheel))
        return m_qvecWheels.indexOf(wheel);
    return -1;
}

int Spacecraft::indexMagTorquer(MagTorquer* magtrq) const
{
    if (m_qvecMagTrqs.contains(magtrq))
        return m_qvecMagTrqs.indexOf(magtrq);
    return -1;
}

int Spacecraft::indexThruster(Thruster* thrstr) const
{
    if (m_qvecThrusters.contains(thrstr))
        return m_qvecThrusters.indexOf(thrstr);
    return -1;
}
int Spacecraft::indexGyroAxis(GyroAxis* gyro) const
{
    if (m_qvecGyros.contains(gyro))
        return m_qvecGyros.indexOf(gyro);
    return -1;
}

int Spacecraft::indexMagnetometerAxis(MagnetometerAxis* mgntmt) const
{
    if (m_qvecMMAs.contains(mgntmt))
        return m_qvecMMAs.indexOf(mgntmt);
    return -1;
}

int Spacecraft::indexCoarseSunSensor(CoarseSunSensor* CSS) const
{
    if (m_qvecCSSs.contains(CSS))
        return m_qvecCSSs.indexOf(CSS);
    return -1;
}

int Spacecraft::indexFineSunSensor(FineSunSensor* FFS) const
{
    if (m_qvecFSSs.contains(FFS))
        return m_qvecFSSs.indexOf(FFS);
    return -1;
}

int Spacecraft::indexStarTracker (StarTracker* ST) const
{
    if (m_qvecSTs.contains(ST))
        return m_qvecSTs.indexOf(ST);
    return -1;
}

int Spacecraft::indexGPSReceiver(GPSReceiver* GPSR) const
{
    if (m_qvecGPSRs.contains(GPSR))
        return m_qvecGPSRs.indexOf(GPSR);
    return -1;
}

int Spacecraft::indexAccelerometer(Accelerometer* accel) const
{
    if (m_qvecAccels.contains(accel))
        return m_qvecAccels.indexOf(accel);
    return -1;
}


void Spacecraft::updateNumberOfRow()
{
    m_numberOfTypeOfComponents = 0;

    if (m_qvecSCBs.size()){
        ++m_numberOfTypeOfComponents;
        m_rowSPACECRAFTBODY = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowSPACECRAFTBODY = -1;
    /* reset the row number of spacecraft bodies to be -1 when no spacecraft bodies exist at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */


    if (m_qvecJoints.size()){
        ++m_numberOfTypeOfComponents;
        m_rowJOINT = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowJOINT = -1;
    /* reset the row number of joints to be -1 when no joints exist at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */


    if (m_qvecWheels.size()){
        ++m_numberOfTypeOfComponents;
        m_rowWHEEL = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowWHEEL = -1;
    /* reset the row number of wheels to be -1 when no wheels exist at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */

    if(m_qvecMagTrqs.size()){
        ++m_numberOfTypeOfComponents;
        m_rowMAGTORQUER = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowMAGTORQUER = -1;
    /* reset the row number of magnetic torquer to be -1 when no magnetic torquer exist
     * at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */


    if (m_qvecThrusters.size()){
        ++m_numberOfTypeOfComponents;
        m_rowTHRUSTER = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowTHRUSTER = -1;
    /* reset the row number of thrusters to be -1 when no thrusters exist at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */


    if (m_qvecGyros.size()){
        ++m_numberOfTypeOfComponents;
        m_rowGYROAXIS = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowGYROAXIS = -1;
    /* reset the row number of gyroaxis to be -1 when no gyroaxiss exist at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */


    if (m_qvecMMAs.size()){
        ++m_numberOfTypeOfComponents;
        m_rowMAGNETOMETERAXIS = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowMAGNETOMETERAXIS = -1;
    /* reset the row number of magnetometeraxis to be -1 when no magnetometeraxis exists
     * at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */


    if (m_qvecCSSs.size()){
        ++m_numberOfTypeOfComponents;
        m_rowCOARSESUNSENSOR = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowCOARSESUNSENSOR = -1;
    /* reset the row number of Coarse sun sensor to be -1 when no Coarse sun sensors exist
     * at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */


    if (m_qvecFSSs.size()){
        ++m_numberOfTypeOfComponents;
        m_rowFINESUNSENSOR = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowFINESUNSENSOR = -1;
    /* reset the row number of Fine sun sensor to be -1 when no Fine sun sensors exist
     * at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */

    if (m_qvecSTs.size()){
        ++m_numberOfTypeOfComponents;
        m_rowSTARTRACKER = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowSTARTRACKER = -1;
    /* reset the row number of Star Trackers to be -1 when no Star trackers exist
     * at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */


    if (m_qvecGPSRs.size()){
        ++m_numberOfTypeOfComponents;
        m_rowGPSRECEIVER = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowGPSRECEIVER = -1;
    /* reset the row number of GPS receiver to be -1 when no GPS receiver exist
     * at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */



    if (m_qvecAccels.size()){
        ++m_numberOfTypeOfComponents;
        m_rowACCELEROMETER = m_numberOfTypeOfComponents-1;
    }
    else
        m_rowACCELEROMETER = -1;
    /* reset the row number of Accelerometer to be -1 when no Accelerometers exist
     * at all;
     * otherwise, Qt42model::removeItem can't function correctly since it remembers the
     * old row number.
     */

}

void Spacecraft::updateNumberOfColumn()
{
    if (m_numberOfColumn < m_qvecSCBs.size())
        m_numberOfColumn = m_qvecSCBs.size();
    if (m_numberOfColumn < m_qvecJoints.size())
        m_numberOfColumn = m_qvecJoints.size();
    if (m_numberOfColumn < m_qvecWheels.size())
        m_numberOfColumn = m_qvecWheels.size();
    if (m_numberOfColumn < m_qvecMagTrqs.size())
        m_numberOfColumn = m_qvecMagTrqs.size();
    if (m_numberOfColumn < m_qvecThrusters.size())
        m_numberOfColumn = m_qvecThrusters.size();
    if (m_numberOfColumn < m_qvecGyros.size())
        m_numberOfColumn = m_qvecGyros.size();
    if (m_numberOfColumn < m_qvecMMAs.size())
        m_numberOfColumn = m_qvecMMAs.size();
    if (m_numberOfColumn < m_qvecCSSs.size())
        m_numberOfColumn = m_qvecCSSs.size();
    if (m_numberOfColumn < m_qvecFSSs.size())
        m_numberOfColumn = m_qvecFSSs.size();
    if (m_numberOfColumn < m_qvecSTs.size())
        m_numberOfColumn = m_qvecSTs.size();
    if (m_numberOfColumn < m_qvecGPSRs.size())
        m_numberOfColumn = m_qvecGPSRs.size();
    if (m_numberOfColumn < m_qvecAccels.size())
        m_numberOfColumn = m_qvecAccels.size();
}

int Spacecraft::numberOfComponentByRow(const int &row)
{
    if (row == rowACCELEROMETER())
        return numberOfAccelerometer();
    else if (row == rowGPSRECEIVER())
        return numberOfGPSReceiver();
    else if (row == rowSTARTRACKER())
        return numberOfStarTracker();
    else if (row == rowFINESUNSENSOR())
        return numberOfFineSunSensor();
    else if (row == rowCOARSESUNSENSOR())
        return numberOfCoarseSunSensor();
    else if (row == rowMAGNETOMETERAXIS())
        return numberOfMMA();
    else if (row == rowGYROAXIS())
        return numberOfGyroAxis();
    else if (row == rowTHRUSTER())
        return numberOfThruster();
    else if (row == rowMAGTORQUER())
        return numberOfMagTorquer();
    else if (row == rowWHEEL())
        return numberOfWheels();
    else if (row == rowJOINT())
        return numberOfJoints();
    else if (row == rowSPACECRAFTBODY())
        return numberOfBodies();
    else
        return 0;

}

bool Spacecraft::reset()
{
    /** Spacecraft Description File **/
    m_description = QString();
    m_label = QString();
    m_spriteFileName = QString();  //"Sprite is a computer graphics term for a two-dimensional bitmap that is integrated into a larger scene, most often in a 2D video game." from  https://en.wikipedia.org/wiki/Sprite_(computer_graphics)
    m_FSIdentifier = QString();   // Flight Software Identifier
    m_FSWSampleTime = 0.0;

    /** Orbit parameters  **/
    m_orbitProp = "FIXED";     // Orbit Prop; could be FIXED, EULER_HILL, or ENCKE;
    m_referncePoint = "CM"; // coulf be CM or ORIGIN, wrt F.
    m_qvecPosition = QVector<double>(3, 0.0);  // Pos wrt Formation (m), expressed in F
    m_qvecVelocity = QVector<double>(3, 0.0);  // Vel wrt Formation (m/s), expressed in F

    /** Initial Attitude **/
    m_angularVelReferece = "N"; //Angular Vel wrt [NL]
    m_attitudeType = "Q"; // Att [QA]
    m_attitudeWithReference = "N"; // this could be [NLF]
    m_qvecInitialAngVel = QVector<double>(3, 0.0);      // angular velocity in degree/second
    m_qvecInitialAngleQuaternion = QVector<double>(4, 0.0);  // angles in terms of quaternion
    m_qvecInitialAngleDegree = QVector<double>(3, 0.0);  // angles in degree
    m_initialAngleEulerSeq = "123";         // Euler Sequence; could be "123"

    /** Dynamic Flags **/
    m_jointRotation = "STEADY";   // Rotation STEADY, KIN_JOINT, or DYN_JOINT;
    m_constMassProp = true;     // If true, then the mass properties are assumed to be constant.
    m_passiveJointForceTorqueEnabled = false;  // If true, then the passive joint forces and torques are enabled.
    m_constraintForceTorqueComputing = false;   // If true, then the constraint forces and torques are to be computed.
    m_refMassProps = "REFPT_CM";    // the reference to which the mass props reference to; could be REFPT_CM or REFPT_JOINT. try enum
    m_flexActiveEnabled = false;  // if true, the flex active is enabled.
    m_include2ndorderflexActive = false;  // if true, 2nd order flex terms are included.
    m_dragCoefficient = 0.0;

    /**  Spacecraft components **/
    m_qvecSCBs = QVector <SpacecraftBody*>();
    m_qvecJoints = QVector <Joint*>();
    m_qvecWheels = QVector <Wheel*>();
    m_qvecMagTrqs = QVector <MagTorquer*> ();
    m_qvecThrusters = QVector <Thruster*>();
    m_qvecGyros = QVector <GyroAxis*>();
    m_qvecMMAs = QVector <MagnetometerAxis*>();
    m_qvecCSSs = QVector <CoarseSunSensor*>();
    m_qvecFSSs = QVector <FineSunSensor*>();
    m_qvecSTs = QVector <StarTracker*>();
    m_qvecGPSRs = QVector <GPSReceiver*>();
    m_qvecAccels= QVector <Accelerometer*>();


    m_numberOfColumn = 0;
    m_numberOfTypeOfComponents = 0;
    m_rowSPACECRAFTBODY = -1;
    m_rowJOINT = -1;
    m_rowWHEEL= -1;
    m_rowMAGTORQUER = -1;
    m_rowTHRUSTER = -1;
    m_rowGYROAXIS = -1;
    m_rowMAGNETOMETERAXIS = -1;
    m_rowCOARSESUNSENSOR = -1;
    m_rowFINESUNSENSOR = -1;
    m_rowSTARTRACKER = -1;
    m_rowGPSRECEIVER = -1;
    m_rowACCELEROMETER = -1;
    return true;
}

void Spacecraft::duplicate(const Spacecraft &s)
{
    m_index = s.m_index;
    m_name = s.m_name;
    m_description = s.m_description;
    m_label = s.m_label;
    m_spriteFileName = s.m_spriteFileName;
    m_FSIdentifier = s.m_FSIdentifier;
    m_FSWSampleTime = s.m_FSWSampleTime;
    /** Orbit parameters  **/
    m_orbitProp = s.m_orbitProp;
    m_referncePoint = s.m_referncePoint;
    m_qvecPosition = s.m_qvecPosition;
    m_qvecVelocity = s.m_qvecVelocity;
    m_includedInCalculation = s.m_includedInCalculation;


    /** Initial Attitude **/
    m_angularVelReferece = s.m_angularVelReferece;
    m_attitudeType = s.m_attitudeType;
    m_attitudeWithReference = s.m_attitudeWithReference;
    m_qvecInitialAngVel = s.m_qvecInitialAngVel;
    m_qvecInitialAngleDegree = s.m_qvecInitialAngleDegree;
    m_qvecInitialAngleQuaternion = s.m_qvecInitialAngleQuaternion;
    m_initialAngleEulerSeq = s.m_initialAngleEulerSeq;

    /** Dynamic Flags **/
    m_jointRotation = s.m_jointRotation;
    m_constMassProp = s.m_constMassProp;
    m_passiveJointForceTorqueEnabled = s.m_passiveJointForceTorqueEnabled;
    m_constraintForceTorqueComputing = s.m_constraintForceTorqueComputing;
    m_refMassProps = s.m_refMassProps;
    m_flexActiveEnabled = s.m_flexActiveEnabled;
    m_include2ndorderflexActive = s.m_include2ndorderflexActive;
    m_dragCoefficient = s.m_dragCoefficient;

    m_qvecScbObjects = s.m_qvecScbObjects;
    m_qvecJointObjects = s.m_qvecJointObjects;
    m_qvecWheelObjects = s.m_qvecWheelObjects;
    m_qvecMagTrqObjects = s.m_qvecMagTrqObjects;
    m_qvecThrusterObjects = s.m_qvecThrusterObjects;
    m_qvecGyroObjects = s.m_qvecGyroObjects;
    m_qvecMMAObjects = s.m_qvecMMAObjects;
    m_qvecCSSObjects = s.m_qvecCSSObjects;
    m_qvecFSSObjects = s.m_qvecFSSObjects;
    m_qvecSTObjects = s.m_qvecSTObjects;
    m_qvecGPSRObjects = s.m_qvecGPSRObjects;
    m_qvecAccelObjects = s.m_qvecAccelObjects;
}


void Spacecraft::updateSCcIncluded(const int &indexSCBEdited, const bool &included)
{
    for (Joint*& jnt : m_qvecJoints)
    {
        if (jnt->indexBodyInner() == indexSCBEdited ||
                jnt->indexBodyOuter() == indexSCBEdited)
            jnt->setIncludedInCalculation(included);
    }

    for (Thruster*& thr : m_qvecThrusters)
    {
        if (thr->indexBody() == indexSCBEdited)
            thr->setIncludedInCalculation(included);
    }

    for (CoarseSunSensor*& css : m_qvecCSSs)
    {
        if (css->bodyIndex() == indexSCBEdited)
            css->setIncludedInCalculation(included);
    }
}

QDataStream& operator<< (QDataStream& dataStream, const Spacecraft& sc)
{
    QVector <SpacecraftBody> qvecScbObjects = QVector <SpacecraftBody>();
    QVector <Joint> qvecJointObjects = QVector <Joint>();
    QVector <Wheel> qvecWheelObjects = QVector <Wheel>();
    QVector <MagTorquer> qvecMagTrqObjects = QVector <MagTorquer> ();
    QVector <Thruster> qvecThrusterObjects = QVector <Thruster>();
    QVector <GyroAxis> qvecGyroObjects = QVector <GyroAxis>();
    QVector <MagnetometerAxis> qvecMMAObjects = QVector <MagnetometerAxis>();
    QVector <CoarseSunSensor> qvecCSSObjects = QVector <CoarseSunSensor>();
    QVector <FineSunSensor> qvecFSSObjects = QVector <FineSunSensor>();
    QVector <StarTracker> qvecSTObjects = QVector <StarTracker>();
    QVector <GPSReceiver> qvecGPSRObjects = QVector <GPSReceiver>();
    QVector <Accelerometer> qvecAccelObjects= QVector <Accelerometer>();

    for (int i = 0; i < sc.m_qvecSCBs.size(); ++i)
    {
        SpacecraftBody scb = SpacecraftBody();
        scb = *sc.m_qvecSCBs[i];
        qvecScbObjects.append(scb);
    }

    for (int i = 0; i < sc.m_qvecJoints.size(); ++i)
    {
        Joint jnt = Joint();
        jnt = *sc.m_qvecJoints[i];
        qvecJointObjects.append(jnt);
    }

    for (int i = 0; i < sc.m_qvecWheels.size(); ++i)
    {
        Wheel whl = Wheel();
        whl = *sc.m_qvecWheels[i];
        qvecWheelObjects.append(whl);
    }

    for (int i = 0; i < sc.m_qvecMagTrqs.size(); ++i)
    {
        MagTorquer mtb = MagTorquer();
        mtb = *sc.m_qvecMagTrqs[i];
        qvecMagTrqObjects.append(mtb);
    }

    for (int i = 0; i < sc.m_qvecThrusters.size(); ++i)
    {
        Thruster thr = Thruster();
        thr = *sc.m_qvecThrusters[i];
        qvecThrusterObjects.append(thr);
    }

    for (int i = 0; i < sc.m_qvecGyros.size(); ++i)
    {
        GyroAxis gyo = GyroAxis();
        gyo = *sc.m_qvecGyros[i];
        qvecGyroObjects.append(gyo);
    }

    for (int i = 0; i < sc.m_qvecMMAs.size(); ++i)
    {
        MagnetometerAxis mma = MagnetometerAxis();
        mma = *sc.m_qvecMMAs[i];
        qvecMMAObjects.append(mma);
    }

    for (int i = 0; i < sc.m_qvecCSSs.size(); ++i)
    {
        CoarseSunSensor css = CoarseSunSensor();
        css = *sc.m_qvecCSSs[i];
        qvecCSSObjects.append(css);
    }

    for (int i = 0; i < sc.m_qvecFSSs.size(); ++i)
    {
        FineSunSensor fss = FineSunSensor();
        fss = *sc.m_qvecFSSs[i];
        qvecFSSObjects.append(fss);
    }

    for (int i = 0; i < sc.m_qvecSTs.size(); ++i)
    {
        StarTracker st = StarTracker();
        st = *sc.m_qvecSTs[i];
        qvecSTObjects.append(st);
    }

    for (int i = 0; i < sc.m_qvecGPSRs.size(); ++i)
    {
        GPSReceiver gpsr = GPSReceiver();
        gpsr = *sc.m_qvecGPSRs[i];
        qvecGPSRObjects.append(gpsr);
    }

    for (int i = 0; i < sc.m_qvecAccels.size(); ++i)
    {
        Accelerometer accl = Accelerometer();
        accl = *sc.m_qvecAccels[i];
        qvecAccelObjects.append(accl);
    }

    dataStream << qvecScbObjects
               << qvecJointObjects
               << qvecWheelObjects
               << qvecMagTrqObjects
               << qvecThrusterObjects
               << qvecGyroObjects
               << qvecMMAObjects
               << qvecCSSObjects
               << qvecFSSObjects
               << qvecSTObjects
               << qvecGPSRObjects
               << qvecAccelObjects
               << sc.m_includedInCalculation
               << sc.m_name
               << sc.m_index
               << sc.m_description
               << sc.m_label
               << sc.m_spriteFileName
               << sc.m_FSIdentifier
               << sc.m_FSWSampleTime
               << sc.m_orbitProp
               << sc.m_referncePoint
               << sc.m_qvecPosition
               << sc.m_qvecVelocity
               << sc.m_angularVelReferece
               << sc.m_attitudeType
               << sc.m_attitudeWithReference
               << sc.m_qvecInitialAngVel
               << sc.m_qvecInitialAngleQuaternion
               << sc.m_qvecInitialAngleDegree
               << sc.m_initialAngleEulerSeq
               << sc.m_jointRotation
               << sc.m_constMassProp
               << sc.m_passiveJointForceTorqueEnabled
               << sc.m_constraintForceTorqueComputing
               << sc.m_refMassProps
               << sc.m_flexActiveEnabled
               << sc.m_include2ndorderflexActive
               << sc.m_dragCoefficient;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, Spacecraft& sc)
{
    dataStream >> sc.m_qvecScbObjects
               >> sc.m_qvecJointObjects
               >> sc.m_qvecWheelObjects
               >> sc.m_qvecMagTrqObjects
               >> sc.m_qvecThrusterObjects
               >> sc.m_qvecGyroObjects
               >> sc.m_qvecMMAObjects
               >> sc.m_qvecCSSObjects
               >> sc.m_qvecFSSObjects
               >> sc.m_qvecSTObjects
               >> sc.m_qvecGPSRObjects
               >> sc.m_qvecAccelObjects
               >> sc.m_includedInCalculation
               >> sc.m_name
               >> sc.m_index
               >> sc.m_description
               >> sc.m_label
               >> sc.m_spriteFileName
               >> sc.m_FSIdentifier
               >> sc.m_FSWSampleTime
               >> sc.m_orbitProp
               >> sc.m_referncePoint
               >> sc.m_qvecPosition
               >> sc.m_qvecVelocity
               >> sc.m_angularVelReferece
               >> sc.m_attitudeType
               >> sc.m_attitudeWithReference
               >> sc.m_qvecInitialAngVel
               >> sc.m_qvecInitialAngleQuaternion
               >> sc.m_qvecInitialAngleDegree
               >> sc.m_initialAngleEulerSeq
               >> sc.m_jointRotation
               >> sc.m_constMassProp
               >> sc.m_passiveJointForceTorqueEnabled
               >> sc.m_constraintForceTorqueComputing
               >> sc.m_refMassProps
               >> sc.m_flexActiveEnabled
               >> sc.m_include2ndorderflexActive
               >> sc.m_dragCoefficient;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const Spacecraft& sc)
{
    QVector <SpacecraftBody> qvecScbObjects = QVector <SpacecraftBody>();
    QVector <Joint> qvecJointObjects = QVector <Joint>();
    QVector <Wheel> qvecWheelObjects = QVector <Wheel>();
    QVector <MagTorquer> qvecMagTrqObjects = QVector <MagTorquer> ();
    QVector <Thruster> qvecThrusterObjects = QVector <Thruster>();
    QVector <GyroAxis> qvecGyroObjects = QVector <GyroAxis>();
    QVector <MagnetometerAxis> qvecMMAObjects = QVector <MagnetometerAxis>();
    QVector <CoarseSunSensor> qvecCSSObjects = QVector <CoarseSunSensor>();
    QVector <FineSunSensor> qvecFSSObjects = QVector <FineSunSensor>();
    QVector <StarTracker> qvecSTObjects = QVector <StarTracker>();
    QVector <GPSReceiver> qvecGPSRObjects = QVector <GPSReceiver>();
    QVector <Accelerometer> qvecAccelObjects= QVector <Accelerometer>();

    for (int i = 0; i < sc.m_qvecSCBs.size(); ++i)
    {
        SpacecraftBody scb = SpacecraftBody();
        scb = *sc.m_qvecSCBs[i];
        qvecScbObjects.append(scb);
    }

    for (int i = 0; i < sc.m_qvecJoints.size(); ++i)
    {
        Joint jnt = Joint();
        jnt = *sc.m_qvecJoints[i];
        qvecJointObjects.append(jnt);
    }

    for (int i = 0; i < sc.m_qvecWheels.size(); ++i)
    {
        Wheel whl = Wheel();
        whl = *sc.m_qvecWheels[i];
        qvecWheelObjects.append(whl);
    }

    for (int i = 0; i < sc.m_qvecMagTrqs.size(); ++i)
    {
        MagTorquer mtb = MagTorquer();
        mtb = *sc.m_qvecMagTrqs[i];
        qvecMagTrqObjects.append(mtb);
    }

    for (int i = 0; i < sc.m_qvecThrusters.size(); ++i)
    {
        Thruster thr = Thruster();
        thr = *sc.m_qvecThrusters[i];
        qvecThrusterObjects.append(thr);
    }

    for (int i = 0; i < sc.m_qvecGyros.size(); ++i)
    {
        GyroAxis gyo = GyroAxis();
        gyo = *sc.m_qvecGyros[i];
        qvecGyroObjects.append(gyo);
    }

    for (int i = 0; i < sc.m_qvecMMAs.size(); ++i)
    {
        MagnetometerAxis mma = MagnetometerAxis();
        mma = *sc.m_qvecMMAs[i];
        qvecMMAObjects.append(mma);
    }

    for (int i = 0; i < sc.m_qvecCSSs.size(); ++i)
    {
        CoarseSunSensor css = CoarseSunSensor();
        css = *sc.m_qvecCSSs[i];
        qvecCSSObjects.append(css);
    }

    for (int i = 0; i < sc.m_qvecFSSs.size(); ++i)
    {
        FineSunSensor fss = FineSunSensor();
        fss = *sc.m_qvecFSSs[i];
        qvecFSSObjects.append(fss);
    }

    for (int i = 0; i < sc.m_qvecSTs.size(); ++i)
    {
        StarTracker st = StarTracker();
        st = *sc.m_qvecSTs[i];
        qvecSTObjects.append(st);
    }

    for (int i = 0; i < sc.m_qvecGPSRs.size(); ++i)
    {
        GPSReceiver gpsr = GPSReceiver();
        gpsr = *sc.m_qvecGPSRs[i];
        qvecGPSRObjects.append(gpsr);
    }

    for (int i = 0; i < sc.m_qvecAccels.size(); ++i)
    {
        Accelerometer accl = Accelerometer();
        accl = *sc.m_qvecAccels[i];
        qvecAccelObjects.append(accl);
    }

    dataStream << qvecScbObjects
               << qvecJointObjects
               << qvecWheelObjects
               << qvecMagTrqObjects
               << qvecThrusterObjects
               << qvecGyroObjects
               << qvecMMAObjects
               << qvecCSSObjects
               << qvecFSSObjects
               << qvecSTObjects
               << qvecGPSRObjects
               << qvecAccelObjects
               << sc.m_includedInCalculation
               << sc.m_name
               << sc.m_index
               << sc.m_description
               << sc.m_label
               << sc.m_spriteFileName
               << sc.m_FSIdentifier
               << sc.m_FSWSampleTime
               << sc.m_orbitProp
               << sc.m_referncePoint
               << sc.m_qvecPosition
               << sc.m_qvecVelocity
               << sc.m_angularVelReferece
               << sc.m_attitudeType
               << sc.m_attitudeWithReference
               << sc.m_qvecInitialAngVel
               << sc.m_qvecInitialAngleQuaternion
               << sc.m_qvecInitialAngleDegree
               << sc.m_initialAngleEulerSeq
               << sc.m_jointRotation
               << sc.m_constMassProp
               << sc.m_passiveJointForceTorqueEnabled
               << sc.m_constraintForceTorqueComputing
               << sc.m_refMassProps
               << sc.m_flexActiveEnabled
               << sc.m_include2ndorderflexActive
               << sc.m_dragCoefficient;

    return dataStream;
}
