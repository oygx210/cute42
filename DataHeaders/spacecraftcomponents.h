#ifndef SPACECRAFTCOMPONENTS_H
#define SPACECRAFTCOMPONENTS_H

#include "ShareHeaders/qt42_sharedparameters.h"
#include "qt42baseclass.h"
#include <QString>
#include <QVector>
#include <QPair>
#include <QMap>
#include <QVariant>
#include <QDataStream>
#include <iostream>
//#include <QAbstractItemModel>
//#include <QModelIndex>
class Spacecraft;

class SpacecraftBody : public Qt42BaseClass
{
public:
    SpacecraftBody(Spacecraft* parentSpacecraft = nullptr);
    ~SpacecraftBody() override;
    SpacecraftBody(const SpacecraftBody&);
    objectType type() const override {return m_type;}
    SpacecraftBody& operator=(const SpacecraftBody& scb);
    int index() const override;                       // The index of this item in Spacecraft object.
    Spacecraft* parentItem() const;              //  "parentItem()" returns the parent pointer in the qt model.
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double mass() const {return m_mass;}
    QVector<QVector <double>> momentInertiaMatrix() const {return m_momentInertiaMatrix;}
    QVector<double>locMassCenter() const {return m_locMassCenter;}
    QVector<double>constEmbeddedMomentum() const {return m_constEmbeddedMomentum;}
    QString geometryFileName () const {return m_geometryFileName;}
    QString geomteryFileDirectory() const {return m_geomteryFileDirectory;}
    QString flexFileName() const {return m_flexFileName;}

    void edit(const double& i_mass, const QVector<QVector<double>>& i_momentInertiaMatrix,
              const QVector<double>& i_locMassCenter,
              const QVector<double>& i_constEmbeddedMomentum,
              const QString& i_geometryFileName,
              const QString& i_geomteryFileDirectory,
              const bool& included);
    void duplicate(const SpacecraftBody& scb);
    bool reset();

    friend bool operator== (const SpacecraftBody& scb1, const SpacecraftBody& scb2);
    friend QDataStream& operator<< (QDataStream& dataStream, const SpacecraftBody& scb);
    friend QDataStream& operator>> (QDataStream& dataStream, SpacecraftBody& scb);
    friend QDebug operator<< (QDebug dataStream, const SpacecraftBody& scb);

private:
    int m_index = -1;
    const objectType m_type = SPACECRAFTBODY;
    const QString m_name = "Spacecraft Body";
    Spacecraft* m_Spacecraft = nullptr;

    bool m_includedInCalculation = false;
    double m_mass = 0.0;
    QVector<QVector <double>> m_momentInertiaMatrix=QVector <QVector <double>>(3, QVector <double> (3,0.0)); // unit: kg-m^2
    QVector<double> m_locMassCenter = QVector <double> (3, 0.0);           // location of mass center in meters
    QVector<double> m_constEmbeddedMomentum = QVector <double> (3, 0.0);   // constant embedded momentum; units: Nms    
    QString m_geometryFileName = QString();                  // the geometry input file name (*.obj)
    QString m_geomteryFileDirectory = QString();
    QString m_flexFileName = "NONE";
};


