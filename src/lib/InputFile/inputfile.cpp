#include "inputfile.h"

#include <QString>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QDateTime>
#include <QVariant>

namespace scivi {
namespace filters {

QString GridInputFile::getName() const
{
    return "InputFile";
}

void GridInputFile::onStart()
{
    QString pathToFile = this->m_settings[PathSetting].toString();
    QFile file(pathToFile.trimmed());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "File (" << pathToFile << ") for input doesn't exists!";
        return;
    }

    QVector<QDateTime> vecx;
    QVector<qreal> vecy;
    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList params = line.split("\t", QString::SkipEmptyParts);
        QDateTime x = QDateTime::fromString(params.at(0), "HH:mm:ss");
        qreal y = params.at(1).toFloat();
        vecx.append(x);
        vecy.append(y);
    }
    file.close();
    emit produced(qVariantFromValue(vecx), XOutput);
    emit produced(qVariantFromValue(vecy), YOutput);
}

void GridInputFile::consume(QVariant data, const QString &slotName)
{
    Q_UNUSED(data);
    Q_UNUSED(slotName);
}

}
}
