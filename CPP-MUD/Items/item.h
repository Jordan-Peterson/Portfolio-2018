#ifndef ITEM_HEADER
#define ITEM_HEADER

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Item{

    public:
        Item(int id =-1,string name ="NONE",string desc="",int level =-1,double sval =0.0,double bval =0.0,int rare =-1);
        virtual ~Item();
        virtual Item* clone() const = 0;
        //Modifiers

        
        //Accessors
        string getInfo() const;  
        inline const int& getID() const {return this->itemID;};
        inline const string& getName() const {return this->itemName;};
        inline const int& getLevel() const {return this->level;};
        inline const double& getSellValue() const {return this->itemSellValue;};
        inline const double& getBuyValue() const {return this->itemBuyValue;};
        inline const int& getRarity() const {return this->rarity;};      


    private:
        //Priv-Modifiers


        //Priv-Accessors

        //Priv-Var
        int itemID;
        string itemName;
        string desc;
        int level;
        double itemSellValue;
        double itemBuyValue;
        int rarity;



};

#endif