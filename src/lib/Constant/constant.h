#ifndef CONSTANT_H
#define CONSTANT_H

#include "constant_global.h"
#include <filterfactory.h>
#include <filterimplementation.h>
#include <QObject>

namespace scivi {
namespace filters {


class CONSTANTSHARED_EXPORT Constant : public FilterImplementation
{
    Q_OBJECT
public:
    Constant(QObject*parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    void onStart() override;
    QString getName() const override;

    constexpr static auto ValueSetting = "value";
    constexpr static auto ValueOutput = "value";

public slots:
    void consume(QVariant data, const QString &slotName) override;
};

class ConstantFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

public:
    FilterPtr create(QObject* parent) override
    {
        return new Constant(parent);
    }
};

}
}


#endif // CONSTANT_H
