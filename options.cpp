//---------------------------------------------------------------------------
#include <irspch.h>
#pragma hdrstop

#include <irsstrm.h>
#include <irsparam.h>

#include "options.h"
#include "error.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#ifdef NOP
TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#ifdef NOP
class options_form_implementation_t: public options_form_t
{
public:
  typedef irs::string_t string_type;
  options_form_implementation_t(TOptionsForm* ap_OptionsForm,
    const string_type& a_device_name,
    const string_type& a_assembly_type,
    irs::param_box_base_t* ap_general_options);
  virtual const irs::string_t& device_name() const;
  virtual const irs::string_t& device_type() const;
  //virtual size_t device_count();
  virtual irs::param_box_base_t* general_options();
  virtual bool is_device_options_button_click();
  virtual bool is_inner_options_button_click();
  virtual bool is_import_button_click();
  virtual bool is_options_apply();
  virtual irs::string_t imported_ini_name();
  virtual void show();

  void device_options_button_click_exec();
  void inner_options_button_click_exec();
  void import_button_click_exec();
  void options_apply_exec();
  void imported_ini_name(const irs::string_t& a_name);
private:
  enum { m_device_list_fixed_cols = 1 };

  TOptionsForm* mp_OptionsForm;
  const string_type m_device_name;
  const string_type m_assembly_type;
  irs::param_box_base_t* mp_general_options;
  irs::event_t m_device_options_button_click_event;
  irs::event_t m_inner_options_button_click_event;
  irs::event_t m_import_button_click_event;
  irs::event_t m_options_apply_event;
  irs::string_t m_imported_ini_name;
};
options_form_implementation_t::options_form_implementation_t(
  TOptionsForm* ap_OptionsForm,
  const string_type& a_device_name,
  const string_type& a_assembly_type,
  irs::param_box_base_t* ap_general_options
):
  mp_OptionsForm(ap_OptionsForm),
  //mp_device_list(ap_device_list),
  m_device_name(a_device_name),
  m_assembly_type(a_assembly_type),
  mp_general_options(ap_general_options),
  m_device_options_button_click_event(),
  m_inner_options_button_click_event(),
  m_import_button_click_event(),
  m_options_apply_event()
{
}
const irs::string_t&
options_form_implementation_t::device_name() const
{
  /*TL4_ERROR_IF((0 > a_index) || (a_index >= device_count()),
    irs::ec_standard, "Вне диапазона");
  if ((0 > a_index) || (a_index >= device_count())) {
    return irst("Вне диапазона");
  }

  #ifdef NOP
  irs::mlog() << endl;
  irs::mlog() << "FixedCols = " << m_device_list_fixed_cols << endl;
  for (size_t device_idx = 0; device_idx < device_count(); ++device_idx) {
    AnsiString device_name_ansi =
      mp_device_list->Keys[device_idx + m_device_list_fixed_cols];
    irs::mlog() << device_idx << "; " << device_name_ansi.c_str() << "; ";
    AnsiString value_name_ansi = mp_device_list->Values[device_name_ansi];
    irs::mlog() << value_name_ansi.c_str() << endl;
  }
  irs::mlog() << endl;
  #endif //NOP
  */
  return m_device_name;
}
const irs::string_t& options_form_implementation_t::device_type() const
{
  /*TL4_ERROR_IF((0 > a_index) || (a_index >= device_count()),
    irs::ec_standard, "Вне диапазона");
  if ((0 > a_index) || (a_index >= device_count())) {
    return irst("Вне диапазона");
  }
  return mp_device_list->Values[device_names(a_index).c_str()].c_str();*/
  return m_assembly_type;
}
/*size_t options_form_implementation_t::device_count()
{
  return mp_device_list->RowCount - m_device_list_fixed_cols;
}*/
irs::param_box_base_t* options_form_implementation_t::general_options()
{
  return mp_general_options;
}
bool options_form_implementation_t::is_device_options_button_click()
{
  return m_device_options_button_click_event.check();
}
bool options_form_implementation_t::is_inner_options_button_click()
{
  return m_inner_options_button_click_event.check();
}
bool options_form_implementation_t::is_import_button_click()
{
  return m_import_button_click_event.check();
}
bool options_form_implementation_t::is_options_apply()
{
  return m_options_apply_event.check();
}
irs::string_t options_form_implementation_t::imported_ini_name()
{
  return m_imported_ini_name;
}
void options_form_implementation_t::show()
{
  mp_OptionsForm->ShowModal();
}
void options_form_implementation_t::device_options_button_click_exec()
{
  m_device_options_button_click_event.exec();
}
void options_form_implementation_t::inner_options_button_click_exec()
{
  m_inner_options_button_click_event.exec();
}
void options_form_implementation_t::import_button_click_exec()
{
  m_import_button_click_event.exec();
}
void options_form_implementation_t::options_apply_exec()
{
  m_options_apply_event.exec();
}
void options_form_implementation_t::imported_ini_name(
  const irs::string_t& a_name)
{
  m_imported_ini_name = a_name;
}
#endif // NOP
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner):
  TForm(Owner),
  //m_device_list_changed_event(),
  m_ini_file(),
  mp_general_options(new irs::param_box_t(irst("Общие настройки"),
    irst("general"))),
  m_options_tune(this)

