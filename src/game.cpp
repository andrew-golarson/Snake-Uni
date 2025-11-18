#include "game.h"
#include "mainMenu.h"
#include "grid.h"
#include <random>
#include <string>

std::random_device rd; // do generacji losowej pozycji owoca
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(1, 19);

struct Player{
    public:
    float x = Grid::tileSize/2.f; // koordynaty początkowe węża
    float y = Grid::tileSize/2.f; 
    static int snakeSize;
};
struct Fruit{
    public:
    float x = Grid::tileSize/2.f + distr(gen)*Grid::tileSize; // koordynaty początkowe owoca
    float y = Grid::tileSize/2.f + distr(gen)*Grid::tileSize;
    static int fruitEaten;
};

Player pSnake[1600]; // segmenty snakea
int Player::snakeSize = 3; // długość węża
int Fruit::fruitEaten = 0;
Fruit apple; // owoc
Grid tilemap[Grid::gridSize][Grid::gridSize];
enum Direction{Down, Left, Right, Up} direction; // enum do przechowywania aktualnego kierunku ruchu

bool Game::gameOver = false; // definicje static
bool Game::goToMainMenu = false;
bool Game::paused = false;


void Game::initVariables(){
    //OKNO
    window = new sf::RenderWindow(sf::VideoMode({640,640}), "Snake", sf::Style::Close | sf::Style::Titlebar ); // okno
    window -> setFramerateLimit(60); // FPS
    window -> setKeyRepeatEnabled(false);

    // UI
    hungerBar.setSize({400.f, 20.f});
    hungerBar.setFillColor(sf::Color(204,102,0));
    hungerBar.setPosition({120.f, 618.f});
    hungerBarBehind.setSize({404.f, 24.f});
    hungerBarBehind.setFillColor(sf::Color::White);
    hungerBarBehind.setPosition({118.f, 616.f});
    hungerBarText.setPosition({282.f, 611.f});
    hungerBarText.setFillColor(sf::Color::Black);
    

    clock = new sf::Clock; // zegar (w tym programie: prędkość ruchu)
    
    //ENTITIES
    head.setOrigin({Grid::tileSize/2, Grid::tileSize/2}); // ustawienie punktu 'przyłożenia' według którego ustawia sie np. koordynaty, na środek spritea
    body.setOrigin({Grid::tileSize/2, Grid::tileSize/2});
    tail.setOrigin({Grid::tileSize/2, Grid::tileSize/2});
    turnBody.setOrigin({Grid::tileSize/2, Grid::tileSize/2});
    fruit.setOrigin({Grid::tileSize/2, Grid::tileSize/2});
    head.setRotation(sf::degrees(90)); // poczatkowa rotacja głowy w dół

    //PAUSE
    pauseScreen.setFillColor(sf::Color(0,0,0,150)); // czarny, przezroczysty
    pauseScreen.setSize({640.f, 640.f});
    pauseResumeButton.setPosition({235.f,150.f});
    pauseMainMenuButton.setPosition({235.f,250.f});
    pauseQuitButton.setPosition({235.f,350.f});

    //GAME OVER
    gameOverScreen.setFillColor(sf::Color(0,0,0,150)); // czarny, przezroczysty
    gameOverScreen.setSize(sf::Vector2f(640.f, 640.f));
    gameOverText.setPosition(sf::Vector2f(110.f, 14.f));
    gameOverMainMenuButton.setPosition(sf::Vector2f(210.f,230.f));
    gameOverQuitButton.setPosition(sf::Vector2f(210.f,330.f));
    
}

