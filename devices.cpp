#include <irspch.h>
#pragma hdrstop

#include <tstlan4lib.h>
#include <irsparam.h>
#include <irstime.h>
#include <mxnetc.h>

#include "devices.h"

#include <irsfinal.h>

namespace irs {

class mxdata_assembly_names_t: public mxdata_assembly_names_base_t
{
public:
  mxdata_assembly_names_t();
  virtual string_type num_from_name(const string_type& a_name);
  virtual void rename(const string_type& a_old_name,
    const string_type& a_new_name);
  virtual bool is_clear_needed(const string_type& a_name);
  virtual void reset_clear_needed(const string_type& a_name);
private:
  ini_file_t m_ini_file;
  vector<string_type> m_name_list;
  vector<bool> m_deleted_list;
  vector<bool> m_clear_needed_list;

  bool find_name(const string_type& a_name, size_t* ap_device_idx);
};
mxdata_assembly_names_t::mxdata_assembly_names_t():
  m_ini_file(),
  m_name_list(),
  m_deleted_list()
{
  for (int device_idx = 0; true; device_idx++) {
    m_ini_file.clear_control();
    m_ini_file.set_section(irst("device.") + String(device_idx));
    string_t name = "";
    m_ini_file.add(irst("name"), &name);
    bool is_deleted = false;
    m_ini_file.add(irst("is_deleted"), &is_deleted);
    bool is_exist = false;
    m_ini_file.add(irst("is_exist"), &is_exist);
    m_ini_file.load();
    if (is_exist) {
      m_name_list.push_back(name);
      m_deleted_list.push_back(is_deleted);
      m_clear_needed_list.push_back(false);
    } else {
      break;
    }
  }
  m_ini_file.clear_control();
}
bool mxdata_assembly_names_t::find_name(const string_type& a_name,
  size_t* ap_device_idx)
{
  vector<string_type>::iterator assembly_it =
    find(m_name_list.begin(), m_name_list.end(), a_name);
  bool is_finded = assembly_it != m_name_list.end();
  if (is_finded) {
    *ap_device_idx = assembly_it - m_name_list.begin();
  }
  return is_finded;
}
mxdata_assembly_names_t::string_type mxdata_assembly_names_t::
  num_from_name(const string_type& a_name)
{
  string_type number = "";
  size_t device_idx = 0;
  if (find_name(a_name, &device_idx)) {
    number = device_idx;
  } else {
    size_t device_idx = 0;
    vector<bool>::iterator device_it =
      find(m_deleted_list.begin(), m_deleted_list.end(), true);
    if (device_it != m_deleted_list.end()) {
      device_idx = m_deleted_list.begin() - device_it;
    } else {
      device_idx = m_deleted_list.size();
    }
    m_ini_file.clear_control();
    m_ini_file.set_section(irst("device.") + String(device_idx));
    string_t name = a_name;
    m_ini_file.add(irst("name"), &name);
    bool is_deleted = true;
    m_ini_file.add(irst("is_deleted"), &is_deleted);
    bool is_exist = true;
    m_ini_file.add(irst("is_exist"), &is_exist);
    m_ini_file.save();
    if (device_it != m_deleted_list.end()) {
      m_name_list.at(device_idx) = name;
      m_deleted_list.at(device_idx) = is_deleted;
      m_clear_needed_list.at(device_idx) = true;
    } else {
      m_name_list.push_back(name);
      m_deleted_list.push_back(is_deleted);
      m_clear_needed_list.push_back(true);
    }

    number = device_idx;

    m_ini_file.clear_control();
  }
  return number;
}
void mxdata_assembly_names_t::rename(const string_type& a_old_name,
  const string_type& a_new_name)
{
  size_t device_idx = 0;
  if (find_name(a_old_name, &device_idx)) {
    m_ini_file.clear_control();
    m_ini_file.set_section(irst("device.") + String(device_idx));
    string_t name = a_new_name;
    m_ini_file.add(irst("name"), &name);
    m_ini_file.save();
  }
}
bool mxdata_assembly_names_t::is_clear_needed(const string_type& a_name)
{
  bool is_clear_needed_res = false;
  size_t device_idx = 0;
  if (find_name(a_name, &device_idx)) {
    is_clear_needed_res = m_clear_needed_list.at(device_idx);
  }
  return is_clear_needed_res;
}
void mxdata_assembly_names_t::reset_clear_needed(const string_type& a_name)
{
  size_t device_idx = 0;
  if (find_name(a_name, &device_idx)) {
    m_clear_needed_list.at(device_idx) = false;
  }
}

} // namespace irs

irs::mxdata_assembly_names_base_t* irs::mxdata_assembly_names()
{
  static mxdata_assembly_names_t i_mxdata_assembly_names;
  return &i_mxdata_assembly_names;
}

irs::mxnet_assembly_t::mxnet_assembly_t(tstlan4_base_t* ap_tstlan4,
  const string_type& a_name
):
  m_name(a_name),
  mp_param_box(new param_box_t(irst("Настройки mxnet ") + m_name,
    irst("device.") + mxdata_assembly_names()->num_from_name(m_name))),
  m_param_box_tune(mp_param_box.get()),
  mp_tstlan4(ap_tstlan4),
  mp_mxnet_client_hardflow(irs::hardflow::make_udp_flow_client(
    mp_param_box->get_param(irst("IP")),
    mp_param_box->get_param(irst("Порт")))),
  mp_mxnet_client(new irs::mxnet_client_t(*mp_mxnet_client_hardflow,
    make_cnt_ms(param_box_read_number<int>(*mp_param_box,
    irst("Время обновления, мс")))))
{
  mp_tstlan4->conf_section(irst("device_vars.") +
    mxdata_assembly_names()->num_from_name(m_name));
  if (mxdata_assembly_names()->is_clear_needed(m_name)) {
    mxdata_assembly_names()->reset_clear_needed(m_name);
    mp_tstlan4->clear_conf();
  } else {
    mp_tstlan4->load_conf();
  }
}
irs::mxnet_assembly_t::~mxnet_assembly_t()
{
  mp_param_box->save();
}
irs::mxnet_assembly_t::param_box_tune_t::param_box_tune_t(
  param_box_base_t* ap_param_box
):
  mp_param_box(ap_param_box)
{
  mp_param_box->add_edit(irst("IP"), irst("127.0.0.1"));
  mp_param_box->add_edit(irst("Порт"), irst("5005"));
  mp_param_box->add_edit(irst("Время обновления, мс"), irst("200"));
  mp_param_box->load();
}
irs::mxdata_t* irs::mxnet_assembly_t::mxdata()
{
  return mp_mxnet_client.get();
}
void irs::mxnet_assembly_t::tick()
{
}
void irs::mxnet_assembly_t::show_options()
{
  if (mp_param_box->show()) {
    mp_param_box->save();
  } else {
    mp_param_box->load();
  }
}
void irs::mxnet_assembly_t::tstlan4(tstlan4_base_t* ap_tstlan4)
{
  mp_tstlan4 = ap_tstlan4;
}
void irs::mxnet_assembly_t::name(const string_type& a_name)
{
  mxdata_assembly_names()->rename(m_name, a_name);
  m_name = a_name;
}

