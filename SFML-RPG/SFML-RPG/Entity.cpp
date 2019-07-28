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
    this->move_speed = 100.f;
}

Entity::~Entity(){
    
}

//Functions

void Entity::move(const float& dt, const float x, const float y){
    this->shape.move(x* this->move_speed *dt, y * this->move_speed *dt);
}

void Entity::update(const float &dt){
    
    
}

void Entity::render(sf::RenderTarget* target){
    target->draw(this->shape);
}


