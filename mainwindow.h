#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "appsettings.h"

#include <QMainWindow>
#include <QClipboard>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <networkapi.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initSettings();

private slots:
    void on_shotButton_pressed();
    void on_imageButton_pressed();
    void on_copyButton_pressed();
    void on_settingButton_pressed();
    void on_copyAllButton_pressed();
    void on_resultEdit_show(QString text);
    void on_ocrTranslate(QString text);

private:
    Ui::MainWindow *ui;

    QClipboard *clipboard;
    QString lastText;
    QImage lastImage;

    // API 接口
    NetworkAPI *ocrApi;
    NetworkAPI *translateApi;
    NetworkAPI *formulaApi;

    // 设置选项
    AppSettings *settings;

    void callForResult(QString text);
    void callForResult(QImage &image);
    QString image2Base64(QImage &image) const;
};
#endif // MAINWINDOW_H
