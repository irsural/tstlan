//---------------------------------------------------------------------------
#include <irspch.h>
#pragma hdrstop

#include "options.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
