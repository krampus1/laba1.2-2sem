#include "itemofcountru.h"
#include "ui_itemofcountru.h"

void UpdateInfo();

ItemOfCountru::ItemOfCountru(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemOfCountru)
{
    ui->setupUi(this);

    w4 = new InfoItem();

    connect(this, SIGNAL(SendItem(item*)), w4, SLOT(RecieveItem(item*)));
    connect(this, SIGNAL(SendBigData(bigdata*)), w4, SLOT(RecieveBigData(bigdata*)));
}

ItemOfCountru::~ItemOfCountru()
{
    delete ui;
}

bigdata * bdw32; //база данных
records * cw32; //выбраный товар

void ItemOfCountru::RecieveBigData(bigdata * bd32){
    bdw32 = bd32;
}

void ItemOfCountru::RecieveItem(records * it32){
    cw32 = it32;

    ui->label->clear();
    ui->label->setText("You choose item: " + cw32->element->name);
    UpdateInfo();
}

void ItemOfCountru::UpdateInfo(){
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(cw32->rec.size()+1);
    QTableWidgetItem * ye = new QTableWidgetItem(tr("%1").arg("Year:"));
    QTableWidgetItem * pr = new QTableWidgetItem(tr("%1").arg("Produce:"));
    QTableWidgetItem * im = new QTableWidgetItem(tr("%1").arg("Import:"));
    QTableWidgetItem * ex = new QTableWidgetItem(tr("%1").arg("Export:"));
    ui->tableWidget->setItem(0, 0, ye);
    ui->tableWidget->setItem(0, 1, pr);
    ui->tableWidget->setItem(0, 2, im);
    ui->tableWidget->setItem(0, 3, ex);

    int k = 1;
    for (auto i = cw32->rec.begin(); i != cw32->rec.end(); i++){
        QTableWidgetItem * ye = new QTableWidgetItem(tr("%1").arg(i->year));
        QTableWidgetItem * pr = new QTableWidgetItem(tr("%1").arg(i->produce));
        QTableWidgetItem * im = new QTableWidgetItem(tr("%1").arg(i->importing));
        QTableWidgetItem * ex = new QTableWidgetItem(tr("%1").arg(i->exporting));
        ui->tableWidget->setItem(k, 0, ye);
        ui->tableWidget->setItem(k, 1, pr);
        ui->tableWidget->setItem(k, 2, im);
        ui->tableWidget->setItem(k, 3, ex);
        k++;
    }
}

void ItemOfCountru::on_pushButton_clicked()
{
    w4->show();
    emit SendBigData(bdw32);
    emit SendItem(cw32->element);
    close();
}

void ItemOfCountru::on_pushButton_2_clicked()
{
    cw32->add_record(ui->lineEdit_2->text().toInt(), ui->lineEdit_4->text().toInt(), ui->lineEdit_3->text().toInt(), ui->lineEdit->text().toInt());
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    UpdateInfo();
}
