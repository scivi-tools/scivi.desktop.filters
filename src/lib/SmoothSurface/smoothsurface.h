#ifndef SMOOTHSURFACE_H
#define SMOOTHSURFACE_H

#include "smoothsurface_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>
#include <QSharedPointer>

namespace scivi {
namespace filters {

class SmoothSurface: public FilterImplementation
{
    Q_OBJECT
public:
    SmoothSurface(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto VerticesInput = "vertices";
    constexpr static auto WidthInput = "width";
    constexpr static auto HeightInput = "height";
    constexpr static auto ResolutionSetting = "resolution";
    constexpr static auto CSetting = "c";
    constexpr static auto VerticesOutput = "vertices";
    constexpr static auto WidthOutput = "width";
    constexpr static auto HeightOutput = "height";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;

private:
    QSharedPointer<QVector<QVector3D>> m_vertices;
    double m_c;
    int m_width;
    int m_height;
    int m_resolution;
};

class SmoothSurfaceFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new SmoothSurface(parent);
    }
};

}
}

#endif // SMOOTHSURFACE_H
