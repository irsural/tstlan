//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <irsdefs.h>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <mxini.h>

#include "tstlan4app.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
  TTimer *TickTimer;
  void __fastcall TickTimerTimer(TObject *Sender);
private:	// User declarations
  tstlan4::cfg_t m_cfg;
  tstlan4::app_t m_app;
  irs::ini_file_t m_ini_file;
public:		// User declarations
  __fastcall TMainForm(TComponent* Owner);
  __fastcall ~TMainForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
