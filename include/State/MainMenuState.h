#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "Game.h"

namespace pr{
    class MainMenuState : public State
    {
        public:
            inline static const std::string BACKGROUND_NAME = "MainMenuBackground";
            inline static const std::string PLAY_BTN_NAME = "PlayBtn";
            inline static const std::string TITLE_NAME = "Title";

            MainMenuState(GameDataRef data);
            virtual ~MainMenuState();

            //////////////////////////////////////////
            /// \brief Loads textures and set sprites's texture, position and origin.
            //////////////////////////////////////////
            void init();

            //////////////////////////////////////////
            /// \brief Handles clicking on the play button and window closing.
            //////////////////////////////////////////
            void handleInput(Event event);

            //////////////////////////////////////////
            /// \brief Remplace this state with GameState is the play button has been clicked.
            //////////////////////////////////////////
            void update(float dt);

            //////////////////////////////////////////
            /// \brief Draws the background, title and
            //////////////////////////////////////////
            void draw(float dt);

        protected:

        private:
            GameDataRef _data;

            Sprite _background;
            Sprite _title;
            Sprite _playBtn;

            bool _clickedPlay;
    };
}

#endif // MAINMENUSTATE_H
