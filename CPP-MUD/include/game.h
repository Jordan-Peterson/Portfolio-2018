#ifndef GAME_HEADER
#define GAME_HEADER

#include "functions.h"
#include "character.h"
#include "World/map.h"
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

class Game{

    public:
        Game();
        virtual ~Game();

        //Accessors
        inline bool getPlaying(){return this->playing;};
        
        //Modifiers
        void mainMenu();
        void initialize();
        inline void setPlaying(bool set){this->playing = set;};
        void createCharacter();
        void loadCharacters();
        void saveCharacters();
    
    private:
        int choice;
        bool playing;

        vector<Character> characters;
        int activeCharacter;
        string filename;
};
#endif
