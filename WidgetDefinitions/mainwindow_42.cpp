#include "WidgetHeaders/mainwindow_42.h"
#include "WidgetHeaders/tabs_42_gui.h"
#include "MVDheaders/qt42model.h"
#include "DataHeaders/qt42_headers.h"
#include "DataHeaders/missionholder.h"
#include "DataHeaders/mission.h"
#include "DataHeaders/orbittype.h"
#include "WidgetHeaders/spacecraftdialog.h"
#include "DataHeaders/spacecraft.h"
#include "WidgetHeaders/referenceorbitdialog.h"
#include "MVDheaders/qt42delegate.h"
#include "DataHeaders/inpsimterms.h"
#include "WidgetHeaders/inpsimtermswidgets.h"
#include "WidgetHeaders/fovdialog.h"
#include "WidgetHeaders/inpipcdialog.h"
#include "WidgetHeaders/graphicsdialog.h"
#include "WidgetHeaders/inptdrsdialog.h"
#include "WidgetHeaders/inpregiondialog.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QList>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QSplitter>
#include <QTreeView>
#include <QListView>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QAbstractItemModel>
#include <unistd.h>
#include <QCheckBox>
#include <QDockWidget>
#include <QFormLayout>
#include <QDialog>
#include <QPushButton>
#include <QDialogButtonBox>
#include <time.h>


//extern "C" int exec42(int argc, char** argv);

MainWindow_42::MainWindow_42(QWidget *parent)
    : QMainWindow(parent)
{
    //setWindowIcon(QIcon(""));
    //btnTest = new QPushButton(tr("test"),this);
    //btnTest->setIcon(QIcon("Qt42_Images/test.png"));
    //connect(btnTest, &QPushButton::clicked, this, &MainWindow_42::testFunctions);

    QSize minSize(800, 500);
    QSize maxSize(1200,800);
    setWindowTitle(title_42);
    setMinimumSize(minSize);
    setMaximumSize(maxSize);
    resize(minSize);
    createActions();
    createMenus();
    manageWindows();
    createToolBars();
    createStatusBar();
    createConnections();
}

MainWindow_42::~MainWindow_42(){}

void MainWindow_42::testFunctions()
{
}


