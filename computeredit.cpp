#include "computeredit.h"
#include "ui_computeredit.h"

ComputerEdit::ComputerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerEdit)
{
    ui->setupUi(this);

    ui->wasBuilt->setChecked(true);
    ui->buildYear->setMinimum(1000);
    ui->buildYear->setMaximum(2015);
}

ComputerEdit::~ComputerEdit()
{
    delete ui;
}

void ComputerEdit::setRequest(RequestProcessor *_request)
{
    request = _request;
}

void ComputerEdit::setTable(QTableView *_table)
{
    table = _table;
}
