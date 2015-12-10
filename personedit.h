#ifndef PERSONEDIT_H
#define PERSONEDIT_H

#include <QDialog>
#include "requestprocessor.h"
#include <QAbstractButton>
#include <QPushButton>

namespace Ui {
class PersonEdit;
}

class PersonEdit : public QDialog
{
    Q_OBJECT

public:
    explicit PersonEdit(QWidget *parent = 0);
    ~PersonEdit();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::PersonEdit *ui;

    RequestProcessor request;
};

#endif // PERSONEDIT_H
