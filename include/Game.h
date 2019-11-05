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
            Game(int screenWidth = 1920, int screenHeight = 1080, string screenTitle = "Pool and Run");
            virtual ~Game();

        protected:

        private:
            /// It is equivalent to the game's framerate
            const float _dt = 1.0 / 120.0;
            Clock _clock;
            GameDataRef _data = std::make_shared<GameData>();

            //////////////////////////////////////////////////////////
            /// \brief Runs the game loop.
            //////////////////////////////////////////////////////////
            void run();
    };
}

#endif // GAME_H
