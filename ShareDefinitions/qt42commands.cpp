#include "ShareHeaders/qt42commands.h"
#include "DataHeaders/qt42baseclass.h"
#include "DataHeaders/spacecraft.h"
#include "DataHeaders/spacecraftcomponents.h"
#include <QDebug>
/****   RemoveCommand ****/

RemoveCommand::RemoveCommand(QAbstractItemModel* model,
                             QModelIndex index,
                             QUndoCommand* parent): QUndoCommand(parent)
{
    m_model = static_cast<Qt42Model*>(model);
    m_index = index;
    m_parent = index.parent();
    m_row = index.row();
    m_column = index.column();
    convertToType(index);
}

RemoveCommand::~RemoveCommand()
{

}

void RemoveCommand::convertToType(const QModelIndex& index)
{
    if (index.data().canConvert<SpacecraftBody>())
    {
        m_SCcToRemove = static_cast<SpacecraftBody*>(index.internalPointer());
    }
    else if (index.data().canConvert<Joint>())
    {
        m_SCcToRemove = static_cast<Joint*>(index.internalPointer());
    }
    else if (index.data().canConvert<Wheel>())
    {
        m_SCcToRemove = static_cast<Wheel*>(index.internalPointer());
    }
    else if (index.data().canConvert<MagTorquer>())
    {
        m_SCcToRemove = static_cast<MagTorquer*>(index.internalPointer());
    }
    else if (index.data().canConvert<Thruster>())
    {
        m_SCcToRemove = static_cast<Thruster*>(index.internalPointer());
    }
    else if (index.data().canConvert<GyroAxis>())
    {
        m_SCcToRemove = static_cast<GyroAxis*>(index.internalPointer());
    }
    else if (index.data().canConvert<MagnetometerAxis>())
    {
        m_SCcToRemove = static_cast<MagnetometerAxis*>(index.internalPointer());
    }
    else if (index.data().canConvert<CoarseSunSensor>())
    {
        m_SCcToRemove = static_cast<CoarseSunSensor*>(index.internalPointer());
    }
    else if (index.data().canConvert<FineSunSensor>())
    {
        m_SCcToRemove = static_cast<FineSunSensor*>(index.internalPointer());
    }
    else if (index.data().canConvert<StarTracker>())
    {
        m_SCcToRemove = static_cast<StarTracker*>(index.internalPointer());
    }
    else if (index.data().canConvert<GPSReceiver>())
    {
        m_SCcToRemove = static_cast<GPSReceiver*>(index.internalPointer());
    }
    else if (index.data().canConvert<Accelerometer>())
    {
        m_SCcToRemove = static_cast<Accelerometer*>(index.internalPointer());
    }
    m_type = m_SCcToRemove->type();
}

void RemoveCommand::undo()
{
    m_model->insertItem(m_parent, m_type, m_row, m_column, m_SCcToRemove);
    setObsolete(true);
}

void RemoveCommand::redo()
{
    if (m_index.isValid())
    {
        int row = m_index.row();
        int column = m_index.column();
        QModelIndex parent = m_index.parent();
        m_model->removeItem(row, column, parent);
        m_index = QModelIndex();
        //Spacecraft sc = m_parent.data().value<Spacecraft>();
    }
    else
    {
        qDebug() << "index is invalid in command.";
    }
}



/**** CreateCommand  ****/

CreateCommand::CreateCommand(objectType type, QAbstractItemModel* model,
                             const QModelIndex& parentIndex,
                             QUndoCommand* parent) : QUndoCommand(parent)
{
    m_model = static_cast<Qt42Model*>(model);
    m_parentIndex = parentIndex;
    m_type = type;
    convertToType();
}

CreateCommand::~CreateCommand()
{

}

void CreateCommand::undo()
{
    Spacecraft SC = m_parentIndex.data().value<Spacecraft>();
    if (m_type == SPACECRAFTBODY)
        m_model->removeItem(SC.rowSPACECRAFTBODY(), SC.numberOfBodies()-1 , m_parentIndex);
    else if (m_type == JOINT)
        m_model->removeItem(SC.rowJOINT(), SC.numberOfJoints()-1 , m_parentIndex);
    else if (m_type == WHEEL)
        m_model->removeItem(SC.rowWHEEL(), SC.numberOfWheels()-1, m_parentIndex);
    else if (m_type == MAGTORQUER)
        m_model->removeItem(SC.rowMAGTORQUER(), SC.numberOfMagTorquer()-1, m_parentIndex);
    else if (m_type == THRUSTER)
        m_model->removeItem(SC.rowTHRUSTER(), SC.numberOfThruster()-1, m_parentIndex);
    else if (m_type == GYROAXIS)
        m_model->removeItem(SC.rowGYROAXIS(), SC.numberOfGyroAxis()-1, m_parentIndex);
    else if (m_type == MAGNETOMETERAXIS)
        m_model->removeItem(SC.rowMAGNETOMETERAXIS(), SC.numberOfMMA()-1, m_parentIndex);
    else if (m_type == COARSESUNSENSOR)
        m_model->removeItem(SC.rowCOARSESUNSENSOR(), SC.numberOfCoarseSunSensor()-1, m_parentIndex);
    else if (m_type == FINESUNSENSOR)
        m_model->removeItem(SC.rowFINESUNSENSOR(), SC.numberOfFineSunSensor()-1, m_parentIndex);
    else if (m_type == GPSRECEIVER)
        m_model->removeItem(SC.rowGPSRECEIVER(), SC.numberOfGPSReceiver()-1, m_parentIndex);
    else if (m_type == STARTRACKER)
        m_model->removeItem(SC.rowSTARTRACKER(), SC.numberOfStarTracker()-1, m_parentIndex);
    else if (m_type == ACCELEROMETER)
        m_model->removeItem(SC.rowACCELEROMETER(), SC.numberOfAccelerometer()-1, m_parentIndex);

    setObsolete(true);
}

