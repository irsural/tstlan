#ifndef tstlan4cfgH
#define tstlan4cfgH

#include <irsdefs.h>

#include <forms.hpp>

#include <tstlan4abs.h>
#include <mxdata.h>
#include <mxnet.h>
#include <mxnetc.h>
#include <irsdefs.h>
#include <irscpp.h>
#include <irsstrdefs.h>
#include <hardflowg.h>
#include <irsparam.h>

#include "devices.h"

#include <irsfinal.h>

namespace tstlan4 {

class test_t
{
public:
  test_t();
  void tick();
private:
  bool m_is_test_on;
  size_t m_var_count;
  irs_u16 m_server_port;
  counter_t m_update_time;
  irs::handle_t<irs::hardflow_t> mp_mxnet_server_hardflow;
  irs::mxnet_t m_mxnet_server;
  irs::handle_t<irs::hardflow_t> mp_mxnet_client_hardflow;
  irs::handle_t<irs::mxdata_t> mp_mxnet_client;
  irs::conn_data_t<irs_u32> m_test_var_server;
  irs::conn_data_t<irs_u32> m_test_var_client;
  irs::change_data_t<irs_u32> m_test_var_server_change;
  bool m_is_server_on;
  irs::timer_t m_wait_timer;
  irs::event_t m_start_event;
};

class cfg_t
{
public:
  typedef irs::string_t string_type;
  cfg_t();
  irs::handle_t<irs::param_box_base_t> make_options_param_box();
  irs::handle_t<irs::tstlan4_base_t> make_tstlan4lib(
    irs::chart_window_t* ap_chart);
  irs::handle_t<irs::chart_window_t> make_chart();
  counter_t update_time() const;
  string_type ini_name() const;
  irs::hardflow_t& mxnet_client_hardflow();
  irs::hardflow_t& mxnet_server_hardflow();
private:
  string_type m_ini_name;
  irs::mxdata_assembly_params_t m_mxdata_assembly_params;
  counter_t m_update_time;
  irs::handle_t<irs::hardflow_t> mp_mxnet_client_hardflow;
  irs::handle_t<irs::hardflow_t> mp_mxnet_server_hardflow;
};

} //namespace tstlan4

#endif //tstlan4cfgH
