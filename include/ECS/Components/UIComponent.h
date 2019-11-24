#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <Component.h>
#include <UITypeEnum.h>


class UIComponent : public Component
{
    public:
        UIComponent(UITypeEnum type = UITypeEnum::HealthBar, int data = -1);
        virtual ~UIComponent();
        static inline const ComponentID ID = 10;

        virtual ComponentID getTypeId() const;
        UITypeEnum getUIType() const;
        int getDataValue() const;

        virtual std::string str() const;

    protected:

    private:
        UITypeEnum UIType;
        int dataValue;
};

#endif // UICOMPONENT_H
