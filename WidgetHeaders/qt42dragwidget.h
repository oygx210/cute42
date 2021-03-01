#ifndef QT42DRAGWIDGET_H
#define QT42DRAGWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QWidget>

class Qt42DragWidget : public QFrame
{
    Q_OBJECT
public:
    explicit Qt42DragWidget(QWidget* parent = nullptr);
    ~Qt42DragWidget() override;
    QLabel* createLabel(const QString& text,
                        const QString& name = QString());
    void clearAllLabels();
    void alignLabels();
    void enableDropFromOtherSources(const bool& enable)
    {m_enableDropFromOtherSources = enable;}
    void enableDeleteLabelByDrag(const bool& enable)
    {m_enableDeleteLabelByDrag = enable;}
    bool hasLabelName(const QLabel* label) const;
    bool hasLabelName(const QString& name) const;
    void setLimitedToOneLabel(const bool& limit) {m_limitedToOneLabel = limit;}
    bool limitedToOneLabel() const {return m_limitedToOneLabel;}

signals:
    void addLabelbyDropping(const QString& text);
    void removeLabelbyDragging(const QString& text);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool m_limitedToOneLabel = false;
    bool m_enableDropFromOtherSources = false;
    bool m_enableDeleteLabelByDrag = false;
};

#endif // QT42DRAGWIDGET_H
