#include "WidgetHeaders/graphicsdialog.h"
#include "MVDheaders/qt42model.h"
#include "ShareHeaders/qt42_sharedparameters.h"
#include "ShareHeaders/qt42commands.h"
#include "DataHeaders/spacecraftcomponents.h"
#include "DataHeaders/spacecraft.h"
#include "DataHeaders/mission.h"
#include <QAbstractItemModel>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QAction>
#include <QUndoStack>
#include <QFont>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QDebug>
#include <QString>
#include<bits/stdc++.h>

GraphicsDialog::GraphicsDialog(QWidget* parent) : QDialog(parent)
{
    m_undoStack = new QUndoStack(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                       QDialogButtonBox::Apply|
                                       QDialogButtonBox::Cancel);
    createWidgets();
    createActions();
    createConnections();
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(pal);
}

GraphicsDialog::~GraphicsDialog()
{

}

void GraphicsDialog::setModel(QAbstractItemModel* model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    else
        m_model = nullptr;
}

void GraphicsDialog::setRootIndex(const QModelIndex& index)
{
    if (!index.isValid() || !index.data().canConvert<GraphicsHeader>())
    {
        m_index = QModelIndex();
        m_graphicsHeader = GraphicsHeader();
        comboboxPOVInitialHostSC->clear();
        comboboxPOVInitialHostSCB->clear();
        return;
    }
    else{
        m_index = index;
        mapDataFromModelToWidget();
        m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
        m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    }
}

void GraphicsDialog::updateInitalHostSCB(Spacecraft& sc)
{
    comboboxPOVInitialHostSCB->clear();
    QStringList listSCB{""};
    for (int i = 0; i < sc.numberOfBodies(); ++i)
    {
        if (sc.body(i)->includedInCalculation())
            listSCB.append(sc.body(i)->name().trimmed());
    }
    comboboxPOVInitialHostSCB->addItems(listSCB);
}

void GraphicsDialog::updateInitalTargetSCB(Spacecraft& sc)
{
    comboboxPOVInitialTargetSCB->clear();
    QStringList listSCB{""};
    for (int i = 0; i < sc.numberOfBodies(); ++i)
    {
        if (sc.body(i)->includedInCalculation())
            listSCB.append(sc.body(i)->name().trimmed());
    }
    comboboxPOVInitialTargetSCB->addItems(listSCB);
}

