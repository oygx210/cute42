#include "MVDheaders/qt42delegate.h"
#include "DataHeaders/qt42baseclass.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "MVDheaders/qt42model.h"
#include "DataHeaders/missionholder.h"
#include "DataHeaders/mission.h"
#include "DataHeaders/spacecraft.h"
#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/spacecraftcomponents.h"
#include "DataHeaders/orbittype.h"
#include "DataHeaders/inpsimterms.h"

#include "WidgetHeaders/lineeditor42.h"

#include <QLineEdit>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QSize>
#include <QPushButton>
#include <QMessageBox>
#include <QIcon>
#include <QPen>
#include <QMouseEvent>
#include <QModelIndex>

#include <QLabel>

Qt42Delegate::Qt42Delegate(QObject *parent): QStyledItemDelegate (parent)
{
    connect(this, &Qt42Delegate::editSpacecraft, this, &Qt42Delegate::printOutName);
}

Qt42Delegate::~Qt42Delegate()
{
}

void Qt42Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if (canConvertToCustomType(index.data())){
        if (option.state & QStyle::State_Selected)
        {
           painter->fillRect(option.rect, option.palette.highlight());
        }

        Qt42BaseClass* Qt42BC = static_cast<Qt42BaseClass*>(index.internalPointer());
        if (!Qt42BC->includedInCalculation())
        {
            QPen pen(Qt::gray, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            painter->setPen(pen);
        }
        else
        {
            QPen pen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            painter->setPen(pen);

        }

        if (!canConvertToCustomTypeSCcomponents(index.data()))
        {
            painter->drawText(option.rect, Qt::AlignLeft, nameByType(index));
        }
        else
        {
            painter->drawText(option.rect, Qt::AlignLeft, nameByType(index));
        }
    }

    else {
        qDebug() << "can't paint";
        painter->drawText(option.rect, Qt::AlignLeft, "can't paint");
    }
}


QWidget* Qt42Delegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QLineEdit* lineEditor = new QLineEdit(parent);
    lineEditor->setReadOnly(true);
    //lineEditor->setContextMenuPolicy(Qt::CustomContextMenu);
    return lineEditor;
}

void Qt42Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);
    if (canConvertToCustomType(index.data())){
        lineEditor->setText(nameByType(index));
    }
    else {
        lineEditor->setText("Can't convert.");
        qDebug() << "can't setData";
    }

}

void Qt42Delegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);
    setModelDataByType(lineEditor, model, index);
}

void Qt42Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                        const QModelIndex& /*index*/) const
{
    editor->setGeometry(option.rect);
}

