#ifndef QT42_SHAREDPARAMETERS_H
#define QT42_SHAREDPARAMETERS_H

#include <QMap>
#include <QString>
#include <QStringListModel>
#include <QStringList>
#include <QList>
enum objectType
{
    QT42BASECLASS,
    MISSIONHOLDER, MISSION,
    SPACECRAFTHEADER,SPACECRAFT,
    SPACECRAFTBODY, JOINT, WHEEL, MAGTORQUER, THRUSTER,
    GYROAXIS, MAGNETOMETERAXIS, COARSESUNSENSOR,
    FINESUNSENSOR, STARTRACKER, GPSRECEIVER, ACCELEROMETER,
    ORBITHEADER, ORBIT, ORBITZERO, ORBITFLIGHT, ORBITCENTRAL, ORBITTHREEBODY,
    INPSIMHEADER, INPSIMSIMULATIONCONTROL , INPSIMENVIRONMENT, INPSIMCELESTIALBODY,
    INPSIMLAGRANGEPOINTSYSTEM, INPSIMGROUNDSTATION,
    FOVHEADER, FIELDOFVIEW, INPIPC, INPIPCHEADER, INPSIMORBITSCSET,
    GRAPHICSHEADER, INPTDRS, REGIONHEADER
};

const QString appName = "Cute42";


const int missionColumn = 0;
const int spacecraftHeaderColumn = 0;
const int spacecraftHeaderRow = 0;
const int spacecraftColumn = 0;
const int orbitHeaderColumn = 0;
const int orbitHeaderRow = 1;
const int inpsimRow = 2;
const int inpsimColumn = 0;
const int fovHeaderRow = 3;
const int fovHeaderColumn = 0;
//const int inpIPCRow = 4;
//const int inpIPCColumn = 0;
const int inpIPCHeaderRow = 4;
const int inpIPCHeaderColumn = 0;
const int graphicsHeaderRow = 5;
const int graphicsHeaderColumn = 0;
const int inpTDRsRow = 6;
const int inpTDRsColumn = 0;
const int inpRegionRow = 7;
const int inpRegionColumn = 0;

const QStringList list_OrbitProp {"Fixed", "Euler-Hill Formulation", "Encke Method"};
const QStringList list_ReferencePoint {"Center of Mass", "Origin"};
const QMap <QString , QString> map_orbitalPara {
                                                 {list_OrbitProp[0]      , "FIXED"}     ,
                                                 {list_OrbitProp[1]      , "EULER_HILL"} ,
                                                 {list_OrbitProp[2]      , "ENCKE"}      ,
                                                 {list_ReferencePoint[0] , "CM"}         ,
                                                 {list_ReferencePoint[1] , "ORIGIN"}     ,
                                                 {"FIXED"     , list_OrbitProp[0] }     ,
                                                 {"EULER_HILL" , list_OrbitProp[1] }     ,
                                                 {"ENCKE"      , list_OrbitProp[2] }     ,
                                                 {"CM"         , list_ReferencePoint[0]} ,
                                                 {"ORIGIN"     , list_ReferencePoint[1]}
                                               };

const QStringList list_ReferenceFrame {"Inertial Frame", "LVLH"};
const QStringList list_ReferenceFrameWithFormationFrame {
                                                           list_ReferenceFrame[0],
                                                           list_ReferenceFrame[1],
                                                           "Formation Frame",
                                                           "Body Frame"
                                                        };

const QMap <QString, QString> map_RefernceFrame {
                                        {list_ReferenceFrame[0], "N"},
                                        {list_ReferenceFrame[1], "L"},
                                        {list_ReferenceFrameWithFormationFrame[2], "F"},
                                        {list_ReferenceFrameWithFormationFrame[3], "B"},
                                        {"N", list_ReferenceFrame[0]},
                                        {"L", list_ReferenceFrame[1]},
                                        {"F", list_ReferenceFrameWithFormationFrame[2]},
                                        {"B", list_ReferenceFrameWithFormationFrame[3]}
                                        };

const QStringList list_AttitudeType {"Quaternion", "Euler Angles"};
const QMap <QString, QString> map_AttitudeType {
                                              {list_AttitudeType[0]  , "Q"} ,
                                              {list_AttitudeType[1]  , "A"} ,
                                              {"Q" , list_AttitudeType[0]}  ,
                                              {"A" , list_AttitudeType[1]}
                                            };

