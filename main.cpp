//---------------------------------------------------------------------------
#include <irspch.h>
#pragma hdrstop

#include <irstest.h>
#include <irsstring.h>
#include <irsstrconv.h>

#include "main.h"
#include "locktick.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
// 09.05.2011
// CodeGuard ������ ����:
// - ��� ������ � ����� � �������� ��������� (� ����� � �� ������ � ��������)
//   ����� ���������� ������� ������ setg � ��������������� �����������. ��,
//   ���� �� �����, ��� ��������� �����, � �� ������. CodeGuard ��
//   ������������� ��� ��� ������.
// - ��� �������� ��������� ������ � C++ Builder 2010 ���� �����������
//   �������� ��� ����� ����� const wchar_t*, ���� �� ���������, ����������
//   �� ���� ������� ������������� � ������, ����������� ���� ������ �����
//   const char*. ���� ��� ����� �������� ����� const wchar_t*, ��
//   ��� ������� ������� ���������� ������������ ������ ��� �����������
//   ����� �� wchar_t � char (csvwork.cpp:165)
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

  #ifdef NOP
  irs::string_t num_str = 3.14;
  irs::mlog() << "�������������� � ������ � irs::string_t: ";
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

