//
//  Entity.hpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <vector>
#include <stdio.h>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "ResourcePath.hpp"
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

class Entity
{
private:
    
protected:
    sf::RectangleShape shape;
    float move_speed;
    
public:
    Entity();
    virtual ~Entity();
    
    //Functions
    virtual void move(const float& dt, const float x, const float y);

    
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target = nullptr);
    
};
#endif /* Entity_hpp */