class Joint : public Qt42BaseClass
{
public:
    Joint(Spacecraft* parentSpacecraft =nullptr);
    ~Joint() override;
    Joint(const Joint& jnt);
    void operator=(const Joint& jnt);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    SpacecraftBody* bodyInner() const {return m_bodyInner;}
    SpacecraftBody* bodyOuter() const {return m_bodyOuter;}
    unsigned int RotDOF() const {return m_RotDOF;}
    QString RotSeq() const {return m_RotSeq;}
    QString jointType() const {return m_jointType;}
    unsigned int TrnDOF() const {return m_TrnDOF;}
    QString TrnSeq() const {return m_TrnSeq;}
    QVector <bool> RotLocked() const {return m_RotLocked;}
    QVector <bool> TrnLocked() const {return m_TrnLocked;}
    QVector <double> initialAngles() const {return m_initialAngles;}
    QVector <double> initialRates() const {return m_initialRates;}
    QVector <double> initialDisplacement() const {return m_initialDisplacement;}
    QVector <double> initialDisplacementRate() const {return m_initialDisplacementRate;}
    QVector <double> StaticAngBiGi() const {return m_StaticAngBiGi;}
    QString BiGiSeq() const {return m_BiGiSeq;}
    QVector <double> StaticAngGoBo() const {return m_StaticAngGoBo;}
    QString GoBoSeq() const {return m_GoBoSeq;}
    QVector <double> jointPosInnerBody() const {return m_jointPosInnerBody;}
    QVector <double> jointPosOuterBody() const {return m_jointPosOuterBody;}
    QVector <double> rotPassiveSpringCoeff() const {return m_rotPassiveSpringCoeff;}
    QVector <double> rotPassiveDampingCoeff() const {return m_rotPassiveDampingCoeff;}
    QVector <double> trnPassiveSpringCoeff() const {return m_trnPassiveSpringCoeff;}
    QVector <double> trnPassiveDampingCoeff() const {return m_trnPassiveDampingCoeff;}
    int indexBodyInner() const {return m_indexBodyInner;}
    int indexBodyOuter() const {return m_indexBodyOuter;}
    QString nameBodyInner() const {if (m_bodyInner) {return m_bodyInner->name();} else {return QString();}}
    QString nameBodyOuter() const {if (m_bodyOuter) {return m_bodyOuter->name();} else {return QString();}}

    int index() const override;
    Spacecraft* parentItem() const;
    void updateIndex();
    void edit(const int& indexBodyInner, const int& indexBodyOuter,
              const unsigned int& RotDOF,
              const QString& RotSeq, const QString& jointType, const unsigned int& TrnDOF,
              const QString& TrnSeq, const QVector<bool> &RotLocked, const QVector<bool>&TrnLocked,
              const QVector<double>& initialAngles, const QVector <double>& initialRates,
              const QVector <double>& initialDisplacement,
              const QVector <double>& initialDisplacementRate,
              const QVector <double>& StaticAngBiGi, const QString& BiGiSeq,
              const QVector <double>& StaticAngGoBo, const QString& GoBoSeq,
              const QVector <double>& jointPosInnerBody,
              const QVector <double>& jointPosOuterBody,
              const QVector <double>& rotPassiveSpringCoeff,
              const QVector <double>& rotPassiveDampingCoeff,
              const QVector <double>& trnPassiveSpringCoeff,
              const QVector <double>& trnPassiveDampingCoeff,
              const bool included);
    void duplicate(const Joint& jnt);
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator == (const Joint& j1, const Joint& j2);
    friend QDataStream& operator<< (QDataStream& dataStream, const Joint& jnt);
    friend QDataStream& operator>> (QDataStream& dataStream, Joint& jnt);
    friend QDebug operator<< (QDebug dataStream, const Joint& jnt);

private:
    int m_index = -1;
    const objectType m_type = JOINT;
    QString m_name = "Joint";
    Spacecraft* m_Spacecraft = nullptr;

    bool m_includedInCalculation = false;

    int m_indexBodyInner = -1;
    int m_indexBodyOuter = -1;
    SpacecraftBody* m_bodyInner = nullptr;
    SpacecraftBody* m_bodyOuter = nullptr;

    unsigned int m_RotDOF = 0;
    QString m_RotSeq = "123";         // This could be 123 or 213 and etc..
    QString m_jointType = "GIMBAL";   // This could be "GIMBAL" or "SPHERICAL"
    unsigned int m_TrnDOF = 0;        // Degree of freedom of tranlation motion (maybe?)
    QString m_TrnSeq = "123";
    QVector <bool> m_RotLocked = QVector<bool>(3,false);
    QVector <bool> m_TrnLocked = QVector<bool>(3,false);
    QVector <double> m_initialAngles = QVector<double>(3,0.0);  // Initial angles in degree (what does this reference to?)
    QVector <double> m_initialRates = QVector<double>(3,0.0);   // Initial rates in degree/second (again, what does this refernce to?)
    QVector <double> m_initialDisplacement = QVector<double>(3,0.0); // Initial displacements in meter.
    QVector <double> m_initialDisplacementRate = QVector<double>(3,0.0);  // Initial displacement rate in meter/second
    QVector <double> m_StaticAngBiGi = QVector<double>(3,0.0);  // Bi to Gi Static Angles in degree.
    QString m_BiGiSeq = "123";
    QVector <double> m_StaticAngGoBo = QVector<double>(3,0.0);  // Bi to Gi Static Angles in degree.
    QString m_GoBoSeq = "123";
    QVector <double> m_jointPosInnerBody = QVector<double>(3,0.0);  // Position wrt inner body origin in meter.
    QVector <double> m_jointPosOuterBody = QVector<double>(3,0.0);  // Position wrt outer body origin in meter.
    QVector <double> m_rotPassiveSpringCoeff = QVector<double>(3,0.0);  // Rot Passive Spring Coefficients. (Nm/rad)
    QVector <double> m_rotPassiveDampingCoeff = QVector<double>(3,0.0);  // Rot Passive Damping Coefficients. (Nms/rad)
    QVector <double> m_trnPassiveSpringCoeff = QVector<double>(3,0.0);  // Trn Passive Spring Coefficients. (N/m)
    QVector <double> m_trnPassiveDampingCoeff = QVector<double>(3,0.0);  // Trn Passive Damping Coefficients. (Ns/m)

};

