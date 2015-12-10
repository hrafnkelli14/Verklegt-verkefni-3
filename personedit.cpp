#include "personedit.h"
#include "ui_personedit.h"

PersonEdit::PersonEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonEdit)
{
    ui->setupUi(this);
}

PersonEdit::~PersonEdit()
{
    delete ui;
}

void PersonEdit::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        Person pers;
        string dob = "";
        string dod = "";
        pers.setName(ui->nameEdit->text().toStdString());
        //dob = ui->dobEdit->text().toStdString();
        request.addPerson(pers);
    }
}
