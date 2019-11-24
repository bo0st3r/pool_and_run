#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SFML/Graphics.hpp>

#include <System.h>
#include <AssetManager.h>
#include <Configuration/Configuration.h>


class RenderSystem : public System
{
    public:
        RenderSystem(Positions& p, Renderers& r, Characters& ch, Controllers& co, UIs& u, pr::AssetManager& am);
        virtual ~RenderSystem();

        virtual void update(float dt);
        void updateRender(float dt, sf::RenderWindow& window, sf::View& view);
        bool isInsideView(sf::Sprite sprite, sf::View view);

    protected:

    private:
        Positions* positions;
        Renderers* renderers;
        Characters* characters;
        Controllers* controllers;
        UIs* uis;
        pr::AssetManager* asset;
};

#endif // RENDERSYSTEM_H
