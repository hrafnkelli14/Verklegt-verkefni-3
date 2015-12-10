#include "computeredit.h"
#include "ui_computeredit.h"

ComputerEdit::ComputerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerEdit)
{
    ui->setupUi(this);
}

ComputerEdit::~ComputerEdit()
{
    delete ui;
}
