//
//  main.cpp
//  Exam
//
//  Created by Богдан on 12/9/18.
//  Copyright © 2018 Богдан. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

void show_items();
void home();
void add_items();
void add_component(int num);
void info_items(int num);
int search_item(string a);
void add_countries();
void show_countries();
void add_item_to_country(int num);
void info_countries(int num);
void add_records(int num, int ct);

class item { //класс товара, который содержит название товара и массив компонентов (и их количества)
public:
    string name;
    map <item,int> components;
    
    item (string name) {
        item::name = name;
    }
    
    item(){
        
    }
    
    void set_component (item part, int amount) {
        components[part] = amount;
    }
    
    bool operator <(const item& rhs) const
    {
        return name < rhs.name;
    }
};

vector<item> items; //массив товаров.

struct record { //структура, для хранения статистики по товарам для разных периодов
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
};

struct data { //структура, используемая для страны, хранит указатель на товар и доп. информацию про него
    item * element;
    vector<record> records;
    
    data (int n){
        element = &items[n];
    }
    
    data(){
        
    }
};

class country { //класс страны, который содержит название страны и массив товаров (со всей присущей им информацией)
public:
    string name;
    vector<data> items_of_country;
    
    country (string name) {
        country::name = name;
    }
    country(){
        
    }
};

vector<country> countries; //массив стран

void home() { //начальное диалоговое окно
    int cho;
    cout << endl << " Главное меню" << endl;
    cout << "1. Список стран" << endl;
    cout << "2. Список товаров" << endl;
    cout << "3. Добавить страну" << endl;
    cout << "4. Добавить товар" << endl;
    cout << "5. Выход из программы" << endl;
    cin >> cho;
    switch (cho) {
        case 1: {
            show_countries();
            break;
        }
        case 2: {
            show_items();
            break;
        }
        case 3: {
            add_countries();
            break;
        }
        case 4: {
            add_items();
            break;
        }
        case 5: {
            exit(0);
            break;
        }
        default: {
            home();
        }
    }
}

template <typename Pair>
struct Less : public std::binary_function<Pair, Pair, bool>
{
    bool operator()(const Pair &x, const Pair &y) const
    {
        return x.first < y.first;
    }
};

void balance(int num) {
    vector<int> used;
    multimap <int, int> statistic;
    int cho;
    for ( auto it = countries.begin(); it != countries.end(); ++it ) {
        for ( auto its = it->items_of_country.begin(); its != it->items_of_country.end(); ++its ) {
            if (its->element->name == items[num].name) {
                for ( auto itss = its->records.begin(); itss != its->records.end(); ++itss ) {
                    statistic.insert(make_pair(itss->year, itss->exporting - itss->importing));
                }
            }
        }
    }
    cout << endl << " Просмотр баланса по товару " << items[num].name << ":" << endl;
    for ( auto it = statistic.begin(); it != statistic.end(); ++it ) {
        int sum = 0;
        pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret = statistic.equal_range(it->first);
        for(multimap<int, int>::iterator its = ret.first; its!=ret.second; ++its) {
            sum += its->second;
        }
        int tmp = 0;
        for(int i = 0; i < used.size(); i++){
            if(used[i] == it->first){
                tmp = 1;
            }
        }
        if (tmp == 0) {
            cout << "За " << it->first << " год баланс = " << sum << endl;
            used.push_back(it->first);
        }
    }
    cout << "1. Назад" << endl << "2. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        info_items(num);
    } else {
        home();
    }
}

void show_items() { //выводит список товаров
    int i = 0;
    int cho;
    cout << endl << " Список товар: (узнать инф. про товар - введите номер товара)" << endl;
    for ( auto its = items.begin(); its != items.end(); ++its ) {
        i++;
        cout << i << ". " << its->name << endl;
    }
    cout << i+1 << ". " << "Домой" << endl;
    cin >> cho;
    if (cho >= i+1 || cho <= 0) {
        home();
    } else {
        info_items(cho-1);
    }
}

void show_components(int num){ //диалог с компнентами товара и возможностью добавить новые компоненты
    int cho;
    cout << endl << " Товар " << items[num].name<< " состоит из: (узнать инф. про компонент - введите номер компонента)" << endl;
    int i = 0;
    for ( auto its = items[num].components.begin(); its != items[num].components.end(); ++its ) {
        i++;
        cout << i << ". " << its->first.name << " в количестве " << its->second << endl;
    }
    cout << i+1 << ". Добавить новый компонент" << endl;
    cout << i+2 << ". Назад" << endl;
    cout << i+3 << ". Домой" << endl;
    cin >> cho;
    if (cho == i+1) {
        add_component(num);
    } else if (cho >= i+3) {
        home();
    } else if (cho == i+2) {
        info_items(num);
    } else {
        i = 0;
        for ( auto its = items[num].components.begin(); its != items[num].components.end(); ++its ) {
            i++;
            if (i == cho) {
                info_items(search_item(its->first.name));
            }
        }
    }
}

