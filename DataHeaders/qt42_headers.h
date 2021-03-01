#ifndef QT42_HEADERS_H
#define QT42_HEADERS_H

#include "ShareHeaders/qt42_sharedparameters.h"
#include "qt42baseclass.h"
#include "orbittype.h"
#include "spacecraft.h"
#include "inpsimterms.h"
#include "fieldofview.h"
#include "inp_ipc.h"
#include "qt42region.h"
#include <QVector>
#include <QVariant>
#include <QDataStream>

class Mission;

class SpacecraftHeader : public Qt42BaseClass
{
public:
    SpacecraftHeader(Mission* mission = nullptr);
    SpacecraftHeader(const SpacecraftHeader& SC_Header);
    ~SpacecraftHeader () override;
    SpacecraftHeader& operator= (const SpacecraftHeader& SC_Header);
    objectType type() const override {return m_type;}
    QString name() const override{return m_name;}
    int index() const override {return m_index;}
    Mission* parentItem() const;

    bool createSpacecraft();
    bool removeSpacecraft(Spacecraft* SC);
    bool hasSpacecraftNamedAs(const QString& name);
    int maxNumberDefaultSC() const;

    Spacecraft* spacecraft (const int& index = -1) const;
    int indexSpacecraft(Spacecraft* SC);
    int numberOfSpacecraft() const {return m_qvecSpacecraft.size();}

    /** "QVector<Spacecraft> m_qvecSpacecraftObjects" and
     * "int numberOfSpacecraftObject() const"
     * are for "QDataStream& operator<<" and "QDataStream& operator>>"
     **/
    QVector<Spacecraft> m_qvecSpacecraftObjects = QVector<Spacecraft>();
    int numberOfSpacecraftObject() const {return m_qvecSpacecraftObjects.size();}
    void setMission(Mission* m = nullptr) {if (m) m_mission = m; else return;}
    void duplicate(const SpacecraftHeader& sch);
    /** end **/

    friend QDataStream& operator<< (QDataStream& dataStream, const SpacecraftHeader& sch);
    friend QDataStream& operator>> (QDataStream& dataStream, SpacecraftHeader& sch);
    friend QDebug operator<< (QDebug dataStream, const SpacecraftHeader& sch);

private:
    void changeType(const objectType& type) override
    {Qt42BaseClass::changeType(type);}
    const QString m_name = "Spacecraft";
    const objectType m_type = SPACECRAFTHEADER;
    const int m_index = spacecraftHeaderRow;
    Mission* m_mission = nullptr;
    QVector <Spacecraft*> m_qvecSpacecraft;
};


class OrbitHeader : public Qt42BaseClass
{
public:
    OrbitHeader(Mission* mission = nullptr);
    OrbitHeader(const OrbitHeader& OH);
    ~OrbitHeader() override;
    OrbitHeader& operator= (const OrbitHeader& OH);
    objectType type() const override { return m_type; }
    QString name() const override { return m_name; }
    int index() const override { return m_index; }
    Mission* parentItem() const { return m_mission; }
    /** For data serialization (operator<< and operator>>) **/
    void setMission(Mission* m = nullptr) {if (m) m_mission = m; else return;}
    /** end **/

    bool createOrbit();
    bool removeOrbit(Orbit* orbit);
    bool hasOrbitNamedAs(const QString& name);
    int maxNumberDefaultOrbit() const;

    Orbit* orbit (const int& index = -1) const;
    int indexOrbit(Orbit* orbit);
    int numberOfOrbit() const { return m_qvecOrbit.size();}
    friend QDataStream& operator<< (QDataStream& dataStream, const OrbitHeader& oh);
    friend QDataStream& operator>> (QDataStream& dataStream, OrbitHeader& oh);
    friend QDebug operator<< (QDebug dataStream, const OrbitHeader& oh);

    /** "QVector<Orbit> m_qvecOrbitObjects" and
     * "int numberOfOrbitObject() const"
     * are for "QDataStream& operator<<" and "QDataStream& operator>>"
     **/
    QVector<Orbit> m_qvecOrbitObjects = QVector<Orbit>();
    int numberOfOrbitObject() const { return m_qvecOrbitObjects.size();}
    void duplicate(const OrbitHeader& oh);
    /** end **/

private:
    void changeType(const objectType& type) override
    {Qt42BaseClass::changeType(type);}
    const QString m_name = "Orbit";
    const objectType m_type = ORBITHEADER;
    const int m_index = orbitHeaderRow;
    Mission* m_mission;
    QVector <Orbit*> m_qvecOrbit;
};

