//
//  State.cpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#include "State.hpp"


State::State(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys){
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
}

State::~State(){
    
}

const bool& State::getQuit(){
    return this->quit;
}

void State::checkForQuit(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))){
        this->quit = true;
    }
}