QString Qt42Delegate::nameByType(const QModelIndex& index) const{
    if (index.data().canConvert<MissionHolder>())
        return QString();

    else if (index.data().canConvert<Mission>()){
        Mission mission = index.data().value<Mission>();
        return mission.name();
    }

    else if (index.data().canConvert<SpacecraftHeader>()){
        SpacecraftHeader SCH = index.data().value<SpacecraftHeader>();
        return SCH.name();
    }

    else if (index.data().canConvert<Spacecraft>()){
        Spacecraft SC = index.data().value<Spacecraft>();
        return SC.name();
    }

    else if (index.data().canConvert<SpacecraftBody>()){
        SpacecraftBody SCB = index.data().value<SpacecraftBody>();
        return SCB.name();
    }

    else if (index.data().canConvert<Joint>()){
        Joint JNT = index.data().value<Joint>();
        return JNT.name();
    }

    else if (index.data().canConvert<Wheel>()){
        Wheel WHL = index.data().value<Wheel>();
        return WHL.name();
    }

    else if (index.data().canConvert<MagTorquer>()){
        MagTorquer MAGT = index.data().value<MagTorquer>();
        return MAGT.name();
    }

    else if (index.data().canConvert<Thruster>()){
        Thruster THR = index.data().value<Thruster>();
        return THR.name();
    }

    else if (index.data().canConvert<GyroAxis>()){
        GyroAxis GYRO = index.data().value<GyroAxis>();
        return GYRO.name();
    }

    else if (index.data().canConvert<MagnetometerAxis>()){
        MagnetometerAxis MMA = index.data().value<MagnetometerAxis>();
        return MMA.name();
    }

    else if (index.data().canConvert<CoarseSunSensor>()){
        CoarseSunSensor CSS = index.data().value<CoarseSunSensor>();
        return CSS.name();
    }

    else if (index.data().canConvert<FineSunSensor>()){
        FineSunSensor FSS = index.data().value<FineSunSensor>();
        return FSS.name();
    }

    else if (index.data().canConvert<StarTracker>()){
        StarTracker ST = index.data().value<StarTracker>();
        return ST.name();
    }

    else if (index.data().canConvert<GPSReceiver>()){
        GPSReceiver GPSR = index.data().value<GPSReceiver>();
        return GPSR.name();
    }

    else if (index.data().canConvert<Accelerometer>()){
        Accelerometer ACCL = index.data().value<Accelerometer>();
        return ACCL.name();
    }

    else if (index.data().canConvert<OrbitHeader>()){
        OrbitHeader oh = index.data().value<OrbitHeader>();
        return oh.name();
    }

    else if (index.data().canConvert<Orbit>()){
        Orbit orbit = index.data().value<Orbit>();
        return orbit.name();
    }

    else if (index.data().canConvert<InpSimHeader>()){
        InpSimHeader ish = index.data().value<InpSimHeader>();
        return ish.name();
    }

    else if (index.data().canConvert<InpSimSimulationControl>()){
        InpSimSimulationControl ishc = index.data().value<InpSimSimulationControl>();
        return ishc.name();
    }
    else if (index.data().canConvert<InpSimOrbitSCSet>()){
        InpSimOrbitSCSet isosc = index.data().value<InpSimOrbitSCSet>();
        return isosc.name();
    }

    else if (index.data().canConvert<InpSimEnvironment>()){
        InpSimEnvironment ise = index.data().value<InpSimEnvironment>();
        return ise.name();
    }
    else if (index.data().canConvert<InpSimCelestialBody>()){
        InpSimCelestialBody isc = index.data().value<InpSimCelestialBody>();
        return isc.name();
    }
    else if (index.data().canConvert<InpSimLagrangePointSystem>()){
        InpSimLagrangePointSystem isl = index.data().value<InpSimLagrangePointSystem>();
        return isl.name();
    }
    else if (index.data().canConvert<InpSimGroundStation>()){
        InpSimGroundStation isg = index.data().value<InpSimGroundStation>();
        return isg.name();
    }
    else if (index.data().canConvert<FOVHeader>()){
        FOVHeader fovh = index.data().value<FOVHeader>();
        return fovh.name();
    }

    else if (index.data().canConvert<InpIPCHeader>()){
        InpIPCHeader inpipch = index.data().value<InpIPCHeader>();
        return inpipch.name();
    }

    else if (index.data().canConvert<GraphicsHeader>()){
        GraphicsHeader gh = index.data().value<GraphicsHeader>();
        return gh.name();
    }

    else if (index.data().canConvert<InpTDRs>()){
        InpTDRs inptdrs = index.data().value<InpTDRs>();
        return inptdrs.name();
    }

    else if (index.data().canConvert<RegionHeader>()){
        RegionHeader rgnh = index.data().value<RegionHeader>();
        return rgnh.name();
    }
    else {
        return QString();
    }
}

