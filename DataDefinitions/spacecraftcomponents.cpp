#include "DataHeaders/spacecraftcomponents.h"
#include "DataHeaders/spacecraft.h"
#include <QDebug>

SpacecraftBody::SpacecraftBody(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft){
       m_Spacecraft = parentSpacecraft;
    }
}
SpacecraftBody::~SpacecraftBody()
{

}

SpacecraftBody& SpacecraftBody::operator=(const SpacecraftBody &SCB)
{
    if (this == &SCB)
        return *this;
    m_index = SCB.m_index;
    m_Spacecraft = SCB.m_Spacecraft;
    m_includedInCalculation = SCB.m_includedInCalculation;
    m_mass = SCB.m_mass;
    m_momentInertiaMatrix=SCB.m_momentInertiaMatrix;
    m_locMassCenter = SCB.m_locMassCenter;
    m_constEmbeddedMomentum = SCB.m_constEmbeddedMomentum;
    m_geometryFileName = SCB.m_geometryFileName;
    m_geomteryFileDirectory = SCB.m_geomteryFileDirectory;
    m_flexFileName = SCB.m_flexFileName;
    return *this;
}

bool operator== (const SpacecraftBody& scb1, const SpacecraftBody& scb2)
{
    return
            scb1.m_index == scb2.m_index &&
            scb1.m_Spacecraft == scb2.m_Spacecraft &&
            scb1.m_includedInCalculation == scb2.m_includedInCalculation &&
            scb1.m_mass == scb2.m_mass &&
            scb1.m_momentInertiaMatrix == scb2.m_momentInertiaMatrix &&
            scb1.m_locMassCenter == scb2.m_locMassCenter &&
            scb1.m_constEmbeddedMomentum == scb2.m_constEmbeddedMomentum &&
            scb1.m_geometryFileName == scb2.m_geometryFileName &&
            scb1.m_geomteryFileDirectory == scb2.m_geomteryFileDirectory &&
            scb1.m_flexFileName == scb2.m_flexFileName;
}

SpacecraftBody::SpacecraftBody(const SpacecraftBody& SCB) : Qt42BaseClass(SCB)
{
    m_index = SCB.m_index;
    m_Spacecraft = SCB.m_Spacecraft;
    m_includedInCalculation = SCB.m_includedInCalculation;
    m_mass = SCB.m_mass;
    m_momentInertiaMatrix = SCB.m_momentInertiaMatrix;
    m_locMassCenter = SCB.m_locMassCenter;
    m_constEmbeddedMomentum = SCB.m_constEmbeddedMomentum;
    m_geometryFileName = SCB.m_geometryFileName;
    m_geomteryFileDirectory = SCB.m_geomteryFileDirectory;
    m_flexFileName = SCB.m_flexFileName;
};

bool SpacecraftBody::reset()
{
    m_mass = 0.0;
    m_momentInertiaMatrix = QVector <QVector <double>>(3, QVector <double> (3,0.0));
    m_locMassCenter = QVector <double> (3, 0.0);
    m_constEmbeddedMomentum = QVector <double> (3, 0.0);
    m_geometryFileName = QString();
    m_geomteryFileDirectory = QString();
    return true;
}

int SpacecraftBody::index() const
{
    if (m_Spacecraft)
    {
        return m_index;
    }
    else
        return -1;
}
Spacecraft* SpacecraftBody::parentItem() const
{
    if (m_Spacecraft)
       return m_Spacecraft;
    else{
        return nullptr;
    }
}
void SpacecraftBody::updateIndex()
{
    if (m_Spacecraft){
        m_index = m_Spacecraft->indexSCBs(this);
    }
}

void SpacecraftBody::edit(const double &i_mass, const QVector<QVector<double> > &i_momentInertiaMatrix,
                          const QVector<double> &i_locMassCenter,
                          const QVector<double> &i_constEmbeddedMomentum,
                          const QString &i_geometryFileName,
                          const QString& i_geomteryFileDirectory,
                          const bool& included)
{
    m_mass = i_mass;
    m_momentInertiaMatrix = i_momentInertiaMatrix;
    m_locMassCenter = i_locMassCenter;
    m_constEmbeddedMomentum = i_constEmbeddedMomentum;
    m_geometryFileName = i_geometryFileName;
    m_geomteryFileDirectory = i_geomteryFileDirectory;
    m_includedInCalculation = included;
}

void SpacecraftBody::duplicate(const SpacecraftBody& scb)
{
    m_mass = scb.m_mass;
    m_momentInertiaMatrix = scb.m_momentInertiaMatrix;
    m_locMassCenter = scb.m_locMassCenter;
    m_constEmbeddedMomentum = scb.m_constEmbeddedMomentum;
    m_geometryFileName = scb.m_geometryFileName;
    m_geomteryFileDirectory = scb.m_geomteryFileDirectory;
    m_includedInCalculation = scb.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const SpacecraftBody& scb)
{
    dataStream << scb.m_includedInCalculation
               << scb.m_mass
               << scb.m_momentInertiaMatrix
               << scb.m_locMassCenter
               << scb.m_constEmbeddedMomentum
               << scb.m_geometryFileName
               << scb.m_geomteryFileDirectory
               << scb.m_flexFileName;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, SpacecraftBody& scb)
{
    dataStream >> scb.m_includedInCalculation
               >> scb.m_mass
               >> scb.m_momentInertiaMatrix
               >> scb.m_locMassCenter
               >> scb.m_constEmbeddedMomentum
               >> scb.m_geometryFileName
               >> scb.m_geomteryFileDirectory
               >> scb.m_flexFileName;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const SpacecraftBody& scb)
{
    dataStream << scb.name()
               << scb.m_includedInCalculation
               << scb.m_mass
               << scb.m_momentInertiaMatrix
               << scb.m_locMassCenter
               << scb.m_constEmbeddedMomentum
               << scb.m_geometryFileName
               << scb.m_geomteryFileDirectory
               << scb.m_flexFileName;
    return dataStream;
}

/************   Joint  **************/
Joint::Joint(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft){
        m_Spacecraft = parentSpacecraft;
    }
}
Joint::~Joint(){};
Joint::Joint(const Joint& jnt) : Qt42BaseClass(jnt)
{
    m_index = jnt.m_index;
    m_Spacecraft = jnt.m_Spacecraft;
    m_bodyInner = jnt.m_bodyInner;
    m_bodyOuter = jnt.m_bodyOuter;
    m_RotDOF = jnt.m_RotDOF;
    m_RotSeq = jnt.m_RotSeq;
    m_jointType = jnt.m_jointType;
    m_TrnDOF = jnt.m_TrnDOF;
    m_TrnSeq = jnt.m_TrnSeq;
    m_RotLocked = jnt.m_RotLocked;
    m_TrnLocked = jnt.m_TrnLocked;
    m_initialAngles = jnt.m_initialAngles;
    m_initialRates = jnt.m_initialRates;
    m_initialDisplacement = jnt.m_initialDisplacement;
    m_initialDisplacementRate = jnt.m_initialDisplacementRate;
    m_StaticAngBiGi = jnt.m_StaticAngBiGi;
    m_BiGiSeq = jnt.m_BiGiSeq;
    m_StaticAngGoBo = jnt.m_StaticAngGoBo;
    m_GoBoSeq = jnt.m_GoBoSeq;
    m_jointPosInnerBody = jnt.m_jointPosInnerBody;
    m_jointPosOuterBody = jnt.m_jointPosOuterBody;
    m_rotPassiveSpringCoeff = jnt.m_rotPassiveSpringCoeff;
    m_rotPassiveDampingCoeff = jnt.m_rotPassiveDampingCoeff;
    m_trnPassiveSpringCoeff = jnt.m_trnPassiveSpringCoeff;
    m_trnPassiveDampingCoeff = jnt.m_trnPassiveDampingCoeff;
    m_indexBodyInner = jnt.m_indexBodyInner;
    m_indexBodyOuter = jnt.m_indexBodyOuter;
    m_includedInCalculation = jnt.m_includedInCalculation;
}

