#include "../../include/Enemies/enemy.h"

//=========
//CONSTRUCT
//=========
Enemy::Enemy(int level){
    this->level = level;
    this->hpMax = level*10;
    this->hp = hpMax;
    this->manaMax = level * (3);
    this->mana = manaMax;
    this->staminaMax = level * (5);
    this->stamina = staminaMax;
    this->defence = rand() %100 * level;
    this->accuracy = rand()%100 * level;
    this->physDmgMin = level * 3;
    this->physDmgMax = level * 4;
    this->magicDmgMin = level * 3;
    this->magicDmgMax = level * 4;
}

Enemy::~Enemy(){

}

//+++++++++
//MODIFIERS
//---------

//=========
//ACCESSORS
//=========
string Enemy::getAsString() const{
    return "Level: " + to_string(level) + "\n"
        + "HP: [" + to_string(hp) + "/" + to_string(hpMax) + "]\n"
        + "Mana: [" + to_string(mana) + "/" + to_string(manaMax) +"]\n"
        + "Stamina: [" + to_string(stamina) + "/"+ to_string(staminaMax) + "]\n"
        + "Phys. Damage: [" + to_string(physDmgMin) + " - " + to_string(physDmgMax) + "]\n"
        + "Mag. Damage: [" + to_string(magicDmgMin) + " - " + to_string(magicDmgMax) + "]\n"
        + "Defence: " + to_string(defence) + "\n"
        + "Accuracy: " + to_string(accuracy);
}

//++++++++++++++
//PRIV-MODIFIERS
//--------------

//==============
//PRIV-ACCESSORS
//==============
