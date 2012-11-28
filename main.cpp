//---------------------------------------------------------------------------
#include <irspch.h>
#pragma hdrstop

#include <irstest.h>
#include <irsstring.h>
#include <irsstrconv.h>
#include <cbsysutils.h>

#include "main.h"
#include "locktick.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
// 09.05.2011
// CodeGuard выявил баги:
// - При записи в поток с широкими символами (а может и не только с широкими)
//   числа вызывается функция буфера setg с подозрительными параметрами. Но,
//   судя по всему, это осознаный вызов, а не ошибка. CodeGuard же
//   рассматривает это как ошибку.
// - При открытии файлового потока в C++ Builder 2010 есть возможность
//   задавать имя файла через const wchar_t*, хотя по стандарту, независимо
//   от типа символа передаваемого в шаблон, открывается файл только через
//   const char*. Если имя файла задавать через const wchar_t*, то
//   при попытке открыть происходит переполнение буфера при конвертации
//   имени из wchar_t в char (csvwork.cpp:165)
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner):
  TForm(Owner),
  m_cfg(this),
  m_app(&m_cfg),
  m_ini_file()
{
  enum { clearance = 10 };
  Top = clearance;
  Left = clearance;
  Height = Screen->WorkAreaHeight - 2*clearance;
  Width = 550;

  m_ini_file.set_ini_name(m_cfg.ini_name().c_str());
  m_ini_file.set_section("MainForm");
  m_ini_file.add("", this);
  m_ini_file.load();

  irs::mlog() << irs::sdatetime << "Запуск программы" << endl;
  irs::cbuilder::file_version_t file_version;
  irs::cbuilder::get_file_version(Application->ExeName.c_str(), file_version);
  irs::irs_string_t version_str = IRS_SIMPLE_FROM_TYPE_STR(
    irs::cbuilder::file_version_to_str(file_version).c_str());
  irs::mlog() << "Версия: " << version_str << endl;
  irs::mlog() << endl;

  #ifdef NOP
  irs::string_t num_str = 3.14;
  irs::mlog() << "Преобразование в числов в irs::string_t: ";
  irs::mlog() << irs::str_conv<irs::std_string_t>(num_str) << endl;
  #endif //NOP
  //irs::float_test::for_infinity::raw_float_test_out(&irs::mlog());
}
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
  m_ini_file.save();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TickTimerTimer(TObject *Sender)
{
  if (!tstlan4::tick_lock()->check()) {
    m_app.tick();
  }
}
//---------------------------------------------------------------------------

