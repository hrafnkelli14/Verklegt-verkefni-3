#ifndef COMPUTEREDIT_H
#define COMPUTEREDIT_H

#include <QDialog>

namespace Ui {
class ComputerEdit;
}

class ComputerEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerEdit(QWidget *parent = 0);
    ~ComputerEdit();

private:
    Ui::ComputerEdit *ui;
};

#endif // COMPUTEREDIT_H
