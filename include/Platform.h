#ifndef PLATFORM_H
#define PLATFORM_H

#include <LevelElement.h>


class Platform : public LevelElement
{
    public:
        Platform();
        virtual ~Platform();
        Platform(const Platform& other);

    protected:

    private:
};

#endif // PLATFORM_H
