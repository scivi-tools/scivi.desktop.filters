#include "floatadapter.h"

#include <QString>
#include <QDebug>

namespace scivi {
namespace filters {

QString FloatAdapter::getName() const
{
    return "FloatAdapter";
}

void FloatAdapter::onStart()
{
    // Put your filter initialization here
}

void FloatAdapter::consume(QVariant data, const QString &slotName)
{
    if (slotName != DataInput) return;
    bool ok;
    qreal value = data.toDouble(&ok);
    if (ok) {
        emit produced(qVariantFromValue(value), ValueOutput);
        return;
    }
    QVariantList arr = data.toList();
    if (arr.size() >= 1) {
        value = arr[0].toDouble(&ok);
        if (ok) {
            emit produced(qVariantFromValue(value), ValueOutput);
        }
    }
    qWarning() << "Unknown input data format for value convertion";
}

}
}
