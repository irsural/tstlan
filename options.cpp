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
TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
class options_form_implementation_t: public options_form_t
{
public:
  options_form_implementation_t(TOptionsForm* ap_OptionsForm,
    TValueListEditor *ap_device_list,
    irs::param_box_base_t* ap_general_options);
  virtual irs::string_t device_names(size_t a_index);
  virtual irs::string_t device_types(size_t a_index);
  virtual size_t device_count();
  virtual irs::param_box_base_t* general_options();
  virtual bool is_device_options_button_click();
  virtual bool is_options_apply();
  virtual void show();
  void device_options_button_click_exec();
  void options_apply_exec();
private:
  //enum { m_values_shift = 1 };

  TOptionsForm* mp_OptionsForm;
  TValueListEditor *mp_device_list;
  irs::param_box_base_t* mp_general_options;
  irs::event_t m_device_options_button_click_event;
  irs::event_t m_options_apply_event;
};
options_form_implementation_t::options_form_implementation_t(
  TOptionsForm* ap_OptionsForm,
  TValueListEditor *ap_device_list,
  irs::param_box_base_t* ap_general_options
):
  mp_OptionsForm(ap_OptionsForm),
  mp_device_list(ap_device_list),
  mp_general_options(ap_general_options),
  m_device_options_button_click_event(),
  m_options_apply_event()
{
}
irs::string_t options_form_implementation_t::device_names(size_t a_index)
{
  TL4_ERROR_IF((0 > a_index) || (a_index >= device_count()),
    irs::ec_standard, "Вне диапазоны");
  if ((0 > a_index) || (a_index >= device_count())) {
    return irst("Вне диапазоны");
  }
  return mp_device_list->Keys[a_index + mp_device_list->FixedCols].c_str();
}
irs::string_t options_form_implementation_t::device_types(size_t a_index)
{
  TL4_ERROR_IF((0 > a_index) || (a_index >= device_count()),
    irs::ec_standard, "Вне диапазоны");
  if ((0 > a_index) || (a_index >= device_count())) {
    return irst("Вне диапазоны");
  }
  return mp_device_list->Values[device_names(a_index).c_str()].c_str();
}
size_t options_form_implementation_t::device_count()
{
  return mp_device_list->RowCount - mp_device_list->FixedCols;
}
irs::param_box_base_t* options_form_implementation_t::general_options()
{
  return mp_general_options;
}
bool options_form_implementation_t::is_device_options_button_click()
{
  return m_device_options_button_click_event.check();
}
bool options_form_implementation_t::is_options_apply()
{
  return m_options_apply_event.check();
}
void options_form_implementation_t::show()
{
  mp_OptionsForm->ShowModal();
}
void options_form_implementation_t::device_options_button_click_exec()
{
  m_device_options_button_click_event.exec();
}
void options_form_implementation_t::options_apply_exec()
{
  m_options_apply_event.exec();
}
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner):
  TForm(Owner),
  //m_device_list_changed_event(),
  m_ini_file(),
  m_assembly_type_list(),
  mp_general_options(new irs::param_box_t(irst("Общие настройки"),
    irst("general"))),
  m_options_tune(this),
  mp_options_form(new options_form_implementation_t(
    this, DeviceListValueListEditor, mp_general_options.get()
  ))
{
  irs::mxdata_assembly_types()->enum_types(&m_assembly_type_list);

  NameEdit->Hint =
    irst("Ctrl+N - переход в поле ввода имени\n")
    irst("Ctrl+L - переход в список устройств\n")
    irst("Ctrl+Insert - добавить устройство\n")
    irst("Ctrl+Delete - удалить выделенные устройства\n")
    irst("Ctrl+R - переименовать устройство");
  NameEdit->ShowHint = true;
}
//---------------------------------------------------------------------------
TOptionsForm::options_tune_t::options_tune_t(
  TOptionsForm* ap_OptionsForm
):
  mp_OptionsForm(ap_OptionsForm)
{
  TValueListEditor* DeviceList = mp_OptionsForm->DeviceListValueListEditor;

  mp_OptionsForm->m_ini_file.set_section(irst("device_list"));
  mp_OptionsForm->m_ini_file.add(irst("make_"), DeviceList,
    irs::ini_file_t::vle_load_full);
  mp_OptionsForm->m_ini_file.load();

  DeviceList->KeyOptions = TKeyOptions() << keyUnique;

  irs::string_t device_name_def = irst("");
  int row_count = DeviceList->RowCount;
  if (row_count > 1) {
    device_name_def = DeviceList->Keys[1].c_str();
  }

  irs::param_box_base_t* p_general_options =
    mp_OptionsForm->mp_general_options.get();
  p_general_options->add_edit(irst("Текущее устройство"), device_name_def);
  for (int row_idx = 1; row_idx < row_count; row_idx++) {
    irs::string_t device_name = DeviceList->Keys[row_idx].c_str();
    p_general_options->add_combo_by_item(irst("Текущее устройство"),
      device_name);
  }
  //p_general_options->add_edit(irst("Порт"), irst("5005"));
  p_general_options->load();
}
//---------------------------------------------------------------------------
options_form_t* TOptionsForm::data()
{
  return mp_options_form.get();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::OkButtonClick(TObject *Sender)
{
  m_ini_file.save();
  //m_device_list_changed_event.exec();
  options_form_implementation_t* p_options_form_implementation =
    static_cast<options_form_implementation_t*>(mp_options_form.get());
  p_options_form_implementation->options_apply_exec();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::ApplyButtonClick(TObject *Sender)
{
  m_ini_file.save();
  //m_device_list_changed_event.exec();
  options_form_implementation_t* p_options_form_implementation =
    static_cast<options_form_implementation_t*>(mp_options_form.get());
  p_options_form_implementation->options_apply_exec();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::CancelButtonClick(TObject *Sender)
{
  m_ini_file.load();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
  m_ini_file.load();
}
//---------------------------------------------------------------------------
void TOptionsForm::add_device_list(int a_row)
{
  String Key = DeviceListValueListEditor->Keys[a_row];
  size_t list_size = m_assembly_type_list.size();
  for (size_t list_idx = 0; list_idx < list_size; list_idx++) {
    DeviceListValueListEditor->ItemProps[Key]->PickList->
      Add(m_assembly_type_list.at(list_idx).c_str());
  }
}
//---------------------------------------------------------------------------
bool TOptionsForm::check_device_list(int a_row)
{
  String Key = DeviceListValueListEditor->Keys[a_row];
  int PickListCount =
    DeviceListValueListEditor->ItemProps[Key]->PickList->Count;
  return PickListCount != 0;
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::AddButtonClick(TObject *Sender)
{
  if (!NameEdit->Text.IsEmpty()) {
    int row = 0;
    if (!DeviceListValueListEditor->FindRow(NameEdit->Text, row)) {
      int row_sel = DeviceListValueListEditor->Row;
      int row_count = DeviceListValueListEditor->RowCount;
      if (row_count > 1) {
        String key = DeviceListValueListEditor->Keys[1];
        if (NameEdit->Text < key) {
          DeviceListValueListEditor->Row = 1;
          DeviceListValueListEditor->InsertRow(NameEdit->Text, "", false);
        } else {
          for (int row_idx = 1; row_idx < row_count; row_idx++) {
            String key = DeviceListValueListEditor->Keys[row_idx];
            if (NameEdit->Text > key) {
              DeviceListValueListEditor->Row = row_idx;
              DeviceListValueListEditor->InsertRow(NameEdit->Text, "", true);
              break;
            }
          }
        }
      } else {
        DeviceListValueListEditor->InsertRow(NameEdit->Text, "", true);
      }
      int row = 0;
      if (DeviceListValueListEditor->FindRow(NameEdit->Text, row)) {
        add_device_list(row);
        String key = DeviceListValueListEditor->Keys[row];
        if (m_assembly_type_list.size() > 0) {
          DeviceListValueListEditor->Values[key] =
            m_assembly_type_list.at(0).c_str();
        }
      } else {
        TL4_ASSERT_MSG("Устройство не найдено");
      }
      DeviceListValueListEditor->Row = row_sel;
      NameEdit->Text = "";
    } else {
      ShowMessage(irst("Устройство существует"));
    }
  } else {
    ShowMessage(irst("Пустое название устройства недопустимо"));
  }
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::DeleteButtonClick(TObject *Sender)
{
  TGridRect GridRect = DeviceListValueListEditor->Selection;
  for (int row_idx = GridRect.Top; row_idx <= GridRect.Bottom; row_idx++) {
    DeviceListValueListEditor->DeleteRow(row_idx);
  }
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::RenameButtonClick(TObject *Sender)
{
  TGridRect GridRect = DeviceListValueListEditor->Selection;
  DeviceListValueListEditor->Keys[GridRect.Top] = NameEdit->Text;
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::DeviceListValueListEditorSelectCell(
  TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
  NameEdit->Text = DeviceListValueListEditor->Keys[ARow];
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::FormKeyUp(TObject *Sender, WORD &Key,
  TShiftState Shift)
{
  if (OptionsPageControl->ActivePage == DeviceListSheet) {
    if (Shift.Contains(ssCtrl)) {
      switch (Key) {
        case 'N': {
          NameEdit->SetFocus();
        } break;
        case 'L': {
          DeviceListValueListEditor->SetFocus();
        } break;
        case VK_INSERT: {
          AddButtonClick(this);
        } break;
        case VK_DELETE: {
          DeleteButtonClick(this);
        } break;
        case 'R': {
          RenameButtonClick(this);
        } break;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::GeneralOptionsButtonClick(TObject *Sender)
{
  mp_general_options->show();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::DeviceOptionsButtonClick(TObject *Sender)
{
  options_form_implementation_t* p_options_form_implementation =
    static_cast<options_form_implementation_t*>(mp_options_form.get());
  p_options_form_implementation->device_options_button_click_exec();
}
//---------------------------------------------------------------------------

