#ifndef AREADATETIME_H
#define AREADATETIME_H

#include "areadatetime_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QtCharts/QAbstractAxis>
#include <QQuickItem>
#include <visual.h>

QT_CHARTS_USE_NAMESPACE

namespace scivi {
namespace filters {

class AreaDatetimeVisualImpl: public Visual, QObject {
public:
    AreaDatetimeVisualImpl(QColor &color, QString axisXTitle, QString axisYTitle, QObject *parent = nullptr);
    void setData(QVector<QDateTime> *x, QVector<qreal> *y);

private:
    QColor m_color;
    QVector<qreal> m_x;
    QVector<qreal> m_y;
    QString m_axisXTitle;
    QString m_axisYTitle;
    QQuickItem* m_view { nullptr };

    // Visual interface
protected:
    void setupAxis(QAbstractAxis *axisX, QAbstractAxis *axisY);
    QQuickItem *createChartView(QQuickItem* container);
    void render(QQuickItem *container) override;
};

class AreaDatetime: public FilterImplementation
{
    Q_OBJECT
public:
    AreaDatetime(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;

    constexpr static auto ColorSetting = "color";
    constexpr static auto XInput = "x";
    constexpr static auto YInput = "y";
    constexpr static auto VisualOutput = "visual";
    constexpr static auto XTitleSetting = "xtitle";
    constexpr static auto YTitleSetting = "ytitle";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;

private:
    QSharedPointer<QVector<QDateTime>> m_x;
    QSharedPointer<QVector<qreal>> m_y;
    AreaDatetimeVisualImpl* m_visual { nullptr };
};

class AREADATETIMESHARED_EXPORT AreaDatetimeFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new AreaDatetime(parent);
    }
};

}
}

#endif // AREADATETIME_H