void show_parents(int num) { //отображает товары, компонентом который является данный товар
    int i = 0;
    int cho;
    cout << endl << " Товар " << items[num].name<< " ипользуется в:" << endl;
    for ( auto its = items.begin(); its != items.end(); ++its ) {
        for (auto it = its->components.begin(); it != its->components.end(); ++it) {
            if (it->first.name == items[num].name) {
                i++;
                cout << i << ". " << its->name << endl;
            }
        }
    }
    cout << i+1 << ". Назад" << endl;
    cout << i+2 << ". Домой" << endl;
    cin >> cho;
    if (cho >= i+2) {
        home();
    } else if (cho == i+1) {
        info_items(num);
    } else {
        i = 0;
        for ( auto its = items.begin(); its != items.end(); ++its ) {
            for (auto it = its->components.begin(); it != its->components.end(); ++it) {
                if (it->first.name == items[num].name) {
                    i++;
                    if (i == cho) {
                        info_items(search_item(its->name));
                    }
                }
            }
        }
    }
}

void show_pr_country_pr(int num){ //вывод стран-производителей
    int cho;
    cout << endl << " Список стран-производителей:" << endl;
    for (auto it = countries.begin(); it != countries.end(); ++it ) {
        for (auto its = it->items_of_country.begin(); its != it->items_of_country.end(); ++its ) {
            if (its->element->name == items[num].name) {
                for (auto itss = its->records.begin(); itss != its->records.end(); ++itss ) {
                    if (itss->produce > 0) {
                        cout << "Страна: " << it->name << " Количество: " << itss->produce << " Год: " << itss->year << endl;
                    }
                }
            }
        }
    }
    cout << "1. Назад" << endl << "2. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        info_items(num);
    } else {
        home();
    }
}

void show_pr_country_im(int num){ //вывод стран-импортеров
    int cho;
    cout << endl << " Список стран-импортеров:" << endl;
    for (auto it = countries.begin(); it != countries.end(); ++it ) {
        for (auto its = it->items_of_country.begin(); its != it->items_of_country.end(); ++its ) {
            if (its->element->name == items[num].name) {
                for (auto itss = its->records.begin(); itss != its->records.end(); ++itss ) {
                    if (itss->importing > 0) {
                        cout << "Страна: " << it->name << " Количество: " << itss->importing << " Год: " << itss->year << endl;
                    }
                }
            }
        }
    }
    cout << "1. Назад" << endl << "2. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        info_items(num);
    } else {
        home();
    }
}

void show_pr_country_ex(int num){ //вывод стран-экспортеров
    int cho;
    cout << endl << " Список стран-экспортеров:" << endl;
    for (auto it = countries.begin(); it != countries.end(); ++it ) {
        for (auto its = it->items_of_country.begin(); its != it->items_of_country.end(); ++its ) {
            if (its->element->name == items[num].name) {
                for (auto itss = its->records.begin(); itss != its->records.end(); ++itss ) {
                    if (itss->exporting > 0) {
                        cout << "Страна: " << it->name << " Количество: " << itss->exporting << " Год: " << itss->year << endl;
                    }
                }
            }
        }
    }
    cout << "1. Назад" << endl << "2. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        info_items(num);
    } else {
        home();
    }
}

void info_items(int num) { //информационный диалог
    int cho;
    cout << endl << " Вы выбрали товар " << items[num].name << ":" << endl;
    cout << "1. Просмотр компонентов этого товара" << endl;
    cout << "2. Компонентом чего есть этот товар" << endl;
    cout << "3. Страны-производители" << endl;
    cout << "4. Страны-импортеры" << endl;
    cout << "5. Страны-экспортеры" << endl;
    cout << "6. Баланс" << endl;
    cout << "7. Домой" << endl;
    cin >> cho;
    
    switch (cho) {
        case 1: {
            show_components(num);
            break;
        }
        case 2: {
            show_parents(num);
            break;
        }
        case 3: {
            show_pr_country_pr(num);
            break;
        }
        case 4: {
            show_pr_country_im(num);
            break;
        }
        case 5: {
            show_pr_country_ex(num);
            break;
        }
        case 6: {
            balance(num);
            break;
        }
        default: {
            home();
        }
    }
}

int search_item(string a){ //возвращает номер товара по названию
    for (int i = 0; i < items.size(); i++ ) {
        if (items[i].name == a) {
            return i;
        }
    }
    return -1;
}

