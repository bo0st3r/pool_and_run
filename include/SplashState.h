#ifndef SPLASHSTpdaATE_H
#define SPLASHSTATE_H

#include "State.h"
#include "Game.h"

namespace pr{
    class SplashState : public State
    {
        public:
            SplashState(GameDataRef data);
            virtual ~SplashState();
            void init();
            void handleInput();
            void update(float dt);
            void draw(float dt);

        private:
            GameDataRef _data;
            Clock _clock;
            Sprite _background;
    };
}

#endif // SPLASHSTATE_H