class Wheel : public Qt42BaseClass
{
public:
    Wheel(Spacecraft* parentSpacecraft = nullptr);
    ~Wheel() override;
    Wheel(const Wheel&);
    void operator=(const Wheel& wheel);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double initialMomentum() const {return m_initialMomentum;}
    QVector <double> wheelAxisComp() const {return m_wheelAxisComp;}
    double maxTorque() const {return m_maxTorque;}
    double maxMomentum() const {return m_maxMomentum;}
    double wheelRotorInertia() const  {return m_wheelRotorInertia;}
    double staticImbalance() const {return m_staticImbalance;}
    double dynamicImbalance() const {return m_dynamicImbalance;}
    unsigned int flexNodeIndex() const {return m_flexNodeIndex;}

    void edit(const double& initialMomentum, const QVector <double>& wheelAxisComp,
              const double& maxTorque, const double& maxMomentum,
              const double& wheelRotorInertia, const double& staticImbalance,
              const double& dynamicImbalance, const unsigned int& flexNodeIndex,
              const bool& included);
    void duplicate(const Wheel& whl);

    int index() const override;                       // The index of this item in Spacecraft object.
    Spacecraft* parentItem() const;              //  "parentItem()" returns the parent pointer in the qt model.
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator == (const Wheel& w1, const Wheel& w2);
    friend QDataStream& operator<< (QDataStream& dataStream, const Wheel& whl);
    friend QDataStream& operator>> (QDataStream& dataStream, Wheel& whl);
    friend QDebug operator<< (QDebug dataStream, const Wheel& whl);
private:
    const objectType m_type = WHEEL;
    int m_index = -1;
    QString m_name = "Wheel";
    Spacecraft* m_Spacecraft;

    bool m_includedInCalculation = false;
    double m_initialMomentum = 0.0; // Intital Momentum; units: N-m-sec
    QVector <double> m_wheelAxisComp = QVector <double> (3, 0.0); // wheel axis components, [X,Y,Z]
    double m_maxTorque = 0.0;     // unit: N-m
    double m_maxMomentum = 0.0;   // unit: N-m-sec
    double m_wheelRotorInertia = 0.0; // unit: kg-m^2
    double m_staticImbalance = 0.0;  // g-cm
    double m_dynamicImbalance = 0.0; // g-cm^2
    unsigned int m_flexNodeIndex = 0;
};

class MagTorquer : public Qt42BaseClass
{
public:
    /* MTB (Magnetic Torquer Bars) Parameters */
    MagTorquer(Spacecraft* parentSpacecraft = nullptr);
    ~MagTorquer() override;
    MagTorquer(const MagTorquer& MTB);
    void operator=(const MagTorquer& MTB);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double saturation() const {return m_saturation;}
    QVector <double> MTBaxis() const {return m_MTBaxis;}
    unsigned int flexNodeIndex () const {return m_flexNodeIndex;}
    void edit(const double& saturation, const QVector <double>& MTBaxis,
              const unsigned int& flexNodeIndex,
              const bool& included);