class InpSimHeader : public Qt42BaseClass
{
public:
    InpSimHeader(Mission* mission = nullptr);
    InpSimHeader(const InpSimHeader& inpsimheader);
    ~InpSimHeader() override;
    InpSimHeader& operator= (const InpSimHeader& inpsimheader);
    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    int index() const override {return m_index;}
    int indexSimulationControl() const;
    int indexOrbitSCset() const;
    int indexEnvironment() const;
    int indexCelestialBody() const;
    int indexLagrangePointSystem() const;
    int indexGroudStation() const;
    InpSimSimulationControl* simulationcontrol(){return m_simulationcontrol;}
    InpSimOrbitSCSet* orbitSCSet(){return m_orbitSCSet;}
    InpSimEnvironment* environment(){return m_environment;}
    InpSimCelestialBody* celestialbody(){return m_celestialbody;}
    InpSimLagrangePointSystem* lagrangepointsystem(){return m_lagrangepointsystem;}
    InpSimGroundStation* groupstation(){return m_groupstation;}
    Mission* parentItem() const {return m_mission;}

    /** For data serialization (operator<< and operator>>) **/
    void setMission(Mission* m = nullptr) {if (m) m_mission = m; else return;}
    InpSimSimulationControl m_simulationcontrolObject = InpSimSimulationControl();
    InpSimOrbitSCSet m_orbitSCSetObject = InpSimOrbitSCSet();
    InpSimEnvironment m_environmentObject = InpSimEnvironment();
    InpSimCelestialBody m_celestialbodyObject = InpSimCelestialBody();
    InpSimLagrangePointSystem m_lagrangepointsystemObject = InpSimLagrangePointSystem();
    InpSimGroundStation m_groupstationObject = InpSimGroundStation();
    /** end **/


    friend QDataStream& operator<< (QDataStream& dataStream, const InpSimHeader& ish);
    friend QDataStream& operator>> (QDataStream& dataStream, InpSimHeader& ish);
    friend QDebug operator<< (QDebug dataStream, const InpSimHeader& ish);

private:
    void changeType(const objectType &type) override
    {Qt42BaseClass::changeType(type);}
    const QString m_name = "Simulation Settings";
    const objectType m_type = INPSIMHEADER;
    const int m_index = inpsimRow;
    Mission* m_mission = nullptr;

    InpSimSimulationControl* m_simulationcontrol = nullptr;
    InpSimOrbitSCSet* m_orbitSCSet = nullptr;
    InpSimEnvironment* m_environment = nullptr;
    InpSimCelestialBody* m_celestialbody = nullptr;
    InpSimLagrangePointSystem* m_lagrangepointsystem = nullptr;
    InpSimGroundStation* m_groupstation = nullptr;
};

class FOVHeader : public Qt42BaseClass
{
public:
    FOVHeader(Mission* mission = nullptr);
    FOVHeader(const FOVHeader& fovh);
    ~FOVHeader() override;
    FOVHeader& operator= (const FOVHeader& fovh);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    Mission* parentItem() const {return m_mission;}
    int index() const override {return m_index;}

    QVector<FieldOfView> qvecFieldsOfView = QVector<FieldOfView>();
    int numberOfFOV() const {return qvecFieldsOfView.size();}
    void createFOV();
    void createFOV(const int& index, const FieldOfView& fov)
    {if (qvecFieldsOfView.contains(fov) || index <= -1 || index > qvecFieldsOfView.size()) return;
    else qvecFieldsOfView.insert(index, fov);}

    void removeFOV(const int& index= -1)
    {if (index > -1 && index < qvecFieldsOfView.size()) qvecFieldsOfView.remove(index); else return;}

    void removeFOV(const FieldOfView& fov)
    {if (qvecFieldsOfView.contains(fov)) qvecFieldsOfView.removeAll(fov); else return;}

    void duplicate(const FOVHeader& fovh){ qvecFieldsOfView = fovh.qvecFieldsOfView;}

