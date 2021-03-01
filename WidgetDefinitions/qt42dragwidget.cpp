#include "WidgetHeaders/qt42dragwidget.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QDebug>
#include <QRegularExpression>
#include <QMainWindow>
#include <QtWidgets>

Qt42DragWidget::Qt42DragWidget(QWidget* parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    setMinimumWidth(300);
    setMinimumHeight(400);
    //resize(500,900);
}

Qt42DragWidget::~Qt42DragWidget()
{
    qDeleteAll(this->children());
}

QLabel* Qt42DragWidget::createLabel(const QString &text,
                                    const QString &name)
{
    QLabel* newLabel = new QLabel(text.trimmed(), this);
    QString objectName = name.trimmed();
    if (objectName.isEmpty())
        objectName = text.trimmed();
    QFont f ("Arial", 14, QFont::Bold);
    newLabel->setObjectName(objectName);
    newLabel->setStyleSheet("color : white");
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    newLabel->setAutoFillBackground(true);
    newLabel->setPalette(pal);
    newLabel->setFont(f);
    //newLabel->setAttribute(Qt::WA_DeleteOnClose); //This doesn't work well; when newLabel is closed, it is deleted right away.
    newLabel->setFrameShape(QFrame::Panel);
    newLabel->setFrameShadow(QFrame::Raised);
    newLabel->show();
    return newLabel;
}

void Qt42DragWidget::clearAllLabels()
{
    for (int i = children().size()-1; i > -1; --i)
    {
        QLabel* labelToRemove = qobject_cast<QLabel*>(children()[i]);
        labelToRemove->close();
        delete labelToRemove;
    }
}

void Qt42DragWidget::alignLabels()
{
    QList <QLabel*> listLabel = this->findChildren<QLabel*>();
    if (!listLabel.size())
        return;
    listLabel.first()->show();
    listLabel.first()->move(5,5);
    for (int i = 1; i < children().size(); ++i)
    {
        listLabel[i]->show();
        int x = 0;
        int y = listLabel[i-1]->pos().y();
        x = listLabel[i-1]->pos().x() + listLabel[i-1]->width() + 5;
        if (x > (this->width() - listLabel[i]->width()))
        {
            x = 5;
            y = listLabel[i-1]->pos().y() + listLabel[i-1]->height() + 5;
            if (y > (height() - listLabel[i]->height()))
                this->setMinimumHeight(y + listLabel[i]->height() + 20);
        }
        QPoint position(x,y);
        listLabel[i]->move(position);
    }
}

bool Qt42DragWidget::hasLabelName(const QLabel* label) const
{
    bool hasLabel = false;
    QList <QLabel*> listLabel = this->findChildren<QLabel*>();
    for (QLabel* l : listLabel)
    {
        if (label->text().trimmed() == l->text().trimmed() ||
                label->objectName().trimmed() == l->objectName().trimmed())
        {
            hasLabel = true;
            break;
        }
    }
    return hasLabel;
}

bool Qt42DragWidget::hasLabelName(const QString& name) const
{
    bool hasLabel = false;
    QList <QLabel*> listLabel = this->findChildren<QLabel*>();
    for (QLabel* l : listLabel)
    {
        if (name.trimmed() == l->text().trimmed())
        {
            hasLabel = true;
            break;
        }
    }
    return hasLabel;
}
void Qt42DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText()){
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else {
            event->acceptProposedAction();
        }
    }
    else {
        event->ignore();
    }
}

void Qt42DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasText()){
        if (event->source() == this){
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else {
            event->acceptProposedAction();
        }
    }
    else {
        event->ignore();
    }
}

void Qt42DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasText()) {
        const QMimeData *mime = event->mimeData();
        QString piece = mime->text().trimmed();
        QPoint position = event->pos();
        QPoint hotSpot;

        QByteArrayList hotSpotPos = mime->data("application/x-hotspot").split(' ');
        if (hotSpotPos.size() == 2) {
            hotSpot.setX(hotSpotPos.first().toInt());
            hotSpot.setY(hotSpotPos.last().toInt());
        }

        if (event->source() == this) {
            QLabel* newLabel = createLabel(piece);
            newLabel->move(position - hotSpot);
            newLabel->show();
            event->setDropAction(Qt::MoveAction);
            event->accept();
            if (m_enableDeleteLabelByDrag){
                const QString text = newLabel->text().trimmed();
                QPoint posCenter =
                        newLabel->pos() + QPoint(0.5*newLabel->width(), 0.5*newLabel->height());

                const int range = 8;
                bool removeLabel = false;
                if (posCenter.x() < range || posCenter.y() < range)
                    removeLabel = true;
                else if (posCenter.x() > (width() - range) ||
                         posCenter.y() > (height() - range))
                    removeLabel = true;
                if (removeLabel)
                {
                    newLabel->close();
                    delete newLabel;
                    emit removeLabelbyDragging(text);
                }
            }
        }

        else{
            if (!m_enableDropFromOtherSources || hasLabelName(piece.trimmed()))
            {
                event->ignore();
            }
            else if (m_limitedToOneLabel && findChildren<QLabel*>().size() > 0)
            {
                event->ignore();
            }
            else{
                QLabel* newLabel = createLabel(piece);
                newLabel->move(position - hotSpot);
                newLabel->show();
                alignLabels();
                emit addLabelbyDropping(piece.trimmed());
                event->acceptProposedAction();
            }
        }
    }

    else {
        event->ignore();
    }
}

void Qt42DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = qobject_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPoint hotSpot = event->pos() - child->pos();

    QMimeData *mimeData = new QMimeData;
    mimeData->setText(child->text());
    mimeData->setData("application/x-hotspot",
                      QByteArray::number(hotSpot.x()) + ' ' + QByteArray::number(hotSpot.y()));

    qreal dpr = devicePixelRatio();
    QPixmap pixmap(child->size() * dpr);
    pixmap.setDevicePixelRatio(dpr);
    child->render(&pixmap);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(hotSpot);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

    if (dropAction == Qt::MoveAction)
    {
        child->close();
        delete child;
    }
}