    int index() const override;                       // The index of this item in Spacecraft object.
    Spacecraft* parentItem() const;              //  "parentItem()" returns the parent pointer in the qt model.
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}
    void duplicate(const MagTorquer& mtb);

    friend bool operator== (const MagTorquer& mtb1, const MagTorquer& mtb2);
    friend QDataStream& operator<< (QDataStream& dataStream, const MagTorquer& mtb);
    friend QDataStream& operator>> (QDataStream& dataStream, MagTorquer& mtb);
    friend QDebug operator<< (QDebug dataStream, const MagTorquer& mtb);

private:
    int m_index = -1;
    const objectType m_type = MAGTORQUER;
    QString m_name = "Magnetic Torquer Bars";
    Spacecraft* m_Spacecraft = nullptr;

    bool m_includedInCalculation = false;
    double m_saturation = 0.0; // units: A-m^2
    QVector <double> m_MTBaxis = QVector<double>(3, 0.0); // MTB Axis Components, [X, Y, Z]
    unsigned int m_flexNodeIndex = 0;
};

class Thruster : public Qt42BaseClass
{
public:
   Thruster(Spacecraft* parentSpacecraft = nullptr);
   ~Thruster() override;
   Thruster(const Thruster& THR);
   void operator= (const Thruster& THR);
   objectType type() const override {return m_type;}
   void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
   bool includedInCalculation () const override {return m_includedInCalculation;}
   double thrustForce() const {return m_thrustForce;}
   SpacecraftBody* body () const {return m_body;}
   int indexBody() const {return m_indexBody;}
   QVector <double> thrustAxis() const {return m_thrustAxis;}
   QVector <double> locationBody() const {return m_locationBody;}
   unsigned int flexNodeIndex() const {return m_flexNodeIndex;}
   QString bodyName () const {if (m_body) {return m_body->name();} else {return QString();}}

   void edit(const double& thrustForce, const int& indexBody,
             const QVector <double>& thrustAxis,
             const QVector <double>& locationBody, const unsigned int& flexNodeIndex,
             const bool& included);

   int index() const override;                       // The index of this item in Spacecraft object.
   Spacecraft* parentItem() const;              //  "parentItem()" returns the parent pointer in the qt model.
   void updateIndex();
   QString name() const override {return m_name + "-" + QString::number(m_index);}
   void duplicate(const Thruster& thr);

   friend bool operator== (const Thruster& thr1, const Thruster& thr2);
   friend QDataStream& operator<< (QDataStream& dataStream, const Thruster& thr);
   friend QDataStream& operator>> (QDataStream& dataStream, Thruster& thr);
   friend QDebug operator<< (QDebug dataStream, const Thruster& thr);

private:
   int m_index = -1;
   const objectType m_type = THRUSTER;
   QString m_name = "Thruster";
   Spacecraft* m_Spacecraft = nullptr;
   SpacecraftBody* m_body = nullptr;

   bool m_includedInCalculation = false;
   double m_thrustForce = 0.0;     // unit: N
   int m_indexBody = -1;
   QVector <double> m_thrustAxis = QVector <double> (3, 0.0);
   QVector <double> m_locationBody = QVector <double> (3, 0.0);   // locationin B0; unit: meter
   unsigned int m_flexNodeIndex = 0;
};

class GyroAxis : public Qt42BaseClass
{
public:
    GyroAxis(Spacecraft* parentSpacecraft = nullptr);
    ~GyroAxis() override;
    GyroAxis(const GyroAxis& G);
    void operator=(const GyroAxis& G);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double sampleTime() const {return m_sampleTime;}
    QVector <double> axisInBodyFrame() const {return m_axisInBodyFrame;}
    double maxRate() const {return m_maxRate;}
    double scaleFactorError() const {return m_scaleFactorError;}
    double quantization() const {return m_quantization;}
    double angRandomWalk() const {return m_angRandomWalk;}
    double biasStability() const {return m_biasStability;}
    double biasStabilityTimeSpan() const {return m_biasStabilityTimeSpan;}
    double angleNoise() const {return m_angleNoise;}
    double initialBias() const {return m_initialBias;}
    unsigned int flexNodeIndex() const {return m_flexNodeIndex;}

    void edit(const double& sampleTime, const QVector <double>& axisInBodyFrame,
              const double& maxRate, const double& scaleFactorError,
              const double& quantization, const double& angRandomWalk,
              const double& biasStability, const double& biasStabilityTimeSpan,
              const double& angleNoise, const double& initialBias,
              const unsigned int& flexNodeIndex,
              const bool& included);