void Joint::operator=(const Joint &jnt)
{
    m_index = jnt.m_index;
    m_Spacecraft = jnt.m_Spacecraft;
    m_bodyInner = jnt.m_bodyInner;
    m_bodyOuter = jnt.m_bodyOuter;
    m_RotDOF = jnt.m_RotDOF;
    m_RotSeq = jnt.m_RotSeq;
    m_jointType = jnt.m_jointType;
    m_TrnDOF = jnt.m_TrnDOF;
    m_TrnSeq = jnt.m_TrnSeq;
    m_RotLocked = jnt.m_RotLocked;
    m_TrnLocked = jnt.m_TrnLocked;
    m_initialAngles = jnt.m_initialAngles;
    m_initialRates = jnt.m_initialRates;
    m_initialDisplacement = jnt.m_initialDisplacement;
    m_initialDisplacementRate = jnt.m_initialDisplacementRate;
    m_StaticAngBiGi = jnt.m_StaticAngBiGi;
    m_BiGiSeq = jnt.m_BiGiSeq;
    m_StaticAngGoBo = jnt.m_StaticAngGoBo;
    m_GoBoSeq = jnt.m_GoBoSeq;
    m_jointPosInnerBody = jnt.m_jointPosInnerBody;
    m_jointPosOuterBody = jnt.m_jointPosOuterBody;
    m_rotPassiveSpringCoeff = jnt.m_rotPassiveSpringCoeff;
    m_rotPassiveDampingCoeff = jnt.m_rotPassiveDampingCoeff;
    m_trnPassiveSpringCoeff = jnt.m_trnPassiveSpringCoeff;
    m_trnPassiveDampingCoeff = jnt.m_trnPassiveDampingCoeff;
    m_indexBodyInner = jnt.m_indexBodyInner;
    m_indexBodyOuter = jnt.m_indexBodyOuter;
    m_includedInCalculation = jnt.m_includedInCalculation;
}

Spacecraft* Joint::parentItem() const
{
    if (m_Spacecraft)
       return m_Spacecraft;
    else{
        return nullptr;
    }
}

void Joint::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexJoint(this);
}

int Joint::index() const
{
    if (m_Spacecraft)
       return m_index;
    else
       return -1;
}

void Joint::edit(const int& indexBodyInner, const int& indexBodyOuter,
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
                 const bool included)

{
    if (m_Spacecraft)
    {
        if (indexBodyInner > -1 && indexBodyInner < m_Spacecraft->numberOfBodies())
            m_indexBodyInner = indexBodyInner;
        else
            m_indexBodyInner = -1;

        if (indexBodyOuter > -1 && indexBodyOuter < m_Spacecraft->numberOfBodies())
            m_indexBodyOuter = indexBodyOuter;
        else
            m_indexBodyOuter = -1;

        if (m_indexBodyInner > -1 && m_indexBodyOuter > -1
                && m_indexBodyInner != m_indexBodyOuter)
        {
            m_bodyInner = m_Spacecraft->body(m_indexBodyInner);
            m_bodyOuter = m_Spacecraft->body(m_indexBodyOuter);
        }
        else
        {
            m_bodyInner = nullptr;
            m_bodyOuter = nullptr;
        }
    }

    m_RotDOF = RotDOF;
    m_RotSeq = RotSeq;
    m_jointType = jointType;
    m_TrnDOF = TrnDOF;
    m_TrnSeq = TrnSeq;
    m_RotLocked = RotLocked;
    m_TrnLocked = TrnLocked;
    m_initialAngles = initialAngles;
    m_initialRates = initialRates;
    m_initialDisplacement = initialDisplacement;
    m_initialDisplacementRate = initialDisplacementRate;
    m_StaticAngBiGi = StaticAngBiGi;
    m_BiGiSeq = BiGiSeq;
    m_StaticAngGoBo = StaticAngGoBo;
    m_GoBoSeq = GoBoSeq;
    m_jointPosInnerBody = jointPosInnerBody;
    m_jointPosOuterBody = jointPosOuterBody;
    m_rotPassiveSpringCoeff = rotPassiveSpringCoeff;
    m_rotPassiveDampingCoeff = rotPassiveDampingCoeff;
    m_trnPassiveSpringCoeff = trnPassiveSpringCoeff;
    m_trnPassiveDampingCoeff = trnPassiveDampingCoeff;

    if (m_bodyInner)
        m_indexBodyInner = (m_bodyInner->name()).split("-")[1].toInt();
    else
        m_indexBodyInner = -1;
    if (m_bodyOuter)
        m_indexBodyOuter = (m_bodyOuter->name()).split("-")[1].toInt();
    else
        m_indexBodyOuter = -1;
    m_includedInCalculation = included;
}

void Joint::duplicate(const Joint &jnt)
{
    m_RotDOF = jnt.m_RotDOF;
    m_RotSeq = jnt.m_RotSeq;
    m_jointType = jnt.m_jointType;
    m_TrnDOF = jnt.m_TrnDOF;
    m_TrnSeq = jnt.m_TrnSeq;
    m_RotLocked = jnt.m_RotLocked;
    m_TrnLocked = jnt.m_TrnLocked;
    m_initialAngles = jnt.m_initialAngles;
    m_initialRates = jnt.m_initialRates;
    m_initialDisplacement = jnt.m_initialDisplacement;
    m_initialDisplacementRate = jnt.m_initialDisplacementRate;
    m_StaticAngBiGi = jnt.m_StaticAngBiGi;
    m_BiGiSeq = jnt.m_BiGiSeq;
    m_StaticAngGoBo = jnt.m_StaticAngGoBo;
    m_GoBoSeq = jnt.m_GoBoSeq;
    m_jointPosInnerBody = jnt.m_jointPosInnerBody;
    m_jointPosOuterBody = jnt.m_jointPosOuterBody;
    m_rotPassiveSpringCoeff = jnt.m_rotPassiveSpringCoeff;
    m_rotPassiveDampingCoeff = jnt.m_rotPassiveDampingCoeff;
    m_trnPassiveSpringCoeff = jnt.m_trnPassiveSpringCoeff;
    m_trnPassiveDampingCoeff = jnt.m_trnPassiveDampingCoeff;
    m_indexBodyInner = jnt.m_indexBodyInner;
    m_indexBodyOuter = jnt.m_indexBodyOuter;
    m_includedInCalculation = jnt.m_includedInCalculation;
}


bool operator == (const Joint& j1, const Joint& j2)
{
    return
            j1.m_index == j2.m_index &&
            j1.m_Spacecraft == j2.m_Spacecraft &&
            j1.m_bodyInner == j2.m_bodyInner &&
            j1.m_bodyOuter == j2.m_bodyOuter &&
            j1.m_RotDOF == j2.m_RotDOF &&
            j1.m_RotSeq == j2.m_RotSeq &&
            j1.m_jointType == j2.m_jointType &&
            j1.m_TrnDOF == j2.m_TrnDOF &&
            j1.m_TrnSeq == j2.m_TrnSeq &&
            j1.m_RotLocked == j2.m_RotLocked &&
            j1.m_TrnLocked == j2.m_TrnLocked &&
            j1.m_initialAngles == j2.m_initialAngles &&
            j1.m_initialRates == j2.m_initialRates &&
            j1.m_initialDisplacement == j2.m_initialDisplacement &&
            j1.m_initialDisplacementRate == j2.m_initialDisplacementRate &&
            j1.m_StaticAngBiGi == j2.m_StaticAngBiGi &&
            j1.m_BiGiSeq == j2.m_BiGiSeq &&
            j1.m_StaticAngGoBo == j2.m_StaticAngGoBo &&
            j1.m_GoBoSeq == j2.m_GoBoSeq &&
            j1.m_jointPosInnerBody == j2.m_jointPosInnerBody &&
            j1.m_jointPosOuterBody == j2.m_jointPosOuterBody &&
            j1.m_rotPassiveSpringCoeff == j2.m_rotPassiveSpringCoeff &&
            j1.m_rotPassiveDampingCoeff == j2.m_rotPassiveDampingCoeff &&
            j1.m_trnPassiveSpringCoeff == j2.m_trnPassiveSpringCoeff &&
            j1.m_trnPassiveDampingCoeff == j2.m_trnPassiveDampingCoeff &&
            j1.m_indexBodyInner == j2.m_indexBodyInner &&
            j1.m_indexBodyOuter == j2.m_indexBodyOuter &&
            j1.m_includedInCalculation == j2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const Joint& jnt)
{
    dataStream << jnt.m_includedInCalculation
               << jnt.m_indexBodyInner
               << jnt.m_indexBodyOuter
               << jnt.m_RotDOF
               << jnt.m_RotSeq
               << jnt.m_jointType
               << jnt.m_TrnDOF
               << jnt.m_TrnSeq
               << jnt.m_RotLocked
               << jnt.m_TrnLocked
               << jnt.m_initialAngles
               << jnt.m_initialRates
               << jnt.m_initialDisplacement
               << jnt.m_initialDisplacementRate
               << jnt.m_StaticAngBiGi
               << jnt.m_BiGiSeq
               << jnt.m_StaticAngGoBo
               << jnt.m_GoBoSeq
               << jnt.m_jointPosInnerBody
               << jnt.m_jointPosOuterBody
               << jnt.m_rotPassiveSpringCoeff
               << jnt.m_rotPassiveDampingCoeff
               << jnt.m_trnPassiveSpringCoeff
               << jnt.m_trnPassiveDampingCoeff;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, Joint& jnt)
{
    dataStream >> jnt.m_includedInCalculation
               >> jnt.m_indexBodyInner
               >> jnt.m_indexBodyOuter
               >> jnt.m_RotDOF
               >> jnt.m_RotSeq
               >> jnt.m_jointType
               >> jnt.m_TrnDOF
               >> jnt.m_TrnSeq
               >> jnt.m_RotLocked
               >> jnt.m_TrnLocked
               >> jnt.m_initialAngles
               >> jnt.m_initialRates
               >> jnt.m_initialDisplacement
               >> jnt.m_initialDisplacementRate
               >> jnt.m_StaticAngBiGi
               >> jnt.m_BiGiSeq
               >> jnt.m_StaticAngGoBo
               >> jnt.m_GoBoSeq
               >> jnt.m_jointPosInnerBody
               >> jnt.m_jointPosOuterBody
               >> jnt.m_rotPassiveSpringCoeff
               >> jnt.m_rotPassiveDampingCoeff
               >> jnt.m_trnPassiveSpringCoeff
               >> jnt.m_trnPassiveDampingCoeff;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const Joint& jnt)
{
    dataStream << jnt.name()
               << jnt.m_includedInCalculation
               << jnt.m_indexBodyInner
               << jnt.m_indexBodyOuter
               << jnt.m_RotDOF
               << jnt.m_RotSeq
               << jnt.m_jointType
               << jnt.m_TrnDOF
               << jnt.m_TrnSeq
               << jnt.m_RotLocked
               << jnt.m_TrnLocked
               << jnt.m_initialAngles
               << jnt.m_initialRates
               << jnt.m_initialDisplacement
               << jnt.m_initialDisplacementRate
               << jnt.m_StaticAngBiGi
               << jnt.m_BiGiSeq
               << jnt.m_StaticAngGoBo
               << jnt.m_GoBoSeq
               << jnt.m_jointPosInnerBody
               << jnt.m_jointPosOuterBody
               << jnt.m_rotPassiveSpringCoeff
               << jnt.m_rotPassiveDampingCoeff
               << jnt.m_trnPassiveSpringCoeff
               << jnt.m_trnPassiveDampingCoeff;
    return dataStream;
}

