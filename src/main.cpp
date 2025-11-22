#include "game.h"
#include "mainMenu.h"
int main(){
    while(true){
        if(MainMenu::quit || Game::quit){// jesli nacisnięty przycisk quit
            return 0;
        }
        MainMenu menu;
        while(menu.menuOpen()){
            menu.render();
            menu.update();
        }
        if(menu.play){
            Game::gameOver = false;
            Game::paused = false;
            Game snakeGame;
            while(snakeGame.Open()){
                    snakeGame.render();
                    snakeGame.update();
            }
        }
    }
}   