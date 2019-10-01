#include "glove.h"

#include <QString>
#include <QDebug>

namespace scivi {
namespace filters {

QString Glove::getName() const
{
    return "Glove";
}

void Glove::onTextMessageReceived(QString message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject json = doc.object();
    QVariant orientation = json["q"].toVariant();
    QVariant finger = json["f"].toVariant();
    produced(orientation, OrientationOutput);
    produced(finger, FingerOutput);
}

}
}
