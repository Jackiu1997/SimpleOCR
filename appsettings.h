#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QJsonArray>
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

    int getOcrEngineOption() const;
    void setOcrEngineOption(int value);

    int getTranslateEngineOption() const;
    void setTranslateEngineOption(int value);

    int getFormulaEngineOption() const;
    void setFormulaEngineOption(int value);

    QJsonObject getOcrEngineConf() const;
    QJsonObject getTranslateEngineConf() const;
    QJsonObject getFormulaEngineConf() const;

    QJsonArray getOcrEngines() const;
    void setOcrEngines(const QJsonArray &value);

    QJsonArray getTranslateEngines() const;
    void setTranslateEngines(const QJsonArray &value);

    QJsonArray getFormulaEngines() const;
    void setFormulaEngines(const QJsonArray &value);

private:
    QJsonObject jsonSettings;

    // Switch 设置选项
    bool watchClipboard = false;
    bool selectWordTranslate = false;
    bool startWithBoot = false;
    bool punctuationReplace = false;
    bool leftCornerScreenshot = false;
    bool resultDialogFollow = false;
    bool resultAutoCopy = false;
    bool resultAutoFocus = false;
    bool resultAutoRead = false;

    // 引擎选择
    int ocrEngineOption = 0;
    int translateEngineOption = 0;
    int formulaEngineOption = 0;

    // 引擎配置
    QJsonArray ocrEngines = QJsonArray();
    QJsonArray translateEngines = QJsonArray();
    QJsonArray formulaEngines = QJsonArray();

    void loadSettings();
    void saveSettings();
};

#endif // APPSETTINGS_H
