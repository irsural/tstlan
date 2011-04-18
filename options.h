//---------------------------------------------------------------------------
#ifndef optionsH
#define optionsH
//---------------------------------------------------------------------------
#include <irsdefs.h>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ExtCtrls.hpp>

#include <irsfinal.h>
//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
  TPageControl *OptionsPageControl;
  TTabSheet *GeneralSheet;
  TTabSheet *DeviceListSheet;
  TValueListEditor *ValueListEditor1;
  TPanel *ButtonPanel;
  TButton *OkButton;
  TButton *CancelButton;
private:	// User declarations
public:		// User declarations
  __fastcall TOptionsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
