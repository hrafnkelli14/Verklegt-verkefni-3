#ifndef RELATIONWINDOW_H
#define RELATIONWINDOW_H

#include <QDialog>
#include "requestprocessor.h"
#include <QSortFilterProxyModel>

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

private slots:
    void on_addRelation_clicked();

    void on_deleteRelation_clicked();

private:
    void hideColumns();
    void prepareTables();
    void refreshTables();

    char type;
    Computer curr_comp;
    Person curr_pers;
    QSortFilterProxyModel *related_proxy;
    QSortFilterProxyModel *n_related_proxy;
    RequestProcessor *request;
    Ui::RelationWindow *ui;
};

#endif // RELATIONWINDOW_H
