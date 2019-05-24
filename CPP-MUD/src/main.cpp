#include "../include/game.h"

using namespace std;

int main(){
    srand(time(NULL));

    Game game;
    game.initialize();

    while(game.getPlaying()){
        game.mainMenu();
    }

    return 0;
}
