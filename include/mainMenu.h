#pragma once
#include<SFML/Graphics.hpp>

class MainMenu{
    public:
    const bool menuOpen() const; // czy menu otwarte
    void render();
    void update();
    void initMenuVariables(); // inicjalizacja zmiennych
    bool play = false; // czy rozpocząć grę
    static bool quit;
    static int skin;
    MainMenu();
    ~MainMenu();

    private:
    bool skinSelectionScreen = false;

    sf::RenderWindow* menuWindow;

    sf::RectangleShape skinBox1;
    sf::RectangleShape skinBox2;
    sf::RectangleShape skinBox3;
    sf::RectangleShape skinBox4;
    sf::RectangleShape skinBox5;
    sf::RectangleShape skinBox6;
    sf::Texture skinBoxTex1;
    sf::Texture skinBoxTex2;
    sf::Texture skinBoxTex3;
    sf::Texture skinBoxTex4;
    sf::Texture skinBoxTex5;
    sf::Texture skinBoxTex6;
    sf::Text xButton; // przycisk X w wyborze skina

    sf::Texture backgroundTex; // obraz w tle
    sf::Texture arrowsTex; // obrazek strzałek
    sf::Texture escTex; // obrazek escape
    sf::RectangleShape background;
    sf::RectangleShape arrows;
    sf::RectangleShape esc;
    sf::Text escDesc; // opis escape
    sf::Text arrowsDesc; // opis strzałek

    sf::Font font; // czcionka
    sf::Text playButton;
    sf::Text quitButton;
    sf::Text skinsButton;
};