#include "Game.h"
#include <iostream>
#include <windows.h>

#include "State/SplashState.h"

namespace pr{
    Game::Game(int screenWidth, int screenHeight, string screenTitle)
    {
        _data->window.create(sf::VideoMode(screenWidth, screenHeight), screenTitle);
//        _data->window.create(sf::VideoMode(screenWidth, screenHeight), screenTitle, sf::Style::Fullscreen);
//        _data->window.setPosition(sf::Vector2i(0 - GetSystemMetrics(SM_CXSIZEFRAME), 0));
        run();
    }

    Game::~Game()
    {

    }

    void Game::run(){
        _data->machine.addState(pr::StateRef(new pr::SplashState(_data)));

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
                Event event;
                _data->window.pollEvent(event);
                _data->machine.getActiveState()->handleInput(event);

                _data->machine.getActiveState()->update(_dt);

                accumulator -= _dt;
            }

            interpolation = accumulator / _dt;

            _data->window.clear();
            _data->machine.getActiveState()->draw(interpolation);
            _data->window.display();
        }
    }

}
