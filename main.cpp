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
/*#include "tstlan5lib.h"
#include "MxChart.h"
#include "MxBase.h"*/
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
#pragma link "dxColorEdit"
#pragma link "cxColorComboBox"
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
  m_grid_options_file_name(),
  m_devices_config_dir(irst("devices")),
  m_device_config_file_ext(irst("ini")),
  m_device_options_section(irst("device")),
  m_chart_position(),
  m_assembly_type_list(),
  m_assembly_type_default(),
  m_devices(),
  m_update_status_timer(irs::make_cnt_s(0.5)),
  m_update_options_timer(irs::make_cnt_s(0.5))
{
  enum {
    clearance = 10
  };
  Top = clearance;
  Left = clearance;
  Height = Screen->WorkAreaHeight - 2 * clearance;
  Width = 550;

  m_chart_position = m_app.chart()->position();

  const string_type exe_dir = irs::str_conv<string_type>(ExtractFileDir(
    Application->ExeName));

  m_grid_options_file_name = exe_dir + irst("\\") +
    m_cfg.grid_options_file_name();

  m_ini_file.set_ini_name(m_cfg.ini_name().c_str());
  m_ini_file.set_section("MainForm");
  m_ini_file.add("", this);
  m_ini_file.set_section("ChartForm");
  m_ini_file.add(String("left"),
    reinterpret_cast<irs_u32*>(&m_chart_position.left));
  m_ini_file.add("top", reinterpret_cast<irs_u32*>(&m_chart_position.top));
  m_ini_file.add("right", reinterpret_cast<irs_u32*>(&m_chart_position.right));
  m_ini_file.add("bottom",
    reinterpret_cast<irs_u32*>(&m_chart_position.bottom));
  m_ini_file.load();

  load_grid_options();

  m_app.chart()->set_position(m_chart_position);

  update_options();

  irs::cbuilder::file_version_t file_version;
  irs::cbuilder::get_file_version(Application->ExeName.c_str(), file_version);
  const string_type file_version_str = irs::cbuilder::file_version_to_str
    (file_version);
  String program_name = irst("Тест сети ") + irs::str_conv<String>
    (file_version_str);

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

  const vector<string_type>bad_devices = m_app.set_devices(m_devices);
  if (!bad_devices.empty()) {
    show_bad_devices_if_exists(bad_devices);
    for (size_type i = 0; i < bad_devices.size(); i++) {
      devices_type::iterator it = m_devices.find(bad_devices[i]);
      IRS_LIB_ASSERT(it != m_devices.end());
      it->second.enabled = false;
      const int row = FindRowDevice(it->first);
      IRS_LIB_ASSERT(row >= 0);
      DevicesCXGrid->ActiveView->DataController->Values[row]
        [EnabledColumn->Index] = Variant(false);
    }
  }
}

void TMainForm::create_devices_dir() {
  String dir = GetCurrentDir() + irst("\\") +
    irs::str_conv<String>(m_devices_config_dir);
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
  String dir = GetCurrentDir() + irst("\\") +
    irs::str_conv<String>(m_devices_config_dir);

  String filter = dir + String(irst("\\*")) + irst(".") +
    irs::str_conv<String>(m_device_config_file_ext);
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

void TMainForm::load_grid_options()
{
  TcxGridStorageOptions options;
  options = (TcxGridStorageOptions() << gsoUseFilter << gsoUseSummary);
  bool children_creating = true;
  bool children_deleting = false;
  DevicesCXGrid->ActiveView->RestoreFromIniFile(
    irs::str_conv<String>(m_grid_options_file_name),
    children_creating, children_deleting, options);
}

void TMainForm::save_grid_options()
{
  TcxGridStorageOptions AOptions;
  bool recreate = false;
  AOptions = (TcxGridStorageOptions() << gsoUseFilter << gsoUseSummary);
  DevicesCXGrid->ActiveView->StoreToIniFile(
    irs::str_conv<String>(m_grid_options_file_name),
    recreate, AOptions);
}

void TMainForm::add_device(const String& a_file_name) {
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
    DevicesCXGrid->ActiveView->DataController->Values[row][TypeColumn->Index] =
      Variant(irs::str_conv<String>(m_assembly_type_default));
  }
}

void TMainForm::show_bad_devices_if_exists(
  const std::vector<string_type>& a_bad_devices) {
  if (!a_bad_devices.empty()) {
    string_type msg = irst("Следующие устройства включить не удалось: ");
    for (size_type i = 0; i < a_bad_devices.size(); i++) {
      if (i > 0) {
        msg += irst(", ");
      }
      msg += irst("\"") + a_bad_devices[i] + irst("\"");
    }
    msg += irst(".");
    Application->MessageBox(msg.c_str(), irst("Ошибка"), MB_OK + MB_ICONERROR);
  }
}

