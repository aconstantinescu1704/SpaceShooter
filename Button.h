#pragma once
#include<SFML/graphics.hpp>

class Button: public sf::Drawable
{
    enum class States
    {
        Pressed,
        Idle,
        Hover
    };
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Sprite graphics;
    States state;
    sf::RenderWindow* win;
public:
    Button(sf::Texture& tex, sf::Vector2f creationPosition, sf::Vector2f size,sf::RenderWindow* win);
    bool isMouseOver(sf::Vector2f point);
    void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
    void update(float dt);

};