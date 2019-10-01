#ifndef WEBSOCKETINPUT_H
#define WEBSOCKETINPUT_H

#include "websocketinput_global.h"
#include <filterfactory.h>
#include "basewebsocketinput.h"

namespace scivi {
namespace filters {

class WebSocketInput: public BaseWebSocketInput
{
    Q_OBJECT
public:
    WebSocketInput(QObject *parent): BaseWebSocketInput(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto DataOutput = "data";

    // BaseWebSocketInput interface
protected slots:
    void onTextMessageReceived(QString message) override;
};

class WebSocketInputFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    ~WebSocketInputFactory() override {}
    FilterPtr create(QObject *parent) override
    {
        return new WebSocketInput(parent);
    }
};

}
}

#endif // WEBSOCKETINPUT_H
