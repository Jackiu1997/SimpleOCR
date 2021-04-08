#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_shotButton_pressed();

    void on_imageButton_pressed();

    void on_copyButton_pressed();

    void on_engine1Button_pressed();

    void on_engine2Button_pressed();

    void on_engine3Button_pressed();

    void on_engine4Button_pressed();

    void on_settingButton_pressed();

    void on_copyAllButton_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
