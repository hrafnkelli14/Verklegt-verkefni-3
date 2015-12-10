#ifndef RELATIONWINDOW_H
#define RELATIONWINDOW_H

#include <QDialog>

namespace Ui {
class RelationWindow;
}

class RelationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RelationWindow(QWidget *parent = 0);
    ~RelationWindow();

private:
    Ui::RelationWindow *ui;
};

#endif // RELATIONWINDOW_H
