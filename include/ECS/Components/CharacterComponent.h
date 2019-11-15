#ifndef CHARACTERCOMPONENT_H
#define CHARACTERCOMPONENT_H

#include <Component.h>


class CharacterComponent : public Component
{
    public:
        CharacterComponent(std::string myName = "", std::string tag = "unknown", int live = 0);
        virtual ~CharacterComponent();

        virtual ComponentID getTypeId() const;
        std::string getMyName() const;
        std::string getTag() const;
        int getLive() const;

        void addLive(int amount);

        virtual std::string str() const;

        static inline const ComponentID ID = 6;


    protected:

    private:
        std::string myName;
        std::string tag;
        int live;
};

#endif // CHARACTERCOMPONENT_H
