#include "computeredit.h"
#include "ui_computeredit.h"

ComputerEdit::ComputerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerEdit)
{
    ui->setupUi(this);

    def_stylesheet = ui->nameEdit->styleSheet();
    def_palette = ui->buildYear->palette();

    ui->wasBuilt->setChecked(true);
    ui->buildYear->setMinimum(1820); //the mechanical computer was still just an idea in Babbages head then, should suffice
    ui->buildYear->setMaximum(QDate::currentDate().year());

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->nameEdit->setStyleSheet("border: 1px solid red");
    ui->typeEdit->setStyleSheet("border: 1px solid red");

    prepareWarningIcons();
    valid_name = false;
    valid_type = false;

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

void ComputerEdit::setProxyModel(QSortFilterProxyModel *_proxy_model)
{
    proxy_model = _proxy_model;
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

        proxy_model->setSourceModel(request->outputComputers());
        table->setModel(proxy_model);
        table->hideColumn(0);
        table->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
    }
}

void ComputerEdit::setComputer(Computer comp)
{
    this->setWindowTitle("Edit Computer");
    valid_name = true;
    valid_type = true;
    is_edit = true;
    edit_id = comp.getId();
    bool built = comp.getBuilt();
    QString year_of_build;

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    ui->nameEdit->setStyleSheet(def_stylesheet);
    ui->typeEdit->setStyleSheet(def_stylesheet);
    ui->nameWarning->hide();
    ui->typeWarning->hide();

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
        ui->unknownYear->setChecked(false);
        ui->unknownYear->setDisabled(true);
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
    ui->unknownYear->setDisabled(false);
}

void ComputerEdit::on_notBuilt_clicked()
{
    QPalette palette = ui->buildYear->palette();
    QColor col = palette.color(QPalette::Button);
    palette.setColor(QPalette::Base, col);
    palette.setColor(QPalette::Text, Qt::black);
    ui->buildYear->setPalette(palette);
    ui->buildYear->setReadOnly(true);
    ui->unknownYear->setDisabled(true);
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

void ComputerEdit::prepareWarningIcons()
{
    QStyle *style = QApplication::style();
    QIcon warning_icon = style->standardIcon(QStyle::SP_MessageBoxWarning, 0, this);
    ui->nameWarning->setPixmap(warning_icon.pixmap(20));
    ui->typeWarning->setPixmap(warning_icon.pixmap(20));
}

bool ComputerEdit::checkInput(const QString &input)
{
    if(input.isEmpty())
    {
        return false;
    }

    for(int i = 0; i < input.size(); i++)
    {
        if(!checkChar(input[i]))
        {
            return false;
        }
    }

    return true;
}

bool ComputerEdit::checkChar(const QChar &ch)
{
    if(ch.isLetterOrNumber())
    {
        return true;
    }
    else if(ch.isSpace())
    {
        return true;
    }
    else if(ch == '.')
    {
        return true;
    }
    else if(ch == '-')
    {
        return true;
    }
    else if(ch == '\'')
    {
        return true;
    }

    return false;
}

void ComputerEdit::isOk()
{
    if(valid_name && valid_type)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void ComputerEdit::on_nameEdit_textEdited(const QString &arg1)
{
    if(!checkInput(arg1))
    {
        valid_name = false;
        ui->nameWarning->show();
        ui->nameEdit->setStyleSheet("border: 1px solid red");
    }
    else
    {
        valid_name = true;
        ui->nameWarning->hide();
        ui->nameEdit->setStyleSheet(def_stylesheet);
    }

    isOk();
}

void ComputerEdit::on_typeEdit_textEdited(const QString &arg1)
{
    if(!checkInput(arg1))
    {
        valid_type = false;
        ui->typeWarning->show();
        ui->typeEdit->setStyleSheet("border: 1px solid red");
    }
    else
    {
        valid_type = true;
        ui->typeWarning->hide();
        ui->typeEdit->setStyleSheet(def_stylesheet);
    }

    isOk();
}
