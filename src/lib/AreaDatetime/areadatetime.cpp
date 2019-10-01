#include "areadatetime.h"

#include <QQmlEngine>
#include <limits>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QVector>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QValueAxis*)
Q_DECLARE_METATYPE(QLineSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)

namespace scivi {
namespace filters {

AreaDatetimeVisualImpl::AreaDatetimeVisualImpl(QColor &color, QString axisXTitle, QString axisYTitle, QObject *parent)
    : QObject(parent)
{
    m_color = color;
    m_axisXTitle = axisXTitle;
    m_axisYTitle = axisYTitle;
}

void AreaDatetimeVisualImpl::setData(QVector<QDateTime> *x, QVector<qreal> *y)
{
    m_x.clear();
    m_y.clear();
    for (auto &xi: *x) {
        this->m_x.append(xi.toMSecsSinceEpoch());
    }
    for (const auto &yi: *y) {
        this->m_y.append(yi);
    }
}

void AreaDatetimeVisualImpl::setupAxis(QAbstractAxis *axisX, QAbstractAxis *axisY)
{
    QDateTimeAxis *dateTimeXAxis = qobject_cast<QDateTimeAxis*>(axisX);
    QValueAxis *realYAxis = qobject_cast<QValueAxis*>(axisY);
    auto minY = std::numeric_limits<qreal>::max();
    auto maxY = std::numeric_limits<qreal>::min();
    for (const auto &yi: m_y) {
        if (yi < minY) minY = yi;
        if (yi > maxY) maxY = yi;
    }
    realYAxis->setMin(minY - (maxY-minY) * 0.1);
    realYAxis->setMax(maxY + (maxY-minY) * 0.1);
    realYAxis->setTitleText(m_axisYTitle);
    QDateTime lastDateTime = QDateTime::fromMSecsSinceEpoch(m_x.first());
    bool isInOneDay = true;
    for (const auto &xi: m_x) {
        if (lastDateTime.date() != QDateTime::fromMSecsSinceEpoch(xi).date()) {
            isInOneDay = false;
            break;
        }
    }
    dateTimeXAxis->setTitleText(m_axisXTitle);
    dateTimeXAxis->setMin(QDateTime::fromMSecsSinceEpoch(m_x.first()));
    dateTimeXAxis->setMax(QDateTime::fromMSecsSinceEpoch(m_x.last()));
    if (!isInOneDay) {
        dateTimeXAxis->setFormat("dd.MM.yyyy");
    } else {
        dateTimeXAxis->setFormat("HH:mm:ss");
    }
}

QQuickItem *AreaDatetimeVisualImpl::createChartView(QQuickItem *container)
{
    QQmlEngine *engine = new QQmlEngine(container);
    QQmlComponent linearQmlComponent(engine, "qrc:/AreaDatetime.qml", QQmlComponent::PreferSynchronous);
    if (!linearQmlComponent.isReady() || linearQmlComponent.isError() || linearQmlComponent.isNull()) {
        return nullptr;
    }

    QQuickItem* chartView = qobject_cast<QQuickItem*>(linearQmlComponent.create());
    chartView->setParentItem(container);
    return chartView;
}

void AreaDatetimeVisualImpl::render(QQuickItem *container)
{
    if (m_x.isEmpty() || m_y.isEmpty()) {
        qWarning() << "Data is empty";
        return;
    }
    if (!m_view) {
        m_view = createChartView(container);
        m_view->setParentItem(container);
        m_view->setProperty("color", this->m_color);
    }
    QAbstractAxis *axisX = m_view->property("axisX").value<QAbstractAxis*>();
    QAbstractAxis *axisY = m_view->property("axisY").value<QAbstractAxis*>();
    if (axisX == nullptr || axisY == nullptr) {
        qWarning() << "Axis are null";
        return;
    }
    setupAxis(axisX, axisY);
    QLineSeries *series = m_view->property("series").value<QLineSeries*>();
    series->clear();
    int count = m_x.size();
    for (int i = 0; i < count; i++) {
        series->append(m_x[i], m_y[i]);
    }
}

QString AreaDatetime::getName() const
{
    return "AreaDatetime";
}

void AreaDatetime::onStart()
{

}

void AreaDatetime::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(data);
    Q_UNUSED(slotName);
    if (slotName == XInput) {
        QVector<QDateTime> x = data.value<QVector<QDateTime>>();
        m_x = QSharedPointer<QVector<QDateTime>>::create(x);
    }
    if (slotName == YInput) {
        QVector<qreal> y = data.value<QVector<qreal>>();
        m_y = QSharedPointer<QVector<qreal>>::create(y);
    }
    if (!m_x.isNull() && !m_y.isNull()) {
        auto color = m_settings[ColorSetting].value<QColor>();
        auto xTitle = m_settings[XTitleSetting].toString();
        auto yTitle = m_settings[YTitleSetting].toString();
        if (!m_visual) {
            m_visual = new AreaDatetimeVisualImpl(color, xTitle, yTitle, this);
        }
        m_visual->setData(m_x.data(), m_y.data());
        emit produced(qVariantFromValue((void*)m_visual), VisualOutput);
    }
}

}
}
