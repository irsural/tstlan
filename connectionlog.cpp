//---------------------------------------------------------------------------

#include <irspch.h>
#pragma hdrstop

#include "connectionlog.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConnectionLogForm *ConnectionLogForm;
//---------------------------------------------------------------------------
__fastcall TConnectionLogForm::TConnectionLogForm(TComponent* Owner)
  : TForm(Owner),
  m_memo_error_string_list(),
  m_error_string_list(),
  m_update_timer(irs::make_cnt_s(1))
{
}
//---------------------------------------------------------------------------
void __fastcall TConnectionLogForm::CloseButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TConnectionLogForm::ClearButtonClick(TObject *Sender)
{
  m_memo_error_string_list.clear();
  LogMemo->Lines->Clear();
}

void TConnectionLogForm::add_errors(
  const error_string_list_type& a_error_string_list)
{
  size_type start_index = 0;
  if (a_error_string_list.size() > error_list_max_size) {
    start_index = a_error_string_list.size() - error_list_max_size;
  }
  for (size_type i = start_index; i < a_error_string_list.size(); i++) {
    m_error_string_list.push_back(a_error_string_list[i]);
    if (m_error_string_list.size() > error_list_max_size) {
      m_error_string_list.pop_front();
    }
  }
}

void TConnectionLogForm::update_error_list()
{
  m_memo_error_string_list = m_error_string_list;
  m_error_string_list.clear();
  for (size_type i = 0; i < m_memo_error_string_list.size(); i++) {
    string_type s = m_memo_error_string_list[i];
    LogMemo->Lines->Add(irs::str_conv<String>(m_memo_error_string_list[i]));
  }
}
//---------------------------------------------------------------------------



void __fastcall TConnectionLogForm::FormShow(TObject *Sender)
{
  update_error_list();
}
//---------------------------------------------------------------------------

void __fastcall TConnectionLogForm::MainTimerTimer(TObject *Sender)
{
  if (AutoUpdateCheckBox->Checked && m_update_timer.check()) {
    update_error_list();
  }
}
//---------------------------------------------------------------------------


