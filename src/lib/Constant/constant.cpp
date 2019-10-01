#include "constant.h"

namespace scivi {
namespace filters {

void Constant::onStart()
{
    emit produced(m_settings[ValueSetting], ValueOutput);
}

QString Constant::getName() const
{
    return "Constant";
}

void Constant::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(slotName);
    Q_UNUSED(data);
}

}
}
