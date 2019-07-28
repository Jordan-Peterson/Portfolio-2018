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
    
    this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
    this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
    this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
    this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
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




