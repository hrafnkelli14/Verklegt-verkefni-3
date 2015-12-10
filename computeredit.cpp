#include "computeredit.h"
#include "ui_computeredit.h"

ComputerEdit::ComputerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerEdit)
{
    ui->setupUi(this);

    ui->wasBuilt->setChecked(true);
    ui->buildYear->setMinimum(0);
    ui->buildYear->setMaximum(2015);

    def_palette = ui->buildYear->palette();
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

void ComputerEdit::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        Computer comp;
        comp.setName(ui->nameEdit->text().toStdString());
        comp.setType(ui->typeEdit->text().toStdString());
        if(ui->wasBuilt->isChecked())
        {
            comp.setBuilt(true);
        }
        else
        {
            comp.setBuilt(false);
            on_notBuilt_clicked();
        }
    }
}

void ComputerEdit::on_wasBuilt_clicked()
{
    ui->buildYear->setPalette(def_palette);
    ui->buildYear->setReadOnly(false);
}

void ComputerEdit::on_notBuilt_clicked()
{
    QPalette palette = ui->buildYear->palette();
    QColor col = palette.color(QPalette::Button);
    palette.setColor(QPalette::Base, col);
    palette.setColor(QPalette::Text, Qt::black);
    ui->buildYear->setPalette(palette);
    ui->buildYear->setReadOnly(true);
}

void ComputerEdit::on_unknownYear_clicked(bool checked)
{
    if(checked == true)
    {
        QPalette palette = ui->buildYear->palette();
        QColor col = palette.color(QPalette::Button);
        palette.setColor(QPalette::Base, col);
        palette.setColor(QPalette::Text, Qt::black);
        ui->buildYear->setPalette(palette);
        ui->buildYear->setReadOnly(true);
    }
    else
    {
        ui->buildYear->setPalette(def_palette);
        ui->buildYear->setReadOnly(false);
    }
}
