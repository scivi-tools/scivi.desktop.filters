#include "verticalstack.h"

#include <QQmlEngine>

namespace scivi {
namespace filters {

QString VerticalStack::getName() const
{
    return "VerticalStack";
}

void VerticalStack::onStart()
{
}

void VerticalStack::consume(QVariant data, const QString &slotName)
{
    if (slotName == VisualInput1) {
        m_visual1 = (Visual*)data.value<void*>();
    }
    if (slotName == VisualInput2) {
        m_visual2 = (Visual*)data.value<void*>();
    }
    if (m_visual1 != nullptr && m_visual2 != nullptr) {
        if (!m_visual) {
            m_visual = new VerticalStackVisual(m_visual1, m_visual2);
        }
        emit produced(qVariantFromValue((void*)m_visual), VisualOutput);
    }
}

void VerticalStackVisual::render(QQuickItem *container)
{
    if (m_visual1 == nullptr) {
        qWarning() << "Visual1 is null";
        return;
    }
    if (m_visual2 == nullptr) {
        qWarning() << "Visual2 is null";
        return;
    }
    if (!m_view) {
        QQmlEngine *engine = new QQmlEngine(container);
        QQmlComponent linearQmlComponent(engine, "qrc:/VerticalStack.qml", QQmlComponent::PreferSynchronous);
        if (!linearQmlComponent.isReady() || linearQmlComponent.isError() || linearQmlComponent.isNull()) {
            return;
        }

        m_view = qobject_cast<QQuickItem*>(linearQmlComponent.create());
        m_view->setParentItem(container);
    }
    auto visual1Container = m_view->property("visual1Container").value<QQuickItem*>();
    auto visual2Container = m_view->property("visual2Container").value<QQuickItem*>();
    m_visual1->render(visual1Container);
    m_visual2->render(visual2Container);
}

}
}
