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

#include <irsint.h>
#include <mxini.h>
#include <irscpp.h>

#include "devices.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
  TPageControl *OptionsPageControl;
  TTabSheet *GeneralSheet;
  TTabSheet *DeviceListSheet;
  TValueListEditor *DeviceListValueListEditor;
  TPanel *ButtonPanel;
  TButton *OkButton;
  TButton *CancelButton;
  TButton *AddButton;
  TButton *DeleteButton;
  TButton *RenameButton;
  TButton *ApplyButton;
  TEdit *NameEdit;
  TLabel *NameLabel;
  void __fastcall OkButtonClick(TObject *Sender);
  void __fastcall ApplyButtonClick(TObject *Sender);
  void __fastcall CancelButtonClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall AddButtonClick(TObject *Sender);
  void __fastcall DeleteButtonClick(TObject *Sender);
  void __fastcall RenameButtonClick(TObject *Sender);
  void __fastcall DeviceListValueListEditorSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
  irs::generator_events_t m_device_list_changed_event;
  irs::ini_file_t m_ini_file;
  irs::mxdata_assembly_types_t* mp_assembly_types;
  vector<irs::string_t> m_assembly_type_list;

  void add_device_list(int a_row);
  bool check_device_list(int a_row);
public:		// User declarations
  __fastcall TOptionsForm(TComponent* Owner);
  void device_list_changed_event_add(irs::event_t* ap_event);
  void device_list_changed_event_clear();
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
