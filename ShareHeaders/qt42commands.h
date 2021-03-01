#ifndef QT42COMMANDS_H
#define QT42COMMANDS_H

#include <QUndoCommand>
#include <QModelIndex>
#include <QVariant>
#include "ShareHeaders/qt42_sharedparameters.h"
#include "MVDheaders/qt42model.h"

class QAbstractItemModel;


/** RemoveCommand **/

class RemoveCommand : public QUndoCommand
{
public:
    RemoveCommand(QAbstractItemModel* model = nullptr,
                  QModelIndex index = QModelIndex(),
                  QUndoCommand* parent = nullptr);

    ~RemoveCommand() override;

    void undo() override;
    void redo() override;
private:
    void convertToType(const QModelIndex& index = QModelIndex());
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    QModelIndex m_parent = QModelIndex();
    Qt42BaseClass* m_SCcToRemove = nullptr;
    objectType m_type;
    int m_row = -1;
    int m_column = -1;

};


/** CreateCommand **/
class CreateCommand : public QUndoCommand
{
public:
    CreateCommand(objectType type, QAbstractItemModel* model = nullptr,
                  const QModelIndex& parentIndex = QModelIndex(),
                  QUndoCommand* parent = nullptr);

    ~CreateCommand() override;

    void undo() override;
    void redo() override;

private:
    void convertToType();
    Qt42Model* m_model = nullptr;
    QModelIndex m_parentIndex = QModelIndex();
    Qt42BaseClass* m_SCcToCreate = nullptr;
    objectType m_type;
    int m_row = -1;
    int m_column = -1;

};

/** EditCommand **/
class EditCommand : public QUndoCommand
{
public:
    EditCommand(QAbstractItemModel* model, const QModelIndex& index,
                QVariant data, QUndoCommand* parent = nullptr);
    ~EditCommand() override;

    void undo() override;
    void redo() override;

private:
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    Qt42BaseClass* m_Qt42BC = nullptr;
    objectType m_type;
    QVariant m_dataUndo = QVariant();
    QVariant m_dataRedo = QVariant();
};

class ResetCommand : public QUndoCommand
{
public:
    ResetCommand(QAbstractItemModel* model, const QModelIndex& index,
                 QUndoCommand* parent = nullptr);
    ~ResetCommand() override;

    void undo() override;
    void redo() override;
    //bool mergeWith(const QUndoCommand *other) override;

private:
    Qt42Model* m_model = nullptr;
    QModelIndex m_index = QModelIndex();
    Qt42BaseClass* m_Qt42BC = nullptr;
    QVariant m_dataUndo = QVariant();
};

#endif // QT42COMMANDS_H
