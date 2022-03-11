#include "Ship.h"
using namespace sf;
Ship::Ship(Vector2f creationPosition, Texture& shipTexture)
{
    radius = 5;
    position = creationPosition;
    velocity = Vector2f(creationPosition.x / 3.0f, 0);
    graphics.setTexture(shipTexture);
    graphics.setOrigin(shipTexture.getSize().x / 2.0, shipTexture.getSize().y / 2.0);
    graphics.setPosition(position);
    graphics.setScale(2 * radius / shipTexture.getSize().x, -2 * radius / shipTexture.getSize().y);
}
void Ship::update(float dt, float direction)
{
    position += velocity * dt * direction;
    graphics.setPosition(position);
}
void Ship::draw(RenderTarget& rT, RenderStates rS) const
{
    rT.draw(graphics, rS);
}