void MainWindow_42::setupMVC()
{
    modelQt42 = new Qt42Model;
    qt42Delegate = new Qt42Delegate;
    viewListMissions = new QListView();
    viewTreeMissionSetUp = new QTreeView();

    viewListMissions = new QListView;
    viewListMissions->setModel(modelQt42);
    viewListMissions->setItemDelegate(qt42Delegate);
    viewListMissions->setSpacing(5);
    viewListMissions->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void MainWindow_42::closeTabs(const int& index){
    if (index == -1)
        return;
    //QWidget* widget = tabEditMission->widget(index);
    tabEditMission->removeTab(index);
}

void MainWindow_42::createActions()
{
    openAction = new QAction(tr("&Load a Mission"), this);
    openAction->setShortcut(tr(""));
    openAction->setIcon(QIcon("Qt42_Images/loadMission.png"));
    connect(openAction, &QAction::triggered , this, &MainWindow_42::openFile);

    newAction = new QAction(tr("New Mission"), this);
    newAction -> setShortcut(tr(""));
    newAction->setIcon(QIcon("Qt42_Images/newMission.png"));

    saveAction = new QAction(tr("Save..."),this);
    saveAction->setShortcut(tr(""));
    saveAction->setIcon(QIcon("Qt42_Images/saveMission.png"));
    connect(saveAction, &QAction::triggered, this, &MainWindow_42::saveFile);

    saveAsAction = new QAction(tr("&Save as..."));
    saveAsAction -> setShortcut(tr(""));
    saveAsAction->setIcon(QIcon("Qt42_Images/saveAsMission.png"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow_42::saveAsFile);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction -> setShortcut(tr(""));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    runSimuaionAction = new QAction(tr("Run"), this);
    runSimuaionAction->setIcon(QIcon("Qt42_Images/run.png"));
    runSimuaionAction->setToolTip(tr("Run/Resume the missions selected in the Mission Tab."));

    connect(runSimuaionAction, &QAction::triggered, this, &MainWindow_42::run42);

    stopSimulationAction = new QAction(tr("Stop"), this);
    stopSimulationAction->setIcon(QIcon("Qt42_Images/stop.png"));
    stopSimulationAction->setToolTip(tr("Stop the missions selected in the Mission Tab."));

    pauseSimulationAction = new QAction(tr("Pause"), this);
    pauseSimulationAction->setIcon(QIcon("Qt42_Images/pause.png"));
    pauseSimulationAction->setToolTip("Pause the missions selected in the Mission Tab.");

    listActionsFileMenu = {openAction, newAction, saveAction, saveAsAction, exitAction};
}

void MainWindow_42::showDialogDeveloperInfo()
{
    QString infomation = tr("******* ") + title_42 + tr(" ******\n\n") +
            tr("Developer: Yu Tso (左 昀)\n\n") +
            //tr("PTT ID: skyconquer\n\n") +
            tr("SourceForge Username: ytroy\n\n") +
            tr("Email: whiteroy2008@gmail.com");

    QDialog* dialogDeveloperInfo = new QDialog(this);
    dialogDeveloperInfo->setMinimumSize(500,300);
    dialogDeveloperInfo->setWindowTitle(tr("Developer Information"));
    QDialogButtonBox* btnBox = new QDialogButtonBox(QDialogButtonBox::Close, dialogDeveloperInfo);
    QTextEdit* textEdit = new QTextEdit(dialogDeveloperInfo);
    textEdit->setText(infomation);
    //textEdit->selectAll();
    //textEdit->setFontPointSize(24);
    textEdit->setReadOnly(true);
    QVBoxLayout* layoutDialogDeveloperInfo = new QVBoxLayout;
    layoutDialogDeveloperInfo->addWidget(textEdit);
    layoutDialogDeveloperInfo->addWidget(btnBox);
    dialogDeveloperInfo->setLayout(layoutDialogDeveloperInfo);
    connect(btnBox, &QDialogButtonBox::rejected, dialogDeveloperInfo, &QDialogButtonBox::close);
    dialogDeveloperInfo->exec();

    delete layoutDialogDeveloperInfo;
    delete textEdit;
    delete btnBox;
    delete dialogDeveloperInfo;
}

void MainWindow_42::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu -> addActions(listActionsFileMenu);

  editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu -> addActions(listActionsEditMenu);

  plotMenu = menuBar()->addMenu(tr("&Plot"));
  helpMenu = menuBar()->addMenu(tr("&Help"));

  infoAction = menuBar()->addAction(tr("&Info"), this ,&MainWindow_42::showDialogDeveloperInfo);
  infoAction->setStatusTip(tr("Information of the developer"));
}

void MainWindow_42::manageWindows()
{
    QList<int> sizeHorizontal;
    sizeHorizontal << 100 << 450;

    QList<int> sizeVertical;
    sizeVertical << 600 << 120;
    scrollareaEditMission = new QScrollArea;
    //scrollareaSelectMission = new QScrollArea;
    tabEditMission = new QTabWidget();
    tabEditMission->setMinimumWidth(1300);
    tabEditMission->setMinimumHeight(750);

    tabEditMission->setTabsClosable(true);
    tabEditMission->setMovable(true);
    tabEditMission->setUsesScrollButtons(true);

    connect(tabEditMission, &QTabWidget::tabCloseRequested,
            this, &MainWindow_42::closeTabs);


    //********* We have to add an empty widget to tabEditMission before
    // adding tabEditMission to another widget; otherwise, the dynamically added
    // widget (ex: SpacecraftDialog, referenceOrbitDialog) can't display.
    spacecraftdialog = new SpacecraftDialog(tabEditMission);
    referenceorbitdialog = new ReferenceOrbitDialog(tabEditMission);
    inpSimSimCtrlDialog = new InpSimSimCtrlDialog(tabEditMission);
    inpSimOrbitSCSetDialog = new InpSimOrbitSCSetDialog(tabEditMission);
    inpSimEnvironmentDialog = new InpSimEnvironmentDialog(tabEditMission);
    inpSimCelestialBodyDialog = new InpSimCelestialBodyDialog(tabEditMission);
    inpSimLagrangePointSystemsDialog = new InpSimLagrangePointSystemsDialog(tabEditMission);
    inpSimGroundStationDialog = new InpSimGroundStationDialog(tabEditMission);
    inpRegionDialog = new InpRegionDialog(tabEditMission);
    fOVDialog = new FOVDialog(tabEditMission);
    inpIpcDialog = new InpIpcDialog(tabEditMission);
    graphicsDialog = new GraphicsDialog(tabEditMission);
    inpTDRsDialog = new InpTDRsDialog(tabEditMission);
    tabEditMission->addTab(spacecraftdialog, tr("Spacecraft"));

    scrollareaEditMission->setWidget(tabEditMission);

    splitterMainwindow = new QSplitter(this);
    splitterMainwindow->setChildrenCollapsible(true);
    splitterMissionGraphics = new QSplitter(splitterMainwindow);
    splitterMissionGraphics->setChildrenCollapsible(true);
    createMissionTree();

    splitterMissionGraphics->addWidget(tabWidgetMission);
    //scrollareaSelectMission->setWidget(tabWidgetMission);
    //splitterMissionGraphics->addWidget(scrollareaSelectMission);

    splitterMissionGraphics->addWidget(scrollareaEditMission);
    splitterMissionGraphics->setSizes(sizeHorizontal);
    messageText = new QTextEdit(splitterMainwindow);
    messageText->setReadOnly(true);
    messageText->append(developerInfo);

    splitterMainwindow->setOrientation(Qt::Vertical);
    splitterMainwindow->setSizes(sizeVertical);
    setCentralWidget(splitterMainwindow);

    tabEditMission->removeTab(tabEditMission->indexOf(spacecraftdialog));
}

void MainWindow_42::createToolBars()
{
    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);
    fileToolBar->addAction((newAction));
    fileToolBar->setIconSize(QSize(35,35));

    QToolBar *simulationToolBar = addToolBar(tr("Simulation"));
    simulationToolBar->addAction(runSimuaionAction);
    simulationToolBar->addAction(pauseSimulationAction);
    simulationToolBar->addAction(stopSimulationAction);
    simulationToolBar->setIconSize(QSize(35,35));

    QToolBar* testToolBar = addToolBar(tr("TEST"));
    testToolBar->addWidget(btnTest);

}

