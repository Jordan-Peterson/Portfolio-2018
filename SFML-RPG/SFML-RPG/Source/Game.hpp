//
//  Game.hpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "MainMenuState.hpp"

class Game
{
private:
    //Variables
    sf::RenderWindow* window;
    sf::Event sfEvent;
    
    sf::Clock dtClock;
    float dt;
    
    std::stack<State*> states;
    std::map<std::string,int> supportedkeys;
    //Init Functions
    void initWindow();
    void initKeys();
    void initStates();
    
    
public:
    //Static Functions
    
    //Constructor-Destructor
    Game();
    virtual ~Game();
    
    //Funcitons
    
    //Update
    void updateSFMLEvent();
    void update();
    void updateDT();
    
    //Render
    void render();
    
    //Core
    void run();
};

#endif /* Game_hpp */
