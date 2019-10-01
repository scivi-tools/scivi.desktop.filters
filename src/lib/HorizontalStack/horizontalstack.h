#ifndef HORIZONTALSTACK_H
#define HORIZONTALSTACK_H

#include "horizontalstack_global.h"
#include <filterimplementation.h>
#include <filterfactory.h>
#include <QDebug>
#include <visual.h>

namespace scivi {
namespace filters {

class HorizontalStackVisual: public Visual, QObject {
public:
    HorizontalStackVisual(Visual* visual1, Visual* visual2, QObject *parent = nullptr): QObject(parent) {
        m_visual1 = visual1;
        m_visual2 = visual2;
    }

private:
    Visual* m_visual1;
    Visual* m_visual2;
    QQuickItem* m_view { nullptr };

    // Visual interface
public:
    void render(QQuickItem *container) override;
};

class HorizontalStack: public FilterImplementation
{
    Q_OBJECT
public:
    HorizontalStack(QObject *parent): FilterImplementation(parent) {}
    // FilterImplementation interface
public:
    QString getName() const override;
    const QString VisualInput1 = "visual1";
    const QString VisualInput2 = "visual2";
    const QString VisualOutput = "visual";

public slots:
    void onStart() override;
    void consume(QVariant data, const QString &slotName) override;

private:
    Visual* m_visual1 {nullptr};
    Visual* m_visual2 {nullptr};
    HorizontalStackVisual* m_visual { nullptr };
};

class HorizontalStackFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)

    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new HorizontalStack(parent);
    }
};

}
}

#endif // HORIZONTALSTACK_H
