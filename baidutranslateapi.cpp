#include "baidutranslateapi.h"
#include "utils.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>


BaiduTranslateAPI::BaiduTranslateAPI(QJsonObject config)
{
    apiKey = config.contains("apiKey") && !config.value("apiKey").toString().isEmpty()
            ? config.value("apiKey").toString()
            : "20210409000769586";
    secretKey = config.contains("secretKey") && !config.value("secretKey").toString().isEmpty()
            ? config.value("secretKey").toString()
            : "k3S3YiT4tvEpIdZv6h8o";
    apiURL = config.contains("apiURL") && !config.value("apiURL").toString().isEmpty()
            ? config.value("apiURL").toString()
            : "https://fanyi-api.baidu.com/api/trans/vip/translate";
}

void BaiduTranslateAPI::apiRequest(QString data)
{
    // 拼接授权信息字符串
    QString salt = "1435660288";
    QString signOrgin = apiKey + data + salt + secretKey;
    QString signMD5 = QCryptographicHash::hash(signOrgin.toUtf8(), QCryptographicHash::Md5).toHex();

    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(apiRequestSlot(QNetworkReply*)));

    QNetworkRequest request;
    request.setUrl(QUrl(apiURL));
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("q=" + data.toUtf8().toPercentEncoding()); // urlencode编码（否则失败）
    postData.append("&from=auto&to=zh&appid=" + apiKey +"&salt=" + salt +"&sign=" + signMD5);
    accessManager->post(request, postData);
}

void BaiduTranslateAPI::apiRequestSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        // 处理获取图像处理结果并回传
        QString result;
        QJsonObject object = Utils::parseJson(&bytes);
        if (object.contains("trans_result")) {
            QJsonValue value = object.value("trans_result");
            if (value.isArray())
            {
                QJsonArray array = value.toArray();
                for (auto it: array)
                {
                    QJsonValue words = it.toObject().value("dst");
                    result += words.toString();
                }
            }
        }
        else if (object.contains("error_code")) {
            result = object.value("error_code").toString();
        }
        emit renderResult(result);
    }
    else
    {
        qDebug() << "apiRequestSlot error:" << (int)reply->error()  << ", " << reply->errorString();
    }
    reply->deleteLater();
}
