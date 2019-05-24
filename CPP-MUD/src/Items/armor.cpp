#include "../../include/Item/armor.h"

//=========
//CONSTRUCT
//=========
Armor::Armor(int id,string name,string desc,int level,double sval,double bval,int rare,int type, double phys, double magic)
    : Item(id,name,desc,level,sval,bval,rare){
    this->type = type;
    this->physResist = phys;
    this->magicResist = magic;

}

Armor::~Armor(){

}

Armor* Armor::clone() const{
    return new Armor(*this);
}

//+++++++++
//MODIFIERS
//---------

//=========
//ACCESSORS
//=========

//++++++++++++++
//PRIV-MODIFIERS
//--------------

//==============
//PRIV-ACCESSORS
//==============
