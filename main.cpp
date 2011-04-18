//---------------------------------------------------------------------------
#include <irspch.h>
#pragma hdrstop

#include "main.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
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
}
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
  m_ini_file.save();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TickTimerTimer(TObject *Sender)
{
  m_app.tick();
}
//---------------------------------------------------------------------------

