#include "State/MainMenuState.h"
#include "Configuration/Configuration.h"

#include <iostream>

#include "State/GameState.h"

namespace pr{
    MainMenuState::MainMenuState(GameDataRef data):_data(data){
        ///////////////////////////// UNCOMMENT THIS WHEN DONE TESTING        ///////////////////////////// UNCOMMENT THIS WHEN DONE TESTING        ///////////////////////////// UNCOMMENT THIS WHEN DONE TESTING
        _clickedPlay = false;
        ///////////////////////////// UNCOMMENT THIS WHEN DONE TESTING
        ///////////////////////////// UNCOMMENT THIS WHEN DONE TESTING
        ///////////////////////////// UNCOMMENT THIS WHEN DONE TESTING
    }

    MainMenuState::~MainMenuState(){

    }

    void MainMenuState::init(){
        // Loads and sets the background
        _data->assets.loadTexture(BACKGROUND_NAME, MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assets.setSpriteTexture(_background, BACKGROUND_NAME);
        _background.setPosition(0,0);
        scaleBackgroundToWindow(_background, _data);

        // Loads and sets the title
        _data->assets.loadTexture(TITLE_NAME, MAIN_MENU_TITLE_FILEPATH);
        _data->assets.setSpriteTexture(_title, TITLE_NAME);
        _data->assets.centerSpriteOrigin(_title, TITLE_NAME);
        _title.setPosition(_data->window.getSize().x * 0.5, Game::SCREEN_HEIGHT*0.34);

        // Loads and sets the play button
        _data->assets.loadTexture(PLAY_BTN_NAME, PLAY_BTN_FILEPATH);
        _data->assets.setSpriteTexture(_playBtn, PLAY_BTN_NAME);
        _data->assets.centerSpriteOrigin(_playBtn, PLAY_BTN_NAME);
        _playBtn.setPosition(_data->window.getSize().x * 0.5, Game::SCREEN_HEIGHT*0.64);
    }

    void MainMenuState::handleInput(Event event){
        switch(event.type){

            case Event::MouseButtonPressed:
                // If the play button sprite is clicked and hasn't been clicked yet, sets _clickedPlay to true.
                if(_data->inputs.isSpriteClicked(_playBtn, event.mouseButton.button, _data->window)
                   && !_clickedPlay){
                    _clickedPlay = true;
                }
                break;

            case Event::Closed:
                _data->window.close();
                break;

            default:
                break;
        }
    }

    void MainMenuState::str(){
        std::cout << "menu" << std::endl;
    }

    void MainMenuState::update(float dt){
        // If the play button has been clicked, remplace the current state with GameState
        if(_clickedPlay){
            _data->machine.addState(StateRef(new GameState(_data)));
            _clickedPlay = false;
        }
    }

    void MainMenuState::draw(float dt){
        _data->window.draw(_background);
        _data->window.draw(_title);
        _data->window.draw(_playBtn);
    }
}
