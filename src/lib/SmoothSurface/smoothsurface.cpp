#include "smoothsurface.h"

#include <QString>
#include <QDebug>
#include <QVector3D>

#include "sleek-surface/surface.h"

namespace scivi {
namespace filters {

using namespace SleekSurface;

QString SmoothSurface::getName() const
{
    return "SmoothSurface";
}

void SmoothSurface::onStart()
{
}

void SmoothSurface::consume(QVariant data, const QString &slotName)
{
    bool ok;
    m_c = this->m_settings[CSetting].toDouble(&ok);
    if (!ok) {
        qWarning() << "Coudnt parse c parameter";
    }
    m_resolution = this->m_settings[ResolutionSetting].toInt(&ok);
    if (!ok) {
        qWarning() << "Coudnt parse resolution parameter";
    }
    if (slotName == VerticesInput) {
        auto vertices = data.value<QVector<QVector3D>>();
        m_vertices = QSharedPointer<QVector<QVector3D>>::create(vertices);
    } else if (slotName == WidthInput) {
        m_width = data.toInt();
    } else if (slotName == HeightInput) {
        m_height = data.toInt();
    }
    if (!m_vertices.isNull()) {
        std::vector<Vec3> points(m_width * m_height);
        for (int i = 0; i < m_height; i++) {
            for (int j = 0; j < m_width; j++) {
                int ind = i * m_width + j;
                QVector3D vert = (*m_vertices)[ind];
                points[ind] = Vec3(vert.x(), vert.z(), vert.y());
            }
        }
        std::vector<Vertex> vertices;
        int rw, rh;
        SurfaceBuilder::build(points, m_width, m_height, m_resolution, m_c, vertices, rw, rh);

        QVector<QVector3D> out_vertices;
        out_vertices.reserve(rw * rh);
        for (int i = 0; i < rh; i++) {
            for (int j = 0; j < rw; j++) {
                SleekSurface::Vec3 vec = vertices[i * rw + j].position;
                out_vertices.append(QVector3D(vec.x, vec.z, vec.y));
            }
        }
        emit produced(qVariantFromValue(rw), WidthOutput);
        emit produced(qVariantFromValue(rh), HeightOutput);
        emit produced(qVariantFromValue(out_vertices), VerticesOutput);
    }
}

}
}
