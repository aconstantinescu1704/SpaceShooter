#include "Bullet.h";
using namespace sf;

Bullet::Bullet(Vector2f creationPosition, Texture& bulletTexture)
{
    radius = 0.5;
    position = creationPosition;
    velocity = Vector2f(0, 20);
    Vector2f frameSize(182, 206);
    graphics.setTexture(bulletTexture);
    graphics.setTextureRect(sf::IntRect(182, 206, frameSize.x, frameSize.y));
    graphics.setOrigin(91, 103);
    graphics.setPosition(position);
    float graphicsToCollisionRatio = 206 / 108.0f;
    graphics.setScale(graphicsToCollisionRatio * 2 * radius / frameSize.x, graphicsToCollisionRatio * -2 * radius / frameSize.y);
    isAlive = true;
    //create animation: g = new Animation(.....);
}
void Bullet::update(float dt)
{
    position += velocity * dt;
    graphics.setPosition(position);
    // update g
}
void Bullet::draw(RenderTarget& rt, RenderStates rs) const
{
    rt.draw(graphics, rs);
    // draw g
}
Bullet::~Bullet()
{
    //delete g;
}