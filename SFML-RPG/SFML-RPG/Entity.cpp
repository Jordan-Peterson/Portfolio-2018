//
//  Entity.cpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity(){
    this->shape.setSize(sf::Vector2f(50.f,50.f));
    this->shape.setFillColor(sf::Color::White);
    this->move_speed = 1000.f;
}

Entity::~Entity(){
    
}

//Functions

void Entity::move(const float& dt, const float x, const float y){
    this->shape.move(x* this->move_speed *dt, y * this->move_speed *dt);
}

void Entity::update(const float &dt){
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->move(dt, -1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->move(dt, 1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->move(dt, 0.f, -1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->move(dt, 0.f, 1.f);
    }
}

void Entity::render(sf::RenderTarget* target){
    target->draw(this->shape);
}


