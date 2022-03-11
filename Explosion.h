#pragma once
#include<SFML/graphics.hpp>
class Explosion : public sf::Drawable
{
public:
    float radius;
    sf::Vector2f position;
    sf::Sprite graphics;
    float lifeTime;
    float elapsedTime;
    bool isAlive = true;
public:
    Explosion(sf::Vector2f creationPosition, sf::Texture& explosionTexture, float radius);
    void update(float dt);
    void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};