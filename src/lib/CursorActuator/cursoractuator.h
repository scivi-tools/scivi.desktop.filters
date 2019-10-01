#ifndef CURSORACTUATOR_H
#define CURSORACTUATOR_H

#include "cursoractuator_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>


namespace scivi {
namespace filters {

class CursorActuator: public FilterImplementation
{
    Q_OBJECT
public:
    CursorActuator(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto XInput = "x";
    constexpr static auto YInput = "y";
    constexpr static auto MousePressed = "mousePressed";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;

private:
    int m_x {-1};
    int m_y {-1};
};

class CursorActuatorFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new CursorActuator(parent);
    }
};

}
}

#endif // CURSORACTUATOR_H
