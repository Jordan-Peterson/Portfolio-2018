#include "../include/inventory.h"

//=========
//CONSTRUCT
//=========

Inventory::Inventory(){
    this->capacity = 5;
    this->numItem = 0;
    this->items = new Item*[this->capacity];
    this->initialize();
}

Inventory::Inventory(const Inventory& cpy){
    this->capacity = cpy.capacity;
    this->numItem = cpy.numItem;
    this->items = new Item*[cpy.capacity];
    for(int i = 0; i < cpy.numItem;i++){
        this->items[i] = cpy.items[i]->clone();
    }
    this->initialize(this->numItem);
}

Inventory::~Inventory(){
    for(int i = 0; i < this->numItem;i++){
        delete this->items[i];
    }
    delete[] items;
}

Item& Inventory::operator[](const int index){
    if(index < 0 || index >= this->numItem){
        throw("Bad Index");
    }
    
    return *this->items[index];
}

//+++++++++
//MODIFIERS
//---------

void Inventory::addItem(const Item& item){
    if(this->numItem >= this->capacity){
        expand();
    }

    this->items[this->numItem++] = item.clone();
}

// void Inventory::removeItem(int index){

// }

//=========
//ACCESSORS
//=========

string Inventory::getAsString() const{
    string allItems;
    for(int i = 0; i < numItem; i++){
        if(i == numItem-1){
            allItems += this->items[i]->getInfo();
        }
        else{
            allItems += this->items[i]->getInfo() + " ";
        }
    }
    return allItems;
}

//++++++++++++++
//PRIV-MODIFIERS
//--------------

void Inventory::expand(){
    //double size
    this->capacity *=2;

    Item **tempItems = new Item *[this->capacity];

    for(int i = 0; i < this->numItem; i++){
        tempItems[i] = this->items[i];
    }

    delete[] this->items;

    this->items = tempItems;

    this->initialize(this->numItem);
}

void Inventory::initialize(const int from){
    for(int i = from; i < this->capacity; i++){
        items[i] = nullptr;
    }
}

//==============
//PRIV-ACCESSORS
//==============
