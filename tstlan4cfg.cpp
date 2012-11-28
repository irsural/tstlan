#include <irspch.h>
#pragma hdrstop

#include <tstlan4lib.h>
#include <irsstd.h>
#include <irsstring.h>
#include <irstime.h>

#include "tstlan4cfg.h"

#include <irsfinal.h>

tstlan4::cfg_t::cfg_t(TForm* ap_form):
  m_ini_name(irst("tstlan4.ini")),
  m_update_time(irs::make_cnt_ms(100)),
  mp_tstlan4lib(IRS_NULL),
  #ifdef NOP
  mp_tstlan4lib(
    new irs::tstlan4_t(
      irs::tstlan4_t::ft_external,
      m_ini_name,
      irst(""),
      m_update_time,
      irs::tstlan4_t::global_log_connect
    )
  ),
  #endif //NOP
  mp_mxnet_client_hardflow(IRS_NULL/*irs::hardflow::make_udp_flow_client(
    irst("127.0.0.1"), 5005)*/),
  mp_mxnet_server_hardflow(irs::hardflow::make_udp_flow_server(5005)),
  mp_form(ap_form),
  mp_options_form(new TOptionsForm(ap_form))
{
  #ifdef NOP
  irs::tstlan4_t* p_tstlan4lib_cb =
    static_cast<irs::tstlan4_t*>(mp_tstlan4lib.get());
  p_tstlan4lib_cb->init(ap_form);
  #endif //NOP
}
irs::tstlan4_base_t* tstlan4::cfg_t::tstlan4lib()
{
  mp_tstlan4lib.reset();
  mp_tstlan4lib.reset(new irs::tstlan4_t(
    irs::tstlan4_t::ft_external,
    m_ini_name,
    irst(""),
    m_update_time,
    irs::tstlan4_t::global_log_connect
  ));
  irs::tstlan4_t* p_tstlan4lib_cb =
    static_cast<irs::tstlan4_t*>(mp_tstlan4lib.get());
  p_tstlan4lib_cb->init(mp_form);
  return mp_tstlan4lib.get();
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
options_form_t* tstlan4::cfg_t::options_form()
{
  return mp_options_form->data();
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

