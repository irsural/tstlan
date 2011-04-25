#ifndef tstlan4appH
#define tstlan4appH

#include <irsdefs.h>

#include <mxnetc.h>
#include <mxnet.h>
#include <timer.h>
#include <mxdata.h>
#include <irsint.h>

#include "tstlan4cfg.h"

#include <irsfinal.h>

namespace tstlan4 {

struct mxnet_vars_data_t
{
private:
  size_t m_size;
public:
  irs::conn_data_t<irs_u32> counter;
  irs::conn_data_t<irs_u32> year;
  irs::conn_data_t<irs_u32> month;

  mxnet_vars_data_t(irs::mxdata_t *ap_data = IRS_NULL)
  {
    connect(ap_data);
  }
  size_t size()
  {
    return m_size;
  }
  void connect(irs::mxdata_t *ap_data = IRS_NULL)
  {
    m_size = 0;
    m_size = counter.connect(ap_data, m_size);
    m_size = year.connect(ap_data, m_size);
    m_size = month.connect(ap_data, m_size);
  }
};

class app_t
{
public:
  app_t(cfg_t* ap_cfg);
  void tick();
private:
  cfg_t* mp_cfg;
  irs::tstlan4_base_t* mp_tstlan4lib;
  irs::mxnetc_data_t m_mxnet_client;
  mxnet_vars_data_t m_mxnet_client_data;
  mxnet_vars_data_t m_mxnet_server_data;
  irs::mxnet_t m_mxnet_server;
  irs::event_t m_options_event;
  irs::local_data_t m_dbg_data;
};

} //namespace tstlan4

#endif //tstlan4appH
