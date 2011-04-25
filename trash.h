#ifndef trashH
#define trashH

#include <irsdefs.h>

#include <irsfinal.h>

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

#endif //trashH
