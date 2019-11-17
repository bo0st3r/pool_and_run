#include "CollisionSystem.h"
#include <iostream>

CollisionSystem::CollisionSystem(Characters& cha,
                        Renderers& r,
                        Positions& p,
                        Velocities& ve,
                        Gravities& g,
                        Colliders& col,
                        Triggers& t,
                        Constraints& con,
                        sf::View& v
                        )
{
    characters = &cha;
    renderers = &r;
    positions = &p;
    velocities = &ve;
    gravities = &g;
    colliders = &col;
    triggers = &t;
    constraints = &con;
    view = &v;

}

CollisionSystem::~CollisionSystem()
{
    delete characters;
    delete renderers;
    delete positions;
    delete velocities;
    delete colliders;
    delete triggers;
    delete constraints;
}

///le collisionSystem va permettre de détecter les collisions entre les personnages et les autres éléments du jeu
///il va parcourir la liste via une double boucle, la première sur les entités possédant un characterComponent, la deuxieme sur les entités possédant un ColliderComponent
///pour éviter les tests impossibles on va d'abord vérifier que les deux entités sont suffisamment proches l'une de l'autre
///on va ensuite verifier si il y a collision sur base du type de collider, si l'autre entité est un personnage on va transférer une proportion de la vélocité
///si oui on va bloquer le déplacement du personnage dans la direction qui a provoqué la collision
///si l'entité a un trigger, on ne bloque pas le déplacement mais on déclenche la fonction "onTrigger()" du composant
///si le personnage est le joueur et tombe hors de la caméra, on le tue
void CollisionSystem::update(float dt)
{
    for(Characters::iterator it1 = characters->begin(); it1 != characters->cend(); it1++)
    {

        Entity e1 = it1->first;
        CharacterComponent& ch1 = *(it1->second);
        PositionComponent& p1 = *(positions->at(e1));
        VelocityComponent v1 = *(velocities->at(e1));
        GravityComponent& g1 = *(gravities->at(e1));
        RendererComponent& r1 = *(renderers->at(e1));
        ColliderComponent& co1 = *(colliders->at(e1));

       //on bouge le sprite pour la durée du test de collision
        v1.addVelocity(0, g1.getG() * dt);
        r1.getSpriteRef().move(v1.getVelocity() * dt);

        //y a-t-il eu un rebond sur une plateforme
        bool floorBounce = false;
        //y a-t-il eu une collision?
        bool colliding = false;

        //centre la caméra sur le joueur et test de collision avec les bords de la vue (pour le joueur uniquement)
        if(ch1.getTag() == "Joueur")
        {
            view->setCenter(p1.getPosition());
            viewClamping();
            colliding = addViewBorderConstraints(r1.getSpriteRef(), e1);
        }

        //test de collision avec d'autres entité
        for(Colliders::iterator it2 = colliders->begin(); it2 != colliders->cend(); it2++)
        {
            Entity e2 = it2->first;
            ColliderComponent& c2 = *(it2->second);
            PositionComponent& p2 = *(positions->at(e2));
            RendererComponent& r2 = *(renderers->at(e2));


            if(e1 == e2)
            {
                continue;
            }

            bool collideWith = false;

            //verifie si il y a une collision selon 3 test possibles
            if(Vector2fMath::distanceBetween(p1.getPosition(), p2.getPosition()) <= maxCollidingDistance)
            {
                switch (co1.getColliderType())
                {
                    case ColliderTypeEnum::Circle:{
                        collideWith = Collision::CircleTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                    case ColliderTypeEnum::PixelPerfect:{
                        collideWith = Collision::PixelPerfectTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                    default:{//box par defaut
                        collideWith = Collision::BoundingBoxTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                }

            }

            // en cas de collision...
            if(collideWith)
            {

                //declenche le trigger de la deuxieme entité si il existe
                if(triggers->find(e2) != triggers->cend())
                {
                    triggers->at(e2)->onTrigger(e1, ch1.getTag());
                }
                //si on ne passe pas au travers de l'autre objet
                else if(!co1.isCrossable())
                {
                    //transfert de vitesse si l'autre entité c'est un personnage
                    if(characters->find(e2) != characters->cend() && velocities->find(e2) != velocities->cend())
                    {
                        transfertVelocity(e1, e2, c2.getImpactAbsorption());
                    }
                    //sinon evalue la vitesse pour soit rebondir, soit appliquer des contraintes
                    else
                    {
                            addCollisionConstraints(r1.getSpriteRef(), r2.getSpriteRef(), e1);
                            floorBouncing(e1, e2, c2.getImpactAbsorption());
                            floorBounce = true;
                    }
                }

                colliding = true;
            }
        }

        if(!colliding && constraints->find(e1) != constraints->cend()) //si il n'y a pas eu de collision, on retire les contraintes
        {
                removeCollisionConstraints(e1);
        }

        //on remet le sprite a sa position d'origine
        r1.getSpriteRef().move(-v1.getVelocity() * dt);


    }
}

void CollisionSystem::viewClamping()
{
    sf::Vector2f viewSize = view->getSize();
    sf::Vector2f viewCenter = view->getCenter();
    sf::Vector2f levelSize = sf::Vector2f(TILE_WIDTH * MAP_WIDTH, TILE_HEIGHT * MAP_HEIGHT);

    if(viewCenter.x - viewSize.x/2 < 0) //trop a gauche
    {
        view->setCenter(viewSize.x/2, viewCenter.y);
    }
    if(viewCenter.y - viewSize.y/2 < 0) //trop en haut
    {
        view->setCenter(view->getCenter().x, viewSize.y/2);
    }
    if(viewCenter.x + viewSize.x/2 > levelSize.x) // trop a droite
    {
        view->setCenter(levelSize.x - viewSize.x/2, view->getCenter().y);

    }
    if(viewCenter.y + viewSize.y/2 > levelSize.y) // trop en bas
    {
        view->setCenter(view->getCenter().x, levelSize.y - viewSize.y/2);
    }
}

bool CollisionSystem::addViewBorderConstraints(sf::Sprite s, Entity entity)
{
    ConstraintComponent& c = *(constraints->at(entity));
    sf::FloatRect gb = s.getGlobalBounds();
    sf::Vector2f p = s.getPosition();

    sf::Vector2f viewSize = view->getSize();
    sf::Vector2f viewCenter = view->getCenter();

    bool colliding = false;

    if(p.x + gb.width > viewCenter.x + (viewSize.x / 2)) //collision à droite
    {
        c.addConstraint(ConstraintEnum::Right);
        colliding = true;
    }
    if(p.y > viewCenter.y + (viewSize.y / 2)) //collision en bas
    {
        ComponentManagerSingleton::getInstance()->addComponentToEntity(*(new RespawnComponent()), RespawnComponent::ID, entity);
        colliding = true;
    }
    if(viewCenter.x - (viewSize.x / 2) > p.x) //collision à gauche
    {
        c.addConstraint(ConstraintEnum::Left);
        colliding = true;
    }
    if(viewCenter.y - (viewSize.y / 2) > p.y) //collision en haut
    {
        c.addConstraint(ConstraintEnum::Up);
        colliding = true;
    }

    return colliding;
}

//ajoute les contraintes adéquates en fonction de la direction de la collision
void CollisionSystem::addCollisionConstraints(sf::Sprite s1, sf::Sprite s2, Entity entity)
{
    ConstraintComponent& c = *(constraints->at(entity));

    sf::Vector2 p1 = s1.getPosition();
    sf::Vector2 p2 = s2.getPosition();

    float angle = Vector2fMath::angleBetween(p2, p1) * 180 / M_PI;

    if(angle > 120 || angle <= -120)//collision en bas
    {
        c.addConstraint(ConstraintEnum::Down);
    }else if(angle <= -30 && angle > -120) // collision a droite
    {
        c.addConstraint(ConstraintEnum::Right);
    }else if(angle <= 120 && angle > 30) // collision à gauche
    {
        c.addConstraint(ConstraintEnum::Left);
    }else //collision en haut
    {
        c.addConstraint(ConstraintEnum::Up);
    }
}

void CollisionSystem::removeCollisionConstraints(Entity entity)
{

    ConstraintComponent& c = *(constraints->at(entity));
    c.removeConstraint(ConstraintEnum::Right);
    c.removeConstraint(ConstraintEnum::Down);
    c.removeConstraint(ConstraintEnum::Up);
    c.removeConstraint(ConstraintEnum::Left);
}

void CollisionSystem::transfertVelocity(Entity e1, Entity e2, float absorption)
{
    sf::Sprite& s1 = renderers->at(e1)->getSpriteRef();
    sf::Sprite& s2 = renderers->at(e2)->getSpriteRef();

    VelocityComponent& v1 = *(velocities->at(e1));
    VelocityComponent& v2 = *(velocities->at(e2));

    float angle12 = Vector2fMath::angleBetween(s1.getPosition(), s2.getPosition());
    float angle21 = Vector2fMath::angleBetween(s2.getPosition(), s1.getPosition());
    float speed = Vector2fMath::magnitude(v1.getVelocity());

    sf::Vector2f dv2 = sf::Vector2f(v1.getVelocity().x * std::sin(angle12) * absorption, v1.getVelocity().y * std::cos(angle12) * absorption);
    sf::Vector2f dv1 = sf::Vector2f(speed * std::sin(angle21) * (1+absorption), speed * std::cos(angle21) * (1+absorption));
    v2.addVelocity(dv2);
    v1.addVelocity(dv1);
}

void CollisionSystem::floorBouncing(Entity character, Entity platform, float absorption)
{
    ConstraintComponent& c = *(constraints->at(character));

    sf::Sprite& s1 = renderers->at(character)->getSpriteRef();
    sf::Sprite& s2 = renderers->at(platform)->getSpriteRef();

    VelocityComponent& v = *(velocities->at(character));

    float angle;
    sf::Vector2f dv = sf::Vector2f(0, 0);

    if(c.hasConstraint(ConstraintEnum::Down))
    {
        dv += sf::Vector2((float)0., -v.getVelocity().y * (1+(1-absorption)));
    }
    if(c.hasConstraint(ConstraintEnum::Up))
    {
        dv += sf::Vector2((float)0., -v.getVelocity().y * (1+(1-absorption)));

    }
    if(c.hasConstraint(ConstraintEnum::Left))
    {
        dv += sf::Vector2(-v.getVelocity().x * (1+(1-absorption)), (float)0.0);

    }
    if(c.hasConstraint(ConstraintEnum::Right))
    {
        dv += sf::Vector2(-v.getVelocity().x * (1+(1-absorption)), (float)0.0);

    }
    v.addVelocity(dv);
}













