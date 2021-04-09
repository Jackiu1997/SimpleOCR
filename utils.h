#ifndef UTILS_H
#define UTILS_H

#include <QJsonObject>
#include <QJsonParseError>

class Utils
{
public:
    Utils();

    static QJsonObject parseJson(QByteArray *bytes);
};

#endif // UTILS_H
