#ifndef VERTICALSTACK_H
#define VERTICALSTACK_H

#include "verticalstack_global.h"
#include <filterimplementation.h>
#include <visual.h>
#include <filterfactory.h>

namespace scivi {
namespace filters {

class VerticalStackVisual: public Visual, QObject {
public:
    VerticalStackVisual(Visual* visual1, Visual* visual2, QObject *parent = nullptr): QObject(parent) {
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

class VerticalStack: public FilterImplementation
{
    Q_OBJECT
public:
    VerticalStack(QObject *parent): FilterImplementation(parent) {}

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
    VerticalStackVisual* m_visual { nullptr };
};

class VERTICALSTACKSHARED_EXPORT VerticalStackFactory: public FilterFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tools.scivi.filters.FilterFactory")
    Q_INTERFACES(scivi::filters::FilterFactory)


    // FilterFactory interface
public:
    FilterPtr create(QObject *parent) override
    {
        return new VerticalStack(parent);
    }
};

}
}

#endif // VERTICALSTACK_H
