#ifndef FIELDOFVIEW_H
#define FIELDOFVIEW_H

#include <QDataStream>
#include <QDebug>
#include "qt42baseclass.h"
#include "ShareHeaders/qt42_sharedparameters.h"

class FieldOfView : public Qt42BaseClass
{
public:
    FieldOfView();
    ~FieldOfView() override;
    FieldOfView(const FieldOfView& fov);
    FieldOfView& operator= (const FieldOfView& fov);

    objectType type() const override {return m_type;}

    void rename(const QString& label) {m_label = label;}
    void edit(const QString& label, const int& numberOfSides, const double& lengthOfSides,
              const double& X_Width, const double& Y_Height,
              const double& colorRGB_R, const double& colorRGB_G, const double& colorRGB_B,
              const double& colorRGB_Alpha, const QString& drawing,
              const bool& drawNearField, const bool& drawFarField,
              const int& indexSC, const int& indexSCB,
              QVector<double>& qvecPositionInBody,
              QVector<double>& qvecEulerAngles, const QString& EulerAngleSeq);

    QString label() const {return m_label;}
    int numberOfSides() const {return m_numberOfSides;}
    double lengthOfSides() const {return m_lengthOfSides;}
    double X_Width() const {return m_X_Width;}
    double Y_Height() const {return m_Y_Height;}
    double colorRGB_R() const {return m_colorRGB_R;}
    double colorRGB_G() const {return m_colorRGB_G;}
    double colorRGB_B() const {return m_colorRGB_B;}
    double colorRGB_Alpha() const {return m_colorRGB_Alpha;}
    QString drawing() const {return m_drawing;}
    bool drawNearField() const {return m_drawNearField;}
    bool drawFarField() const {return m_drawFarField;}
    int indexSC() const {return m_indexSC;}
    int indexSCB() const {return m_indexSCB;}
    QVector<double> qvecPositionInBody() const {return m_qvecPositionInBody;}
    QVector<double> qvecEulerAngles() const {return m_qvecEulerAngles;}
    QString EulerAngleSeq() const {return m_EulerAngleSeq;}

    friend bool operator== (const FieldOfView& fov1, const FieldOfView& fov2);
    friend QDataStream& operator<<(QDataStream& dataStream, const FieldOfView& fov);
    friend QDataStream& operator>>(QDataStream& dataStream, FieldOfView& fov);
    friend QDebug operator<< (QDebug dataStream, const FieldOfView& fov);
    const QString defaultName = "Default FOV";
private:
    void changeType(const objectType &type = QT42BASECLASS) override {Qt42BaseClass::changeType(type);}
    const objectType m_type = FIELDOFVIEW;

    QString m_label = QString();
    int m_numberOfSides = 0;
    double m_lengthOfSides = 0.0;  // length of sides [meter]
    double m_X_Width = 0.0;       // X width [degree]
    double m_Y_Height = 0.0;      // Y height [degree]
    double m_colorRGB_R = 0.0;
    double m_colorRGB_G = 0.0;
    double m_colorRGB_B = 0.0;
    double m_colorRGB_Alpha = 0.0;
    QString m_drawing = "SOLID";   // "drawing" could be "WIREFRAME", "SOLID", "VECTOR", "PLANE"
    bool m_drawNearField = true;
    bool m_drawFarField = true;
    int m_indexSC = -1;
    int m_indexSCB = -1;
    QVector<double> m_qvecPositionInBody = QVector<double>(3, 0.0); // position in Body [m]
    QVector<double> m_qvecEulerAngles = QVector<double>(3,0.0);
    QString m_EulerAngleSeq = "123";
};

Q_DECLARE_METATYPE(FieldOfView)
#endif // FIELDOFVIEW_H
