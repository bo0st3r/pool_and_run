#ifndef GAMEMANAGERSINGLETON_H
#define GAMEMANAGERSINGLETON_H

#include<Level.h>


class GameManagerSingleton
{
    public:
        GameManagerSingleton();
        virtual ~GameManagerSingleton();
        GameManagerSingleton(const GameManagerSingleton& other);
        void AddLevel(Level l);
        void LoadLevel(int id);

    protected:

    private:
        Level levels[5];

};

#endif // GAMEMANAGERSINGLETON_H
