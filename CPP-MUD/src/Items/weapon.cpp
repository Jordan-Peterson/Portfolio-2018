#include "../../include/Item/weapon.h"

//=========
//CONSTRUCT
//=========
Weapon::Weapon(int id,string name,string desc,int level,double sval,double bval,int rare,double physMin,double physMax,double magMin, double magMax)
    : Item(id,name,desc,level,sval,bval,rare){
    this->physDamageMin = physMin;
    this->physDamageMax = physMax;
    this->magicDamageMin = magMin;
    this->magicDamageMax = magMax;
}

Weapon::~Weapon(){

}

Weapon* Weapon::clone() const{
    return new Weapon(*this);
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
