#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QNetworkProxyFactory>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QWebPage>
#include <QtNetwork>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AboutWindow *ui;
    int easter_clicked;
};

#endif // ABOUTWINDOW_H
