#include "settingform.h"
#include "ui_settingform.h"

SettingForm::SettingForm(QWidget *parent, AppSettings *settings) :
    QWidget(parent),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() &~ Qt::WindowMinMaxButtonsHint);

    this->settings = settings;

    // 设置 switch button 状态
    ui->watchClipboard->SetSelected(settings->getWatchClipboard());
    ui->selectWordTranslate->SetSelected(settings->getSelectWordTranslate());
    ui->startWithBoot->SetSelected(settings->getStartWithBoot());
    ui->punctuationReplace->SetSelected(settings->getPunctuationReplace());
    ui->leftCornerScreenshot->SetSelected(settings->getLeftCornerScreenshot());
    ui->resultDialogFollow->SetSelected(settings->getResultDialogFollow());
    ui->resultAutoCopy->SetSelected(settings->getResultAutoCopy());
    ui->resultAutoFocus->SetSelected(settings->getResultAutoFocus());
    ui->resultAutoRead->SetSelected(settings->getResultAutoRead());

    // 设置 combobox 状态
    lastOcrEngineOption = settings->getOcrEngineOption();
    lastTranslateEngineOption = settings->getTranslateEngineOption();
    lastFormulaEngineOption = settings->getFormulaEngineOption();

    ui->ocrEngineOption->setCurrentIndex(lastOcrEngineOption);
    ui->translateEngineOption->setCurrentIndex(lastTranslateEngineOption);
    ui->formulaEngineOption->setCurrentIndex(lastFormulaEngineOption);

    // 设置 API 设置 文字
    ocrEngines = settings->getOcrEngines();
    translateEngines = settings->getTranslateEngines();
    formulaEngines = settings->getFormulaEngines();

    on_ocrEngineOption_currentIndexChanged(lastOcrEngineOption);
    on_translateEngineOption_currentIndexChanged(lastTranslateEngineOption);
    on_formulaEngineOption_currentIndexChanged(lastFormulaEngineOption);
}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::on_saveSettingButton_pressed()
{
    // 保存设置选项
    settings->setWatchClipboard(ui->watchClipboard->IsSelected());
    settings->setSelectWordTranslate(ui->selectWordTranslate->IsSelected());
    settings->setStartWithBoot(ui->startWithBoot->IsSelected());
    settings->setPunctuationReplace(ui->punctuationReplace->IsSelected());
    settings->setLeftCornerScreenshot(ui->leftCornerScreenshot->IsSelected());
    settings->setResultDialogFollow(ui->resultDialogFollow->IsSelected());
    settings->setResultAutoCopy(ui->resultAutoCopy->IsSelected());
    settings->setResultAutoFocus(ui->resultAutoFocus->IsSelected());
    settings->setResultAutoRead(ui->resultAutoRead->IsSelected());

    // 保存引擎选择
    settings->setOcrEngineOption(ui->ocrEngineOption->currentIndex());
    settings->setTranslateEngineOption(ui->translateEngineOption->currentIndex());
    settings->setFormulaEngineOption(ui->formulaEngineOption->currentIndex());

    // 保存 API 接口设置
    settings->setOcrEngines(ocrEngines);
    settings->setTranslateEngines(translateEngines);
    settings->setFormulaEngines(formulaEngines);

    this->close();
}

void SettingForm::on_exitSettingButton_pressed()
{
    this->close();
}

void SettingForm::on_ocrEngineOption_currentIndexChanged(int index)
{
    // 保存修改信息
    QJsonObject config = ocrEngines.at(lastOcrEngineOption).toObject();
    if (ui->ocrApiKeyEdit->isModified() || ui->ocrSecretKeyEdit->isModified()) {
        config.insert("apiKey", ui->ocrApiKeyEdit->text());
        config.insert("secretKey", ui->ocrSecretKeyEdit->text());
        ocrEngines.replace(lastOcrEngineOption, config);
    }

    // 更新接口信息
    lastOcrEngineOption = index;
    if (ocrEngines.size() > index)
    {
        QJsonObject config = ocrEngines.at(index).toObject();
        ui->ocrApiKeyEdit->setText(config.value("apiKey").toString());
        ui->ocrSecretKeyEdit->setText(config.value("secretKey").toString());
    }
    else {
        ui->ocrApiKeyEdit->setText("");
        ui->ocrSecretKeyEdit->setText("");
    }
}

void SettingForm::on_translateEngineOption_currentIndexChanged(int index)
{
    // 保存修改信息
    QJsonObject config = translateEngines.at(lastTranslateEngineOption).toObject();
    if (ui->translateApiKeyEdit->isModified() || ui->translateSecretKeyEdit->isModified()) {
        config.insert("apiKey", ui->translateApiKeyEdit->text());
        config.insert("secretKey", ui->translateSecretKeyEdit->text());
        translateEngines.replace(lastTranslateEngineOption, config);
    }

    // 更新接口信息
    lastTranslateEngineOption = index;
    if (translateEngines.size() > index)
    {
        QJsonObject config = translateEngines.at(index).toObject();
        ui->translateApiKeyEdit->setText(config.value("apiKey").toString());
        ui->translateSecretKeyEdit->setText(config.value("secretKey").toString());
    }
    else {
        ui->translateApiKeyEdit->setText("");
        ui->translateSecretKeyEdit->setText("");
    }
}

void SettingForm::on_formulaEngineOption_currentIndexChanged(int index)
{
    // 保存修改信息
    QJsonObject config = formulaEngines.at(lastFormulaEngineOption).toObject();
    if (ui->formulaApiKeyEdit->isModified() || ui->formulaSecretKeyEdit->isModified()) {
        config.insert("apiKey", ui->formulaApiKeyEdit->text());
        config.insert("secretKey", ui->formulaSecretKeyEdit->text());
        formulaEngines.replace(lastFormulaEngineOption, config);
    }

    // 更新接口信息
    lastFormulaEngineOption = index;
    if (formulaEngines.size() > index)
    {
        QJsonObject config = formulaEngines.at(index).toObject();
        ui->formulaApiKeyEdit->setText(config.value("apiKey").toString());
        ui->formulaSecretKeyEdit->setText(config.value("secretKey").toString());
    }
    else {
        ui->formulaApiKeyEdit->setText("");
        ui->formulaSecretKeyEdit->setText("");
    }
}
