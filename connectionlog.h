//---------------------------------------------------------------------------

#ifndef connectionlogH
#define connectionlogH
//---------------------------------------------------------------------------
#include <irsdefs.h>

#include <irsdevices.h>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <irsfinal.h>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TConnectionLogForm : public TForm
{
__published:	// IDE-managed Components
  TButton *ClearButton;
  TMemo *LogMemo;
  TButton *CloseButton;
  TTimer *MainTimer;
  TCheckBox *AutoUpdateCheckBox;
  void __fastcall CloseButtonClick(TObject *Sender);
  void __fastcall ClearButtonClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall MainTimerTimer(TObject *Sender);
private:	// User declarations
  void update_error_list();
  typedef std::size_t size_type;
  typedef irs::string_t string_type;
  typedef irs::mxdata_assembly_t::error_string_list_type error_string_list_type;
  enum { error_list_max_size = 1000 };
  error_string_list_type m_memo_error_string_list;
  error_string_list_type m_error_string_list;
  irs::loop_timer_t m_update_timer;
public:		// User declarations
  __fastcall TConnectionLogForm(TComponent* Owner);
  void add_errors(const error_string_list_type& a_error_string_list);
};
//---------------------------------------------------------------------------
extern PACKAGE TConnectionLogForm *ConnectionLogForm;
//---------------------------------------------------------------------------
#endif