void add_items() { //добавляет товар
    string tmp;
    int cho;
    cout << endl << " Введите название товара" << endl;
    cin >> tmp;
    items.push_back(item(tmp));
    
    cout << endl;
    cout << "1. Добавить компонент" << endl;
    cout << "2. Список товаров" << endl;
    cout << "3. Домой" << endl;
    cin >> cho;
    
    switch (cho) {
        case 1: {
            add_component(search_item(tmp));
            break;
        }
        case 2: {
            show_items();
            break;
        }
        default: {
            home();
        }
    }
}

void add_component(int num) { //диалог для добавления компонентов в товар
    int cho;
    cout << endl;
    cout << "1. Выбрать из существующих" << endl;
    cout << "2. Создать новый" << endl;
    cin >> cho;
    
    switch (cho) {
        case 1: {
            int n;
            cout << endl << " Выберите товар, необходимый для " << items[num].name << ":" << endl;
            for (int i = 0; i < items.size(); i++ ) {
                cout << i+1 << ". " << items[i].name << endl;
            }
            cin >> cho;
            cout << endl << "Введите количество, необхожимое для " << items[num].name << ":" << endl;
            cin >> n;
            items[num].set_component(items[cho - 1], n);
            
            cout << endl;
            cout << "1. Добавить еще компонент" << endl;
            cout << "2. Домой" << endl;
            cin >> cho;
            if (cho == 1) {
                add_component(num);
            } else {
                home();
            }
            break;
            
            break;
        }
        case 2: {
            string tmp;
            int n;
            cout << endl << "Введите название товара, необходимого для " << items[num].name << ":" << endl;
            cin >> tmp;
            items.push_back(item(tmp));
            cout << endl << "Введите количество, необхожимое для " << items[num].name << ":" << endl;
            cin >> n;
            items[num].set_component(items.back(), n);
            
            cout << endl;
            cout << "1. Добавить еще" << endl;
            cout << "2. Домой" << endl;
            cin >> cho;
            if (cho == 1) {
                add_component(num);
            } else {
                home();
            }
            break;
        }
        default: {
            home();
        }
    }
}

void show_items_of_ct(int num){ //отображение списка товаров, относящихся к стране
    int cho;
    int i = 0;
    cout << " Список товаров страны " << countries[num].name << ": (узнать инф. про товар - введите номер товара)" << endl;
    for (auto it = countries[num].items_of_country.begin(); it != countries[num].items_of_country.end(); it++){
        i++;
        cout << i << ". " << it->element->name << endl;
    }
    cout << i+1 << ". Назад" << endl;
    cin >> cho;
    
    if ((cho > 0) && ( cho <= i)) {
        i = 0;
        for (auto it = countries[num].items_of_country.begin(); it != countries[num].items_of_country.end(); it++){
            i++;
            if (i == cho) {
                cout << endl << " Информация про товар " << it->element->name << ":" << endl;
                for (auto its = it->records.begin(); its != it->records.end(); its++){
                    cout << "Год: " << its->year << " Производит: " << its->produce << " Импортирует: " << its->importing << " Экспортирует: " << its->exporting << endl;
                }
                cout << "1. Назад" << endl << "2. Добавить статистики про товар" << endl << "3. Домой" << endl;
                cin >> cho;
                if (cho == 1){
                    show_items_of_ct(num);
                } else if (cho == 2) {
                    add_records(search_item(it->element->name), num);
                } else {
                    home();
                }
            }
        }
    } else {
        info_countries(num);
    }
}

void info_countries(int num){ //информационный диалог для страны
    int cho;
    cout << endl << " Вы выбрали страну " << countries[num].name << ":" << endl;
    cout << "1. Присвоить товар стране" << endl;
    cout << "2. Список товаров" << endl;
    cout << "3. Назад" << endl;
    cout << "4. Домой" << endl;
    cin >> cho;
    
    switch (cho) {
        case 1: {
            add_item_to_country(num);
            break;
        }
        case 2: {
            show_items_of_ct(num);
            break;
        }
        case 3: {
            show_countries();
            break;
        }
        default: {
            home();
        }
    }
}

void show_countries(){ //функция вывода массива стран с возможностью получить дальнейшую информацию про нее
    int cho;
    int i = 0;
    cout << endl << " Список стран: (узнать инф. про товар - введите номер товара)" << endl;
    for (auto its = countries.begin(); its != countries.end(); ++its ) {
        i++;
        cout << i << ". " << its->name << endl;
    }
    cout << i+1 << ". Домой" << endl;
    cin >> cho;
    if (cho >= i+1 || cho <= 0) {
        home();
    } else {
        info_countries(cho-1);
    }
}

