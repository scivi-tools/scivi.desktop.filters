#include "websocketinput.h"

#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

namespace scivi {
namespace filters {

QString WebSocketInput::getName() const
{
    return "WebSocketInput";
}

void WebSocketInput::onTextMessageReceived(QString message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject json = doc.object();
    // TODO: Check message type
    QVariant data = json["data"].toVariant();
    produced(data, DataOutput);
}

}
}
