#include <irspch.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif // __BORLANDC__

#include <locale.h>

#include <irsstrdefs.h>
#include <irserror.h>
#include <irscpp.h>
#include <irstest.h>
#include <irssysutils.h>
#include <mxifa.h>

#include "tstlan4app.h"

#include <irsfinal.h>

tstlan4::app_t::app_t(cfg_t* ap_cfg):
  mp_cfg(ap_cfg),
  mp_tstlan4lib(mp_cfg->tstlan4lib()),
  #ifdef OLD_MXNET_CLIENT
  m_mxnet_client(MXIFA_MXNETC, irs::make_cnt_s(2),
    mp_cfg->update_time()),
  #else //OLD_MXNET_CLIENT
  m_mxnet_client(mp_cfg->mxnet_client_hardflow(), mp_cfg->update_time()),
  #endif //OLD_MXNET_CLIENT
  m_mxnet_client_data(&m_mxnet_client),
  m_mxnet_server_data(),
  m_mxnet_server(mp_cfg->mxnet_server_hardflow(),
    m_mxnet_server_data.size()/sizeof(irs_i32)),
  m_options_event(),
  m_dbg_data(16)
{
  m_mxnet_server_data.connect(&m_mxnet_server);
  m_mxnet_server_data.year = 2011;
  m_mxnet_server_data.month = 4;
  #ifdef OLD_MXNET_CLIENT
  m_mxnet_client.ip(irs::make_mxip(127, 0, 0, 1));
  //m_mxnet_client.ip(irs::make_mxip(192, 168, 1, 148));
  //m_mxnet_client.ip(irs::make_mxip(192, 168, 0, 190));
  m_mxnet_client.port(5005);
  #endif //
  mp_tstlan4lib->connect(&m_mxnet_client);
  mp_tstlan4lib->options_event_connect(&m_options_event);
}
void tstlan4::app_t::tick()
{
  for (int i = 0; i < 5; i++) {
    m_mxnet_client.tick();
    m_mxnet_server.tick();
  }

  m_mxnet_server_data.counter++;

  if (m_mxnet_client.connected()) {
    m_mxnet_client_data.month++;
    mp_tstlan4lib->tick();
  }

  if (m_options_event.check()) {
    mp_cfg->options_show();
  }
}

