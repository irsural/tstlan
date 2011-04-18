#include <irspch.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif // __BORLANDC__

#include <locale.h>

#include <irsstrdefs.h>
#include <mxdata.h>
#include <irserror.h>
#include <irscpp.h>
#include <irstest.h>
#include <irssysutils.h>
#include <mxifa.h>

#include "tstlan4app.h"

#include <irsfinal.h>

tstlan4::app_t::app_t(cfg_t* ap_cfg):
  mp_cfg(ap_cfg),
  m_mnetc_data(MXIFA_MXNETC, irs::make_cnt_s(2),
    mp_cfg->update_time()),
  mp_tstlan4lib(mp_cfg->tstlan4lib()),
  m_dbg_data(16)
{
  m_mnetc_data.ip(irs::make_mxip(192, 168, 0, 37));
  m_mnetc_data.port(5005);
  mp_tstlan4lib->connect(&m_dbg_data);
  mp_tstlan4lib->options_event_connect(&m_options_event);

  #ifdef NOP
  //irs::cstr_convert::exec(irs::mlog());
  //irs::compiler_test::template_template_inheritance::exec(irs::mlog());
  //irs::display_parametrs_of_built_in_types(irs::mlog());
  //irs::convert_str_test(irs::mlog());

  //Russian_Russia.1251
  //Russian_Russia.866
  locale loccpp("Russian_Russia.1251");
  irs::mlog().imbue(loccpp);
  irs::mlog() << IRS_PI << endl;
  #ifdef NOP
  char* loc = setlocale(LC_ALL, "Russian_Russia.1251");
  if (loc) {
    irs::mlog() << loc << endl;
  } else {
    irs::mlog() << "bad locale" << endl;
  }
  #endif //NOP
  irs::mlog() << IRS_PI << endl;
  irs::raw_data_t<char> str(30);

  char alpha = 'Я';
  if (isalpha(alpha, loccpp)) {
    irs::mlog() << alpha << " - буква" << endl;
  } else {
    irs::mlog() << alpha << " - не буква" << endl;
  }
  //sprintf(str.data(), "Привет");
  //irs::mlog() << str.data() << endl;

  std::string s;
  //locale loccpp("Russian_Russia.1251");
  //locale loc = irs::loc().get();
  locale::global(locale("Russian_Russia.1251"));
  //locale::global(loccpp);
  //irs::loc().get();
  irs::number_to_string(15.5, &s, locale());
  irs::mlog() << s << endl;
  #endif //NOP
}
void tstlan4::app_t::tick()
{
  //for (int i = 0; i < 5; i++) m_mnetc_data.tick();
  mp_tstlan4lib->tick();
  if (m_options_event.check()) {
    mp_cfg->options_show();
  }
}

