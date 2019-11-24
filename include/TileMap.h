#ifndef TILEMAP_H
#define TILEMAP_H


#include <SFML/Graphics.hpp>
#include <ECSCoordinatorSingleton.h>
#include <ComponentManagerSingleton.h>
#include <EntityCreator.h>

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
            loadMap(const string& tileSet, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, ECSCoordinatorSingleton* ecs, ComponentManagerSingleton* compManager);

            static std::unordered_map<int, Entity>& getloadedTileEntitiesRef();
        protected:

        private:
            sf::VertexArray _vertices;
            sf::Texture _tileSet;
            static inline std::unordered_map<int, Entity> loadedTileEntities = std::unordered_map<int, Entity>();
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
