#ifndef MYPROJECT_H
#define MYPROJECT_H
#include <QString>
#include <QVector>
#include <QMap>

class country;
class item;
class record;
class records;
class bigdata;

class item { //класс товара, который содержит название товара и массив компонентов (и их количества)
public:
    QString name;
    QVector<item*> components;
    QVector<country*> parents;

    item (QString name) {
        item::name = name;
    }

    item(){
    }

    void set_component (item* part) {
        components.push_back(part);
    }

    bool is_parent(country * cnt){
        for (auto i = parents.begin(); i != parents.end(); i++){
            if (*i == cnt){
                return false;
            }
        }
        return true;
    }

    bool check_cmp(QString name){
        for (int i = 0; i < components.size(); i++){
            if (components[i]->name == name){
                return false;
            }
        }
        return true;
    }

    bool operator <(const item& rhs) const
    {
        return name < rhs.name;
    }
};

class record { //структура, для хранения статистики по товарам для разных периодов
public:
    int produce;
    int exporting;
    int importing;
    int year;

    record (int pr, int ex, int im, int ye){
        produce = pr;
        exporting = ex;
        importing = im;
        year = ye;
    }

    record(){

    }

    bool operator <(const record& rhs) const
    {
        return year < rhs.year;
    }
};

class records { //структура, используемая для страны, хранит указатель на товар и доп. информацию про него
public:
    item * element;
    QVector<record> rec;

    void add_record(int pr = 0, int ex = 0, int im = 0, int ye = 0){
        bool tmp = false;
        for (auto i = rec.begin(); i != rec.end(); i++){
            if (i->year == ye){
                tmp = true;
            }
        }
        if (tmp == false){
            rec.push_back(record(pr, ex, im, ye));
        }
    }

    records(item * el){
        element = el;
    }

    records(){

    }
};

class country { //класс страны, который содержит название страны и массив товаров (со всей присущей им информацией)
public:
    QString name;
    QVector<records> items_of_country;

    void add_item_to_country(item * el){
        items_of_country.push_back(records(el));
    }

    records* search_ritem(QString name){ //находит структуру records по имени товара
        for (auto i = items_of_country.begin(); i != items_of_country.end(); i++){
            if (i->element->name == name){
                return i;
            }
        }
        return nullptr;
    }

    country (QString name) {
        country::name = name;
    }
    country(){

    }
};

class bigdata {
public:
    QVector<country> countries;
    QVector<item> items;

    bigdata(){
    }

    void ad_item(QString name) { //добавляет товар
        items.push_back(item(name));
    }

    void ad_country(QString name) { //добавляет страну
        countries.push_back(country(name));
    }

    country * search_country(QString name){
        for (auto i = countries.begin(); i != countries.end(); i++){
            if (i->name == name){
                return i;
            }
        }
        return nullptr;
    }

    item * search_item(QString name){
        for (auto i = items.begin(); i != items.end(); i++){
            if (i->name == name){
                return i;
            }
        }
        return nullptr;
    }
};





#endif // MYPROJECT_H