    void duplicate(const GyroAxis& gyo);

    int index() const override;                           // The index of this item in Spacecraft object.
    Spacecraft* parentItem() const;              //  "parentItem()" returns the parent pointer in the qt model.
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator== (const GyroAxis& gyro1, const GyroAxis& gyro2);
    friend QDataStream& operator<< (QDataStream& dataStream, const GyroAxis& gyro);
    friend QDataStream& operator>> (QDataStream& dataStream, GyroAxis& gyro);
    friend QDebug operator<< (QDebug dataStream, const GyroAxis& gyro);
private:
    int m_index = -1;
    const objectType m_type = GYROAXIS;
    QString m_name = "Gyroscope";
    Spacecraft* m_Spacecraft = nullptr;

    bool m_includedInCalculation = false;
    double m_sampleTime = 0.0;    // Sample time, unit: seconds
    QVector <double> m_axisInBodyFrame = QVector <double> (3, 0.0);
    double m_maxRate = 0.0;    // unit: degree/second
    double m_scaleFactorError = 0.0;  //  unit: ppm
    double m_quantization = 0.0;    // unit: arcsec
    double m_angRandomWalk = 0.0;   // angle random walk; unit: deg/rt-hr
    double m_biasStability = 0.0;  // biasstability; unit: degree/hour
    double m_biasStabilityTimeSpan = 0.0;  // unit: hour
    double m_angleNoise = 0.0;  // unit: arcsec RMS
    double m_initialBias = 0.0;  // unit: degree/hour
    unsigned int m_flexNodeIndex = 1;
};

class MagnetometerAxis : public Qt42BaseClass
{
public:
    MagnetometerAxis(Spacecraft* parentSpacecraft = nullptr);
    ~MagnetometerAxis() override;
    MagnetometerAxis(const MagnetometerAxis& MagMt);
    void operator= (const MagnetometerAxis& MagMt);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double sampleTime() const {return m_sampleTime;}
    QVector <double> axisInBodyFrame() const {return m_axisInBodyFrame;}
    double saturation() const {return m_saturation;}
    double scaleFactorError() const {return m_scaleFactorError;}
    double quantization () const {return m_quantization;}
    double noise() const {return m_noise;}
    unsigned int flexNodeIndex() const {return m_flexNodeIndex;}

    void edit(const double& sampleTime, const QVector <double>& axisInBodyFrame,
              const double& saturation, const double& scaleFactorError,
              const double& quantization, const double& noise,
              const unsigned int& flexNodeIndex,
              const bool& included);

    void duplicate(const MagnetometerAxis& mma);

    int index() const override;                 // The index of this item in Spacecraft object.
    Spacecraft* parentItem() const;    //  "parentItem()" returns the parent pointer in the qt model.
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator== (const MagnetometerAxis& mma1, const MagnetometerAxis& mma2);
    friend QDataStream& operator<< (QDataStream& dataStream, const MagnetometerAxis& mma);
    friend QDataStream& operator>> (QDataStream& dataStream, MagnetometerAxis& mma);
    friend QDebug operator<< (QDebug dataStream, const MagnetometerAxis& mma);

private:
    int m_index = -1;
    const objectType m_type = MAGNETOMETERAXIS;
    Spacecraft* m_Spacecraft = nullptr;
    QString m_name = "Magnetometer";

    bool m_includedInCalculation = false;
    double m_sampleTime = 0.0;    // Sample time, unit: seconds
    QVector <double> m_axisInBodyFrame = QVector <double> (3, 0.0);
    double m_saturation = 0.0;   // unit: Tesla
    double m_scaleFactorError = 0.0;  //  unit: ppm
    double m_quantization = 0.0;    // unit: Tesla
    double m_noise = 0.0;           // unit:Tesla RMS
    unsigned int m_flexNodeIndex = 1;
};

