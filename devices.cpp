#include <irspch.h>
#pragma hdrstop

#include <tstlan4lib.h>
#include <irsparam.h>
#include <irstime.h>
#include <mxnetc.h>
#include <irsmbus.h>
#include <irsnetdefs.h>

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
  virtual void erase(const string_type& a_name);
private:
  ini_file_t m_ini_file;
  vector<string_type> m_name_list;
  vector<bool> m_erased_list;
  vector<bool> m_clear_needed_list;

  bool find_name(const string_type& a_name, size_t* ap_device_idx);
};
mxdata_assembly_names_t::mxdata_assembly_names_t():
  m_ini_file(),
  m_name_list(),
  m_erased_list()
{
  for (int device_idx = 0; true; device_idx++) {
    m_ini_file.clear_control();
    m_ini_file.set_section(irst("device.") + String(device_idx));
    string_t name = irst("");
    m_ini_file.add(irst("name"), &name);
    bool is_erased = false;
    m_ini_file.add(irst("is_erased"), &is_erased);
    bool is_exist = false;
    m_ini_file.add(irst("is_exist"), &is_exist);
    m_ini_file.load();
    if (is_exist) {
      m_name_list.push_back(name);
      m_erased_list.push_back(is_erased);
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
  string_type number = irst("");
  size_t device_idx = 0;
  if (find_name(a_name, &device_idx)) {
    number = device_idx;
  } else {
    size_t device_idx = 0;
    vector<bool>::iterator device_it =
      find(m_erased_list.begin(), m_erased_list.end(), true);
    if (device_it != m_erased_list.end()) {
      device_idx = m_erased_list.begin() - device_it;
    } else {
      device_idx = m_erased_list.size();
    }
    m_ini_file.clear_control();
    m_ini_file.set_section(irst("device.") + String(device_idx));
    string_t name = a_name;
    m_ini_file.add(irst("name"), &name);
    bool is_erased = false;
    m_ini_file.add(irst("is_erased"), &is_erased);
    bool is_exist = true;
    m_ini_file.add(irst("is_exist"), &is_exist);
    m_ini_file.save();
    if (device_it != m_erased_list.end()) {
      m_name_list.at(device_idx) = name;
      m_erased_list.at(device_idx) = is_erased;
      m_clear_needed_list.at(device_idx) = true;
    } else {
      m_name_list.push_back(name);
      m_erased_list.push_back(is_erased);
      m_clear_needed_list.push_back(false);
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
void mxdata_assembly_names_t::erase(const string_type& a_name)
{
  size_t device_idx = 0;
  if (find_name(a_name, &device_idx)) {
    m_ini_file.clear_control();
    m_ini_file.set_section(irst("device.") + String(device_idx));
    bool is_erased = true;
    m_ini_file.add(irst("is_erased"), &is_erased);
    m_ini_file.save();
  }
}

} // namespace irs

irs::mxdata_assembly_names_base_t* irs::mxdata_assembly_names()
{
  static mxdata_assembly_names_t i_mxdata_assembly_names;
  return &i_mxdata_assembly_names;
}

namespace irs {

class mxnet_assembly_creator_t: public mxdata_assembly_creator_t
{
public:
  virtual handle_t<mxdata_assembly_t> make(tstlan4_base_t* ap_tstlan4,
    const string_type& a_name);
private:
};

class mxnet_assembly_t: public mxdata_assembly_t
{
public:
  mxnet_assembly_t(tstlan4_base_t* ap_tstlan4, const string_type& a_name);
  virtual ~mxnet_assembly_t();
  virtual irs::mxdata_t* mxdata();
  virtual void tick();
  virtual void show_options();
  virtual void tstlan4(tstlan4_base_t* ap_tstlan4);
  virtual void name(const string_type& a_name);
private:
  struct param_box_tune_t {
    param_box_base_t* mp_param_box;

    param_box_tune_t(param_box_base_t* ap_param_box);
  };

  string_type m_name;
  handle_t<param_box_base_t> mp_param_box;
  param_box_tune_t m_param_box_tune;
  tstlan4_base_t* mp_tstlan4;
  handle_t<hardflow_t> mp_mxnet_client_hardflow;
  handle_t<mxdata_t> mp_mxnet_client;
};

} // namespace irs

irs::handle_t<irs::mxdata_assembly_t> irs::mxnet_assembly_creator_t::make(
  tstlan4_base_t* ap_tstlan4, const string_type& a_name)
{
  return handle_t<mxdata_assembly_t>(new mxnet_assembly_t(ap_tstlan4, a_name));
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
  mp_tstlan4->connect(mp_mxnet_client.get());
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
  mp_mxnet_client->tick();
}
void irs::mxnet_assembly_t::show_options()
{
  if (mp_param_box->show()) {
    mp_mxnet_client_hardflow->set_param(irst("remote_adress"),
      mp_param_box->get_param(irst("IP")));
    mp_mxnet_client_hardflow->set_param(irst("remote_port"),
      mp_param_box->get_param(irst("Порт")));
    mxnet_client_t* p_mxnet_client =
      static_cast<mxnet_client_t*>(mp_mxnet_client.get());
    p_mxnet_client->update_time(make_cnt_ms(
      param_box_read_number<int>(*mp_param_box,
      irst("Время обновления, мс"))));
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

namespace irs {

class modbus_udp_assembly_creator_t: public mxdata_assembly_creator_t
{
public:
  virtual handle_t<mxdata_assembly_t> make(tstlan4_base_t* ap_tstlan4,
    const string_type& a_name);
private:
};

class modbus_tcp_assembly_creator_t: public mxdata_assembly_creator_t
{
public:
  virtual handle_t<mxdata_assembly_t> make(tstlan4_base_t* ap_tstlan4,
    const string_type& a_name);
private:
};

class modbus_assembly_t: public mxdata_assembly_t
{
public:
  enum protocol_t { udp_protocol, tcp_protocol };

  modbus_assembly_t(tstlan4_base_t* ap_tstlan4, const string_type& a_name,
    protocol_t a_protocol);
  virtual ~modbus_assembly_t();
  virtual irs::mxdata_t* mxdata();
  virtual void tick();
  virtual void show_options();
  virtual void tstlan4(tstlan4_base_t* ap_tstlan4);
  virtual void name(const string_type& a_name);
private:
  struct param_box_tune_t {
    param_box_base_t* mp_param_box;

    param_box_tune_t(param_box_base_t* ap_param_box);
  };

  string_type m_name;
  handle_t<param_box_base_t> mp_param_box;
  param_box_tune_t m_param_box_tune;
  tstlan4_base_t* mp_tstlan4;
  handle_t<hardflow_t> mp_modbus_client_hardflow;
  handle_t<mxdata_t> mp_modbus_client;

  static handle_t<mxdata_t> make_client(handle_t<hardflow_t> ap_hardflow,
    handle_t<param_box_base_t> ap_param_box);
  static handle_t<hardflow_t> make_hardflow(protocol_t a_protocol,
    handle_t<param_box_base_t> ap_param_box);
};

} // namespace irs

irs::handle_t<irs::mxdata_assembly_t> irs::modbus_udp_assembly_creator_t::make(
  tstlan4_base_t* ap_tstlan4, const string_type& a_name)
{
  return handle_t<mxdata_assembly_t>(new modbus_assembly_t(ap_tstlan4,
    a_name, modbus_assembly_t::udp_protocol));
}

irs::handle_t<irs::mxdata_assembly_t> irs::modbus_tcp_assembly_creator_t::make(
  tstlan4_base_t* ap_tstlan4, const string_type& a_name)
{
  return handle_t<mxdata_assembly_t>(new modbus_assembly_t(ap_tstlan4,
    a_name, modbus_assembly_t::tcp_protocol));
}

irs::handle_t<irs::mxdata_t> irs::modbus_assembly_t::make_client(
  handle_t<hardflow_t> ap_hardflow,
  handle_t<param_box_base_t> ap_param_box)
{
  return new irs::modbus_client_t(
    ap_hardflow.get(),
    modbus_client_t::mode_refresh_auto,
    param_box_read_number<size_t>(*ap_param_box,
      irst("Биты, только чтение (Discret inputs), байт")),
    param_box_read_number<size_t>(*ap_param_box,
      irst("Биты, чтение/запись (Coils), байт")),
    param_box_read_number<size_t>(*ap_param_box,
      irst("Регистры, чтение/запись (Holding Registers), кол-во")),
    param_box_read_number<size_t>(*ap_param_box,
      irst("Регистры, только чтение (Input Registers), кол-во")),
    make_cnt_ms(param_box_read_number<int>(*ap_param_box,
      irst("Время обновления, мс")))
  );
}
irs::handle_t<irs::hardflow_t> irs::modbus_assembly_t::make_hardflow(
  protocol_t a_protocol,
  handle_t<param_box_base_t> ap_param_box)
{
  handle_t<hardflow_t> hardflow_ret = IRS_NULL;
  switch (a_protocol) {
    case udp_protocol: {
      hardflow_ret = hardflow::make_udp_flow_client(
        ap_param_box->get_param(irst("IP")),
        ap_param_box->get_param(irst("Порт")));
    } break;
    case tcp_protocol: {
      hardflow_ret.reset(new hardflow::tcp_client_t(
        make_mxip(ap_param_box->get_param(irst("IP")).c_str()),
        param_box_read_number<irs_u16>(*ap_param_box, irst("Порт"))));
    } break;
  }
  return hardflow_ret;
}
irs::modbus_assembly_t::modbus_assembly_t(tstlan4_base_t* ap_tstlan4,
  const string_type& a_name, protocol_t a_protocol
):
  m_name(a_name),
  mp_param_box(new param_box_t(irst("Настройки MODBUS ") + m_name,
    irst("device.") + mxdata_assembly_names()->num_from_name(m_name))),
  m_param_box_tune(mp_param_box.get()),
  mp_tstlan4(ap_tstlan4),
  mp_modbus_client_hardflow(make_hardflow(a_protocol, mp_param_box)),
  mp_modbus_client(make_client(mp_modbus_client_hardflow, mp_param_box))
{
  mp_tstlan4->connect(mp_modbus_client.get());
  mp_tstlan4->conf_section(irst("device_vars.") +
    mxdata_assembly_names()->num_from_name(m_name));
  if (mxdata_assembly_names()->is_clear_needed(m_name)) {
    mxdata_assembly_names()->reset_clear_needed(m_name);
    mp_tstlan4->clear_conf();
  } else {
    mp_tstlan4->load_conf();
  }
}
irs::modbus_assembly_t::~modbus_assembly_t()
{
  mp_param_box->save();
}
irs::modbus_assembly_t::param_box_tune_t::param_box_tune_t(
  param_box_base_t* ap_param_box
):
  mp_param_box(ap_param_box)
{
  mp_param_box->add_edit(irst("IP"), irst("127.0.0.1"));
  mp_param_box->add_edit(irst("Порт"), irst("5005"));
  mp_param_box->add_edit(irst("Время обновления, мс"), irst("200"));
  mp_param_box->add_edit(irst("Биты, только чтение (Discret inputs), байт"),
    irst("0"));
  mp_param_box->add_edit(irst("Биты, чтение/запись (Coils), байт"),
    irst("0"));
  mp_param_box->add_edit(irst("Регистры, чтение/запись ")
    irst("(Holding Registers), кол-во"), irst("10"));
  mp_param_box->add_edit(irst("Регистры, только чтение ")
    irst("(Input Registers), кол-во"), irst("0"));
  mp_param_box->load();
}
irs::mxdata_t* irs::modbus_assembly_t::mxdata()
{
  return mp_modbus_client.get();
}
void irs::modbus_assembly_t::tick()
{
  mp_modbus_client->tick();
}
void irs::modbus_assembly_t::show_options()
{
  if (mp_param_box->show()) {
    mp_modbus_client_hardflow->set_param(irst("remote_adress"),
      mp_param_box->get_param(irst("IP")));
    mp_modbus_client_hardflow->set_param(irst("remote_port"),
      mp_param_box->get_param(irst("Порт")));
    mp_modbus_client = make_client(mp_modbus_client_hardflow, mp_param_box);
  }
}
void irs::modbus_assembly_t::tstlan4(tstlan4_base_t* ap_tstlan4)
{
  mp_tstlan4 = ap_tstlan4;
}
void irs::modbus_assembly_t::name(const string_type& a_name)
{
  mxdata_assembly_names()->rename(m_name, a_name);
  m_name = a_name;
}

namespace irs {

class mxdata_assembly_types_implementation_t: public mxdata_assembly_types_t
{
public:
  mxdata_assembly_types_implementation_t();
  virtual void enum_types(vector<string_type>* ap_types) const;
  virtual handle_t<mxdata_assembly_t> make_assembly(
    const string_type& a_assembly_type, tstlan4_base_t* ap_tstlan4,
    const string_type& a_name);
private:
  typedef map<string_type, handle_t<mxdata_assembly_creator_t> > ac_list_type;
  typedef ac_list_type::iterator ac_list_it_type;
  typedef ac_list_type::const_iterator ac_list_const_it_type;

  ac_list_type m_ac_list;
};

} //namespace irs

irs::mxdata_assembly_types_t* irs::mxdata_assembly_types()
{
  static mxdata_assembly_types_implementation_t
    mxdata_assembly_types_implementation;
  return &mxdata_assembly_types_implementation;
}

irs::mxdata_assembly_types_implementation_t::
  mxdata_assembly_types_implementation_t(
):
  m_ac_list()
{
  m_ac_list[irst("mxnet")] = handle_t<mxdata_assembly_creator_t>(
    new mxnet_assembly_creator_t);
  m_ac_list[irst("modbus udp")] = handle_t<mxdata_assembly_creator_t>(
    new modbus_udp_assembly_creator_t);
  m_ac_list[irst("modbus tcp")] = handle_t<mxdata_assembly_creator_t>(
    new modbus_udp_assembly_creator_t);
}
void irs::mxdata_assembly_types_implementation_t::
  enum_types(vector<string_type>* ap_types) const
{
  ap_types->clear();
  for (ac_list_const_it_type it = m_ac_list.begin();
    it != m_ac_list.end(); it++)
  {
    ap_types->push_back(it->first);
  }
}
irs::handle_t<irs::mxdata_assembly_t>
  irs::mxdata_assembly_types_implementation_t::make_assembly
(
  const string_type& a_assembly_type, tstlan4_base_t* ap_tstlan4,
  const string_type& a_name)
{
  handle_t<mxdata_assembly_t> result_assembly(IRS_NULL);
  ac_list_it_type it = m_ac_list.find(a_assembly_type);
  if (it != m_ac_list.end()) {
    result_assembly = IRS_NULL;
    result_assembly = it->second->make(ap_tstlan4, a_name);
  }
  return result_assembly;
}