void MainWindow_42::createStatusBar()
{
   statusbar = statusBar();
   QLabel *locationLabel = new QLabel(" Status: \n", this);
   statusbar -> addWidget(locationLabel);
}

void MainWindow_42::openFile()
{
    QFileDialog fileDialogOpen(this);
    fileDialogOpen.setOption(QFileDialog::DontUseNativeDialog, true);
    fileDialogOpen.setNameFilter(tr("Mission file (*.mission)"));
    QString fileWithDirectory = fileDialogOpen.getOpenFileName(this, tr("Load Mission File"), QString(),
                                                             tr("Mission File (*.") + missionFileType+tr(")"));

    // In Linux:
    QString fileName = fileWithDirectory.trimmed().split("/").last();
    // In Windows:
    //QString fileName = fileWithDirectory.split("\").last();
    QString missionName = fileName.trimmed().split(".")[0].trimmed();


    if (!fileName.isEmpty())
    {
        QFile fileReadIn(fileWithDirectory);
        fileReadIn.open(QIODevice::ReadWrite);
        QDataStream in(&fileReadIn);
        in.setVersion(QDataStream::Qt_5_12);

        Mission missionReadIn;
        in >> missionReadIn;
        missionReadIn.rename(missionName);
        QString fileDirectory = fileWithDirectory.remove(tr("/")+fileName);
        missionReadIn.setDirectroy(fileDirectory);

        bool missionExisting = false;
        for (int i = 0; i < modelQt42->numberOfMission(); ++i)
        {
            Mission existingMission = modelQt42->index(i, 0, QModelIndex()).data().value<Mission>();
            if (missionReadIn.name() == existingMission.name())
            {
                QMessageBox* msg = new QMessageBox(this);
                msg->setIcon(QMessageBox::Warning);
                msg->setWindowTitle(tr("Loaded Mission Already Existed"));
                msg->setText(tr("\"") + missionName + tr("\" already existed."));
                msg->exec();

                missionExisting = true;
                break;
            }
        }
        if (!missionExisting)
        {
            int numberOfMission = modelQt42->numberOfMission();
            modelQt42->insertRows(numberOfMission, numberOfMission, QModelIndex());
            QVariant newData = QVariant();
            newData.setValue(missionReadIn);
            QModelIndex modelIndexMission = modelQt42->index(numberOfMission, 0, QModelIndex());
            //modelQt42->setData(modelIndexMission, newData);
            modelQt42->loadMission(modelIndexMission, newData);

        }
        fileReadIn.flush();
        fileReadIn.close();

    }
    else qDebug() << "No file is selected.";
}

