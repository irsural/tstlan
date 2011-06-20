#ifndef tstlan4cfgH
#define tstlan4cfgH

#include <irsdefs.h>

#include <forms.hpp>

#include <tstlan4abs.h>
#include <mxdata.h>
#include <irsdefs.h>
#include <irscpp.h>
#include <irsstrdefs.h>
#include <hardflowg.h>

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
  string_type ini_name() const;
  irs::hardflow_t& mxnet_client_hardflow();
  irs::hardflow_t& mxnet_server_hardflow();
  options_form_t* options_form();
private:
  string_type m_ini_name;
  counter_t m_update_time;
  irs::handle_t<irs::tstlan4_base_t> mp_tstlan4lib;
  irs::handle_t<irs::hardflow_t> mp_mxnet_client_hardflow;
  irs::handle_t<irs::hardflow_t> mp_mxnet_server_hardflow;
  TOptionsForm* mp_options_form;
};

} //namespace tstlan4

#endif //tstlan4cfgH
