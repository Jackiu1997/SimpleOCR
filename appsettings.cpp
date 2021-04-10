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

int AppSettings::getOcrEngineOption() const
{
    return ocrEngineOption;
}

void AppSettings::setOcrEngineOption(int value)
{
    ocrEngineOption = value;
    jsonSettings.insert("ocrEngineOption", value);
    saveSettings();
}

int AppSettings::getTranslateEngineOption() const
{
    return translateEngineOption;
}

void AppSettings::setTranslateEngineOption(int value)
{
    translateEngineOption = value;
    jsonSettings.insert("translateEngineOption", value);
    saveSettings();
}

int AppSettings::getFormulaEngineOption() const
{
    return formulaEngineOption;
}

void AppSettings::setFormulaEngineOption(int value)
{
    formulaEngineOption = value;
    jsonSettings.insert("formulaEngineOption", value);
    saveSettings();
}

QJsonObject AppSettings::getOcrEngineConf() const
{
    return ocrEngines.size() > ocrEngineOption
            ? ocrEngines.at(ocrEngineOption).toObject()
            : QJsonObject();
}

QJsonObject AppSettings::getTranslateEngineConf() const
{
    return translateEngines.size() > translateEngineOption
            ? translateEngines.at(translateEngineOption).toObject()
            : QJsonObject();
}

QJsonObject AppSettings::getFormulaEngineConf() const
{
    return formulaEngines.size() > formulaEngineOption
            ? formulaEngines.at(formulaEngineOption).toObject()
            : QJsonObject();
}

QJsonArray AppSettings::getOcrEngines() const
{
    return ocrEngines;
}

void AppSettings::setOcrEngines(const QJsonArray &value)
{
    ocrEngines = value;
    jsonSettings.insert("ocrEngines", ocrEngines);
}

QJsonArray AppSettings::getTranslateEngines() const
{
    return translateEngines;
}

void AppSettings::setTranslateEngines(const QJsonArray &value)
{
    translateEngines = value;
    jsonSettings.insert("translateEngines", translateEngines);
}

QJsonArray AppSettings::getFormulaEngines() const
{
    return formulaEngines;
}

void AppSettings::setFormulaEngines(const QJsonArray &value)
{
    formulaEngines = value;
    jsonSettings.insert("formulaEngines", formulaEngines);
}

void AppSettings::loadSettings()
{
    jsonSettings = QJsonObject();
    
    QFile file("app_settings.json");
    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        QByteArray bytes = file.readAll();
        jsonSettings = Utils::parseJson(&bytes);

        // Switch设置选项读取
        watchClipboard = jsonSettings.contains("watchClipboard")
                ? jsonSettings.value("watchClipboard").toBool()
                : false;
        selectWordTranslate = jsonSettings.contains("selectWordTranslate")
                ? jsonSettings.value("selectWordTranslate").toBool()
                : false;
        startWithBoot = jsonSettings.contains("startWithBoot")
                ? jsonSettings.value("startWithBoot").toBool()
                : false;
        punctuationReplace = jsonSettings.contains("punctuationReplace")
                ? jsonSettings.value("punctuationReplace").toBool()
                : false;
        leftCornerScreenshot = jsonSettings.contains("leftCornerScreenshot")
                ? jsonSettings.value("leftCornerScreenshot").toBool()
                : false;
        resultDialogFollow = jsonSettings.contains("resultDialogFollow")
                ? jsonSettings.value("resultDialogFollow").toBool()
                : false;
        resultAutoCopy = jsonSettings.contains("resultAutoCopy")
                ? jsonSettings.value("resultAutoCopy").toBool()
                : false;
        resultAutoFocus = jsonSettings.contains("resultAutoFocus")
                ? jsonSettings.value("resultAutoFocus").toBool()
                : false;
        resultAutoRead = jsonSettings.contains("resultAutoRead")
                ? jsonSettings.value("resultAutoRead").toBool()
                : false;

        // 引擎选择读取
        ocrEngineOption = jsonSettings.contains("ocrEngineOption")
                ? jsonSettings.value("ocrEngineOption").toInt()
                : 0;
        translateEngineOption = jsonSettings.contains("translateEngineOption")
                ? jsonSettings.value("translateEngineOption").toInt()
                : 0;
        formulaEngineOption = jsonSettings.contains("formulaEngineOption")
                ? jsonSettings.value("formulaEngineOption").toInt()
                : 0;

        // 引擎配置读取
        ocrEngines = jsonSettings.contains("ocrEngines")
                ? jsonSettings.value("ocrEngines").toArray()
                : QJsonArray();
        translateEngines = jsonSettings.contains("translateEngines")
                ? jsonSettings.value("translateEngines").toArray()
                : QJsonArray();
        formulaEngines = jsonSettings.contains("formulaEngines")
                ? jsonSettings.value("formulaEngines").toArray()
                : QJsonArray();
    }
    file.close();
}

void AppSettings::saveSettings()
{
    QFile file("app_settings.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonDocument jsonDoc;

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

        jsonSettings.insert("ocrEngineOption", ocrEngineOption);
        jsonSettings.insert("translateEngineOption", translateEngineOption);
        jsonSettings.insert("formulaEngineOption", formulaEngineOption);

        jsonSettings.insert("ocrEngines", ocrEngines);
        jsonSettings.insert("translateEngines", translateEngines);
        jsonSettings.insert("formulaEngines", formulaEngines);

        jsonDoc.setObject(jsonSettings);
        file.write(jsonDoc.toJson());
    }
    file.close();
}
