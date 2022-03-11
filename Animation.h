#pragma once
#include<SFML/graphics.hpp>

class Animation : public sf::Drawable
{
    enum class States
    {
        Paused,
        Playing,
        Stopped
    };
    int nrFrames;
    int nrColumns;
    int nrRows;
    sf::Vector2f frameSize;
    sf::Sprite graphics;
    float elapsedTime;
    float totalTime;
    States currentState;
    bool loopable;
public:
    Animation(sf::Texture& animationSheetTexture, int nrFrames, int nrColumns, int nrRows, sf::Vector2f worldSize, sf::Vector2f position, sf::Vector2f origin, float totalTime, bool loopable);
    int CurrentFrameNumber();
    void update(float dt);
    void Play();
    void Pause();
    void Stop();
    bool IsStopped();
    void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};
