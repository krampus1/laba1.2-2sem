#include "additemtocnt.h"
#include "ui_additemtocnt.h"
#include "myproject.h"

AddItemToCnt::AddItemToCnt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemToCnt)
{
    ui->setupUi(this);
}

AddItemToCnt::~AddItemToCnt()
{
    delete ui;
}

bigdata * bdw31; //база данных
country * cw31; //выбранная страна

void AddItemToCnt::RecieveBigData(bigdata * bgd){
    bdw31 = bgd;

    ui->listWidget->clear();
    for (auto i = bdw31->items.begin(); i != bdw31->items.end(); i++){
        ui->listWidget->addItem(i->name);
    }
}

void AddItemToCnt::RecieveCountry(country * cr){
    cw31 = cr;
}

void AddItemToCnt::on_pushButton_clicked()
{
    if (bdw31->search_item(ui->listWidget->currentItem()->text())->is_parent(cw31)){
        cw31->add_item_to_country(bdw31->search_item(ui->listWidget->currentItem()->text()));
        bdw31->search_item(ui->listWidget->currentItem()->text())->parents.push_back(cw31);
    }
    close();
}
