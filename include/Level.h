#ifndef LEVEL_H
#define LEVEL_H

#include<string>

using std::string;


class Level
{
    public:
        Level(string name);
        virtual ~Level();
        Level(const Level& other);

    protected:

    private:
        int* id;
        static inline int lastId = 0;
        string name;
};

#endif // LEVEL_H
