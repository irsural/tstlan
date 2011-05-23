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
  mp_param_box->add_edit(irst("ip"), irst("127.0.0.1"));
  mp_param_box->add_edit(irst("port"), irst("5005"));
  mp_param_box->load();
}
irs::mxnet_assembly_t::~mxnet_assembly_t()
{
  mp_param_box->save();
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
  mp_param_box->show();
}
void irs::mxnet_assembly_t::tstlan4(tstlan4_base_t* ap_tstlan4)
{
  mp_tstlan4 = ap_tstlan4;
}
void irs::mxnet_assembly_t::name(const string_type& a_name)
{
  mp_param_box->save();
  mp_param_box.reset(new param_box_t(irst("Настройки mxnet ") + a_name,
    irst("device.") + a_name));
  mp_param_box->add_edit(irst("ip"), irst("127.0.0.1"));
  mp_param_box->add_edit(irst("port"), irst("5005"));
  mp_param_box->load();
}

