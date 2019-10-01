#include "surface3d.h"

#include <QString>
#include <QDebug>
#include <QPointer>
#include <QtQml/QQmlEngine>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>

#include "surfacedatamodel.h"

namespace scivi {
namespace filters {

class Surface3DVisualImpl: public Visual, QObject {
public:
    Surface3DVisualImpl(Surface3D *surface3D, QObject *parent = nullptr);

    // Visual interface
public:
    void render(QQuickItem *container) override;

private:
    QPointer<Surface3D> m_surface3D;
    QQuickItem *m_view { nullptr };
    SurfaceDataModel m_surfaceModel;
};

QString Surface3D::getName() const
{
    return "Surface3D";
}

void Surface3D::onStart()
{
}

void Surface3D::consume(QVariant data, const QString &slotName)
{
    if (slotName == VerticesInput) {
        auto vertices = data.value<QVector<QVector3D>>();
        m_vertices = QSharedPointer<QVector<QVector3D>>::create(vertices);
    } else if (slotName == WidthInput) {
        m_width = data.toInt();
    } else if (slotName == HeightInput) {
        m_height = data.toInt();
    }
    if (!m_vertices.isNull()) {
        if (!m_visual) {
            m_visual = new Surface3DVisualImpl(this, this);
        }
        emit produced(qVariantFromValue(static_cast<void*>(m_visual)), VisualOutput);
    }
}

Surface3DVisualImpl::Surface3DVisualImpl(Surface3D *surface3D, QObject *parent): QObject(parent)
{
    m_surface3D = surface3D;
}

void Surface3DVisualImpl::render(QQuickItem *container)
{
    if (!m_view) {
        QQmlEngine *engine = new QQmlEngine(container);
        QQmlComponent component(engine, "qrc:/Surface3D.qml", QQmlComponent::PreferSynchronous);
        if (!component.isReady() || component.isError()) {
            qWarning() << component.errorString();
            return;
        }

        m_view = qobject_cast<QQuickItem*>(component.create());
        m_view->setParentItem(container);
        m_view->setProperty("model", qVariantFromValue(&m_surfaceModel));
    }
    QVector<QVector3D> *vertices = m_surface3D->m_vertices.data();
    m_surfaceModel.setupData(*vertices);
}

}
}