void GraphicsDialog::mapDataFromModelToWidget()
{
    comboboxPOVInitialHostSC->clear();
    comboboxPOVInitialHostSCB->clear();
    comboboxPOVInitialTargetSC->clear();
    comboboxPOVInitialTargetSCB->clear();
    Mission mission = Mission();
    if (!m_index.isValid() || !m_index.data().canConvert<GraphicsHeader>()){
        m_graphicsHeader = GraphicsHeader();
    }
    else
    {
        m_graphicsHeader = m_index.data().value<GraphicsHeader>();
        QModelIndex indexMission = m_index.parent();
        mission = indexMission.data().value<Mission>();
        QStringList InitialHostTargetSC{""};
        for (int i = 0; i < mission.numberOfSpacecraft(); ++i)
        {
            Spacecraft SC = *(mission.spacecraft(i));
            if (SC.includedInCalculation())
            {
                InitialHostTargetSC.append(SC.name().trimmed());
            }
        }
        comboboxPOVInitialHostSC->addItems(InitialHostTargetSC);
        comboboxPOVInitialTargetSC->addItems(InitialHostTargetSC);
    }
    labelMission->setText(tr("Mission: ") + mission.name().trimmed());
    dblSpinboxGLOuputInterval->setValue(m_graphicsHeader.GLOutputInterval());
    editStarCatalogFileName->setText(m_graphicsHeader.starCatalogFileName().trimmed());
    chkbxMapWindowExists->setChecked(m_graphicsHeader.mapWindowExists());

    chkbxOrreyWindowExists->setChecked(m_graphicsHeader.orreryWindowExists());
    chkbxUnitSphereWindowExists->setChecked(m_graphicsHeader.unitSphereWindowExists());
    chkbxPauseAtStartup->setChecked(m_graphicsHeader.pauseAtStartup());

    comboboxPOVMode->setCurrentText(map_GraphicsPOVMode.value(m_graphicsHeader.povMode().trimmed()));
    comboboxHostType->setCurrentText(map_GraphicsHostTargetType.value(m_graphicsHeader.hostType().trimmed()));

    if (mission.numberOfSpacecraft())
    {
        comboboxPOVInitialHostSC->setCurrentText(mission.spacecraft(m_graphicsHeader.initialHostSC())->name().trimmed());
        updateInitalHostSCB(*mission.spacecraft(m_graphicsHeader.initialHostSC()));
        if (mission.spacecraft(m_graphicsHeader.initialHostSC())->numberOfBodies())
        {
            comboboxPOVInitialHostSCB->setCurrentText(mission.spacecraft(m_graphicsHeader.initialHostSC())->body(m_graphicsHeader.initialHostSC())->name().trimmed());
        }
        else
        {
            comboboxPOVInitialHostSCB->setCurrentText("");
        }
        comboboxPOVInitialHostPOVFrame->setCurrentText(map_RefernceFrame.value(m_graphicsHeader.initialHostPOVFrame().trimmed()));

        comboboxTargetType->setCurrentText(map_GraphicsHostTargetType.value(m_graphicsHeader.targetType().trimmed()));
        comboboxPOVInitialTargetSC->setCurrentText(mission.spacecraft(m_graphicsHeader.initialTargetSC())->name().trimmed());
        updateInitalTargetSCB(*mission.spacecraft(m_graphicsHeader.initialTargetSC()));
        if (mission.spacecraft(m_graphicsHeader.initialTargetSC())->numberOfBodies())
        {
            comboboxPOVInitialTargetSCB->setCurrentText(mission.spacecraft(m_graphicsHeader.initialTargetSC())->body(m_graphicsHeader.initialTargetSC())->name().trimmed());
        }
        else
        {
            comboboxPOVInitialTargetSCB->setCurrentText("");
        }
    }

    comboboxPOVInitialTargetPOVFrame->setCurrentText(map_RefernceFrame.value(m_graphicsHeader.initialTargetPOVFrame().trimmed()));
    comboboxBoresightAxis->setCurrentText(map_GraphicsPOVAxes.value(m_graphicsHeader.boresightAxis().trimmed()));
    comboboxUpAxis->setCurrentText(map_GraphicsPOVAxes.value(m_graphicsHeader.upAxis().trimmed()));

    dblSpinboxInitialPOVRangeFromTarget->setValue(m_graphicsHeader.initialPOVrangeFromTarget());
    dblSpinboxPOVAngleVertical->setValue(m_graphicsHeader.povAngleVertical());
    dblSpinboxPOVPositionHostX1->setValue(m_graphicsHeader.povPositionInHost()[0]);
    dblSpinboxPOVPositionHostX2->setValue(m_graphicsHeader.povPositionInHost()[1]);
    dblSpinboxPOVPositionHostX3->setValue(m_graphicsHeader.povPositionInHost()[2]);
    comboboxInitialPOVView->setCurrentText(map_GraphicsPOVViews.value(m_graphicsHeader.InitialPOVView().trimmed()));

    editCamTitle->setText(m_graphicsHeader.camTitle().trimmed());
    spinboxCAMWidth->setValue(m_graphicsHeader.camWidthHeight().first);
    spinboxCAMHeight->setValue(m_graphicsHeader.camWidthHeight().second);
    dblSpinboxMouseScaleFactor->setValue(m_graphicsHeader.camMouseScaleFactor());
    dblSpinboxDisplayGammaExponent->setValue(m_graphicsHeader.displayGammaExponent());

    chkbx_N_axes->setChecked(m_graphicsHeader.camShowMenu_N_Axes());
    chkbx_L_axes->setChecked(m_graphicsHeader.camShowMenu_L_Axes());
    chkbx_F_axes->setChecked(m_graphicsHeader.camShowMenu_F_Axes());
    chkbx_B_axes->setChecked(m_graphicsHeader.camShowMenu_B_Axes());
    chkbx_N_grid->setChecked(m_graphicsHeader.camShowMenu_N_Grid());
    chkbx_L_grid->setChecked(m_graphicsHeader.camShowMenu_L_Grid());
    chkbx_F_grid->setChecked(m_graphicsHeader.camShowMenu_F_Grid());
    chkbx_B_grid->setChecked(m_graphicsHeader.camShowMenu_B_Grid());
    chkbx_Gal_Grid->setChecked(m_graphicsHeader.camShowMenu_Gal_Grid());
    chkbx_FOVs->setChecked(m_graphicsHeader.camShowMenu_FOVs());
    chkbx_ProxOps->setChecked(m_graphicsHeader.camShowMenu_ProxOps());
    chkbx_TDRS->setChecked(m_graphicsHeader.camShowMenu_TDRS());
    chkbx_Shadows->setChecked(m_graphicsHeader.camShowMenu_Shadows());
    chkbx_AstroLabels->setChecked(m_graphicsHeader.camShowMenu_AstroLabels());
    chkbx_TruthVectors->setChecked(m_graphicsHeader.camShowMenu_TruthVectors());
    chkbx_FSWVectors->setChecked(m_graphicsHeader.camShowMenu_FSWVectors());
    chkbx_MilkyWay->setChecked(m_graphicsHeader.camShowMenu_MilkyWay());
    chkbx_FermiSky->setChecked(m_graphicsHeader.camShowMenu_FermiSky());

    editMapTitle->setText(m_graphicsHeader.mapMapTitle().trimmed());
    spinboxMapWidth->setValue(m_graphicsHeader.mapWidthHeight().first);
    spinboxMapHeight->setValue(m_graphicsHeader.mapWidthHeight().second);

    chkbxClock->setChecked(m_graphicsHeader.mapShowMenuClock());
    chkbxTlmClock->setChecked(m_graphicsHeader.mapShowMenuTlmClock());
    chkbxCredits->setChecked(m_graphicsHeader.mapShowMenuCredits());
    chkbxNight->setChecked(m_graphicsHeader.mapShowMenuNight());

    chkbxShowMajorConstellations->setChecked(m_graphicsHeader.unitSphereShowMenuMajor());
    chkbxShowZodiacConstellations->setChecked(m_graphicsHeader.unitSphereShowMenuZodiac());
    chkbxShowMinorConstellations->setChecked(m_graphicsHeader.unitShpereShowMenuMinor());
}

