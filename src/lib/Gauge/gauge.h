#ifndef GAUGE_H
#define GAUGE_H

#include "gauge_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>
#include <visual.h>

namespace scivi {
namespace filters {

class GaugeVisualImpl: public Visual, QObject {
    friend class Gauge;
public:
    GaugeVisualImpl(QColor &color, qreal min, qreal max, qreal value, QObject *parent = nullptr);

private:
    QColor m_color;
    qreal m_min;
    qreal m_max;
    qreal m_value;
    QQuickItem* m_view = { nullptr };

    // Visual interface
protected:
    QQuickItem *createChartView(QQuickItem* container);
    void render(QQuickItem *container) override;
};

class Gauge: public FilterImplementation
{
    Q_OBJECT
public:
    Gauge(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;
    const QString ValueInput = "value";
    const QString VisualOutput = "visual";
    const QString ColorSetting = "color";
    const QString MinSetting = "min";
    const QString MaxSetting = "max";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;

private:
    GaugeVisualImpl* m_visual = { nullptr };
};

class GaugeFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new Gauge(parent);
    }
};

}
}

#endif // GAUGE_H
