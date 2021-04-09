#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QJsonObject>
#include <QObject>

class AppSettings : public QObject
{
    Q_OBJECT
public:
    explicit AppSettings(QObject *parent = nullptr);
    ~AppSettings();

    bool getWatchClipboard() const;
    void setWatchClipboard(bool value);

    bool getSelectWordTranslate() const;
    void setSelectWordTranslate(bool value);

    bool getStartWithBoot() const;
    void setStartWithBoot(bool value);

    bool getPunctuationReplace() const;
    void setPunctuationReplace(bool value);

    bool getLeftCornerScreenshot() const;
    void setLeftCornerScreenshot(bool value);

    bool getResultDialogFollow() const;
    void setResultDialogFollow(bool value);

    bool getResultAutoCopy() const;
    void setResultAutoCopy(bool value);

    bool getResultAutoFocus() const;
    void setResultAutoFocus(bool value);

    bool getResultAutoRead() const;
    void setResultAutoRead(bool value);

private:
    QJsonObject jsonSettings;

    bool watchClipboard = false;
    bool selectWordTranslate = false;
    bool startWithBoot = false;
    bool punctuationReplace = false;
    bool leftCornerScreenshot = false;
    bool resultDialogFollow = false;
    bool resultAutoCopy = false;
    bool resultAutoFocus = false;
    bool resultAutoRead = false;

    void loadSettings();
    void saveSettings();
};

#endif // APPSETTINGS_H
