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
    void on_watchClipboard_clicked(bool );

    void on_resultAutoRead_clicked(bool );

    void on_selectWordTranslate_clicked(bool );

    void on_startWithBoot_clicked(bool );

    void on_punctuationReplace_clicked(bool );

    void on_leftCornerScreenshot_clicked(bool );

    void on_resultDialogFollow_clicked(bool );

    void on_resultAutoCopy_clicked(bool );

    void on_resultAutoFocus_clicked(bool );

private:
    Ui::SettingForm *ui;

    AppSettings *settings;
};

#endif // SETTINGFORM_H
