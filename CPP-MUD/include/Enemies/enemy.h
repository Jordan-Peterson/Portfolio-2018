#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include <stdlib.h>
#include <string>

using namespace std;

class Enemy{

    public:

        Enemy(int level = 0);
        virtual ~Enemy();
        virtual Enemy* clone() = 0;

        //Var


        //Modifiers


        //Accessors
        inline bool isAlive() const {return this->hp >0;};
        string getAsString() const;
        inline void takeDamage(int damage) {this->hp -= damage;};
        inline int getDamage() const {return -(rand() % this->physDmgMax - this->physDmgMin);};
        inline int getExp() const {return this->level*100;};


    private:

        //Priv-Var
        int level;
        int hpMax;
        int hp;
        int manaMax;
        int mana;
        int staminaMax;
        int stamina;
        int physDmgMin;
        int physDmgMax;
        int magicDmgMin;
        int magicDmgMax;
        double defence;
        double accuracy;


        //Priv-Modifiers


        //Priv-Accessors
};
#endif
