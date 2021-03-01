#ifndef QT42DELEGATELINEEDITOR_H
#define QT42DELEGATELINEEDITOR_H

#include <QLineEdit>
#include <QPaintEvent>

class Qt42DelegateLineEditor : public QLineEdit
{
    Q_OBJECT
public:
    Qt42DelegateLineEditor(QWidget* parent = nullptr);
    ~Qt42DelegateLineEditor() override;
    void paintEvent(QPaintEvent* event) override;
};

#endif // QT42DELEGATELINEEDITOR_H
