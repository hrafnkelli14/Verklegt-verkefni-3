#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(request.outputPersons());
    ui->tableView->setModel(proxy_model); //Initial table view
    ui->tableView->setSortingEnabled(true);

    ui->radioCS->setChecked(true); //Initial radio button check
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioComp_clicked()
{
    QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(request.outputComputers());
    ui->tableView->setModel(proxy_model);
}

void MainWindow::on_radioCS_clicked()
{
    QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(request.outputPersons());
    ui->tableView->setModel(proxy_model);
}
