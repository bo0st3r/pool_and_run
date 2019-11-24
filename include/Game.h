#ifndef GAME_H
#define GAME_H
#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

using std::string;
using sf::Clock;

namespace pr{
    struct GameData{
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        InputManager inputs;
    };

    /// Represents a shared pointer of GameData struct
    typedef std::shared_ptr<GameData> GameDataRef;

    class Game
    {
        public:
            inline static int SCREEN_WIDTH = 1344;
            inline static int SCREEN_HEIGHT = 756;
//            inline static int SCREEN_WIDTH = 1920;
//            inline static int SCREEN_HEIGHT = 1080;
            inline static int VIEW_WIDTH = SCREEN_WIDTH * 0.25;
            inline static int VIEW_HEIGHT = SCREEN_HEIGHT * 0.25;

            /// \brief Builds the window (default is 1920x1090, titled "Pool and Run") and runs the game.
            Game(int screenWidth = SCREEN_WIDTH, int screenHeight = SCREEN_HEIGHT, string screenTitle = "Pool and Run", bool isFullscreen = false);
            virtual ~Game();

            void initTextures();

        protected:

        private:
            /// Game's max framerate
            const float _dt = 1.0 / 50.0;
            Clock _clock;
            /// Represents the window, state machine, asset manager and input manager
            GameDataRef _data = std::make_shared<GameData>();

            //////////////////////////////////////////////////////////
            /// \brief Runs the game loop.
            /// Starts with the SplashState and then automatically moves on to the MenuState.
            //////////////////////////////////////////////////////////
            void run();
    };
}

#endif // GAME_H
