#include "character.h"

//=========
//CONSTRUCT
//=========

Character::Character(){

    //Construct position
    this->xPos = 0;
    this->yPos = 0;

    //construct attributes
    this->name = "";
    this->level = 0;
    this->exp = 0;
    this->expNext = 0;

    //construct stats
    this->strength = 0;
    this->constitution = 0;
    this->dexterity = 0;
    this->wisdom = 0;
    this->intelligence = 0;
    this->luck = 0;
    this->charisma = 0;

    this->hp = 0;
    this->hpMax = 0;
    this->stamina = 0;
    this->maxStamina = 0;
    this->mana = 0;
    this->maxMana = 0;
    this->physDamageMin = 0;
    this->physDamageMax = 0;
    this->magicDamageMin = 0;
    this->magicDamageMax = 0;
    this->defence = 0;
    this->accuracy = 0;

    //construct points
    this->statPoints = 0;
    this->skillPoints = 0;
}

Character::~Character(){

}

//+++++++++
//MODIFIERS
//---------

void Character::initialize(const string name){
    //Initialize postion
    this->xPos = 0;
    this->yPos = 0;

    //Initialize character attributes
    this->name = name;
    this->level = 1;
    this->exp = 0;
    this->expNext = static_cast<int>((50/3)*((pow(level,3)-
                                    6*pow(level,2))+
                                    17*level-12)+100);

    //Initialize stats
    this->strength = 5;
    this->constitution = 5;
    this->dexterity = 5;
    this->wisdom = 5;
    this->intelligence = 5;
    this->luck = 5;
    this->charisma = 5;

    this->hpMax = (this->constitution*2) + (this->strength/2);
    this->hp = hpMax;
    this->maxStamina = this->constitution + (this->strength/2) + (this->dexterity/3);
    this->stamina = maxStamina;
    this->maxMana = this->intelligence + (this->wisdom/2);
    this->mana = maxMana;
    this->physDamageMin = (this->strength);
    this->physDamageMax = (this->strength) + (this->dexterity/3);
    this->magicDamageMin = (this->intelligence);
    this->magicDamageMax = (this->intelligence) + (this->wisdom/3);
    this->defence = (this->constitution/2) + (this->strength/4);
    this->accuracy = (this->dexterity) + (this->luck/2) + (this->wisdom/4);
    //Initialize sp/ap points
    this->statPoints = 0;
    this->skillPoints = 0;
}

void Character::printStats() const{
    cout << "= Character Sheet =" << endl;
    cout << " Name: " << this->name << endl;
    cout << " Level: " << this->level << endl;
    cout << " Health: [" << this->hpMax << "/" << this->hpMax << "]" << endl;
    cout << " Stamina: [" << this->stamina << "/" << this->maxStamina << "]" << endl;
    cout << " Mana: [" << this->mana << "/" << this->maxMana << "]" << endl;
    cout << " EXP: " << this->exp << endl;
    cout << " EXP Needed: " << this->expNext << endl;
    cout << "= STATS =" << endl;
    cout << "vvvvvvvvv" << endl;
    cout << " Strength: " << this->strength << endl;
    cout << " Constitution: " << this->constitution << endl;
    cout << " Dexterity: " << this->dexterity << endl;
    cout << " Wisdom: " << this->wisdom << endl;
    cout << " Luck: " << this->luck << endl;
    cout << " Charisma: " << this->charisma << endl;
    cout << "^^^^^^^^^" << endl;
    cout << "= COMBAT =" << endl;
    cout << " Defence: " << this->defence << endl;
    cout << " Accuracy: " << this->accuracy << endl;
    cout << " Physical Damage Min: " << this->physDamageMin << endl;
    cout << " Physical Damage Max: " << this->physDamageMax << endl;
    cout << " Magical Damage Min: " << this->magicDamageMin << endl;
    cout << " Magical Damage Max: " << this->magicDamageMax << endl;
    cout << "= End Sheet =" << endl;
    cout << endl;
}

void Character::levelUp(){
    
    //level up and handle overlevel
    while(exp >= expNext){
        exp -= expNext;
        this->level++;
        this->expNext=static_cast<int>((50/3)*((pow(level,3)-
                                    6*pow(level,2))+
                                    17*level-12));
    }
    this->statPoints++;
    this->skillPoints++;
}

//=========
//ACCESSORS
//=========

string Character::getAsString() const{
    return to_string(this->xPos) + " "
        + to_string(this->yPos) + " "
        + name + " "
        + to_string(level) + " "
        + to_string(exp) + " "
        + to_string(expNext) + " "
        + to_string(hp) + " "
        + to_string(hpMax) + " "
        + to_string(stamina) + " "
        + to_string(maxStamina) + " "
        + to_string(mana) + " "
        + to_string(maxMana) + " "
        + to_string(magicDamageMin) + " "
        + to_string(magicDamageMax) + " "
        + to_string(physDamageMin) + " "
        + to_string(physDamageMax) + " "
        + to_string(defence) + " "
        + to_string(accuracy) + " "
        + to_string(statPoints) + " "
        + to_string(skillPoints) + " "
        + to_string(strength) + " "
        + to_string(constitution) + " "
        + to_string(dexterity) + " "
        + to_string(wisdom) + " "
        + to_string(intelligence) + " "
        + to_string(luck) + " "
        + to_string(charisma) + " "
        + this->inventory.getAsString();
}

//++++++++++++++
//PRIV-MODIFIERS
//--------------

//==============
//PRIV-ACCESSORS
//==============
