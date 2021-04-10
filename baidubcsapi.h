#ifndef BAIDUBCSAPI_H
#define BAIDUBCSAPI_H

#include "networkapi.h"


class BaiduBcsAPI : public NetworkAPI
{
    Q_OBJECT

public:
    explicit BaiduBcsAPI(QJsonObject object);
    void authRequest() override;
    void apiRequest(QString data) override;

private slots:
    void authRequestSlot(QNetworkReply *reply) override;
    void apiRequestSlot(QNetworkReply *reply) override;

protected:
    QString accessToken;
};

#endif // BAIDUBCSAPI_H
