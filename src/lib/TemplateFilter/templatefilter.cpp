#include "templatefilter.h"

#include <QString>
#include <QDebug>

namespace scivi {
namespace filters {

QString TemplateFilter::getName() const
{
    return "TemplateFilter";
}

void TemplateFilter::onStart()
{
    // Put your filter initialization here
}

void TemplateFilter::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(data);
    Q_UNUSED(slotName);
    // Consume input parameters
}

}
}
