#include "surfacedatamodel.h"

#include <QDebug>

namespace scivi {

SurfaceDataModel::SurfaceDataModel(QObject *parent): QAbstractListModel(parent)
{
}

void SurfaceDataModel::setupData(QVector<QVector3D> data)
{
    m_innerData.clear();
    for(const auto &v: data) {
        m_innerData.append(v);
    }
}

int SurfaceDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_innerData.count();
}

QVariant SurfaceDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVector3D point = m_innerData[index.row()];
    switch (role) {
        case Qt::UserRole + 1: return point.x();
        case Qt::UserRole + 2: return point.y();
        case Qt::UserRole + 3: return point.z();
    }
    return QVariant();
}

QHash<int, QByteArray> SurfaceDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "x";
    roles[Qt::UserRole + 2] = "y";
    roles[Qt::UserRole + 3] = "z";
    return roles;
}

}
