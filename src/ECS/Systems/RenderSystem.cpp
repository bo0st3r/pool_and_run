#include "RenderSystem.h"
#include <iostream>

RenderSystem::RenderSystem(Positions& p, Renderers& r, Characters& ch, Controllers& co, UIs& u, pr::AssetManager& am)
{
    positions = &p;
    renderers = &r;
    characters = &ch;
    controllers = &co;
    uis = &u;
    asset = &am;
}

RenderSystem::~RenderSystem()
{
<<<<<<< HEAD
//    delete positions;
//    delete renderers;
//    delete asset;
=======
    delete positions;
    delete renderers;
    delete characters;
    delete controllers;
    delete uis;
    delete asset;
>>>>>>> 25c12bb88d5b7163c5b66f4ad4372690a330b1a3
}

void RenderSystem::update(float dt)
{

}


///Le renderSystem va permettre l'affichage des sprites des différentes entités sur la vue
///Il va commencer chaque update en nettoyant la vue
///la boucle se fait par couche
///-1 : les tiles, non affichée mais nécéssaires aux calculs de collision
///0 : le background
///1 : le niveau complet
///2 : les triggers
///3 : les ennemis
///4 : le joueur
///5 : le GUI
///ensuite charger la texture sur le sprite si celui ci ne la possède pas déjà
///puis il va ajuster l'echelle du sprite
///avant de finalement le dessiner sur la vue
///(par soucis d'optimisation, le draw des tiles individuelles est remplacer par le draw du niveau mais leur existence reste nécéssaire pour les collision)
///et pour finir il va afficher la vue dans la fenêtre
void RenderSystem::updateRender(float dt, sf::RenderWindow& window, sf::View& view)
{
    for(int layer = -1; layer < 6; layer++)
    {
        for(Renderers::iterator it = renderers->begin(); it != renderers->cend(); it++)
        {
            Entity entity = it->first;
            RendererComponent& render = *(it->second);
            sf::Sprite& sprite = render.getSpriteRef();

            int renderLayer = render.getLayer();

            //si c'est un élément d'UI, fait un test pour l'affichage
            if(renderLayer == 5 && uis->find(entity) != uis->cend())
            {
                Entity player = EntityManagerSingleton::MAX_ENTITY;
                for(Characters::iterator it2 = characters->begin(); it2 != characters->cend(); it2++)
                {
                    if(it2->second->getTag() == TAG_PLAYER)
                    {
                        player = it2->first;

                    }
                }

                UIComponent ui = *(uis->at(entity));
                switch (ui.getUIType())
                {
                    case UITypeEnum::DashIndicator:{
                        if(controllers->at(player)->getDashTime() > 0)
                        {
                            renderLayer = -1;
                        }
                    break;}
                    case UITypeEnum::HealthBar:{
                        if(characters->at(player)->getLive() < ui.getDataValue())
                        {
                            renderLayer = -1;
                        }
                    break;}
                }
            }

            //saute l'entité pour cette boucle
            if (renderLayer != layer)
            {
                continue;
            }

            //si le sprite n'a pas encore de texture, lui en assigne une
            if(!render.hasSpriteTextured()){
                asset->setSpriteTexture(sprite, render.getTextureName());
                sprite.setScale(render.getScale());
            }

            //si l'entité a une position, applique cette position au sprite, sinon lui assigne la position (0, 0);
            if(positions->find(entity) != positions->cend())
            {
                if(renderLayer < 5)
                {
                    sprite.setPosition(positions->at(entity)->getPosition());
                }else
                {
                    sf::Vector2f viewSize = view.getSize();
                    sf::Vector2f viewCenter = view.getCenter();
                    sf::Vector2f origin = sf::Vector2f(viewCenter.x - viewSize.x/2, viewCenter.y - viewSize.y/2);

                    sprite.setPosition(origin + positions->at(entity)->getPosition());
                }
            }else
            {
                sprite.setPosition(0.0, 0.0);
            }

            //dessinne le sprite
            if(layer >= 0 && isInsideView(sprite, view)){window.draw(sprite);}

        }
    }
}

bool RenderSystem::isInsideView(sf::Sprite sprite, sf::View view)
{
    sf::Vector2f spritePos = sprite.getPosition();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    return (spritePos.x + sprite.getGlobalBounds().width >= (viewCenter.x - viewSize.x / 2) &&
       spritePos.x < (viewCenter.x + viewSize.x / 2) &&
       spritePos.y + sprite.getGlobalBounds().height >= (viewCenter.y - viewSize.y / 2) &&
       spritePos.y < (viewCenter.y + viewSize.y / 2));

}
