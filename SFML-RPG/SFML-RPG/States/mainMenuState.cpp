//
//  mainMenuState.cpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#include "mainMenuState.hpp"


void MainMenuState::initKeybinds(){
    
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

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys) : State(window, supportedKeys){
    
    this->initKeybinds();
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::White);
    
}

MainMenuState::~MainMenuState(){
    
}

//Functions
void MainMenuState::updateInput(const float& dt){
    this->checkForQuit();
    
}

void MainMenuState::update(const float& dt){
    this->updateInput(dt);
    
}

void MainMenuState::render(sf::RenderTarget* target){
    if(!target){
        target = this->window;
    }
    
    target->draw(this->background);
    
}

void MainMenuState::endState(){
    std::cout << "ending game state" << "\n";
}




