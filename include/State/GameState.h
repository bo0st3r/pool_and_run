#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "State.h"
#include "Game.h"
#include "TileMap.h"
#include "EntityCreator.h"
#include "Configuration/Configuration.h"

#include "ECSCoordinatorSingleton.h"
#include "ComponentManagerSingleton.h"

using sf::View;
using std::unique_ptr;

namespace pr{
    typedef unique_ptr<View> ViewRef;

    class GameState : public State
    {
        public:
            inline static const std::string BACKGROUND_NAME = "GameBackground";

            ///////////////////
            /// \brief Initialises the game state and sets it's view.
            ///////////////////
            GameState(GameDataRef data);
            virtual ~GameState();

            void init();
            void handleInput(Event event);
            void update(float dt);
            void draw(float dt);

            ///////////////////////
            /// \brief Inits the game's tile map.
            ///////////////////////
            void initTileMap();

            ///////////////////////
            /// \brief Inits the ECS itself
            ///////////////////////
            void initECS();

            ///////////////////////
            /// \brief Inits the ECS's entities
            ///////////////////////
            void initEntities();

            ///////////////////////
            /// \brief Resizes the view based on the window.
            ///////////////////////
            void resizeView();

        protected:

        private:
            GameDataRef _data;

            Sprite _background;
            TileMap _tileMap;
            ViewRef _view;

            bool _isEnding;
            bool _isWinning;

            ECSCoordinatorSingleton* ecs;
            ComponentManagerSingleton* compManager;
            RespawnSystem* respawnSystem;
            TriggerSystem* triggerSystem;

    };
}

#endif // GAMESTATE_H
