#include "game.h"

//=========
//CONSTRUCT
//=========

Game::Game(){
    this->choice = 0;
    this->playing = true;
    this->activeCharacter = 0;
    filename = "characters.txt";
}

Game::~Game(){

}

//+++++++++
//MODIFIERS
//---------

void Game::initialize(){
    Map m;
    m.generateMap(10);
    m.showMap();
    this->createCharacter();
}   

void Game::mainMenu(){
    //Display options menu
    cout << "= Main Menu =" << endl;

    cout << "0: Quit" << endl;
    cout << "1: Load Character" << endl;
    cout << "2: Save Character" << endl;
    cout << "3: New Character" << endl;
    cout << endl;

    cout << endl << "Choice:" << endl;
    
    //Take input and acts
    cin >> choice;
    cout << endl;
    switch(choice){
        case 0: playing = false;
                break;

        case 1: this->loadCharacters();
                break;

        case 2: this->saveCharacters();
                break;

        case 3: cin.ignore();
                this->createCharacter();
                this->saveCharacters ();
                break;

        case 4: this->characters[this->activeCharacter].printStats();
                break;

        default: break;
    }
}

void Game::createCharacter(){
    string name;
    cout << "Enter character name: ";
    getline(cin,name);

    this->characters.push_back(Character());
    this->activeCharacter = this->characters.size()-1;
    this->characters[activeCharacter].initialize(name);
}

void Game::loadCharacters(){

}

void Game::saveCharacters(){
    ofstream outfile(this->filename);

    if(outfile.is_open()){
        for(size_t i =0; i < this->characters.size();i++){
            outfile << this->characters[i].getAsString() << "\n";
        }
    }

    outfile.close();
}

//=========
//ACCESSORS
//=========

//++++++++++++++
//PRIV-MODIFIERS
//--------------

//==============
//PRIV-ACCESSORS
//==============
