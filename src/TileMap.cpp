#include "Collision.h"

#include "TileMap.h"

#include <iostream>

using sf::Vector2f;

namespace pr{
    TileMap::TileMap()
    {
        //ctor
    }

    TileMap::~TileMap()
    {
        //dtor
    }

    TileMap::loadMap(const string& tileSet, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height){
        // Tries to load file
        if(!Collision::CreateTextureAndBitmask(_tileSet, tileSet))
            return false;

        // Resizes the vertex array so it can contain the whole level
        _vertices.setPrimitiveType(sf::Quads);
        _vertices.resize(width * height * 4);


        for(unsigned int i =0; i < width; ++i){
            for(unsigned int j =0; j < height; ++j){

                // Get the current tile number
                int tileNb = tiles[i + j * width];

                // Finds its position in the tileset
                int tu = tileNb % (_tileSet.getSize().x / tileSize.x);
                int tv = tileNb / (_tileSet.getSize().y / tileSize.y);

                // Gets a pointer to the current tile's quad
                sf::Vertex* quad = &_vertices[(i + j * width) * 4];

                // Defines its 4 corners
                quad[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // Defines its 4 texture coordinates
                quad[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }

        return true;
    }

}

