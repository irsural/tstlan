#include <irspch.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif // __BORLANDC__

#include "locktick.h"

#include <irsfinal.h>

tstlan4::lock_t* tstlan4::tick_lock()
{
  static lock_t tick_lock_obj;
  return &tick_lock_obj;
}

