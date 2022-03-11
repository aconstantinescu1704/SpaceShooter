#include "Animation.h"

using namespace sf;

Animation::Animation(Texture& animationSheetTexture, int nrFrames, int nrColumns, int nrRows, Vector2f worldSize, Vector2f position, Vector2f origin, float totalTime, bool loopable)
{
    currentState = States::Stopped;
    elapsedTime = 0;
    this->loopable = loopable;
    this->totalTime = totalTime;
    this->nrFrames = nrFrames;
    this->nrColumns = nrColumns;
    this->nrRows = nrRows;
    frameSize = Vector2f(animationSheetTexture.getSize().x / nrColumns, animationSheetTexture.getSize().y / nrRows);
    graphics.setTexture(animationSheetTexture);
    int currentFrameNumber = CurrentFrameNumber();
    graphics.setPosition(position);
    graphics.setOrigin(origin.x*frameSize.x, origin.y*frameSize.y);
    graphics.setTextureRect(IntRect((currentFrameNumber%nrColumns)*frameSize.x, (currentFrameNumber / nrColumns)*frameSize.y, frameSize.x, frameSize.y));
    graphics.setScale(worldSize.x / frameSize.x, worldSize.y / frameSize.y);
}
int Animation::CurrentFrameNumber()
{
    float percentage = elapsedTime / totalTime;
    return floor(percentage * nrFrames);
}

void Animation::update(float dt)
{
    switch (currentState)
    {
    case States::Playing:
    {
        elapsedTime += dt;

        if (elapsedTime > totalTime)
        {
            if (loopable)
                elapsedTime = 0;
            else
            {
                Stop();
                return;
            }
        }
        int currentFrameNumber = CurrentFrameNumber();
        graphics.setTextureRect(IntRect((currentFrameNumber%nrColumns)*frameSize.x, (currentFrameNumber / nrColumns)*frameSize.y, frameSize.x, frameSize.y));

        break;
    }
    case States::Paused:
        break;
    case States::Stopped:
        break;
    }

}

void Animation::Play()
{
    currentState = States::Playing;
}
void Animation::Pause()
{
    currentState = States::Paused;
}
void Animation::Stop()
{
    currentState = States::Stopped;
    elapsedTime = 0;
}
bool Animation::IsStopped()
{
    return (currentState == States::Stopped);
}
void Animation::draw(RenderTarget& rt, RenderStates rs) const
{
    rt.draw(graphics, rs);
}
