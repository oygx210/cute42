#ifndef LINEEDITOR42_H
#define LINEEDITOR42_H

#include <QLineEdit>

class LineEditor42 : public QLineEdit
{
public:
    LineEditor42(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* e) override;
};

#endif // LINEEDITOR42_H