void snakeMove(){
    for(int i = Player::snakeSize; i > 0; i--){
        pSnake[i].x = pSnake[i-1].x; // pozycja następnego segmentu na miejsce poprzedniego
        pSnake[i].y = pSnake[i-1].y;
        if(i>3){
            if((pSnake[0].x == pSnake[i].x) && (pSnake[0].y == pSnake[i].y)){ // detekcja kolizji z segmentami węża
                Game::gameOver = true;
            }
        }
    }
    switch(direction){
        case Right:
        pSnake[0].x += Grid::tileSize; // ruch w prawo
        break;
        case Left:
        pSnake[0].x -= Grid::tileSize; // ruch w lewo
        break;
        case Down:
        pSnake[0].y += Grid::tileSize; // ruch w dół
        break;
        case Up:
        pSnake[0].y -= Grid::tileSize; // ruch w górę
        break;
    }
    if(pSnake[0].x > (Grid::tileSize*Grid::gridSize)-(Grid::tileSize/2)) pSnake[0].x = Grid::tileSize/2; // teleportacja na drugą stronę ekranu
    if(pSnake[0].x < Grid::tileSize/2) pSnake[0].x = (Grid::tileSize*Grid::gridSize)-(Grid::tileSize/2);
    if(pSnake[0].y > (Grid::tileSize*Grid::gridSize)-(Grid::tileSize/2)) pSnake[0].y = Grid::tileSize/2;
    if(pSnake[0].y < Grid::tileSize/2) pSnake[0].y = (Grid::tileSize*Grid::gridSize)-(Grid::tileSize/2);
}

const bool Game::Open() const{  // sprawdzanie czy okno jest dalej otwarte
    return window->isOpen();
}

void Game::update(){
    while(const std::optional event = window->pollEvent()){    // sprawdza czy jakieś eventy są od ostatniego odświeżenia    
            if(event -> is<sf::Event::Closed>()){   // zamknięcie okna
                window->close();
            }
            if(!paused && !gameOver){
                bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
                bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
                bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
                bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

                int pressCount = (int)up + (int)down + (int)left + (int)right;

                if (pressCount == 1) {
                    if (up && direction != Down) {
                        direction = Up;
                    } else if (down && direction != Up) {
                        direction = Down;
                    } else if (left && direction != Right) {
                        direction = Left;
                    } else if (right && direction != Left) {
                        direction = Right;
                    }
                }
            }else if(paused){ // eventy przycisków pauzy
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                if(pauseResumeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){ // sprawdzenie czy kursor zawiera sie w obszarze przycisku
                    pauseResumeButton.setFillColor(sf::Color::Red); // kolor czerwony przy najechaniu
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        paused = false; // odpauzowanie
                    }
                }else{
                    pauseResumeButton.setFillColor(sf::Color::White);
                }

                if(pauseQuitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){ 
                    pauseQuitButton.setFillColor(sf::Color::Red); // kolor czerwony przy najechaniu
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        window -> close();
                    }
                }else{
                    pauseQuitButton.setFillColor(sf::Color::White);
                }

                if(pauseMainMenuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){ 
                    pauseMainMenuButton.setFillColor(sf::Color::Red); // kolor czerwony przy najechaniu
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        goToMainMenu = true;
                        window -> close();
                    }
                }else{
                    pauseMainMenuButton.setFillColor(sf::Color::White);
                }
            }else{ // eventy przycisków game over
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                if(gameOverQuitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){ 
                    gameOverQuitButton.setFillColor(sf::Color::Red); // kolor czerwony przy najechaniu
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        window -> close();
                    }
                }else{
                    gameOverQuitButton.setFillColor(sf::Color::White);
                }

                if(gameOverMainMenuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){ 
                    gameOverMainMenuButton.setFillColor(sf::Color::Red); // kolor czerwony przy najechaniu
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        goToMainMenu = true;
                        window -> close();
                    }
                }else{
                    gameOverMainMenuButton.setFillColor(sf::Color::White);
                }
            }

            if(auto pressed = event -> getIf<sf::Event::KeyPressed>()){ // Esc = pauza
                if(pressed->scancode == sf::Keyboard::Scan::Escape && !gameOver){
                    paused = !paused;
                }
            }

        }
    
    if(!paused && !gameOver){
    if(clock -> getElapsedTime().asMilliseconds() > 50){ // w.w. prędkość ruchu: co 75 ms
        snakeMove();
        clock -> restart();
    }
    }

    if(pSnake[0].x ==apple.x && pSnake[0].y ==apple.y ){
        Player::snakeSize++;
        Fruit::fruitEaten++;
        hungerBar.setSize({400.f-(1.f*Fruit::fruitEaten), 20.f});
        hungerBarText.setString(std::to_string(400-Fruit::fruitEaten) + "/400");
        apple.x = Grid::tileSize/2.f + distr(gen)*Grid::tileSize; // losowanie koordynatów owoca
        apple.y = Grid::tileSize/2.f + distr(gen)*Grid::tileSize; 
    }
    fruit.setPosition(sf::Vector2f(apple.x, apple.y)); // nowa pozycja owoca
}

