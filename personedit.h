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

    void setRequest(RequestProcessor* _request); //uses a pointer so we dont have to make two connections to db
    void setTable(QTableView* _table); //so it can update the tableview from here
    void setPerson(Person pers); //if this is called, editing mode will be assumed
    void setProxyModel(QSortFilterProxyModel* _proxy_model); //so it can update the model from here

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_aliveButton_clicked();

    void on_deadButton_clicked();

    void on_nameEdit_textEdited(const QString &arg1);

    void on_dobEdit_editingFinished();

private:
    //Input checking helpers
    void prepareWarningIcon();
    bool checkInput(const QString &input);
    bool checkChar(const QChar &ch);
    QString def_stylesheet;

    Ui::PersonEdit *ui;

    RequestProcessor* request;
    QTableView* table;
    QSortFilterProxyModel* proxy_model;
    QPalette def_palette;
    bool is_edit;
    QString edit_id;
};

#endif // PERSONEDIT_H