const QStringList list_jointRotation { "Steady", "Kinetic", "Dynamic"};
const QMap <QString,QString> map_jointRotation{
                                     {list_jointRotation[0] , "STEADY"} ,
                                     {list_jointRotation[1] , "KIN_JOINT"} ,
                                     {list_jointRotation[2] , "DYN_JOINT"} ,
                                     {"STEADY"     , list_jointRotation[0]} ,
                                     {"KIN_JOINT"  , list_jointRotation[1]} ,
                                     { "DYN_JOINT" , list_jointRotation[2] }
};

const QStringList list_massPropRef{ "Center of mass" , "Joint"};
const QMap <QString, QString> map_massPropRef{
                                               {list_massPropRef[0], "REFPT_CM"},
                                               {list_massPropRef[1], "REFPT_JOINT"},
                                               {"REFPT_CM"     , list_massPropRef[0]},
                                               {"REFPT_JOINT" , list_massPropRef[1]}
                                             };

const QStringList list_orbitCenter_World {
      "Sol" ,
      "Mercury" , "Venus" , "Earth" , "Mars" , "Jupiter" , "Saturn" ,
      "Uranus" , "Neptune" , "Pluto" , "Luna" , "Phobos" , "Deimos" ,
      "Io" , "Europa" , "Ganymede" , "Callisto" , "Amalthea" , "Himalia" ,
      "Elara" , "Pasiphae" , "Sinope" , "Lysithea" , "Carme" , "Ananke" ,
      "Leda" , "Thebe" , "Adrastea" , "Metis" , "Mimas" , "Enceladus" ,
      "Tethys" , "Dione" , "Rhea" , "Titan" , "Hyperion" , "Iapetus" ,
      "Phoebe" , "Janus" , "Epimetheus" , "Helene" , "Telesto" , "Calypso" ,
      "Atlas" , "Prometheus" , "Pandora" , "Pan" , "Ariel" , "Umbriel" ,
      "Titania" , "Oberon" , "Miranda" , "Triton" , "Neried" , "Charon" ,
      "Minor body 0", "Minor body 1", "Minor body 2", "Minor body 3", "Minor body 4",
      "Minor body 5", "Minor body 6", "Minor body 7", "Minor body 8", "Minor body 9"
};

QString orbitCenter_World(const QString& Center_World);

const QStringList list_OrbitCentralKEP_PA_AE {
                                               "Periapsis/Apoapsis",
                                               "Minimum Attitude/Eccentricity"
                                             };
const QMap <QString, QString> map_OrbitCentralKEP_PA_AE{
    {list_OrbitCentralKEP_PA_AE[0], "PA"}, {list_OrbitCentralKEP_PA_AE[1], "AE"},
    {"PA", list_OrbitCentralKEP_PA_AE[0]}, {"AE", list_OrbitCentralKEP_PA_AE[1]}
};

const QStringList list_OrbitCentral_KEP_RV_FILE {
                                                 "Keplerian elements",
                                                 "Initial Position/Velocity",
                                                 "File"
                                                };

const QMap <QString, QString> map_OrbitCentral_KEP_RV_FILE{
                       {list_OrbitCentral_KEP_RV_FILE[0], "KEP"},
                       {list_OrbitCentral_KEP_RV_FILE[1], "RV"},
                       {list_OrbitCentral_KEP_RV_FILE[2], "FILE"},
                       {"KEP"  , list_OrbitCentral_KEP_RV_FILE[0]},
                       {"RV"   , list_OrbitCentral_KEP_RV_FILE[1]},
                       {"FILE" ,list_OrbitCentral_KEP_RV_FILE[2]}
};

const QStringList list_Orbit3BodyLagrangeSystem {"Earth-Moon", "Sun-Earth", "Sun-Jupiter"};
const QMap <QString, QString> map_Orbit3BodyLagrangeSystem{
      {list_Orbit3BodyLagrangeSystem[0], "EARTHMOON" },
      {list_Orbit3BodyLagrangeSystem[1], "SUNEARTH"  },
      {list_Orbit3BodyLagrangeSystem[2], "SUNJUPITER"},
      {"EARTHMOON"  , list_Orbit3BodyLagrangeSystem[0]},
      {"SUNEARTH"   , list_Orbit3BodyLagrangeSystem[1]},
      {"SUNJUPITER" , list_Orbit3BodyLagrangeSystem[2]}
      };

