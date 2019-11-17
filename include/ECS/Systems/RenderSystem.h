#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SFML/Graphics.hpp>

#include <System.h>
#include <AssetManager.h>


class RenderSystem : public System
{
    public:
        RenderSystem(Positions& p, Renderers& r, pr::AssetManager& am);
        virtual ~RenderSystem();

        virtual void update(float dt);
        void updateRender(float dt, sf::RenderWindow& window, sf::View& view);

    protected:

    private:
        Positions* positions;
        Renderers* renderers;
        pr::AssetManager* asset;
};

#endif // RENDERSYSTEM_H
