#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(request.outputPersons());

    ui->radioCS->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioComp_clicked()
{
    ui->tableView->setModel(request.outputComputers());
}

void MainWindow::on_radioCS_clicked()
{
    ui->tableView->setModel(request.outputPersons());
}
