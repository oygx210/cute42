#include "WidgetHeaders/inpregiondialog.h"
#include "MVDheaders/qt42model.h"
#include "DataHeaders/mission.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "ShareHeaders/qt42commands.h"
#include <QUndoStack>
#include <QAction>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QFileDialog>
InpRegionDialog::InpRegionDialog(QWidget* parent) : QDialog(parent)
{
    tabWidgetParent = qobject_cast<QTabWidget*>(parent);
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
}

InpRegionDialog::~InpRegionDialog()
{

}

void InpRegionDialog::setModel(QAbstractItemModel* model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    else
        m_model = nullptr;
}

void InpRegionDialog::setRootIndex(const QModelIndex& index)
{
    if (!index.isValid() || !index.data().canConvert<RegionHeader>())
    {
        m_index = QModelIndex();
        m_regionHeader = RegionHeader();
        return;
    }

    else
        m_index = index;

    m_regionHeader = m_index.data().value<RegionHeader>();
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    mapDataFromModelToWidget();
    return;
}

void InpRegionDialog::createWidgets()
{
    const int widthBtnComboboxEdit = 150;
    const int widthSpinbox = 120;

    QHBoxLayout* layoutGroupBoxDetails_Edit= new QHBoxLayout;
    QFormLayout* layoutDialog = new QFormLayout;

    groupboxDetails = new QGroupBox(tr("Details"));
    groupboxDetails->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutGroupBoxDetails = new QFormLayout;
    labelMission = new QLabel(tr("Mission:"));
    editMission = new QLineEdit;
    editMission->setReadOnly(true);
    labelNumberOfRegions = new QLabel(tr("Number of Regions"));
    editNumberOfRegions = new QLineEdit;
    editNumberOfRegions->setReadOnly(true);
    labelRegions = new QLabel(tr("Region"));
    comboboxRegions = new QComboBox;
    btnAddRegions = new QPushButton(tr("Add"));
    btnRemoveRegions = new QPushButton(tr("Remove"));
    btnAddRegions->setMaximumWidth(widthBtnComboboxEdit);
    btnRemoveRegions->setMaximumWidth(widthBtnComboboxEdit);

    QHBoxLayout* layoutBtnAddRemove = new QHBoxLayout;
    layoutBtnAddRemove->addWidget(btnAddRegions,1);
    layoutBtnAddRemove->addWidget(btnRemoveRegions,1);
    layoutBtnAddRemove->setAlignment(Qt::AlignCenter);

    layoutGroupBoxDetails->addRow(labelMission, editMission);
    layoutGroupBoxDetails->addRow(labelNumberOfRegions, editNumberOfRegions);
    layoutGroupBoxDetails->addRow(labelRegions, comboboxRegions);
    layoutGroupBoxDetails->addRow(layoutBtnAddRemove);
    groupboxDetails->setLayout(layoutGroupBoxDetails);


    groupboxEdit = new QGroupBox(tr("Region Selected"));
    groupboxEdit->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutEdit = new QFormLayout;
    QHBoxLayout* layoutPOSW_LLA = new QHBoxLayout;

    chkbxExists = new QCheckBox(tr("Exists"));
    labelName = new QLabel(tr("Name"));
    editName = new QLineEdit;
    labelWorld = new QLabel(tr("World"));
    comboboxWorld = new QComboBox;
    comboboxWorld->addItems(list_orbitCenter_World);
    labelPOWSLLA = new QLabel(tr("POSW")+QString::fromUtf8("\u002A") + tr(" or ") +
                              tr("LLA") + QString::fromUtf8("\u002A")+
                              QString::fromUtf8("\u002A"));
    comboboxPOWSLLA = new QComboBox;
    comboboxPOWSLLA->addItems(list_regionPOWS_LLA);

    groupboxPositionInWorld = new QGroupBox(tr("Position in World [m]"));
    QFormLayout* layoutPositionInWorld = new QFormLayout;
    labelPositionInWorld1 = new QLabel(tr("x")+QString::fromUtf8("\u2081"));
    dblSpinboxPositionInWorld1= new QDoubleSpinBox;
    dblSpinboxPositionInWorld1->setMinimum(std::numeric_limits<double>::lowest());
    dblSpinboxPositionInWorld1->setMaximumWidth(widthSpinbox);
    labelPositionInWorld2 = new QLabel(tr("x")+QString::fromUtf8("\u2082"));
    dblSpinboxPositionInWorld2= new QDoubleSpinBox;
    dblSpinboxPositionInWorld2->setMinimum(std::numeric_limits<double>::lowest());
    dblSpinboxPositionInWorld2->setMaximumWidth(widthSpinbox);
    labelPositionInWorld3 = new QLabel(tr("x")+QString::fromUtf8("\u2083"));
    dblSpinboxPositionInWorld3= new QDoubleSpinBox;
    dblSpinboxPositionInWorld3->setMinimum(std::numeric_limits<double>::lowest());
    dblSpinboxPositionInWorld3->setMaximumWidth(widthSpinbox);
    layoutPositionInWorld->addRow(labelPositionInWorld1, dblSpinboxPositionInWorld1);
    layoutPositionInWorld->addRow(labelPositionInWorld2, dblSpinboxPositionInWorld2);
    layoutPositionInWorld->addRow(labelPositionInWorld3, dblSpinboxPositionInWorld3);
    groupboxPositionInWorld->setLayout(layoutPositionInWorld);


    groupboxLngLatAlt = new QGroupBox(tr("Longitude, Latitude and Altitude"));
    QFormLayout* layoutLngLatAlt = new QFormLayout;
    labelLongitude = new QLabel(tr("Longitude [deg]"));
    dblSpinboxLongitude = new QDoubleSpinBox;
    dblSpinboxLongitude->setRange(-180.0,180.0);
    dblSpinboxLongitude->setMaximumWidth(widthSpinbox);
    labelLatitude = new QLabel(tr("Latitude [deg]"));
    dblSpinboxLatitude = new QDoubleSpinBox;
    dblSpinboxLatitude->setRange(-90.0,90.0);
    dblSpinboxLatitude->setMaximumWidth(widthSpinbox);
    labelAltitude = new QLabel(tr("Altitude [m]"));
    dblSpinboxAltitude = new QDoubleSpinBox;
    dblSpinboxAltitude->setMaximum(std::numeric_limits<double>::max());
    dblSpinboxAltitude->setMaximumWidth(widthSpinbox);
    layoutLngLatAlt->addRow(labelLongitude, dblSpinboxLongitude);
    layoutLngLatAlt->addRow(labelLatitude, dblSpinboxLatitude);
    layoutLngLatAlt->addRow(labelAltitude, dblSpinboxAltitude);
    groupboxLngLatAlt->setLayout(layoutLngLatAlt);

    groupboxElasticityDampingFrictionCoef =
            new QGroupBox(tr("Elasticity, Damping, and Friction Coefficients"));
    QHBoxLayout* layoutElasticityDampingFriction = new QHBoxLayout;
    QVBoxLayout* layoutElasticity = new QVBoxLayout;
    QVBoxLayout* layoutDamping = new QVBoxLayout;
    QVBoxLayout* layoutFriction = new QVBoxLayout;
    labelElasticity = new QLabel(tr("Elasticity"));
    dblSpinboxElasticity = new QDoubleSpinBox;
    dblSpinboxElasticity->setMaximum(std::numeric_limits<double>::max());
    labelDamping = new QLabel(tr("Damping"));
    dblSpinboxDamping = new QDoubleSpinBox;
    dblSpinboxDamping->setMaximum(std::numeric_limits<double>::max());
    labelFrictionCoef = new QLabel(tr("Friction"));
    dblSpinboxFrictionCoef = new QDoubleSpinBox;
    dblSpinboxFrictionCoef->setMaximum(std::numeric_limits<double>::max());

    layoutElasticity->addWidget(labelElasticity, 1);
    layoutElasticity->addWidget(dblSpinboxElasticity, 1);
    layoutDamping->addWidget(labelDamping, 1);
    layoutDamping->addWidget(dblSpinboxDamping, 1);
    layoutFriction->addWidget(labelFrictionCoef, 1);
    layoutFriction->addWidget(dblSpinboxFrictionCoef, 1);
    layoutElasticityDampingFriction->addLayout(layoutElasticity,1);
    layoutElasticityDampingFriction->addLayout(layoutDamping, 1);
    layoutElasticityDampingFriction->addLayout(layoutFriction, 1);
    groupboxElasticityDampingFrictionCoef->setLayout(layoutElasticityDampingFriction);

    btnGeometryFileName = new QPushButton(tr("Geometry File Name"));
    editGeometryFileName = new QLineEdit;
    editGeometryFileName->setReadOnly(true);

    layoutPOSW_LLA->addWidget(groupboxPositionInWorld, 1);
    layoutPOSW_LLA->addWidget(groupboxLngLatAlt,1);

    layoutEdit->addRow(chkbxExists);
    layoutEdit->addRow(labelName, editName);
    layoutEdit->addRow(labelWorld, comboboxWorld);
    layoutEdit->addRow(labelPOWSLLA, comboboxPOWSLLA);
    layoutEdit->addRow(layoutPOSW_LLA);
    layoutEdit->addRow(groupboxElasticityDampingFrictionCoef);
    layoutEdit->addRow(btnGeometryFileName, editGeometryFileName);
    groupboxEdit->setLayout(layoutEdit);

    layoutGroupBoxDetails_Edit->addWidget(groupboxDetails,1);
    layoutGroupBoxDetails_Edit->addWidget(groupboxEdit,1);

    labelNoteAsterisk = new QLabel(QString::fromUtf8("\u002A")+
                                   tr("POSW: Position in World"));
    labelNoteAsteriskAsterisk = new QLabel(QString::fromUtf8("\u002A\u002A")+
                                           tr("LLA: Longtitude, Latitude, and Altitude"));
    layoutDialog->addRow(layoutGroupBoxDetails_Edit);
    layoutDialog->addRow(labelNoteAsterisk);
    layoutDialog->addRow(labelNoteAsteriskAsterisk);
    layoutDialog->addRow(m_buttonBox);
    setLayout(layoutDialog);
}

void InpRegionDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void InpRegionDialog::updateNameComboboxRegions()
{
    const int indexComboboxRegions = comboboxRegions->currentIndex();
    const QString newRegionName = editName->text().trimmed();
    comboboxRegions->removeItem(indexComboboxRegions);
    comboboxRegions->insertItem(indexComboboxRegions, newRegionName);
    comboboxRegions->setCurrentIndex(indexComboboxRegions);
}

void InpRegionDialog::openDirectoryDialog()
{
    QFileDialog fileDialog(this);
    fileDialog.setOption(QFileDialog::DontUseNativeDialog);
    //fileDialog.setNameFilter(tr("Geometry file (*.txt)"));
    QString geometryFileWithDir = fileDialog.getOpenFileName(this, tr("Open Geometry File"), QString(),
                                                                  tr("*.txt"));
    editGeometryFileName->blockSignals(false);
    editGeometryFileName->setText(geometryFileWithDir.trimmed());
    editGeometryFileName->blockSignals(true);
}

void InpRegionDialog::addRegion()
{
    m_regionHeader.addRegion();
    editNumberOfRegions->setText(QString::number(m_regionHeader.numberOfRegions()));
    comboboxRegions->addItem(m_regionHeader.qvecRegions().last().name().trimmed());
}

void InpRegionDialog::removeRegion()
{
    // the QComboBox::currentIndex may be -1 if the comboboxRegions is empty, which may cause error of out of range for QVector. by Yu Tso (Roy) on Jan.20th, 2020.
    if (comboboxRegions->currentIndex() <= 0 || comboboxRegions->currentText().trimmed().isEmpty())
        return;
    qDebug() << "void InpRegionDialog::removeRegion()" << "current index" << comboboxRegions->currentIndex();
    m_regionHeader.removeRegion(comboboxRegions->currentIndex()-1);
    editNumberOfRegions->setText(QString::number(m_regionHeader.numberOfRegions()));
    comboboxRegions->removeItem(comboboxRegions->currentIndex());
    if (comboboxRegions->currentIndex() == -1)
        groupboxEdit->setEnabled(false);
    else
    {
        comboboxRegions->setCurrentIndex(0);
    }
}

