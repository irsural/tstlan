//---------------------------------------------------------------------------
#include <irspch.h>
#pragma hdrstop

#include <irsstrm.h>

#include "options.h"
#include "error.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner):
  TForm(Owner),
  m_device_list_changed_event(),
  m_ini_file(),
  mp_assembly_types(irs::mxdata_assembly_types()),
  m_assembly_type_list()
{
  m_ini_file.set_section(irst("device_list"));
  m_ini_file.add(irst("make_"), DeviceListValueListEditor,
    irs::ini_file_t::vle_load_full);
  m_ini_file.load();
  DeviceListValueListEditor->KeyOptions =
    TKeyOptions() << keyUnique; //keyEdit << keyAdd << keyDelete <<

  mp_assembly_types->enum_types(&m_assembly_type_list);

  // Здесь намеренно не используется irst, т. к. С++ Builder 2010 неправильно
  // в исходниках преобразует из кодовой страницы 1251 в юникод
  NameEdit->Hint =
    "Ctrl+N - переход в поле ввода имени\n"
    "Ctrl+L - переход в список устройств\n"
    "Ctrl+Insert - добавить устройство\n"
    "Ctrl+Delete - удалить выделенные устройства\n"
    "Ctrl+R - переименовать устройство";
  NameEdit->ShowHint = true;
}
//---------------------------------------------------------------------------
void TOptionsForm::device_list_changed_event_add(irs::event_t* ap_event)
{
  m_device_list_changed_event.push_back(ap_event);
}
//---------------------------------------------------------------------------
void TOptionsForm::device_list_changed_event_clear()
{
  m_device_list_changed_event.clear();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::OkButtonClick(TObject *Sender)
{
  m_ini_file.save();
  m_device_list_changed_event.exec();
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::ApplyButtonClick(TObject *Sender)
{
  m_ini_file.save();
  m_device_list_changed_event.exec();
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

