#include "baidubcsapi.h"
#include "utils.h"

#include <QJsonArray>
#include <QJsonObject>

BaiduBcsAPI::BaiduBcsAPI(QJsonObject config)
{
    apiKey = config.contains("apiKey") && !config.value("apiKey").toString().isEmpty()
            ? config.value("apiKey").toString()
            : "Q8WHLoKnlQoI8fAbgNEWhEiX";
    secretKey = config.contains("secretKey") && !config.value("secretKey").toString().isEmpty()
            ? config.value("secretKey").toString()
            : "171miOFiGHp4d5ITFI0aV5lM7dGeI7n1";
    authURL = config.contains("authURL") && !config.value("authURL").toString().isEmpty()
            ? config.value("authURL").toString()
            : "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=$apiKey&client_secret=$secretKey";
    apiURL = config.contains("apiURL") && !config.value("apiURL").toString().isEmpty()
            ? config.value("apiURL").toString()
            : "";

    authRequest();
}

void BaiduBcsAPI::authRequest()
{
    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(authRequestSlot(QNetworkReply*)));

    QNetworkRequest request;
    QString requestURL = authURL.replace("$apiKey", apiKey).replace("$secretKey", secretKey);
    request.setUrl(QUrl(requestURL));
    accessManager->get(request);
}

void BaiduBcsAPI::authRequestSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        // 处理获取accessToken
        QJsonObject object = Utils::parseJson(&bytes);
        if (object.contains("access_token")) {
            accessToken = object.value("access_token").toString();
        }
    }
    else
    {
        qDebug() << "authRequestSlot error:" << (int)reply->error()  << ", " << reply->errorString();
    }
    reply->deleteLater();
}

void BaiduBcsAPI::apiRequest(QString data)
{
    if (!accessToken.isEmpty())
    {
        QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
        connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(apiRequestSlot(QNetworkReply*)));

        QNetworkRequest request;
        QString requestURL = apiURL.replace("$accessToken", accessToken);
        request.setUrl(QUrl(requestURL));
        request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        QByteArray postData;
        postData.append("image=" + data.toUtf8().toPercentEncoding()); // urlencode编码（否则失败）
        accessManager->post(request, postData);
    }
    else
    {
        authRequest();
        qDebug() << "Bad AccessToken Call";
    }
}

void BaiduBcsAPI::apiRequestSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        // 处理获取图像处理结果并回传
        QString result;
        QJsonObject object = Utils::parseJson(&bytes);
        if (object.contains("words_result")) {
            QJsonValue value = object.value("words_result");
            if (value.isArray())
            {
                QJsonArray array = value.toArray();
                for (auto it: array)
                {
                    QJsonValue words = it.toObject().value("words");
                    result += words.toString();
                }
            }
        }
        else if (object.contains("error_msg")) {
            result = object.value("error_msg").toString();
        }
        emit renderResult(result);
    }
    else
    {
        qDebug() << "apiRequestSlot error:" << (int)reply->error()  << ", " << reply->errorString();
    }
    reply->deleteLater();
}
