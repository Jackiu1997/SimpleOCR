#include "settingform.h"
#include "ui_settingform.h"

SettingForm::SettingForm(QWidget *parent, AppSettings *settings) :
    QWidget(parent),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);

    this->settings = settings;

    ui->watchClipboard->SetSelected(settings->getWatchClipboard());
    ui->selectWordTranslate->SetSelected(settings->getSelectWordTranslate());
    ui->startWithBoot->SetSelected(settings->getStartWithBoot());
    ui->punctuationReplace->SetSelected(settings->getPunctuationReplace());
    ui->leftCornerScreenshot->SetSelected(settings->getLeftCornerScreenshot());
    ui->resultDialogFollow->SetSelected(settings->getResultDialogFollow());
    ui->resultAutoCopy->SetSelected(settings->getResultAutoCopy());
    ui->resultAutoFocus->SetSelected(settings->getResultAutoFocus());
    ui->resultAutoRead->SetSelected(settings->getResultAutoRead());
}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::on_watchClipboard_clicked(bool isSelected)
{
    settings->setWatchClipboard(isSelected);
}

void SettingForm::on_selectWordTranslate_clicked(bool isSelected)
{
    settings->setSelectWordTranslate(isSelected);
}

void SettingForm::on_startWithBoot_clicked(bool isSelected)
{
    settings->setStartWithBoot(isSelected);
}

void SettingForm::on_punctuationReplace_clicked(bool isSelected)
{
    settings->setPunctuationReplace(isSelected);
}

void SettingForm::on_leftCornerScreenshot_clicked(bool isSelected)
{
    settings->setLeftCornerScreenshot(isSelected);
}

void SettingForm::on_resultDialogFollow_clicked(bool isSelected)
{
    settings->setResultDialogFollow(isSelected);
}

void SettingForm::on_resultAutoCopy_clicked(bool isSelected)
{
    settings->setResultAutoCopy(isSelected);
}

void SettingForm::on_resultAutoFocus_clicked(bool isSelected)
{
    settings->setResultAutoFocus(isSelected);
}

void SettingForm::on_resultAutoRead_clicked(bool isSelected)
{
    settings->setResultAutoRead(isSelected);
}