    friend QDataStream& operator<<(QDataStream& dataStream, const FOVHeader& fovh);
    friend QDataStream& operator>>(QDataStream& dataStream, FOVHeader& fovh);
    friend QDebug operator<< (QDebug dataStream, const FOVHeader& fovh);
private:
    void changeType(const objectType &type) override {Qt42BaseClass::changeType(type);}
    const objectType m_type = FOVHEADER;
    const QString m_name = "Fields of View";
    const int m_index = fovHeaderRow;
    Mission* m_mission = nullptr;


};


class InpIPCHeader : public Qt42BaseClass
{
public:
    InpIPCHeader(Mission* mission = nullptr);
    ~InpIPCHeader() override;
    InpIPCHeader(const InpIPCHeader& iiph);
    InpIPCHeader& operator=(const InpIPCHeader& iiph);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    Mission* parentItem() const {return m_mission;}
    int index() const override {return m_index;}

    void duplicate(const InpIPCHeader& inpIPCHeader)
    {m_qvecInpIpc = inpIPCHeader.m_qvecInpIpc;}

    int numberOfInpIpc() const {return m_qvecInpIpc.size();}
    QVector<Inp_IPC> qvecInpIpc() const {return m_qvecInpIpc;}
    void createNewIPC();
    void removeIPC(const QString& name);
    void removeIPC(const int& index);
    void editIPC(const QString& name, const Inp_IPC& newInp_IPC);
    void editIPC(const int& index, const Inp_IPC& newInp_IPC);
    Inp_IPC& ipc(const int& indexIPC) {return m_qvecInpIpc[indexIPC];}

    friend QDataStream& operator<<(QDataStream& dataStream, const InpIPCHeader& iiph);
    friend QDataStream& operator>>(QDataStream& dataStream, InpIPCHeader& iiph);
    friend QDebug operator<< (QDebug dataStream, const InpIPCHeader& iiph);
private:
    void changeType(const objectType &type) override {Qt42BaseClass::changeType(type);}
    const QString m_name = "Interprocess Communication";
    const objectType m_type = INPIPCHEADER;
    const int m_index = inpIPCHeaderRow;
    Mission* m_mission = nullptr;
    QVector<Inp_IPC> m_qvecInpIpc = QVector<Inp_IPC>();
};


class GraphicsHeader : public Qt42BaseClass
{
public:
    GraphicsHeader(Mission* mission = nullptr);
    ~GraphicsHeader() override;
    GraphicsHeader(const GraphicsHeader& gh);
    GraphicsHeader& operator=(const GraphicsHeader& gh);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    Mission* parentItem() const {return m_mission;}
    int index() const override {return m_index;}

    void duplicate(const GraphicsHeader& gh);

