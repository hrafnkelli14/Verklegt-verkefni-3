#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>
#include "requestprocessor.h"

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = 0);
    ~InfoWindow();

    void setPerson(Person pers);
    void setComputer(Computer comp);
    void setRequest(RequestProcessor *_request);

private slots:

private:
    void setWikiLink();
    QString spaceToLine(QString s);

    Ui::InfoWindow *ui;

    RequestProcessor *request;
    Person curr_pers;
    Computer curr_comp;
    char type;
};

#endif // INFOWINDOW_H