bool Qt42Delegate::canConvertToCustomType(const QVariant &data) const
{
    return  data.canConvert<MissionHolder>() ||
            data.canConvert<Mission>() ||
            data.canConvert<SpacecraftHeader>() ||
            data.canConvert<Spacecraft>() ||
            data.canConvert<SpacecraftBody>() ||
            data.canConvert<Joint>() ||
            data.canConvert<Wheel>() ||
            data.canConvert<MagTorquer>() ||
            data.canConvert<Thruster>() ||
            data.canConvert<GyroAxis>() ||
            data.canConvert<MagnetometerAxis>() ||
            data.canConvert<CoarseSunSensor>() ||
            data.canConvert<FineSunSensor>() ||
            data.canConvert<StarTracker>() ||
            data.canConvert<GPSReceiver>()   ||
            data.canConvert<Accelerometer>() ||
            data.canConvert<OrbitHeader>()   ||
            data.canConvert<Orbit>()         ||
            data.canConvert<InpSimHeader>()   ||
            data.canConvert<InpSimSimulationControl>() ||
            data.canConvert<InpSimOrbitSCSet>() ||
            data.canConvert<InpSimEnvironment>()   ||
            data.canConvert<InpSimCelestialBody>() ||
            data.canConvert<InpSimLagrangePointSystem>() ||
            data.canConvert<InpSimGroundStation>() ||
            data.canConvert<FOVHeader>() ||
            data.canConvert<Inp_IPC>() ||
            data.canConvert<InpIPCHeader>() ||
            data.canConvert<GraphicsHeader>() ||
            data.canConvert<InpTDRs>() ||
            data.canConvert<RegionHeader>();
}

bool Qt42Delegate::canConvertToCustomTypeSCcomponents(const QVariant &data) const
{
    return  data.canConvert<SpacecraftBody>() ||
            data.canConvert<Joint>() ||
            data.canConvert<Wheel>() ||
            data.canConvert<MagTorquer>() ||
            data.canConvert<Thruster>() ||
            data.canConvert<GyroAxis>() ||
            data.canConvert<MagnetometerAxis>() ||
            data.canConvert<CoarseSunSensor>() ||
            data.canConvert<FineSunSensor>() ||
            data.canConvert<StarTracker>() ||
            data.canConvert<GPSReceiver>()   ||
            data.canConvert<Accelerometer>();
}

void Qt42Delegate::CM_CreateSpacecraft(QMouseEvent *event,
                                       QAbstractItemModel *model,
                                       const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QMenu* contextMenuSpacecraftHeader = new QMenu;
    QAction* actionCreateSpacecraft = new QAction(tr("Create Spacecraft"), this);
    connect(actionCreateSpacecraft, &QAction::triggered,
            this, [=](){this->createSpacecraft(model,index);});
    contextMenuSpacecraftHeader->addAction(actionCreateSpacecraft);
    contextMenuSpacecraftHeader->exec(event->globalPosition().toPoint());
    delete contextMenuSpacecraftHeader;
}

void Qt42Delegate::CM_ClickOnSpacecraft(QMouseEvent *event ,
                                        QAbstractItemModel* model ,
                                        const QModelIndex& index)
{
    if (!index.isValid())
        return;
    Spacecraft SC = index.data().value<Spacecraft>();
    QMenu* contextMenuClickOnSpaceCraft = new QMenu;
    QAction* actionSpacecraftTitle  = new QAction(SC.name());
    QAction* actionRemoveSpacecraft = new QAction(tr("Remove"), this);
    QAction* actionRenameSpacecraft = new QAction(tr("Rename"), this);
    contextMenuClickOnSpaceCraft->addAction(actionSpacecraftTitle);
    actionSpacecraftTitle->setDisabled(true);
    contextMenuClickOnSpaceCraft->addSeparator();
    contextMenuClickOnSpaceCraft->addAction(actionRenameSpacecraft);
    contextMenuClickOnSpaceCraft->addAction(actionRemoveSpacecraft);
    connect(actionRenameSpacecraft, &QAction::triggered,
             this, [=](){this->ShowDialogModifiyName(model,index);});
    connect(actionRemoveSpacecraft, &QAction::triggered,
            this, [=](){this->showDialogRemoveClose(model,index);});

    contextMenuClickOnSpaceCraft->exec(event->globalPosition().toPoint());
    delete contextMenuClickOnSpaceCraft;
}

