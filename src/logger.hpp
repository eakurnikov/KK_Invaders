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
#include <exception>
#include <fstream>

using namespace std;

class Logger: public Singleton<Logger>
{
public:

  template <typename T>
  void Log(T obj)
  {
    m_file.open("Log.txt", ios::app);
    if (m_file.is_open())
    {
      m_file << obj;
      m_file.close();
    }
  }

  template <typename EntityType>
  void Log(EntityType & entity, ActionType actionType)
  {
    m_file.open("Log.txt", ios::app);
    if (m_file.is_open())
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
      m_file << entity << action << endl;
      m_file.close();
    }
  }

  template <typename EntityType, typename parameter>
  void Log(EntityType & entity, ActionType actionType, parameter param)
  {
    m_file.open("Log.txt", ios::app);
    if (m_file.is_open())
    {
      string action = "";
      switch(actionType)
      {
        case ActionType::Creation:
          action = "Created";
          m_file << entity << action << ": " << param << " points" << endl;
          break;
        case ActionType::CauseDamage:
          action = "Caused damage";
          m_file << entity << action << ": " << param << " points" << endl;
          break;
        case ActionType::SufferDamage:
          action = "Suffered damage";
          m_file << entity << action << ": " << param << " points" << endl;
          break;
        case ActionType::Destroying:
          action = "Destroyed";
          m_file << entity << action << ": " << param << " points" << endl;
          break;
        case ActionType::Shot:
          action = "Shoots";
          m_file << entity << action << ": " << param << " points" << endl;
          break;
        default:
          action = "";
      }
      m_file.close();
    }
  }

  template <typename EntityType, template<typename, typename> class C>
  void Log(C <EntityType, std::allocator<EntityType>> const & objs, ActionType actionType)
  {
    m_file.open("Log.txt", ios::app);
    if (m_file.is_open())
    {
      for (auto const & obj : objs)
        Log(obj, actionType);
      m_file.close();
    }
  }

private:

  friend class Singleton<Logger>;

  Logger() = default;

  std::ofstream m_file;
};
