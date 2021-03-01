#ifndef MAINWINDOW_42_H
#define MAINWINDOW_42_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDebug>
#include "ShareHeaders/qt42_sharedparameters.h"
class QMenu;
class QPushButton;
class QStatusBar;
class QTabWidget;
class QLineEdit;
class QTextEdit;
class QSplitter;
class QScrollArea;
class QVBoxLayout;
class Qt42Model;
class Qt42Delegate;
class QTreeView;
class QColumnView;
class QListView;
class Tab_Mission;
class Tab_MissionSetUp;
class Tab_MissionOutput;
class QAbstractItemModel;
class SpacecraftDialog;
class ReferenceOrbitDialog;
class InpSimSimCtrlDialog;
class InpSimOrbitSCSetDialog;
class InpSimEnvironmentDialog;
class InpSimCelestialBodyDialog;
class InpSimLagrangePointSystemsDialog;
class InpSimGroundStationDialog;
class FOVDialog;
class InpIpcDialog;
class GraphicsDialog;
class QUndoStack;
class QDialog;
class InpTDRsDialog;
class InpRegionDialog;


class MainWindow_42 : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow_42(QWidget *parent = nullptr);
   ~MainWindow_42() override;

   void closeEvent(QCloseEvent* event) override
   {
   }


private:
   const QString missionFileType = "mission";
   QUndoStack* m_undoStack;
   QAction* m_renameCommand;
   QAction* m_undoRenameCommand;

   void createActions();
   void createMenus();
   void createToolBars();
   void createStatusBar();
   void createMissionTree();
   void manageWindows();
   void setupMVC();
   void createConnections();
   void showDialogDeveloperInfo();

    /***    Model/View/Delegate    ***/
    Qt42Model* modelQt42;
    QListView* viewListMissions;
    QTreeView* viewTreeMissionSetUp;
    //QColumnView* viewColumn;
    Qt42Delegate* qt42Delegate;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* plotMenu;
    QMenu* toolMenu;
    QMenu* helpMenu;
    //QMenu* infoMenu;

    QAction* openAction;
    QAction* newAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* exitAction;
    QAction* runSimuaionAction;
    QAction* stopSimulationAction;
    QAction* pauseSimulationAction;
    QAction* infoAction;

    /*    The QLists are for holdind the QActions for each menu.   */
    QList <QAction*> listActionsFileMenu;
    QList <QAction*> listActionsEditMenu;
    QList <QAction*> plotMenu_acts;
    QList <QAction*> toolMenu_acts;
    QList <QAction*> helpMenu_acts;
    QList <QAction*> infoMenu_acts;
    /*    End of QLists.   */

    QStatusBar* statusbar;
    QSplitter* splitterMissionGraphics;
    QSplitter* splitterMainwindow;
    QTabWidget* tabWidgetMission;
    //QScrollArea* scrollareaSelectMission;
    QScrollArea* scrollareaEditMission;
    QTabWidget* tabEditMission;

    QTextEdit* messageText;
    const QString title_42 = appName;

    const QString developerInfo = "*** \"" + title_42 +  "\" is developed and maintained by Yu Tso (Roy) 左 昀 ***";

    Tab_Mission*       tab_mission;
    Tab_MissionSetUp*  tab_missionSetup;
    Tab_MissionOutput* tab_missionOutput;
    SpacecraftDialog* spacecraftdialog;
    ReferenceOrbitDialog* referenceorbitdialog;
    InpSimSimCtrlDialog* inpSimSimCtrlDialog;
    InpSimOrbitSCSetDialog* inpSimOrbitSCSetDialog;
    InpSimEnvironmentDialog* inpSimEnvironmentDialog;
    InpSimCelestialBodyDialog* inpSimCelestialBodyDialog;
    InpSimLagrangePointSystemsDialog* inpSimLagrangePointSystemsDialog;
    InpSimGroundStationDialog* inpSimGroundStationDialog;
    FOVDialog* fOVDialog;
    InpIpcDialog* inpIpcDialog;
    GraphicsDialog* graphicsDialog;
    InpTDRsDialog* inpTDRsDialog;
    InpRegionDialog* inpRegionDialog;
    QPushButton* btnTest;

    void testFunctions();

private slots:
    void openFile();
    void saveFile();
    void saveAsFile();
    void closeTabs(const int& index);
    void closeTabsByType(QAbstractItemModel* model, const QModelIndex& modelindex);
    void showMissionSelected(QAbstractItemModel* model, const QModelIndex& index);
    void buildSpacecraftDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildReferenceOrbitDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildInpSimSimCtrlDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildInpSimOrbitSCSetDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildInpSimEnvironmentDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildInpSimCelestialBodyDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildInpSimLagrangePointSystemsDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildInpSimGroundStationDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildFOVHeaderDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildInpIpcDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildGraphicsDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildInpTDRsDialog(QAbstractItemModel* model, const QModelIndex& index);
    void buildRegionDialog(QAbstractItemModel* model, const QModelIndex& index);
    void hideSCcomponents(const QModelIndex& index);
    void hideSCcomponentsForAll();
    void closeTabsWhenSelectingMission();
    void missionSelectedChanged();
    void removeMission(const int& row);

    void run42();

};

#endif // MAINWINDOW_42_H
