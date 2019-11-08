#include "RenderSystem.h"
#include <iostream>

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
    delete view;
    delete asset;
}


///Le renderSystem va permettre l'affichage des sprites des différentes entités sur la vue
///Il va commencer chaque update en nettoyant la vue
///ensuite charger la texture sur le sprite si celui ci ne la possède pas déjà
///puis il va ajuster l'echelle du sprite
///avant de finalement le dessiner sur la vue
///et pour finir il va afficher la vue dans la fenêtre
void RenderSystem::update(float dt)
{

    view->clear();

    for(Renderers::iterator it = renderers->begin(); it != renderers->cend(); it++)
    {

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
        std::cout << entity << " : " << render.getSpriteRef().getPosition().x << ", " << render.getSpriteRef().getPosition().y << std::endl;
    }

    view->display();
}
