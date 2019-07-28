//  Game.cpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#include "Game.hpp"

//Init Functions
void Game::initWindow()
{
    //Creates SFML window using options from window.ini file
    std::ifstream ifs("Config/window.ini");
    
    std::string title = "None";
    sf::VideoMode window_bounds(800,600);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    
    if(ifs.is_open()){
        std::getline(ifs,title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    
    ifs.close();
    
    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);

}

void Game::initStates(){
    this->states.push(new GameState(this->window));
}

//Static Functions

//Constructor-Destructor
Game::Game()
{
    this->initWindow();
    this->initStates();
}

Game::~Game()
{
    delete this->window;
    while(!this->states.empty()){
        delete this->states.top();
        this->states.pop();
    }
}


//Functions
void Game::updateSFMLEvent(){
    while (this->window->pollEvent(this->sfEvent))
    {
        // Close window: exit
        if (this->sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
        
        // Escape pressed: exit
        if (this->sfEvent.type == sf::Event::KeyPressed && this->sfEvent.key.code == sf::Keyboard::Escape) {
            this->window->close();
        }
    }
    
    // Clear screen
    this->window->clear();
}

void Game::update(){
    this->updateSFMLEvent();
    
    if(!this->states.empty()){
        this->states.top()->update(this->dt);
        
        if(this->states.top()->getQuit()){
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
}

void Game::updateDT(){
    //sets delta time to the sf clock time
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::render(){
    this->window->clear();
    
    if(!this->states.empty()){
        this->states.top()->render(this->window);
    }
    //Render items
    this->window->display();
}

void Game::run(){
    // Start the game loop
    while (this->window->isOpen()){
        this->updateDT();
        this->update();
        this->render();
    }
}
