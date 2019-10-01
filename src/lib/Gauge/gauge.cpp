#include "gauge.h"

#include <QString>
#include <QDebug>
#include <QQmlEngine>

namespace scivi {
namespace filters {

GaugeVisualImpl::GaugeVisualImpl(QColor &color, qreal min, qreal max, qreal value, QObject *parent)
    : QObject(parent), m_color(color), m_min(min), m_max(max), m_value(value)
{

}

QQuickItem *GaugeVisualImpl::createChartView(QQuickItem *container)
{
    QQmlEngine *engine = new QQmlEngine(container);
    QQmlComponent gaugeQmlComponent(engine, "qrc:/Gauge.qml", QQmlComponent::PreferSynchronous);
    if (!gaugeQmlComponent.isReady() || gaugeQmlComponent.isError() || gaugeQmlComponent.isNull()) {
        qWarning() << gaugeQmlComponent.errorString();
        return nullptr;
    }

    QQuickItem* chartView = qobject_cast<QQuickItem*>(gaugeQmlComponent.create());
    chartView->setParentItem(container);
    return chartView;
}

void GaugeVisualImpl::render(QQuickItem *container)
{
    if (m_view == nullptr) {
        QQuickItem *chartView = createChartView(container);
        m_view = chartView;
        chartView->setParentItem(container);
        chartView->setProperty("maximumValue", m_max);
        chartView->setProperty("minimumValue", m_min);
        chartView->setProperty("color", m_color);
    }
    m_view->setProperty("value", m_value);
}

QString Gauge::getName() const
{
    return "Gauge";
}

void Gauge::onStart()
{
    // Put your filter initialization here
}

void Gauge::consume(QVariant data, const QString &slotName)
{
    if (slotName != ValueInput) return;
    bool ok;
    auto color = m_settings[ColorSetting].value<QColor>();
    auto max = m_settings[MaxSetting].toReal(&ok);
    if (!ok) {
        qWarning() << "Wrong max value setting";
        max = 100;
    }
    auto min = m_settings[MinSetting].toReal(&ok);
    if (!ok) {
        qWarning() << "Wrong min value setting";
        min = 0;
    }
    auto value = data.toReal(&ok);
    if (!ok) {
        qWarning() << "Couldn't convert consumed data to real";
        return;
    }
    if (!m_visual) {
        m_visual = new GaugeVisualImpl(color, min, max, value, this);
    }
    m_visual->m_value = value;
    emit produced(qVariantFromValue((void*)m_visual), VisualOutput);
}


}
}
