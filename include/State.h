#ifndef STATE_H
#define STATE_H
#pragma once

#include <SFML/Graphics.hpp>

using sf::Clock;
using sf::Sprite;
using sf::Event;
using sf::Vector2f;

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
            virtual void handleInput(Event event) = 0;

            // Updates the state elements
            virtual void update(float dt) = 0;

            // Draws the state drawables
            virtual void draw(float dt) = 0;

            // Pauses the state
            virtual void pause(){}

            // Resumes the state
            virtual void resume(){}


        protected:
            ////////////////////////////////////////
            /// \brief Sets the sprite size to fit the window size from the given GameDataRef.
            ////////////////////////////////////////
            template <class T>
            void scaleBackgroundToWindow(Sprite& sprite, T& data){
                Vector2f backSize = (Vector2f) sprite.getTexture()->getSize();
                Vector2f windowSize = (Vector2f) data->window.getSize();
                sprite.scale(windowSize.x /backSize.x, windowSize.y /backSize.y);
            }

            /////////////////////////////////////////////////////////
            // Copy what's written below when adding a new state.  //
            /////////////////////////////////////////////////////////
//            void init();
//
//            void handleInput(Event event);
//
//            void update(float dt);
//
//            void draw(float dt);
    };
}

#endif // STATE_H
