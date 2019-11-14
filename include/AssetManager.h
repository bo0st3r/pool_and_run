#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#pragma once

#include <map>
#include <SFML/Graphics.hpp>

using std::string;
using sf::Texture;
using sf::Sprite;

namespace pr{

    ////////////////////////////////////////////////////////////
    /// \class Manages and holds textures, fonts, sounds and so on.    ////////////////////////////////////////////////////////////
    class AssetManager
    {
        public:
            inline static const string RESSOURCES_PATH = "ressources/";

            inline static const string TILESETS_PATH = RESSOURCES_PATH + "tilesets/";

            inline static const string IMG_PATH = RESSOURCES_PATH + "img/";
            inline static const string BALLS_PATH = IMG_PATH + "balls/";
            inline static const string OTHERS_PATH = IMG_PATH + "others/";


            AssetManager();
            virtual ~AssetManager();

            ////////////////////////////////////////////////////////////
            //////////////////////// SPRITE ////////////////////////////
            ////////////////////////////////////////////////////////////
            /// \brief Set the sprite origin at it's center.
            ////////////////////////////////////////////////////////////
            void centerSpriteOrigin(Sprite& sprite, const string& name);

            ////////////////////////////////////////////////////////////
            /////////////////////// TEXTURES ///////////////////////////
            ////////////////////////////////////////////////////////////
            /// \brief Sets the given Sprite's texture using, if there is, the loaded Texture
            /// from _textures which corresponds to the given name.
            ////////////////////////////////////////////////////////////
            bool setSpriteTexture(Sprite& sprite, const string& name);

            ////////////////////////////////////////////////////////////
            /// \brief Loads a Texture from a file path into _textures and assigns it to the given name.
            ////////////////////////////////////////////////////////////
            bool loadTexture(const string& name, const string& filePath);

            ////////////////////////////////////////////////////////////
            /// \brief Unloads from _textures the Texture, if existing, that corresponds to the given name.
            ////////////////////////////////////////////////////////////
            void unloadTexture(const string& name);

            ////////////////////////////////////////////////////////////
            /// \brief Returns if _textures has a Texture for the given name.
            ////////////////////////////////////////////////////////////
            bool hasTexture(const string& name);

            ////////////////////////////////////////////////////////////            /// \brief Returns the Texture, if existing, that corresponds to the given name.
            ////////////////////////////////////////////////////////////
            Texture& getTexture(const string& name);



            ////////////////////////////////////////////////////////////
            /////////////////////// FONTS //////////////////////////////
            ////////////////////////////////////////////////////////////
            /// \brief Loads a Font from a file path into _fonts and assigns it to the given name.
            ////////////////////////////////////////////////////////////
            bool loadFont(const string& name, const string& filePath);

            ////////////////////////////////////////////////////////////
            /// \brief Unloads from _fonts the Font, if existing, that corresponds to the given name.
            ////////////////////////////////////////////////////////////
            void unloadFont(const string& name);

            ////////////////////////////////////////////////////////////
            /// \brief Returns if _fonts has a Font for the given name.
            ////////////////////////////////////////////////////////////
            bool hasFont(const string& name);

            ////////////////////////////////////////////////////////////            /// \brief Returns the Font, if existing, that corresponds to the given name.
            ////////////////////////////////////////////////////////////
            sf::Font& getFont(const string& name);

        private:
            std::map<string, Texture> _textures;
            std::map<string, sf::Font> _fonts;

    };
}

#endif // ASSETMANAGER_H