/************** Wheel *************/
Wheel::Wheel(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft){
        m_Spacecraft = parentSpacecraft;
    }
}
Wheel::~Wheel(){};
Wheel::Wheel(const Wheel& whl) : Qt42BaseClass(whl)
{
    m_index = whl.m_index;
    m_includedInCalculation = whl.m_includedInCalculation;
    m_Spacecraft = whl.m_Spacecraft;
    m_initialMomentum = whl.m_initialMomentum;
    m_wheelAxisComp = whl.m_wheelAxisComp;
    m_maxTorque = whl.m_maxTorque;
    m_maxMomentum = whl.m_maxMomentum;
    m_wheelRotorInertia = whl.m_wheelRotorInertia;
    m_staticImbalance = whl.m_staticImbalance;
    m_dynamicImbalance = whl.m_dynamicImbalance;
    m_flexNodeIndex = whl.m_flexNodeIndex;
}

void Wheel::operator=(const Wheel &whl)
{
    m_index = whl.m_index;
    m_includedInCalculation = whl.m_includedInCalculation;
    m_Spacecraft = whl.m_Spacecraft;
    m_initialMomentum = whl.m_initialMomentum;
    m_wheelAxisComp = whl.m_wheelAxisComp;
    m_maxTorque = whl.m_maxTorque;
    m_maxMomentum = whl.m_maxMomentum;
    m_wheelRotorInertia = whl.m_wheelRotorInertia;
    m_staticImbalance = whl.m_staticImbalance;
    m_dynamicImbalance = whl.m_dynamicImbalance;
    m_flexNodeIndex = whl.m_flexNodeIndex;
}

void Wheel::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexWheel(this);
}

Spacecraft* Wheel::parentItem() const
{
    if (m_Spacecraft)
       return m_Spacecraft;
    else{
        return nullptr;
    }
}

int Wheel::index() const
{
    if (m_Spacecraft)
        return m_index;
    else
        return -1;
}

void Wheel::edit(const double &initialMomentum, const QVector<double> &wheelAxisComp,
                 const double &maxTorque, const double &maxMomentum,
                 const double &wheelRotorInertia, const double &staticImbalance,
                 const double &dynamicImbalance, const unsigned int &flexNodeIndex,
                 const bool& included)
{
   m_initialMomentum = initialMomentum;
   m_wheelAxisComp = wheelAxisComp;
   m_maxTorque = maxTorque;
   m_maxMomentum = maxMomentum;
   m_wheelRotorInertia = wheelRotorInertia;
   m_staticImbalance = staticImbalance;
   m_dynamicImbalance = dynamicImbalance;
   m_flexNodeIndex = flexNodeIndex;
   m_includedInCalculation = included;
}

void Wheel::duplicate(const Wheel &whl)
{
    m_includedInCalculation = whl.m_includedInCalculation;
    m_initialMomentum = whl.m_initialMomentum;
    m_wheelAxisComp = whl.m_wheelAxisComp;
    m_maxTorque = whl.m_maxTorque;
    m_maxMomentum = whl.m_maxMomentum;
    m_wheelRotorInertia = whl.m_wheelRotorInertia;
    m_staticImbalance = whl.m_staticImbalance;
    m_dynamicImbalance = whl.m_dynamicImbalance;
    m_flexNodeIndex = whl.m_flexNodeIndex;
}

QDataStream& operator<< (QDataStream& dataStream, const Wheel& whl)
{
    dataStream << whl.m_includedInCalculation
               << whl.m_initialMomentum
               << whl.m_wheelAxisComp
               << whl.m_maxTorque
               << whl.m_maxMomentum
               << whl.m_wheelRotorInertia
               << whl.m_staticImbalance
               << whl.m_dynamicImbalance
               << whl.m_flexNodeIndex;

    return dataStream;
}

bool operator == (const Wheel& w1, const Wheel& w2)
{
    return
    w1.m_index == w2.m_index &&
    w1.m_includedInCalculation == w2.m_includedInCalculation &&
    w1.m_Spacecraft == w2.m_Spacecraft &&
    w1.m_initialMomentum == w2.m_initialMomentum &&
    w1.m_wheelAxisComp == w2.m_wheelAxisComp &&
    w1.m_maxTorque == w2.m_maxTorque &&
    w1.m_maxMomentum == w2.m_maxMomentum &&
    w1.m_wheelRotorInertia == w2.m_wheelRotorInertia &&
    w1.m_staticImbalance == w2.m_staticImbalance &&
    w1.m_dynamicImbalance == w2.m_dynamicImbalance &&
    w1.m_flexNodeIndex == w2.m_flexNodeIndex;
}

QDataStream& operator>> (QDataStream& dataStream, Wheel& whl)
{
    dataStream >> whl.m_includedInCalculation
               >> whl.m_initialMomentum
               >> whl.m_wheelAxisComp
               >> whl.m_maxTorque
               >> whl.m_maxMomentum
               >> whl.m_wheelRotorInertia
               >> whl.m_staticImbalance
               >> whl.m_dynamicImbalance
               >> whl.m_flexNodeIndex;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const Wheel& whl)
{
    dataStream << whl.name()
               << whl.m_includedInCalculation
               << whl.m_initialMomentum
               << whl.m_wheelAxisComp
               << whl.m_maxTorque
               << whl.m_maxMomentum
               << whl.m_wheelRotorInertia
               << whl.m_staticImbalance
               << whl.m_dynamicImbalance
               << whl.m_flexNodeIndex;

    return dataStream;
}
/*************  MagTorquer *************/

MagTorquer::MagTorquer(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft)
    {
        m_Spacecraft = parentSpacecraft;
    }
}
MagTorquer::~MagTorquer(){}
MagTorquer::MagTorquer(const MagTorquer& MTB) : Qt42BaseClass(MTB)
{
    m_index = MTB.m_index;
    m_Spacecraft = MTB.m_Spacecraft;
    m_saturation = MTB.m_saturation;
    m_MTBaxis = MTB.m_MTBaxis;
    m_flexNodeIndex = MTB.m_flexNodeIndex;
    m_includedInCalculation = MTB.m_includedInCalculation;
}

void MagTorquer::operator=(const MagTorquer &MTB)
{
    m_index = MTB.m_index;
    m_Spacecraft = MTB.m_Spacecraft;
    m_saturation = MTB.m_saturation;
    m_MTBaxis = MTB.m_MTBaxis;
    m_flexNodeIndex = MTB.m_flexNodeIndex;
    m_includedInCalculation = MTB.m_includedInCalculation;
}

