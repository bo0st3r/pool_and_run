#ifndef CHARACTERCOMPONENT_H
#define CHARACTERCOMPONENT_H

#include <Component.h>


class CharacterComponent : public Component
{
    public:
        CharacterComponent(std::string myName, std::string tag);
        virtual ~CharacterComponent();

        virtual ComponentID getTypeId() const;
        std::string getMyName() const;
        std::string getTag() const;

        virtual std::string str() const;

        static inline const ComponentID ID = 6;


    protected:

    private:
        std::string myName;
        std::string tag;
};

#endif // CHARACTERCOMPONENT_H
