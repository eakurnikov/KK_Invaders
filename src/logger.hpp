#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include "gameentity.hpp"
#include "alien.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "obstacle.hpp"
#include "space.hpp"
#include <initializer_list>
#include <functional>
#include <ostream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
class Logger
{
public:
  template <typename T>
  static std::ostream & Log(T obj, std::ostream & os)
  {
    os << obj;
    return os;
  }

  template <typename EntityType>
  static std::ostream & Log(EntityType entity, ActionType actionType, std::ostream & os)
  {
    string action = "";
    switch(actionType)
    {
      case ActionType::Creation:
        action = "Created ";
        break;
      case ActionType::CauseDamage:
        action = "Caused damage ";
        break;
      case ActionType::SufferDamage:
        action = "Suffered damage ";
        break;
      case ActionType::Destroying:
        action = "Destroyed ";
        break;
      case ActionType::Shot:
        action = "Shoots ";
        break;
      default:
        action = "";
    }

    os << "--------------" << endl
       << action << entity
       << "--------------" << endl;

    return os;
  }

  template <typename EntityType, template<typename, typename> class C>
  static std::ostream & Log(C <EntityType, std::allocator<EntityType>> const & objs, ActionType actionType, std::ostream & os)
  {
    for (auto const & obj : objs)
      Log(obj, actionType, os);

    return os;
  }

private:
  Logger();
};
