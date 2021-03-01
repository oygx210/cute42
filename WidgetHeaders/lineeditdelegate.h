#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H

#include <QLineEdit>

class LineEditDelegate : public QLineEdit
{
public:
    LineEditDelegate();

protected:
    void paintEvent(QPaintDevice) override;
};

#endif // LINEEDITDELEGATE_H