void Qt42Delegate::CM_ClickOnOrbit(QMouseEvent *event,
                                   QAbstractItemModel *model,
                                   const QModelIndex &index)
{
    if (!index.isValid())
        return;
    Orbit O = index.data().value<Orbit>();
    QMenu* contextMenuClickOnOrbit = new QMenu;
    QAction* actionOrbitTitle  = new QAction(O.name());
    QAction* actionRemoveOrbit = new QAction(tr("Remove"), this);
    QAction* actionRenameOrbit = new QAction(tr("Rename"), this);
    contextMenuClickOnOrbit->addAction(actionOrbitTitle);
    actionOrbitTitle->setDisabled(true);
    contextMenuClickOnOrbit->addSeparator();
    contextMenuClickOnOrbit->addAction(actionRenameOrbit);
    contextMenuClickOnOrbit->addAction(actionRemoveOrbit);
    connect(actionRenameOrbit, &QAction::triggered,
             this, [=](){this->ShowDialogModifiyName(model,index);});
    connect(actionRemoveOrbit, &QAction::triggered,
            this, [=](){this->showDialogRemoveClose(model,index);});

    contextMenuClickOnOrbit->exec(event->globalPosition().toPoint());
    delete contextMenuClickOnOrbit;
}

bool Qt42Delegate::createOrbit(QAbstractItemModel *model, const QModelIndex &index)
{
    if (!index.isValid())
        return false;
    if (index.data().canConvert<OrbitHeader>())
    {
        int position = (index.data().value<OrbitHeader>()).numberOfOrbit();
        int rows = 1;
        model->insertRows(position , rows, index);
        emit orbitCreated(model, model->parent(index));
        return true;
    }
    return false;
}

void Qt42Delegate::CM_CreateOrbit(QMouseEvent *event, QAbstractItemModel *model,
                                  const QModelIndex &index)
{
    if (!index.isValid())
        return;
    if (!index.data().canConvert<OrbitHeader>())
        return;
    QMenu* contextMenuOrbitHeader = new QMenu;
    QAction* actionCreateOrbit = new QAction(tr("Create Orbit"), this);
    connect(actionCreateOrbit, &QAction::triggered,
            this, [=](){this->createOrbit(model,index);});
    contextMenuOrbitHeader->addAction(actionCreateOrbit);
    contextMenuOrbitHeader->exec(event->globalPosition().toPoint());
    delete contextMenuOrbitHeader;
}

void Qt42Delegate::CM_ClickOnMission(QMouseEvent *event,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index)
{
    if (!index.isValid())
        return;
    Mission m = index.data().value<Mission>();
    QMenu* contextMenuMission = new QMenu;
    QAction* actionMissionTitle = new QAction(m.name(), this);
    QAction* actionRenameMission = new QAction(tr("Rename"), this);
    QAction* actionRemoveMission = new QAction(tr("Close"), this);
    connect(actionRenameMission, &QAction::triggered,
            this, [=](){this->ShowDialogModifiyName(model,index);});
    connect(actionRemoveMission, &QAction::triggered,
            this, [=](){this->showDialogRemoveClose(model, index);});
    contextMenuMission->addAction(actionMissionTitle);
    actionMissionTitle->setDisabled(true);
    contextMenuMission->addSeparator();
    contextMenuMission->addAction(actionRenameMission);
    contextMenuMission->addAction(actionRemoveMission);
    contextMenuMission->exec((event->globalPosition().toPoint()));
    delete contextMenuMission;

}


