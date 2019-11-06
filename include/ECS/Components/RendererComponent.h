#ifndef RENDERERCOMPONENT_H
#define RENDERERCOMPONENT_H

#include <SFML/Graphics.hpp>

#include <Component.h>


class RendererComponent : public Component
{
    public:
        RendererComponent(std::string textureName = "");
        virtual ~RendererComponent();
        virtual ComponentID getTypeId() const;
        static ComponentID getId(){return ID;};

        static inline const ComponentID ID = 3;

        std::string getTextureName() const;
        sf::Sprite& getSpriteRef();
        bool hasSpriteTextured() const;

        //changer la position
        //dessiner

        virtual std::string str()const;

    protected:

    private:
        sf::Sprite sprite;
        bool spriteSetted;
        std::string textureName;
};

#endif // RENDERERCOMPONENT_H
