#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);

    proxy_relator = new QSortFilterProxyModel();
    proxy_relator->setDynamicSortFilter(true);
    proxy_related = new QSortFilterProxyModel();

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
    proxy_relator->setSourceModel(request->outputPerson(curr_pers.getId()));
    proxy_related->setSourceModel(request->outputPersonXComputers(curr_pers.getId()));
    ui->relatedTable->setModel(proxy_related);
    ui->relatorTable->setModel(proxy_relator);
    ui->relatedTable->hideColumn(0);
    ui->relatorTable->hideColumn(0);
    ui->relatedTable->verticalHeader()->setVisible(false);
    ui->relatorTable->verticalHeader()->setVisible(false);
    ui->relatedTable->setSortingEnabled(true);
    for (int c = 0; c < ui->relatedTable->horizontalHeader()->count(); ++c) //fill the width of the table window
    {
        ui->relatedTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    for (int c = 0; c < ui->relatorTable->horizontalHeader()->count(); ++c) //fill the width of the table window
    {
        ui->relatorTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    ui->typeLabel->setText("Computer Scientist:");
    ui->typeLabel->setAlignment(Qt::AlignCenter);
    this->setWindowTitle(curr_pers.getName());
    setWikiLink();
    ui->relatorTable->verticalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

void InfoWindow::setComputer(Computer comp)
{
    type = 'c';
    curr_comp = comp;
    proxy_relator->setSourceModel(request->outputComputer(curr_comp.getId()));
    proxy_related->setSourceModel(request->outputComputerXPersons(curr_comp.getId()));
    ui->relatedTable->setModel(proxy_related);
    ui->relatorTable->setModel(proxy_relator);
    ui->relatedTable->hideColumn(0);
    ui->relatorTable->hideColumn(0);
    ui->relatedTable->verticalHeader()->setVisible(false);
    ui->relatorTable->verticalHeader()->setVisible(false);
    ui->relatedTable->setSortingEnabled(true);
    for (int c = 0; c < ui->relatedTable->horizontalHeader()->count(); ++c) //fill the width of the table window
    {
        ui->relatedTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    for (int c = 0; c < ui->relatorTable->horizontalHeader()->count(); ++c) //fill the width of the table window
    {
        ui->relatorTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    ui->typeLabel->setText("Computer:");
    ui->typeLabel->setAlignment(Qt::AlignCenter);
    this->setWindowTitle(curr_comp.getName());
    setWikiLink();
    ui->relatorTable->verticalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

void InfoWindow::setRequest(RequestProcessor *_request)
{
    request = _request;
}


void InfoWindow::setWikiLink()
{
    QString article_name = "";
    if(type == 'p')
    {
        article_name = spaceToLine(curr_pers.getName());
        article_url = "https://en.wikipedia.org/wiki/" + article_name;
        ui->wikiLabel->setText("<a href=\"" + article_url + "\">Visit Wiki</a>");
    }
    else
    {
        article_name = spaceToLine(curr_comp.getName());
        article_url = "https://en.wikipedia.org/wiki/" + article_name;
        ui->wikiLabel->setText("<a href=\"" + article_url + "\">Visit Wiki</a>");
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



void InfoWindow::on_pushButton_clicked()
{
    this->close();
}
