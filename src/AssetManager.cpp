#include <iostream>
#include <stdexcept>


#include "Collision.h"
#include "AssetManager.h"

using namespace std;
namespace pr{
    AssetManager::AssetManager()
    {
        //ctor
    }

    AssetManager::~AssetManager()
    {
        //dtor
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
        return _textures.count(name) > 0;
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
    }

    void AssetManager::unloadFont(const string& name){
    }

    bool AssetManager::hasFont(const string& name){
    }

    sf::Font& AssetManager::getFont(const string& name) const{
    }


}