const QStringList list_Orbit3BodyLagrangeDOF {"Modes", "Cowell", "Spline"};
const QMap <QString, QString> map_Orbit3BodyLagrangeDOF{
                            {list_Orbit3BodyLagrangeDOF[0], "LAGDOF_MODES"},
                            {list_Orbit3BodyLagrangeDOF[1], "LAGDOF_COWELL"},
                            {list_Orbit3BodyLagrangeDOF[2], "LAGDOF_SPLINE"},
                            {"LAGDOF_MODES"  , list_Orbit3BodyLagrangeDOF[0]},
                            {"LAGDOF_COWELL" , list_Orbit3BodyLagrangeDOF[1]},
                            {"LAGDOF_SPLINE" , list_Orbit3BodyLagrangeDOF[2]}
                            };

const QStringList list_Orbit3BodyInitializing {"Modes", "XYZ", "File"};
const QMap <QString, QString> map_Orbit3BodyInitializing{
                            {list_Orbit3BodyInitializing[0], "MODES"} ,
                            {list_Orbit3BodyInitializing[1], "XYZ"}   ,
                            {list_Orbit3BodyInitializing[2], "FILE"}  ,
                            {"MODES" , list_Orbit3BodyInitializing[0]} ,
                            {"XYZ"   , list_Orbit3BodyInitializing[1]} ,
                            {"FILE"  , list_Orbit3BodyInitializing[2]}
                            };

const QStringList list_Orbit3BodySense { "Clockwise", "Counterclockwise" };
const QMap <QString, QString> map_Orbit3BodySense {
                                           {list_Orbit3BodySense[0], "CW"},
                                           {list_Orbit3BodySense[1], "CCW"},
                                           {"CW"  , list_Orbit3BodySense[0]},
                                           {"CCW" , list_Orbit3BodySense[1]}
                                           };

const QStringList list_OrbitType {"Zero", "Flight", "Body-Centered", "Three-Body"};
const QMap <QString, QString> map_OrbitType {
                   {list_OrbitType[0], "ZERO"}      , {list_OrbitType[1], "FLIGHT"},
                   {list_OrbitType[2], "CENTRAL"}   , {list_OrbitType[3], "THREE_BODY"},
                   {"ZERO", list_OrbitType[0]}      , {"FLIGHT", list_OrbitType[1]},
                   {"CENTRAL", list_OrbitType[2]}   , {"THREE_BODY" ,list_OrbitType[3]}
};



const QStringList list_regions;
const QStringList list_EulerSeq { "123" , "132" , "121" , "131" , "213" , "231" , "212" , "232",
                                  "312" , "321" , "313" , "323"};
const QStringList list_OrbitCentral_TLE_TRV{"TLE", "TRV"};
const QStringList list_Orbit3Body_TLE_TRV_SPLINE { "TLE", "TRV", "SPLINE" };
/*
const QStringList list_minorbodies  {"MINORBODY_0", "MINORBODY_1", "MINORBODY_2",
                                     "MINORBODY_3", "MINORBODY_4", "MINORBODY_5",
                                     "MINORBODY_6", "MINORBODY_7", "MINORBODY_8",
                                     "MINORBODY_9"};
*/
const QStringList list_Orbit3BodyLibrationPoint {"L1", "L2", "L3", "L4", "L5"};

const QStringList list_SCcomponents {"Body", "Joint", "Wheel", "Magnetic Torquer Bar",
                                    "Thruster", "Gyroscope", "Magnetometer", "Coarse Sun Sensor",
                                    "Fine Sun Sensor", "Star Tracker", "GPS Receiver", "Accelerometer"};

const QMap <QString, objectType> map_SCc_StrEnum{
    {list_SCcomponents[0], SPACECRAFTBODY}  , {list_SCcomponents[1], JOINT},
    {list_SCcomponents[2], WHEEL}           , {list_SCcomponents[3], MAGTORQUER} ,
    {list_SCcomponents[4], THRUSTER}        , {list_SCcomponents[5], GYROAXIS}   ,
    {list_SCcomponents[6], MAGNETOMETERAXIS}, {list_SCcomponents[7], COARSESUNSENSOR} ,
    {list_SCcomponents[8], FINESUNSENSOR}   , {list_SCcomponents[9], STARTRACKER}     ,
    {list_SCcomponents[10], GPSRECEIVER}    , {list_SCcomponents[11], ACCELEROMETER}
};

