#ifndef ADDITEMTOCNT_H
#define ADDITEMTOCNT_H

#include <QDialog>
#include "myproject.h"

namespace Ui {
class AddItemToCnt;
}

class AddItemToCnt : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemToCnt(QWidget *parent = nullptr);
    ~AddItemToCnt();

private:
    Ui::AddItemToCnt *ui;

private slots:
    void RecieveBigData(bigdata * bgd);
    void RecieveCountry(country * cr);
    void on_pushButton_clicked();

signals:
    void close();
};

#endif // ADDITEMTOCNT_H
