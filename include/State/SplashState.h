#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "State.h"
#include "Game.h"

namespace pr{
    /////////
    /// \class First state that pops-up. It shows the background scene for a defined time before skipping to the MainMenuState.
    /////////
    class SplashState : public State
    {
        public:
            inline static const std::string BACKGROUND_NAME = "SplashBackground";

            /////
            /// \brief Instantiates a SplashState and sets it's GameDataRef.
            /////
            SplashState(GameDataRef data);
            virtual ~SplashState();

            /////
            /// \brief Loads the background texture and set it to the background sprite.
            /////
            void init();

            /////
            /// \brief Handles Escape and close window inputs.
            /// Escape : skips the scene
            /////
            void handleInput(Event event);

            /////
            /// \brief Decreases sceneDuration by the dt argument.
            /////
            void update(float dt);

            /////
            /// \brief Draws the background sprite.
            /////
            void draw(float dt);

            /////
            /// \brief Resizes the background to fit the window.
            /////
            void resizeBackground();

        private:
            GameDataRef _data;
            Sprite _background;
            /// \brief Represents the time left for the scene to end.
//            float sceneTimeLeft = 1.8;
            float sceneTimeLeft = 0.0001;
//            float sceneTimeLeft = 5;
    };
}

#endif // SPLASHSTATE_H
