#ifndef RELATIONWINDOW_H
#define RELATIONWINDOW_H

#include <QDialog>
#include "requestprocessor.h"

namespace Ui {
class RelationWindow;
}

class RelationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RelationWindow(QWidget *parent = 0);
    ~RelationWindow();

    void setRequest(RequestProcessor *_request);
    void setPerson(Person pers);
    void setComputer(Computer comp);

private:
    char type;
    RequestProcessor *request;
    Ui::RelationWindow *ui;
};

#endif // RELATIONWINDOW_H
