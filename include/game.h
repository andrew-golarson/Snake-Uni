#pragma once
#include<SFML/Graphics.hpp>
#include <string>

class Game{
    public:
    void update(); // sprawdzanie czy zaszły jakieś zmiany eventów np. naciśniecie klawisza
    void render(); // wyświetlanie rzeczy w oknie
    void initVariables();
    const bool Open() const; // sprawdzenie czy okno jest otwarte
    static bool quit; // czy wyjść z aplikacji
    static bool gameOver; // czy koniec gry
    static bool paused; // czy spauzować grę
    static std::string getHeadSkinPath(int skin); // inicjalizacja tekstur według wybranego skina
    static std::string getBodySkinPath(int skin);
    static std::string getTailSkinPath(int skin);
    static std::string getTurnBodySkinPath(int skin);
     Game();
    ~Game();
    
    private:

    sf::Clock* clock;
    sf::RenderWindow* window; 
    sf::Font font;

    sf::RectangleShape hungerBar;
    sf::RectangleShape hungerBarBehind;
    sf::Text hungerBarText;

    sf::Texture headTex;
    sf::Texture bodyTex;
    sf::Texture tailTex;
    sf::Texture turnBodyTex;
    sf::Texture fruitTex;

    sf::Sprite head;
    sf::Sprite body;
    sf::Sprite tail;
    sf::Sprite turnBody;
    sf::Sprite fruit;

    sf::RectangleShape pauseScreen;
    sf::Text pauseResumeButton;
    sf::Text pauseMainMenuButton; 
    sf::Text pauseQuitButton;


    sf::RectangleShape gameOverScreen;
    sf::Text gameOverText;
    sf::Text gameOverMainMenuButton; 
    sf::Text gameOverQuitButton;
};