void InpRegionDialog::enablePOSW_LLA(const int& index)
{
    if (index == 0){
        groupboxPositionInWorld->setEnabled(true);
        groupboxLngLatAlt->setEnabled(false);
    }
    else if (index == 1)
    {
        groupboxPositionInWorld->setEnabled(false);
        groupboxLngLatAlt->setEnabled(true);
    }
}

void InpRegionDialog::editQt42RegionWhenEditFinished()
{
    if (comboboxRegions->currentIndex()==0)
        return;
    const int indexRegion = comboboxRegions->currentIndex()-1;
    m_regionHeader.region(indexRegion).edit(chkbxExists->isChecked(),
                                            editName->text().trimmed(),
                                            orbitCenter_World(comboboxWorld->currentText().trimmed()).trimmed(),
                                            map_regionPOWS_LLA.value(comboboxPOWSLLA->currentText().trimmed()).trimmed(),
    {dblSpinboxPositionInWorld1->value(),dblSpinboxPositionInWorld2->value(),dblSpinboxPositionInWorld3->value()},
    {dblSpinboxLongitude->value(), dblSpinboxLatitude->value(), dblSpinboxAltitude->value()},
    {dblSpinboxElasticity->value(), dblSpinboxDamping->value(), dblSpinboxFrictionCoef->value()},
                                            editGeometryFileName->text().trimmed());
}

