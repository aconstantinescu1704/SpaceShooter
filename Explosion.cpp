#include "Explosion.h"
using namespace sf;
Explosion::Explosion(Vector2f creationPosition, Texture& explosionTexture, float radius)
{
    lifeTime = 1;
    elapsedTime = 0;
    position = creationPosition;
    graphics.setTexture(explosionTexture);
    //   graphics.setTextureRect(sf::IntRect(182, 206, 182, 206));
    graphics.setOrigin(explosionTexture.getSize().x / 2.0, explosionTexture.getSize().y / 2.0);
    graphics.setPosition(position);
    graphics.setScale(2 * radius / explosionTexture.getSize().x, -2 * radius / explosionTexture.getSize().y);
}
void Explosion::update(float dt)
{
    elapsedTime += dt;
    if (elapsedTime > lifeTime)
        isAlive = false;
    float t = elapsedTime / lifeTime;
    float opacity = (-pow(1 - t, 12) + 1) * (1 - pow(t, 6));
    graphics.setColor(Color(255, 255, 255, 255 * opacity));
}
void Explosion::draw(RenderTarget& rt, RenderStates rs) const
{
    rt.draw(graphics, rs);
}