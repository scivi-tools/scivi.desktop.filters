#ifndef INPUTFILE_H
#define INPUTFILE_H

#include "inputfile_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>
#include <QObject>


namespace scivi {
namespace filters {

#define PathSetting QString("path")
#define XOutput QString("x")
#define YOutput QString("y")

class GridInputFile: public FilterImplementation
{
    Q_OBJECT
public:
    GridInputFile(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;
};

class GridInputFileFactory:
        public FilterFactory
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new GridInputFile(parent);
    }
};

}
}

#endif // INPUTFILE_H
