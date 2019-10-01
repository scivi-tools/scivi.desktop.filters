#ifndef ORIENTATION2COORD_H
#define ORIENTATION2COORD_H

#include "orientation2coord_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QObject>


namespace scivi {
namespace filters {

class Orientation2Coord: public FilterImplementation
{
    Q_OBJECT
public:
    Orientation2Coord(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto OrientationInput = "Orientation";
    constexpr static auto CoordOutput = "Coord";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;
};

class Orientation2CoordFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new Orientation2Coord(parent);
    }
};

}
}

#endif // ORIENTATION2COORD_H