// ---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
  m_chart_position = m_app.chart()->position();
  m_ini_file.save();
  save_grid_options();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::TickTimerTimer(TObject *Sender)
{
  try {
    if (!tstlan4::tick_lock()->check()) {
      m_app.tick();
      if (m_update_status_timer.check()) {
        update_device_status_color();
      }
      /*devices_type::iterator it = m_devices.begin();
      int device_index = 0;
      while (it != m_devices.end()) {
        const error_string_list_type error_list =
          m_app.get_last_error_string_list(it->first);
        it->second.
        ++it;
      } */
    }
    if (m_update_options_timer.check()) {
      update_options();
    }
  }
  catch(Exception & exception) {
    TickTimer->Enabled = false;
    tstlan4::tick_lock()->enable();
    Application->ShowException(&exception);
    tstlan4::tick_lock()->disable();
    Close();
  } catch(...) {
    try {
      throw Exception("");
    }
    catch(Exception & exception) {
      TickTimer->Enabled = false;
      tstlan4::tick_lock()->enable();
      Application->ShowException(&exception);
      tstlan4::tick_lock()->disable();
      Close();
    }
  }
}

void TMainForm::update_device_status_color()
{
  DevicesCXGrid->ActiveView->BeginUpdate();

  for (int i = 0; i < DevicesCXGrid->ActiveView->DataController->RecordCount;
    i++) {
    const bool enabled = DevicesCXGrid->ActiveView->DataController->Values
        [i][EnabledColumn->Index];
    TColor color = clWhite;
    if (enabled) {
      const String file_full_name_bstr =
        DevicesCXGrid->ActiveView->DataController->Values[i]
        [FileNameColumn->Index];
      devices_type::iterator it = m_devices.find(irs::str_conv<string_type>
        (file_full_name_bstr));
      device_status_type status = m_app.get_status(it->first);

      switch (status) {
        case irs::mxdata_assembly_t::status_not_supported: {
          color = clSilver;
        } break;
        case irs::mxdata_assembly_t::status_connected: {
          color = clGreen;
        } break;
        case irs::mxdata_assembly_t::status_busy: {
          color = clYellow;
        } break;
        case irs::mxdata_assembly_t::status_error: {
          color = clRed;
        } break;
      }
    }
    DevicesCXGrid->ActiveView->DataController->Values[i]
      [StatusColumn->Index] = Variant(color);
  }

  DevicesCXGrid->ActiveView->EndUpdate();
}

void TMainForm::update_options()
{
  if (m_app.options()->get_param(irst("Отображать лог")) ==
      irst("true")) {
    LogMemo->Visible = true;
    irs::mlog().rdbuf(mp_memo_buf.get());
  } else {
    LogMemo->Visible = false;
    irs::mlog().rdbuf(NULL);
  }
}
// ---------------------------------------------------------------------------

struct less_nocase_t {
  bool operator()(const irs::string_t & a_left,
    const irs::string_t & a_right) const
  {
    irs::string_t left;
    irs::string_t right;
    transform(a_left.begin(), a_left.end(), back_inserter(left),
      toloweru<irs::char_t>);
    transform(a_right.begin(), a_right.end(), back_inserter(right),
      toloweru<irs::char_t>);
    return left < right;
  }
};

void TMainForm::enum_assembly_types() {
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
  return irs::str_conv<String>(make_file_full_name(irs::str_conv<string_type>
    (aUltraShortName)));
}

TMainForm::string_type TMainForm::make_file_full_name(
  const string_type& a_file_ultra_short_name)
{
  string_type dir = irs::str_conv<string_type>(GetCurrentDir()) + irst("\\")
    + m_devices_config_dir;
  return dir + irst("\\") + a_file_ultra_short_name + irst(".")
    + m_device_config_file_ext;
}

TPoint TMainForm::GetFocusedCellCoord()
{
  TcxCustomGridView* View = DevicesCXGrid->ActiveView;
  TcxCustomDataController* DataController = View->DataController;

  TcxCustomGridTableView * TableView = (TcxCustomGridTableView*)
    DevicesCXGrid->FocusedView;
  TcxCustomGridTableController * TableController = TableView->Controller;

  const int row = DataController->FocusedRecordIndex;
  const int col = TableController->FocusedItemIndex;
  TPoint point;
  point.x = col;
  point.y = row;
  return point;
}

int TMainForm::FindRowDevice(const string_type& a_device_full_name)
{
  for (int i = 0; i < DevicesCXGrid->ActiveView->DataController->RowCount;
    i++) {
    const String file_name_bstr =
      DevicesCXGrid->ActiveView->DataController->Values[i]
      [FileNameColumn->Index];
    if (irs::str_conv<string_type>(file_name_bstr) == a_device_full_name) {
      return i;
    }
  }
  return -1;
}
// ---------------------------------------------------------------------------

