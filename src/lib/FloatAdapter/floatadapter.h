#ifndef FLOATADAPTER_H
#define FLOATADAPTER_H

#include "floatadapter_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>


namespace scivi {
namespace filters {

class FloatAdapter: public FilterImplementation
{
    Q_OBJECT
public:
    FloatAdapter(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;
    const QString DataInput = "data";
    const QString ValueOutput = "value";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;
};

class FloatAdapterFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new FloatAdapter(parent);
    }
};

}
}

#endif // FLOATADAPTER_H
