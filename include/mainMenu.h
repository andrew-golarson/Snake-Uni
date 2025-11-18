#pragma once
#include<SFML/Graphics.hpp>

class MainMenu{
    public:
    const bool menuOpen() const; // czy menu otwarte
    void render();
    void update();
    void initMenuVariables(); // inicjalizacja zmiennych
    bool play = false; // czy rozpocząć grę
    MainMenu();
    ~MainMenu();

    private:
    sf::RenderWindow* menuWindow;

    sf::Texture backgroundTex;
    sf::Texture arrowsTex;
    sf::Texture escTex;
    sf::RectangleShape background;
    sf::RectangleShape arrows;
    sf::RectangleShape esc;
    sf::Text escDesc;
    sf::Text arrowsDesc;

    sf::Font font; // czcionka
    sf::Text playButton;
    sf::Text quitButton;
};