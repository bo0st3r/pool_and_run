#include "Game.h"
#include <iostream>

namespace pr{
    Game::Game(int screenWidth, int screenHeight, string screenTitle)
    {
        _data->window.create(sf::VideoMode(screenWidth, screenHeight), screenTitle);

        run();
    }

    Game::~Game()
    {
        //dtor
    }

    void Game::run(){
        float newTime, frameTime, interpolation;

        float currentTime = _clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while( _data->window.isOpen()){
            _data->machine.processStateChanges();

            // Gets the time elapsed since last retrieval
            newTime = _clock.getElapsedTime().asSeconds();
            // Equals to the duration between frames
            frameTime = newTime - currentTime;
            if(frameTime > 0.25f){
                frameTime = 0.25f;
            }

            // Refresh the current time
            currentTime = newTime;

            // Increments the accumulator
            accumulator += frameTime;

            while(accumulator >= _dt){
                _data->machine.getActiveState()->handleInput();
                _data->machine.getActiveState()->update(_dt);

                accumulator -= _dt;
            }

            interpolation = accumulator / _dt;
            _data->machine.getActiveState()->draw(interpolation);
        }
    }

}
