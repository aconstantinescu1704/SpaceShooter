#include "Meteorite.h";
#include "MathUtils.h";

using namespace sf;
Meteorite::Meteorite(Vector2f creationPosition, Texture& meteoriteTexture)
{
    radius = floatRandRange(0.5, 3);
    angularSpeed = floatRandRange(5, 180);
    position = creationPosition;
    velocity = Vector2f(floatRandRange(-3, 3), floatRandRange(-7, -3));
    graphics.setTexture(meteoriteTexture);
    //   graphics.setTextureRect(sf::IntRect(182, 206, 182, 206));
    graphics.setOrigin(meteoriteTexture.getSize().x / 2.0, meteoriteTexture.getSize().y / 2.0);
    graphics.setPosition(position);
    graphics.setRotation(floatRandRange(0, 360));
    float graphicsToCollisionRatio = 512 / 430.0f;
    graphics.setScale(graphicsToCollisionRatio * 2 * radius / meteoriteTexture.getSize().x, graphicsToCollisionRatio * -2 * radius / meteoriteTexture.getSize().y);
}
void Meteorite::update(float dt)
{
    position += velocity * dt;
    graphics.setPosition(position);
    graphics.rotate(angularSpeed * dt);
}
void Meteorite::draw(RenderTarget& rT, RenderStates rS) const
{
    rT.draw(graphics, rS);
}