void Game::render(){
    window -> clear(sf::Color::Black); // czyszczenie ekranu z poprzedniej klatki
    for(int i = 0; i<Grid::gridSize; i++){ // rysowanie mapy
        for(int j = 0; j<Grid::gridSize; j++){
            window -> draw(tilemap[i][j].tile);
        }
    }
    window -> draw(fruit);

    const float width = Grid::tileSize * Grid::gridSize; // szerokość ekranu
    const float height = Grid::tileSize * Grid::gridSize; // wysokość ekranu
    auto wrappedDX = [width](float partA, float partB)->float{ 
        float diff = partA - partB; // różnica dystansu między jednym segmentem a drugim
        if(diff > (width/2.f)) diff -= width; // różnica za duża i dodatnia
        else if(diff < -(width/2.f)) diff += width; // różnica za duża i ujemna
        return diff; // zwrócenie najmniejszego możliwego dystansu
    };
    auto wrappedDY = [height](float partA, float partB)->float{
        float diff = partA - partB;
        if(diff > (height/2.f)) diff -= height;
        else if(diff < -(height/2.f)) diff += height;
        return diff;
    };

    for(int i = 0; i<Player::snakeSize; i++){
        if(i==0){
            float NextX{ wrappedDX(pSnake[i].x, pSnake[i+1].x) }; // x względem następnego segmentu
            float NextY{ wrappedDY(pSnake[i].y, pSnake[i+1].y) }; // y względem następnego segmentu
            if(NextX == 0 && NextY > 0){
                head.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y)); // pozycja głowy
                head.setRotation(sf::degrees(90));
                window -> draw(head);
            }else if(NextX == 0 && NextY < 0){
                head.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y));
                head.setRotation(sf::degrees(270));
                window -> draw(head);
            }else if(NextX > 0 && NextY == 0){
                head.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y));
                head.setRotation(sf::degrees(0));
                window -> draw(head);
            }else{
                head.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y));
                head.setRotation(sf::degrees(180));
                window -> draw(head);
            }
        }
        else if(i>0 && i<Player::snakeSize-1){
            float PrevX{ wrappedDX(pSnake[i].x, pSnake[i-1].x) }; // x względem poprzedniego segmentu
            float PrevY{ wrappedDY(pSnake[i].y, pSnake[i-1].y) }; // y względem poprzedniego segmentu
            float NextX{ wrappedDX(pSnake[i].x, pSnake[i+1].x) }; // x względem następnego segmentu
            float NextY{ wrappedDY(pSnake[i].y, pSnake[i+1].y) }; // y względem następnego segmentu
            if((NextY == 0 && PrevY>0 && NextX<0) || (PrevY==0 && NextY>0 && PrevX<0)){ // 1 ćwiartka układy
                turnBody.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y)); // pozycja danego segmentu ciała
                turnBody.setRotation(sf::degrees(270)); // obrót segmentu
                window -> draw(turnBody); 
            }else if((NextY == 0 && PrevY>0 && NextX>0) || (PrevY == 0 && NextY > 0 && PrevX>0)){ // 2 ćwiartka układu
                turnBody.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y)); 
                turnBody.setRotation(sf::degrees(180));
                window -> draw(turnBody); 
            }else if((PrevY==0 && NextY<0 && PrevX>0) || (PrevY<0 && NextX>0 && NextY==0) ){ // 3 ćwiartka układu
                turnBody.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y)); 
                turnBody.setRotation(sf::degrees(90));
                window -> draw(turnBody); 
            }else if((PrevY==0 && NextY<0 && PrevX<0) || (PrevY<0 && NextY==0 && NextX<0)){ // 4 ćwiartka układu
                turnBody.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y)); 
                turnBody.setRotation(sf::degrees(0));
                window -> draw(turnBody); 
            }else if(PrevY == 0 && NextY ==0){ 
                body.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y));
                body.setRotation(sf::degrees(0)); // obrót ciała poziomo
                window -> draw(body); 
            }else{
                body.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y));
                body.setRotation(sf::degrees(90)); // obrót ciała pionowo
                window -> draw(body);
            }
            
        }else{
            tail.setPosition(sf::Vector2f(pSnake[i].x, pSnake[i].y)); // pozycja ogona
            float PrevX{ wrappedDX(pSnake[i].x, pSnake[i-1].x) }; // x względem poprzedniego segmentu
            float PrevY{ wrappedDY(pSnake[i].y, pSnake[i-1].y) }; // y względem poprzedniego segmentu
            if(PrevY == 0 && PrevX <0){ 
                tail.setRotation(sf::degrees(0)); // prawo
            }else if(PrevY == 0 && PrevX > 0){
                tail.setRotation(sf::degrees(180)); // lewo
            }else if(PrevY>0){
                tail.setRotation(sf::degrees(270)); // dół
            }else{
                tail.setRotation(sf::degrees(90));  // góra
            }
            window -> draw(tail); // rysowanie ogona
        }
    }
    //UI
    window -> draw(hungerBarBehind);
    window -> draw(hungerBar);
    window -> draw(hungerBarText);

    if(paused){
        window -> draw(pauseScreen);
        window -> draw(pauseResumeButton);
        window -> draw(pauseMainMenuButton);
        window -> draw(pauseQuitButton);
    }
    if(gameOver){
        window -> draw(gameOverScreen);
        window -> draw(gameOverText);
        window -> draw(gameOverMainMenuButton);
        window -> draw(gameOverQuitButton);
    }

    window -> display(); // wyświetlenie wszystkiego
}

Game::Game():
    headTex("resources/head.png"), // inicjalizacja tekstur
    bodyTex("resources/body.png"),
    tailTex("resources/tail.png"),
    turnBodyTex("resources/turnBody.png"),
    fruitTex("resources/Apple.png"),
    head(headTex), //inicjalizacja spriteow teksturami
    body(bodyTex),
    tail(tailTex),
    turnBody(turnBodyTex),
    fruit(fruitTex),
    font("resources/pixel-operator-bold.ttf"), // czcionka przycisków
    pauseResumeButton(font, "Resume", 50), // inicjalizacja przycisków
    pauseQuitButton(font, "Quit", 50),
    pauseMainMenuButton(font, "Main Menu", 50),
    gameOverText(font, "Game Over", 100),
    gameOverMainMenuButton(font, "Main Menu", 50),
    gameOverQuitButton(font, "Quit", 50), 
    hungerBarText(font, "400/400", 23)
{
    initVariables();
    Grid::initTilemap(tilemap);
}

Game::~Game(){
    Player::snakeSize = 3;
    Fruit::fruitEaten = 0;
    direction = Down;
    pSnake[0].x = Grid::tileSize/2;
    pSnake[0].y = Grid::tileSize/2;
    delete window;
    delete clock;
}