bool Qt42Delegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index)
{
    QMouseEvent* mouseEvent = nullptr;
    if (event->type() == QEvent::MouseButtonPress)
    {
        m_indexSelected = index;
        mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button()==Qt::RightButton){
            if (index.data().canConvert<Mission>())
                CM_ClickOnMission(mouseEvent, model, index);
            else if (index.data().canConvert<SpacecraftHeader>())
                CM_CreateSpacecraft(mouseEvent, model, index);
            else if(index.data().canConvert<Spacecraft>())
                CM_ClickOnSpacecraft(mouseEvent, model, index);
            else if(index.data().canConvert<OrbitHeader>())
                CM_CreateOrbit(mouseEvent, model, index);
            else if(index.data().canConvert<Orbit>())
                CM_ClickOnOrbit(mouseEvent, model, index);
            /*else if (canConvertToCustomTypeSCcomponents(index.data()))
                CM_ClickOnSCcomponents(mouseEvent, model, index);*/

            //emit passInfoModelandIndex(model, index);
        }

    }
    else if (event->type() == QEvent::MouseButtonDblClick)
    {
        m_indexSelected = index;
        if (index.data().canConvert<Mission>())
            emit missionSelected(model,index);
        else if (index.data().canConvert<Spacecraft>())
            emit spacecraftSelected(model,index);
        else if (index.data().canConvert<Orbit>())
            emit orbitSelected(model,index);
        else if (index.data().canConvert<InpSimSimulationControl>())
            emit InpSimParameterSelected(model,index);
        else if (index.data().canConvert<InpSimOrbitSCSet>())
            emit InpSimParameterSelected(model,index);
        else if (index.data().canConvert<InpSimEnvironment>())
            emit InpSimParameterSelected(model,index);
        else if (index.data().canConvert<InpSimCelestialBody>())
            emit InpSimParameterSelected(model,index);
        else if (index.data().canConvert<InpSimLagrangePointSystem>())
            emit InpSimParameterSelected(model, index);
        else if (index.data().canConvert<InpSimGroundStation>())
            emit InpSimParameterSelected(model,index);
        else if (index.data().canConvert<FOVHeader>())
            emit FOVHeadserSelected(model, index);
        else if (index.data().canConvert<InpIPCHeader>())
            emit InpIpcHeaderSelected(model, index);
        else if (index.data().canConvert<GraphicsHeader>())
            emit GraphicsHeaderSelected(model, index);
        else if (index.data().canConvert<InpTDRs>())
            emit InpTDRsSelected(model, index);
        else if (index.data().canConvert<RegionHeader>())
            emit RegionHeaderSelected(model, index);
        /*
        mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton)
            emit missionSelected(model,index);
        else if (mouseEvent->button() == Qt::LeftButton)
            emit missionSelected(model,index);
        else
            qDebug() << "Double click: Middle";*/
        //emit passInfoModelandIndex(model,index);
    }
    //QStyledItemDelegate::editorEvent(event, model, option,index);
    return false;
}

void Qt42Delegate::printOutName(QAbstractItemModel* model, const QModelIndex& index)
{
    Q_UNUSED (model)
    Qt42BaseClass* Qt42BC = static_cast<Qt42BaseClass*>(index.internalPointer());
    qDebug() << Qt42BC->name() << " this is a test";
}

void Qt42Delegate::setModelDataByType(QLineEdit *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
    if (!index.isValid())
        return;
    QVariant V_oldData = index.data();
    QVariant V_newData = QVariant();
    QString newName = editor->text();

    if (V_oldData.canConvert<Mission>())
    {
        Mission oldMission = V_oldData.value<Mission>();
        Mission newMission = oldMission;
        if (newName.isEmpty())
            newName = oldMission.name();
        newMission.rename(newName);
        V_newData.setValue(newMission);
        model->setData(index, V_newData, Qt::EditRole);
    }
    else if (V_oldData.canConvert<Spacecraft>())
    {
        Spacecraft oldSpacecraft = V_oldData.value<Spacecraft>();
        Spacecraft newSpacecraft = oldSpacecraft;
        if (newName.isEmpty())
            newName = oldSpacecraft.name();
        newSpacecraft.rename(newName);
        V_newData.setValue(newSpacecraft);
        model->setData(index, V_newData, Qt::EditRole);
    }

    else if (V_oldData.canConvert<Orbit>())
    {
        Orbit oldOrbit = V_oldData.value<Orbit>();
        Orbit newOrbit = oldOrbit;
        if (newName.isEmpty())
            newName = oldOrbit.name();
        newOrbit.rename(newName);
        V_newData.setValue(newOrbit);
        model->setData(index, V_newData, Qt::EditRole);
    }
}

