//
//  State.hpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include "Entity.hpp"

class State{
private:
protected:
    sf::RenderWindow* window;
    std::vector<sf::Texture*> textures;
    bool quit;
    
public:
    State(sf::RenderWindow* window);
    virtual ~State();
    
    const bool& getQuit();
    
    virtual void checkForQuit();
    virtual void updateKeyBinds(const float& dt) = 0;
    virtual void update(const float& dt) =0;
    virtual void render(sf::RenderTarget* target = nullptr) =0;
    virtual void endState() = 0;
};

#endif /* State_hpp */
