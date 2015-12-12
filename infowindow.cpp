#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);

    type = ' ';

    ui->wikiLabel->setOpenExternalLinks(true);
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::setPerson(Person pers)
{
    type = 'p';
    curr_pers = pers;
    setWikiLink();
}

void InfoWindow::setComputer(Computer comp)
{
    type = 'c';
    curr_comp = comp;
}

void InfoWindow::setRequest(RequestProcessor *_request)
{
    request = _request;
}


void InfoWindow::setWikiLink()
{
    QString article_name = "";
    if(type = 'p')
    {
        article_name = spaceToLine(curr_pers.getName());
        ui->wikiLabel->setText("<a href=\"https://en.wikipedia.org/wiki/" + article_name + "\">Visit Wiki</a>");
    }
}

QString InfoWindow::spaceToLine(QString s)
{
    QString newstring;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == ' ')
        {
            newstring += '_';
        }
        else
        {
            newstring += s[i];
        }
    }

    return newstring;
}
