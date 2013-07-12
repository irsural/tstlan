#ifndef tstlanappH
#define tstlanappH

#include <irsdefs.h>

#include <mxnetc.h>
#include <mxnet.h>
#include <timer.h>
#include <mxdata.h>
#include <irsint.h>
#include <irsdevices.h>

#include "tstlancfg.h"

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

struct device_options_t
{
  typedef irs::string_t string_type;
  string_type type;
  bool enabled;
  device_options_t():
    type(),
    enabled(false)
  {
    vector<string_type> type_list;
    irs::mxdata_assembly_types()->enum_types(&type_list);
    if (!type_list.empty()) {
      type = type_list.front();
    }
  }
};

class app_t
{
public:
  typedef std::size_t size_type;
  typedef irs::string_t string_type;
  app_t(cfg_t* ap_cfg);
  void set_devices(
    const std::map<string_type, device_options_t>& a_devices);
  void show_tstlan4lib(const string_type& a_name);
  void show_device_options(const string_type& a_name);
  void show_chart();
  void show_modal_options();
  void import(const string_type& a_source, const string_type& a_destination);
  void tick();
private:
  void apply_options();
  typedef irs::string_t string_type;
  struct device_t
  {
    string_type type;
    irs::handle_t<irs::tstlan4_base_t> tstlan4lib;
    irs::handle_t<irs::mxdata_assembly_t> mxdata_assembly;
  };
  cfg_t* mp_cfg;
  irs::handle_t<irs::param_box_base_t> mp_options_param_box;
  irs::handle_t<irs::chart_window_t> mp_chart;
  mxnet_vars_data_t m_mxnet_server_data;
  irs::mxnet_t m_mxnet_server;
  irs::event_t m_options_event;
  bool m_is_mxnet_server_first_connected;
  test_t m_test;
  std::map<string_type, device_t> m_devices_map;
  std::vector<irs::handle_t<irs::mxdata_assembly_t> >::iterator
    mp_current_mxdata_assembly;
};

} //namespace tstlan4

#endif //tstlan4appH
