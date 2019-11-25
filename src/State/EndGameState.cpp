#include "EndGameState.h"
#include "MainMenuState.h"
#include <iostream>

namespace pr{

    EndGameState::EndGameState(GameDataRef data, bool hasWon):_data(data),_hasWon(hasWon){
        _clickedMenuBtn = false;
    }

    EndGameState::~EndGameState(){}

    void EndGameState::init(){
        // Loads and sets the background
        _data->assets.loadTexture(BACKGROUND_NAME, MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assets.setSpriteTexture(_background, BACKGROUND_NAME);
        _background.setPosition(0,0);
        scaleBackgroundToWindow(_background, _data);

        // Loads and sets the game result
        if(_hasWon){
            _data->assets.loadTexture(GAME_RESULT_NAME, END_GAME_WON_TITLE_FILEPATH);
        } else {
            _data->assets.loadTexture(GAME_RESULT_NAME, END_GAME_LOST_TITLE_FILEPATH);
        }
        _data->assets.setSpriteTexture(_gameResult, GAME_RESULT_NAME);
        _data->assets.centerSpriteOrigin(_gameResult, GAME_RESULT_NAME);
        _gameResult.setPosition(_data->window.getSize().x * 0.5, 300.0);

        // Loads and sets the play button
        _data->assets.loadTexture(MENU_BTN_NAME, END_GAME_MENU_BTN_FILEPATH);
        _data->assets.setSpriteTexture(_menuBtn, MENU_BTN_NAME);
        _menuBtn.setPosition(_data->window.getSize().x * 0.5, 570.0);
        _data->assets.centerSpriteOrigin(_menuBtn, MENU_BTN_NAME);

        // Resets the view
        _data->window.setView(_data->window.getDefaultView());
    }

    void EndGameState::handleInput(Event event){
        switch(event.type){
            case Event::MouseButtonPressed:
                // If the play button sprite is clicked and hasn't been clicked yet, sets _clickedPlay to true.
                if(_data->inputs.isSpriteClicked(_menuBtn, event.mouseButton.button, _data->window)
                   && !_clickedMenuBtn){
                    _clickedMenuBtn = true;
                }
                break;

            case Event::Closed:
                _data->window.close();
                break;

            default:
                break;
        }

    }

    void EndGameState::update(float dt){
        // If the menu button has been clicked, remplace the current state with MainMenuState
        if(_clickedMenuBtn){
            _data->machine.addState(StateRef(new MainMenuState(_data)));
            _clickedMenuBtn = false;
        }
    }

    void EndGameState::draw(float dt){
        _data->window.draw(_background);
        _data->window.draw(_gameResult);
        _data->window.draw(_menuBtn);
    }
}
