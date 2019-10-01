#ifndef COLOR_H
#define COLOR_H

#include "color_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>

namespace scivi {
namespace filters {


class COLORSHARED_EXPORT Color: public FilterImplementation
{   
    Q_OBJECT
public:
    Color(QObject* parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto ColorSetting = "color";
    constexpr static auto ColorOutput = "color";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;
};

class ColorFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

public:
    FilterPtr create(QObject *parent) override
    {
        return new Color(parent);
    }
};

}
}

#endif // COLOR_H
