#pragma once
#include<SFML/graphics.hpp>
class Meteorite : public sf::Drawable
{
public:
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Sprite graphics;
    float angularSpeed;
    bool isAlive = true;
public:
    Meteorite(sf::Vector2f creationPosition, sf::Texture& meteoriteTexture);
    void update(float dt);
    void draw(sf::RenderTarget& rT, sf::RenderStates rS) const;
};
