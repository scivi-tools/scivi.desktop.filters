#include "basewebsocketinput.h"

#include <QString>
#include <QDebug>

namespace scivi {
namespace filters {

BaseWebSocketInput::BaseWebSocketInput(QObject *parent)
    : FilterImplementation(parent)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &BaseWebSocketInput::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &BaseWebSocketInput::onDisconnected);
}

QString BaseWebSocketInput::getName() const
{
    return "BaseWebSocketInput";
}

BaseWebSocketInput::~BaseWebSocketInput()
{
    m_webSocket.close();
}

void BaseWebSocketInput::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textFrameReceived, this, &BaseWebSocketInput::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::binaryFrameReceived, this, &BaseWebSocketInput::onBinaryMessageReceived);
}

void BaseWebSocketInput::onDisconnected()
{
    qDebug() << "Disconnected" << m_webSocket.peerName();
    disconnect(&m_webSocket);
}

void BaseWebSocketInput::onTextMessageReceived(QString message)
{
    Q_UNUSED(message);
}

void BaseWebSocketInput::onBinaryMessageReceived(const QByteArray bytes, bool isLastFrame)
{
    Q_UNUSED(bytes);
    Q_UNUSED(isLastFrame);
}

void BaseWebSocketInput::onStart()
{
    QUrl url = this->m_settings[UrlSetting].toUrl();
    if (!url.isValid()) {
        qDebug() << "Passed url is invalid";
        return;
    }
    m_webSocket.open(url);
}

void BaseWebSocketInput::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(data);
    Q_UNUSED(slotName);
}

}
}
