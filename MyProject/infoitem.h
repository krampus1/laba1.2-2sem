#ifndef INFOITEM_H
#define INFOITEM_H

#include <QDialog>
#include <QListWidget>
#include "myproject.h"
#include "addcomponent.h"

namespace Ui {
class InfoItem;
}

class InfoItem : public QDialog
{
    Q_OBJECT

public:
    explicit InfoItem(QWidget *parent = nullptr);
    ~InfoItem();

private:
    Ui::InfoItem *ui;
    AddComponent *w41;
//     InfoItem *w4;

private slots:
    void RecieveItem(item * it);
    void RecieveBigData(bigdata * bgd);
    void UpdateInfo();
    void on_pushButton_clicked();

//    void on_listWidget_itemActivated(QListWidgetItem *item);

    void on_pushButton_2_clicked();

signals:
    void SendBigData(bigdata * bgd);
    void SendItem(item * it);
};

#endif // INFOITEM_H