void MagTorquer::edit(const double &saturation, const QVector<double> &MTBaxis,
                      const unsigned int &flexNodeIndex,
                      const bool& included)
{
    m_saturation = saturation;
    m_MTBaxis = MTBaxis;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
}

void MagTorquer::duplicate(const MagTorquer &mtb)
{
    m_includedInCalculation = mtb.m_includedInCalculation;
    m_saturation = mtb.m_saturation;
    m_MTBaxis = mtb.m_MTBaxis;
    m_flexNodeIndex = mtb.m_flexNodeIndex;
}

void MagTorquer::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexMagTorquer(this);
}

Spacecraft* MagTorquer::parentItem() const
{
    if (m_Spacecraft)
       return m_Spacecraft;
    else{
        return nullptr;
    }
}

int MagTorquer::index() const
{
    if (m_Spacecraft)
        return m_index;
    else
        return -1;
}

bool operator== (const MagTorquer& mtb1, const MagTorquer& mtb2)
{
    return
            mtb1.m_index == mtb2.m_index &&
            mtb1.m_Spacecraft == mtb2.m_Spacecraft &&
            mtb1.m_saturation == mtb2.m_saturation &&
            mtb1.m_MTBaxis == mtb2.m_MTBaxis &&
            mtb1.m_flexNodeIndex == mtb2.m_flexNodeIndex &&
            mtb1.m_includedInCalculation == mtb2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const MagTorquer& mtb)
{
    dataStream << mtb.m_includedInCalculation
               << mtb.m_saturation
               << mtb.m_MTBaxis
               << mtb.m_flexNodeIndex;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, MagTorquer& mtb)
{
    dataStream >> mtb.m_includedInCalculation
               >> mtb.m_saturation
               >> mtb.m_MTBaxis
               >> mtb.m_flexNodeIndex;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const MagTorquer& mtb)
{
    dataStream << mtb.name()
               << mtb.m_includedInCalculation
               << mtb.m_saturation
               << mtb.m_MTBaxis
               << mtb.m_flexNodeIndex;
    return dataStream;
}


/************* Thruster **************/
Thruster::Thruster(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft)
    {
        m_Spacecraft = parentSpacecraft;
    }
}
Thruster::~Thruster(){}
Thruster::Thruster(const Thruster&th) : Qt42BaseClass(th)
{
    m_index = th.m_index;
    m_Spacecraft = th.m_Spacecraft;
    m_thrustForce = th.m_thrustForce;
    m_body = th.m_body;
    m_indexBody = th.m_indexBody;
    m_thrustAxis = th.m_thrustAxis;
    m_locationBody = th.m_locationBody;
    m_flexNodeIndex = th.m_flexNodeIndex;
    m_includedInCalculation = th.m_includedInCalculation;
}

void Thruster::operator=(const Thruster &th)
{
    m_index = th.m_index;
    m_Spacecraft = th.m_Spacecraft;
    m_thrustForce = th.m_thrustForce;
    m_body = th.m_body;
    m_indexBody = th.m_indexBody;
    m_thrustAxis = th.m_thrustAxis;
    m_locationBody = th.m_locationBody;
    m_flexNodeIndex = th.m_flexNodeIndex;
    m_includedInCalculation = th.m_includedInCalculation;
}

void Thruster::edit(const double &thrustForce,
                    const int& indexBody,
                    const QVector<double> &thrustAxis,
                    const QVector<double> &locationBody,
                    const unsigned int &flexNodeIndex,
                    const bool& included)

{
    m_thrustForce = thrustForce;
    m_indexBody = indexBody;
    m_thrustAxis = thrustAxis;
    m_locationBody = locationBody;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
    if (m_Spacecraft && indexBody > -1 && indexBody < m_Spacecraft->numberOfBodies())
        m_body = m_Spacecraft->body(m_indexBody);
    else
        m_body = nullptr;
}

void Thruster::duplicate(const Thruster &thr)
{
    m_includedInCalculation = thr.m_includedInCalculation;
    m_thrustForce = thr.m_thrustForce;
    m_indexBody = thr.m_indexBody;
    m_thrustAxis = thr.m_thrustAxis;
    m_locationBody = thr.m_locationBody;
    m_flexNodeIndex = thr.m_flexNodeIndex;
}

void Thruster::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexThruster(this);
}

Spacecraft* Thruster::parentItem() const
{
    if (m_Spacecraft)
       return m_Spacecraft;
    else{
        return nullptr;
    }
}

int Thruster::index() const
{
    if (m_Spacecraft)
        return m_index;
    else
        return -1;
}

bool operator== (const Thruster& thr1, const Thruster& thr2)
{
    return
            thr1.m_index == thr2.m_index &&
            thr1.m_Spacecraft == thr2.m_Spacecraft &&
            thr1.m_thrustForce == thr2.m_thrustForce &&
            thr1.m_body == thr2.m_body &&
            thr1.m_indexBody == thr2.m_indexBody &&
            thr1.m_thrustAxis == thr2.m_thrustAxis &&
            thr1.m_locationBody == thr2.m_locationBody &&
            thr1.m_flexNodeIndex == thr2.m_flexNodeIndex &&
            thr1.m_includedInCalculation == thr2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const Thruster& thr)
{
    dataStream << thr.m_includedInCalculation
               << thr.m_thrustForce
               << thr.m_indexBody
               << thr.m_thrustAxis
               << thr.m_locationBody
               << thr.m_flexNodeIndex;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, Thruster& thr)
{
    dataStream >> thr.m_includedInCalculation
            >> thr.m_thrustForce
            >> thr.m_indexBody
            >> thr.m_thrustAxis
            >> thr.m_locationBody
            >> thr.m_flexNodeIndex;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const Thruster& thr)
{
    dataStream << thr.name()
               << thr.m_includedInCalculation
               << thr.m_thrustForce
               << thr.m_indexBody
               << thr.m_thrustAxis
               << thr.m_locationBody
               << thr.m_flexNodeIndex;
    return dataStream;
}

/****************  GyroAxis ************/
GyroAxis::GyroAxis(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft){
        m_Spacecraft = parentSpacecraft;
    }
}
GyroAxis::~GyroAxis(){}
GyroAxis::GyroAxis(const GyroAxis& G) : Qt42BaseClass(G)
{
    m_index = G.m_index;
    m_Spacecraft = G.m_Spacecraft;
    m_sampleTime = G.m_sampleTime;
    m_axisInBodyFrame = G.m_axisInBodyFrame;
    m_maxRate = G.m_maxRate;
    m_scaleFactorError = G.m_scaleFactorError;
    m_quantization = G.m_quantization;
    m_angRandomWalk = G.m_angRandomWalk;
    m_biasStability = G.m_biasStability;
    m_biasStabilityTimeSpan = G.m_biasStabilityTimeSpan;
    m_angleNoise = G.m_angleNoise;
    m_initialBias = G.m_initialBias;
    m_flexNodeIndex = G.m_flexNodeIndex;
    m_includedInCalculation = G.m_includedInCalculation;
}

void GyroAxis::operator=(const GyroAxis &G)
{
    m_index = G.m_index;
    m_Spacecraft = G.m_Spacecraft;
    m_sampleTime = G.m_sampleTime;
    m_axisInBodyFrame = G.m_axisInBodyFrame;
    m_maxRate = G.m_maxRate;
    m_scaleFactorError = G.m_scaleFactorError;
    m_quantization = G.m_quantization;
    m_angRandomWalk = G.m_angRandomWalk;
    m_biasStability = G.m_biasStability;
    m_biasStabilityTimeSpan = G.m_biasStabilityTimeSpan;
    m_angleNoise = G.m_angleNoise;
    m_initialBias = G.m_initialBias;
    m_flexNodeIndex = G.m_flexNodeIndex;
    m_includedInCalculation = G.m_includedInCalculation;
}

void GyroAxis::edit(const double &sampleTime, const QVector<double> &axisInBodyFrame,
                    const double &maxRate, const double &scaleFactorError,
                    const double &quantization, const double &angRandomWalk,
                    const double &biasStability, const double &biasStabilityTimeSpan,
                    const double &angleNoise, const double &initialBias,
                    const unsigned int &flexNodeIndex,
                    const bool& included)
{
    m_sampleTime = sampleTime;
    m_axisInBodyFrame = axisInBodyFrame;
    m_maxRate = maxRate;
    m_scaleFactorError = scaleFactorError;
    m_quantization = quantization;
    m_angRandomWalk = angRandomWalk;
    m_biasStability = biasStability;
    m_biasStabilityTimeSpan = biasStabilityTimeSpan;
    m_angleNoise = angleNoise;
    m_initialBias = initialBias;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
}

