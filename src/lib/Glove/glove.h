#ifndef GLOVE_H
#define GLOVE_H

#include "glove_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include "basewebsocketinput.h"
#include <QObject>


namespace scivi {
namespace filters {

class Glove: public BaseWebSocketInput
{
    Q_OBJECT
public:
    Glove(QObject *parent): BaseWebSocketInput (parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto OrientationOutput = "Orientation";
    constexpr static auto FingerOutput = "Finger";

    // BaseWebSocketInput interface
protected slots:
    void onTextMessageReceived(QString message) override;
};

class GloveFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    ~GloveFactory() override {}
    FilterPtr create(QObject *parent) override
    {
        return new Glove(parent);
    }
};

}
}

#endif // GLOVE_H