void MainWindow_42::saveFile()
{
    QModelIndexList selectedMissionList = viewListMissions->selectionModel()->selectedIndexes();
    if (selectedMissionList.size())
    {
        for (int i = 0; i < selectedMissionList.size(); ++i)
        {
            QFile fileWriteTo;
            bool writeFile = true;
            QString saveDirectoryWithFileName = QString();
            Mission selectedMission = selectedMissionList[i].data().value<Mission>();
            QString missionName = selectedMission.name();
            QString saveDirectory = selectedMission.directory().trimmed();
            bool directoryNotSpecifiedByMission = saveDirectory.isEmpty();

            saveDirectoryWithFileName = saveDirectory + tr("/") + missionName + tr(".") + missionFileType;
            fileWriteTo.setFileName(saveDirectoryWithFileName);

            if (directoryNotSpecifiedByMission){
                QFileDialog fileDialogSave(this);
                fileDialogSave.setOption(QFileDialog::DontUseNativeDialog,true);
                // QFileDialog::setOption(QFileDialog::DontUseNativeDialog,true) is for adjusting the size of QFileDialog.
                saveDirectory = fileDialogSave.getExistingDirectory(this);
                if (saveDirectory.isEmpty())
                    continue;
                // If "saveDirectory.isEmpty()" is true, then it means that the user cancels savfing files.
                saveDirectoryWithFileName = saveDirectory + tr("/") + missionName + tr(".") + missionFileType;
                fileWriteTo.setFileName(saveDirectoryWithFileName);
                if (fileWriteTo.exists()){
                    QMessageBox* msg = new QMessageBox(this);
                    msg->setIcon(QMessageBox::Information);
                    msg->setWindowTitle(tr("The File Already Exists."));
                    msg->setText(tr("Mission \"") + missionName + tr("\" already exists\n") +
                                 tr("in the location \"") + saveDirectory + tr("\"") +
                                 tr("\nDo you want to replace it?"));
                    msg->setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
                    int exc = msg->exec();
                    switch(exc)
                    {
                    case QMessageBox::Cancel:
                        msg->close();
                        writeFile = false;
                        break;
                    case QMessageBox::Yes:
                        msg->close();
                        break;
                    }
                }
            }

            else
            {
                if (!fileWriteTo.exists())
                {
                    QMessageBox* msg = new QMessageBox(this);
                    msg->setIcon(QMessageBox::Information);
                    msg->setWindowTitle(tr("The File Already Exists."));
                    msg->setText(tr("Mission \"") + missionName + tr("\"") +
                                 tr(" in the location: \n") + tr("\"") + saveDirectory + tr("\"") + tr("\nis lost.") +
                                 tr("\nDo you want to create and save the current one?"));
                    msg->setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
                    int exc = msg->exec();
                    switch(exc)
                    {
                    case QMessageBox::Cancel:
                        msg->close();
                        writeFile = false;
                        break;
                    case QMessageBox::Yes:
                        msg->close();
                        break;
                    }
                }
            }

            if (writeFile)
            {
                QVariant savedData = QVariant();
                selectedMission.setDirectroy(saveDirectory);
                savedData.setValue(selectedMission);

                modelQt42->setData(selectedMissionList[i], savedData);

                fileWriteTo.open(QIODevice::WriteOnly);
                QDataStream out(&fileWriteTo);
                out << selectedMission;
                fileWriteTo.close();

            }
        }
    }
    else
    {
        QMessageBox* msg = new QMessageBox(this);
        msg->setIcon(QMessageBox::Warning);
        msg->setWindowTitle(tr("No Mission is Selected"));
        msg->setText(tr("Please select at least one mission."));
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        return;
    }
}

void MainWindow_42::createMissionTree()
{
    tabWidgetMission = new QTabWidget(this);
    setupMVC();
    tab_mission = new Tab_Mission(tabWidgetMission);
    QVBoxLayout* layout_mission = new QVBoxLayout;
    layout_mission->addWidget(viewListMissions);
    tab_mission->setLayout(layout_mission);

    tab_missionSetup = new Tab_MissionSetUp(tabWidgetMission);
    QVBoxLayout* layout_missionSetup = new QVBoxLayout;
    layout_missionSetup->addWidget(viewTreeMissionSetUp);
    tab_missionSetup->setLayout(layout_missionSetup);

    tab_missionOutput = new Tab_MissionOutput(tabWidgetMission);
    tabWidgetMission->addTab(tab_mission, tr("Missions"));
    tabWidgetMission->addTab(tab_missionSetup, tr("Mission Setup"));
    tabWidgetMission->addTab(tab_missionOutput, tr("Mission Output"));

}

