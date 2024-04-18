#pragma once
#include "Actor.h"
class Player :
    public Actor
{
public:
    Player(const Point2f& pos, const Rectf& boundaries);
    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;

    void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
    void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
private:

};

