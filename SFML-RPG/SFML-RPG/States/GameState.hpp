//
//  GameState.hpp
//  SFML-RPG
//
//  Created by Jordan Peterson on 7/27/19.
//  Copyright © 2019 Jordan Peterson. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp
#include "State.hpp"

class GameState:
    public State{
    private:
        Entity player;
        
    public:
        GameState(sf::RenderWindow* window);
        virtual ~GameState();
        
        //Functions
        void updateKeyBinds(const float& dt);
        void update(const float& dt);
        void render(sf::RenderTarget* tartget = nullptr);
        void endState();
        
};

#endif /* GameState_hpp */
