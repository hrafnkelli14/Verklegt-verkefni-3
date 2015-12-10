#ifndef COMPUTEREDIT_H
#define COMPUTEREDIT_H

#include <QDialog>

namespace Ui {
class computeredit;
}

class computeredit : public QDialog
{
    Q_OBJECT

public:
    explicit computeredit(QWidget *parent = 0);
    ~computeredit();

private:
    Ui::computeredit *ui;
};

#endif // COMPUTEREDIT_H