const QStringList list_GimbalSpherical {"Gimbal", "Spherical"};
const QMap <QString, QString> map_GimbalSpherical {
    {list_GimbalSpherical[0], "GIMBAL"}, {list_GimbalSpherical[1], "SPHERICAL"},
    {"GIMBAL", list_GimbalSpherical[0]}, {"SPHERICAL", list_GimbalSpherical[1]}
};

const QStringList list_SolarFluxAPvalues {"Two sigma", "Nomial", "User-Defined"};
const QMap<QString, QString> map_SolarFluxAPvalues
{
    {list_SolarFluxAPvalues[0]  , "TWOSIGMA_KP"  },
    {list_SolarFluxAPvalues[1]  , "NOMINAL"      },
    {list_SolarFluxAPvalues[2]  , "USER_DEFINED" },
    {"TWOSIGMA_KP"   , list_SolarFluxAPvalues[0] },
    {"NOMINAL"       , list_SolarFluxAPvalues[1] },
    {"USER_DEFINED"  , list_SolarFluxAPvalues[2] }
};

const QStringList list_Magfield {"None", "Dipole", "IGRF"};
const QMap <QString, QString> map_Magfield
{
    {list_Magfield[0] ,   "NONE"   },
    {list_Magfield[1] ,   "DIPOLE" },
    {list_Magfield[2] ,   "IGRF"   },
    {"NONE"   ,  list_Magfield[0]  },
    {"DIPOLE" ,  list_Magfield[1]  },
    {"IGRF"   ,  list_Magfield[2]  }
};

const QStringList list_EphemeridesOptions {"Mean", "DE430"};
const QMap<QString, QString> map_EphemeridesOptions
{
    {list_EphemeridesOptions[0], "MEAN" },
    {list_EphemeridesOptions[1], "DE430"},
    {"MEAN" , list_EphemeridesOptions[0]},
    {"DE430", list_EphemeridesOptions[1]}
};

const QStringList list_FOV_Drawing {"Wireframe", "Solid", "Vector", "Plane"};
const QStringList list_SimTimeMode {"Fast", "Real", "External", "NOS3"};

bool compareVector(const QVector<double> &v1,
                          const QVector<double> &v2,
                          const double &epsilon = 1e-6);

const QStringList list_IPCMode {"Off", "Tx", "Rx", "Tx/Rx", "ACS", "Write File", "Read File"};
const QMap <QString, QString> map_IPCMode
{
    {list_IPCMode[0], "OFF"},
    {list_IPCMode[1], "TX"},
    {list_IPCMode[2], "RX"},
    {list_IPCMode[3], "TXRX"},
    {list_IPCMode[4], "ACS"},
    {list_IPCMode[5], "WRITEFILE"},
    {list_IPCMode[6], "READFILE"},
    {"OFF"  , list_IPCMode[0]},
    {"TX"   , list_IPCMode[1]},
    {"RX"   , list_IPCMode[2]},
    {"TXRX" , list_IPCMode[3]},
    {"ACS"  , list_IPCMode[4]},
    {"WRITEFILE", list_IPCMode[5]},
    {"READFILE" , list_IPCMode[6]},
};

const QStringList list_SocketRole {"Server", "Client", "GMSEC Client"};
const QMap<QString, QString> map_SocketRole
{
    {list_SocketRole[0], "SERVER"},
    {list_SocketRole[1], "CLIENT"},
    {list_SocketRole[2], "GMSEC_CLIENT"},
    {"SERVER", list_SocketRole[0]},
    {"CLIENT", list_SocketRole[1]},
    {"GMSEC_CLIENT", list_SocketRole[2]},
};

const QStringList list_GraphicsPOVMode{"Track Host", "Track Target", "Fixed in Host"};
const QMap<QString, QString> map_GraphicsPOVMode
{
    {list_GraphicsPOVMode[0], "TRACK_HOST"}    ,
    {list_GraphicsPOVMode[1], "TRACK_TARGET"}  ,
    {list_GraphicsPOVMode[2], "FIXED_IN_HOST"} ,
    {"TRACK_HOST"   , list_GraphicsPOVMode[0]} ,
    {"TRACK_TARGET" , list_GraphicsPOVMode[1]} ,
    {"FIXED_IN_HOST", list_GraphicsPOVMode[2]}
};