{
  //String value_bstr = /*DeviceList*/DeviceListValueListEditor->Values[1];
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
TOptionsForm::options_tune_t::options_tune_t(
  TOptionsForm* ap_OptionsForm
) {
  //TValueListEditor* DeviceList = ap_OptionsForm->DeviceListValueListEditor;

  ap_OptionsForm->m_ini_file.set_section(irst("device_list"));
  //ap_OptionsForm->m_ini_file.add(irst("make_"), DeviceList,
    //irs::ini_file_t::vle_load_full);



  ap_OptionsForm->options_load();

  //ap_OptionsForm->cur_device_update();
  irs::handle_t<irs::param_box_base_t> p_general_options =
    ap_OptionsForm->mp_general_options;
  //p_general_options->add_edit(irst("Порт"), irst("5005"));
  p_general_options->load();
}
//---------------------------------------------------------------------------


/*void sort_value_list_editor(TValueListEditor* ap_value_list_editor)
{

  size_t row_count = ap_value_list_editor->RowCount;
  typedef map<irs::string_t, irs::string_t, less_nocase_t> list_t;
  list_t cont_list;
  for (size_t row_index = 1; row_index < row_count; ++row_index) {
    irs::string_t key = ap_value_list_editor->Keys[row_index].c_str();
    irs::string_t value = ap_value_list_editor->Values[key.c_str()].c_str();
    cont_list[key] = value;
  }

  ap_value_list_editor->Strings->Clear();

  typedef list_t::iterator list_it_t;
    for (list_it_t list_it = cont_list.begin(); list_it != cont_list.end();
    ++list_it)
  {
    static const bool append = true;
    String key = list_it->first.c_str();
    String value = list_it->second.c_str();
    ap_value_list_editor->InsertRow(key, value, append);
  }
}*/
void TOptionsForm::options_load()
{
  m_ini_file.load();
  /*sort_value_list_editor(DeviceListValueListEditor);
  enum_assembly_types();
  const int row_count = DeviceListValueListEditor->RowCount;
  for (int row_idx = 1; row_idx < row_count; row_idx++) {
    add_device_list(row_idx);
  }*/
}
//---------------------------------------------------------------------------
/*void TOptionsForm::cur_device_update()
{
  irs::string_t device_name_def = irst("");
  const int row_count = DeviceListValueListEditor->RowCount;
  if (row_count > 1) {
    device_name_def = DeviceListValueListEditor->Keys[1].c_str();
  }

  mp_general_options->add_edit(irst("Текущее устройство"), device_name_def);
  mp_general_options->load();
  irs::string_t cur_device = mp_general_options->
    get_param(irst("Текущее устройство"));
  mp_general_options->delete_edit(irst("Текущее устройство"));
  mp_general_options->add_edit(irst("Текущее устройство"), device_name_def);
  for (int row_idx = 1; row_idx < row_count; row_idx++) {
    irs::string_t device_name =
      DeviceListValueListEditor->Keys[row_idx].c_str();
    mp_general_options->add_combo_by_item(irst("Текущее устройство"),
      device_name);
  }
  mp_general_options->set_param(irst("Текущее устройство"), cur_device);
} */
//---------------------------------------------------------------------------
options_form_t* TOptionsForm::data()
{
  return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::OkButtonClick(TObject *Sender)
{
  //cur_device_update();
  m_ini_file.save();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::CancelButtonClick(TObject *Sender)
{
  options_load();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/*bool TOptionsForm::check_device_list(int a_row)
{
  String Key = DeviceListValueListEditor->Keys[a_row];
  int PickListCount =
    DeviceListValueListEditor->ItemProps[Key]->PickList->Count;
  return PickListCount != 0;
} */
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::FormKeyUp(TObject *Sender, WORD &Key,
  TShiftState Shift)
{
  if (OptionsPageControl->ActivePage == DeviceListSheet) {
    
  }
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::GeneralOptionsButtonClick(TObject *Sender)
{
  mp_general_options->show();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::ImportButtonClick(TObject *Sender)
{
  //m_imported_ini_name; ImportOpenDialog
  
}
//---------------------------------------------------------------------------
#endif // NOP
