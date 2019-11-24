#include "RenderSystem.h"
#include <iostream>

RenderSystem::RenderSystem(Positions& p, Renderers& r, pr::AssetManager& am)
{
    positions = &p;
    renderers = &r;
    asset = &am;
}

RenderSystem::~RenderSystem()
{
//    delete positions;
//    delete renderers;
//    delete asset;
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

            //saute l'entité pour cette boucle
            if (render.getLayer() != layer)
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
                sprite.setPosition(positions->at(entity)->getPosition());
            }else
            {
                sprite.setPosition(0.0, 0.0);
            }

            //dessinne le sprite
            if(layer >= 0){window.draw(sprite);}

        }
    }
}
