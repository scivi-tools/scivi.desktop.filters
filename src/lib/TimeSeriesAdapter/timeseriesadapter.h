#ifndef TIMESERIESADAPTER_H
#define TIMESERIESADAPTER_H

#include "timeseriesadapter_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>


namespace scivi {
namespace filters {

class TimeSeriesAdapter: public FilterImplementation
{
    Q_OBJECT
public:
    TimeSeriesAdapter(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    const QString DataInput = "data";
    const QString XOutput = "x";
    const QString YOutput = "y";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;
};

class TimeSeriesAdapterFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new TimeSeriesAdapter(parent);
    }
};

}
}

#endif // TIMESERIESADAPTER_H
