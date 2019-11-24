#ifndef ENDGAMESTATE_H
#define ENDGAMESTATE_H

#include "State.h"
#include "Game.h"
#include "Configuration/Configuration.h"


namespace pr{
    class EndGameState : public State
    {
        public:
            inline static const std::string BACKGROUND_NAME = "EndGameBackground";
            inline static const std::string GAME_RESULT_NAME = "GameResult";
            inline static const std::string MENU_BTN_NAME= "MenuBtn";

            EndGameState(GameDataRef data, bool hasWon);
            virtual ~EndGameState();
            void init();
            void handleInput(Event event);
            void update(float dt);
            void draw(float dt);
            void str();

        protected:

        private:
            GameDataRef _data;

            Sprite _background;
            Sprite _gameResult;
            Sprite _menuBtn;

            bool _hasWon;

            bool _clickedMenuBtn;
    };
}

#endif // ENDGAMESTATE_H
