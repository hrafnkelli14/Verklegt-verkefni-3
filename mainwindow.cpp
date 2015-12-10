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
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
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

RequestProcessor* MainWindow::getRequest()
{
    return &request;
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

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->tableView->indexAt(pos);

    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction("Edit", this));
    menu->addAction(new QAction("Delete", this));
    menu->addAction(new QAction("Info", this));
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::on_addButton_clicked()
{
    ui->tableView->model()->disconnect();
    PersonEdit add_window;
    add_window.setModal(true);
    add_window.setRequest(&request);
    add_window.exec();
}
