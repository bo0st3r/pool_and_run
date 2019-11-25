#include "Game.h"
#include <iostream>
#include <windows.h>

#include "State/SplashState.h"

namespace pr{
    Game::Game(int screenWidth, int screenHeight, string screenTitle, bool isFullscreen)
    {
        if(isFullscreen){
            _data->window.create(sf::VideoMode(screenWidth, screenHeight), screenTitle, sf::Style::Fullscreen);
        }  else {
            _data->window.create(sf::VideoMode(screenWidth, screenHeight), screenTitle);
        }

        initTextures();
        run();
    }

    Game::~Game(){}

    void Game::run(){
        _data->machine.addState(pr::StateRef(new pr::SplashState(_data)));

        float newTime, frameTime;

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
                while(_data->window.pollEvent(event))
                {
                    _data->machine.getActiveState()->handleInput(event);
                }

                _data->machine.getActiveState()->update(_dt);

                _data->window.clear();
                _data->machine.getActiveState()->draw(_dt);
                _data->window.display();
                accumulator -= _dt;
            }
        }
    }

    void Game::initTextures()
    {
        _data->assets.loadTexture("ball0", AssetManager::BALLS_PATH + "ball0.png");
        _data->assets.loadTexture("ball1", AssetManager::BALLS_PATH + "ball1.png");
        _data->assets.loadTexture("ball2", AssetManager::BALLS_PATH + "ball2.png");
        _data->assets.loadTexture("ball3", AssetManager::BALLS_PATH + "ball3.png");
        _data->assets.loadTexture("ball4", AssetManager::BALLS_PATH + "ball4.png");
        _data->assets.loadTexture("ball5", AssetManager::BALLS_PATH + "ball5.png");
        _data->assets.loadTexture("ball6", AssetManager::BALLS_PATH + "ball6.png");
        _data->assets.loadTexture("ball7", AssetManager::BALLS_PATH + "ball7.png");
        _data->assets.loadTexture("ball8", AssetManager::BALLS_PATH + "ball8.png");
        _data->assets.loadTexture("ball9", AssetManager::BALLS_PATH + "ball9.png");
        _data->assets.loadTexture("ball10", AssetManager::BALLS_PATH + "ball10.png");
        _data->assets.loadTexture("ball11", AssetManager::BALLS_PATH + "ball11.png");
        _data->assets.loadTexture("ball12", AssetManager::BALLS_PATH + "ball12.png");
        _data->assets.loadTexture("ball13", AssetManager::BALLS_PATH + "ball13.png");
        _data->assets.loadTexture("ball14", AssetManager::BALLS_PATH + "ball14.png");
        _data->assets.loadTexture("ball15", AssetManager::BALLS_PATH + "ball15.png");
        _data->assets.loadTexture("tile", AssetManager::GAME_PATH + "tileHitBox.png");
        _data->assets.loadTexture("cueLeft", AssetManager::GAME_PATH + "cueLeft.png");
        _data->assets.loadTexture("cueRight", AssetManager::GAME_PATH + "cueRight.png");
        _data->assets.loadTexture("checkPoint", AssetManager::GAME_PATH + "holeWhite.png");
        _data->assets.loadTexture("warpIn", AssetManager::GAME_PATH + "holeOrange.png");
        _data->assets.loadTexture("warpOut", AssetManager::GAME_PATH + "holeCyan.png");
        _data->assets.loadTexture("holeEnemy", AssetManager::GAME_PATH + "holeGreen.png");
        _data->assets.loadTexture("holePlayer", AssetManager::GAME_PATH + "holeRed.png");
        _data->assets.loadTexture("endLevel", AssetManager::GAME_PATH + "holeYellow.png");
<<<<<<< HEAD
        _data->assets.loadTexture("tuto", AssetManager::GAME_PATH + "Tuto.png");
=======
        _data->assets.loadTexture("chalk", AssetManager::GAME_PATH + "chalk.png");
>>>>>>> 6b5653ccf5f937cb53ca2797f1c04113dbbd6869
    }

}
