#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

bigdata world;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    test_setup();

    w1 = new AddCountry();
    w2 = new additem();
    w3 = new InfoCountry();
    w4 = new InfoItem();

    connect(w1, SIGNAL(SendCountryName(QString)), this, SLOT(RecieveCountryName(QString)));
    connect(w2, SIGNAL(SendItemName(QString)), this, SLOT(RecieveItemName(QString)));
    connect(this, SIGNAL(SendCountryName(QString)), w3, SLOT(RecieveCountryName(QString)));
    connect(this, SIGNAL(SendBigData(bigdata*)), w3, SLOT(RecieveBigData(bigdata*)));
    connect(this, SIGNAL(SendItem(item*)), w4, SLOT(RecieveItem(item*)));
    connect(this, SIGNAL(SendBigData(bigdata*)), w4, SLOT(RecieveBigData(bigdata*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test_setup()
{
    world.ad_country("Ukraine");
    world.ad_country("USA");
    world.ad_country("France");
    world.ad_country("Spain");
    world.ad_country("German");
    world.ad_country("China");
    CountriesUpdate();

    world.ad_item("Iron");
    world.ad_item("Car");
    world.ad_item("Glass");
    world.ad_item("Window");
    world.ad_item("Plastic");
    world.ad_item("Pen");
    world.ad_item("Wood");
    world.ad_item("Table");
    world.ad_item("Rubber");
    world.ad_item("Tire");
    world.ad_item("Silk");
    world.ad_item("Skirt");
    ItemsUpdate();
}

void MainWindow::on_pushButton_clicked()
{
    w1->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    w2->show();
}

void MainWindow::CountriesUpdate(){
    ui->listWidget->clear();
    for (auto i = world.countries.begin(); i != world.countries.end(); i++){
        ui->listWidget->addItem(i->name);
    }
}

void MainWindow::ItemsUpdate(){
    ui->listWidget_2->clear();
    for (auto i = world.items.begin(); i != world.items.end(); i++){
        ui->listWidget_2->addItem(i->name);
    }
}

void MainWindow::RecieveCountryName(QString str){
    if (world.search_country(str) == nullptr){
        world.ad_country(str);
        CountriesUpdate();
    }
}

void MainWindow::RecieveItemName(QString str){
    if (world.search_item(str) == nullptr){
        world.ad_item(str);
        ItemsUpdate();
    }
}

void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    w3->show();
    emit SendBigData(&world);
    emit SendCountryName(item->text());
}

void MainWindow::on_listWidget_2_itemActivated(QListWidgetItem *item)
{
    w4->show();
    emit SendBigData(&world);
    emit SendItem(world.search_item(item->text()));
}
