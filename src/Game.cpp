#include "hpp/Game.hpp"
#include <string>
#include <sstream>
#include <imgui-SFML.h>
#include <imgui.h>

Game::Game() : grd() {
    font.loadFromFile("ressources/Daydream.ttf");
    text.setFont(font);
    text.setString("Tetris++");
    text.setCharacterSize(24); 
    text.setFillColor(sf::Color::White);
    
    scoreTxt.setFont(font);
    scoreTxt.setString("Score :");
    scoreTxt.setCharacterSize(20); 
    scoreTxt.setFillColor(sf::Color::White);

    nextPiece.setFont(font);
    nextPiece.setString("Next piece :");
    nextPiece.setCharacterSize(17); 
    nextPiece.setFillColor(sf::Color::White);


    looseText.setFont(font);
    looseText.setString("Vous avez perdu !!");
    looseText.setCharacterSize(24); 
    looseText.setFillColor(sf::Color::White);


    blockTexture.loadFromFile("ressources/texture2.png");
    blockTexture.setSmooth(true);  // Optionnel : pour une texture lissée
    blockTexture.setRepeated(false);
}

void Game::window() {
    bool fast = false;
    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(600, 740), "Tetris++");
     window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    // Création d'une horloge pour mesurer le temps
    sf::Clock clock;

    // Définir le délai de descente initial (350 millisecondes)
    sf::Time descentDelay = sf::milliseconds(350);

    while (window.isOpen()) {
        if(this->grd.getLoose()){
            this->loose(clock,descentDelay,fast,window);
        }else{
            //this->loose(clock,descentDelay,fast,window);
            this->game(clock,descentDelay,fast,window);
        }
        
    }
}

void Game::game(sf::Clock &clock, sf::Time &descentDelay,bool &fast,sf::RenderWindow &window){
    // Mesurer le temps écoulé depuis la dernière descente
        sf::Time elapsedTime = clock.restart();

        // Mettre à jour le délai de descente en fonction du temps écoulé
        descentDelay -= elapsedTime;

        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed){
                window.close();
            }else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Left) {
                    this->grd.moveLeft();
                    //std::cout<<"left"<<std::endl;
                } else if (event.key.code == sf::Keyboard::Right) {
                    this->grd.moveRight();
                    //std::cout<<"right"<<std::endl;
                } else if (event.key.code == sf::Keyboard::Down) {
                    fast=true;
                    std::cout<<"down"<<std::endl;
                }else if (event.key.code == sf::Keyboard::Up) {
                    fast=false;
                    std::cout<<"down"<<std::endl;
                }else if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
                    this->grd.turnActual();
                    std::cout<<"rotate"<<std::endl;
                }else if (event.key.code == sf::Keyboard::Enter) {
                    this->grd.checkGrid(true);
                    std::cout<<"insant"<<std::endl;
                }
                // Ajoutez des conditions pour d'autres touches
            }
        }

        // Vérifier si le délai de descente est écoulé
        if (descentDelay <= sf::Time::Zero) {
            this->grd.checkGrid();
            //std::this_thread::sleep_for(std::chrono::seconds(500));
            // Descendre la case d'un cran
            // ...

            // Réinitialiser le délai de descente
            if(fast){
                descentDelay = sf::milliseconds(100);
            }else{
                descentDelay = sf::milliseconds(200);
            }
            
        }

        // Effacer la fenêtre avec une couleur de fond
        ImGui::SFML::Update(window, clock.restart());

        ImGui::Begin("Hello, world!");
        //ImGui::Button("Rayane");
        std::stringstream ss;
        ss << "X " << this->grd.getAcutal().getX() << " Y "<<this->grd.getAcutal().getY();
        ImGui::Text(ss.str().c_str());
        
        ImGui::End();

        
        window.clear(sf::Color::Black);
        


        // Dessiner ici vos éléments graphiques
        sf::RectangleShape cell(sf::Vector2f(35, 35));
        cell.setFillColor(sf::Color::White);


        this->setCaseColor(cell,window);
        this->drawNextPiece(cell,window);
        this->drawScore(window);

        ImGui::SFML::Render(window);

        // Afficher la fenêtre
        window.display();
}



void Game::loose(sf::Clock &clock, sf::Time &descentDelay,bool &fast,sf::RenderWindow &window){
    // Mesurer le temps écoulé depuis la dernière descente
        sf::Time elapsedTime = clock.restart();

        // Mettre à jour le délai de descente en fonction du temps écoulé
        descentDelay -= elapsedTime;

        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::R) {
                    this->grd.restart();
                    //std::cout<<"left"<<std::endl;
                }
                // Ajoutez des conditions pour d'autres touches
            }
        }

        // Vérifier si le délai de descente est écoulé
        if (descentDelay <= sf::Time::Zero) {
            this->grd.checkGrid();
            //std::this_thread::sleep_for(std::chrono::seconds(500));
            // Descendre la case d'un cran
            // ...

            // Réinitialiser le délai de descente
            if(fast){
                descentDelay = sf::milliseconds(100);
            }else{
                descentDelay = sf::milliseconds(200);
            }
            
        }

        // Effacer la fenêtre avec une couleur de fond
        window.clear(sf::Color::Black);

        // Dessiner ici vos éléments graphiques
        
        //this->drawScore(window);
        this->drawLoose(window);

        // Afficher la fenêtre
        window.display();
}


