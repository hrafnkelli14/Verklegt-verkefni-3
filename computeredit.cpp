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

    is_edit = false;
    edit_id = "";
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
        }
        if(comp.getBuilt() == false || ui->unknownYear->isChecked())
        {
            comp.setYear("NULL");
        }
        else
        {
            comp.setYear(ui->buildYear->text().toStdString());
        }

        switch(is_edit)
        {
        case false:
            request->addComputer(comp);
            break;
        case true:
            request->editComputer(comp, edit_id);
            break;
        }

        QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
        proxy_model->setSourceModel(request->outputPersons());
        table->setModel(proxy_model);
        table->hideColumn(0);
        table->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
    }
}

void ComputerEdit::setComputer(Computer comp)
{
    this->setWindowTitle("Edit Computer");
    is_edit = true;
    edit_id = comp.getId();
    bool built = comp.getBuilt();
    QString year_of_build;

    ui->nameEdit->setText(comp.getName());
    ui->typeEdit->setText(comp.getType());
    if(built)
    {
        ui->wasBuilt->setChecked(true);
        if(comp.getYear() == "NULL")
        {
            ui->unknownYear->setChecked(true);
        }
    }
    else
    {
        ui->notBuilt->setChecked(true);
        ui->unknownYear->setChecked(true);
        on_unknownYear_clicked(true);
    }
}

void ComputerEdit::on_wasBuilt_clicked()
{
    if(ui->unknownYear->isChecked() == false)
    {
        ui->buildYear->setPalette(def_palette);
        ui->buildYear->setReadOnly(false);
    }
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
    else if(ui->wasBuilt->isChecked() == true)
    {
        ui->buildYear->setPalette(def_palette);
        ui->buildYear->setReadOnly(false);
    }
}