void MainWindow_42::saveAsFile()
{
    QModelIndexList selectedMissionList = viewListMissions->selectionModel()->selectedIndexes();
    if (selectedMissionList.size())
    {
        for (int i = 0; i < selectedMissionList.size(); ++i)
        {
            QString saveDirectoryWithFileName = QString();
            Mission selectedMission = selectedMissionList[i].data().value<Mission>();
            QString missionName = selectedMission.name();
            QString saveDirectory = QString();
            QFileDialog fileDialogSave(this);
            fileDialogSave.setOption(QFileDialog::DontUseNativeDialog,true);
            // QFileDialog::setOption(QFileDialog::DontUseNativeDialog,true) is for adjusting the size of QFileDialog.
            saveDirectory = fileDialogSave.getExistingDirectory(this);
            saveDirectoryWithFileName = saveDirectory + tr("/") + missionName + tr(".") + missionFileType;
            QFile fileWriteTo(saveDirectoryWithFileName);
            QDataStream out(&fileWriteTo);

            if(fileWriteTo.exists())
            {
                QMessageBox* msg = new QMessageBox(this);
                msg->setWindowTitle(tr("File Already Existed"));
                msg->setStandardButtons(QMessageBox::Yes |
                                        QMessageBox::Cancel);
                msg->setIcon(QMessageBox::Information);
                msg->setText(tr("Mission \"") + missionName + tr("\" already exists\nin location \"")
                             + saveDirectory + tr("\".") + tr("\nDo you want to replace it?"));
                int exe = msg->exec();
                switch (exe){
                case QMessageBox::Cancel:
                    msg->close();
                    break;
                case QMessageBox::Yes:
                    fileWriteTo.open(QIODevice::WriteOnly);
                    selectedMission.setDirectroy(saveDirectory);
                    out << selectedMission;
                    fileWriteTo.flush();
                    fileWriteTo.close();
                    break;
                }
            }
            else
            {
                fileWriteTo.open(QIODevice::WriteOnly);
                selectedMission.setDirectroy(saveDirectory);
                out << selectedMission;
                fileWriteTo.flush();
                fileWriteTo.close();
            }
            QVariant savedData = QVariant();
            savedData.setValue(selectedMission);
            modelQt42->setData(selectedMissionList[i], savedData);
        }
    }
    else
    {
        QMessageBox* msg = new QMessageBox(this);
        msg->setIcon(QMessageBox::Warning);
        msg->setWindowTitle(tr("No Mission is Selected"));
        msg->setText(tr("Please select at least one mission."));
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        return;
    }
}

void MainWindow_42::createConnections()
{
    connect(newAction, &QAction::triggered, modelQt42,
            [=](){ int position = modelQt42->numberOfMission();
        modelQt42->insertRows(position, position, QModelIndex());});
    connect(qt42Delegate, &Qt42Delegate::missionSelected,
            this, &MainWindow_42::showMissionSelected);
    connect(qt42Delegate, &Qt42Delegate::missionSelected,
            this, &MainWindow_42::closeTabsWhenSelectingMission);
    connect(qt42Delegate, &Qt42Delegate::spacecraftSelected,
            this, &MainWindow_42::buildSpacecraftDialog);
    connect(qt42Delegate, &Qt42Delegate::orbitSelected,
            this, &MainWindow_42::buildReferenceOrbitDialog);
    connect(qt42Delegate, &Qt42Delegate::InpSimParameterSelected,
            this, &MainWindow_42::buildInpSimSimCtrlDialog);
    connect(qt42Delegate, &Qt42Delegate::InpSimParameterSelected,
            this, &MainWindow_42::buildInpSimOrbitSCSetDialog);
    connect(qt42Delegate, &Qt42Delegate::InpSimParameterSelected,
            this, &MainWindow_42::buildInpSimEnvironmentDialog);
    connect(qt42Delegate, &Qt42Delegate::InpSimParameterSelected,
            this, &MainWindow_42::buildInpSimCelestialBodyDialog);
    connect(qt42Delegate, &Qt42Delegate::InpSimParameterSelected,
            this, &MainWindow_42::buildInpSimLagrangePointSystemsDialog);
    connect(qt42Delegate, &Qt42Delegate::InpSimParameterSelected,
            this, &MainWindow_42::buildInpSimGroundStationDialog);
    connect(qt42Delegate, &Qt42Delegate::FOVHeadserSelected,
            this, &MainWindow_42::buildFOVHeaderDialog);
    connect(qt42Delegate, &Qt42Delegate::InpIpcHeaderSelected,
            this, &MainWindow_42::buildInpIpcDialog);
    connect(qt42Delegate, &Qt42Delegate::GraphicsHeaderSelected,
            this, &MainWindow_42::buildGraphicsDialog);
    connect(qt42Delegate, &Qt42Delegate::InpTDRsSelected,
            this, &MainWindow_42::buildInpTDRsDialog);
    connect(qt42Delegate, &Qt42Delegate::RegionHeaderSelected,
            this, &MainWindow_42::buildRegionDialog);

    connect(qt42Delegate, &Qt42Delegate::removeObject,
            this, &MainWindow_42::closeTabsByType);
    connect(viewListMissions, &QListView::clicked, this,
            [=](){missionSelectedChanged();});
    connect(qt42Delegate, &Qt42Delegate::removeMission, this,
            &MainWindow_42::removeMission);
    connect(modelQt42, &QAbstractItemModel::dataChanged, this, [=](){hideSCcomponentsForAll();});
    connect(modelQt42, &QAbstractItemModel::columnsMoved, this, [=](){hideSCcomponentsForAll();});
    connect(modelQt42, &QAbstractItemModel::columnsRemoved, this, [=](){hideSCcomponentsForAll();});
    connect(modelQt42, &QAbstractItemModel::columnsInserted, this, [=](){hideSCcomponentsForAll();});
    connect(modelQt42, &QAbstractItemModel::rowsMoved, this, [=](){hideSCcomponentsForAll();});
    connect(modelQt42, &QAbstractItemModel::rowsRemoved, this, [=](){hideSCcomponentsForAll();});
    connect(modelQt42, &QAbstractItemModel::rowsInserted, this, [=](){hideSCcomponentsForAll();});
}

