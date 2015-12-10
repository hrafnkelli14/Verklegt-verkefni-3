#ifndef PERSONEDIT_H
#define PERSONEDIT_H

#include <QDialog>
#include "requestprocessor.h"
#include <QAbstractButton>
#include <QPushButton>
#include <QTableView>

namespace Ui {
class PersonEdit;
}

class PersonEdit : public QDialog
{
    Q_OBJECT

public:
    explicit PersonEdit(QWidget *parent = 0);
    ~PersonEdit();

    void setRequest(RequestProcessor* _request);
    void setTable(QTableView* _table);
    void setPerson(Person pers);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_aliveButton_clicked();

    void on_deadButton_clicked();

private:
    Ui::PersonEdit *ui;

    RequestProcessor* request;
    QTableView* table;
    QPalette def_palette;
    bool is_edit;
    QString edit_id;
};

#endif // PERSONEDIT_H
