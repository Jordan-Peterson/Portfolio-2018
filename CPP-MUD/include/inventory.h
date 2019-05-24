#ifndef INVENTORY_HEADER
#define INVENTORY_HEADER

#include "Item/weapon.h"
#include "Item/armor.h"

using namespace std;

class Inventory{

    public:
        Inventory();
        Inventory(const Inventory&);
        virtual ~Inventory();
        Item& operator[](const int index);

        //Modifiers
        void addItem(const Item& item);
        //void removeItem(int index);

        //Accessors
        string getAsString() const;
        inline int size() const {return this->numItem;};

    private:

        //Priv-Modifiers
        void expand();
        void initialize(const int from = 0);

        //Priv-Accessors

        //Priv-Var
        int capacity;
        int numItem;
        Item **items;

};
#endif
