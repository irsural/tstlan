// ---------------------------------------------------------------------------
#include <irspch.h>
#pragma hdrstop

#include <irstest.h>
#include <irsstring.h>
#include <irsstrconv.h>
#include <cbsysutils.h>
#include <tstlan5lib.h>

#include "main.h"
#include "locktick.h"
#include "error.h"

#include <irsfinal.h>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxClasses"
#pragma link "cxControls"
#pragma link "cxCustomData"
#pragma link "cxData"
#pragma link "cxDataStorage"
#pragma link "cxDBData"
#pragma link "cxEdit"
#pragma link "cxFilter"
#pragma link "cxGraphics"
#pragma link "cxGrid"
#pragma link "cxGridCustomTableView"
#pragma link "cxGridCustomView"
#pragma link "cxGridDBTableView"
#pragma link "cxGridLevel"
#pragma link "cxGridTableView"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxStyles"
#pragma link "dxSkinBlack"
#pragma link "dxSkinBlue"
#pragma link "dxSkinBlueprint"
#pragma link "dxSkinCaramel"
#pragma link "dxSkinCoffee"
#pragma link "dxSkinDarkRoom"
#pragma link "dxSkinDarkSide"
#pragma link "dxSkinDevExpressDarkStyle"
#pragma link "dxSkinDevExpressStyle"
#pragma link "dxSkinFoggy"
#pragma link "dxSkinGlassOceans"
#pragma link "dxSkinHighContrast"
#pragma link "dxSkiniMaginary"
#pragma link "dxSkinLilian"
#pragma link "dxSkinLiquidSky"
#pragma link "dxSkinLondonLiquidSky"
#pragma link "dxSkinMcSkin"
#pragma link "dxSkinMoneyTwins"
#pragma link "dxSkinOffice2007Black"
#pragma link "dxSkinOffice2007Blue"
#pragma link "dxSkinOffice2007Green"
#pragma link "dxSkinOffice2007Pink"
#pragma link "dxSkinOffice2007Silver"
#pragma link "dxSkinOffice2010Black"
#pragma link "dxSkinOffice2010Blue"
#pragma link "dxSkinOffice2010Silver"
#pragma link "dxSkinPumpkin"
#pragma link "dxSkinsCore"
#pragma link "dxSkinscxPCPainter"
#pragma link "dxSkinsDefaultPainters"
#pragma link "dxSkinSeven"
#pragma link "dxSkinSevenClassic"
#pragma link "dxSkinSharp"
#pragma link "dxSkinSharpPlus"
#pragma link "dxSkinSilver"
#pragma link "dxSkinSpringTime"
#pragma link "dxSkinStardust"
#pragma link "dxSkinSummer2008"
#pragma link "dxSkinTheAsphaltWorld"
#pragma link "dxSkinValentine"
#pragma link "dxSkinVS2010"
#pragma link "dxSkinWhiteprint"
#pragma link "dxSkinXmas2008Blue"
#pragma link "cxCheckBox"
#pragma link "cxDropDownEdit"
#pragma link "cxCheckGroup"
#pragma link "cxTextEdit"
#pragma link "cxInplaceContainer"
#pragma link "cxTL"
#pragma link "cxTLdxBarBuiltInMenu"
#pragma link "cxBlobEdit"
#pragma link "cxButtonEdit"
#pragma link "cxHyperLinkEdit"
#pragma link "cxCalc"
#pragma link "cxCurrencyEdit"
#pragma resource "*.dfm"

TMainForm *MainForm;

