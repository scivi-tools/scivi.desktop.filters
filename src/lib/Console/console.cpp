#include "console.h"

#include <QDebug>

namespace scivi {
namespace filters {


void Console::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(slotName);
    qDebug() << data.toString();
}

QString Console::getName() const
{
    return "Console";
}

void Console::onStart()
{

}

}
}
