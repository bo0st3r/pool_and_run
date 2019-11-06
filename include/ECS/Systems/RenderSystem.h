#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SFML/Graphics.hpp>

#include <System.h>
#include <AssetManager.h>


class RenderSystem : public System
{
    public:
        RenderSystem(Positions& p, Renderers& r, sf::RenderWindow& v, pr::AssetManager& am);
        virtual ~RenderSystem();

        virtual void update(float dt);

    protected:

    private:
        Positions* positions;
        Renderers* renderers;
        sf::RenderWindow* view;
        pr::AssetManager* asset;
};

#endif // RENDERSYSTEM_H
