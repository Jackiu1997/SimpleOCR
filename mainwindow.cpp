#include "mainwindow.h"
#include "settingform.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shotButton_pressed()
{

}

void MainWindow::on_imageButton_pressed()
{

}

void MainWindow::on_copyButton_pressed()
{

}

void MainWindow::on_engine1Button_pressed()
{

}

void MainWindow::on_engine2Button_pressed()
{

}

void MainWindow::on_engine3Button_pressed()
{

}

void MainWindow::on_engine4Button_pressed()
{

}

void MainWindow::on_settingButton_pressed()
{
    SettingForm *settingForm = new SettingForm();
    settingForm->show();
}

void MainWindow::on_copyAllButton_pressed()
{

}
