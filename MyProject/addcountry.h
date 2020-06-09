#ifndef ADDCOUNTRY_H
#define ADDCOUNTRY_H

#include <QDialog>

namespace Ui {
class AddCountry;
}

class AddCountry : public QDialog
{
    Q_OBJECT

public:
    explicit AddCountry(QWidget *parent = nullptr);
    ~AddCountry();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddCountry *ui;

signals:
    void SendCountryName(QString str);
};

#endif // ADDCOUNTRY_H
