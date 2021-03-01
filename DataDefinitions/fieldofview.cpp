#include "DataHeaders/fieldofview.h"
FieldOfView::FieldOfView()
{
    changeType(m_type);
}

FieldOfView::~FieldOfView()
{
}

FieldOfView::FieldOfView(const FieldOfView& fov) : Qt42BaseClass(fov)
{
    m_label = fov.m_label;
    m_numberOfSides = fov.m_numberOfSides;
    m_lengthOfSides = fov.m_lengthOfSides;
    m_X_Width = fov.m_X_Width;
    m_Y_Height = fov.m_Y_Height;
    m_colorRGB_R = fov.m_colorRGB_R;
    m_colorRGB_G = fov.m_colorRGB_G;
    m_colorRGB_B = fov.m_colorRGB_B;
    m_colorRGB_Alpha = fov.m_colorRGB_Alpha;
    m_drawing = fov.m_drawing;
    m_drawNearField = fov.m_drawNearField;
    m_drawFarField = fov.m_drawFarField;
    m_indexSC = fov.m_indexSC;
    m_indexSCB = fov.m_indexSCB;
    m_qvecPositionInBody = fov.m_qvecPositionInBody;
    m_qvecEulerAngles = fov.m_qvecEulerAngles;
    m_EulerAngleSeq = fov.m_EulerAngleSeq.trimmed();
}

FieldOfView& FieldOfView::operator=(const FieldOfView &fov)
{
    if (this == &fov)
        return *this;

    m_label = fov.m_label;
    m_numberOfSides = fov.m_numberOfSides;
    m_lengthOfSides = fov.m_lengthOfSides;
    m_X_Width = fov.m_X_Width;
    m_Y_Height = fov.m_Y_Height;
    m_colorRGB_R = fov.m_colorRGB_R;
    m_colorRGB_G = fov.m_colorRGB_G;
    m_colorRGB_B = fov.m_colorRGB_B;
    m_colorRGB_Alpha = fov.m_colorRGB_Alpha;
    m_drawing = fov.m_drawing;
    m_drawNearField = fov.m_drawNearField;
    m_drawFarField = fov.m_drawFarField;
    m_indexSC = fov.m_indexSC;
    m_indexSCB = fov.m_indexSCB;
    m_qvecPositionInBody = fov.m_qvecPositionInBody;
    m_qvecEulerAngles = fov.m_qvecEulerAngles;
    m_EulerAngleSeq = fov.m_EulerAngleSeq.trimmed();
    return *this;
}

bool operator== (const FieldOfView& fov1, const FieldOfView& fov2)
{
    const double ep = 0.000001;
    bool PositionInBodyEqual =
            (std::abs(fov1.m_qvecPositionInBody[0]-fov2.m_qvecPositionInBody[0]) < ep &&
        std::abs(fov1.m_qvecPositionInBody[1]-fov2.m_qvecPositionInBody[1]) < ep &&
        std::abs(fov1.m_qvecPositionInBody[2]-fov2.m_qvecPositionInBody[2]) < ep);

    bool EulerAnglesEqual =
            (std::abs(fov1.m_qvecEulerAngles[0]-fov2.m_qvecEulerAngles[0]) < ep &&
            std::abs(fov1.m_qvecEulerAngles[1]-fov2.m_qvecEulerAngles[1]) < ep &&
            std::abs(fov1.m_qvecEulerAngles[2]-fov2.m_qvecEulerAngles[2]) < ep);

    return
            fov1.m_label == fov2.m_label &&
    fov1.m_numberOfSides == fov2.m_numberOfSides &&
    std::abs(fov1.m_lengthOfSides-fov2.m_lengthOfSides) < ep &&
    std::abs(fov1.m_X_Width-fov2.m_X_Width) < ep &&
    std::abs(fov1.m_Y_Height-fov2.m_Y_Height) < ep &&
    std::abs(fov1.m_colorRGB_R-fov2.m_colorRGB_R) < ep &&
    std::abs(fov1.m_colorRGB_G-fov2.m_colorRGB_G) < ep &&
    std::abs(fov1.m_colorRGB_B-fov2.m_colorRGB_B) < ep &&
    std::abs(fov1.m_colorRGB_Alpha-fov2.m_colorRGB_Alpha) < ep &&
    fov1.m_drawing == fov2.m_drawing &&
    fov1.m_drawNearField == fov2.m_drawNearField &&
    fov1.m_drawFarField == fov2.m_drawFarField &&
    fov1.m_indexSC == fov2.m_indexSC &&
    fov1.m_indexSCB == fov2.m_indexSCB &&
    PositionInBodyEqual &&
    EulerAnglesEqual &&
    fov1.m_EulerAngleSeq.trimmed() == fov2.m_EulerAngleSeq.trimmed();
}

