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
#include <Dialogs.hpp>
//---------------------------------------------------------------------------

struct device_t
{
  typedef irs::string_t string_type;
  string_type name;
  string_type type;
  bool enabled;
  device_t():
    name(),
    type(),
    enabled(false)
  {
  }
};

class options_form_t
{
public:
  typedef std::vector<device_t> devices_type;
  ~options_form_t() {}
  virtual const devices_type& get_devices() const = 0;
  //virtual const irs::string_t& device_name() const = 0;
  //virtual const irs::string_t& device_type() const = 0;
  //virtual size_t device_count() = 0;
  virtual irs::param_box_base_t* general_options() = 0;
  virtual bool is_device_options_button_click() = 0;
  virtual bool is_inner_options_button_click() = 0;
  //virtual bool is_import_button_click() = 0;
  virtual bool is_options_apply() = 0;
  //virtual irs::string_t imported_ini_name() = 0;
  virtual void show() = 0;
};

//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
  TPageControl *OptionsPageControl;
  TTabSheet *GeneralSheet;
  TTabSheet *DeviceListSheet;
  TPanel *ButtonPanel;
  TButton *OkButton;
  TButton *CancelButton;
  TButton *ApplyButton;
  TButton *GeneralOptionsButton;
  TButton *InnerButton;
  void __fastcall OkButtonClick(TObject *Sender);
  void __fastcall CancelButtonClick(TObject *Sender);
  void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall GeneralOptionsButtonClick(TObject *Sender);
  void __fastcall ImportButtonClick(TObject *Sender);
private:	// User declarations
  struct options_tune_t {
    options_tune_t(TOptionsForm* ap_OptionsForm);
  };
  friend class options_tune_t;

  irs::ini_file_t m_ini_file;
  irs::handle_t<irs::param_box_base_t> mp_general_options;
  options_tune_t m_options_tune;
  irs::handle_t<options_form_t> mp_options_form;


  //bool check_device_list(int a_row);

  void options_load();
  //void cur_device_update();
public:		// User declarations
  __fastcall TOptionsForm(TComponent* Owner);
  options_form_t* data();
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
