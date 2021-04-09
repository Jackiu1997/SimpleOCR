#include "appsettings.h"
#include "utils.h"

#include <QFile>

AppSettings::AppSettings(QObject *parent) : QObject(parent)
{
    loadSettings();
}

AppSettings::~AppSettings()
{
    saveSettings();
}

bool AppSettings::getWatchClipboard() const
{
    return watchClipboard;
}

void AppSettings::setWatchClipboard(bool value)
{
    watchClipboard = value;
    jsonSettings.insert("watchClipboard", value);
    saveSettings();
}

bool AppSettings::getSelectWordTranslate() const
{
    return selectWordTranslate;
}

void AppSettings::setSelectWordTranslate(bool value)
{
    selectWordTranslate = value;
    jsonSettings.insert("selectWordTranslate", value);
    saveSettings();
}

bool AppSettings::getStartWithBoot() const
{
    return startWithBoot;
}

void AppSettings::setStartWithBoot(bool value)
{
    startWithBoot = value;
    jsonSettings.insert("startWithBoot", value);
    saveSettings();
}

bool AppSettings::getPunctuationReplace() const
{
    return punctuationReplace;
}

void AppSettings::setPunctuationReplace(bool value)
{
    punctuationReplace = value;
    jsonSettings.insert("punctuationReplace", value);
    saveSettings();
}

bool AppSettings::getLeftCornerScreenshot() const
{
    return leftCornerScreenshot;
}

void AppSettings::setLeftCornerScreenshot(bool value)
{
    leftCornerScreenshot = value;
    jsonSettings.insert("leftCornerScreenshot", value);
    saveSettings();
}

bool AppSettings::getResultDialogFollow() const
{
    return resultDialogFollow;
}

void AppSettings::setResultDialogFollow(bool value)
{
    resultDialogFollow = value;
    jsonSettings.insert("resultDialogFollow", value);
    saveSettings();
}

bool AppSettings::getResultAutoCopy() const
{
    return resultAutoCopy;
}

void AppSettings::setResultAutoCopy(bool value)
{
    resultAutoCopy = value;
    jsonSettings.insert("resultAutoCopy", value);
    saveSettings();
}

bool AppSettings::getResultAutoFocus() const
{
    return resultAutoFocus;
}

void AppSettings::setResultAutoFocus(bool value)
{
    resultAutoFocus = value;
    jsonSettings.insert("resultAutoFocus", value);
    saveSettings();
}

bool AppSettings::getResultAutoRead() const
{
    return resultAutoRead;
}

void AppSettings::setResultAutoRead(bool value)
{
    resultAutoRead = value;
    jsonSettings.insert("resultAutoRead", value);
    saveSettings();
}

void AppSettings::loadSettings()
{
    QFile file("app_settings.json");
    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        QByteArray bytes = file.readAll();
        jsonSettings = Utils::parseJson(&bytes);

        if (jsonSettings.contains("watchClipboard") && jsonSettings.value("watchClipboard").isBool()) {
            watchClipboard = jsonSettings.value("watchClipboard").toBool();
        } else {
            jsonSettings.insert("watchClipboard", watchClipboard);
        }

        if (jsonSettings.contains("selectWordTranslate") && jsonSettings.value("selectWordTranslate").isBool()) {
            selectWordTranslate = jsonSettings.value("selectWordTranslate").toBool();
        } else {
            jsonSettings.insert("selectWordTranslate", selectWordTranslate);
        }

        if (jsonSettings.contains("startWithBoot") && jsonSettings.value("startWithBoot").isBool()) {
            startWithBoot = jsonSettings.value("startWithBoot").toBool();
        } else {
            jsonSettings.insert("startWithBoot", startWithBoot);
        }

        if (jsonSettings.contains("punctuationReplace") && jsonSettings.value("punctuationReplace").isBool()) {
            punctuationReplace = jsonSettings.value("punctuationReplace").toBool();
        } else {
            jsonSettings.insert("punctuationReplace", punctuationReplace);
        }

        if (jsonSettings.contains("leftCornerScreenshot") && jsonSettings.value("leftCornerScreenshot").isBool()) {
            leftCornerScreenshot = jsonSettings.value("leftCornerScreenshot").toBool();
        } else {
            jsonSettings.insert("leftCornerScreenshot", leftCornerScreenshot);
        }

        if (jsonSettings.contains("resultDialogFollow") && jsonSettings.value("resultDialogFollow").isBool()) {
            resultDialogFollow = jsonSettings.value("resultDialogFollow").toBool();
        } else {
            jsonSettings.insert("resultDialogFollow", resultDialogFollow);
        }

        if (jsonSettings.contains("resultAutoCopy") && jsonSettings.value("resultAutoCopy").isBool()) {
            resultAutoCopy = jsonSettings.value("resultAutoCopy").toBool();
        } else {
            jsonSettings.insert("resultAutoCopy", resultAutoCopy);
        }

        if (jsonSettings.contains("resultAutoFocus") && jsonSettings.value("resultAutoFocus").isBool()) {
            resultAutoFocus = jsonSettings.value("resultAutoFocus").toBool();
        } else {
            jsonSettings.insert("resultAutoFocus", resultAutoFocus);
        }

        if (jsonSettings.contains("resultAutoRead") && jsonSettings.value("resultAutoRead").isBool()) {
            resultAutoRead = jsonSettings.value("resultAutoRead").toBool();
        } else {
            jsonSettings.insert("resultAutoRead", resultAutoRead);
        }
    } else {
        jsonSettings = QJsonObject();
        jsonSettings.insert("watchClipboard", watchClipboard);
        jsonSettings.insert("selectWordTranslate", selectWordTranslate);
        jsonSettings.insert("startWithBoot", startWithBoot);
        jsonSettings.insert("punctuationReplace", punctuationReplace);
        jsonSettings.insert("leftCornerScreenshot", leftCornerScreenshot);
        jsonSettings.insert("resultDialogFollow", resultDialogFollow);
        jsonSettings.insert("resultAutoCopy", resultAutoCopy);
        jsonSettings.insert("resultAutoFocus", resultAutoFocus);
        jsonSettings.insert("resultAutoRead", resultAutoRead);
    }
    file.close();
}

void AppSettings::saveSettings()
{
    QFile file("app_settings.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonDocument jsonDoc;
        jsonDoc.setObject(jsonSettings);

        file.write(jsonDoc.toJson());
    }
    file.close();
}
