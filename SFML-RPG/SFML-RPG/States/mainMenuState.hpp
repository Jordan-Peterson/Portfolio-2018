//
//  mainMenuState.hpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#ifndef mainMenuState_hpp
#define mainMenuState_hpp

#include "GameState.hpp"

class MainMenuState:
public State{
private:
    //Variables
    sf::RectangleShape background;
    //Functions
    void initKeybinds();
    
public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys);
    virtual ~MainMenuState();
    
    //Functions
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* tartget = nullptr);
    void endState();
};

#endif /* mainMenuState_hpp */
