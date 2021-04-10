#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include "appsettings.h"

#include <QWidget>

namespace Ui {
class SettingForm;
}

class SettingForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingForm(QWidget *parent = nullptr, AppSettings *settings = nullptr);
    ~SettingForm();

private slots:
    void on_saveSettingButton_pressed();
    void on_exitSettingButton_pressed();

    void on_ocrEngineOption_currentIndexChanged(int index);

    void on_translateEngineOption_currentIndexChanged(int index);

    void on_formulaEngineOption_currentIndexChanged(int index);

private:
    Ui::SettingForm *ui;

    AppSettings *settings;

    QJsonArray ocrEngines;
    QJsonArray translateEngines;
    QJsonArray formulaEngines;

    int lastOcrEngineOption;
    int lastTranslateEngineOption;
    int lastFormulaEngineOption;
};

#endif // SETTINGFORM_H