class CoarseSunSensor : public Qt42BaseClass
{
public:
    CoarseSunSensor(Spacecraft* parentSpacecraft = nullptr);
    ~CoarseSunSensor() override;
    CoarseSunSensor(const CoarseSunSensor& CSS);
    void operator= (const CoarseSunSensor& CSS);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double sampleTime() const {return m_sampleTime;}
    SpacecraftBody* body() const {return m_body;}
    QString bodyName() const {if(m_body) {return m_body->name();} else {return QString();}}
    int bodyIndex () const {return m_bodyIndex;}
    QVector<double> axisInBodyFrame() const {return m_axisInBodyFrame;}
    double halfConeAngle() const {return m_halfConeAngle;}
    double scaleFactor() const {return m_scaleFactor;}
    double quantization() const {return m_quantization;}
    unsigned int flexNodeIndex() const {return m_flexNodeIndex;}

    void edit(const double& sampleTime,
              const int& bodyIndex,
              const QVector<double>& axisInBodyFrame,
              const double& halfConeAngle, const double& scaleFactor,
              const double& quantization, const unsigned int& flexNodeIndex,
              const bool& included);

    void duplicate(const CoarseSunSensor& css);

    int index() const override;
    Spacecraft* parentItem() const;
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator== (const CoarseSunSensor& css1, const CoarseSunSensor& css2);
    friend QDataStream& operator<< (QDataStream& dataStream, const CoarseSunSensor& css);
    friend QDataStream& operator>> (QDataStream& dataStream, CoarseSunSensor& css);
    friend QDebug operator<< (QDebug dataStream, const CoarseSunSensor& css);

private:
    int m_index = -1;
    const objectType m_type = COARSESUNSENSOR;
    Spacecraft* m_Spacecraft = nullptr;
    QString m_name = "Coarse Sun Sensor";
    SpacecraftBody* m_body = nullptr;

    bool m_includedInCalculation = false;
    int m_bodyIndex = -1;
    double m_sampleTime = 0.0;    // Sample time, unit: seconds
    QVector<double> m_axisInBodyFrame = QVector <double> (4,0.0);  // four components?
    double m_halfConeAngle = 0.0;    // half-cone angle; unit: degree
    double m_scaleFactor = 0.0;
    double m_quantization = 0.0;
    unsigned int m_flexNodeIndex = 0;
};

class FineSunSensor: public Qt42BaseClass
{
public:
    FineSunSensor(Spacecraft* parentSpacecraft = nullptr);
    ~FineSunSensor() override;
    FineSunSensor(const FineSunSensor& FSS);
    void operator= (const FineSunSensor& FSS);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double sampleTime() const {return  m_sampleTime;}
    QVector <double> mountingAngles() const {return m_mountingAngles;}
    QString mountingAnglesSeq() const {return m_mountingAnglesSeq;}
    QVector <double> FOV_Size() const {return m_FOV_Size;}
    double noiseEquivalentAngle() const {return m_noiseEquivalentAngle;}
    double quantization() const {return m_quantization;}
    unsigned int flexNodeIndex() const {return m_flexNodeIndex;}

    void edit(const double& sampleTime, const QVector <double>& mountingAngles,
              const QString& mountingAnglesSeq, const QVector <double>& FOV_Size,
              const double& noiseEquivalentAngle, const double& quantization,
              const unsigned int& flexNodeIndex, const bool& included);

    void duplicate(const FineSunSensor& fss);

    int index() const override;
    Spacecraft* parentItem() const;
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator== (const FineSunSensor& fss1, const FineSunSensor& fss2);
    friend QDataStream& operator<< (QDataStream& dataStream, const FineSunSensor& fss);
    friend QDataStream& operator>> (QDataStream& dataStream, FineSunSensor& fss);
    friend QDebug operator<< (QDebug dataStream, const FineSunSensor& fss);

private:
    const objectType m_type = FINESUNSENSOR;
    Spacecraft* m_Spacecraft = nullptr;
    QString m_name = "Fine Sun Sensor";

    int m_index = -1;
    bool m_includedInCalculation = false;
    double m_sampleTime = 0.0;  // unit: seconds
    QVector <double> m_mountingAngles = QVector <double>(3,0.0);  // unit: degree
    QString m_mountingAnglesSeq = "123";  // Seq in Body; ex: 123
    QVector <double> m_FOV_Size = QVector <double> (2,0.0); // X, Y FOV Size; unit: degree
    double m_noiseEquivalentAngle = 0.0;  // Noise Equivalent Angle; unit: degree RMS
    double m_quantization = 0.0;   // Quantization; unit degree
    unsigned int m_flexNodeIndex = 0;
};

