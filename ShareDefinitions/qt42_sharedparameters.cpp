#include "ShareHeaders/qt42_sharedparameters.h"

bool compareVector(const QVector<double> &v1,
                          const QVector<double> &v2,
                          const double &epsilon)
{
    if (v1.size() != v2.size()){
        return false;
    }
    bool flag = true;
    for (int i = 0; i < v1.size(); ++i)
    {
        if (abs(v1[i]-v2[i]) > epsilon)
            flag = false;
    }
    return flag;
}

QString orbitCenter_World(const QString& Center_World)
{
    QStringList list_centerWorld_underscore = Center_World.split("_");
    if (list_centerWorld_underscore[0].trimmed().toUpper() == "MINORBODY")
        return "Minor body " + list_centerWorld_underscore[1];

    QStringList list_centerWorld_space = Center_World.split(" ");
    if (list_centerWorld_space[0] == "Minor")
        return "MINORBODY_" + list_centerWorld_space[2];

    if (Center_World[0].isUpper() && Center_World[1].isLower())
        return Center_World.toUpper();

    else if (Center_World[0].isUpper() && Center_World[1].isUpper())
    {
        QString returnString = Center_World[0];
        for (int i = 1; i < Center_World.size(); ++i)
        {
            returnString.append(Center_World[i].toLower());
        }
        return returnString;
    }
    else
        return QString();
}