void MainWindow_42::closeTabsWhenSelectingMission()
{
    for (int indexTab = tabEditMission->count()-1; indexTab > -1; --indexTab)
        tabEditMission->removeTab(indexTab);
}

void MainWindow_42::missionSelectedChanged()
{
    //qDebug() << viewListMissions->selectionModel()->selectedIndexes().size();
}

void MainWindow_42::showMissionSelected(QAbstractItemModel* model, const QModelIndex& index)
{
    if (model)
        modelQt42 = static_cast<Qt42Model*>(model);
    else
    {
        modelQt42->disconnect(this);
    }
    if (!model->hasIndex(index.row(),index.column(), QModelIndex()))
        return;
    viewTreeMissionSetUp->setModel(modelQt42);
    viewTreeMissionSetUp->setItemDelegate(qt42Delegate);
    viewTreeMissionSetUp->setRootIndex(index);
    viewTreeMissionSetUp->hideColumn(1);
    viewTreeMissionSetUp->setHeaderHidden(true);
    viewTreeMissionSetUp->setAnimated(true);
    viewTreeMissionSetUp->setIndentation(35);
    viewTreeMissionSetUp->setColumnWidth(0, 350);
    tabWidgetMission->setCurrentWidget(tab_missionSetup);
    hideSCcomponents(index);

    // QTreeView::setColumnWidth() needs to be called after setting the model, so the horizontal scroll bar will be available;
    //viewTreeMissionSetUp->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}


void MainWindow_42::hideSCcomponents(const QModelIndex& index)
{
    if (!index.isValid() || !index.data().canConvert<Mission>())
        return;
    QModelIndex indexSCH = modelQt42->index(0, 0, index);
    SpacecraftHeader SCH = indexSCH.data().value<SpacecraftHeader>();
    int numberOfSpacecraft = SCH.numberOfSpacecraft();
    for (int rowSC = numberOfSpacecraft-1; rowSC > -1; --rowSC)
    {
        QModelIndex indexSC = modelQt42->index(rowSC, 0, indexSCH);
        int numberOfSpacecraftRow = SCH.spacecraft(rowSC)->numberOfRow();
        for (int rowSCc = numberOfSpacecraftRow -1; rowSCc > -1; --rowSCc)
            viewTreeMissionSetUp->setRowHidden(rowSCc, indexSC, true);
    }

    Mission m = index.data().value<Mission>();
}

void MainWindow_42::hideSCcomponentsForAll()
{
    for (int indexMission = 0; indexMission < modelQt42->numberOfMission(); ++indexMission)
    {
        QModelIndex modelIndexMission = modelQt42->index(indexMission, 0, QModelIndex());
        hideSCcomponents(modelIndexMission);
    }
}

void MainWindow_42::buildSpacecraftDialog(QAbstractItemModel* model, const QModelIndex& index)
{
    if (tabEditMission->indexOf(spacecraftdialog) < 0)
    {
        tabEditMission->addTab(spacecraftdialog, tr("Spacecraft"));
    }
    spacecraftdialog->setModel(model);
    spacecraftdialog->setRootIndex(index);
    spacecraftdialog->moveToFirstPage();
    tabEditMission->setCurrentWidget(spacecraftdialog);
}

void MainWindow_42::buildReferenceOrbitDialog(QAbstractItemModel* model, const QModelIndex& index)
{
    if (tabEditMission->indexOf(referenceorbitdialog) < 0)
    {
        tabEditMission->addTab(referenceorbitdialog, tr("Orbit"));
    }
    referenceorbitdialog->setModel(model);
    referenceorbitdialog->setRootIndex(index);
    referenceorbitdialog->moveToFirstPage();
    tabEditMission->setCurrentWidget(referenceorbitdialog);
}

void MainWindow_42::buildInpSimSimCtrlDialog(QAbstractItemModel* model, const QModelIndex& index)
{
    if (model && index.data().canConvert<InpSimSimulationControl>())
    {
        if (tabEditMission->indexOf(inpSimSimCtrlDialog) < 0)
            tabEditMission->addTab(inpSimSimCtrlDialog, tr("Simulation Control"));
        inpSimSimCtrlDialog->setModel(model);
        inpSimSimCtrlDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpSimSimCtrlDialog);
    }
}

