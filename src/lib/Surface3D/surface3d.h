#ifndef SURFACE3D_H
#define SURFACE3D_H

#include "surface3d_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>
#include <QVector3D>
#include <visual.h>


namespace scivi {
namespace filters {

class Surface3D: public FilterImplementation
{
    Q_OBJECT
public:
    Surface3D(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto VerticesInput = "vertices";
    constexpr static auto WidthInput = "width";
    constexpr static auto HeightInput = "height";
    constexpr static auto VisualOutput = "visual";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;

private:
    friend class Surface3DVisualImpl;
    QSharedPointer<QVector<QVector3D>> m_vertices;
    int m_width;
    int m_height;
    Visual* m_visual { nullptr };
};

class Surface3DFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new Surface3D(parent);
    }
};

}
}

#endif // SURFACE3D_H
