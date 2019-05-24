#ifndef ARMOR_HEADER
#define ARMOR_HEADER

#include "item.h"

using namespace std;

class Armor : public Item{

    public:

        Armor(int id=-1,string name="NONE",string desc="",int level=0,double sval=0.0,double bval=0.0,int rare=-1,int type=-1,double phys=0.0,double magic=0.0);
        virtual ~Armor();

        //Pure Virtual
        virtual Armor* clone() const;


        //Modifiers


        //Accessors

    private:
        //Priv-Var
        int type;
        double physResist;
        double magicResist;

        //Priv-Modifiers


        //Priv-Accessors
};
#endif
