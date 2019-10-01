#ifndef GRIDINPUTFILE_H
#define GRIDINPUTFILE_H

#include "gridinputfile_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>
#include <QVariant>
#include <QString>


namespace scivi {
namespace filters {

class GridInputFile: public FilterImplementation
{
    Q_OBJECT
public:
    GridInputFile(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    ~GridInputFile() override {}
    QString getName() const override;

    constexpr static auto PathSetting = "path";
    constexpr static auto VerticesOutput = "vertices";
    constexpr static auto WidthOutput = "width";
    constexpr static auto HeightOutput = "height";


public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;
};

class GridInputFileFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    ~GridInputFileFactory() override {}
    FilterPtr create(QObject *parent) override
    {
        return new GridInputFile(parent);
    }
};

}
}

#endif // GRIDINPUTFILE_H
