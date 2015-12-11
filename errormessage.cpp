#include "errormessage.h"
#include "ui_errormessage.h"

ErrorMessage::ErrorMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorMessage)
{
    ui->setupUi(this);
}

ErrorMessage::~ErrorMessage()
{
    delete ui;
}
