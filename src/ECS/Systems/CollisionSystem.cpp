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
                        sf::View& v,
                        std::unordered_map<int, Entity>& tem
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

    tileEntityMap = &tem;

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

    delete tileEntityMap;
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

        //trouve la tile du sprite du personnage sur la tilemap
        sf::Vector2i tmPosition = sf::Vector2i((int)(r1.getSpriteRef().getPosition().x / TILE_WIDTH), (int)(r1.getSpriteRef().getPosition().y / TILE_HEIGHT));

        //y a-t-il eu une collision?
        bool colliding = false;

        //centre la caméra sur le joueur et test de collision avec les bords de la vue (pour le joueur uniquement)
        if(ch1.getTag() == "Joueur")
        {
            view->setCenter(p1.getPosition());
            viewClamping();
            colliding = addViewBorderConstraints(r1.getSpriteRef(), e1);
        }

        //test de collision avec le terrain (les 8 tiles adjacentes a celles du personnage et celle ou il se trouve)
        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {

                Entity e2 = EntityManagerSingleton::MAX_ENTITY;
                int tablePos = tmPosition.x + i + (tmPosition.y + j) * MAP_WIDTH;

                if(tileEntityMap->find(tablePos) != tileEntityMap->cend())
                {
                    e2 = (*tileEntityMap)[tablePos];
                }

                if(e2 != EntityManagerSingleton::MAX_ENTITY && colliders->find(e2) != colliders->cend())
                {
                    PositionComponent& p2 = *(positions->at(e2));
                    ColliderComponent& co2 = *(colliders->at(e2));
                    RendererComponent& r2 = *(renderers->at(e2));
                    if(tryCollision(e1, p1, co1, r1, ch1, e2, p2, co2, r2))
                    {
                        colliding = true;
                    }
                }

            }
        }

        //test de collision avec les autres personnages
        for(Characters::iterator it2 = characters->begin(); it2 != characters->cend(); it2++)
        {
            Entity e2 = it2->first;
            //on passe l'entité si c'est la même que celle en cours
            if(e1 == e2)
            {
                continue;
            }
            PositionComponent& p2 = *(positions->at(e2));
            ColliderComponent& co2 = *(colliders->at(e2));
            RendererComponent& r2 = *(renderers->at(e2));
            if(tryCollision(e1, p1, co1, r1, ch1, e2, p2, co2, r2))
            {
                colliding = true;
            }
        }

        //test de collision avec les trigger (autre que la queue deja testée dans personnage)
        for(Triggers::iterator it2 = triggers->begin(); it2 != triggers->cend(); it2++)
        {
            Entity e2 = it2->first;
            //on passe l'entité si c'est la même que celle en cours ou si c'est un personnage (les trigger des personnages etant declenchés à la boucle précédente)
            if(e1 == e2 && characters->find(e2) != characters->cend())
            {
                continue;
            }
            PositionComponent& p2 = *(positions->at(e2));
            ColliderComponent& co2 = *(colliders->at(e2));
            RendererComponent& r2 = *(renderers->at(e2));
            if(tryCollision(e1, p1, co1, r1, ch1, e2, p2, co2, r2))
            {
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

    if(angle < -30 && angle >= -150)//collision en bas
    {
        c.addConstraint(ConstraintEnum::Down);
    }else if(angle < 45 && angle >= -30) // collision a gauche
    {
        c.addConstraint(ConstraintEnum::Left);
    }else if(angle < 135 && angle >= 45) // collision en haut
    {
        c.addConstraint(ConstraintEnum::Up);
    }else //collision à droite
    {
        c.addConstraint(ConstraintEnum::Right);
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

    sf::Vector2f deltaSpeed = v1.getVelocity()-v2.getVelocity();

    float angleV12 = Vector2fMath::angle(deltaSpeed);
    float angleP12 = Vector2fMath::angleBetween(s1.getPosition(), s2.getPosition());

    float deltaAngle = angleP12 - angleV12;
    float deltaAngleInv = deltaAngle + M_PI;

    sf::Vector2f dv1 = sf::Vector2((deltaSpeed.x * std::cos(deltaAngle) + deltaSpeed.y * std::sin(deltaAngle)) * (-2+absorption), (deltaSpeed.x * std::sin(deltaAngle) + deltaSpeed.y * std::cos(deltaAngle)) * (-2+absorption));
    sf::Vector2f dv2 = sf::Vector2((deltaSpeed.x * std::cos(deltaAngle) + deltaSpeed.y * std::sin(deltaAngle)) * absorption, (deltaSpeed.x * std::sin(deltaAngle) + deltaSpeed.y * std::cos(deltaAngle)) * absorption);


    v1.addVelocity(dv1);
    v2.addVelocity(dv2);
}

void CollisionSystem::floorBouncing(Entity character, Entity platform, float absorption)
{
    ConstraintComponent& c = *(constraints->at(character));

    sf::Sprite& s1 = renderers->at(character)->getSpriteRef();
    sf::Sprite& s2 = renderers->at(platform)->getSpriteRef();

    VelocityComponent& v1 = *(velocities->at(character));

    if(c.hasConstraint(ConstraintEnum::Up) && Vector2fMath::magnitude(sf::Vector2f(0, v1.getVelocity().y)) > minBouncingSpeed){
        c.removeConstraint(ConstraintEnum::Up);
        v1.addVelocity(0, v1.getVelocity().y * (absorption-2));
    }
    if(c.hasConstraint(ConstraintEnum::Left) && Vector2fMath::magnitude(sf::Vector2f(v1.getVelocity().x, 0)) > minBouncingSpeed){
        c.removeConstraint(ConstraintEnum::Left);
        v1.addVelocity(v1.getVelocity().x * (absorption-2), 0);
    }
    if(c.hasConstraint(ConstraintEnum::Down) && Vector2fMath::magnitude(sf::Vector2f(0, v1.getVelocity().y)) > minBouncingSpeed){
        c.removeConstraint(ConstraintEnum::Down);
        v1.addVelocity(0, v1.getVelocity().y * (absorption-2));
    }
    if(c.hasConstraint(ConstraintEnum::Right) && Vector2fMath::magnitude(sf::Vector2f(v1.getVelocity().x, 0)) > minBouncingSpeed){
        c.removeConstraint(ConstraintEnum::Right);
        v1.addVelocity(v1.getVelocity().x * (absorption-2), 0);
    }
    /*
    float deltaAngle = (angleP12 - angleV12) * 180 / M_PI;

    if(deltaAngle < -30 && deltaAngle >= -150)//collision en bas
    {
        if(Vector2fMath::magnitude(sf::Vector2f(0, v1.getVelocity().y)) > minBouncingSpeed){canBounce = true;}
        deltaAngle = -M_PI / 2;
    }else if(deltaAngle < 45 && deltaAngle >= -30) // collision a gauche
    {
        if(Vector2fMath::magnitude(sf::Vector2f(v1.getVelocity().x, 0)) > minBouncingSpeed){canBounce = true;}
        deltaAngle = M_PI;
    }else if(deltaAngle < 135 && deltaAngle >= 45) // collision en haut
    {
        deltaAngle = -M_PI / 2;
    }else //collision à droite
    {
        if(Vector2fMath::magnitude(sf::Vector2f(v1.getVelocity().x, 0)) > minBouncingSpeed){canBounce = true;}
        deltaAngle = M_PI;
    }


    hasBounce = true;
    sf::Vector2f dv = sf::Vector2(v1.getVelocity().x * std::cos(deltaAngle) * (1+1-absorption), v1.getVelocity().y * std::sin(deltaAngle) * (1+1-absorption));
    v1.addVelocity(dv);
    */
}

bool CollisionSystem::tryCollision( Entity e1, PositionComponent& p1, ColliderComponent& co1, RendererComponent& r1, CharacterComponent& ch1,
                                    Entity e2, PositionComponent& p2, ColliderComponent& co2, RendererComponent& r2)
{
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
                transfertVelocity(e1, e2, co2.getImpactAbsorption());
            }
            //sinon evalue la vitesse pour soit rebondir, soit appliquer des contraintes
            else
            {
                    addCollisionConstraints(r1.getSpriteRef(), r2.getSpriteRef(), e1);
                    floorBouncing(e1, e2, co2.getImpactAbsorption());

            }
        }

    }

    return collideWith;
}













