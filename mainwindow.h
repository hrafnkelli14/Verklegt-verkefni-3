#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "requestprocessor.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_radioComp_clicked();

    void on_radioCS_clicked();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    RequestProcessor request;
};

#endif // MAINWINDOW_H
