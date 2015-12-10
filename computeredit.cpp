#include "computeredit.h"
#include "ui_computeredit.h"

computeredit::computeredit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::computeredit)
{
    ui->setupUi(this);
}

computeredit::~computeredit()
{
    delete ui;
}