TMainForm::string_type TMainForm::generate_new_unique_name(
  const string_type& a_device_name)
{
  int i = 1;
  while (true) {
    const string_type new_full_file_name =
      make_file_full_name(a_device_name + irst("_") + irs::num_to_str(i));
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

void __fastcall TMainForm::ShowTstlanColumnPropertiesButtonClick
  (TObject *Sender, int AButtonIndex)
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
    String grid_conf_file_name = create_grid_configuration_file_full_name
        (file_name_bstr);
    String new_grid_conf_file_name = create_grid_configuration_file_full_name
        (irs::str_conv<String>(new_file_name));

    RenameFile(grid_conf_file_name, new_grid_conf_file_name);

    tstlan4::device_options_t device_options = it->second;
    m_devices.erase(it);
    m_devices.insert(make_pair(new_file_name, device_options));
    DevicesCXGrid->ActiveView->DataController->Values[row]
      [FileNameColumn->Index] = Variant
      (irs::str_conv<String>(new_file_name));
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
  String grid_configuration_file_name = create_grid_configuration_file_full_name
      (file_full_name_bstr);
  DeleteFile(grid_configuration_file_name);
}

String TMainForm::create_grid_configuration_file_full_name
  (const String& a_device_file_full_name)
{
  String grid_options_file_ext = irs::str_conv<String>(
    irs::tstlan::get_grid_options_file_ext());
  String grid_configuration_file_name = ExtractFileDir(
    a_device_file_full_name) + irst("\\") + irs::extract_file_ultra_short_name(
    a_device_file_full_name) + irst(".") + grid_options_file_ext;
  return grid_configuration_file_name;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::CopyDeviceActionExecute(TObject *Sender)
{
  TPoint point = GetFocusedCellCoord();
  const String file_name_bstr =
    DevicesCXGrid->ActiveView->DataController->Values[point.y]
    [FileNameColumn->Index];

  const String device_name_bstr = ExtractFileUltraShortName(
    irs::str_conv<String>(file_name_bstr));
  const String new_file_name_bstr = irs::str_conv<String>(
    generate_new_unique_name(irs::str_conv<string_type>(device_name_bstr)));
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
  const string_type file_full_name = generate_new_unique_name(
    irst("новое_устройство"));
  add_device(irs::str_conv<String>(file_full_name));
  m_app.set_devices(m_devices);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ImportActionExecute(TObject *Sender)
{
  if (ImportOpenDialog->Execute()) {
    const string_type destination = string_type(irst(".\\")) +
      m_devices_config_dir + +irst(".") + m_device_config_file_ext;
    m_app.import(irs::str_conv<string_type>(ImportOpenDialog->FileName),
      destination);
  }
}
// ---------------------------------------------------------------------------

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
// ---------------------------------------------------------------------------

TMainForm::devices_type::iterator TMainForm::get_focused_device()
{
  TPoint point = GetFocusedCellCoord();
  const String file_full_name_bstr =
    DevicesCXGrid->ActiveView->DataController->Values[point.y]
    [FileNameColumn->Index];
  devices_type::iterator it = m_devices.find(irs::str_conv<string_type>
    (file_full_name_bstr));
  return it;
}

void __fastcall TMainForm::EnabledColumnPropertiesChange(TObject *Sender)
{
  DevicesCXGrid->ActiveView->DataController->PostEditingData();
  TPoint point = GetFocusedCellCoord();
  devices_type::iterator it = get_focused_device();
  IRS_LIB_ASSERT(it != m_devices.end());

  const bool enabled = DevicesCXGrid->ActiveView->DataController->Values
    [point.y][EnabledColumn->Index];
  it->second.enabled = enabled;
  const vector<string_type>bad_devices = m_app.set_devices(m_devices);
  if (!bad_devices.empty()) {
    show_bad_devices_if_exists(bad_devices);
    DevicesCXGrid->ActiveView->DataController->Values[point.y]
      [EnabledColumn->Index] = Variant(false);
    it->second.enabled = false;
  }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TypeColumnPropertiesChange(TObject *Sender)
{
  DevicesCXGrid->ActiveView->DataController->PostEditingData();
  TPoint point = GetFocusedCellCoord();
  devices_type::iterator it = get_focused_device();
  String type_bstr = DevicesCXGrid->ActiveView->DataController->Values[point.y]
    [TypeColumn->Index];
  it->second.type = irs::str_conv<string_type>(type_bstr);
  m_app.set_devices(m_devices);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ShowChartActionExecute(TObject *Sender)
{
  m_app.show_chart();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::OptionsActionExecute(TObject *Sender)
{
  m_app.show_modal_options();
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::LogColumnPropertiesButtonClick(TObject *Sender, int AButtonIndex)

{
  String name = FileNameColumn->EditValue;
  m_app.show_connection_log(irs::str_conv<string_type>(name));
}
//---------------------------------------------------------------------------



