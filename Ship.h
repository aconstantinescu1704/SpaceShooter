#pragma once
#include<SFML/graphics.hpp>
class Ship : public sf::Drawable
{
public:
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Sprite graphics;
    bool isAlive = true;
public:
    Ship(sf::Vector2f creationPosition, sf::Texture& shipTexture);
    void update(float dt, float direction);
    void draw(sf::RenderTarget& rT, sf::RenderStates rS) const;
};