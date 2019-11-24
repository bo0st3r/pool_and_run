#include "UIComponent.h"

UIComponent::UIComponent(UITypeEnum type, int data)
:UIType(type), dataValue(data)
{}

UIComponent::~UIComponent()
{}

ComponentID UIComponent::getTypeId() const
{
    return ID;
}

UITypeEnum UIComponent::getUIType() const
{
    return UIType;
}

int UIComponent::getDataValue() const
{
    return dataValue;
}

std::string UIComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (UI) : type = " << UIType;
    return sstr.str();
}