void GyroAxis::duplicate(const GyroAxis &gyo)
{
    m_includedInCalculation = gyo.m_includedInCalculation;
    m_sampleTime = gyo.m_sampleTime;
    m_axisInBodyFrame = gyo.m_axisInBodyFrame;
    m_maxRate = gyo.m_maxRate;
    m_scaleFactorError = gyo.m_scaleFactorError;
    m_quantization = gyo.m_quantization;
    m_angRandomWalk = gyo.m_angRandomWalk;
    m_biasStability = gyo.m_biasStability;
    m_biasStabilityTimeSpan = gyo.m_biasStabilityTimeSpan;
    m_angleNoise = gyo.m_angleNoise;
    m_initialBias = gyo.m_initialBias;
    m_flexNodeIndex = gyo.m_flexNodeIndex;
}

void GyroAxis::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexGyroAxis(this);
}

Spacecraft*  GyroAxis::parentItem() const
{
    if (m_Spacecraft)
       return m_Spacecraft;
    else{
        return nullptr;
    }
}

int GyroAxis::index() const
{
    if (m_Spacecraft)
        return m_index;
    else
        return -1;
}

bool operator== (const GyroAxis& gyro1, const GyroAxis& gyro2)
{
    return
            gyro1.m_index == gyro2.m_index &&
            gyro1.m_Spacecraft == gyro2.m_Spacecraft &&
            gyro1.m_sampleTime == gyro2.m_sampleTime &&
            gyro1.m_axisInBodyFrame == gyro2.m_axisInBodyFrame &&
            gyro1.m_maxRate == gyro2.m_maxRate &&
            gyro1.m_scaleFactorError == gyro2.m_scaleFactorError &&
            gyro1.m_quantization == gyro2.m_quantization &&
            gyro1.m_angRandomWalk == gyro2.m_angRandomWalk &&
            gyro1.m_biasStability == gyro2.m_biasStability &&
            gyro1.m_biasStabilityTimeSpan == gyro2.m_biasStabilityTimeSpan &&
            gyro1.m_angleNoise == gyro2.m_angleNoise &&
            gyro1.m_initialBias == gyro2.m_initialBias &&
            gyro1.m_flexNodeIndex == gyro2.m_flexNodeIndex &&
            gyro1.m_includedInCalculation == gyro2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const GyroAxis& gyro)
{
    dataStream << gyro.m_includedInCalculation
        << gyro.m_sampleTime
        << gyro.m_axisInBodyFrame
        << gyro.m_maxRate
        << gyro.m_scaleFactorError
        << gyro.m_quantization
        << gyro.m_angRandomWalk
        << gyro.m_biasStability
        << gyro.m_biasStabilityTimeSpan
        << gyro.m_angleNoise
        << gyro.m_initialBias
        << gyro.m_flexNodeIndex;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, GyroAxis& gyro)
{
    dataStream >> gyro.m_includedInCalculation
            >> gyro.m_sampleTime
            >> gyro.m_axisInBodyFrame
            >> gyro.m_maxRate
            >> gyro.m_scaleFactorError
            >> gyro.m_quantization
            >> gyro.m_angRandomWalk
            >> gyro.m_biasStability
            >> gyro.m_biasStabilityTimeSpan
            >> gyro.m_angleNoise
            >> gyro.m_initialBias
            >> gyro.m_flexNodeIndex;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const GyroAxis& gyro)
{
    dataStream << gyro.name()
               << gyro.m_includedInCalculation
               << gyro.m_sampleTime
               << gyro.m_axisInBodyFrame
               << gyro.m_maxRate
               << gyro.m_scaleFactorError
               << gyro.m_quantization
               << gyro.m_angRandomWalk
               << gyro.m_biasStability
               << gyro.m_biasStabilityTimeSpan
               << gyro.m_angleNoise
               << gyro.m_initialBias
               << gyro.m_flexNodeIndex;

    return dataStream;
}


/************ MagnetometerAxis ***********/
MagnetometerAxis::MagnetometerAxis(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if(parentSpacecraft){
        m_Spacecraft = parentSpacecraft;
    }
}

MagnetometerAxis::~MagnetometerAxis(){}
MagnetometerAxis::MagnetometerAxis(const MagnetometerAxis& MagMt) : Qt42BaseClass(MagMt)
{
    m_index = MagMt.m_index;
    m_Spacecraft = MagMt.m_Spacecraft;
    m_sampleTime = MagMt.m_sampleTime;
    m_axisInBodyFrame = MagMt.m_axisInBodyFrame;
    m_saturation = MagMt.m_saturation;
    m_scaleFactorError = MagMt.m_scaleFactorError;
    m_quantization = MagMt.m_quantization;
    m_noise = MagMt.m_noise;
    m_flexNodeIndex = MagMt.m_flexNodeIndex;
    m_includedInCalculation = MagMt.m_includedInCalculation;
}

void MagnetometerAxis::operator=(const MagnetometerAxis &MagMt)
{
    m_index = MagMt.m_index;
    m_Spacecraft = MagMt.m_Spacecraft;
    m_sampleTime = MagMt.m_sampleTime;
    m_axisInBodyFrame = MagMt.m_axisInBodyFrame;
    m_saturation = MagMt.m_saturation;
    m_scaleFactorError = MagMt.m_scaleFactorError;
    m_quantization = MagMt.m_quantization;
    m_noise = MagMt.m_noise;
    m_flexNodeIndex = MagMt.m_flexNodeIndex;
    m_includedInCalculation = MagMt.m_includedInCalculation;
}

void MagnetometerAxis::duplicate(const MagnetometerAxis &mma)
{
    m_includedInCalculation = mma.m_includedInCalculation;
    m_sampleTime = mma.m_sampleTime;
    m_axisInBodyFrame = mma.m_axisInBodyFrame;
    m_saturation = mma.m_saturation;
    m_scaleFactorError = mma.m_scaleFactorError;
    m_quantization = mma.m_quantization;
    m_noise = mma.m_noise;
    m_flexNodeIndex = mma.m_flexNodeIndex;
}

void MagnetometerAxis::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexMagnetometerAxis(this);
}

void MagnetometerAxis::edit(const double &sampleTime,
                            const QVector<double> &axisInBodyFrame,
                            const double &saturation, const double &scaleFactorError,
                            const double &quantization, const double &noise,
                            const unsigned int &flexNodeIndex,
                            const bool& included)
{
    m_sampleTime = sampleTime;
    m_axisInBodyFrame = axisInBodyFrame;
    m_saturation = saturation;
    m_scaleFactorError = scaleFactorError;
    m_quantization = quantization;
    m_noise = noise;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
}

Spacecraft* MagnetometerAxis::parentItem() const
{
    if (m_Spacecraft)
       return m_Spacecraft;
    else{
        return nullptr;
    }
}

int MagnetometerAxis::index() const
{
    if (m_Spacecraft)
        return m_index;
    else
        return -1;
}


bool operator== (const MagnetometerAxis& mma1, const MagnetometerAxis& mma2)
{
    return
            mma1.m_index == mma2.m_index &&
            mma1.m_Spacecraft == mma2.m_Spacecraft &&
            mma1.m_sampleTime == mma2.m_sampleTime &&
            mma1.m_axisInBodyFrame == mma2.m_axisInBodyFrame &&
            mma1.m_saturation == mma2.m_saturation &&
            mma1.m_scaleFactorError == mma2.m_scaleFactorError &&
            mma1.m_quantization == mma2.m_quantization &&
            mma1.m_noise == mma2.m_noise &&
            mma1.m_flexNodeIndex == mma2.m_flexNodeIndex &&
            mma1.m_includedInCalculation == mma2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const MagnetometerAxis& mma)
{
    dataStream << mma.m_includedInCalculation
               << mma.m_sampleTime
               << mma.m_axisInBodyFrame
               << mma.m_saturation
               << mma.m_scaleFactorError
               << mma.m_quantization
               << mma.m_noise
               << mma.m_flexNodeIndex;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, MagnetometerAxis& mma)
{
    dataStream >> mma.m_includedInCalculation
            >> mma.m_sampleTime
            >> mma.m_axisInBodyFrame
            >> mma.m_saturation
            >> mma.m_scaleFactorError
            >> mma.m_quantization
            >> mma.m_noise
            >> mma.m_flexNodeIndex;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const MagnetometerAxis& mma)
{
    dataStream << mma.m_includedInCalculation
               << mma.m_sampleTime
               << mma.m_axisInBodyFrame
               << mma.m_saturation
               << mma.m_scaleFactorError
               << mma.m_quantization
               << mma.m_noise
               << mma.m_flexNodeIndex;

    return dataStream;
}


