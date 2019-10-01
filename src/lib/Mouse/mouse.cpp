#include "mouse.h"

#include <QString>
#include <QDebug>
#include <QCursor>

#if defined(Q_OS_MACOS)
#include <CoreGraphics/CoreGraphics.h>
#endif

namespace scivi {
namespace filters {

QString Mouse::getName() const
{
    return "Mouse";
}

void Mouse::onStart()
{
    // Put your filter initialization here
    m_pressed = false;
    m_shouldUpdateCursorPos = false;
}

void Mouse::consume(QVariant data, const QString &slotName)
{
    if (slotName == CoordInput) {
        QVariantList lst = data.toList();
        if (lst.size() != 2) {
            qWarning() << "Mouse: Got coord array size which has size of " << lst.size();
            return;
        }
        bool ok;
        int x = lst[0].toInt(&ok);
        if (!ok) {
            qWarning() << "Mouse: Couldn't parse x coordinate from vector";
            return;
        }
        int y = lst[1].toInt(&ok);
        if (!ok) {
            qWarning() << "Mouse: Couldn't parse y coordinate from vector";
            return;
        }
        QPoint newCursorPos(x, y);
        if (m_lastCursorPos != newCursorPos) {
            m_lastCursorPos = newCursorPos;
            m_shouldUpdateCursorPos = true;
        }
        // TODO: Should we set position only after we received press state?
        //qWarning() << "MOUSE " << x << " " << y;
        //QCursor::setPos(newCursorPos);
    }
    if (slotName == PressedInput) {
        bool isPressed = data.toBool();
        Q_UNUSED(isPressed);
        qDebug() << isPressed;
#if defined(Q_OS_MACOS)
        if (m_shouldUpdateCursorPos || isPressed != m_pressed) {
            CGPoint loc = {
                static_cast<CGFloat>(m_lastCursorPos.x()),
                static_cast<CGFloat>(m_lastCursorPos.y())
            };
            CGEventRef evt;
            if (isPressed == m_pressed)
                evt = CGEventCreateMouseEvent(nullptr, isPressed ? kCGEventLeftMouseDragged : kCGEventMouseMoved, loc, kCGMouseButtonLeft);
            else {
                evt = CGEventCreateMouseEvent(nullptr, isPressed ? kCGEventLeftMouseDown : kCGEventLeftMouseUp, loc, kCGMouseButtonLeft);
                m_pressed = isPressed;
            }
            m_shouldUpdateCursorPos = false;
            CGEventPost(kCGSessionEventTap, evt);
            CFRelease(evt);
        }
#endif
        // TODO: Send mouse events to window system you should use saved last cursor position
    }
}

}
}
