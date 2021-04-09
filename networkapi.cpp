#include "networkapi.h"
#include "utils.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>


// Baidu OCR 插件 API
BaiduOCRAPI::BaiduOCRAPI()
{
    apiKey = "Q8WHLoKnlQoI8fAbgNEWhEiX";
    secretKey = "171miOFiGHp4d5ITFI0aV5lM7dGeI7n1";

    authURL = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=$apiKey&client_secret=$secretKey";
    apiURL = "https://aip.baidubce.com/rest/2.0/ocr/v1/general_basic?access_token=$accessToken";

    authRequest();
}

void BaiduOCRAPI::authRequest()
{
    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(authRequestSlot(QNetworkReply*)));

    QNetworkRequest request;
    QString requestURL = authURL.replace("$apiKey", apiKey).replace("$secretKey", secretKey);
    request.setUrl(QUrl(requestURL));
    accessManager->get(request);
}

void BaiduOCRAPI::authRequestSlot(QNetworkReply *reply)
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

void BaiduOCRAPI::apiRequest(QString data)
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

void BaiduOCRAPI::apiRequestSlot(QNetworkReply *reply)
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


// Baidu 翻译 插件 API
BaiduTransAPI::BaiduTransAPI()
{
    apiKey = "20210409000769586";
    secretKey = "k3S3YiT4tvEpIdZv6h8o";

    apiURL = "https://fanyi-api.baidu.com/api/trans/vip/translate";
}

void BaiduTransAPI::apiRequest(QString data)
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

void BaiduTransAPI::apiRequestSlot(QNetworkReply *reply)
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


// Baidu 公式 插件 API
BaiduFormulaAPI::BaiduFormulaAPI()
{
    apiKey = "Q8WHLoKnlQoI8fAbgNEWhEiX";
    secretKey = "171miOFiGHp4d5ITFI0aV5lM7dGeI7n1";

    authURL = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=$apiKey&client_secret=$secretKey";
    apiURL = "https://aip.baidubce.com/rest/2.0/ocr/v1/formula?access_token=$accessToken";

    authRequest();
}

void BaiduFormulaAPI::authRequest()
{
    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(authRequestSlot(QNetworkReply*)));

    QNetworkRequest request;
    QString requestURL = authURL.replace("$apiKey", apiKey).replace("$secretKey", secretKey);
    request.setUrl(QUrl(requestURL));
    accessManager->get(request);
}

void BaiduFormulaAPI::authRequestSlot(QNetworkReply *reply)
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

void BaiduFormulaAPI::apiRequest(QString data)
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

void BaiduFormulaAPI::apiRequestSlot(QNetworkReply *reply)
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

