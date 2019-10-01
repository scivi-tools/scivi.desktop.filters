#ifndef TEMPLATEFILTER_H
#define TEMPLATEFILTER_H

#include "templatefilter_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QObject>


namespace scivi {
namespace filters {

class TemplateFilter: public FilterImplementation
{
    Q_OBJECT
public:
    TemplateFilter(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;
};

class TemplateFilterFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    ~TemplateFilterFactory() override {}
    FilterPtr create(QObject *parent) override
    {
        return new TemplateFilter(parent);
    }
};

}
}

#endif // TEMPLATEFILTER_H
