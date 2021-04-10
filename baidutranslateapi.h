#ifndef BAIDUTRANSLATEAPI_H
#define BAIDUTRANSLATEAPI_H

#include "networkapi.h"


class BaiduTranslateAPI : public NetworkAPI
{
    Q_OBJECT

public:
    explicit BaiduTranslateAPI(QJsonObject config);
    void apiRequest(QString data) override;

private slots:
    void apiRequestSlot(QNetworkReply *reply) override;
};

#endif // BAIDUTRANSLATEAPI_H
