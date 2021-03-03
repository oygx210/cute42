#ifndef QT42DELEGATE_H
#define QT42DELEGATE_H

#include <QStyledItemDelegate>

class Qt42BaseClass;
class QAction;
class QMenu;
class QDialog;
class QLabel;
class Qt42Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    Qt42Delegate(QObject *parent = nullptr);
    ~Qt42Delegate() override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

    QModelIndex indexSelected() const {return m_indexSelected;}
    bool renewIndexInEditor(const QModelIndex& index = QModelIndex()){m_indexSelected = index; return true;}

signals:
    void editSpacecraft(QAbstractItemModel* model, const QModelIndex& index);
    // This signal is emitted when the user wants to edit the spacecraft,
    // and it is connected to MainWindow to generate a SpacecraftDialog object.
    void removeObject(QAbstractItemModel* model, const QModelIndex& index);
    // This signal is emitted when the user wants to remove the spacecraft,
    // and it is connected to MainWindow to close the SpacecraftDialog object.
    void editOrbit(QAbstractItemModel* model, const QModelIndex& index);
    // This signal is emitted when the user wants to edit the orbit,
    // and it is connected to MainWindow to generate a ReferenceOrbitDialog object.
    void missionSelected(QAbstractItemModel* model, const QModelIndex& index);
    void spacecraftSelected(QAbstractItemModel* model, const QModelIndex& index);
    void orbitSelected(QAbstractItemModel* model, const QModelIndex& index);
    //void passInfoModelandIndex(QAbstractItemModel* model, const QModelIndex& index);
    void orbitCreated(QAbstractItemModel* model, const QModelIndex& index);
    void delegateFocusOut(QAbstractItemModel* model, const QModelIndex& index);
    void InpSimParameterSelected(QAbstractItemModel* model, const QModelIndex& index);
    void FOVHeadserSelected(QAbstractItemModel* model, const QModelIndex& index);
    void InpIpcHeaderSelected(QAbstractItemModel* model, const QModelIndex& index);
    void GraphicsHeaderSelected(QAbstractItemModel* model, const QModelIndex& index);
    void InpTDRsSelected(QAbstractItemModel* model, const QModelIndex& index);
    void RegionHeaderSelected(QAbstractItemModel* model, const QModelIndex& index);
    void removeMission(const int& row);
private slots:
    void printOutName(QAbstractItemModel* model, const QModelIndex& index);

private:
    QModelIndex m_indexSelected;
    QString nameByType(const QModelIndex& index) const;
    void setModelDataByType(QLineEdit* editor, QAbstractItemModel* model,
                                const QModelIndex& index) const;
    bool canConvertToCustomType(const QVariant& data) const;
    bool canConvertToCustomTypeSCcomponents(const QVariant& data) const;
    void CM_ClickOnMission(QMouseEvent *event , QAbstractItemModel* model ,
                           const QModelIndex& index);  // CM = Context Menu
    bool createSpacecraft(QAbstractItemModel* model, const QModelIndex& index);
    void CM_CreateSpacecraft(QMouseEvent *event , QAbstractItemModel* model ,
                             const QModelIndex& index = QModelIndex());   // CM = Context Menu
    void CM_ClickOnSpacecraft(QMouseEvent *event , QAbstractItemModel* model ,
                              const QModelIndex& index = QModelIndex());  // CM = Context Menu

    bool createOrbit(QAbstractItemModel* model, const QModelIndex& index);
    void CM_CreateOrbit(QMouseEvent* event, QAbstractItemModel* model,
                        const QModelIndex& index = QModelIndex());  // CM = Context Menu

    void CM_ClickOnOrbit(QMouseEvent *event , QAbstractItemModel* model ,
                              const QModelIndex& index = QModelIndex());  // CM = Context Menu

    /*
     * void CM_ClickOnSCcomponents(QMouseEvent *event , QAbstractItemModel* model ,
                              const QModelIndex& index = QModelIndex());  // CM = Context Menu
    */

    void ShowDialogModifiyName(QAbstractItemModel* model,
                               const QModelIndex& index = QModelIndex());

    void showDialogRemoveClose(QAbstractItemModel* model, const QModelIndex& index= QModelIndex());

};

#endif // QT42DELEGATE_H
