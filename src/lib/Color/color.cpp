#include "color.h"

#include <QColor>

namespace scivi {
namespace filters {


QString Color::getName() const
{
    return "Color";
}

void Color::onStart()
{
    QColor colorSetting = this->m_settings[ColorSetting].value<QColor>();
    emit produced(colorSetting, ColorOutput);
}

void Color::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(data);
    Q_UNUSED(slotName);
}

}
}