void Game::setCaseColor(sf::RectangleShape& cell, sf::RenderWindow& window){
    for (int i = 0; i < GRID_HEIGHT; i++) {
            for (int j = 0; j < GRID_WIDTH; j++) {

                switch (abs(this->grd.getGrid()[i][j]))
                {
                case 1:
                    cell.setFillColor(sf::Color(220,20,60));
                    
                    break;
                case 2:
                    cell.setFillColor(sf::Color(0,0,139));
                    break;
                case 3:
                    cell.setFillColor(sf::Color(127,255,0));    
                    break;
                case 4:
                    cell.setFillColor(sf::Color(255,255,0));    
                    break;
                case 5:
                    cell.setFillColor(sf::Color(138,43,226));    
                    break;
                case 6:
                    cell.setFillColor(sf::Color(135,206,250));    
                    break;
                case 7:
                    //sf::Color orange1(255, 165, 0);
                    cell.setFillColor(sf::Color(255, 165, 0));    
                    break;    
                case 8:
                    //sf::Color orange1(255, 165, 0);
                    cell.setFillColor(sf::Color(200, 120, 47));    
                    break;
                default:
                    cell.setFillColor(sf::Color::White);
                    break;
                }

                // Positionner le rectangle de la case actuelle
                cell.setPosition(j * 37, i * 37);

                if(this->grd.getGrid()[i][j]!=0){
                    cell.setTexture(&blockTexture);
                }else{
                    cell.setTexture(NULL);
                }           

                // Dessiner le rectangle de la case
                window.draw(cell);
            }
        }
}


void Game::drawNextPiece(sf::RectangleShape& cell, sf::RenderWindow& window){
    for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                switch (this->grd.getNext().getMatrix()[i][j])
                {
                case 1:
                    cell.setFillColor(sf::Color(220,20,60));
                    break;
                case 2:
                    cell.setFillColor(sf::Color(0,0,139));
                    break;
                case 3:
                    cell.setFillColor(sf::Color(127,255,0));    
                    break;
                case 4:
                    cell.setFillColor(sf::Color(255,255,0));    
                    break;
                case 5:
                    cell.setFillColor(sf::Color(138,43,226));    
                    break;
                case 6:
                    cell.setFillColor(sf::Color(135,206,250));    
                    break;
                case 7:
                    //sf::Color orange1(255, 165, 0);
                    cell.setFillColor(sf::Color(255, 165, 0));    
                    break;    
                case 8:
                    //sf::Color orange1(255, 165, 0);
                    cell.setFillColor(sf::Color(200, 120, 47));    
                    break;
                default:
                    cell.setFillColor(sf::Color::Black);
                    break;
                }

                
                

                // Positionner le rectangle de la case actuelle
                cell.setPosition(430+j * 37, 550+i * 37);

                cell.setTexture(&blockTexture);
                // Dessiner le rectangle de la case
                window.draw(cell);
            }
        }
}

void Game::drawScore(sf::RenderWindow& window){
    text.setPosition(380,10);
    scoreTxt.setPosition(380,80);
    nextPiece.setPosition(380,500);
    std::string scoreStr = "score: "+std::to_string(this->grd.getScore());
    scoreTxt.setString(scoreStr);
    window.draw(text);
    window.draw(scoreTxt);
    window.draw(nextPiece);
}

void Game::drawLoose(sf::RenderWindow& window){

    sf::Text rText;
    rText.setFont(font);
    rText.setString("appuyez sur R pour recommencer");
    rText.setCharacterSize(18); 
    rText.setFillColor(sf::Color::White);

    std::string scoreStr = "score: "+std::to_string(this->grd.getScore());
    scoreTxt.setString(scoreStr);

    sf::Vector2u windowSize = window.getSize();

    // Calculer les positions pour centrer les textes
    float textX = (windowSize.x - text.getLocalBounds().width) / 2.0f;
    float scoreTxtX = (windowSize.x - scoreTxt.getLocalBounds().width) / 2.0f;
    float looseTextX = (windowSize.x - looseText.getLocalBounds().width) / 2.0f;
    float rTextX = (windowSize.x - rText.getLocalBounds().width) / 2.0f;

    // Définir les positions des textes centrés
    text.setPosition(textX, 10);
    scoreTxt.setPosition(scoreTxtX, 80);
    looseText.setPosition(looseTextX, 200);
    rText.setPosition(rTextX, 300);
    

    //nextPiece.setPosition(380,500);
    
    window.draw(text);
    window.draw(scoreTxt);
    window.draw(looseText);
    window.draw(rText);
    //window.draw(nextPiece);
}