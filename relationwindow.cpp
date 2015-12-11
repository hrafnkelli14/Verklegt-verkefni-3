#include "relationwindow.h"
#include "ui_relationwindow.h"

RelationWindow::RelationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationWindow)
{
    ui->setupUi(this);

    related_proxy = new QSortFilterProxyModel();
    n_related_proxy = new QSortFilterProxyModel();
    related_proxy->setDynamicSortFilter(true); //allows filtering dynamically
    related_proxy->setFilterKeyColumn(1); //filter by name
    related_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); //filtering is not case sensitive
    n_related_proxy->setDynamicSortFilter(true); //allows filtering dynamically
    n_related_proxy->setFilterKeyColumn(1); //filter by name
    n_related_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); //filtering is not case sensitive

    type = ' ';

    ui->relatedTable->verticalHeader()->hide();
    ui->relatedTable->setSortingEnabled(true);

    ui->nRelatedTable->verticalHeader()->hide();
    ui->nRelatedTable->setSortingEnabled(true);

    ui->buttonBox->button(QDialogButtonBox::Cancel)->hide();

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
    this->setWindowTitle(pers.getName());
    ui->nameOfEdit->setText(pers.getName());
    type = 'p';
    curr_pers = pers;
    refreshTables();
}

void RelationWindow::setComputer(Computer comp)
{
    this->setWindowTitle(comp.getName());
    ui->nameOfEdit->setText(comp.getName());
    type = 'c';
    curr_comp = comp;
    refreshTables();
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

void RelationWindow::prepareTables()
{
    related_proxy->sourceModel()->setHeaderData(1, Qt::Horizontal, tr("Related to"));
    n_related_proxy->sourceModel()->setHeaderData(1, Qt::Horizontal, tr("Unrelated to"));
    ui->relatedTable->setModel(related_proxy);
    ui->nRelatedTable->setModel(n_related_proxy);
    hideColumns();
    ui->relatedTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->nRelatedTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->relatedTable->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
    ui->nRelatedTable->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
    ui->relatedTable->setShowGrid(false);
    ui->nRelatedTable->setShowGrid(false);
}

void RelationWindow::on_addRelation_clicked()
{
    int row = ui->nRelatedTable->selectionModel()->currentIndex().row();
    QString id = ui->nRelatedTable->model()->data(ui->nRelatedTable->model()->index(row,0)).toString();
    if(type == 'p')
    {
        request->addComputerXPerson(id, curr_pers.getId());
    }
    else
    {
        request->addComputerXPerson(curr_comp.getId(), id);
    }
    refreshTables();
}

void RelationWindow::refreshTables()
{
    if(type == 'p')
    {
        related_proxy->setSourceModel(request->outputPersonXComputers(curr_pers.getId()));
        n_related_proxy->setSourceModel(request->outputNPersonXComputers(curr_pers.getId()));
    }
    else
    {
        related_proxy->setSourceModel(request->outputComputerXPersons(curr_comp.getId()));
        n_related_proxy->setSourceModel(request->outputNComputerXPersons(curr_comp.getId()));
    }
    prepareTables();
}

void RelationWindow::on_deleteRelation_clicked()
{
    int row = ui->relatedTable->selectionModel()->currentIndex().row();
    QString id = ui->relatedTable->model()->data(ui->relatedTable->model()->index(row,0)).toString();
    if(type == 'p')
    {
        request->deleteRelation(id, curr_pers.getId());
    }
    else
    {
        request->deleteRelation(curr_comp.getId(), id);
    }
    refreshTables();
}

void RelationWindow::on_filterRelated_textChanged(const QString &arg1)
{
    related_proxy->setFilterFixedString(arg1);
}

void RelationWindow::on_filterNRelated_textChanged(const QString &arg1)
{
    n_related_proxy->setFilterFixedString(arg1);
}
