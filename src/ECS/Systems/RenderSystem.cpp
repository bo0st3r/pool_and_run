#include "RenderSystem.h"

RenderSystem::RenderSystem(Positions& p, Renderers& r, sf::RenderWindow& v, pr::AssetManager& am)
{
    positions = &p;
    renderers = &r;
    view = &v;
    asset = &am;
}

RenderSystem::~RenderSystem()
{
    delete positions;
    delete renderers;
}

void RenderSystem::update(float dt)
{
    for(Renderers::iterator it = renderers->begin(); it != renderers->cend(); it++)
    {
        view->clear();

        Entity entity = it->first;
        RendererComponent& render = it->second;
        sf::Sprite& sprite = render.getSpriteRef();

        //si le sprite n'a pas encore de texture, lui en assigne une
        if(!render.hasSpriteTextured()){
            asset->setSpriteTexture(sprite, render.getTextureName());
            sprite.setScale(render.getScale());
        }

        //si l'entité a une position, applique cette position au sprite, sinon lui assigne la position (0, 0);
        if(positions->find(entity) != positions->cend())
        {
            sprite.setPosition(positions->at(entity).getPosition());
        }else
        {
            sprite.setPosition(0.0, 0.0);
        }

        view->draw(sprite);
    }

    view->display();
}
