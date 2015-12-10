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


private:
    Ui::ComputerEdit *ui;

    RequestProcessor* request;
    QTableView* table;
    QPalette def_palette;
};

#endif // COMPUTEREDIT_H
