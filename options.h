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
#include <irsparamabs.h>

#include "devices.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
class options_form_t
{
public:
  ~options_form_t() {}
  virtual irs::string_t device_names(size_t a_index) = 0;
  virtual irs::string_t device_types(size_t a_index) = 0;
  virtual size_t device_count() = 0;
  virtual irs::param_box_base_t* general_options() = 0;
  virtual bool is_device_options_button_click() = 0;
  virtual bool is_options_apply() = 0;
  virtual void show() = 0;
};
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
  TButton *GeneralOptionsButton;
  TButton *DeviceOptionsButton;
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
  void __fastcall GeneralOptionsButtonClick(TObject *Sender);
  void __fastcall DeviceOptionsButtonClick(TObject *Sender);
private:	// User declarations
  struct options_tune_t {
    TOptionsForm* mp_OptionsForm;
    options_tune_t(TOptionsForm* ap_OptionsForm);
  };
  friend class options_tune_t;

  //irs::generator_events_t m_device_list_changed_event;
  irs::ini_file_t m_ini_file;
  vector<irs::string_t> m_assembly_type_list;
  irs::handle_t<irs::param_box_base_t> mp_general_options;
  options_tune_t m_options_tune;
  irs::handle_t<options_form_t> mp_options_form;

  void add_device_list(int a_row);
  bool check_device_list(int a_row);
public:		// User declarations
  __fastcall TOptionsForm(TComponent* Owner);
  options_form_t* data();
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
