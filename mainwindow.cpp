#include "mainwindow.h"
#include "settingform.h"
#include "./ui_mainwindow.h"
#include "networkapi.h"
#include "mainwindow.h"
#include "clipboardthread.h"
#include "baidubcsapi.h"
#include "baidutranslateapi.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QBuffer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textRadioButtton->setChecked(true); // 默认为 OCR 模式

    initSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSettings()
{
    settings = new AppSettings();

    clipboard = QApplication::clipboard();
    if (settings->getWatchClipboard()) {
        ClipboardThread *clipboardThread = new ClipboardThread(clipboard);
        connect(clipboardThread, SIGNAL(callClipboard()), this, SLOT(on_copyButton_pressed()));
        clipboardThread->start();
    }

    ocrApi = new BaiduBcsAPI(settings->getOcrEngineConf());
    translateApi = new BaiduTranslateAPI(settings->getTranslateEngineConf());
    formulaApi = new BaiduBcsAPI(settings->getFormulaEngineConf());
}

void MainWindow::on_shotButton_pressed()
{

}

void MainWindow::on_imageButton_pressed()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选取进行OCR的图片"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("图像 (*.png *.jpg *jpeg *.bmp)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    if (fileDialog->exec())
    {
        QImage *img = new QImage;
        if (img->load(fileDialog->selectedFiles()[0]))
        {
            // 按QLabel窗口大小缩放图像
            QImage scaledImg = img->scaled(ui->inputEdit->size().width(),
                                           ui->inputEdit->size().height(),
                                           Qt::KeepAspectRatio);
            ui->inputEdit->setPixmap(QPixmap::fromImage(scaledImg));
            ui->inputEdit->setAlignment(Qt::AlignCenter);

            callForResult(*img);
        }
        else
        {
            QMessageBox::information(this, tr("打开图像失败"), tr("打开图像失败!"));
        }
    }
}

void MainWindow::on_copyButton_pressed()
{
    QString selectedText = clipboard->text();
    QImage selectedQImage = clipboard->image();
    if (!selectedText.isEmpty())
    {
         ui->inputEdit->setText(selectedText);
         ui->inputEdit->setAlignment(Qt::AlignTop);

         callForResult(selectedText);
    }
    else if (!selectedQImage.isNull())
    {
        QImage scaledImg = selectedQImage.scaled(ui->inputEdit->size().width(),
                                                 ui->inputEdit->size().height(),
                                                 Qt::KeepAspectRatio);
        ui->inputEdit->setPixmap(QPixmap::fromImage(scaledImg));
        ui->inputEdit->setAlignment(Qt::AlignCenter);

        callForResult(selectedQImage);
    }
}

void MainWindow::on_settingButton_pressed()
{
    SettingForm *settingForm = new SettingForm(nullptr, settings);
    settingForm->show();
}

void MainWindow::on_copyAllButton_pressed()
{
    clipboard->setText(ui->resultEdit->document()->toPlainText());
}

void MainWindow::on_resultEdit_show(QString text)
{
    ui->resultEdit->setText(text);
    ui->countLabel->setText("总字数：" + QString(text.size()));

    if (settings->getResultAutoCopy()) clipboard->setText(text); // 启用自动复制
}

void MainWindow::on_ocrTranslate(QString text)
{
    connect(translateApi, SIGNAL(renderResult(QString)), this, SLOT(on_resultEdit_show(QString)));
    translateApi->apiRequest(text);
}

void MainWindow::callForResult(QString text)
{
    if (lastText == text) return;
    lastText = text;

    if (ui->transRadioButton->isChecked())
    {
        connect(translateApi, SIGNAL(renderResult(QString)), this, SLOT(on_resultEdit_show(QString)));
        translateApi->apiRequest(text);
    }
}

void MainWindow::callForResult(QImage &image)
{
    if (lastImage == image) return;
    lastImage = image;

    if (ui->textRadioButtton->isChecked())
    {
        connect(ocrApi, SIGNAL(renderResult(QString)), this, SLOT(on_resultEdit_show(QString)));
        ocrApi->apiRequest(image2Base64(image));
    }
    else if (ui->transRadioButton->isChecked())
    {
        connect(ocrApi, SIGNAL(renderResult(QString)), this, SLOT(on_ocrTranslate(QString)));
        ocrApi->apiRequest(image2Base64(image));
    }
    else if (ui->formRadioButton->isChecked())
    {
        connect(formulaApi, SIGNAL(renderResult(QString)), this, SLOT(on_resultEdit_show(QString)));
        formulaApi->apiRequest(image2Base64(image));
    }
}

QString MainWindow::image2Base64(QImage &image) const
{
    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    image.save(&buf, "PNG");
    return QString(ba.toBase64());
}
