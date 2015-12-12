#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    easter_clicked = 0;
    ui->webView->hide();
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_pushButton_clicked()
{
    this->close();
}

void AboutWindow::on_pushButton_2_clicked()
{
    easter_clicked++;
    if(easter_clicked == 5)
    {
        ui->webView->show();
        QNetworkProxyFactory::setUseSystemConfiguration(true);
        QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
        QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
        ui->webView->load(QUrl("http://i.imgur.com/j85s4Fw.jpg"));
        ui->textBrowser->hide();
    }
}