void add_records(int num, int ct){ //функция добавление статистики за год для товара страны
    int cho;
    int pr, ex, im, ye;
    cout << endl << "Сколько производит страна " << countries[ct].name  << " товара " << items[num].name << ": (введите число)" << endl;
    cin >> pr;
    cout << endl << "Сколько экспортирует страна " << countries[ct].name  << " товара " << items[num].name << ": (введите число)" << endl;
    cin >> ex;
    cout << endl << "Сколько импортирует страна " << countries[ct].name  << " товара " << items[num].name << ": (введите число)" << endl;
    cin >> im;
    cout << endl << "За какой год статистика: (введите число)" << endl;
    cin >> ye;
    for (auto its = countries[ct].items_of_country.begin(); its != countries[ct].items_of_country.end(); ++its ) {
        if (its->element->name == items[num].name) {
            its->records.push_back(record(pr, ex, im, ye));
        }
    }
    
    cout << endl << "1. Добавить еще статистики" << endl;
    cout << "2. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        add_records(num, ct);
    } else {
        home();
    }
}

void add_item_to_country(int num){ //функция добавления принадлежности товара к стране
    int cho;
    int i = 0;
    cout << endl;
    if (items.empty()){
        cout << " Список товаров пуст, нужно добавить товар" << endl;
        cout << "1. Добавить товар" << endl << "2. Домой" << endl;
        cin >> cho;
        if (cho == 1){
            add_items();
        } else {
            home();
        }
    } else {
        cout << " Выберите товар, который хотите добавить к стране:" << endl;
        for ( auto its = items.begin(); its != items.end(); ++its ) {
            i++;
            cout << i << ". " << its->name << endl;
        }
        cin >> cho;
        if (cho-1 <= items.size() && cho-1 >= 0){
            countries[num].items_of_country.push_back(cho-1);
        } else {
            home();
        }
        
        cout << endl << "1. Добавить статистику товара" << endl;
        cout << "2. Добавить еще товар" << endl;
        cout << "3. Домой" << endl;
        int cho2;
        cin >> cho2;
        if (cho2 == 1){
            add_records(cho-1, num);
        } else if (cho2 == 2){
            add_item_to_country(num);
        } else {
            home();
        }
    }
}

int search_country(string a){ //возвращает номер страны в массиве стран
    for (int i = 0; i < countries.size(); i++ ) {
        if (countries[i].name == a) {
            return i;
        }
    }
    return -1;
}

void add_countries() { //добавляет страну
    string tmp;
    int cho;
    cout << endl << "Введите название страны:" << endl;
    cin >> tmp;
    countries.push_back(country(tmp));
    
    cout << endl;
    cout << "1. Добавить товар к стране" << endl;
    cout << "2. Список стран" << endl;
    cout << "3. Домой" << endl;
    cin >> cho;
    
    switch (cho) {
        case 1: {
            add_item_to_country(search_country(tmp));
            break;
        }
        case 2: {
            show_countries();
            break;
        }
        default: {
            home();
        }
    }
}

const char* FName = "/Myproject/data.txt";

void writing(){
    ofstream out(FName);
    size_t size = countries.size();
    out.write((char*)&size,sizeof(size_t));
    out.write((char*)&countries[0],size*sizeof(countries[0]));
    out.close();
    cout << "Successfuly written";
}

void reading(){
    ifstream in(FName);
    size_t size;
    in.read((char*)&size,sizeof(size_t));
    countries.resize(size);
    in.read((char*)&countries[0],size*sizeof(countries[0]));
    in.close();
}

int main(int argc, const char * argv[]) {
    reading();
    atexit(writing);
    home();
    return 0;
    
    //  4 Glass 3 4 Iron 3 4 Plastic 3 4 Tea 3 4 Rubber 3 4 Wire 1 1 2 1 1 1 5 3 2 4 Board 1 1 2 2 1 1 3 5 2 4 Controller 1 1 2 2 1 1 3 5 2 4 Fridge 1 1 2 5 1 1 3 10 1 1 5 2 1 1 6 20 2 4 Computer 1 1 2 3 1 1 3 5 1 1 6 2 1 1 7 2 2 4 Oven 1 1 2 10 1 1 1 5 1 1 8 1 1 1 6 5 2 4 Window 1 1 1 10 1 1 2 2 1 1 3 5 2 4 Tyre 1 1 5 15 2 3 Ukraine 1 2 2 3 2 6 2 9 2 12 3 3 Russia 1 1 2 2 2 5 2 6 2 13 3 3 Poland 1 1 2 3 2 8 2 9 2 11 3 3 Bulgaria 1 1 2 2 2 7 2 12 2 13 3 3 Germany 1 2 2 4 2 7 2 8 2 13 3 3 USA 1 1 2 2 2 3 2 7 2 8 2 10 2 13 3 3 England 1 4 2 2 2 5 2 8 2 9 2 12 3 1 1 2 1 2 5 3 2 2016 1 20 4 10 2015 2 1 2 2 2 2 300 10 40 2016 1 30 25 10 2014 2
}