const QStringList list_GraphicsHostTargetType{"World", "Reference Orbit", "Frame", "Spacecraft", "Body"};
const QMap <QString, QString> map_GraphicsHostTargetType
{
    {list_GraphicsHostTargetType[0], "WORLD"},
    {list_GraphicsHostTargetType[1], "REFORB"},
    {list_GraphicsHostTargetType[2], "FRM"},
    {list_GraphicsHostTargetType[3], "SC"},
    {list_GraphicsHostTargetType[4], "BODY"},
    {"WORLD"  , list_GraphicsHostTargetType[0]},
    {"REFORB" , list_GraphicsHostTargetType[1]},
    {"FRM"    , list_GraphicsHostTargetType[2]},
    {"SC"     , list_GraphicsHostTargetType[3]},
    {"BODY"   , list_GraphicsHostTargetType[4]}
};

const QStringList list_GraphicsPOVAxes {"+x", "-x", "+y", "-y", "+z", "-z"};
const QMap<QString, QString> map_GraphicsPOVAxes
{
    {list_GraphicsPOVAxes[0], "POS_X"},
    {list_GraphicsPOVAxes[1], "NEG_X"},
    {list_GraphicsPOVAxes[2], "POS_Y"},
    {list_GraphicsPOVAxes[3], "NEG_Y"},
    {list_GraphicsPOVAxes[4], "POS_Z"},
    {list_GraphicsPOVAxes[5], "NEG_Z"},
    {"POS_X", list_GraphicsPOVAxes[0]},
    {"NEG_X", list_GraphicsPOVAxes[1]},
    {"POS_Y", list_GraphicsPOVAxes[2]},
    {"NEG_Y", list_GraphicsPOVAxes[3]},
    {"POS_Z", list_GraphicsPOVAxes[4]},
    {"NEG_Z", list_GraphicsPOVAxes[5]}
};

const QStringList list_GraphicsPOVViews{
    "Front", "Front right", "Right", "Rear right",
    "Rear" , "Rear left"  , "Left" , "Front left",
    "Up"   , "Down"
};

const QMap <QString, QString> map_GraphicsPOVViews
{
    {list_GraphicsPOVViews[0], "FRONT"}       ,
    {list_GraphicsPOVViews[1], "FRONT_RIGHT"} ,
    {list_GraphicsPOVViews[2], "RIGHT"}       ,
    {list_GraphicsPOVViews[3], "REAR_RIGHT"}  ,
    {list_GraphicsPOVViews[4], "REAR"}        ,
    {list_GraphicsPOVViews[5], "REAR_LEFT"}   ,
    {list_GraphicsPOVViews[6], "LEFT"}        ,
    {list_GraphicsPOVViews[7], "FRONT_LEFT"}  ,
    {list_GraphicsPOVViews[8], "UP"        }  ,
    {list_GraphicsPOVViews[9], "DOWN"      }  ,
    {"FRONT",        list_GraphicsPOVViews[0]},
    {"FRONT_RIGHT" , list_GraphicsPOVViews[1]},
    {"RIGHT"       , list_GraphicsPOVViews[2]},
    {"REAR_RIGHT"  , list_GraphicsPOVViews[3]},
    {"REAR"        , list_GraphicsPOVViews[4]},
    {"REAR_LEFT"   , list_GraphicsPOVViews[5]},
    {"LEFT"        , list_GraphicsPOVViews[6]},
    {"FRONT_LEFT"  , list_GraphicsPOVViews[7]},
    {"UP"          , list_GraphicsPOVViews[8]},
    {"DOWN"        , list_GraphicsPOVViews[9]}
};

const QStringList list_regionPOWS_LLA =
{"Position in world [m]", "Longitude [deg], Latitude [deg], and Altitude [m]"};
const QMap<QString, QString> map_regionPOWS_LLA
{
    {list_regionPOWS_LLA[0], "POSW"},
    {list_regionPOWS_LLA[1], "LLA"},
    {"POSW" , list_regionPOWS_LLA[0]},
    {"LLA"  , list_regionPOWS_LLA[1]}
};

#endif // QT42_SHAREDPARAMETERS_H
