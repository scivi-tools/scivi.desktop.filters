#ifndef SURFACEDATAMODEL_H_
#define SURFACEDATAMODEL_H_

#include <QObject>
#include <QList>
#include <QVector3D>
#include <QAbstractItemModel>

namespace scivi {

class SurfaceDataModel : public QAbstractListModel {
public:
    SurfaceDataModel(QObject *parent = nullptr);

    void setupData(QVector<QVector3D> data);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<QVector3D> m_innerData;
};

}

#endif
