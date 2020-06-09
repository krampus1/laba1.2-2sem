#ifndef ITEMOFCOUNTRU_H
#define ITEMOFCOUNTRU_H

#include <QDialog>
#include "myproject.h"
#include "infoitem.h"

namespace Ui {
class ItemOfCountru;
}

class ItemOfCountru : public QDialog
{
    Q_OBJECT

public:
    explicit ItemOfCountru(QWidget *parent = nullptr);
    ~ItemOfCountru();

private:
    Ui::ItemOfCountru *ui;
    InfoItem *w4;

private slots:
    void RecieveItem(records * it);
    void RecieveBigData(bigdata * bgd);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void UpdateInfo();

signals:
    void SendBigData(bigdata * bgd);
    void SendItem(item * it);
};

#endif // ITEMOFCOUNTRU_H
