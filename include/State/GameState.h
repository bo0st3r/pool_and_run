#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "State.h"
#include "Game.h"
#include "TileMap.h"
#include "EntityCreator.h"

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
            /// \brief Inits the ECS
            ///////////////////////
            void initECS();

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

            ECSCoordinatorSingleton* ecs;
            ComponentManagerSingleton* compManager;



    };
}

#endif // GAMESTATE_H
