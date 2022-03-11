#pragma once
#include<SFML/graphics.hpp>

class Bullet : public sf::Drawable
{
public:
    float radius;
    sf::Vector2f position;
    sf:: Vector2f velocity;
    sf::Sprite graphics;
    //Animation* g;
    bool isAlive;
public:
    Bullet(sf::Vector2f creationPosition, sf::Texture& bulletTexture);
    void update(float dt);
    void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
    ~Bullet();
};