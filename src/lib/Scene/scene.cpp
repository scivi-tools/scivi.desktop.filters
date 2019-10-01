#include "scene.h"

#include <visual.h>

namespace scivi {
namespace filters {

QString Scene::getName() const
{
    return "Scene";
}

void Scene::onStart()
{
}

void Scene::consume(QVariant data, const QString &slotName)
{
    if (slotName == VisualInput) {
        Visual* d = (Visual*)(data.value<void*>());
        if (d == nullptr) {
            qWarning() << "Passed input isn't visual type";
            return;
        }
        if (m_container == nullptr) {
            qWarning() << "Passed container to render is null";
            return;
        }
        d->render(m_container);
    }
}

}
}
