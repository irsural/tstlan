#ifndef tstlan4appH
#define tstlan4appH

#include <irsdefs.h>

#include <mxnetc.h>
#include <timer.h>
#include <mxdata.h>
#include <irsint.h>

#include "tstlan4cfg.h"

#include <irsfinal.h>

namespace tstlan4 {

class app_t
{
public:
  app_t(cfg_t* ap_cfg);
  void tick();
private:
  cfg_t* mp_cfg;
  irs::mxnetc_data_t m_mnetc_data;
  irs::tstlan4_base_t* mp_tstlan4lib;
  irs::local_data_t m_dbg_data;
  irs::event_t m_options_event;
};

} //namespace tstlan4

#endif //tstlan4appH