void Qt42Delegate::ShowDialogModifiyName(QAbstractItemModel *model,
                                         const QModelIndex &index)
{
    if (!index.isValid())
        return;
    if (canConvertToCustomType(index.data()))
    {
        QSize size(280,120);
        QSize sizeMax(320,180);
        QDialog* DialogModifyName = new QDialog;
        QLineEdit* nameLineEdit = new QLineEdit;
        QPushButton* btnOK = new QPushButton(tr("&OK"));
        QPushButton* btnCancel = new QPushButton(tr("&Cancel"));
        QDialogButtonBox* btnBox = new QDialogButtonBox;
        btnBox->addButton(btnOK, QDialogButtonBox::AcceptRole);
        btnBox->addButton(btnCancel, QDialogButtonBox::RejectRole);
        connect(btnBox, &QDialogButtonBox::accepted, DialogModifyName, &QDialog::accept);
        connect(btnBox, &QDialogButtonBox::rejected, DialogModifyName, &QDialog::reject);
        connect(btnOK, &QPushButton::clicked, this, [=](){this->setModelData(nameLineEdit, model,index);});
        QVBoxLayout* layoutV = new QVBoxLayout;
        layoutV->setContentsMargins(30,20,30,20);
        layoutV->addWidget(nameLineEdit);
        layoutV->addWidget(btnBox);
        DialogModifyName->setLayout(layoutV);
        DialogModifyName->resize(size);
        DialogModifyName->setMaximumSize(sizeMax);
        QString dialogTitle = QString();
        QString dataName = QString();
        if (index.data().canConvert<Mission>()){
            Mission M = index.data().value<Mission>();
            dialogTitle = "Rename Mission";
            dataName = M.name();
        }
        if (index.data().canConvert<Spacecraft>()){
            Spacecraft SC = index.data().value<Spacecraft>();
            dialogTitle = "Rename Spacecraft";
            dataName = SC.name();
        }
        if (index.data().canConvert<Orbit>()){
            Orbit O = index.data().value<Orbit>();
            dialogTitle = "Rename Orbit";
            dataName = O.name();
        }

        DialogModifyName->setWindowTitle(dialogTitle);
        nameLineEdit->setText(dataName);
        nameLineEdit->selectAll();
        DialogModifyName->exec();
    }
}

void Qt42Delegate::showDialogRemoveClose(QAbstractItemModel *model, const QModelIndex& index)
{
    if (!index.isValid())
        return;
    QMessageBox* msgBox = new QMessageBox;
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    msgBox->setDefaultButton(QMessageBox::No);

    QModelIndex parentIndex = model->parent(index);
    int row = -1;
    if (index.data().canConvert<Mission>()){
        Mission oldMission = index.data().value<Mission>();
        msgBox->setWindowTitle(tr("Close Mission"));
        msgBox->setText(tr("Mission \"") + oldMission.name() +
                        tr("\" will be closed.)") + tr("\nContinue?"));
        row = oldMission.index();
    }

    if (index.data().canConvert<Spacecraft>()){
        Spacecraft oldSC = index.data().value<Spacecraft>();
        msgBox->setWindowTitle(tr("Remove Spacecraft"));
        msgBox->setText(tr("Spacecraft \"") + oldSC.name() +
                        tr("\" will be removed.\nContinue?"));
        row = oldSC.index();
    }

    if (index.data().canConvert<Orbit>()){
        Orbit oldO = index.data().value<Orbit>();
        msgBox->setWindowTitle(tr("Remove Orbit"));
        msgBox->setText(tr("Orbit \"") + oldO.name() +
                        tr("\" will be removed.\nContinue?"));
        row = oldO.index();
    }

    int ret = msgBox->exec();
    switch (ret) {
    case QMessageBox::Ok:
        emit removeObject(model, index);
        // This signal is emitted to close the widget before deleting the object.
        if (parentIndex.isValid()){
            model->removeRows(row, 1, parentIndex);
        }
        else
            emit removeMission(row);
        break;
    case QMessageBox::No:
        break;
    default:
        break;
    }
}


bool Qt42Delegate::createSpacecraft(QAbstractItemModel *model, const QModelIndex &index)
{
    if (!index.isValid())
        return false;
    if (index.data().canConvert<SpacecraftHeader>())
    {
        int position = (index.data().value<SpacecraftHeader>()).numberOfSpacecraft();
        int rows = 1;
        model->insertRows(position, rows, index);
        return true;
    }
    return false;
}