void CreateCommand::redo()
{
    if (!m_parentIndex.isValid())
        return;
    Spacecraft SC = m_parentIndex.data().value<Spacecraft>();
    m_model->createItem(m_parentIndex, m_type);
    convertToType();
    if (m_type == SPACECRAFTBODY)
        m_SCcToCreate = SC.body(SC.numberOfBodies()-1);
    else if (m_type == JOINT)
        m_SCcToCreate = SC.joint(SC.numberOfJoints()-1);
    else if (m_type == WHEEL)
        m_SCcToCreate = SC.wheel(SC.numberOfWheels()-1);
    else if (m_type == MAGTORQUER)
        m_SCcToCreate = SC.magTorque(SC.numberOfMagTorquer()-1);
    else if (m_type == THRUSTER)
        m_SCcToCreate = SC.thruster(SC.numberOfThruster()-1);
    else if (m_type == GYROAXIS)
        m_SCcToCreate = SC.gyroAxis(SC.numberOfGyroAxis()-1);
    else if (m_type == MAGNETOMETERAXIS)
        m_SCcToCreate = SC.MMA(SC.numberOfMMA()-1);
    else if (m_type == COARSESUNSENSOR)
        m_SCcToCreate = SC.coarseSunSensor(SC.numberOfCoarseSunSensor()-1);
    else if (m_type == FINESUNSENSOR)
        m_SCcToCreate = SC.fineSunSensor(SC.numberOfFineSunSensor()-1);
    else if (m_type == GPSRECEIVER)
        m_SCcToCreate = SC.gPSReceiver(SC.numberOfGPSReceiver()-1);
    else if (m_type == STARTRACKER)
        m_SCcToCreate = SC.starTracker(SC.numberOfStarTracker()-1);
    else if (m_type == ACCELEROMETER)
        m_SCcToCreate = SC.accelerometer(SC.numberOfAccelerometer()-1);
}

void CreateCommand::convertToType()
{
    if (m_type == SPACECRAFTBODY)
        m_SCcToCreate = new SpacecraftBody;
    else if (m_type == JOINT)
        m_SCcToCreate = new Joint;
    else if (m_type == WHEEL)
        m_SCcToCreate = new Wheel;
    else if (m_type == MAGTORQUER)
        m_SCcToCreate = new MagTorquer;
    else if (m_type == THRUSTER)
        m_SCcToCreate = new Thruster;
    else if (m_type == GYROAXIS)
        m_SCcToCreate = new GyroAxis;
    else if (m_type == MAGNETOMETERAXIS)
        m_SCcToCreate = new MagnetometerAxis;
    else if (m_type == COARSESUNSENSOR)
        m_SCcToCreate = new CoarseSunSensor;
    else if (m_type == FINESUNSENSOR)
        m_SCcToCreate = new FineSunSensor;
    else if (m_type == GPSRECEIVER)
        m_SCcToCreate = new GPSReceiver;
    else if (m_type == STARTRACKER)
        m_SCcToCreate = new StarTracker;
    else if (m_type == ACCELEROMETER)
        m_SCcToCreate = new Accelerometer;
}


/**** EditCommand ****/

EditCommand::EditCommand(QAbstractItemModel* model, const QModelIndex& index,
                         QVariant data, QUndoCommand* parent) : QUndoCommand(parent)
{
    m_model = static_cast<Qt42Model*>(model);
    m_index = index;
    //m_Qt42BC = static_cast<Qt42BaseClass*>(index.internalPointer());
    //m_type = m_Qt42BC->type();
    m_dataUndo = index.data();
    m_dataRedo = data;
}

EditCommand::~EditCommand()
{

}

void EditCommand::undo()
{
    if (m_index.isValid()){
        m_model->setData(m_index, m_dataUndo, Qt::EditRole);
        setObsolete(true);
    }
}

void EditCommand::redo()
{
    if (m_index.isValid())
        m_model->setData(m_index, m_dataRedo, Qt::EditRole);

}

/*** ResetCommand ***/

ResetCommand::ResetCommand(QAbstractItemModel* model, const QModelIndex& index,
                           QUndoCommand* parent) : QUndoCommand(parent)
{
    m_model = static_cast<Qt42Model*>(model);
    m_index = index;
    m_dataUndo = index.data();
}

ResetCommand::~ResetCommand()
{

}

void ResetCommand::undo()
{
    m_model->setData(m_index, m_dataUndo, Qt::EditRole);
    setObsolete(true);
}

void ResetCommand::redo()
{
    QVariant resetData = QVariant();
    if (m_index.data().canConvert<Spacecraft>())
    {
        Spacecraft resetSC = m_index.data().value<Spacecraft>();
        resetSC.reset();
        resetData.setValue(resetSC);
        m_model->setData(m_index, resetData, Qt::EditRole);
    }

}

