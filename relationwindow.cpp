#include "relationwindow.h"
#include "ui_relationwindow.h"

RelationWindow::RelationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationWindow)
{
    ui->setupUi(this);
    type = ' ';
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
    ui->relatedTable->setModel(request->outputPersonXComputers(pers.getId()));
    ui->nRelatedTable->setModel(request->outputNPersonXComputers(pers.getId()));
}

void RelationWindow::setComputer(Computer comp)
{
    type = 'c';
    ui->relatedTable->setModel(request->outputComputerXPersons(comp.getId()));
    ui->nRelatedTable->setModel(request->outputNComputerXPersons(comp.getId()));
}