/***********  CoarseSunSensor ***************/
CoarseSunSensor::CoarseSunSensor(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft){
        m_Spacecraft = parentSpacecraft;
    }
}
CoarseSunSensor::~CoarseSunSensor(){}
CoarseSunSensor::CoarseSunSensor(const CoarseSunSensor& CSS) : Qt42BaseClass(CSS)
{
    m_index = CSS.m_index;
    m_Spacecraft = CSS.m_Spacecraft;
    m_sampleTime = CSS.m_sampleTime;
    m_body = CSS.m_body;
    m_bodyIndex = CSS.m_bodyIndex;
    m_axisInBodyFrame = CSS.m_axisInBodyFrame;
    m_halfConeAngle = CSS.m_halfConeAngle;
    m_scaleFactor = CSS.m_scaleFactor;
    m_quantization = CSS.m_quantization;
    m_flexNodeIndex = CSS.m_flexNodeIndex;
    m_includedInCalculation = CSS.m_includedInCalculation;
}

void CoarseSunSensor::operator=(const CoarseSunSensor &CSS)
{
    m_index = CSS.m_index;
    m_Spacecraft = CSS.m_Spacecraft;
    m_sampleTime = CSS.m_sampleTime;
    m_body = CSS.m_body;
    m_bodyIndex = CSS.m_bodyIndex;
    m_axisInBodyFrame = CSS.m_axisInBodyFrame;
    m_halfConeAngle = CSS.m_halfConeAngle;
    m_scaleFactor = CSS.m_scaleFactor;
    m_quantization = CSS.m_quantization;
    m_flexNodeIndex = CSS.m_flexNodeIndex;
    m_includedInCalculation = CSS.m_includedInCalculation;
}

void CoarseSunSensor::edit(const double& sampleTime,
                           const int& bodyIndex,
                           const QVector<double>& axisInBodyFrame,
                           const double& halfConeAngle, const double& scaleFactor,
                           const double& quantization, const unsigned int& flexNodeIndex,
                           const bool& included)
{
    m_sampleTime = sampleTime;
    m_bodyIndex = bodyIndex;
    m_axisInBodyFrame = axisInBodyFrame;
    m_halfConeAngle =halfConeAngle;
    m_scaleFactor = scaleFactor;
    m_quantization = quantization;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
    if (m_Spacecraft && bodyIndex > -1 && bodyIndex < m_Spacecraft->numberOfBodies())
        m_body = m_Spacecraft->body(m_bodyIndex);
    else
        m_body = nullptr;
}

void CoarseSunSensor::duplicate(const CoarseSunSensor &css)
{
    m_includedInCalculation = css.m_includedInCalculation;
    m_bodyIndex = css.m_bodyIndex;
    m_sampleTime = css.m_sampleTime;
    m_axisInBodyFrame = css.m_axisInBodyFrame;
    m_halfConeAngle = css.m_halfConeAngle;
    m_scaleFactor = css.m_scaleFactor;
    m_quantization = css.m_quantization;
    m_flexNodeIndex = css.m_flexNodeIndex;
}

void CoarseSunSensor::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexCoarseSunSensor(this);
}

Spacecraft* CoarseSunSensor::parentItem() const
{
    if (m_Spacecraft)
        return m_Spacecraft;
    else
        return nullptr;
}

int CoarseSunSensor::index() const
{
    if (m_Spacecraft)
        return m_index;
    return -1;
}

bool operator== (const CoarseSunSensor& css1, const CoarseSunSensor& css2)
{
    return
    css1.m_index == css2.m_index &&
    css1.m_Spacecraft == css2.m_Spacecraft &&
    css1.m_sampleTime == css2.m_sampleTime &&
    css1.m_body == css2.m_body &&
    css1.m_bodyIndex == css2.m_bodyIndex &&
    css1.m_axisInBodyFrame == css2.m_axisInBodyFrame &&
    css1.m_halfConeAngle == css2.m_halfConeAngle &&
    css1.m_scaleFactor == css2.m_scaleFactor &&
    css1.m_quantization == css2.m_quantization &&
    css1.m_flexNodeIndex == css2.m_flexNodeIndex &&
    css1.m_includedInCalculation == css2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const CoarseSunSensor& css)
{
    dataStream << css.m_includedInCalculation
               << css.m_sampleTime
               << css.m_bodyIndex
               << css.m_axisInBodyFrame
               << css.m_halfConeAngle
               << css.m_scaleFactor
               << css.m_quantization
               << css.m_flexNodeIndex;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, CoarseSunSensor& css)
{
    dataStream >> css.m_includedInCalculation
            >> css.m_sampleTime
            >> css.m_bodyIndex
            >> css.m_axisInBodyFrame
            >> css.m_halfConeAngle
            >> css.m_scaleFactor
            >> css.m_quantization
            >> css.m_flexNodeIndex;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const CoarseSunSensor& css)
{
    dataStream << css.name()
               << css.m_includedInCalculation
               << css.m_sampleTime
               << css.m_bodyIndex
               << css.m_axisInBodyFrame
               << css.m_halfConeAngle
               << css.m_scaleFactor
               << css.m_quantization
               << css.m_flexNodeIndex;

    return dataStream;
}
/****************** FSS ************************/
FineSunSensor::FineSunSensor(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft){
        m_Spacecraft = parentSpacecraft;
    }
}
FineSunSensor::~FineSunSensor(){}
FineSunSensor::FineSunSensor(const FineSunSensor& FSS) : Qt42BaseClass(FSS)
{
    m_index = FSS.m_index;
    m_Spacecraft = FSS.m_Spacecraft;
    m_sampleTime = FSS.m_sampleTime;
    m_mountingAngles = FSS.m_mountingAngles;
    m_mountingAnglesSeq = FSS.m_mountingAnglesSeq;
    m_FOV_Size = FSS.m_FOV_Size;
    m_noiseEquivalentAngle = FSS.m_noiseEquivalentAngle;
    m_quantization = FSS.m_quantization;
    m_flexNodeIndex = FSS.m_flexNodeIndex;
    m_includedInCalculation = FSS.m_includedInCalculation;
}

void FineSunSensor::operator=(const FineSunSensor &FSS)
{
    m_index = FSS.m_index;
    m_Spacecraft = FSS.m_Spacecraft;
    m_sampleTime = FSS.m_sampleTime;
    m_mountingAngles = FSS.m_mountingAngles;
    m_mountingAnglesSeq = FSS.m_mountingAnglesSeq;
    m_FOV_Size = FSS.m_FOV_Size;
    m_noiseEquivalentAngle = FSS.m_noiseEquivalentAngle;
    m_quantization = FSS.m_quantization;
    m_flexNodeIndex = FSS.m_flexNodeIndex;
    m_includedInCalculation = FSS.m_includedInCalculation;
}

void FineSunSensor::edit(const double &sampleTime, const QVector<double> &mountingAngles,
                         const QString &mountingAnglesSeq, const QVector<double> &FOV_Size,
                         const double &noiseEquivalentAngle, const double &quantization,
                         const unsigned int &flexNodeIndex,
                         const bool& included)
{
    m_sampleTime = sampleTime;
    m_mountingAngles = mountingAngles;
    m_mountingAnglesSeq = mountingAnglesSeq;
    m_FOV_Size = FOV_Size;
    m_noiseEquivalentAngle = noiseEquivalentAngle;
    m_quantization = quantization;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
}

void FineSunSensor::duplicate(const FineSunSensor &fss)
{
    m_includedInCalculation = fss.m_includedInCalculation;
    m_sampleTime = fss.m_sampleTime;
    m_mountingAngles = fss.m_mountingAngles;
    m_mountingAnglesSeq = fss.m_mountingAnglesSeq;
    m_FOV_Size = fss.m_FOV_Size;
    m_noiseEquivalentAngle = fss.m_noiseEquivalentAngle;
    m_quantization = fss.m_quantization;
    m_flexNodeIndex = fss.m_flexNodeIndex;
}

int FineSunSensor::index() const
{
    if (m_Spacecraft)
        return m_index;
    return -1;
}

Spacecraft* FineSunSensor::parentItem() const
{
    if (m_Spacecraft)
        return m_Spacecraft;
    return nullptr;
}

void FineSunSensor::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexFineSunSensor(this);
}

