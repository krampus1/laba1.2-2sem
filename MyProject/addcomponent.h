#ifndef ADDCOMPONENT_H
#define ADDCOMPONENT_H

#include <QDialog>
#include "myproject.h"

namespace Ui {
class AddComponent;
}

class AddComponent : public QDialog
{
    Q_OBJECT

public:
    explicit AddComponent(QWidget *parent = nullptr);
    ~AddComponent();

private:
    Ui::AddComponent *ui;

private slots:
    void RecieveBigData(bigdata * bgd);
    void RecieveItem(item * it);
    void on_pushButton_clicked();

signals:
    void close();
};

#endif // ADDCOMPONENT_H
