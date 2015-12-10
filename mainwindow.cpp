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
    ui->tableView->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
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

void MainWindow::on_radioComp_clicked()
{
    QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(request.outputComputers());
    ui->tableView->setModel(proxy_model);
    showAllRows();
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
}

void MainWindow::on_radioCS_clicked()
{
    QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(request.outputPersons());
    ui->tableView->setModel(proxy_model);
    showAllRows();
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->tableView->indexAt(pos);
    curr_index = index;

    QMenu *menu = new QMenu(this);
    QAction *edit_action = new QAction("Edit", this);
    connect(edit_action, SIGNAL(triggered()), this, SLOT(editAction()));
    QAction *delete_action = new QAction("Delete", this);
    connect(delete_action, SIGNAL(triggered()), this, SLOT(deleteAction()));
    QAction *info_action = new QAction("Info", this);

    menu->addAction(edit_action);
    menu->addAction(delete_action);
    menu->addAction(info_action);
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));

}

void MainWindow::on_addButton_clicked()
{
    if(ui->radioCS->isChecked())
    {
        PersonEdit add_window;
        add_window.setModal(true);
        add_window.setRequest(&request);
        add_window.setTable(ui->tableView);
        add_window.exec();
    }
    else if(ui->radioComp->isChecked())
    {
        ComputerEdit add_window;
        add_window.setModal(true);
        add_window.setRequest(&request);
        add_window.setTable(ui->tableView);
        add_window.exec();
    }
}

void MainWindow::editAction()
{
    int row = curr_index.row();
    QString id = ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toString();
    Person pers = request.getPerson(id);

    PersonEdit edit_window;
    edit_window.setModal(true);
    edit_window.setRequest(&request);
    edit_window.setTable(ui->tableView);
    edit_window.setPerson(pers);
    edit_window.exec();
}

void MainWindow::deleteAction()
{
    int row = curr_index.row();
    QString id = ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toString();
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(row,1)).toString();

    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(this, "Delete", "Are you sure you want to delete " + name + "?",
                                    QMessageBox::Yes | QMessageBox::No);
    if(confirm == QMessageBox::Yes)
    {
        if(ui->radioCS->isChecked())
        {
            request.deletePerson(id);
        }
        else if(ui->radioComp->isChecked())
        {
            request.deleteComputer(id);
        }
        ui->tableView->hideRow(row);
    }
}

void MainWindow::showAllRows()
{
    for(int i = 0; i<ui->tableView->model()->rowCount(); i++)
    {
        ui->tableView->setRowHidden(0, false);
    }
}
