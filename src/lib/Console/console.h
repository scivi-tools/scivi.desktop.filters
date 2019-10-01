#ifndef CONSOLE_H
#define CONSOLE_H

#include "console_global.h"
#include <filterfactory.h>
#include <filterimplementation.h>
#include <QObject>

namespace scivi {
namespace filters {

class Console : public FilterImplementation
{
    Q_OBJECT
public:
    Console(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

public slots:
    void onStart();
    void consume(QVariant data, const QString &slotName) override;
};

class ConsoleFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new Console(parent);
    }
};

}
}

#endif // CONSOLE_H
