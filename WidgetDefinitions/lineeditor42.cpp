#include "WidgetHeaders/lineeditor42.h"
#include <QPainter>
LineEditor42::LineEditor42(QWidget* parent) : QLineEdit(parent)
{

}

void LineEditor42::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
}
