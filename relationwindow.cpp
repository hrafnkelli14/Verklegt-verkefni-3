#include "relationwindow.h"
#include "ui_relationwindow.h"

RelationWindow::RelationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationWindow)
{
    ui->setupUi(this);

    related_proxy = new QSortFilterProxyModel();
    n_related_proxy = new QSortFilterProxyModel();

    type = ' ';

    ui->relatedTable->verticalHeader()->hide();


    ui->nRelatedTable->verticalHeader()->hide();

}

RelationWindow::~RelationWindow()
{
    delete ui;
}

void RelationWindow::setRequest(RequestProcessor *_request)
{
    request = _request;
}

void RelationWindow::setPerson(Person pers)
{
    type = 'p';
    related_proxy->setSourceModel(request->outputPersonXComputers(pers.getId()));
    n_related_proxy->setSourceModel(request->outputNPersonXComputers(pers.getId()));
    ui->relatedTable->setModel(related_proxy);
    ui->nRelatedTable->setModel(n_related_proxy);
    hideColumns();
    ui->relatedTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->nRelatedTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void RelationWindow::setComputer(Computer comp)
{
    type = 'c';
    related_proxy->setSourceModel(request->outputComputerXPersons(comp.getId()));
    n_related_proxy->setSourceModel(request->outputNComputerXPersons(comp.getId()));
    ui->relatedTable->setModel(related_proxy);
    ui->nRelatedTable->setModel(n_related_proxy);
    hideColumns();
    ui->relatedTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->nRelatedTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void RelationWindow::hideColumns()
{
    ui->relatedTable->hideColumn(0);
    ui->relatedTable->hideColumn(2);
    ui->relatedTable->hideColumn(3);
    ui->relatedTable->hideColumn(4);
    ui->nRelatedTable->hideColumn(0);
    ui->nRelatedTable->hideColumn(2);
    ui->nRelatedTable->hideColumn(3);
    ui->nRelatedTable->hideColumn(4);
}
