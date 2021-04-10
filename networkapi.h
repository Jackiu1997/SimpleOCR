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
    QString authURL;
    QString apiURL;
};

#endif // NETWORKAPI_H