void GraphicsDialog::mapDataFromWidgetToModel()
{
    if (!m_index.isValid() || !m_index.data().canConvert<GraphicsHeader>())
        return;

    QVariant newData = QVariant();
    QModelIndex indexMission = m_index.parent();
    Mission mission = indexMission.data().value<Mission>();

    int indexHostSC = 0;
    int indexHostSCB = 0;
    int indexTargetSC = 0;
    int indexTargetSCB = 0;
    if (!comboboxPOVInitialHostSC->currentText().isEmpty() &&
            comboboxHostType->currentText().trimmed().toUpper() == "SPACECRAFT")
    {
        for (int i = 0; i < mission.numberOfSpacecraft(); ++i)
        {
            if (mission.spacecraft(i)->name().trimmed() == comboboxPOVInitialHostSC->currentText().trimmed())
            {
               indexHostSC = i;
               break;
            }
        }
    }

    if (!comboboxPOVInitialHostSCB->currentText().isEmpty() &&
            comboboxHostType->currentText().trimmed().toUpper() == "BODY")
    {
        Spacecraft sc = *mission.spacecraft(indexHostSC);
        for (int i = 0; i < sc.numberOfBodies(); ++i)
        {
            if (sc.body(i)->name().trimmed() == comboboxPOVInitialHostSCB->currentText().trimmed())
            {
                indexHostSCB = i;
                break;
            }
        }
    }

    if (!comboboxPOVInitialTargetSC->currentText().isEmpty() &&
            comboboxTargetType->currentText().trimmed().toUpper() == "SPACECRAFT")
    {
        for (int i = 0; i < mission.numberOfSpacecraft(); ++i)
        {
            if (mission.spacecraft(i)->name().trimmed() == comboboxPOVInitialTargetSC->currentText().trimmed())
            {
               indexTargetSC = i;
               break;
            }
        }
    }

    if (!comboboxPOVInitialTargetSCB->currentText().isEmpty() &&
            comboboxTargetType->currentText().trimmed().toUpper() == "BODY")
    {
        Spacecraft sc = *mission.spacecraft(indexTargetSC);
        for (int i = 0; i < sc.numberOfBodies(); ++i)
        {
            if (sc.body(i)->name().trimmed() == comboboxPOVInitialTargetSCB->currentText().trimmed())
            {
                indexTargetSCB = i;
                break;
            }
        }
    }


    m_graphicsHeader.edit(dblSpinboxGLOuputInterval->value(),
                          editStarCatalogFileName->text().trimmed(),
                          chkbxMapWindowExists->isChecked(),
                          chkbxOrreyWindowExists->isChecked(),
                          chkbxUnitSphereWindowExists->isChecked(),
                          chkbxPauseAtStartup->isChecked(),
                          map_GraphicsPOVMode.value(comboboxPOVMode->currentText().trimmed()),
                          map_GraphicsHostTargetType.value(comboboxHostType->currentText().trimmed()),
                          indexHostSC,
                          indexHostSCB,
                          map_RefernceFrame.value(comboboxPOVInitialHostPOVFrame->currentText().trimmed()),
                          map_GraphicsHostTargetType.value(comboboxTargetType->currentText().trimmed()),
                          indexTargetSC,
                          indexTargetSCB,
                          map_RefernceFrame.value(comboboxPOVInitialTargetPOVFrame->currentText().trimmed()),
                          map_GraphicsPOVAxes.value(comboboxBoresightAxis->currentText().trimmed()),
                          map_GraphicsPOVAxes.value(comboboxUpAxis->currentText().trimmed()),
                          dblSpinboxInitialPOVRangeFromTarget->value(),
                          dblSpinboxPOVAngleVertical->value(),
    {dblSpinboxPOVPositionHostX1->value(),dblSpinboxPOVPositionHostX2->value(),dblSpinboxPOVPositionHostX3->value()},
                          map_GraphicsPOVViews.value(comboboxInitialPOVView->currentText().trimmed()),
                          editCamTitle->text().trimmed(),
    {spinboxCAMWidth->value(), spinboxCAMHeight->value()},
                          dblSpinboxMouseScaleFactor->value(),
                          dblSpinboxDisplayGammaExponent->value(),
                          chkbx_N_axes->isChecked(),
                          chkbx_L_axes->isChecked(),
                          chkbx_F_axes->isChecked(),
                          chkbx_B_axes->isChecked(),
                          chkbx_N_grid->isChecked(),
                          chkbx_L_grid->isChecked(),
                          chkbx_F_grid->isChecked(),
                          chkbx_B_grid->isChecked(),
                          chkbx_Gal_Grid->isChecked(),
                          chkbx_FOVs->isChecked(),
                          chkbx_ProxOps->isChecked(),
                          chkbx_TDRS->isChecked(),
                          chkbx_Shadows->isChecked(),
                          chkbx_AstroLabels->isChecked(),
                          chkbx_TruthVectors->isChecked(),
                          chkbx_FSWVectors->isChecked(),
                          chkbx_MilkyWay->isChecked(),
                          chkbx_FermiSky->isChecked(),
                          editMapTitle->text(),
    {spinboxMapWidth->value(), spinboxMapHeight->value()},
                          chkbxClock->isChecked(),
                          chkbxTlmClock->isChecked(),
                          chkbxCredits->isChecked(),
                          chkbxNight->isChecked(),
                          chkbxShowMajorConstellations->isChecked(),
                          chkbxShowZodiacConstellations->isChecked(),
                          chkbxShowMinorConstellations->isChecked());

    newData.setValue(m_graphicsHeader);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
}


