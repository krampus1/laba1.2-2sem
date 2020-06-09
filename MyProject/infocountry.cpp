#include "infocountry.h"
#include "ui_infocountry.h"
#include <QString>
#include <QVector>
#include <QObject>

InfoCountry::InfoCountry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoCountry)
{
    ui->setupUi(this);
    w31 = new AddItemToCnt();
    w32 = new ItemOfCountru();

    connect(this, SIGNAL(SendBigData(bigdata*)), w31, SLOT(RecieveBigData(bigdata*)));
    connect(this, SIGNAL(SendCountry(country*)), w31, SLOT(RecieveCountry(country*)));
    connect(this, SIGNAL(SendBigData(bigdata*)), w32, SLOT(RecieveBigData(bigdata*)));
    connect(this, SIGNAL(SendItem(records*)), w32, SLOT(RecieveItem(records*)));
    connect(w31, SIGNAL(close()), this, SLOT(UpdateInfo()));
}

InfoCountry::~InfoCountry()
{
    delete ui;
}

bigdata * bdw3; //база данных
country * cw3; //выбраная страна

void InfoCountry::RecieveBigData(bigdata * bgd){
    bdw3 = bgd;
}

void InfoCountry::UpdateInfo(){
    ui->listWidget->clear();
    for (auto i = cw3->items_of_country.begin(); i != cw3->items_of_country.end(); i++){
        ui->listWidget->addItem(i->element->name);
    }
}

void InfoCountry::RecieveCountryName(QString str){ // получает имя выбранной страны и апдейтит для нее информацию
    cw3 = bdw3->search_country(str);

    ui->label->setText("Info about " + str);
    UpdateInfo();
}

void InfoCountry::on_pushButton_clicked()
{
    w31->show();
    emit SendBigData(bdw3);
    emit SendCountry(cw3);
}

void InfoCountry::on_listWidget_itemActivated(QListWidgetItem *item)
{
    w32->show();
    emit SendBigData(bdw3);
    emit SendItem(cw3->search_ritem(item->text()));
}
