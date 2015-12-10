#ifndef COMPUTEREDIT_H
#define COMPUTEREDIT_H

#include <QDialog>
#include "requestprocessor.h"
#include <QAbstractButton>
#include <QPushButton>
#include <QTableView>

namespace Ui {
class ComputerEdit;
}

class ComputerEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerEdit(QWidget *parent = 0);
    ~ComputerEdit();

    void setRequest(RequestProcessor* _request);
    void setTable(QTableView* _table);
    void setComputer(Computer comp);
    void setProxyModel(QSortFilterProxyModel* _proxy_model);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_wasBuilt_clicked();
    void on_notBuilt_clicked();
    void on_unknownYear_clicked(bool checked);

private:
    Ui::ComputerEdit *ui;

    RequestProcessor* request;
    QTableView* table;
    QSortFilterProxyModel* proxy_model;
    QPalette def_palette;
    bool is_edit;
    QString edit_id;
};

#endif // COMPUTEREDIT_H
