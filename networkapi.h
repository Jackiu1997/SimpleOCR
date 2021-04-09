#ifndef NETWORKAPI_H
#define NETWORKAPI_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetworkAPI : public QObject
{
    Q_OBJECT

public:
    virtual void authRequest() {};
    virtual void apiRequest(QString data) {};

signals:
    virtual void renderResult(QString);

private slots:
    virtual void authRequestSlot(QNetworkReply *reply) {};
    virtual void apiRequestSlot(QNetworkReply *reply) {};

protected:
    QString apiKey;
    QString secretKey;
    QString accessToken;

    QString authURL;
    QString apiURL;
};

class BaiduOCRAPI : public NetworkAPI
{
    Q_OBJECT

public:
    explicit BaiduOCRAPI();
    void authRequest() override;
    void apiRequest(QString data) override;

private slots:
    void authRequestSlot(QNetworkReply *reply) override;
    void apiRequestSlot(QNetworkReply *reply) override;
};

class BaiduTransAPI : public NetworkAPI
{
    Q_OBJECT

public:
    explicit BaiduTransAPI();
    void apiRequest(QString data) override;

private slots:
    void apiRequestSlot(QNetworkReply *reply) override;
};

class BaiduFormulaAPI : public NetworkAPI
{
    Q_OBJECT

public:
    explicit BaiduFormulaAPI();
    void authRequest() override;
    void apiRequest(QString data) override;

private slots:
    void authRequestSlot(QNetworkReply *reply) override;
    void apiRequestSlot(QNetworkReply *reply) override;
};

#endif // NETWORKAPI_H