class StarTracker : public Qt42BaseClass
{
public:
    StarTracker(Spacecraft* parentSpacecraft = nullptr);
    ~StarTracker() override;
    StarTracker(const StarTracker&ST);
    void operator= (const StarTracker& ST);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double sampleTime() const {return m_sampleTime;}
    QVector <double> mountingAngles() const {return m_mountingAngles;}
    QString  mountingAnglesSeq() const {return m_mountingAnglesSeq;}
    QVector <double> FOV_Size() const {return m_FOV_Size;}
    QVector <double> SunMoonEarthExclusionAngles() const {return m_SunMoonEarthExclusionAngles;}
    QVector <double> noiseEquivAng() const {return m_noiseEquivAng;}
    unsigned int flexNodeIndex() const {return m_flexNodeIndex;}

    void edit(const double& sampleTime,
              const QVector <double>& mountingAngles,
              const QString& mountingAnglesSeq,
              const QVector <double>& FOV_Size,
              const QVector <double>& SunMoonEarthExclusionAngles,
              const QVector <double>& noiseEquivAng,
              const unsigned int& flexNodeIndex, const bool& included);
    void duplicate(const StarTracker& st);

    int index() const override;                       // The index of this item in Spacecraft object.
    Spacecraft* parentItem() const;              //  "parentItem()" returns the parent pointer in the qt model.
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator== (const StarTracker& st1, const StarTracker& st2);
    friend QDataStream& operator<< (QDataStream& dataStream, const StarTracker& st);
    friend QDataStream& operator>> (QDataStream& dataStream, StarTracker& st);
    friend QDebug operator<< (QDebug dataStream, const StarTracker& st);

private:
    const objectType m_type = STARTRACKER;
    QString m_name = "Star Tracker";
    Spacecraft* m_Spacecraft = nullptr;

    int m_index = -1;
    bool m_includedInCalculation = false;
    double m_sampleTime = 0.0; // unit: second
    QVector <double> m_mountingAngles = QVector <double>(3,0.0);  // unit: degree
    QString m_mountingAnglesSeq = "123";  // Seq in Body; ex: 123
    QVector <double> m_FOV_Size = QVector <double> (2,0.0); // X, Y FOV Size; unit: degree
    QVector <double> m_SunMoonEarthExclusionAngles = QVector <double> (3,0.0);   // unit: angles
    QVector <double> m_noiseEquivAng = QVector <double> (3,0.0);  // Noise Equivalent Angle; unit: arcsec RMS
    unsigned int m_flexNodeIndex = 0;
};


class GPSReceiver : public Qt42BaseClass
{
public:
    GPSReceiver(Spacecraft* parentSpacecraft = nullptr);
    ~GPSReceiver() override;
    GPSReceiver(const GPSReceiver& GPSR);
    void operator=(const GPSReceiver& GPSR);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double sampleTime() const {return m_sampleTime;}
    double posNoise() const {return m_posNoise;}
    double velNoise() const {return m_velNoise;}
    double timeNoise() const {return m_timeNoise;}
    unsigned int flexNodeIndex() const {return m_flexNodeIndex;}
    void edit(const double& sampleTime, const double& posNoise,
              const double& velNoise  , const double& timeNoise,
              const unsigned int& flexNodeIndex,
              const bool& included);

    void duplicate(const GPSReceiver& gpsr);

    int index() const override;                       // The index of this item in Spacecraft object.
    Spacecraft* parentItem() const;              //  "parentItem()" returns the parent pointer in the qt model.
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator== (const GPSReceiver& gps1, const GPSReceiver& gps2);
    friend QDataStream& operator<< (QDataStream& dataStream, const GPSReceiver& gps);
    friend QDataStream& operator>> (QDataStream& dataStream, GPSReceiver& gps);
    friend QDebug operator<< (QDebug dataStream, const GPSReceiver& gps);
private:
    const objectType m_type = GPSRECEIVER;
    QString m_name = "GPS Receiver";
    Spacecraft* m_Spacecraft = nullptr;