    double GLOutputInterval() const { return m_GLOutputInterval;}
    QString starCatalogFileName() const { return m_starCatalogFileName;}
    bool mapWindowExists() const { return m_mapWindowExists;}
    bool orreryWindowExists() const {return m_orreryWindowExists;}
    bool unitSphereWindowExists() const { return  m_unitSphereWindowExists;}
    bool pauseAtStartup() const { return m_pauseAtStartup;}
    QString povMode() const { return m_povMode;}
    QString hostType() const { return m_hostType;}
    int initialHostSC() const { return m_initialHostSC;}
    int initialHostBody() const { return m_initialHostBody;}
    QString initialHostPOVFrame() const { return m_initialHostPOVFrame;}
    QString targetType() const { return m_targetType;}
    int initialTargetSC() const {return  m_initialTargetSC;}
    int initialTargetBody() const { return m_initialTargetBody;}
    QString initialTargetPOVFrame() const { return m_initialTargetPOVFrame;}
    QString boresightAxis() const {return m_boresightAxis;}
    QString upAxis() const { return m_upAxis;}
    double initialPOVrangeFromTarget() const { return m_initialPOVrangeFromTarget;}
    double povAngleVertical() const { return m_povAngleVertical;}
    QVector <double> povPositionInHost() const { return m_povPositionInHost;}
    QString InitialPOVView() const { return m_InitialPOVView;}
    QString camTitle() const {return m_camTitle;}
    QPair <int,int> camWidthHeight() const { return m_camWidthHeight;}
    double camMouseScaleFactor() const { return m_camMouseScaleFactor;}
    double displayGammaExponent() const { return  m_displayGammaExponent;}
    bool camShowMenu_N_Axes() const { return m_camShowMenu_N_Axes;}
    bool camShowMenu_L_Axes() const { return m_camShowMenu_L_Axes;}
    bool camShowMenu_F_Axes() const { return m_camShowMenu_F_Axes;}
    bool camShowMenu_B_Axes() const { return m_camShowMenu_B_Axes;}
    bool camShowMenu_N_Grid() const { return m_camShowMenu_N_Grid;}
    bool camShowMenu_L_Grid() const { return m_camShowMenu_L_Grid;}
    bool camShowMenu_F_Grid() const { return m_camShowMenu_F_Grid;}
    bool camShowMenu_B_Grid() const { return m_camShowMenu_B_Grid;}
    bool camShowMenu_Gal_Grid() const { return m_camShowMenu_Gal_Grid;}
    bool camShowMenu_FOVs() const { return m_camShowMenu_FOVs;}
    bool camShowMenu_ProxOps() const { return m_camShowMenu_ProxOps;}
    bool camShowMenu_TDRS() const { return m_camShowMenu_TDRS;}
    bool camShowMenu_Shadows() const { return m_camShowMenu_Shadows;}
    bool camShowMenu_AstroLabels() const { return m_camShowMenu_AstroLabels;}
    bool camShowMenu_TruthVectors() const { return m_camShowMenu_TruthVectors;}
    bool camShowMenu_FSWVectors() const { return m_camShowMenu_FSWVectors;}
    bool camShowMenu_MilkyWay() const { return m_camShowMenu_MilkyWay;}
    bool camShowMenu_FermiSky() const { return m_camShowMenu_FermiSky;}
    QString mapMapTitle() const { return m_mapMapTitle;}
    QPair <int,int> mapWidthHeight() const { return m_mapWidthHeight;}
    bool mapShowMenuClock() const { return m_mapShowMenuClock;}
    bool mapShowMenuTlmClock() const { return m_mapShowMenuTlmClock;}
    bool mapShowMenuCredits() const { return m_mapShowMenuCredits;}
    bool mapShowMenuNight() const { return m_mapShowMenuNight;}
    bool unitSphereShowMenuMajor() const { return m_unitSphereShowMenuMajor;}
    bool unitSphereShowMenuZodiac() const { return m_unitSphereShowMenuZodiac;}
    bool unitShpereShowMenuMinor() const { return m_unitShpereShowMenuMinor;}

    void edit(const double& GLOutputInterval,
              const QString& starCatalogFileName,
              const bool& mapWindowExists,
              const bool& orreryWindowExists,
              const bool& unitSphereWindowExists,
              const bool& pauseAtStartup,
              const QString& povMode,
              const QString& hostType,
              const int& initialHostSC,
              const int& initialHostBody,
              const QString& initialHostPOVFrame,
              const QString& targetType,
              const int& initialTargetSC,
              const int& initialTargetBody,
              const QString& initialTargetPOVFrame,
              const QString& boresightAxis,
              const QString& upAxis,
              const double& initialPOVrangeFromTarget,
              const double& povAngleVertical,
              const QVector <double>& povPositionInHost,
              const QString& InitialPOVView,
              const QString& camTitle,
              const QPair<int,int>& camWidthHeight,
              const double& camMouseScaleFactor,
              const double& displayGammaExponent,
              const bool& camShowMenu_N_Axes,
              const bool& camShowMenu_L_Axes,
              const bool& camShowMenu_F_Axes,
              const bool& camShowMenu_B_Axes,
              const bool& camShowMenu_N_Grid,
              const bool& camShowMenu_L_Grid,
              const bool& camShowMenu_F_Grid,
              const bool& camShowMenu_B_Grid,
              const bool& camShowMenu_Gal_Grid,
              const bool& camShowMenu_FOVs,
              const bool& camShowMenu_ProxOps,
              const bool& camShowMenu_TDRS,
              const bool& camShowMenu_Shadows,
              const bool& camShowMenu_AstroLabels,
              const bool& camShowMenu_TruthVectors,
              const bool& camShowMenu_FSWVectors,
              const bool& camShowMenu_MilkyWay,
              const bool& camShowMenu_FermiSky,
              const QString& mapMapTitle,
              const QPair <int,int>& mapWidthHeight,
              const bool& mapShowMenuClock,
              const bool& mapShowMenuTlmClock,
              const bool& mapShowMenuCredits,
              const bool& mapShowMenuNight,
              const bool& unitSphereShowMenuMajor,
              const bool& unitSphereShowMenuZodiac,
              const bool& unitShpereShowMenuMinor);