// ---------------------------------------------------------------------------
// 18.04.2013 tstlan4 1.0.0.185 rev. 53 mxsrclib rev. 1123
// 09.05.2011
// CodeGuard выявил баги:
// - При записи в поток с широкими символами (а может и не только с широкими)
// числа вызывается функция буфера setg с подозрительными параметрами. Но,
// судя по всему, это осознаный вызов, а не ошибка. CodeGuard же
// рассматривает это как ошибку.
// - При открытии файлового потока в C++ Builder 2010 есть возможность
// задавать имя файла через const wchar_t*, хотя по стандарту, независимо
// от типа символа передаваемого в шаблон, открывается файл только через
// const char*. Если имя файла задавать через const wchar_t*, то
// при попытке открыть происходит переполнение буфера при конвертации
// имени из wchar_t в char (csvwork.cpp:165)
// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) :
  TForm(Owner),
  mp_memo_buf(new irs::memobuf(LogMemo, 200)),
  m_cfg(),
  m_app(&m_cfg),
  m_ini_file(),
  m_devices_config_dir(irst("devices")),
  m_device_config_file_ext(irst("ini")),
  m_device_options_section(irst("device")),
  m_assembly_type_list(),
  m_assembly_type_default(),
  m_devices()
{
  enum {
    clearance = 10
  };
  Top = clearance;
  Left = clearance;
  Height = Screen->WorkAreaHeight - 2 * clearance;
  Width = 550;

  m_ini_file.set_ini_name(m_cfg.ini_name().c_str());
  m_ini_file.set_section("MainForm");
  m_ini_file.add("", this);
  m_ini_file.load();

  irs::mlog().rdbuf(mp_memo_buf.get());

  irs::cbuilder::file_version_t file_version;
  irs::cbuilder::get_file_version(Application->ExeName.c_str(), file_version);
  const string_type file_version_str =
    irs::cbuilder::file_version_to_str(file_version);

  String program_name = irst("Тест сети ") +
    irs::str_conv<String>(file_version_str);
  MainForm->Caption = program_name;
  Application->Title = program_name;

  irs::irs_string_t version_str = IRS_SIMPLE_FROM_TYPE_STR
    (irs::cbuilder::file_version_to_str(file_version).c_str());
  irs::mlog() << "Версия: " << version_str << endl;
  irs::mlog() << endl;

  /* NameEdit->Hint =
  irst("Ctrl+N - переход в поле ввода имени\n")
  irst("Ctrl+L - переход в список устройств\n")
  irst("Ctrl+Insert - добавить устройство\n")
  irst("Ctrl+Delete - удалить выделенные устройства\n")
  irst("Ctrl+R - переименовать устройство"); */
  // NameEdit->ShowHint = true;

  irs::mxdata_assembly_types()->enum_types(&m_assembly_type_list);
  TcxComboBoxProperties* Props = dynamic_cast<TcxComboBoxProperties*>
    (TypeColumn->Properties);
  for (std::size_t i = 0; i < m_assembly_type_list.size(); i++) {
    Props->Items->Add(irs::str_conv<String>(m_assembly_type_list[i]));
  }
  m_assembly_type_default = m_assembly_type_list.at(0);

  load_devices_list();

  m_app.set_devices(m_devices);
}

void TMainForm::create_devices_dir()
{
  String dir = GetCurrentDir() + irst("\\") + irs::str_conv<String>
    (m_devices_config_dir);
  if (!DirectoryExists(dir)) {
    if (!ForceDirectories(dir)) {
      throw Exception(irst("Не удалось создать директорию ") + dir);
    }
  }
}

void TMainForm::load_devices_list()
{
  DevicesCXGrid->ActiveView->DataController->RecordCount = 0;

  TSearchRec sr;
  String dir = GetCurrentDir() + irst("\\") + irs::str_conv<String>
    (m_devices_config_dir);

  String filter = dir + String(irst("\\*")) + irst(".") + irs::str_conv<String>
    (m_device_config_file_ext);
  DevicesCXGrid->ActiveView->BeginUpdate();
  if (FindFirst(filter, faAnyFile, sr) == 0) {
    add_device(dir + irst("\\") + sr.Name);
    while (FindNext(sr) == 0) {
      add_device(dir + irst("\\") + sr.Name);
    }
  }
  DevicesCXGrid->ActiveView->EndUpdate();
  FindClose(sr);
}

