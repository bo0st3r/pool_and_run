#ifndef STATE_H
#define STATE_H
#pragma once

// Represents any state of the game (i.e. menu, game, won, lost, ...)
namespace pr{
    ////////////////////////////////////////////////////////////////
    /// \class Manages the states of the game. It is part of the "State" design pattern.
    ////////////////////////////////////////////////////////////////
    class State
    {
        public:
            // Inits the new state
            virtual void init() = 0;

            // Handles the inputs for that state
            virtual void handleInput() = 0;

            // Updates the state elements
            virtual void update(float dt) = 0;

            // Draws the state drawables
            virtual void draw(float dt) = 0;

            // Pauses the state
            virtual void pause();

            // Resumes the state
            virtual void resume();
    };
}

#endif // STATE_H
