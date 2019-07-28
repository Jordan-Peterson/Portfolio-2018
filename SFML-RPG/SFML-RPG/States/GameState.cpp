//
//  GameState.cpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window):State(window){
    
}

GameState::~GameState(){
    
}


//Functions
void GameState::updateKeyBinds(const float& dt){
    this->checkForQuit();
}

void GameState::update(const float& dt){
    this->updateKeyBinds(dt);
    
    this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target){
    this->player.render(this->window);
}

void GameState::endState(){
    std::cout << "ending game state" << "\n";
}




