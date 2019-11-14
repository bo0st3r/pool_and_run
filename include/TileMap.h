#ifndef TILEMAP_H
#define TILEMAP_H


#include <SFML/Graphics.hpp>

using std::string;
using sf::Vector2u;

namespace pr{
    class TileMap : public sf::Drawable, public sf::Transformable
    {
        public:
            TileMap();
            virtual ~TileMap();

            ///////////////
            /// \brief Loads the map as an VertexArray into _vertices and an Texture into _tileSet.
            ///////////////
            loadMap(const string& tileSet, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

        protected:

        private:
            sf::VertexArray _vertices;
            sf::Texture _tileSet;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
                // Apply the transform
                states.transform *= getTransform();

                // Apply the tileset texture
                states.texture = &_tileSet;

                // Draw the vertex array
                target.draw(_vertices, states);
            }
    };
}

#endif // TILEMAP_H
