#include "addcomponent.h"
#include "ui_addcomponent.h"

AddComponent::AddComponent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComponent)
{
    ui->setupUi(this);
}

AddComponent::~AddComponent()
{
    delete ui;
}

bigdata * bdw41; //база данных
item * cw41; //выбранная страна

void AddComponent::RecieveBigData(bigdata * bgd){
    bdw41 = bgd;

    ui->listWidget->clear();
    for (auto i = bdw41->items.begin(); i != bdw41->items.end(); i++){
        ui->listWidget->addItem(i->name);
    }
}

void AddComponent::RecieveItem(item * it){
    cw41 = it;
}

void AddComponent::on_pushButton_clicked()
{
    if (ui->listWidget->currentItem()->text() != cw41->name && cw41->check_cmp(ui->listWidget->currentItem()->text())){
        cw41->set_component(bdw41->search_item(ui->listWidget->currentItem()->text()));
    }
    close();
}

