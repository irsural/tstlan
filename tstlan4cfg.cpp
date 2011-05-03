#include <irspch.h>
#pragma hdrstop

#include <tstlan4lib.h>
#include <irsstd.h>

#include "tstlan4cfg.h"

tstlan4::cfg_t::cfg_t(TForm* ap_form):
  m_ini_name(irst("tstlan4.ini")),
  m_update_time(irs::make_cnt_ms(100)),
  mp_tstlan4lib(
    new irs::tstlan4_t(
      irs::tstlan4_t::ft_external,
      m_ini_name,
      irst(""),
      m_update_time,
      irs::tstlan4_t::global_log_connect
    )
  ),
  mp_mxnet_client_hardflow(irs::hardflow::make_udp_flow_client(
    irst("127.0.0.1"), 5005)),
  mp_mxnet_server_hardflow(irs::hardflow::make_udp_flow_server(5005)),
  mp_options_form(new TOptionsForm(ap_form))
{
  irs::tstlan4_t* p_tstlan4lib_cb =
    static_cast<irs::tstlan4_t*>(mp_tstlan4lib.get());
  p_tstlan4lib_cb->init(ap_form);
}
irs::tstlan4_base_t* tstlan4::cfg_t::tstlan4lib()
{
  return mp_tstlan4lib.get();
}
counter_t tstlan4::cfg_t::update_time() const
{
  return m_update_time;
}
void tstlan4::cfg_t::options_show()
{
  mp_options_form->ShowModal();
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