    friend QDataStream& operator<<(QDataStream& dataStream, const GraphicsHeader& gh);
    friend QDataStream& operator>>(QDataStream& dataStream, GraphicsHeader& gh);
    friend QDebug operator<< (QDebug dataStream, const GraphicsHeader& gh);

private:
    void changeType(const objectType &type) override {Qt42BaseClass::changeType(type);}
    const QString m_name = "Graphics";
    const objectType m_type = GRAPHICSHEADER;
    const int m_index = graphicsHeaderRow;
    Mission* m_mission = nullptr;

    double m_GLOutputInterval = 1.0;  // GL Output Interval [sec]
    QString m_starCatalogFileName = "Skymap09.txt";
    bool m_mapWindowExists = true;
    bool m_orreryWindowExists = true;
    bool m_unitSphereWindowExists = true;
    bool m_pauseAtStartup = false;
    QString m_povMode = "TRACK_HOST"; // POV Mode: could be TRACK_HOST, TRACK_TARGET, FIXED_IN_HOST
    QString m_hostType = "SC"; // WORLD, REFORB, FRM, SC, BODY
    int m_initialHostSC = 0;
    int m_initialHostBody = 0;
    QString m_initialHostPOVFrame = "L";
    QString m_targetType = "SC"; // WORLD, REFORB, FRM, SC, BODY
    int m_initialTargetSC = 0;
    int m_initialTargetBody = 0;
    QString m_initialTargetPOVFrame = "L";
    QString m_boresightAxis = "POS_Z";
    QString m_upAxis = "NEG_Y";
    double m_initialPOVrangeFromTarget = 40.0; // Initial POV Range from Target [m]
    double m_povAngleVertical = 30.0; // POV Angle (Vertical) [deg]
    QVector <double> m_povPositionInHost = QVector<double>(3,0.0); //POV Position in Host [m]
    QString m_InitialPOVView = "FRONT"; // Initial POV View (FRONT, FRONT_RIGHT, etc)
    QString m_camTitle = "\"\""; // Cam Title [delimited by "]
    QPair<int,int> m_camWidthHeight = {800,800};
    double m_camMouseScaleFactor = 5.0E-5; // Mouse Scale Factor
    double m_displayGammaExponent = 1.8; // Display's Gamma Exponent (1.8-4.0)
    bool m_camShowMenu_N_Axes = false;
    bool m_camShowMenu_L_Axes = false;
    bool m_camShowMenu_F_Axes = false;
    bool m_camShowMenu_B_Axes = false;
    bool m_camShowMenu_N_Grid = false;
    bool m_camShowMenu_L_Grid = false;
    bool m_camShowMenu_F_Grid = false;
    bool m_camShowMenu_B_Grid = false;
    bool m_camShowMenu_Gal_Grid = false;
    bool m_camShowMenu_FOVs = false;
    bool m_camShowMenu_ProxOps = false;
    bool m_camShowMenu_TDRS = false;
    bool m_camShowMenu_Shadows = true;
    bool m_camShowMenu_AstroLabels = false;
    bool m_camShowMenu_TruthVectors = false;
    bool m_camShowMenu_FSWVectors = false;
    bool m_camShowMenu_MilkyWay = true;
    bool m_camShowMenu_FermiSky = false;
    QString m_mapMapTitle = "\"42 Map\""; // Map Title [delimited by "]
    QPair <int,int> m_mapWidthHeight = {512, 256};
    bool m_mapShowMenuClock= true;
    bool m_mapShowMenuTlmClock = true;
    bool m_mapShowMenuCredits = false;
    bool m_mapShowMenuNight = true;
    bool m_unitSphereShowMenuMajor = true;
    bool m_unitSphereShowMenuZodiac = true;
    bool m_unitShpereShowMenuMinor = false;
};

class InpTDRs : public Qt42BaseClass
{
public:
    InpTDRs(Mission* mission = nullptr);
    ~InpTDRs() override;
    InpTDRs(const InpTDRs& inptdrs);
    InpTDRs& operator=(const InpTDRs& inptdrs);
    void duplicate(const InpTDRs& inptdrs);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    Mission* parentItem() const {return m_mission;}
    int index() const override {return m_index;}

