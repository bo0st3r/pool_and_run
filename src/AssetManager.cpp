#include <iostream>
#include <stdexcept>

#include "Collision.h"
#include "AssetManager.h"

namespace pr{
    AssetManager::AssetManager()
    {
        //ctor
    }

    AssetManager::~AssetManager()
    {
        //dtor
    }

    ///////////////////////////// SPRITE ///////////////////////////////////
    void AssetManager::centerSpriteOrigin(Sprite& sprite, const string& name){
        sf::Vector2f texSize = (sf::Vector2f) getTexture(name).getSize();
        sprite.setOrigin(texSize.x * 0.5, texSize.y * 0.5);
    }


    //////////////////////////// TEXTURES //////////////////////////////////
    bool AssetManager::setSpriteTexture(Sprite& sprite, const string& name){
        if(hasTexture(name)){
            Texture& tex = getTexture(name);
            sprite.setTexture(tex);
            return true;
        }


        return false;
    }

    bool AssetManager::loadTexture(const string& name, const string& filePath){
        return Collision::CreateTextureAndBitmask(_textures[name], filePath);
    }

    void AssetManager::unloadTexture(const string& name){
        _textures.erase(name);
    }

    bool AssetManager::hasTexture(const string& name){
        bool res = false;
        if(_textures.count(name) > 0){
            res = true;
        }
        return res;
    }

    Texture& AssetManager::getTexture(const string& name){
        try{
            return _textures.at(name);
        }catch(std::out_of_range const& e){
            std::cerr << e.what() << std::endl;
        }
    }

    ////////////////////////////// FONTS ///////////////////////////////////

    bool AssetManager::loadFont(const string& name, const string& filePath){
        return _fonts[name].loadFromFile(filePath);
    }

    void AssetManager::unloadFont(const string& name){
        _fonts.erase(name);
    }

    bool AssetManager::hasFont(const string& name){
        return _fonts.count(name) > 0;
    }

    sf::Font& AssetManager::getFont(const string& name){
        try{
            return _fonts.at(name);
        }catch(std::out_of_range const& e){
            std::cerr << e.what() << std::endl;
        }

        return _fonts.at(name);
    }


}
