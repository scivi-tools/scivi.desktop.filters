#ifndef BASEWEBSOCKETINPUT_H
#define BASEWEBSOCKETINPUT_H

#include "basewebsocketinput_global.h"
#include <QtWebSockets/QtWebSockets>

#include <filterimplementation.h>

namespace scivi {
namespace filters {

class BaseWebSocketInput: public FilterImplementation
{
    Q_OBJECT
public:
    BaseWebSocketInput(QObject *parent = nullptr);
    // FilterImplementation interface
public:
    QString getName() const override;
    ~BaseWebSocketInput() override;

    constexpr static auto UrlSetting = "url";

protected slots:
    virtual void onConnected();
    virtual void onDisconnected();
    virtual void onTextMessageReceived(QString message);
    virtual void onBinaryMessageReceived(const QByteArray bytes, bool isLastFrame);

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;

protected:
     QWebSocket m_webSocket;
};

}
}

#endif // BASEWEBSOCKETINPUT_H