void TMainForm::add_device(const String& a_file_name)
{
  create_devices_dir();
  irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_file_name);
  ini_file.set_section(m_device_options_section);
  tstlan4::device_options_t device_options;

  ini_file.add(irst("enabled"), &device_options.enabled);
  ini_file.add(irst("type"), &device_options.type);
  ini_file.load();
  if (!FileExists(a_file_name.c_str())) {
    ini_file.save();
  }

  string_type name = irs::str_conv<string_type>(a_file_name);
  m_devices.insert(make_pair(name, device_options));
  int row = DevicesCXGrid->ActiveView->DataController->RecordCount;
  DevicesCXGrid->ActiveView->DataController->RecordCount = row + 1;
  DevicesCXGrid->ActiveView->DataController->Values[row][NameColumn->Index]
    = Variant(ExtractFileUltraShortName(a_file_name));
  DevicesCXGrid->ActiveView->DataController->Values[row][FileNameColumn->Index]
    = Variant(a_file_name);
  DevicesCXGrid->ActiveView->DataController->Values[row][EnabledColumn->Index]
    = Variant(device_options.enabled);
  if (std::find(m_assembly_type_list.begin(), m_assembly_type_list.end(),
      device_options.type) != m_assembly_type_list.end()) {
    DevicesCXGrid->ActiveView->DataController->Values[row][TypeColumn->Index]
      = Variant(irs::str_conv<String>(device_options.type));
  } else {
    DevicesCXGrid->ActiveView->DataController->Values[row][TypeColumn->Index]
      = Variant(irs::str_conv<String>(m_assembly_type_default));
  }
}

// ---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
  m_ini_file.save();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::TickTimerTimer(TObject *Sender)
{
  if (!tstlan4::tick_lock()->check()) {
    m_app.tick();
  }
}
// ---------------------------------------------------------------------------

struct less_nocase_t {
  bool operator()(const irs::string_t & a_left, const irs::string_t & a_right)
      const {
    irs::string_t left;
    irs::string_t right;
    transform(a_left.begin(), a_left.end(), back_inserter(left),
      toloweru<irs::char_t>);
    transform(a_right.begin(), a_right.end(), back_inserter(right),
      toloweru<irs::char_t>);
    return left < right;
  }
};



void TMainForm::enum_assembly_types()
{
  irs::mxdata_assembly_types()->enum_types(&m_assembly_type_list);
}

String TMainForm::ExtractFileUltraShortName(const String& Name)
{
  String ShortFileName = ExtractFileName(Name);
  String ExtFileName = ExtractFileExt(ShortFileName);
  int LengthFileName = ShortFileName.Length();
  int LengthExt = ExtFileName.Length();
  if (LengthFileName > LengthExt) {
    ShortFileName = ShortFileName.SubString(1, LengthFileName - LengthExt);
  }
  return ShortFileName;
}

String TMainForm::MakeFileFullName(const String& aUltraShortName)
{
  return irs::str_conv<String>(make_file_full_name(
    irs::str_conv<string_type>(aUltraShortName)));
}

TMainForm::string_type TMainForm::make_file_full_name(
  const string_type& a_file_ultra_short_name)
{
  string_type dir = irs::str_conv<string_type>(GetCurrentDir()) + irst("\\") +
    m_devices_config_dir;
  return dir + irst("\\") + a_file_ultra_short_name + irst(".") +
    m_device_config_file_ext;
}

TPoint TMainForm::GetFocusedCellCoord()
{
  TcxCustomGridTableView * AView = (TcxCustomGridTableView*)
    DevicesCXGrid->FocusedView;
  TcxCustomGridTableController * AController = AView->Controller;
  int row = AController->FocusedRecordIndex;
  int col = AController->FocusedItemIndex;
  TPoint point;
  point.x = AController->FocusedItemIndex;
  point.y = AController->FocusedRecordIndex;
  return point;
}
// ---------------------------------------------------------------------------

