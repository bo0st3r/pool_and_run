#include "Configuration/Configuration.h"
#include "State/SplashState.h"
#include "State/MainMenuState.h"
#include <iostream>

namespace pr{
    SplashState::SplashState(GameDataRef data):_data(data){}

    SplashState::~SplashState(){
        _data->assets.unloadTexture(BACKGROUND_NAME);
    }

    void SplashState::init(){
        _data->assets.loadTexture(BACKGROUND_NAME,SPLASH_SCENE_BACKGROUND_FILEPATH);
        _data->assets.setSpriteTexture(_background, BACKGROUND_NAME);
        _background.setPosition(0,0);

        scaleBackgroundToWindow(_background, _data);
    }

    void SplashState::str(){
        std::cout << "splash" << std::endl;
    }

    void SplashState::handleInput(Event event){
        switch(event.type){
            // Sets the scene duration to 0 on pressing Escape
            case Event::KeyPressed:
                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        sceneTimeLeft = 0.0;
                        break;

                    default:
                        break;
                }
                break;

            case Event::Closed:
                _data->window.close();
                break;

            default:
                break;
        }
    }

    void SplashState::update(float dt){
        sceneTimeLeft -= dt;

        if(sceneTimeLeft <= 0){
            _data->machine.addState(StateRef(new MainMenuState(_data)));
            _data->machine.processStateChanges();
        }
    }

    void SplashState::draw(float dt){
        _data->window.draw(_background);
    }

//    void SplashState::resizeBackground(){
//        Vector2f windowSize = (Vector2f) _data->window.getSize();
//        _background.setScale(windowSize.x / rect.width, windowSize.y / rect.height);
//    }
}