    int m_index = -1;
    bool m_includedInCalculation = false;
    double m_sampleTime = 0.0;  // unit: second
    double m_posNoise = 0.0;    // Position Noise; unit: m RMS
    double m_velNoise = 0.0;    // Velocity Noise; unit m/sec RMS
    double m_timeNoise = 0.0;   // Time Noise; unit: sec RMS
    unsigned int m_flexNodeIndex = 0;
};

class Accelerometer : public Qt42BaseClass
{
public:
    Accelerometer(Spacecraft* parentSpacecraft = nullptr);
    ~Accelerometer() override;
    Accelerometer(const Accelerometer& ACCL);
    void operator=(const Accelerometer& ACCL);
    objectType type() const override {return m_type;}
    void setIncludedInCalculation(const bool& included = true) override {m_includedInCalculation = included;}
    bool includedInCalculation () const override {return m_includedInCalculation;}
    double sampleTime() const {return m_sampleTime;}
    QVector <double> posBody0() const {return m_posBody0;}
    QVector <double> axisInBodyFrame() const {return m_axisInBodyFrame;}
    double maxAcceleration() const {return m_maxAcceleration;}
    double scaleFactorError() const {return m_scaleFactorError;}
    double quantization() const {return m_quantization;}
    double randomWalk() const {return m_randomWalk;}
    double biasStability() const {return m_biasStability;}
    double timeSpan() const {return m_timeSpan;}
    double DVNoise() const {return m_DVNoise;}
    double initialBias() const {return m_initialBias;}
    unsigned int flexNodeIndex() const {return m_flexNodeIndex;}

    void edit(const double& sampleTime, const QVector<double>& posBody0,
              const QVector <double>& axisInBodyFrame,
              const double& maxAcceleration,
              const double& scaleFactorError,
              const double& quantization, const double& randomWalk,
              const double& biasStability, const double& timeSpan,
              const double& DVNoise,
              const double& initialBias, const unsigned int& flexNodeIndex,
              const bool& included);

    void duplicate(const Accelerometer& accl);

    int index() const override;                       // The index of this item in Spacecraft object.
    Spacecraft* parentItem() const;              //  "parentItem()" returns the parent pointer in the qt model.
    void updateIndex();
    QString name() const override {return m_name + "-" + QString::number(m_index);}

    friend bool operator== (const Accelerometer& accl1, const Accelerometer& accl2);
    friend QDataStream& operator<<(QDataStream& dataStream, const Accelerometer& accl);
    friend QDataStream& operator>>(QDataStream& dataStream, Accelerometer& accl);
    friend QDebug operator<<(QDebug dataStream, const Accelerometer& accl);

private:
    const objectType m_type = ACCELEROMETER;
    Spacecraft* m_Spacecraft;
    QString m_name = "Accelerometer";

    int m_index = -1;
    bool m_includedInCalculation = false;
    double m_sampleTime = 0.0; // unit: second
    QVector <double> m_posBody0 = QVector <double> (3, 0.0);   // Position in the 0th spacecraft body; unit: meter
    QVector <double> m_axisInBodyFrame = QVector <double> (3,0.0);
    double m_maxAcceleration = 0.0; // Max Acceleration (m/s^2);
    double m_scaleFactorError = 0.0; // unit: ppm
    double m_quantization = 0.0;  //  m/s^2
    double m_randomWalk = 0.0;  // unit: m/s/rt-hr
    double m_biasStability = 0.0; // unit: m/s^2
    double m_timeSpan = 0.0; // unit (hr)
    double m_DVNoise = 0.0;  // unit: m/s
    double m_initialBias = 0.0; // unit: m/s^2
    unsigned int m_flexNodeIndex = 0;
};



Q_DECLARE_METATYPE(SpacecraftBody)
Q_DECLARE_METATYPE(Joint)
Q_DECLARE_METATYPE(Wheel)
Q_DECLARE_METATYPE(Thruster)
Q_DECLARE_METATYPE(MagTorquer)
Q_DECLARE_METATYPE(GyroAxis)
Q_DECLARE_METATYPE(MagnetometerAxis)
Q_DECLARE_METATYPE(CoarseSunSensor)
Q_DECLARE_METATYPE(FineSunSensor)
Q_DECLARE_METATYPE(StarTracker)
Q_DECLARE_METATYPE(GPSReceiver)
Q_DECLARE_METATYPE(Accelerometer)

#endif // SPACECRAFTCOMPONENTS_H
