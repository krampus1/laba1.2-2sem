#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "addcountry.h"
#include "additem.h"
#include "infocountry.h"
#include "infoitem.h"
#include "myproject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void CountriesUpdate();
     void ItemsUpdate();
     void test_setup();

private slots:
    void on_pushButton_clicked();
    void RecieveCountryName(QString str);
    void RecieveItemName(QString str);
    void on_pushButton_2_clicked();
    void on_listWidget_itemActivated(QListWidgetItem *item);
    void on_listWidget_2_itemActivated(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    AddCountry *w1;
    additem *w2;
    InfoCountry *w3;
    InfoItem *w4;

signals:
    void SendCountryName(QString str);
    void SendBigData(bigdata * bgd);
    void SendItem(item * it);
};

#endif // MAINWINDOW_H
