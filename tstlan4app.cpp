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

//bool find_device(options_form_t* ap_options_form,
  //const irs::string_t& a_name, irs::string_t* ap_type);

irs::handle_t<irs::mxdata_assembly_t> make_assembly(
  const irs::string_t& a_device_name,
  const irs::string_t& a_device_type,
  irs::tstlan4_base_t* ap_tstlan4lib
);

} //namespace tstlan4

/*bool tstlan4::find_device(options_form_t* ap_options_form,
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
}*/

irs::handle_t<irs::mxdata_assembly_t> tstlan4::make_assembly(
  const irs::string_t& a_device_name,
  const irs::string_t& a_device_type,
  irs::tstlan4_base_t* ap_tstlan4lib
) {
  return irs::mxdata_assembly_types()->
    make_assembly(a_device_type, ap_tstlan4lib, a_device_name);
}

tstlan4::app_t::app_t(cfg_t* ap_cfg):
  mp_cfg(ap_cfg),
  mp_options_param_box(mp_cfg->make_options_param_box()),
  mp_chart(mp_cfg->make_chart()),
  m_mxnet_server_data(),
  m_mxnet_server(mp_cfg->mxnet_server_hardflow(),
    m_mxnet_server_data.size()/sizeof(irs_i32)),
  m_options_event(),
  m_is_mxnet_server_first_connected(true),
  m_test(),
  m_devices_map()
{
  mp_options_param_box->add_edit(irst("����� ����������, ��"), irst("200"));
  mp_options_param_box->add_edit(
    irst("���������� ����� � �������"), irst("1000"));
  mp_options_param_box->add_bool(irst("�������� �����"), false);
  mp_options_param_box->set_ini_name(mp_cfg->ini_name());
  mp_options_param_box->load();
  apply_options();

  m_mxnet_server_data.connect(&m_mxnet_server);
}

void tstlan4::app_t::set_devices(
  const std::map<string_type, device_options_t>& a_devices)
{
  std::map<string_type, device_options_t>::const_iterator dev_opt_it =
    a_devices.begin();

  while (dev_opt_it != a_devices.end()) {
    std::map<string_type, device_t>::iterator it =
      m_devices_map.find(dev_opt_it->first);
    bool need_reset = false;
    if (it != m_devices_map.end()) {
      if (it->second.type != dev_opt_it->second.type) {
        need_reset = true;
      }
    } else {
      need_reset = true;
    }
    if (need_reset) {
      if (it != m_devices_map.end()) {
        m_devices_map.erase(it);
      }
      device_t device;
      device.tstlan4lib = mp_cfg->make_tstlan4lib(mp_chart.get());
      if (!device.tstlan4lib.is_empty()) {
        //device.tstlan4lib->conf_section(irst("vars"));
        device.tstlan4lib->ini_name(dev_opt_it->first);
        device.tstlan4lib->load_conf();
        device.mxdata_assembly =
          make_assembly(dev_opt_it->first, dev_opt_it->second.type,
          device.tstlan4lib.get());
        if (!device.mxdata_assembly.is_empty()) {
          device.mxdata_assembly->enabled(dev_opt_it->second.enabled);
          device.type = dev_opt_it->second.type;
          m_devices_map.insert(make_pair(dev_opt_it->first, device));
          device.tstlan4lib->connect(device.mxdata_assembly->mxdata());
        }
      }
    } else if (it != m_devices_map.end()) {
      if (it->second.mxdata_assembly->enabled() != dev_opt_it->second.enabled) {
        it->second.mxdata_assembly->enabled(dev_opt_it->second.enabled);
        it->second.tstlan4lib->connect(it->second.mxdata_assembly->mxdata());
      }
    }
    ++dev_opt_it;
  }

  std::map<string_type, device_t>::iterator it =
    m_devices_map.begin();
  std::map<string_type, device_t>::iterator delete_elem_it =
    m_devices_map.end();
  while (it != m_devices_map.end()) {
    if (a_devices.find(it->first) == a_devices.end()) {
      delete_elem_it = it;
    }
    ++it;
    if (delete_elem_it != m_devices_map.end()) {
      m_devices_map.erase(delete_elem_it);
      delete_elem_it = m_devices_map.end();
    }
  }
}

void tstlan4::app_t::show_tstlan4lib(const string_type& a_name)
{
  std::map<string_type, device_t>::iterator it = m_devices_map.find(a_name);
  if (it == m_devices_map.end()) {
    Application->MessageBox(
      irst("���������� �� ����������"),
      irst("������"),
      MB_OK + MB_ICONERROR);
    return;
  }
  it->second.tstlan4lib->show();
}

void tstlan4::app_t::show_device_options(const string_type& a_name)
{
  std::map<string_type, device_t>::iterator it = m_devices_map.find(a_name);
  if (it == m_devices_map.end()) {
    Application->MessageBox(
      irst("���������� �� ����������"),
      irst("������"),
      MB_OK + MB_ICONERROR);
    return;
  }
  it->second.mxdata_assembly->show_options();
}

void tstlan4::app_t::show_chart()
{
  mp_chart->show();
}

void tstlan4::app_t::show_modal_options()
{
  if (mp_options_param_box->show()) {
    apply_options();
  }
  mp_options_param_box->save();
}

void tstlan4::app_t::apply_options()
{
  const irs_i32 refresh_time =
    irs::param_box_read_number<irs_i32>(mp_options_param_box.get(),
    irst("����� ����������, ��"));
  mp_chart->set_refresh_time(refresh_time);
  const irs_u32 chart_size =
    irs::param_box_read_number<irs_u32>(mp_options_param_box.get(),
    irst("���������� ����� � �������"));
  mp_chart->resize(chart_size);
  if (mp_options_param_box->get_param(irst("�������� �����")) ==
    irst("true")) {
    mp_options_param_box->set_param(irst("�������� �����"), irst("false"));
    std::map<string_type, device_t>::iterator it = m_devices_map.begin();
    while (it == m_devices_map.end()) {
      it->second.tstlan4lib->reset_chart();
      ++it;
    }
    mp_chart->clear();
  }
}

void tstlan4::app_t::import(
  const string_type& a_source, const string_type& a_destination)
{
  irs::handle_t<irs::tstlan4_base_t> tstlan4lib =
    mp_cfg->make_tstlan4lib(NULL);
  string_type section = tstlan4lib->conf_section();
  string_type ini_name = tstlan4lib->ini_name();
  tstlan4lib->conf_section(irst("tstlan4_Vars"));
  tstlan4lib->ini_name(a_source);
  tstlan4lib->load_conf();
  tstlan4lib->conf_section(section);
  tstlan4lib->ini_name(a_destination);
  tstlan4lib->save_conf();
}

void tstlan4::app_t::tick()
{
  m_test.tick();

  std::map<string_type, device_t>::iterator it =
    m_devices_map.begin();
  while (it != m_devices_map.end()) {
    it->second.tstlan4lib->tick();
    it->second.mxdata_assembly->tick();
    ++it;
  }

  for (int i = 0; i < 5; i++) {
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

  /*if (m_options_event.check()) {
    mp_options_form->show();
  }*/

  
}

