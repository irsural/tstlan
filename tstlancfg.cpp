#include <irspch.h>
#pragma hdrstop

#include <tstlan4lib.h>
#include <tstlan5lib.h>
#include <irsstd.h>
#include <irsstring.h>
#include <irstime.h>

#include "tstlancfg.h"

#include <irsfinal.h>

tstlan4::cfg_t::cfg_t():
  m_ini_name(irst("tstlan.ini")),
  m_update_time(irs::make_cnt_ms(100)),
  mp_mxnet_client_hardflow(IRS_NULL),
  mp_mxnet_server_hardflow(irs::hardflow::make_udp_flow_server(5005))
{
}

irs::handle_t<irs::param_box_base_t> tstlan4::cfg_t::make_options_param_box()
{
  irs::handle_t<irs::param_box_base_t> options(
    new irs::param_box_t(irst("Опции"), irst("options")));
  return options;
}

irs::handle_t<irs::tstlan4_base_t> tstlan4::cfg_t::make_tstlan4lib(
  irs::chart_window_t* ap_chart)
{
  irs::handle_t<irs::tstlan4_base_t> tstlan4lib(new irs::tstlan::view_t(
    irs::tstlan::view_t::ft_internal,
    ap_chart,
    m_ini_name,
    string_type(),
    m_update_time,
    irs::tstlan::view_t::global_log_unchange));
  return tstlan4lib;
}

irs::handle_t<irs::chart_window_t> tstlan4::cfg_t::make_chart()
{
  irs::handle_t<irs::chart_window_t> chart_window(
    new irs::chart::builder_chart_window_t(10000, 1000,
    irs::chart::builder_chart_window_t::stay_on_top_off));
  return chart_window;
}

counter_t tstlan4::cfg_t::update_time() const
{
  return m_update_time;
}
tstlan4::cfg_t::string_type tstlan4::cfg_t::ini_name() const
{
  return m_ini_name;
}
irs::hardflow_t& tstlan4::cfg_t::mxnet_client_hardflow()
{
  return *mp_mxnet_client_hardflow;
}
irs::hardflow_t& tstlan4::cfg_t::mxnet_server_hardflow()
{
  return *mp_mxnet_server_hardflow;
}

tstlan4::test_t::test_t():
  m_is_test_on(false),
  m_var_count(100),
  m_server_port(5011),
  m_update_time(irs::make_cnt_ms(10)),
  mp_mxnet_server_hardflow(irs::hardflow::make_udp_flow_server(m_server_port)),
  m_mxnet_server(*mp_mxnet_server_hardflow, m_var_count),
  mp_mxnet_client_hardflow(irs::hardflow::make_udp_flow_client(
    irst("127.0.0.1"), irs::string_t(m_server_port))),
  mp_mxnet_client(new irs::mxnet_client_t(*mp_mxnet_client_hardflow,
    m_update_time)),
  m_test_var_server(&m_mxnet_server, 10),
  m_test_var_client(mp_mxnet_client.get(), m_test_var_server.index()),
  m_test_var_server_change(&m_test_var_server),
  m_is_server_on(true),
  m_wait_timer(),
  m_start_event()
{
  if (m_is_test_on) {
    m_start_event.exec();
    irs::mlog() << irs::sdatetime << "Тест mxnet" << endl;
  }
}
void tstlan4::test_t::tick()
{
  if (m_is_test_on) {
    if (m_is_server_on) {
      mp_mxnet_server_hardflow->tick();
      m_mxnet_server.tick();
    }
    mp_mxnet_client_hardflow->tick();
    mp_mxnet_client->tick();

    if (mp_mxnet_client->connected()) {
      if (m_start_event.check()) {
        m_is_server_on = false;
        irs::mlog() << irs::sdatetime << "Клиент содинился с сервером" << endl;
        m_test_var_client = 777;
        m_wait_timer.set(irs::make_cnt_s(2));
      }
      if (m_wait_timer.check()) {
        m_is_server_on = true;
      }
      if (m_test_var_server_change.changed()) {
        irs::mlog() << irs::sdatetime << "m_test_var_server = ";
        irs::mlog() << m_test_var_server << endl;
      }
    }
  } //if (m_is_test_on)
}

