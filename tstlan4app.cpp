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

bool find_device(options_form_t* ap_options_form,
  const irs::string_t& a_name, irs::string_t* ap_type);

irs::handle_t<irs::mxdata_assembly_t> make_assembly(
  irs::tstlan4_base_t* ap_tstlan4lib,
  options_form_t* ap_options_form
);

} //namespace tstlan4

bool tstlan4::find_device(options_form_t* ap_options_form,
  const irs::string_t& a_name, irs::string_t* ap_type)
{
  bool is_finded = false;
  for (size_t device_idx = 0; device_idx < ap_options_form->device_count();
    device_idx++)
  {
    if (ap_options_form->device_names(device_idx) == a_name) {
      *ap_type = ap_options_form->device_types(device_idx);
      is_finded = true;
      break;
    }
  }
  return is_finded;
}

irs::handle_t<irs::mxdata_assembly_t> tstlan4::make_assembly(
  irs::tstlan4_base_t* ap_tstlan4lib,
  options_form_t* ap_options_form
) {
  if (ap_options_form->device_count() != 0) {
    irs::string_t current_device = ap_options_form->general_options()->
      get_param(irst("Текущее устройство"));
    irs::string_t current_type = irst("");
    if (find_device(ap_options_form, current_device, &current_type)) {
      return irs::mxdata_assembly_types()->
        make_assembly(current_type, ap_tstlan4lib, current_device);
    } else {
      return IRS_NULL;
    }
  } else {
    return IRS_NULL;
  }
}

tstlan4::app_t::app_t(cfg_t* ap_cfg):
  mp_cfg(ap_cfg),
  mp_tstlan4lib(mp_cfg->tstlan4lib()),
  mp_options_form(mp_cfg->options_form()),
  m_mxnet_client_data(IRS_NULL),
  m_mxnet_server_data(),
  m_mxnet_server(mp_cfg->mxnet_server_hardflow(),
    m_mxnet_server_data.size()/sizeof(irs_i32)),
  m_options_event(),
  m_is_mxnet_server_first_connected(true),
  mp_mxdata_assembly(make_assembly(mp_tstlan4lib, mp_options_form))
{
  m_mxnet_server_data.connect(&m_mxnet_server);
  if (mp_mxdata_assembly.get()) {
    m_mxnet_client_data.connect(mp_mxdata_assembly->mxdata());
  }
  mp_tstlan4lib->options_event_connect(&m_options_event);
}
void tstlan4::app_t::tick()
{
  if (mp_mxdata_assembly.get()) {
    for (int i = 0; i < 5; i++) {
      mp_mxdata_assembly->tick();
    }
    if (mp_mxdata_assembly->mxdata()->connected()) {
      //m_mxnet_client_data.month++;
    }
    if (mp_options_form->is_options_apply()) {
      mp_mxdata_assembly = make_assembly(mp_tstlan4lib, mp_options_form);
      m_mxnet_client_data.connect(mp_mxdata_assembly->mxdata());
    }
    if (mp_options_form->is_device_options_button_click()) {
      mp_mxdata_assembly->show_options();
    }
    if (mp_options_form->is_import_button_click()) {
      irs::string_t section = mp_tstlan4lib->conf_section();
      irs::string_t ini_name = mp_tstlan4lib->ini_name();
      mp_tstlan4lib->conf_section(irst("tstlan4_Vars"));
      mp_tstlan4lib->ini_name(mp_options_form->imported_ini_name());
      mp_tstlan4lib->load_conf();
      mp_tstlan4lib->conf_section(section);
      mp_tstlan4lib->ini_name(ini_name);
      mp_tstlan4lib->save_conf();
    }
  }

  for (int i = 0; i < 5; i++) {
    m_mxnet_server.tick();
  }
  mp_tstlan4lib->tick();

  if (m_mxnet_server.connected()) {
    if (m_is_mxnet_server_first_connected) {
      m_is_mxnet_server_first_connected = false;
      m_mxnet_server_data.year = 2011;
      m_mxnet_server_data.month = 4;
    } else {
      m_mxnet_server_data.counter++;
    }
  }

  if (m_options_event.check()) {
    mp_options_form->show();
  }

  if (mp_options_form->is_inner_options_button_click()) {
    mp_tstlan4lib->inner_options_event()->exec();
  }
}

