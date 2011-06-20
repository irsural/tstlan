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

namespace tstlan4 {

bool find_device(const irs::string_t& a_name, irs::string_t* ap_type);
irs::handle_t<irs::mxdata_assembly_t> make_assembly(
  irs::tstlan4_base_t* ap_tstlan4lib,
  options_form_t* ap_options_form
);

} //namespace tstlan4

bool find_device(const irs::string_t& a_name, irs::string_t* ap_type)
{
  //for (size
}

irs::handle_t<irs::mxdata_assembly_t> tstlan4::make_assembly(
  irs::tstlan4_base_t* ap_tstlan4lib,
  options_form_t* ap_options_form
) {
  if (ap_options_form->device_count() != 0) {
    irs::string_t current_device = ap_options_form->general_options()->
      get_param(irst("Текущее устройство"));
    return irs::mxdata_assembly_types()->
      make_assembly(irst("mxnet"), ap_tstlan4lib, current_device);
  } else {
    return IRS_NULL;
  }
}

tstlan4::app_t::app_t(cfg_t* ap_cfg):
  mp_cfg(ap_cfg),
  mp_tstlan4lib(mp_cfg->tstlan4lib()),
  mp_options_form(mp_cfg->options_form()),
  //m_mxnet_client(mp_cfg->mxnet_client_hardflow(), mp_cfg->update_time()),
  m_mxnet_client_data(IRS_NULL/*&m_mxnet_client*/),
  m_mxnet_server_data(),
  m_mxnet_server(mp_cfg->mxnet_server_hardflow(),
    m_mxnet_server_data.size()/sizeof(irs_i32)),
  m_options_event(),
  m_is_mxnet_server_first_connected(true),
  mp_mxdata_assembly(irs::mxdata_assembly_types()->
    make_assembly(irst("mxnet"), mp_tstlan4lib, irst("У309М")))
{
  m_mxnet_server_data.connect(&m_mxnet_server);
  m_mxnet_client_data.connect(mp_mxdata_assembly->mxdata());
  //mp_tstlan4lib->connect(&m_mxnet_client);
  mp_tstlan4lib->options_event_connect(&m_options_event);
}
void tstlan4::app_t::tick()
{
  for (int i = 0; i < 5; i++) {
    //m_mxnet_client.tick();
    mp_mxdata_assembly->tick();
    m_mxnet_server.tick();
  }

  if (m_mxnet_server.connected()) {
    if (m_is_mxnet_server_first_connected) {
      m_is_mxnet_server_first_connected = false;
      m_mxnet_server_data.year = 2011;
      m_mxnet_server_data.month = 4;
    } else {
      m_mxnet_server_data.counter++;
    }
  }

  if (mp_mxdata_assembly->mxdata()->connected()) {
    m_mxnet_client_data.month++;
    mp_tstlan4lib->tick();
  }

  if (m_options_event.check()) {
    mp_options_form->show();
  }

  if (mp_options_form->is_device_options_button_click()) {
    mp_mxdata_assembly->show_options();
  }
}

