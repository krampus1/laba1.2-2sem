#ifndef INFOCOUNTRY_H
#define INFOCOUNTRY_H

#include <QDialog>
#include "myproject.h"
#include <QMetaType>
#include <QListWidget>
#include "itemofcountru.h"
#include "additemtocnt.h"

namespace Ui {
class InfoCountry;
}

class InfoCountry : public QDialog
{
    Q_OBJECT

public:
    explicit InfoCountry(QWidget *parent = nullptr);
    ~InfoCountry();

private:
    Ui::InfoCountry *ui;
    AddItemToCnt *w31;
    ItemOfCountru *w32;

private slots:
    void RecieveCountryName(QString str);
    void RecieveBigData(bigdata * bgd);
    void on_pushButton_clicked();
    void UpdateInfo();
    void on_listWidget_itemActivated(QListWidgetItem *item);

signals:
    void SendBigData(bigdata * bgd);
    void SendCountry(country * cr);
    void SendItem(records * it);
};

#endif // INFOCOUNTRY_H
