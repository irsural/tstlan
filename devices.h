#ifndef devicesH
#define devicesH

#include <irsdefs.h>

#include <tstlan4abs.h>
#include <irsparamabs.h>
#include <hardflowg.h>
#include <mxdata.h>
#include <mxini.h>

#include <irsfinal.h>

namespace irs {

class mxdata_assembly_t
{
public:
  typedef string_t string_type;

  virtual ~mxdata_assembly_t() {}
  virtual irs::mxdata_t* mxdata() = 0;
  virtual void tick() = 0;
  virtual void show_options() = 0;
  virtual void tstlan4(tstlan4_base_t* ap_tstlan4) = 0;
  virtual void name(const string_type& a_name) = 0;
};

class mxdata_assembly_names_base_t
{
public:
  typedef mxdata_assembly_t::string_type string_type;

  virtual ~mxdata_assembly_names_base_t() {}
  virtual string_type num_from_name(const string_type& a_name) = 0;
  virtual void rename(const string_type& a_old_name,
    const string_type& a_new_name) = 0;
  virtual bool is_clear_needed(const string_type& a_name) = 0;
  virtual void reset_clear_needed(const string_type& a_name) = 0;
};

} // namespace irs


namespace irs {

mxdata_assembly_names_base_t* mxdata_assembly_names();

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

#endif //devicesH
