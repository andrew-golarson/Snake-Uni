#include "mainMenu.h"

int MainMenu::skin = 1; // domyślny skin
bool MainMenu::quit = false;

void MainMenu::initMenuVariables(){
    menuWindow = new sf::RenderWindow(sf::VideoMode({640,640}), "Snake", sf::Style::Close | sf::Style::Titlebar); // okno
    menuWindow -> setFramerateLimit(60);

    // menu
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
    playButton.setPosition(sf::Vector2f(265.f,40.f)); // pozycja przycisku play
    quitButton.setPosition(sf::Vector2f(265.f,260.f)); // pozycja przycisku quit
    skinsButton.setPosition(sf::Vector2f(247.f,150.f)); // pozycja przycisku Skin selection

    // skin selection
    skinBox1.setPosition({80.f, 20.f});
    skinBox1.setTexture(&skinBoxTex1);
    skinBox2.setPosition({80.f, 230.f});
    skinBox2.setTexture(&skinBoxTex2);
    skinBox3.setPosition({80.f, 440.f});
    skinBox3.setTexture(&skinBoxTex3);
    skinBox4.setPosition({320.f, 20.f});
    skinBox4.setTexture(&skinBoxTex4);
    skinBox5.setPosition({320.f, 230.f});
    skinBox5.setTexture(&skinBoxTex5);
    skinBox6.setPosition({320.f, 440.f});
    skinBox6.setTexture(&skinBoxTex6);
    xButton.setPosition({580.f, 0.f});
}   

void MainMenu::render(){
    menuWindow -> clear(sf::Color::Black); //czyszczenie ekranu z poprzedniej klatki
    if(!skinSelectionScreen){ // menu główne
        menuWindow -> draw(background);
        menuWindow -> draw(playButton);
        menuWindow -> draw(quitButton);
        menuWindow -> draw(skinsButton);
        menuWindow -> draw(arrows);
        menuWindow -> draw(esc);
        menuWindow -> draw(arrowsDesc);
        menuWindow -> draw(escDesc);
    }else{ // wybór skinów
        menuWindow -> draw(skinBox1); // poszczególne obrazki skinów
        menuWindow -> draw(skinBox2);
        menuWindow -> draw(skinBox3);
        menuWindow -> draw(skinBox4);
        menuWindow -> draw(skinBox5);
        menuWindow -> draw(skinBox6);
        menuWindow -> draw(xButton); // przycisk X
    }
    menuWindow -> display(); // wyświetlenie wszystkiego an ekran
}

