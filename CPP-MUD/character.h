#ifndef CHAR_HEADER
#define CHAR_HEADER

#include "inventory.h"
#include <math.h>

using namespace std;

class Character{

    public:
        Character();
        virtual ~Character();
        
        //Accessors
        inline const double getX() const {return this-> xPos;};
        inline const double getY() const {return this-> yPos;};
        inline const string getName() const {return this->name;};
        inline const int getLevel() const {return this->level;};
        inline const int getExp() const {return this->exp;};
        inline const int getExpNext() const {return this->expNext;};
        inline const int getHP() const {return this->hp;};
        inline const int getMaxHP() const {return this->hpMax;};
        inline const int getStanima() const {return this->stamina;};
        inline const int getDmgMin() const {return this->physDamageMin;};
        inline const int getDmgMax() const {return this->physDamageMax;};
        inline const int getDef() const {return this->defence;};
        inline const int getMana() const {return this->mana;};
        inline const int getMaxMana() const {return this->maxMana;};
        inline const int getMinMagicDamage() const {return this->magicDamageMin;};
        inline const int getMaxMagicDamage() const {return this->magicDamageMax;};
        inline const int getAccuracy() const {return this->accuracy;};
        string getAsString() const;

        //Modifiers
        void initialize(const string name);
        void printStats() const;
        void levelUp();

    private:

        //Priv-Accessors

        //Priv-Modifiers

        //Position
        int xPos;
        int yPos;
        
        //Attributes
        string name;
        int level;
        int exp;
        int expNext;
        int hp;
        int hpMax;
        int stamina;
        int maxStamina;
        int mana;
        int maxMana;
        int magicDamageMin;
        int magicDamageMax;
        int physDamageMin;
        int physDamageMax;
        double defence;
        double accuracy;

        //Points
        int statPoints;
        int skillPoints;

        //Stats
        int strength;
        int constitution;
        int dexterity;
        int wisdom;
        int intelligence;
        int luck;
        int charisma;

        //Inventory
        Inventory inventory;

        //Carry
        Weapon weapon_right;
        Weapon weapon_left;
        Armor armor_head;
        Armor armor_torso;
        Armor armor_waist;
        Armor armor_cloak;
        Armor armor_arms;
        Armor armor_hands;
        Armor armor_legs;
        Armor armor_feet;


};

#endif