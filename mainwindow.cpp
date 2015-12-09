#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //TABLE VIEW
    QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(request.outputPersons());
    ui->tableView->setModel(proxy_model); //Initial table view
    ui->tableView->setSortingEnabled(true); //enable sorting by clicking on header
    ui->tableView->verticalHeader()->setVisible(false); //hide vertical header
    ui->tableView->hideColumn(0); //hide id column
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //select by rows, not columns
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) //fill the width of the table window
    {
        ui->tableView->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

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
    ui->tableView->hideColumn(0);
}

void MainWindow::on_radioCS_clicked()
{
    QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(request.outputPersons());
    ui->tableView->setModel(proxy_model);
    ui->tableView->hideColumn(0);
}
