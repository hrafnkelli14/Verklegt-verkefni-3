#include "personedit.h"
#include "ui_personedit.h"
#include <QDebug>

PersonEdit::PersonEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonEdit)
{
    ui->setupUi(this);

    ui->deadButton->setChecked(true);
    ui->maleButton->setChecked(true);

    def_palette = ui->dodEdit->palette();
    is_edit = false;
    edit_id = "";
}

PersonEdit::~PersonEdit()
{
    delete ui;
}

void PersonEdit::setRequest(RequestProcessor *_request)
{
    request = _request;
}

void PersonEdit::setTable(QTableView *_table)
{
    table = _table;
}

void PersonEdit::setPerson(Person pers)
{
    is_edit = true;
    edit_id = pers.getId();
    QString dod = pers.getDoD();
    QDate date_of_birth = pers.strToQDate(pers.getDoB().toStdString());
    QDate date_of_death;
    QString gender = pers.getGender();

    ui->nameEdit->setText(pers.getName());
    ui->dobEdit->setDate(date_of_birth);
    if(dod == "alive")
    {
        ui->aliveButton->setChecked(true);
    }
    else
    {
        date_of_death = pers.strToQDate(dod.toStdString());
        ui->dodEdit->setDate(date_of_death);
    }
    if(gender == "Male")
    {
        ui->maleButton->setChecked(true);
    }
    else
    {
        ui->femaleButton->setChecked(true);
    }
}

void PersonEdit::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        Person pers;
        QString dob = "";
        QString dod = "";
        pers.setName(ui->nameEdit->text().toStdString());
        dob = ui->dobEdit->date().toString("dd/MM/yyyy");
        if(ui->aliveButton->isChecked())
        {
            dod = "alive";
        }
        else
        {
            dod = ui->dodEdit->date().toString("dd/MM/yyyy");
        }
        pers.setDoB(dob.toStdString());
        pers.setDoD(dod.toStdString());
        if(ui->maleButton->isChecked())
        {
            pers.setGender("Male");
        }
        else if(ui->femaleButton->isChecked())
        {
            pers.setGender("Female");
        }

        switch(is_edit)
        {
        case false:
            request->addPerson(pers);
            break;
        case true:
            request->editPerson(pers, edit_id);
            break;
        }

        QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
        proxy_model->setSourceModel(request->outputPersons());
        table->setModel(proxy_model);
        table->hideColumn(0);
    }
}

void PersonEdit::on_aliveButton_clicked()
{
    QPalette palette = ui->dodEdit->palette();
    QColor col = palette.color(QPalette::Button);
    palette.setColor(QPalette::Base, col);
    palette.setColor(QPalette::Text, Qt::black);
    ui->dodEdit->setPalette(palette);
    ui->dodEdit->setReadOnly(true);
}

void PersonEdit::on_deadButton_clicked()
{
    ui->dodEdit->setPalette(def_palette);
    ui->dodEdit->setReadOnly(false);
}
