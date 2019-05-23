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
        inline double getX() const {return this-> xPos;};
        inline double getY() const {return this-> yPos;};
        inline string getName() const {return this->name;};
        inline int getLevel() const {return this->level;};
        inline int getExp() const {return this->exp;};
        inline int getExpNext() const {return this->expNext;};
        inline int getHP() const {return this->hp;};
        inline int getMaxHP() const {return this->hpMax;};
        inline int getStanima() const {return this->stamina;};
        inline int getDmgMin() const {return this->physDamageMin;};
        inline int getDmgMax() const {return this->physDamageMax;};
        inline int getDef() const {return this->defence;};
        inline int getMana() const {return this->mana;};
        inline int getMaxMana() const {return this->maxMana;};
        inline int getMinMagicDamage() const {return this->magicDamageMin;};
        inline int getMaxMagicDamage() const {return this->magicDamageMax;};
        inline int getAccuracy() const {return this->accuracy;};
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