    QPair<bool, QString> TDRS1() const {return m_TDRS1;}
    QPair<bool, QString> TDRS2() const {return m_TDRS2;}
    QPair<bool, QString> TDRS3() const {return m_TDRS3;}
    QPair<bool, QString> TDRS4() const {return m_TDRS4;}
    QPair<bool, QString> TDRS5() const {return m_TDRS5;}
    QPair<bool, QString> TDRS6() const {return m_TDRS6;}
    QPair<bool, QString> TDRS7() const {return m_TDRS7;}
    QPair<bool, QString> TDRS8() const {return m_TDRS8;}
    QPair<bool, QString> TDRS9() const {return m_TDRS9;}
    QPair<bool, QString> TDRS10() const {return m_TDRS10;}

    void edit(const QPair<bool,QString>& TDRS1,
              const QPair<bool,QString>& TDRS2,
              const QPair<bool,QString>& TDRS3,
              const QPair<bool,QString>& TDRS4,
              const QPair<bool,QString>& TDRS5,
              const QPair<bool,QString>& TDRS6,
              const QPair<bool,QString>& TDRS7,
              const QPair<bool,QString>& TDRS8,
              const QPair<bool,QString>& TDRS9,
              const QPair<bool,QString>& TDRS10);

    friend QDataStream& operator<<(QDataStream& dataStream, const InpTDRs& inptdrs);
    friend QDataStream& operator>>(QDataStream& dataStream, InpTDRs& inptdrs);
    friend QDebug operator<<(QDebug dataStream, const InpTDRs& inptdrs);
private:
    void changeType(const objectType &type = QT42BASECLASS) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = INPTDRS;
    const QString m_name = "TDRS (Tracking and Data Relay Satellite System)";
    const int m_index = inpTDRsRow;

    Mission* m_mission = nullptr;
    QPair<bool, QString> m_TDRS1{false , "TDRS-1"};
    QPair<bool, QString> m_TDRS2{false , "In Memorium"};
    QPair<bool, QString> m_TDRS3{true  , "TDZ"};
    QPair<bool, QString> m_TDRS4{false , "TDS"};
    QPair<bool, QString> m_TDRS5{false , "TD171"};
    QPair<bool, QString> m_TDRS6{true  , "TDW"};
    QPair<bool, QString> m_TDRS7{false , "TDRS-7"};
    QPair<bool, QString> m_TDRS8{false , "TD271"};
    QPair<bool, QString> m_TDRS9{false , "TDRS-9"};
    QPair<bool, QString> m_TDRS10{true , "TDE"};
};

class RegionHeader : public Qt42BaseClass
{
public:
    RegionHeader(Mission* mission = nullptr);
    ~RegionHeader() override;
    RegionHeader(const RegionHeader& rgnh);
    RegionHeader& operator = (const RegionHeader& rgnh);
    void duplicate(const RegionHeader& rgnh);

    objectType type() const override {return m_type;}
    QString name() const override {return m_name;}
    Mission* parentItem() const {return m_mission;}
    int index() const override {return m_index;}

    QVector<Qt42Region> qvecRegions() const {return m_qvecRegions;}
    int numberOfRegions() const {return m_qvecRegions.size();}
    void removeRegion(const int& index);
    void removeRegion(const QString& name);
    void addRegion();
    Qt42Region& region(const int& index);
    void clearRegions(){m_qvecRegions.clear();}

    friend QDataStream& operator<< (QDataStream& dataStream, const RegionHeader& rgnh);
    friend QDataStream& operator>> (QDataStream& dataStream, RegionHeader& rgnh);
    friend QDebug operator<< (QDebug dataStream, const RegionHeader& rgnh);
private:
    Mission* m_mission = nullptr;
    void changeType(const objectType &type = QT42BASECLASS) override
    {Qt42BaseClass::changeType(type);}
    const objectType m_type = REGIONHEADER;
    const QString m_name = "Regions for " + appName;
    const int m_index = inpRegionRow;
    QVector<Qt42Region> m_qvecRegions = QVector<Qt42Region>();
};

Q_DECLARE_METATYPE(SpacecraftHeader)
Q_DECLARE_METATYPE(OrbitHeader)
Q_DECLARE_METATYPE(InpSimHeader)
Q_DECLARE_METATYPE(FOVHeader)
Q_DECLARE_METATYPE(InpIPCHeader)
Q_DECLARE_METATYPE(GraphicsHeader)
Q_DECLARE_METATYPE(InpTDRs)
Q_DECLARE_METATYPE(RegionHeader);
#endif // QT42_HEADERS_H
