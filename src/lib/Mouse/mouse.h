#ifndef MOUSE_H
#define MOUSE_H

#include "mouse_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QObject>
#include <QPoint>


namespace scivi {
namespace filters {

class Mouse: public FilterImplementation
{
    Q_OBJECT
public:
    Mouse(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto CoordInput = "Coord";
    constexpr static auto PressedInput = "Pressed";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;

private:
    QPoint m_lastCursorPos;
    bool m_pressed;
    bool m_shouldUpdateCursorPos;
};

class MouseFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new Mouse(parent);
    }
};

}
}

#endif // MOUSE_H