void InpRegionDialog::mapDataToSelectedRegion(const int& index)
{
    editGeometryFileName->blockSignals(true);
    Qt42Region qt42region;
    // the QComboBox::currentIndex may be -1 if the comboboxRegions is empty, which may cause error of out of range for QVector. by Yu Tso (Roy) on Jan.20th, 2020.
    if (index <= 0){
        qt42region = Qt42Region();
        groupboxEdit->setEnabled(false);
        btnRemoveRegions->setEnabled(false);
;    }

    else{
        qt42region = m_regionHeader.region(index-1);
        groupboxEdit->setEnabled(true);
        btnRemoveRegions->setEnabled(true);
    }

    chkbxExists->setChecked(qt42region.exists());
    editName->setText(qt42region.name().trimmed());
    comboboxWorld->setCurrentText(orbitCenter_World(qt42region.world().trimmed()).trimmed());
    comboboxPOWSLLA->setCurrentText(map_regionPOWS_LLA.value(qt42region.PoswLla().trimmed()).trimmed());
    dblSpinboxPositionInWorld1->setValue(qt42region.positionInWorld()[0]);
    dblSpinboxPositionInWorld2->setValue(qt42region.positionInWorld()[1]);
    dblSpinboxPositionInWorld3->setValue(qt42region.positionInWorld()[2]);
    dblSpinboxLongitude->setValue(qt42region.lngLatAlt()[0]);
    dblSpinboxLatitude->setValue(qt42region.lngLatAlt()[1]);
    dblSpinboxAltitude->setValue(qt42region.lngLatAlt()[2]);
    dblSpinboxElasticity->setValue(qt42region.ElasticityDampingFrictionCoef()[0]);
    dblSpinboxDamping->setValue(qt42region.ElasticityDampingFrictionCoef()[1]);
    dblSpinboxFrictionCoef->setValue(qt42region.ElasticityDampingFrictionCoef()[2]);
    editGeometryFileName->setText(qt42region.geometryFileName().trimmed());
}

void InpRegionDialog::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);

    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Save),
            [=](){m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_undoAction, &QAction::triggered, this, [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});



    connect(comboboxRegions, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &InpRegionDialog::mapDataToSelectedRegion);
    connect(btnAddRegions, &QPushButton::clicked, this, &InpRegionDialog::addRegion);
    connect(btnRemoveRegions, &QPushButton::clicked, this, &InpRegionDialog::removeRegion);
    connect(comboboxPOWSLLA, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &InpRegionDialog::enablePOSW_LLA);

    connect(chkbxExists, &QCheckBox::stateChanged, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(editName, &QLineEdit::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(editName, &QLineEdit::editingFinished, this,
            &InpRegionDialog::updateNameComboboxRegions);
    connect(comboboxWorld, &QComboBox::currentTextChanged, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(comboboxPOWSLLA, &QComboBox::currentTextChanged, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxPositionInWorld1, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxPositionInWorld2, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxPositionInWorld3, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxLongitude, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxLatitude, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxAltitude, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxElasticity, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxDamping, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(dblSpinboxFrictionCoef, &QDoubleSpinBox::editingFinished, this,
            &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(editGeometryFileName, &QLineEdit::textChanged, this, &InpRegionDialog::editQt42RegionWhenEditFinished);
    connect(btnGeometryFileName, &QPushButton::clicked, this, &InpRegionDialog::openDirectoryDialog);

    connect(chkbxExists, &QCheckBox::stateChanged, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editName, &QLineEdit::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxWorld, &QComboBox::currentTextChanged, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPOWSLLA, &QComboBox::currentTextChanged, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxPositionInWorld1, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxPositionInWorld2, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxPositionInWorld3, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxLongitude, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxLatitude, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxAltitude, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxElasticity, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxDamping, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxFrictionCoef, &QDoubleSpinBox::editingFinished, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(btnGeometryFileName, &QPushButton::clicked, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(btnAddRegions, &QPushButton::clicked, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(btnRemoveRegions, &QPushButton::clicked, m_buttonBox,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void InpRegionDialog::mapDataFromModelToWidget()
{
    if (!m_index.isValid() || !m_index.data().canConvert<RegionHeader>())
        return;
    // the QComboBox::currentIndex may be -1 if the comboboxRegions is empty, which may cause error of out of range for QVector. by Yu Tso (Roy) on Jan.20th, 2020.
    if (comboboxRegions->currentIndex() <= 0)
        groupboxEdit->setEnabled(false);
    Mission mission = Mission();
    QModelIndex indexMission = m_index.parent();
    mission = indexMission.data().value<Mission>();
    editMission->setText(mission.name());
    editNumberOfRegions->setText(QString::number(m_regionHeader.numberOfRegions()));

    QStringList listRigions{""};
    for (int i = 0; i < m_regionHeader.numberOfRegions(); ++i)
    {
        listRigions.append(m_regionHeader.region(i).name());
    }
    if (comboboxRegions->count()){
        qDebug() << mission.name() << "comboboxRegions->count()" << comboboxRegions->count();
        comboboxRegions->clear();
    }
    comboboxRegions->addItems(listRigions);
    comboboxRegions->setCurrentIndex(0);
    btnRemoveRegions->setEnabled(false);
    groupboxEdit->setEnabled(false);
}

void InpRegionDialog::mapDataFromWidgetToModel()
{
    QVariant newData = QVariant();
    newData.setValue(m_regionHeader);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
}
