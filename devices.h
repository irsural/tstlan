#ifndef devicesH
#define devicesH

#include <irsdefs.h>

#include <tstlan4abs.h>
#include <irsparamabs.h>

#include <irsfinal.h>

namespace irs {

class mxdata_assembly_t
{
public:
  typedef string_t string_type;

  ~mxdata_assembly_t() {}
  virtual irs::mxdata_t* mxdata() = 0;
  virtual void tick() = 0;
  virtual void show_options() = 0;
  virtual void tstlan4(tstlan4_base_t* ap_tstlan4) = 0;
  virtual void name(const string_type& a_name) = 0;
};

} // namespace irs

namespace irs {

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
  tstlan4_base_t* mp_tstlan4;
  handle_t<param_box_base_t> mp_param_box;
};

} // namespace irs

#endif //devicesH
