#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "requestprocessor.h"
#include <QMainWindow>
#include <QMessageBox>
#include "personedit.h"
#include "computeredit.h"
#include "aboutwindow.h"
#include "relationwindow.h"
#include "infowindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showAllRows();

private slots:

    void on_radioComp_clicked();

    void on_radioCS_clicked();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_addButton_clicked();

    void editAction();

    void deleteAction();

    void on_filterNames_textChanged(const QString &arg1);

    void aboutAction();

    void relateAction();

    void exitAction();

    void infoAction();
private:

    Ui::MainWindow *ui;
    RequestProcessor request;
    QSortFilterProxyModel *proxy_model;
    QModelIndex curr_index;
};

#endif // MAINWINDOW_H
