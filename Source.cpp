#include <iostream>
#include<SFML/graphics.hpp>
#include <cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include "MathUtils.h"

#include "Animation.h"
#include "Bullet.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Ship.h"
#include "Button.h"
using namespace sf;
using namespace std;

enum class GameStates
{
    InitialLoad,
    MainMenu,
    Playing,
    Unload,
    Paused,
    InGameMenu,
    GameOver
};

GameStates gameState = GameStates::InitialLoad;

int main(int nr_argumente, char** argumente)
{
    srand(time(nullptr));
    for (int i = 0; i < nr_argumente; ++i)
    {
        std::cout << argumente[i] << std::endl;
    }

    sf::RenderWindow myWindow(sf::VideoMode::getDesktopMode(), "Space Shooter", sf::Style::Fullscreen);
    //sf::RenderWindow myWindow(sf::VideoMode(1600, 900), "Space Shooter");
    float aspectRatio = (float)myWindow.getSize().x / myWindow.getSize().y;
    float worldWidth = 100;
    float worldHeight = worldWidth / aspectRatio;
    float cameraWidth = worldWidth;
    float cameraHeight = worldHeight;
    myWindow.setView(View(Vector2f(worldWidth / 2, worldHeight / 2), Vector2f(cameraWidth, -cameraHeight)));
    // Stary background
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("stars.jpg");
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setOrigin(backgroundTexture.getSize().x / 2.0f, backgroundTexture.getSize().y / 2.0f);
    background.setPosition(sf::Vector2f(worldWidth / 2, worldHeight / 2));
    float scaleFactorx = worldWidth / backgroundTexture.getSize().x;
    float scaleFactory = worldHeight / backgroundTexture.getSize().y;
    float backgroundFactor = max(scaleFactorx, scaleFactory);
    background.setScale(backgroundFactor, -backgroundFactor);

    //player ship 
    float radius = 5;
    sf::Texture shipTexture;
    shipTexture.loadFromFile("ship.png");
    Ship ship(sf::Vector2f(worldWidth / 2, radius), shipTexture);
    float right = 1;
    float left = -1;
    //bullet
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("bullet.png");
    sf::Vector2f bulletPosition = ship.position + sf::Vector2f(0, radius * 0.7);
    vector<Bullet*> bullets;
    sf::Texture bullet2Texture;
    bullet2Texture.loadFromFile("bullet2.png");
    //meteorite
    float mradius = 2;
    sf::Texture meteoriteTexture;
    meteoriteTexture.loadFromFile("meteorite.png");
    sf::Vector2f meteoritePosition = sf::Vector2f(worldWidth / 2, worldHeight - 2);
    vector<Meteorite*> meteorites;
    //explosion
    sf::Texture explosionTexture;
    explosionTexture.loadFromFile("explosion.png");
    vector<Explosion*>explosions;
    //game over
    float gameOverradius = 20;
    sf::Texture gameOverTexture;
    gameOverTexture.loadFromFile("game_over.png");
    sf::Sprite gameOver;
    gameOver.setTexture(gameOverTexture);
    gameOver.setOrigin(569, 554);
    gameOver.setPosition(worldWidth / 2, worldHeight / 2);
    gameOver.setScale(2 * radius / gameOverTexture.getSize().x, -2 * radius / gameOverTexture.getSize().y);
    //award
    sf::Texture starTexture;
    starTexture.loadFromFile("star.png");
    vector<Meteorite*>awards;
    bool AwardExistence;
    //explosion1
    sf::Texture animationSheetTexture;
    animationSheetTexture.loadFromFile("explosion1.png");
    // Animation anim(animationSheetTexture, 8*6, 8, 6, Vector2f(5.0f, 5.0f), 3,false);
    vector<Animation*>animations;
    // start screen
    sf::Texture startScreenTexture;
    startScreenTexture.loadFromFile("startscreen.png");
    sf::Sprite screenStart;
    screenStart.setTexture(startScreenTexture);
    screenStart.setOrigin(startScreenTexture.getSize().x/2.0f, startScreenTexture.getSize().y/2.0f);
    screenStart.setPosition(worldWidth / 2, worldHeight / 2);
    screenStart.setScale(cameraWidth / startScreenTexture.getSize().x,- cameraHeight / startScreenTexture.getSize().y);
    //button
    sf::Texture startTexture;
    startTexture.loadFromFile("start.png");
    Button button(startTexture, Vector2f(worldWidth / 2.0f, worldHeight / 2.0f),Vector2f(50,10),&myWindow);
    //float x = 100;
    //float y = 200;
    //float speed = 0.1;
    sf::Clock frameClock, time, bulletSpawnInterval, meteoritesInterval, awardInterval;
    float dt;
    gameState = GameStates::MainMenu;
    while (myWindow.isOpen())
    {
        //  anim.Play();
          //empty event queue
        sf::Event e;
        while (myWindow.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                myWindow.close();
            if (e.type == sf::Event::Resized)
                std::cout << "Resized\n";
            if (e.type == sf::Event::KeyPressed)
                if (e.key.code == sf::Keyboard::Escape)
                    myWindow.close();
        }
        dt = frameClock.getElapsedTime().asSeconds();
        frameClock.restart();
        //process input

        switch (gameState)
        {
        case GameStates::MainMenu:
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
                 gameState = GameStates::Playing;
            button.update(dt);
        }
        break;
        case GameStates::Playing:
        {
            if (Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                ship.update(dt, left);
            }
            if (Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                ship.update(dt, right);
            }
            if (Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (bulletSpawnInterval.getElapsedTime().asSeconds() > 2.0f / 10 )
                {
                    Bullet* pBullet = new Bullet(ship.position + sf::Vector2f(0, radius * 0.7), bulletTexture);
                    bullets.push_back(pBullet);
                    bulletSpawnInterval.restart();
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (bulletSpawnInterval.getElapsedTime().asSeconds() > 4.0f / 10  && AwardExistence == true)
                {
                    Bullet* pBullet = new Bullet(ship.position + sf::Vector2f(0, radius * 0.7), bullet2Texture);
                    bullets.push_back(pBullet);
                    bulletSpawnInterval.restart();
                }
            }
            if (meteoritesInterval.getElapsedTime().asSeconds() > 1.0f )
            {
                Meteorite* pMeteorite = new Meteorite(Vector2f(floatRandRange(0, worldWidth), worldHeight - 2), meteoriteTexture);
                meteorites.push_back(pMeteorite);
                meteoritesInterval.restart();
            }
            if (awardInterval.getElapsedTime().asSeconds() > 10.0f)
            {
                Meteorite* award = new Meteorite(Vector2f(floatRandRange(0, worldWidth / 1.0f), worldHeight - 2), starTexture);
                awards.push_back(award);
                awardInterval.restart();
            }
            //update game
           // anim.update(dt);
            for (auto bullet : bullets)
            {
                if (bullet->isAlive)
                    bullet->update(dt);
            }
            for (auto meteorite : meteorites)
            {
                if ((*meteorite).isAlive == true)
                    meteorite->update(dt);
            }
            for (auto award : awards)
            {
                if ((*award).isAlive == true)
                    award->update(dt);
            }
            for (auto explosion : explosions)
            {
                if (explosion->isAlive)
                    explosion->update(dt);
            }
            for (auto meteorite : meteorites)
            {
                if (!meteorite->isAlive)
                    continue;
                float distShip = magnitude(meteorite->position - ship.position);
                if (distShip < meteorite->radius + radius)
                {
                    gameState = GameStates::GameOver;
                    for (auto meteorite : meteorites)
                        meteorite->isAlive = false;
                    for (auto bullet : bullets)
                        bullet->isAlive = false;
                    for (auto award : awards)
                        award->isAlive = false;
                    break;
                }
                for (auto bullet : bullets)
                {
                    if (!bullet->isAlive)
                        continue;
                    float d = magnitude(meteorite->position - bullet->position);
                    if (d < meteorite->radius + bullet->radius)
                    {
                        Animation* animation = new Animation(animationSheetTexture, 8 * 6, 8, 6, Vector2f(meteorite->radius * 2, meteorite->radius * 2), Vector2f(meteorite->position.x, meteorite->position.y), Vector2f(0.5, 0.5), 1, false);
                        animation->Play();
                        animations.push_back(animation);
                        (*meteorite).isAlive = false;
                        bullet->isAlive = false;
                    }
                }
            }
            for (auto animation : animations)
            {

                animation->update(dt);
            }
            for (auto award : awards)
            {
                for (auto bullet : bullets)
                {
                    if (!bullet->isAlive)
                        continue;
                    float d = magnitude(award->position - bullet->position);
                    if (d < award->radius + bullet->radius)
                    {
                        Explosion* explosion = new Explosion(award->position, explosionTexture, award->radius);
                        explosions.push_back(explosion);
                        (*award).isAlive = false;
                        bullet->isAlive = false;
                        AwardExistence = true;
                    }
                }
            }
        }
        break;

        default:
            break;
        }

        //draw game
        myWindow.clear();
        switch (gameState)
        {
        case GameStates::Playing:
        {
            myWindow.draw(background);
            myWindow.draw(ship);
            for (auto bullet : bullets)
            {
                if (bullet->isAlive)
                    myWindow.draw(*bullet);
            }
            for (auto meteorite : meteorites)
            {
                if ((*meteorite).isAlive)
                    myWindow.draw(*meteorite);
            }
            for (auto award : awards)
            {
                if ((*award).isAlive)
                    myWindow.draw(*award);
            }
            for (auto animation : animations)
            {
                if (!animation->IsStopped())
                    myWindow.draw(*animation);

            }
        }
        break;
        case GameStates::GameOver:
        {
            myWindow.draw(gameOver);
        }
        break;
        case GameStates::MainMenu:
        {
            myWindow.draw(screenStart);
            myWindow.draw(button);
        }
        break;
        default:
            break;

        }

        myWindow.display();
    }
    return 0;
}