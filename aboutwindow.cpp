#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    easter_clicked = 0;
    ui->christmasEgg->hide();
    ui->christmasEgg->setReadOnly(true);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_pushButton_clicked()
{
    this->close();
}

void AboutWindow::on_pushButton_2_clicked()
{
    easter_clicked++;
    if(easter_clicked == 5)
    {
        int w = this->width();
        this->resize(w, 900);
        ui->christmasEgg->show();
        int x = ui->pushButton->x();
        ui->pushButton->move(x, 850);
        this->setWindowTitle("Merry Christmas!");
    }
}