void MainMenu::update(){
    while(const std::optional event = menuWindow->pollEvent()){
        if(event ->is<sf::Event::Closed>()){
            MainMenu::quit = true;
            menuWindow -> close();
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(*menuWindow);
        if(!skinSelectionScreen){
            if(playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){ // sprawdzenie czy kursor zawiera sie w obszarze przycisku
                playButton.setFillColor(sf::Color::Red); // kolor czerwony przy najechaniu
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){ // czy kliknięto lewy przycisk myszy
                    play = true; // rozpoczęcie pętli gry
                    menuWindow -> close(); // zamknięcie okna
                }
            } else {
                playButton.setFillColor(sf::Color::White); // kolor biały jeśli kursor nie jest w obszarzee przycisku
            }
            if(quitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){ 
                quitButton.setFillColor(sf::Color::Red);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    MainMenu::quit = true;
                    menuWindow -> close();
                }
            } else {
                quitButton.setFillColor(sf::Color::White);
            }
            if(skinsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){ 
                skinsButton.setFillColor(sf::Color::Red);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    skinSelectionScreen = true;
                }
            } else {
                skinsButton.setFillColor(sf::Color::White);
            }
        }else{ // eventy menu wyboru skina
            if(skinBox1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){ 
                skinBox1.setOutlineColor(sf::Color::Red); // czerwona obramówka przy najechaniu
                skinBox1.setOutlineThickness(3.f);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    skin = 1; // numer skina do poźniejszego załadowania odpowednich tekstur
                }
            }else if(skin == 1){
                skinBox1.setOutlineThickness(3.f); // jeśli wybrany to wyświetl białą obramówkee
                skinBox1.setOutlineColor(sf::Color::White);
            }else{
                skinBox1.setOutlineThickness(0.f); // jeśli niewybrany i nie ma kursora w obszarze
            }

            if(skinBox2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){ 
                skinBox2.setOutlineColor(sf::Color::Red);
                skinBox2.setOutlineThickness(3.f);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    skin = 2;
                }
            }else if(skin == 2){
                skinBox2.setOutlineThickness(3.f);
                skinBox2.setOutlineColor(sf::Color::White);
            }else{
                skinBox2.setOutlineThickness(0.f);
            }

            if(skinBox3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                skinBox3.setOutlineColor(sf::Color::Red);
                skinBox3.setOutlineThickness(3.f); 
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    skin = 3;
                }
            }else if(skin == 3){
                skinBox3.setOutlineThickness(3.f);
                skinBox3.setOutlineColor(sf::Color::White);
            }else{
                skinBox3.setOutlineThickness(0.f);
            }

            if(skinBox4.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                skinBox4.setOutlineColor(sf::Color::Red);
                skinBox4.setOutlineThickness(3.f); 
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    skin = 4;
                }
            }else if(skin == 4){
                skinBox4.setOutlineThickness(3.f);
                skinBox4.setOutlineColor(sf::Color::White);
            }else{
                skinBox4.setOutlineThickness(0.f);
            }

            if(skinBox5.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                skinBox5.setOutlineColor(sf::Color::Red);
                skinBox5.setOutlineThickness(3.f); 
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    skin = 5;
                }
            }else if(skin == 5){
                skinBox5.setOutlineThickness(3.f);
                skinBox5.setOutlineColor(sf::Color::White);
            }else{
                skinBox5.setOutlineThickness(0.f);
            }

            if(skinBox6.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                skinBox6.setOutlineColor(sf::Color::Red);
                skinBox6.setOutlineThickness(3.f); 
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    skin = 6;
                }
            }else if(skin == 6){
                skinBox6.setOutlineThickness(3.f);
                skinBox6.setOutlineColor(sf::Color::White);
            }else{
                skinBox6.setOutlineThickness(0.f);
            }

            if(xButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){ 
                xButton.setFillColor(sf::Color::Red);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    skinSelectionScreen = false; // wyjście do menu glównego
                }
            }else{
                xButton.setFillColor(sf::Color::White);
            }
        }
    }
}

const bool MainMenu::menuOpen() const{  // sprawdzanie czy okno jest dalej otwarte
    return menuWindow->isOpen();
}

MainMenu::MainMenu():
    font("resources/pixel-operator-bold.ttf"), // czcionka przycisków
    playButton(font, "Play", 70), // konstruktory przycisków
    quitButton(font, "Quit", 70),
    skinsButton(font, "Skins", 70),
    xButton(font, "x", 70),
    backgroundTex("resources/background.jpg"), // inicjlizacja obrazków
    arrowsTex("resources/ArrowKeys.png"),
    escTex("resources/EscKey.png"),
    skinBoxTex1("resources/skin.png"),
    skinBoxTex2("resources/skin1.png"),
    skinBoxTex3("resources/skin2.png"),
    skinBoxTex4("resources/skin4.png"),
    skinBoxTex5("resources/skin5.png"),
    skinBoxTex6("resources/skin6.png"),
    arrowsDesc(font, "-  Moving", 40), // konstruktory tekstów
    escDesc(font, "-  Pause", 40),
    skinBox1({180.f, 180.f}), // konstruktory prostokątów
    skinBox2({180.f, 180.f}),
    skinBox3({180.f, 180.f}),
    skinBox4({180.f, 180.f}),
    skinBox5({180.f, 180.f}),
    skinBox6({180.f, 180.f})
{
    initMenuVariables();
}

MainMenu::~MainMenu(){
    delete menuWindow;
}

