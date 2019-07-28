//
//  GameState.cpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#include "GameState.hpp"

//PRIVATE

//Functions

void GameState::initKeybinds(){

    std::ifstream ifs(resourcePath() + "gamestate_keybinds.ini");
    if(ifs.is_open()){
        std::string key = "";
        std::string key_set = "";
        while(ifs >> key >> key_set){
            this->keybinds[key] = this->supportedKeys->at(key_set);
        }
    }
    ifs.close();
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys) : State(window, supportedKeys){
    
    this->initKeybinds();
    
}

GameState::~GameState(){
    
}


//Functions
void GameState::updateInput(const float& dt){
    this->checkForQuit();
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))){
        this->player.move(dt, -1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))){
        this->player.move(dt, 1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))){
        this->player.move(dt, 0.f, -1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))){
        this->player.move(dt, 0.f, 1.f);
    }
}

void GameState::update(const float& dt){
    this->updateInput(dt);
    
    this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target){
    if(!target){
        target = this->window;
    }
    else{
       this->player.render(this->window);
    }
    
}

void GameState::endState(){
    std::cout << "ending game state" << "\n";
}




