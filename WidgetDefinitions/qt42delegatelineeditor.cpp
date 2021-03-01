#include "WidgetHeaders/qt42delegatelineeditor.h"
#include <QPainter>

Qt42DelegateLineEditor::Qt42DelegateLineEditor(QWidget* parent) : QLineEdit(parent)
{
}

Qt42DelegateLineEditor::~Qt42DelegateLineEditor()
{
}

void Qt42DelegateLineEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(this);
    painter.end();
}
