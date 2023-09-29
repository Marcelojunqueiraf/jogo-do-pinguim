#include "Component.hpp"
#include <iostream>

Component::Component(GameObject *associated)
{
  this->associated = associated;
}

Component::~Component()
{
}