void MainWindow_42::buildInpSimOrbitSCSetDialog(QAbstractItemModel* model, const QModelIndex& index)
{
    if (model && index.data().canConvert<InpSimOrbitSCSet>())
    {
        if (tabEditMission->indexOf(inpSimOrbitSCSetDialog) < 0)
            tabEditMission->addTab(inpSimOrbitSCSetDialog, tr("Orbit-Spacecraft Sets"));
        inpSimOrbitSCSetDialog->setModel(model);
        inpSimOrbitSCSetDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpSimOrbitSCSetDialog);
    }
}

void MainWindow_42::buildInpSimEnvironmentDialog(QAbstractItemModel* model,
                                                 const QModelIndex& index)
{
    if (model && index.data().canConvert<InpSimEnvironment>())
    {
        if (tabEditMission->indexOf(inpSimEnvironmentDialog) < 0)
            tabEditMission->addTab(inpSimEnvironmentDialog, tr("Environment"));
        inpSimEnvironmentDialog->setModel(model);
        inpSimEnvironmentDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpSimEnvironmentDialog);
    }
}

void MainWindow_42::buildInpSimCelestialBodyDialog(QAbstractItemModel* model,
                                                   const QModelIndex& index)
{
    if (model && index.data().canConvert<InpSimCelestialBody>())
    {
        if (tabEditMission->indexOf(inpSimCelestialBodyDialog) < 0)
            tabEditMission->addTab(inpSimCelestialBodyDialog, tr("Celestial Bodies"));
        inpSimCelestialBodyDialog->setModel(model);
        inpSimCelestialBodyDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpSimCelestialBodyDialog);
    }
}

void MainWindow_42::buildInpSimLagrangePointSystemsDialog(QAbstractItemModel* model,
                                                          const QModelIndex& index)
{
    if (model && index.data().canConvert<InpSimLagrangePointSystem>())
    {
        if (tabEditMission->indexOf(inpSimLagrangePointSystemsDialog) < 0)
            tabEditMission->addTab(inpSimLagrangePointSystemsDialog, tr("Lagrange Point Systems"));
        inpSimLagrangePointSystemsDialog->setModel(model);
        inpSimLagrangePointSystemsDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpSimLagrangePointSystemsDialog);
    }
}

void MainWindow_42::buildInpSimGroundStationDialog(QAbstractItemModel* model,
                                                   const QModelIndex& index)
{
    if (model && index.data().canConvert<InpSimGroundStation>())
    {
        if (tabEditMission->indexOf(inpSimGroundStationDialog) < 0)
            tabEditMission->addTab(inpSimGroundStationDialog, tr("Ground Stations"));
        inpSimGroundStationDialog->setModel(model);
        inpSimGroundStationDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpSimGroundStationDialog);
    }
}

void MainWindow_42::buildFOVHeaderDialog(QAbstractItemModel* model,
                                         const QModelIndex& index)
{
    if (model && index.data().canConvert<FOVHeader>())
    {
        if (tabEditMission->indexOf(fOVDialog) < 0)
            tabEditMission->addTab(fOVDialog, tr("Fields of View"));
        fOVDialog->setModel(model);
        fOVDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(fOVDialog);
    }
}

void MainWindow_42::buildInpIpcDialog(QAbstractItemModel* model,
                                      const QModelIndex& index)
{
    if (model && index.data().canConvert<InpIPCHeader>())
    {
        if (tabEditMission->indexOf(inpIpcDialog) < 0)
            tabEditMission->addTab(inpIpcDialog, tr("Interprocess Communication"));
        inpIpcDialog->setModel(model);
        inpIpcDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpIpcDialog);
    }
}

