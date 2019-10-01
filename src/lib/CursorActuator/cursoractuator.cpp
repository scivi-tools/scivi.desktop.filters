#include "cursoractuator.h"

#include <QString>
#include <QDebug>
#include <QCursor>
#include <QMouseEvent>

namespace scivi {
namespace filters {

QString CursorActuator::getName() const
{
    return "CursorActuator";
}

void CursorActuator::onStart()
{
    // Put your filter initialization here
}

void CursorActuator::consume(QVariant data, const QString &slotName)
{
    if (slotName == XInput) {
        m_x = data.toInt();
    } else if (slotName == YInput) {
        m_y = data.toInt();
    }
    if (m_x != -1 && m_y != -1) {
        QCursor::setPos(m_x, m_y);
    }
}

}
}
