#include "orientation2coord.h"

#include <QString>
#include <QDebug>
#include <QVariantList>
#include <QVariant>
#include <QtMath>
#include <QScreen>
#include <QGuiApplication>

namespace scivi {
namespace filters {

QString Orientation2Coord::getName() const
{
    return "Orientation2Coord";
}

void Orientation2Coord::onStart()
{
    // Put your filter initialization here
}

QVector<float> orientation2Coords(QVector<float> quat) {
    float x = 0, y = 0, z = -1;
    float qx = -quat[1], qy = quat[2], qz = -quat[0], qw = quat[3];

    float l = static_cast<float>(qSqrt(static_cast<qreal>(qx * qx + qy * qy + qz * qz + qw * qw)));
    qx /= l;
    qy /= l;
    qz /= l;
    qw /= l;

    float ix = qw * x + qy * z - qz * y;
    float iy = qw * y + qz * x - qx * z;
    float iz = qw * z + qx * y - qy * x;
    float iw = -qx * x - qy * y - qz * z;

    QVector<float> result = {
        ix * qw + iw * -qx + iy * -qz - iz * -qy,
        iy * qw + iw * -qy + iz * -qx - ix * -qz,
        iz * qw + iw * -qz + ix * -qy - iy * -qx
    };

    return result;
}

void Orientation2Coord::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(data);
    Q_UNUSED(slotName);
    if (slotName == OrientationInput) {
        QVariantList lst = data.toList();
        QVector<float> quaternion;
        bool ok;
        for (const auto &el : lst) {
            float val = el.toFloat(&ok);
            if (!ok) {
                qWarning() << "Orientation2Coord: Got not float in orientation array";
                return;
            }
            quaternion.prepend(val);
        }
        QVector<float> normalizedOrientation = orientation2Coords(quaternion);

        QScreen *screen = QGuiApplication::primaryScreen();
        if (!screen) {
            qWarning() << "Cannot find screen!";
            return;
        }
        QRect geometry = screen->geometry();
        int width = geometry.width();
        int height = geometry.height();
        int x = qFloor(static_cast<qreal>((normalizedOrientation[0] + 0.7f) * width / 1.4f));
#if defined(Q_OS_MACOS)
        int y = qFloor(static_cast<qreal>((normalizedOrientation[1] + 0.7f) * height / 1.4f));
#else
        int y = qFloor(static_cast<qreal>((height - (normalizedOrientation[1] + 1) * height / 2)));
#endif
        QVariantList coords = { x, y };
        produced(coords, CoordOutput);
    }
}

}
}
