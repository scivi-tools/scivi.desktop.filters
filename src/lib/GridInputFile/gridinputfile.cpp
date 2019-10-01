#include "gridinputfile.h"

#include <QString>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QTextStream>
#include <QVector3D>

namespace scivi {
namespace filters {

QString GridInputFile::getName() const
{
    return "GridInputFile";
}

void GridInputFile::onStart()
{
    QString pathToFile = this->m_settings[PathSetting].toString();
    QFile file(pathToFile.trimmed());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "File (" << pathToFile << ") for input doesn't exists!";
        return;
    }
    int width = 0, height = 0;

    QVector<QVector3D> vertices;

    bool ok = true;
    QString line;
    QStringList buf;
    line = file.readLine();
    buf = line.split(' ');
    if (buf.size() != 2) {
        qWarning() << "Wrong file format";
        file.close();
        return;
    }
    width = buf.at(0).toInt();
    height = buf.at(1).toInt();
    vertices.reserve(width * height);
    for (int i = 0; i < height; i++) {
        line = file.readLine();
        buf = line.split(' ');
        if (buf.size() < width) {
            qWarning() << "Wrong file format";
            break;
        }
        for (int j = 0; j < width; j++) {
            float value = buf.at(j).toFloat(&ok);
            if (!ok) {
                qWarning() << "Couldn't parse grid value";
                break;
            }
            float x = static_cast<float>(j);
            float y = static_cast<float>(i);
            float z = value;
            vertices.append(QVector3D(x, y, z));
        }
    }
    file.close();
    emit produced(qVariantFromValue(width), WidthOutput);
    emit produced(qVariantFromValue(height), HeightOutput);
    emit produced(qVariantFromValue(vertices), VerticesOutput);
}

void GridInputFile::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(data);
    Q_UNUSED(slotName);
}

}
}