TMainForm::string_type TMainForm::generate_new_unique_name(
  const string_type& a_device_name)
{
  int i = 1;
  while (true) {
    const string_type new_full_file_name = make_file_full_name
      (a_device_name + irst("_") + irs::num_to_str(i));
    if (m_devices.find(new_full_file_name) == m_devices.end()) {
      return new_full_file_name;
    }
    i++;
  }
}
// ---------------------------------------------------------------------------


void __fastcall TMainForm::OptionsColumnPropertiesButtonClick(TObject *Sender,
  int AButtonIndex)
{
  String name = FileNameColumn->EditValue;
  m_app.show_device_options(irs::str_conv<string_type>(name));
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ShowTstlanColumnPropertiesButtonClick(
  TObject *Sender, int AButtonIndex)
{
  String name = FileNameColumn->EditValue;
  m_app.show_tstlan4lib(irs::str_conv<string_type>(name));
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::NameColumnPropertiesValidate(TObject *Sender,
  Variant &DisplayValue, TCaption &ErrorText, bool &Error)
{
  TPoint point = GetFocusedCellCoord();
  int row = point.y;
  int col = point.x;
  if (col == NameColumn->Index) {
    const String newname_bstr = DisplayValue;
    const string_type new_name = irs::str_conv<string_type>(newname_bstr);
    if (new_name.empty()) {
      ErrorText = irst("Имя не может быть пустым");
      Error = true;
      return;
    }
    const String file_name_bstr =
      DevicesCXGrid->ActiveView->DataController->Values[row]
      [FileNameColumn->Index];
    const string_type file_name = irs::str_conv<string_type>(file_name_bstr);
    std::map<string_type,
    tstlan4::device_options_t>::iterator it = m_devices.find(file_name);
    IRS_LIB_ASSERT(it != m_devices.end());
    const string_type new_file_name = make_file_full_name(new_name);
    if (!RenameFile(file_name_bstr, irs::str_conv<String>(new_file_name))) {
      ErrorText = irst("Ошибка при переименовании файла");
      Error = true;
      return;
    }
    String grid_conf_file_name =
      create_grid_configuration_file_full_name(file_name_bstr);
    String new_grid_conf_file_name =
      create_grid_configuration_file_full_name(
      irs::str_conv<String>(new_file_name));

    RenameFile(grid_conf_file_name, new_grid_conf_file_name);

    tstlan4::device_options_t device_options = it->second;
    m_devices.erase(it);
    m_devices.insert(make_pair(new_file_name, device_options));
    DevicesCXGrid->ActiveView->DataController->Values[row]
      [FileNameColumn->Index] = Variant(irs::str_conv<String>(new_file_name));
    m_app.set_devices(m_devices);

    // tstlan при уничтожении восстанавливает файл. Удаляем его еще раз
    DeleteFile(file_name_bstr);
    DeleteFile(grid_conf_file_name);
  }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteDeviceActionExecute(TObject *Sender)
{
  TPoint point = GetFocusedCellCoord();
  const String file_full_name_bstr =
    DevicesCXGrid->ActiveView->DataController->Values[point.y]
    [FileNameColumn->Index];

  if (!DeleteFile(file_full_name_bstr)) {
    Application->MessageBox(irst("Удалить файл не удалось"), irst("Ошибка"),
      MB_OK + MB_ICONERROR);
    return;
  }
  DevicesCXGrid->ActiveView->DataController->DeleteSelection();
  const string_type file_full_name = irs::str_conv<string_type>
    (file_full_name_bstr);
  IRS_LIB_ASSERT(m_devices.find(file_full_name) != m_devices.end());
  m_devices.erase(file_full_name);
  m_app.set_devices(m_devices);
  // tstlan при уничтожении восстанавливает файл. Удаляем его еще раз
  DeleteFile(file_full_name_bstr);
  String grid_configuration_file_name =
    create_grid_configuration_file_full_name(file_full_name_bstr);
  DeleteFile(grid_configuration_file_name);
}

String TMainForm::create_grid_configuration_file_full_name(
  const String& a_device_file_full_name)
{
  String grid_options_file_ext =
    irs::str_conv<String>(irs::tstlan::get_grid_options_file_ext());
  String grid_configuration_file_name =
    ExtractFileDir(a_device_file_full_name) +
    irst("\\") + irs::extract_file_ultra_short_name(a_device_file_full_name) +
    irst(".") + grid_options_file_ext;
  return grid_configuration_file_name;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::CopyDeviceActionExecute(TObject *Sender)
{
  TPoint point = GetFocusedCellCoord();
  const String file_name_bstr =
    DevicesCXGrid->ActiveView->DataController->Values[point.y]
    [FileNameColumn->Index];

  const String device_name_bstr = ExtractFileUltraShortName
    (irs::str_conv<String>(file_name_bstr));
  const String new_file_name_bstr = irs::str_conv<String>
    (generate_new_unique_name(irs::str_conv<string_type>(device_name_bstr)));
  if (!CopyFileTo(file_name_bstr, new_file_name_bstr)) {
    Application->MessageBox(irst("Создать копию файла не удалось"),
      irst("Ошибка"), MB_OK + MB_ICONERROR);
    return;
  }
  add_device(new_file_name_bstr);
  m_app.set_devices(m_devices);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::AddDeviceActionExecute(TObject *Sender)
{
  const string_type file_full_name = generate_new_unique_name
    (irst("новое_устройство"));
  add_device(irs::str_conv<String>(file_full_name));
  m_app.set_devices(m_devices);
}
// ---------------------------------------------------------------------------


void __fastcall TMainForm::ImportActionExecute(TObject *Sender)
{
  if (ImportOpenDialog->Execute()) {
    const string_type destination = string_type(irst(".\\"))
        + m_devices_config_dir + +irst(".") + m_device_config_file_ext;
    m_app.import(irs::str_conv<string_type>(ImportOpenDialog->FileName),
      destination);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  irs::ini_file_t ini_file;
  ini_file.set_section(m_device_options_section);
  tstlan4::device_options_t device_options;
  ini_file.add(irst("enabled"), &device_options.enabled);
  ini_file.add(irst("type"), &device_options.type);
  devices_type::const_iterator it = m_devices.begin();
  while (it != m_devices.end()) {
    ini_file.set_ini_name(irs::str_conv<String>(it->first));
    device_options = it->second;
    ini_file.save();
    ++it;
  }
}
//---------------------------------------------------------------------------

TMainForm::devices_type::iterator TMainForm::get_focused_device()
{
  TPoint point = GetFocusedCellCoord();
  const String file_full_name_bstr =
    DevicesCXGrid->ActiveView->DataController->Values[point.y]
    [FileNameColumn->Index];
  devices_type::iterator it = m_devices.find(
    irs::str_conv<string_type>(file_full_name_bstr));
  return it;
}

void __fastcall TMainForm::EnabledColumnPropertiesChange(TObject *Sender)
{
  DevicesCXGrid->ActiveView->DataController->PostEditingData();
  TPoint point = GetFocusedCellCoord();
  devices_type::iterator it = get_focused_device();
  IRS_LIB_ASSERT(it != m_devices.end());
  it->second.enabled = DevicesCXGrid->ActiveView->DataController->
    Values[point.y][EnabledColumn->Index];
  m_app.set_devices(m_devices);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TypeColumnPropertiesChange(TObject *Sender)
{
  DevicesCXGrid->ActiveView->DataController->PostEditingData();
  TPoint point = GetFocusedCellCoord();
  devices_type::iterator it = get_focused_device();
  String type_bstr = DevicesCXGrid->ActiveView->DataController->Values
    [point.y][TypeColumn->Index];
  it->second.type = irs::str_conv<string_type>(type_bstr);
  m_app.set_devices(m_devices);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ShowChartActionExecute(TObject *Sender)
{
  m_app.show_chart();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OptionsActionExecute(TObject *Sender)
{
  m_app.show_modal_options();
}
//---------------------------------------------------------------------------

