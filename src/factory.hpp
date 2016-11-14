#include "singleton.hpp"
#include <memory>

class Factory : public Singleton<Factory>
{
public:

  template <typename T, typename ... Args>
  std::unique_ptr<T> Create(Args && ... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }

private:

  friend class Singleton<Factory>;

  Factory() = default;
};