bool operator== (const FineSunSensor& fss1, const FineSunSensor& fss2)
{
    return
            fss1.m_index == fss2.m_index &&
            fss1.m_Spacecraft == fss2.m_Spacecraft &&
            fss1.m_sampleTime == fss2.m_sampleTime &&
            fss1.m_mountingAngles == fss2.m_mountingAngles &&
            fss1.m_mountingAnglesSeq == fss2.m_mountingAnglesSeq &&
            fss1.m_FOV_Size == fss2.m_FOV_Size &&
            fss1.m_noiseEquivalentAngle == fss2.m_noiseEquivalentAngle &&
            fss1.m_quantization == fss2.m_quantization &&
            fss1.m_flexNodeIndex == fss2.m_flexNodeIndex &&
            fss1.m_includedInCalculation == fss2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const FineSunSensor& fss)
{
    dataStream << fss.m_includedInCalculation
               << fss.m_sampleTime
               << fss.m_mountingAngles
               << fss.m_mountingAnglesSeq
               << fss.m_FOV_Size
               << fss.m_noiseEquivalentAngle
               << fss.m_quantization
               << fss.m_flexNodeIndex;
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, FineSunSensor& fss)
{
    dataStream >> fss.m_includedInCalculation
            >> fss.m_sampleTime
            >> fss.m_mountingAngles
            >> fss.m_mountingAnglesSeq
            >> fss.m_FOV_Size
            >> fss.m_noiseEquivalentAngle
            >> fss.m_quantization
            >> fss.m_flexNodeIndex;
    return dataStream;
}


QDebug operator<< (QDebug dataStream, const FineSunSensor& fss)
{
    dataStream << fss.name()
               << fss.m_includedInCalculation
               << fss.m_sampleTime
               << fss.m_mountingAngles
               << fss.m_mountingAnglesSeq
               << fss.m_FOV_Size
               << fss.m_noiseEquivalentAngle
               << fss.m_quantization
               << fss.m_flexNodeIndex;
    return dataStream;
}

/************ StarTracker *************************/
StarTracker::StarTracker(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft){
        m_Spacecraft = parentSpacecraft;
    }
}
StarTracker::~StarTracker(){}
StarTracker::StarTracker(const StarTracker& ST) : Qt42BaseClass(ST)
{
    m_index = ST.m_index;
    m_Spacecraft = ST.m_Spacecraft;
    m_sampleTime = ST.m_sampleTime;
    m_mountingAngles = ST.m_mountingAngles;
    m_mountingAnglesSeq = ST.m_mountingAnglesSeq;
    m_FOV_Size = ST.m_FOV_Size;
    m_SunMoonEarthExclusionAngles = ST.m_SunMoonEarthExclusionAngles;
    m_noiseEquivAng = ST.m_noiseEquivAng;
    m_flexNodeIndex = ST.m_flexNodeIndex;
    m_includedInCalculation = ST.m_includedInCalculation;
}

void StarTracker::operator=(const StarTracker &ST)
{
    m_index = ST.m_index;
    m_Spacecraft = ST.m_Spacecraft;
    m_sampleTime = ST.m_sampleTime;
    m_mountingAngles = ST.m_mountingAngles;
    m_mountingAnglesSeq = ST.m_mountingAnglesSeq;
    m_FOV_Size = ST.m_FOV_Size;
    m_SunMoonEarthExclusionAngles = ST.m_SunMoonEarthExclusionAngles;
    m_noiseEquivAng = ST.m_noiseEquivAng;
    m_flexNodeIndex = ST.m_flexNodeIndex;
    m_includedInCalculation = ST.m_includedInCalculation;
}

void StarTracker::edit(const double &sampleTime, const QVector<double> &mountingAngles,
                       const QString &mountingAnglesSeq,
                       const QVector<double> &FOV_Size,
                       const QVector<double> &SunMoonEarthExclusionAngles,
                       const QVector<double> &noiseEquivAng,
                       const unsigned int &flexNodeIndex,
                       const bool& included)
{
    m_sampleTime = sampleTime;
    m_mountingAngles = mountingAngles;
    m_mountingAnglesSeq = mountingAnglesSeq;
    m_FOV_Size = FOV_Size;
    m_SunMoonEarthExclusionAngles = SunMoonEarthExclusionAngles;
    m_noiseEquivAng = noiseEquivAng;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
}

void StarTracker::duplicate(const StarTracker &st)
{
    m_includedInCalculation = st.m_includedInCalculation;
    m_sampleTime = st.m_sampleTime;
    m_mountingAngles = st.m_mountingAngles;
    m_mountingAnglesSeq = st.m_mountingAnglesSeq.trimmed();
    m_FOV_Size = st.m_FOV_Size;
    m_SunMoonEarthExclusionAngles = st.m_SunMoonEarthExclusionAngles;
    m_noiseEquivAng = st.m_noiseEquivAng;
    m_flexNodeIndex = st.m_flexNodeIndex;
}

int StarTracker::index() const
{
    if (m_Spacecraft)
        return m_index;
    else
        return -1;
}

Spacecraft* StarTracker::parentItem() const
{
    if (m_Spacecraft)
        return m_Spacecraft;
    else {
        return nullptr;
    }
}

void StarTracker::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexStarTracker(this);
}

bool operator== (const StarTracker& st1, const StarTracker& st2)
{
    return
            st1.m_index == st2.m_index &&
            st1.m_Spacecraft == st2.m_Spacecraft &&
            st1.m_sampleTime == st2.m_sampleTime &&
            st1.m_mountingAngles == st2.m_mountingAngles &&
            st1.m_mountingAnglesSeq == st2.m_mountingAnglesSeq &&
            st1.m_FOV_Size == st2.m_FOV_Size &&
            st1.m_SunMoonEarthExclusionAngles == st2.m_SunMoonEarthExclusionAngles &&
            st1.m_noiseEquivAng == st2.m_noiseEquivAng &&
            st1.m_flexNodeIndex == st2.m_flexNodeIndex &&
            st1.m_includedInCalculation == st2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const StarTracker& st)
{
    dataStream << st.m_includedInCalculation
               << st.m_sampleTime
               << st.m_mountingAngles
               << st.m_mountingAnglesSeq
               << st.m_FOV_Size
               << st.m_SunMoonEarthExclusionAngles
               << st.m_noiseEquivAng
               << st.m_flexNodeIndex;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, StarTracker& st)
{
    dataStream >> st.m_includedInCalculation
       >> st.m_sampleTime
       >> st.m_mountingAngles
       >> st.m_mountingAnglesSeq
       >> st.m_FOV_Size
       >> st.m_SunMoonEarthExclusionAngles
       >> st.m_noiseEquivAng
       >> st.m_flexNodeIndex;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const StarTracker& st)
{
    dataStream << st.m_includedInCalculation
               << st.m_sampleTime
               << st.m_mountingAngles
               << st.m_mountingAnglesSeq
               << st.m_FOV_Size
               << st.m_SunMoonEarthExclusionAngles
               << st.m_noiseEquivAng
               << st.m_flexNodeIndex;

    return dataStream;
}
/************** GPS Receiver ****************/
GPSReceiver::GPSReceiver(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft){
        m_Spacecraft = parentSpacecraft;
    }
}
GPSReceiver::~GPSReceiver(){}
GPSReceiver::GPSReceiver(const GPSReceiver& GPSR) : Qt42BaseClass(GPSR)
{
    m_index = GPSR.m_index;
    m_Spacecraft = GPSR.m_Spacecraft;
    m_sampleTime = GPSR.m_sampleTime;
    m_posNoise = GPSR.m_posNoise;
    m_velNoise = GPSR.m_velNoise;
    m_timeNoise = GPSR.m_timeNoise;
    m_flexNodeIndex = GPSR.m_flexNodeIndex;
    m_includedInCalculation = GPSR.m_includedInCalculation;
}

void GPSReceiver::operator=(const GPSReceiver &GPSR)
{
    m_index = GPSR.m_index;
    m_Spacecraft = GPSR.m_Spacecraft;
    m_sampleTime = GPSR.m_sampleTime;
    m_posNoise = GPSR.m_posNoise;
    m_velNoise = GPSR.m_velNoise;
    m_timeNoise = GPSR.m_timeNoise;
    m_flexNodeIndex = GPSR.m_flexNodeIndex;
    m_includedInCalculation = GPSR.m_includedInCalculation;
}

void GPSReceiver::edit(const double &sampleTime, const double &posNoise,
                       const double &velNoise, const double &timeNoise,
                       const unsigned int &flexNodeIndex, const bool& included)
{
    m_sampleTime = sampleTime;
    m_posNoise = posNoise;
    m_velNoise = velNoise;
    m_timeNoise = timeNoise;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
}

void GPSReceiver::duplicate(const GPSReceiver &gpsr)
{
    m_includedInCalculation = gpsr.m_includedInCalculation;
    m_sampleTime = gpsr.m_sampleTime;
    m_posNoise = gpsr.m_posNoise;
    m_velNoise = gpsr.m_velNoise;
    m_timeNoise = gpsr.m_timeNoise;
    m_flexNodeIndex = gpsr.m_flexNodeIndex;
}

void GPSReceiver::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexGPSReceiver(this);
}
int GPSReceiver::index() const
{
    if (m_Spacecraft)
        return m_index;
    else
        return -1;
}

Spacecraft* GPSReceiver::parentItem() const
{
    if (m_Spacecraft)
        return m_Spacecraft;
    else {
        return nullptr;
    }
}

