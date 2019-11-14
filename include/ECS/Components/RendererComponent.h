#ifndef RENDERERCOMPONENT_H
#define RENDERERCOMPONENT_H

#include <SFML/Graphics.hpp>

#include <Component.h>


class RendererComponent : public Component
{
    public:
        RendererComponent(std::string textureName = "", sf::Vector2f scale = sf::Vector2f(1, 1), int layer = -1);
        virtual ~RendererComponent();
        virtual ComponentID getTypeId() const;

        static inline const ComponentID ID = 3;

        std::string getTextureName() const;
        sf::Vector2f getScale() const;
        sf::Sprite& getSpriteRef();
        bool hasSpriteTextured() const;
        int getLayer() const;

        virtual std::string str()const;

    protected:

    private:
        int layer;
        std::string textureName;
        sf::Sprite sprite;
        sf::Vector2f scale;
};

#endif // RENDERERCOMPONENT_H
