#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "requestprocessor.h"
#include <QMainWindow>
#include <QMessageBox>
#include "personedit.h"
#include "computeredit.h"

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

    void on_addButton_clicked();

    void editAction();

    void deleteAction();

private:
    void showAllRows();
    Ui::MainWindow *ui;
    RequestProcessor request;
    QModelIndex curr_index;
};

#endif // MAINWINDOW_H