bool operator== (const GPSReceiver& gps1, const GPSReceiver& gps2)
{
    return
            gps1.m_index == gps2.m_index &&
            gps1.m_Spacecraft == gps2.m_Spacecraft &&
            gps1.m_sampleTime == gps2.m_sampleTime &&
            gps1.m_posNoise == gps2.m_posNoise &&
            gps1.m_velNoise == gps2.m_velNoise &&
            gps1.m_timeNoise == gps2.m_timeNoise &&
            gps1.m_flexNodeIndex == gps2.m_flexNodeIndex &&
            gps1.m_includedInCalculation == gps2.m_includedInCalculation;
}

QDataStream& operator<< (QDataStream& dataStream, const GPSReceiver& gps)
{
    dataStream << gps.m_includedInCalculation
               << gps.m_sampleTime
               << gps.m_posNoise
               << gps.m_velNoise
               << gps.m_timeNoise
               << gps.m_flexNodeIndex;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, GPSReceiver& gps)
{
    dataStream >> gps.m_includedInCalculation
       >> gps.m_sampleTime
       >> gps.m_posNoise
       >> gps.m_velNoise
       >> gps.m_timeNoise
       >> gps.m_flexNodeIndex;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const GPSReceiver& gps)
{
    dataStream << gps.m_includedInCalculation
               << gps.m_sampleTime
               << gps.m_posNoise
               << gps.m_velNoise
               << gps.m_timeNoise
               << gps.m_flexNodeIndex;

    return dataStream;
}
/**********************Accelerometer ************/
Accelerometer::Accelerometer(Spacecraft* parentSpacecraft)
{
    Qt42BaseClass::changeType(m_type);
    if (parentSpacecraft)
    {
        m_Spacecraft = parentSpacecraft;
    }
}
Accelerometer::~Accelerometer(){}
Accelerometer::Accelerometer(const Accelerometer& ACCL) : Qt42BaseClass(ACCL)
{
    m_index = ACCL.m_index;
    m_Spacecraft = ACCL.m_Spacecraft;
    m_sampleTime = ACCL.m_sampleTime;
    m_posBody0 = ACCL.m_posBody0;
    m_axisInBodyFrame = ACCL.m_axisInBodyFrame;
    m_maxAcceleration = ACCL.m_maxAcceleration;
    m_scaleFactorError = ACCL.m_scaleFactorError;
    m_quantization = ACCL.m_quantization;
    m_randomWalk = ACCL.m_randomWalk;
    m_biasStability = ACCL.m_biasStability;
    m_timeSpan = ACCL.m_timeSpan;
    m_DVNoise = ACCL.m_DVNoise;
    m_initialBias = ACCL.m_initialBias;
    m_includedInCalculation = ACCL.m_includedInCalculation;
    m_flexNodeIndex = ACCL.m_flexNodeIndex;
}

void Accelerometer::operator=(const Accelerometer &ACCL)
{
    m_index = ACCL.m_index;
    m_Spacecraft = ACCL.m_Spacecraft;
    m_sampleTime = ACCL.m_sampleTime;
    m_posBody0 = ACCL.m_posBody0;
    m_axisInBodyFrame = ACCL.m_axisInBodyFrame;
    m_maxAcceleration = ACCL.m_maxAcceleration;
    m_scaleFactorError = ACCL.m_scaleFactorError;
    m_quantization = ACCL.m_quantization;
    m_randomWalk = ACCL.m_randomWalk;
    m_biasStability = ACCL.m_biasStability;
    m_timeSpan = ACCL.m_timeSpan;
    m_DVNoise = ACCL.m_DVNoise;
    m_initialBias = ACCL.m_initialBias;
    m_includedInCalculation = ACCL.m_includedInCalculation;
    m_flexNodeIndex = ACCL.m_flexNodeIndex;
}

void Accelerometer::edit(const double& sampleTime, const QVector<double>& posBody0,
                         const QVector <double>& axisInBodyFrame,
                         const double& maxAcceleration,
                         const double& scaleFactorError,
                         const double& quantization, const double& randomWalk,
                         const double& biasStability, const double& timeSpan,
                         const double& DVNoise,
                         const double& initialBias, const unsigned int& flexNodeIndex,
                         const bool& included)
{
    m_sampleTime = sampleTime;
    m_posBody0 = posBody0;
    m_axisInBodyFrame = axisInBodyFrame;
    m_maxAcceleration = maxAcceleration;
    m_scaleFactorError = scaleFactorError;
    m_quantization = quantization;
    m_randomWalk = randomWalk;
    m_biasStability = biasStability;
    m_timeSpan = timeSpan;
    m_DVNoise = DVNoise;
    m_initialBias = initialBias;
    m_flexNodeIndex = flexNodeIndex;
    m_includedInCalculation = included;
}

void Accelerometer::duplicate(const Accelerometer &accl)
{
    m_includedInCalculation = accl.m_includedInCalculation;
    m_sampleTime = accl.m_sampleTime;
    m_posBody0 = accl.m_posBody0;
    m_axisInBodyFrame = accl.m_axisInBodyFrame;
    m_maxAcceleration = accl.m_maxAcceleration;
    m_scaleFactorError = accl.m_scaleFactorError;
    m_quantization = accl.m_quantization;
    m_randomWalk = accl.m_randomWalk;
    m_biasStability = accl.m_biasStability;
    m_timeSpan = accl.m_timeSpan;
    m_DVNoise = accl.m_DVNoise;
    m_initialBias = accl.m_initialBias;
    m_flexNodeIndex = accl.m_flexNodeIndex;
}


void Accelerometer::updateIndex()
{
    if (m_Spacecraft)
        m_index = m_Spacecraft->indexAccelerometer(this);
}

Spacecraft* Accelerometer::parentItem() const
{
    if (m_Spacecraft)
        return m_Spacecraft;
    return nullptr;
}

int Accelerometer::index() const
{
    if (m_Spacecraft)
        return m_index;
    else
        return -1;
}

bool operator== (const Accelerometer& accl1, const Accelerometer& accl2)
{
   return
           accl1.m_index == accl2.m_index &&
           accl1.m_Spacecraft == accl2.m_Spacecraft &&
           accl1.m_sampleTime == accl2.m_sampleTime &&
           accl1.m_posBody0 == accl2.m_posBody0 &&
           accl1.m_axisInBodyFrame == accl2.m_axisInBodyFrame &&
           accl1.m_maxAcceleration == accl2.m_maxAcceleration &&
           accl1.m_scaleFactorError == accl2.m_scaleFactorError &&
           accl1.m_quantization == accl2.m_quantization &&
           accl1.m_randomWalk == accl2.m_randomWalk &&
           accl1.m_biasStability == accl2.m_biasStability &&
           accl1.m_timeSpan == accl2.m_timeSpan &&
           accl1.m_DVNoise == accl2.m_DVNoise &&
           accl1.m_initialBias == accl2.m_initialBias &&
           accl1.m_includedInCalculation == accl2.m_includedInCalculation &&
           accl1.m_flexNodeIndex == accl2.m_flexNodeIndex;
}

QDataStream& operator<< (QDataStream& dataStream, const Accelerometer& accl)
{
    dataStream << accl.m_includedInCalculation
               << accl.m_sampleTime
               << accl.m_posBody0
               << accl.m_axisInBodyFrame
               << accl.m_maxAcceleration
               << accl.m_scaleFactorError
               << accl.m_quantization
               << accl.m_randomWalk
               << accl.m_biasStability
               << accl.m_timeSpan
               << accl.m_DVNoise
               << accl.m_initialBias
               << accl.m_flexNodeIndex;

    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, Accelerometer& accl)
{

    dataStream >> accl.m_includedInCalculation
            >> accl.m_sampleTime
            >> accl.m_posBody0
            >> accl.m_axisInBodyFrame
            >> accl.m_maxAcceleration
            >> accl.m_scaleFactorError
            >> accl.m_quantization
            >> accl.m_randomWalk
            >> accl.m_biasStability
            >> accl.m_timeSpan
            >> accl.m_DVNoise
            >> accl.m_initialBias
            >> accl.m_flexNodeIndex;

    return dataStream;
}

QDebug operator<< (QDebug dataStream, const Accelerometer& accl)
{
    dataStream << accl.name()
               << accl.m_includedInCalculation
               << accl.m_sampleTime
               << accl.m_posBody0
               << accl.m_axisInBodyFrame
               << accl.m_maxAcceleration
               << accl.m_scaleFactorError
               << accl.m_quantization
               << accl.m_randomWalk
               << accl.m_biasStability
               << accl.m_timeSpan
               << accl.m_DVNoise
               << accl.m_initialBias
               << accl.m_flexNodeIndex;

    return dataStream;
}
