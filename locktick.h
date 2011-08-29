#ifndef locktickH
#define locktickH

#include <irsdefs.h>

#include <irsfinal.h>

namespace tstlan4 {

class lock_t
{
  bool m_is_lock;
public:
  lock_t():
    m_is_lock(false)
  {
  }
  void enable()
  {
    m_is_lock = true;
  }
  void disable()
  {
    m_is_lock = false;
  }
  bool check()
  {
    return m_is_lock;
  }
};

lock_t* tick_lock();

} //namespace tstlan4

#endif //locktickH