void MainWindow_42::buildGraphicsDialog(QAbstractItemModel* model,
                                        const QModelIndex& index)
{
    if (model && index.data().canConvert<GraphicsHeader>())
    {

        if (tabEditMission->indexOf(graphicsDialog) < 0)
            tabEditMission->addTab(graphicsDialog, tr("Graphics"));
        graphicsDialog->setModel(model);
        graphicsDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(graphicsDialog);
    }
}

void MainWindow_42::buildInpTDRsDialog(QAbstractItemModel* model,
                                       const QModelIndex& index)
{
    if (model && index.data().canConvert<InpTDRs>())
    {
        if (tabEditMission->indexOf(inpTDRsDialog) < 0)
            tabEditMission->addTab(inpTDRsDialog, tr("TDRs"));
        inpTDRsDialog->setModel(model);
        inpTDRsDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpTDRsDialog);
    }
}

void MainWindow_42::buildRegionDialog(QAbstractItemModel* model,
                                      const QModelIndex& index)
{
    if (model && index.data().canConvert<RegionHeader>())
    {
        if (tabEditMission->indexOf(inpRegionDialog) < 0)
            tabEditMission->addTab(inpRegionDialog, tr("Regions"));
        inpRegionDialog->setModel(model);
        inpRegionDialog->setRootIndex(index);
        tabEditMission->setCurrentWidget(inpRegionDialog);
    }
}

void MainWindow_42::closeTabsByType(QAbstractItemModel* model, const QModelIndex& modelindex)
{
    Q_UNUSED(model)
    if (!modelindex.isValid())
        return;
    if (modelindex.data().canConvert<Spacecraft>())
        if (tabEditMission->indexOf(spacecraftdialog) > -1)
            tabEditMission->removeTab(tabEditMission->indexOf(spacecraftdialog));
    if (modelindex.data().canConvert<Orbit>())
        if (tabEditMission->indexOf(referenceorbitdialog) > -1)
            tabEditMission->removeTab(tabEditMission->indexOf(referenceorbitdialog));
}

void MainWindow_42::removeMission(const int& row)
{
    tabEditMission->removeTab(tabEditMission->indexOf(spacecraftdialog));
    spacecraftdialog->setModel(nullptr);
    spacecraftdialog->setRootIndex(QModelIndex());

    tabEditMission->removeTab(tabEditMission->indexOf(referenceorbitdialog));
    referenceorbitdialog->setModel(nullptr);
    referenceorbitdialog->setRootIndex(QModelIndex());

    tabEditMission->removeTab(tabEditMission->indexOf(inpSimSimCtrlDialog));
    inpSimSimCtrlDialog->setModel(nullptr);
    inpSimSimCtrlDialog->setRootIndex(QModelIndex());

    tabEditMission->removeTab(tabEditMission->indexOf(inpSimEnvironmentDialog));
    inpSimEnvironmentDialog->setModel(nullptr);
    inpSimEnvironmentDialog->setRootIndex(QModelIndex());

    tabEditMission->removeTab(tabEditMission->indexOf(inpSimCelestialBodyDialog));
    inpSimCelestialBodyDialog->setModel(nullptr);
    inpSimCelestialBodyDialog->setRootIndex(QModelIndex());

    tabEditMission->removeTab(tabEditMission->indexOf(inpSimLagrangePointSystemsDialog));
    inpSimLagrangePointSystemsDialog->setModel(nullptr);
    inpSimLagrangePointSystemsDialog->setRootIndex(QModelIndex());

    tabEditMission->removeTab(tabEditMission->indexOf(inpSimGroundStationDialog));
    inpSimGroundStationDialog->setModel(nullptr);
    inpSimGroundStationDialog->setRootIndex(QModelIndex());

    tabEditMission->removeTab(tabEditMission->indexOf(fOVDialog));
    fOVDialog->setModel(nullptr);
    fOVDialog->setRootIndex(QModelIndex());

    tabEditMission->removeTab(tabEditMission->indexOf(inpIpcDialog));
    inpIpcDialog->setModel(nullptr);
    inpIpcDialog->setRootIndex(QModelIndex());

    viewTreeMissionSetUp->setModel(nullptr);
    modelQt42->removeRows(row, row, QModelIndex());
}

void MainWindow_42::run42()
{
    char* a = "a";
    char* b = "b";
    char* c[] = {a,b};
    //exec42(0,c);
}
