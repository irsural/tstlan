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

class mxdata_assembly_creator_t
{
public:
  typedef mxdata_assembly_t::string_type string_type;

  virtual ~mxdata_assembly_creator_t() {}
  virtual handle_t<mxdata_assembly_t> make(tstlan4_base_t* ap_tstlan4,
    const string_type& a_name) = 0;
private:
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
  virtual void erase(const string_type& a_name) = 0;
};

class mxdata_assembly_types_t
{
public:
  typedef mxdata_assembly_t::string_type string_type;

  virtual void enum_types(vector<string_type>* ap_types) const = 0;
  virtual handle_t<mxdata_assembly_t> make_assembly(
    const string_type& a_assembly_type, tstlan4_base_t* ap_tstlan4,
    const string_type& a_name) = 0;
};

mxdata_assembly_names_base_t* mxdata_assembly_names();

mxdata_assembly_types_t* mxdata_assembly_types();

} // namespace irs

#endif //devicesH

