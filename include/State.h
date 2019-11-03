#ifndef STATE_H
#define STATE_H
#pragma once

// Represents any state of the game (i.e. menu, game, won, lost, ...)
class State
{
    public:
        // Inits the new state
        virtual void init() = 0;

        // Handles the inputs for that state
        virtual void handleInput() = 0;

        // Updates the state elements
        virtual void update() = 0;

        // Draws the state drawables
        virtual void draw(float dt) = 0;

        // Pauses the state
        virtual void pause();

        // Resumes the statez
        virtual void resume();
};

#endif // STATE_H
