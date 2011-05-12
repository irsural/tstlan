#include <irspch.h>
#pragma hdrstop

#include <tstlan4lib.h>
#include <irsparam.h>

#include "devices.h"

#include <irsfinal.h>

irs::mxnet_assembly_t::mxnet_assembly_t(tstlan4_base_t* ap_tstlan4,
  const string_type& a_name
):
  mp_tstlan4(ap_tstlan4),
  mp_param_box(new param_box_t(irst("Настройки mxnet ") + a_name,
    irst("device.") + a_name))
{
}
irs::mxdata_t* irs::mxnet_assembly_t::mxdata()
{
  return IRS_NULL;
}
void irs::mxnet_assembly_t::tick()
{
}
void irs::mxnet_assembly_t::show_options()
{
}
void irs::mxnet_assembly_t::tstlan4(tstlan4_base_t* ap_tstlan4)
{
}
void irs::mxnet_assembly_t::name(const string_type& a_name)
{
}

