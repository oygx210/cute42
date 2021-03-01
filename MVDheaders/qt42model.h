#ifndef QT42MODEL_H
#define QT42MODEL_H


#include <QAbstractItemModel>
#include "ShareHeaders/qt42_sharedparameters.h"
#include "DataHeaders/mission.h"

class MissionHolder;
class Qt42BaseClass;

class Qt42Model : public QAbstractItemModel
{
    Q_OBJECT
public:
    Qt42Model();
    ~Qt42Model() override;

    QModelIndex parent (const QModelIndex& index) const override;
    QModelIndex index (int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QVariant data (const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& data, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount (const QModelIndex& parent = QModelIndex()) const override;
    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex& parent) override;
    bool insertRows(int position, int rows, const QModelIndex& parent) override;
    bool removeItem(int row, int column, const QModelIndex& parent = QModelIndex());
    bool createItem(const QModelIndex& parent, objectType componentType);
    bool insertItem(const QModelIndex& parent, objectType componentType,
                    const int& row = -1, const int& column = -1, Qt42BaseClass* Qt42BC = nullptr);
    bool resetData(const QModelIndex& index);
    int numberOfMission() const;
    void loadMission(Mission*& missionToModify, Mission missionLoaded);
    void loadMission(const QModelIndex& modelIndexMission, const QVariant& newData = QVariant());

signals:

private:
    void setUpModel();
    MissionHolder* m_MissionHolder;
    QModelIndex parentByType (Qt42BaseClass* Qt42BC) const;
    QModelIndex indexByType (int row, int column, Qt42BaseClass* Qt42BC) const;
    QVariant dataByType(Qt42BaseClass* Qt42BC) const;
    QIcon iconByType(Qt42BaseClass* Qt42BC) const;
    int rowCountByType(Qt42BaseClass* Qt42BC) const;
    int columnCountByType(Qt42BaseClass* Qt42BC) const;
    void setDataByType(const QModelIndex& index, const QVariant& data);
};

#endif // QT42MODEL_H
