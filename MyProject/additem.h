#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>

namespace Ui {
class additem;
}

class additem : public QDialog
{
    Q_OBJECT

public:
    explicit additem(QWidget *parent = nullptr);
    ~additem();

private slots:
    void on_pushButton_clicked();

private:
    Ui::additem *ui;

signals:
    void SendItemName(QString str);
};

#endif // ADDITEM_H
