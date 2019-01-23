#include "item.h"

//=========
//CONSTRUCT
//=========

Item::Item(int id, string name,string desc,int level,double sval,double bval,int rare){
    this->itemID = id;
    this->itemName = name;
    this->desc = desc;
    this->level = level;
    this->itemSellValue = sval;
    this->itemBuyValue = bval;
    this->rarity = rare;
}

Item::~Item(){

}

//+++++++++
//MODIFIERS
//---------

//=========
//ACCESSORS
//=========

string Item::getInfo() const{
    return to_string(itemID) + " "
        + itemName + " "
        + desc + " "
        + to_string(itemSellValue) + " "
        + to_string(itemBuyValue);

}

//++++++++++++++
//PRIV-MODIFIERS
//--------------

//==============
//PRIV-ACCESSORS
//==============