void FieldOfView::edit(const QString &label,
                       const int &numberOfSides, const double &lengthOfSides,
                       const double &X_Width, const double &Y_Height,
                       const double &colorRGB_R, const double &colorRGB_G,
                       const double &colorRGB_B, const double &colorRGB_Alpha,
                       const QString &drawing,
                       const bool &drawNearField, const bool &drawFarField,
                       const int &indexSC, const int &indexSCB,
                       QVector<double> &qvecPositionInBody,
                       QVector<double> &qvecEulerAngles,
                       const QString &EulerAngleSeq)
{
    m_label = label;
    m_numberOfSides = numberOfSides;
    m_lengthOfSides = lengthOfSides;
    m_X_Width = X_Width;
    m_Y_Height = Y_Height;
    m_colorRGB_R = colorRGB_R;
    m_colorRGB_G = colorRGB_G;
    m_colorRGB_B = colorRGB_B;
    m_colorRGB_Alpha = colorRGB_Alpha;
    m_drawing = drawing;
    m_drawNearField = drawNearField;
    m_drawFarField = drawFarField;
    m_indexSC = indexSC;
    m_indexSCB = indexSCB;
    m_qvecPositionInBody = qvecPositionInBody;
    m_qvecEulerAngles = qvecEulerAngles;
    m_EulerAngleSeq = EulerAngleSeq.trimmed();
}

QDataStream& operator<< (QDataStream& dataStream, const FieldOfView& fov)
{
    dataStream << fov.m_label
               << fov.m_numberOfSides
               << fov.m_lengthOfSides
               << fov.m_X_Width
               << fov.m_Y_Height
               << fov.m_colorRGB_R
               << fov.m_colorRGB_G
               << fov.m_colorRGB_B
               << fov.m_colorRGB_Alpha
               << fov.m_drawing
               << fov.m_drawNearField
               << fov.m_drawFarField
               << fov.m_indexSC
               << fov.m_indexSCB
               << fov.m_qvecPositionInBody
               << fov.m_qvecEulerAngles
               << fov.m_EulerAngleSeq.trimmed();
    return dataStream;
}

QDataStream& operator>> (QDataStream& dataStream, FieldOfView& fov)
{
    dataStream >> fov.m_label
               >> fov.m_numberOfSides
               >> fov.m_lengthOfSides
               >> fov.m_X_Width
               >> fov.m_Y_Height
               >> fov.m_colorRGB_R
               >> fov.m_colorRGB_G
               >> fov.m_colorRGB_B
               >> fov.m_colorRGB_Alpha
               >> fov.m_drawing
               >> fov.m_drawNearField
               >> fov.m_drawFarField
               >> fov.m_indexSC
               >> fov.m_indexSCB
               >> fov.m_qvecPositionInBody
               >> fov.m_qvecEulerAngles
               >> fov.m_EulerAngleSeq;
    return dataStream;
}

QDebug operator<< (QDebug dataStream, const FieldOfView& fov)
{
    dataStream << fov.m_label
               << fov.m_numberOfSides
               << fov.m_lengthOfSides
               << fov.m_X_Width
               << fov.m_Y_Height
               << fov.m_colorRGB_R
               << fov.m_colorRGB_G
               << fov.m_colorRGB_B
               << fov.m_colorRGB_Alpha
               << fov.m_drawing
               << fov.m_drawNearField
               << fov.m_drawFarField
               << fov.m_indexSC
               << fov.m_indexSCB
               << fov.m_qvecPositionInBody
               << fov.m_qvecEulerAngles
               << fov.m_EulerAngleSeq.trimmed();
    return dataStream;
}
