#include "game.h"
#include "mainMenu.h"
int main(){
    menu:
        if(Game::goToMainMenu){
            Game::gameOver = false;
            Game::paused = false;
            Game::goToMainMenu = false;
        }
        MainMenu menu;
        while(menu.menuOpen()){
            menu.render();
            menu.update();
        }
        if(menu.play){
            Game snakeGame;
            while(snakeGame.Open()){
                    snakeGame.render();
                    snakeGame.update();
            }
        }
    if(Game::goToMainMenu){
        menu.play = false;
        goto menu;
    }
}   