void GraphicsDialog::createWidgets()
{
    QVBoxLayout* layoutDialog = new QVBoxLayout;
    tabWidget = new QTabWidget();
    widgetPage1 = new QWidget();
    QHBoxLayout* layoutWidgetPage1 = new QHBoxLayout;
    widgetPage2 = new QWidget();
    QHBoxLayout* layoutWidgetPage2 = new QHBoxLayout;
    widgetPage3 = new QWidget();
    QVBoxLayout* layoutWidgetPage3 = new QVBoxLayout;

    labelMission = new QLabel(tr("Mission: "));
    QFont fontLabelMission("Arial", 14, QFont::Bold);
    labelMission->setFont(fontLabelMission);
    labelMission->setStyleSheet("QLabel {color : white;}");

    groupboxConfiguration = new QGroupBox(tr("Graphics Configuration"));
    groupboxConfiguration->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutConfiguration = new QFormLayout;
    labelGLOuputInterval = new QLabel(tr("GL Output Interval [sec]"));
    dblSpinboxGLOuputInterval = new QDoubleSpinBox;
    dblSpinboxGLOuputInterval->setMinimum(0.1);
    btnStarCatalogFileName = new QPushButton(tr("Star Catalog File Name"));
    editStarCatalogFileName = new QLineEdit;
    editStarCatalogFileName->setReadOnly(true);
    chkbxMapWindowExists = new QCheckBox(tr("Map Window Exists"));
    chkbxOrreyWindowExists = new QCheckBox(tr("Orrery Window Exists"));
    chkbxUnitSphereWindowExists = new QCheckBox(tr("Unit Sphere Window Exists"));
    layoutConfiguration->addRow(labelGLOuputInterval, dblSpinboxGLOuputInterval);
    layoutConfiguration->addRow(btnStarCatalogFileName, editStarCatalogFileName);
    layoutConfiguration->addRow(chkbxMapWindowExists);
    layoutConfiguration->addRow(chkbxOrreyWindowExists);
    layoutConfiguration->addRow(chkbxUnitSphereWindowExists);
    groupboxConfiguration->setLayout(layoutConfiguration);

    groupboxPOV = new QGroupBox(tr("POV"));
    groupboxPOV->setAlignment(Qt::AlignCenter);
    QHBoxLayout* layoutPOV = new QHBoxLayout;
    QFormLayout* layoutPOVLeft = new QFormLayout;
    QFormLayout* layoutPOVRight = new QFormLayout;

    chkbxPauseAtStartup = new QCheckBox(tr("Pause at Startup"));
    labelPOVMode = new QLabel(tr("POV Mode"));
    comboboxPOVMode = new QComboBox();
    comboboxPOVMode->addItems(list_GraphicsPOVMode);
    comboboxPOVMode->setMaximumWidth(210);
    groupboxPOVInitialHost = new QGroupBox(tr("Initial Host"));
    QFormLayout* layoutInitialHost = new QFormLayout;
    labelHostType = new QLabel(tr("Host Type"));
    comboboxHostType = new QComboBox();
    comboboxHostType->setMaximumWidth(210);
    comboboxHostType->addItems(list_GraphicsHostTargetType);
    labelPOVInitialHostSC = new QLabel(tr("Spacecraft"));
    comboboxPOVInitialHostSC = new QComboBox();
    comboboxPOVInitialHostSC->setMaximumWidth(210);
    labelPOVInitialHostSCB = new QLabel(tr("Body"));
    comboboxPOVInitialHostSCB = new QComboBox();
    comboboxPOVInitialHostSCB->setMaximumWidth(210);
    labelPOVInitialHostPOVFrame = new QLabel(tr("POV Frame"));
    comboboxPOVInitialHostPOVFrame = new QComboBox();
    comboboxPOVInitialHostPOVFrame->setMaximumWidth(210);
    comboboxPOVInitialHostPOVFrame->addItems(list_ReferenceFrameWithFormationFrame);
    layoutInitialHost->addRow(labelHostType, comboboxHostType);
    layoutInitialHost->addRow(labelPOVInitialHostSC, comboboxPOVInitialHostSC);
    layoutInitialHost->addRow(labelPOVInitialHostSCB, comboboxPOVInitialHostSCB);
    layoutInitialHost->addRow(labelPOVInitialHostPOVFrame, comboboxPOVInitialHostPOVFrame);

    groupboxPOVInitialHost->setLayout(layoutInitialHost);
    groupboxPOVInitialTarget = new QGroupBox(tr("Initial Target"));
    QFormLayout* layoutInitialTarget = new QFormLayout;
    labelTargetType = new QLabel(tr("Target Type"));
    comboboxTargetType = new QComboBox;
    comboboxTargetType->setMaximumWidth(210);
    comboboxTargetType->addItems(list_GraphicsHostTargetType);
    labelPOVInitialTargetSC = new QLabel(tr("Spacecraft"));
    comboboxPOVInitialTargetSC = new QComboBox();
    comboboxPOVInitialTargetSC->setMaximumWidth(210);
    labelPOVInitialTargetSCB = new QLabel(tr("Body"));
    comboboxPOVInitialTargetSCB = new QComboBox();
    comboboxPOVInitialTargetSCB->setMaximumWidth(210);
    labelPOVInitialTargetPOVFrame = new QLabel(tr("POV Frame"));
    comboboxPOVInitialTargetPOVFrame = new QComboBox();
    comboboxPOVInitialTargetPOVFrame->setMaximumWidth(210);
    comboboxPOVInitialTargetPOVFrame->addItems(list_ReferenceFrameWithFormationFrame);
    layoutInitialTarget->addRow(labelTargetType, comboboxTargetType);
    layoutInitialTarget->addRow(labelPOVInitialTargetSC, comboboxPOVInitialTargetSC);
    layoutInitialTarget->addRow(labelPOVInitialTargetSCB, comboboxPOVInitialTargetSCB);
    layoutInitialTarget->addRow(labelPOVInitialTargetPOVFrame, comboboxPOVInitialTargetPOVFrame);
    groupboxPOVInitialTarget->setLayout(layoutInitialTarget);
    labelBoresightAxis = new QLabel(tr("Boresight Axis"));
    comboboxBoresightAxis = new QComboBox;
    comboboxBoresightAxis->addItems(list_GraphicsPOVAxes);
    labelUpAxis = new QLabel(tr("Up Axis"));
    comboboxUpAxis = new QComboBox();
    comboboxUpAxis->addItems(list_GraphicsPOVAxes);
    labelInitialPOVRangeFromTarget = new QLabel(tr("Initial POV Range from Target [m]"));
    dblSpinboxInitialPOVRangeFromTarget = new QDoubleSpinBox();
    labelPOVAngleVertical = new QLabel(tr("POV Angle (Vertical) [deg]"));
    dblSpinboxPOVAngleVertical = new QDoubleSpinBox();
    groupboxPOVPositionHost = new QGroupBox(tr("POV Position in Host [m]"));
    QHBoxLayout* layoutPOVPositionHost = new QHBoxLayout;
    QFont f("Arial",16, QFont::Bold);
    labelPOVPositionHostX1 = new QLabel(tr("x")+QString::fromUtf8("\u2081"));
    labelPOVPositionHostX1->setFont(f);
    dblSpinboxPOVPositionHostX1 = new QDoubleSpinBox();
    dblSpinboxPOVPositionHostX1->setRange(std::numeric_limits<double>::lowest(),std::numeric_limits<double>::infinity());
    dblSpinboxPOVPositionHostX1->setMaximumWidth(100);
    labelPOVPositionHostX2 = new QLabel(tr("x")+QString::fromUtf8("\u2082"));
    labelPOVPositionHostX2->setFont(f);
    dblSpinboxPOVPositionHostX2 = new QDoubleSpinBox();
    dblSpinboxPOVPositionHostX2->setRange(std::numeric_limits<double>::lowest(),std::numeric_limits<double>::infinity());
    dblSpinboxPOVPositionHostX2->setMaximumWidth(100);
    labelPOVPositionHostX3 = new QLabel(tr("x")+QString::fromUtf8("\u2083"));
    labelPOVPositionHostX3->setFont(f);
    dblSpinboxPOVPositionHostX3 = new QDoubleSpinBox();
    dblSpinboxPOVPositionHostX3->setRange(std::numeric_limits<double>::lowest(),std::numeric_limits<double>::infinity());
    dblSpinboxPOVPositionHostX3->setMaximumWidth(100);
    layoutPOVPositionHost->addWidget(labelPOVPositionHostX1, 1);
    layoutPOVPositionHost->addWidget(dblSpinboxPOVPositionHostX1, 2);
    layoutPOVPositionHost->addWidget(labelPOVPositionHostX2, 1);
    layoutPOVPositionHost->addWidget(dblSpinboxPOVPositionHostX2, 2);
    layoutPOVPositionHost->addWidget(labelPOVPositionHostX3, 1);
    layoutPOVPositionHost->addWidget(dblSpinboxPOVPositionHostX3, 2);
    groupboxPOVPositionHost->setLayout(layoutPOVPositionHost);
    labelInitialPOVView = new QLabel(tr("Initial POV View"));
    comboboxInitialPOVView = new QComboBox();
    comboboxInitialPOVView->addItems(list_GraphicsPOVViews);
    layoutPOVLeft->addRow(chkbxPauseAtStartup);
    layoutPOVLeft->addRow(labelPOVMode, comboboxPOVMode);
    layoutPOVLeft->addRow(groupboxPOVInitialHost);
    layoutPOVLeft->addRow(groupboxPOVInitialTarget);
    layoutPOVRight->addRow(labelBoresightAxis, comboboxBoresightAxis);
    layoutPOVRight->addRow(labelUpAxis, comboboxUpAxis);
    layoutPOVRight->addRow(labelInitialPOVRangeFromTarget, dblSpinboxInitialPOVRangeFromTarget);
    layoutPOVRight->addRow(labelPOVAngleVertical, dblSpinboxPOVAngleVertical);
    layoutPOVRight->addRow(groupboxPOVPositionHost);
    layoutPOVRight->addRow(labelInitialPOVView, comboboxInitialPOVView);
    layoutPOV->addLayout(layoutPOVLeft  , 1);
    layoutPOV->addLayout(layoutPOVRight , 1);
    groupboxPOV->setLayout(layoutPOV);


    groupboxCAM = new QGroupBox(tr("CAM"));
    groupboxCAM->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutCAM = new QFormLayout;
    labelCamTitle = new QLabel(tr("Cam Title"));
    editCamTitle = new QLineEdit();
    groupboxCAMWidthHeight = new QGroupBox(tr("Width and Height [pixels]"));
    QHBoxLayout* layoutCAMWidthHeight = new QHBoxLayout;
    labelCAMWidth = new QLabel(tr("Width"));
    spinboxCAMWidth = new QSpinBox();
    spinboxCAMWidth->setMaximum(INT_MAX);
    spinboxCAMWidth->setMaximumWidth(120);
    labelCAMHeight = new QLabel(tr("Height"));
    spinboxCAMHeight = new QSpinBox();
    spinboxCAMHeight->setMaximum(INT_MAX);
    spinboxCAMHeight->setMaximumWidth(120);
    layoutCAMWidthHeight->addWidget(labelCAMWidth, 1);
    layoutCAMWidthHeight->addWidget(spinboxCAMWidth, 2);
    layoutCAMWidthHeight->addWidget(labelCAMHeight, 1);
    layoutCAMWidthHeight->addWidget(spinboxCAMHeight, 2);
    groupboxCAMWidthHeight->setLayout(layoutCAMWidthHeight);
    labelMouseScaleFactor = new QLabel(tr("Mouse Scale Factor"));
    dblSpinboxMouseScaleFactor = new QDoubleSpinBox();
    dblSpinboxMouseScaleFactor->setSingleStep(1e-5);
    dblSpinboxMouseScaleFactor->setDecimals(5);
    labelDisplayGammaExponent = new QLabel(tr("Display's Gamma \nExponent (1.8-4.0)"));
    dblSpinboxDisplayGammaExponent = new QDoubleSpinBox();
    dblSpinboxDisplayGammaExponent->setRange(1.8, 4.0);
    layoutCAM->addRow(labelCamTitle, editCamTitle);
    layoutCAM->addRow(groupboxCAMWidthHeight);
    layoutCAM->addRow(labelMouseScaleFactor, dblSpinboxMouseScaleFactor);
    layoutCAM->addRow(labelDisplayGammaExponent, dblSpinboxDisplayGammaExponent);
    groupboxCAM->setLayout(layoutCAM);


    groupboxCamShowMenu = new QGroupBox(tr("CAM Show Menu"));
    QHBoxLayout* layoutCamShowMenu = new QHBoxLayout;
    QVBoxLayout* layoutCamShowMenuLeft = new QVBoxLayout;
    QVBoxLayout* layoutCamShowMenuRight = new QVBoxLayout;
    chkbx_N_axes = new QCheckBox(tr("N Axes"));
    chkbx_L_axes = new QCheckBox(tr("L Axes"));
    chkbx_F_axes = new QCheckBox(tr("F Axes"));
    chkbx_B_axes = new QCheckBox(tr("B Axes"));
    chkbx_N_grid = new QCheckBox(tr("N Grid"));
    chkbx_L_grid = new QCheckBox(tr("L Grid"));
    chkbx_F_grid = new QCheckBox(tr("F Grid"));
    chkbx_B_grid = new QCheckBox(tr("B Grid"));
    chkbx_Gal_Grid = new QCheckBox(tr("Gal Grid"));
    chkbx_FOVs = new QCheckBox(tr("FOVs"));
    chkbx_ProxOps = new QCheckBox(tr("Prox Ops"));
    chkbx_TDRS = new QCheckBox(tr("TDRS"));
    chkbx_Shadows = new QCheckBox(tr("Shadows"));
    chkbx_AstroLabels = new QCheckBox(tr("Astro Labels"));
    chkbx_TruthVectors = new QCheckBox(tr("Truth Vectors"));
    chkbx_FSWVectors = new QCheckBox(tr("FSW Vectors"));
    chkbx_MilkyWay = new QCheckBox(tr("Milky Way"));
    chkbx_FermiSky = new QCheckBox(tr("Fermi Sky"));

    layoutCamShowMenuLeft->addWidget(chkbx_N_axes);
    layoutCamShowMenuLeft->addWidget(chkbx_L_axes);
    layoutCamShowMenuLeft->addWidget(chkbx_F_axes);
    layoutCamShowMenuLeft->addWidget(chkbx_B_axes);
    layoutCamShowMenuLeft->addWidget(chkbx_N_grid);
    layoutCamShowMenuLeft->addWidget(chkbx_L_grid);
    layoutCamShowMenuLeft->addWidget(chkbx_F_grid);
    layoutCamShowMenuLeft->addWidget(chkbx_B_grid);
    layoutCamShowMenuLeft->addWidget(chkbx_Gal_Grid);
    layoutCamShowMenuRight->addWidget(chkbx_FOVs);
    layoutCamShowMenuRight->addWidget(chkbx_ProxOps);
    layoutCamShowMenuRight->addWidget(chkbx_TDRS);
    layoutCamShowMenuRight->addWidget(chkbx_Shadows);
    layoutCamShowMenuRight->addWidget(chkbx_AstroLabels);
    layoutCamShowMenuRight->addWidget(chkbx_TruthVectors);
    layoutCamShowMenuRight->addWidget(chkbx_FSWVectors);
    layoutCamShowMenuRight->addWidget(chkbx_MilkyWay);
    layoutCamShowMenuRight->addWidget(chkbx_FermiSky);
    layoutCamShowMenu->addLayout(layoutCamShowMenuLeft, 1);
    layoutCamShowMenu->addLayout(layoutCamShowMenuRight,1);
    groupboxCamShowMenu->setLayout(layoutCamShowMenu);

    groupboxMap = new QGroupBox(tr("Map"));
    groupboxMap->setAlignment(Qt::AlignCenter);
    QFormLayout* layoutMap = new QFormLayout;
    labelMapTitle = new QLabel(tr("Title"));
    editMapTitle = new QLineEdit();
    groupboxMapWidthHeight = new QGroupBox(tr("Width, Height [pixels]"));
    QHBoxLayout* layoutMapWidthHeight = new QHBoxLayout;
    labelMapWidth = new QLabel(tr("Width"));
    spinboxMapWidth = new QSpinBox();
    spinboxMapWidth->setMaximum(INT_MAX);
    spinboxMapWidth->setMaximumWidth(120);
    labelMapHeight = new QLabel(tr("Height"));
    spinboxMapHeight = new QSpinBox();
    spinboxMapHeight->setMaximum(INT_MAX);
    spinboxMapHeight->setMaximumWidth(120);
    layoutMapWidthHeight->addWidget(labelMapWidth, 1);
    layoutMapWidthHeight->addWidget(spinboxMapWidth, 2);
    layoutMapWidthHeight->addWidget(labelMapHeight, 1);
    layoutMapWidthHeight->addWidget(spinboxMapHeight, 2);
    groupboxMapWidthHeight->setLayout(layoutMapWidthHeight);
    layoutMap->addRow(labelMapTitle, editMapTitle);
    layoutMap->addRow(groupboxMapWidthHeight);
    groupboxMap->setLayout(layoutMap);

    groupboxMapShowMenu = new QGroupBox(tr("MAP Show Menu"));
    groupboxMapShowMenu->setAlignment(Qt::AlignCenter);
    QHBoxLayout* layoutMapShowMenu = new QHBoxLayout;
    QVBoxLayout* layoutMapShowMenuLeft = new QVBoxLayout;
    QVBoxLayout* layoutMapShowMenuRight = new QVBoxLayout;
    chkbxClock = new QCheckBox(tr("Clock"));
    chkbxTlmClock = new QCheckBox(tr("Tlm Clock"));
    chkbxCredits = new QCheckBox(tr("Credits"));
    chkbxNight = new QCheckBox(tr("Night"));
    layoutMapShowMenuLeft->addWidget(chkbxClock, 1);
    layoutMapShowMenuLeft->addWidget(chkbxTlmClock, 1);
    layoutMapShowMenuRight->addWidget(chkbxCredits, 1);
    layoutMapShowMenuRight->addWidget(chkbxNight, 1);
    layoutMapShowMenu->addLayout(layoutMapShowMenuLeft, 1);
    layoutMapShowMenu->addLayout(layoutMapShowMenuRight,1);
    groupboxMapShowMenu->setLayout(layoutMapShowMenu);

    groupboxUnitSphereShowMenu = new QGroupBox(tr("Unit Sphere Show Menu"));
    groupboxUnitSphereShowMenu->setAlignment(Qt::AlignCenter);
    QVBoxLayout* layoutUnitSphereShowMenu = new QVBoxLayout;
    chkbxShowMajorConstellations = new QCheckBox(tr("Show Major Constellations"));
    chkbxShowZodiacConstellations = new QCheckBox(tr("Show Zodiac Constellations"));
    chkbxShowMinorConstellations = new QCheckBox(tr("Show Minor Constellations"));
    layoutUnitSphereShowMenu->addWidget(chkbxShowMajorConstellations);
    layoutUnitSphereShowMenu->addWidget(chkbxShowZodiacConstellations);
    layoutUnitSphereShowMenu->addWidget(chkbxShowMinorConstellations);
    layoutUnitSphereShowMenu->setAlignment(Qt::AlignHCenter);
    layoutUnitSphereShowMenu->setSpacing(30);
    groupboxUnitSphereShowMenu->setLayout(layoutUnitSphereShowMenu);

    QVBoxLayout* layoutWidgetPage1Left = new QVBoxLayout;
    layoutWidgetPage1Left->addWidget(groupboxConfiguration ,1);
    layoutWidgetPage1Left->addWidget(groupboxCAM, 1);
    layoutWidgetPage1->addLayout(layoutWidgetPage1Left, 1);
    layoutWidgetPage1->addWidget(groupboxCamShowMenu, 1);

    layoutWidgetPage2->addWidget(groupboxPOV);

    QHBoxLayout* layoutWidgetPage3Top = new QHBoxLayout;
    layoutWidgetPage3Top->addWidget(groupboxMap, 1);
    layoutWidgetPage3Top->addWidget(groupboxMapShowMenu,1);
    layoutWidgetPage3->addLayout(layoutWidgetPage3Top);
    layoutWidgetPage3->addWidget(groupboxUnitSphereShowMenu,1);

    widgetPage1->setLayout(layoutWidgetPage1);
    widgetPage2->setLayout(layoutWidgetPage2);
    widgetPage3->setLayout(layoutWidgetPage3);
    tabWidget->addTab(widgetPage1, tr("Graphics Configurations/CAM/CAM Show Menu"));
    tabWidget->addTab(widgetPage2, tr("POV"));
    tabWidget->addTab(widgetPage3, tr("Map/MAP Show Menu/Unit Sphere Show Menu"));
    layoutDialog->addWidget(labelMission);
    layoutDialog->addWidget(tabWidget);
    layoutDialog->addWidget(m_buttonBox);
    setLayout(layoutDialog);
}

void GraphicsDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void GraphicsDialog::createConnections()
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
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(comboboxHostType, &QComboBox::currentTextChanged,
            this, &GraphicsDialog::enableDisablePOVScScb);
    connect(comboboxTargetType, & QComboBox::currentTextChanged,
            this, &GraphicsDialog::enableDisablePOVScScb);

    connect(dblSpinboxGLOuputInterval, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editStarCatalogFileName, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxMapWindowExists, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxOrreyWindowExists, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxUnitSphereWindowExists, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxPauseAtStartup, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPOVMode, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxHostType, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPOVInitialHostSC, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPOVInitialHostSCB,&QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPOVInitialHostPOVFrame, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxTargetType, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPOVInitialTargetSC, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPOVInitialTargetSCB,&QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxPOVInitialTargetPOVFrame, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxBoresightAxis, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxUpAxis, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxInitialPOVRangeFromTarget, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxPOVAngleVertical, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxPOVPositionHostX1, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxPOVPositionHostX2, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxPOVPositionHostX3, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(comboboxInitialPOVView, &QComboBox::currentTextChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editCamTitle, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxCAMWidth, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxCAMHeight, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxMouseScaleFactor, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(dblSpinboxDisplayGammaExponent, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_N_axes, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_L_axes, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_F_axes, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_B_axes, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_N_grid, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_L_grid, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_F_grid, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_B_grid, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_Gal_Grid, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_FOVs, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_ProxOps, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_TDRS, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_Shadows, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_AstroLabels, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_TruthVectors, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_FSWVectors, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_MilkyWay, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbx_FermiSky, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editMapTitle, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxMapWidth, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(spinboxMapHeight, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxClock, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTlmClock, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxCredits, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxNight, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxShowMajorConstellations, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxShowZodiacConstellations, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxShowMinorConstellations, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void GraphicsDialog::enableDisablePOVScScb()
{
    if (comboboxHostType->currentText().trimmed().toUpper() != "SPACECRAFT" &&
            comboboxHostType->currentText().trimmed().toUpper() != "BODY")
    {
        comboboxPOVInitialHostSC->setCurrentText(tr(""));
        comboboxPOVInitialHostSC->setEnabled(false);
        comboboxPOVInitialHostSCB->setCurrentText(tr(""));
        comboboxPOVInitialHostSCB->setEnabled(false);
    }
    else
    {
        comboboxPOVInitialHostSC->setEnabled(true);
        comboboxPOVInitialHostSCB->setEnabled(true);
    }


    if (comboboxTargetType->currentText().trimmed().toUpper() != "SPACECRAFT" &&
            comboboxTargetType->currentText().trimmed().toUpper() != "BODY")
    {
        comboboxPOVInitialTargetSC->setCurrentText(tr(""));
        comboboxPOVInitialTargetSC->setEnabled(false);
        comboboxPOVInitialTargetSCB->setCurrentText(tr(""));
        comboboxPOVInitialTargetSCB->setEnabled(false);
    }
    else
    {
        comboboxPOVInitialTargetSC->setEnabled(true);
        comboboxPOVInitialTargetSCB->setEnabled(true);
    }
}
