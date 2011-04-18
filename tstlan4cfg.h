#ifndef tstlan4cfgH
#define tstlan4cfgH

#include <irsdefs.h>

#include <forms.hpp>

#include <tstlan4abs.h>
#include <mxdata.h>
#include <irsdefs.h>
#include <irscpp.h>
#include <irsstrdefs.h>

#include "options.h"

#include <irsfinal.h>

namespace tstlan4 {

class cfg_t
{
public:
  typedef irs::string_t string_type;

  cfg_t(TForm* ap_form);
  irs::tstlan4_base_t* tstlan4lib();
  counter_t update_time() const;
  void options_show();
  string_type ini_name() const;
private:
  string_type m_ini_name;
  counter_t m_update_time;
  irs::handle_t<irs::tstlan4_base_t> mp_tstlan4lib;
  TOptionsForm* mp_options_form;
};

} //namespace tstlan4

#endif //tstlan4cfgH
