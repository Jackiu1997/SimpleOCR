#include "utils.h"

Utils::Utils()
{

}

QJsonObject Utils::parseJson(QByteArray *bytes)
{
       QJsonParseError jsonError;
       QJsonDocument doucment = QJsonDocument::fromJson(*bytes, &jsonError);
       if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError) && doucment.isObject())
       {
           QJsonObject object = doucment.object();
           return object;
       }
       return QJsonObject();
}
