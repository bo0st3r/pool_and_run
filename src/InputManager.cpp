#include <iostream>
#include "Collision.h"

#include "InputManager.h"
#include "AssetManager.h"

namespace pr{
    InputManager::InputManager(){}

    InputManager::~InputManager(){}


    bool InputManager::isSpriteClicked(Sprite target, Mouse::Button btn, RenderWindow& window){
        sf::Texture tex;
        tex.loadFromFile(pr::AssetManager::OTHERS_PATH + "dot.png");
        Sprite mouse(tex);

        mouse.setOrigin(Vector2f(0.5, 0.5));
        mouse.setPosition((Vector2f) Mouse::getPosition(window));

        return Mouse::isButtonPressed(btn) && Collision::PixelPerfectTest(target, mouse);
    }

    Vector2i InputManager::getMousePosition(RenderWindow &window){

    }
}
