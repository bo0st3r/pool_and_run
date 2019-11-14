#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#pragma once

#include <SFML/Graphics.hpp>

using sf::RenderWindow;
using sf::Sprite;
using sf::Mouse;
using sf::Vector2f;
using sf::Vector2i;

namespace pr{
    class InputManager
    {
        public:
            InputManager();
            virtual ~InputManager();

            bool isSpriteClicked(Sprite target, Mouse::Button btn, RenderWindow& window);
            bool isSpriteClickedPixelPerfect(Sprite target, Mouse::Button btn, RenderWindow& window);
            Vector2i getMousePosition(RenderWindow &window);


        protected:

        private:
    };
}

#endif // INPUTMANAGER_H
