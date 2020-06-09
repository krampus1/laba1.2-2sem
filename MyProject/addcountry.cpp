#include "addcountry.h"
#include "ui_addcountry.h"

AddCountry::AddCountry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCountry)
{
    ui->setupUi(this);
}

AddCountry::~AddCountry()
{
    delete ui;
}

void AddCountry::on_pushButton_clicked()
{
    emit SendCountryName(ui->lineEdit->text());
    ui->lineEdit->clear();
    close();
}
