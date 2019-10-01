#include "timeseriesadapter.h"

#include <QString>
#include <QDebug>
#include <QDateTime>

namespace scivi {
namespace filters {

QString TimeSeriesAdapter::getName() const
{
    return "TimeSeriesAdapter";
}

void TimeSeriesAdapter::onStart()
{
    // Put your filter initialization here
}

void TimeSeriesAdapter::consume(QVariant data, const QString &slotName)
{
    if (slotName != DataInput) return;
    QVariantList list = data.toList();
    QVector<QDateTime> dts;
    QVector<qreal> values;
    for (const auto &el: list) {
        auto pair = el.toList();
        dts.append(pair[0].toDateTime());
        values.append(pair[1].toReal());
    }
    emit produced(qVariantFromValue(dts), XOutput);
    emit produced(qVariantFromValue(values), YOutput);
}

}
}
