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
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    
    //Resources
    std::vector<sf::Texture*> textures;
    
    bool quit;
    
    //Functions
    virtual void initKeybinds() = 0;
    
public:
    State(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys);
    virtual ~State();
    
    const bool& getQuit();
    
    virtual void checkForQuit();
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) =0;
    virtual void render(sf::RenderTarget* target = nullptr) =0;
    virtual void endState() = 0;
};

#endif /* State_hpp */
