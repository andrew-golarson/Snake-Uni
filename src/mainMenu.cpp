#include "mainMenu.h"

void MainMenu::initMenuVariables(){
    menuWindow = new sf::RenderWindow(sf::VideoMode({640,640}), "Snake", sf::Style::Close | sf::Style::Titlebar); // okno
    menuWindow -> setFramerateLimit(60); // FPS

    background.setTexture(&backgroundTex);
    background.setSize({640.f,640.f});
    background.setPosition({0.f, 0.f});
    arrows.setTexture(&arrowsTex);
    arrows.setSize({170.f, 170.f});
    arrows.setPosition({50.f, 340.f});
    esc.setTexture(&escTex);
    esc.setSize({120.f, 120.f});
    esc.setPosition({105.f, 490.f});
    arrowsDesc.setPosition({240.f, 390.f});
    escDesc.setPosition({240.f, 517.f});

    playButton.setPosition(sf::Vector2f(265.f,100.f)); // pozycja przycisku play
    quitButton.setPosition(sf::Vector2f(265.f,230.f)); // pozycja przycisku quit
}

void MainMenu::render(){
    menuWindow -> clear(sf::Color::Black); //czyszczenie ekranu z poprzedniej klatki
    menuWindow -> draw(background);
    menuWindow -> draw(playButton);
    menuWindow -> draw(quitButton);
    menuWindow -> draw(arrows);
    menuWindow -> draw(esc);
    menuWindow -> draw(arrowsDesc);
    menuWindow -> draw(escDesc);
    menuWindow -> display(); // wyświetlenie wszystkiego an ekran
}

void MainMenu::update(){
    while(const std::optional event = menuWindow->pollEvent()){
        if(event ->is<sf::Event::Closed>()){
            menuWindow -> close();
        }
            sf::Vector2i mousePos = sf::Mouse::getPosition(*menuWindow);
            if(playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){ // sprawdzenie czy kursor zawiera sie w obszarze przycisku
                playButton.setFillColor(sf::Color::Red); // kolor czerwony przy najechaniu
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    play = true; // rozpoczęciee pętli gry
                    menuWindow -> close();
                }
            } else {
                playButton.setFillColor(sf::Color::White);
            }
            if(quitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){ 
                quitButton.setFillColor(sf::Color::Red); // kolor czerwony przy najechaniu
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    menuWindow -> close();
                }
            } else {
                quitButton.setFillColor(sf::Color::White);
            }
    }
}

const bool MainMenu::menuOpen() const{  // sprawdzanie czy okno jest dalej otwarte
    return menuWindow->isOpen();
}

MainMenu::MainMenu():
    font("resources/pixel-operator-bold.ttf"), // czcionka przycisków
    playButton(font, "Play", 70), // konstruktor przycisku play
    quitButton(font, "Quit", 70),
    backgroundTex("resources/background.jpg"),
    arrowsTex("resources/ArrowKeys.png"),
    escTex("resources/EscKey.png"),
    arrowsDesc(font, "-  Moving", 45),
    escDesc(font, "-  Pause", 45)
{
    initMenuVariables();
}

MainMenu::~MainMenu(){
    delete menuWindow;
}

