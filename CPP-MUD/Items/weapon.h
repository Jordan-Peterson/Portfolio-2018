#ifndef WEAPON_HEADER
#define WEAPON_HEADER

#include "item.h"

using namespace std;

class Weapon : public Item{

    public: 
        Weapon(int id =-1,string name ="NONE",string desc="",int level =-1,double sval =0.0,double bval =0.0,int rare =-1,double physMin=0.0,double physMax=0.0,double magMin=0.0, double magMax=0.0);
        virtual ~Weapon();

        //Pure Virtual
        virtual Weapon* clone() const;
        
        //Modifiers


        //Accessors


    private:
        //Priv-Var
        double physDamageMin;
        double physDamageMax;
        double magicDamageMin;
        double magicDamageMax;

        //Priv-Modifiers


        //Priv-Accessors

};

#endif