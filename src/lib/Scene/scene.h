#ifndef SCENE_H
#define SCENE_H

#include "scene_global.h"
#include <sinkfilter.h>
#include <filterfactory.h>

namespace scivi {
namespace filters {

class Scene: public SinkFilter
{
    Q_OBJECT
public:
    Scene(QObject *parent): SinkFilter(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto VisualInput = "visual";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;
};

class SCENESHARED_EXPORT SceneFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new Scene(parent);
    }
};

}
}

#endif // SCENE_H
