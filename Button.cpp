#include "Button.h";
using namespace sf;

Button::Button(sf::Texture& tex, sf::Vector2f creationPosition, sf::Vector2f size, sf::RenderWindow* win)
{
    position = creationPosition;
    this->size = size;
    state = States::Idle;
    this->win = win;
    graphics.setTexture(tex);
    graphics.setPosition(creationPosition);
    graphics.setOrigin(tex.getSize().x / 2, tex.getSize().y);
    graphics.setScale( size.x / tex.getSize().x, -size.y / tex.getSize().y);

}
bool Button::isMouseOver(Vector2f point)
{
    return (point.x >= position.x - size.x/2 && point.x <= position.x + size.x/2) && 
           (point.y >= position.y - size.y/2 && point.y <= position.y + size.y/2);
}
void Button::update(float dt)
{
    Vector2f mousePos = win->mapPixelToCoords(Mouse::getPosition(*win));
    switch (state)
    {
    case States::Idle:
    {
        if (isMouseOver(mousePos))
        {
            if (Mouse::isButtonPressed(Mouse::Button::Left))
                state = States::Pressed;
            else
                state = States::Hover;
        }
    }
    break;
    case States::Hover:
    {
        if (isMouseOver(mousePos))
        {
            if (Mouse::isButtonPressed(Mouse::Button::Left))
                state = States::Pressed;

        }
        else
            state = States::Idle;
    }
    break;
    case States::Pressed:
    {
        if (isMouseOver(mousePos))
        {
            if (!Mouse::isButtonPressed(Mouse::Button::Left))
                state = States::Hover;

        }
        else
            state = States::Idle;
    }
    break;
    default:
        break;
    }

    switch (state)
    {
    case States::Hover:
    {
        graphics.setColor(Color(200, 200, 200));
    }
    break;
    case States::Idle:
    {
        graphics.setColor(Color::White);
    }
    break;
    case States::Pressed:
    {
        graphics.setColor(Color(100, 100, 100));
    }
    break;
    default:
        break;
    }
}
void Button::draw(RenderTarget& rt, RenderStates rs) const
{
    rt.draw(graphics, rs);
}
