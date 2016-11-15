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
#include "singleton.hpp"
#include <initializer_list>
#include <functional>
#include <ostream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Logger: public Singleton<Logger>
{
public:

  template <typename T>
  std::ostream & Log(T obj, std::ostream & os)
  {
    os << obj;
    return os;
  }

  template <typename EntityType>
  std::ostream & Log(EntityType & entity, ActionType actionType, std::ostream & os)
  {
    string action = "";
    switch(actionType)
    {
      case ActionType::Creation:
        action = "Created";
        break;
      case ActionType::CauseDamage:
        action = "Caused damage";
        break;
      case ActionType::SufferDamage:
        action = "Suffered damage";
        break;
      case ActionType::Destroying:
        action = "Destroyed";
        break;
      case ActionType::Shot:
        action = "Shoots";
        break;
      default:
        action = "";
    }

    os << entity << action << endl;

    return os;
  }

  template <typename EntityType, typename parameter>
  std::ostream & Log(EntityType & entity, ActionType actionType, parameter param, std::ostream & os)
  {
    string action = "";
    switch(actionType)
    {
      case ActionType::Creation:
        action = "Created";
        break;
      case ActionType::CauseDamage:
        action = "Caused damage";
        os << entity << action << ": " << param << " points" << endl;
        return os;
        break;
      case ActionType::SufferDamage:
        action = "Suffered damage";
        os << entity << action << ": " << param << " points" << endl;
        return os;
        break;
      case ActionType::Destroying:
        action = "Destroyed";
        break;
      case ActionType::Shot:
        action = "Shoots";
        break;
      default:
        action = "";
    }

    os << entity << action << endl;

    return os;
  }

  template <typename EntityType, template<typename, typename> class C>
  std::ostream & Log(C <EntityType, std::allocator<EntityType>> const & objs, ActionType actionType, std::ostream & os)
  {
    for (auto const & obj : objs)
      Log(obj, actionType, os);

    return os;
  }

private:

  friend class Singleton<Logger>;

  Logger() = default;
};
