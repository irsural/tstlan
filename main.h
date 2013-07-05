//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <irsdefs.h>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <mxini.h>

#include "tstlan4app.h"

#include <irsfinal.h>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include "cxClasses.hpp"
#include "cxControls.hpp"
#include "cxCustomData.hpp"
#include "cxData.hpp"
#include "cxDataStorage.hpp"
#include "cxDBData.hpp"
#include "cxEdit.hpp"
#include "cxFilter.hpp"
#include "cxGraphics.hpp"
#include "cxGrid.hpp"
#include "cxGridCustomTableView.hpp"
#include "cxGridCustomView.hpp"
#include "cxGridDBTableView.hpp"
#include "cxGridLevel.hpp"
#include "cxGridTableView.hpp"
#include "cxLookAndFeelPainters.hpp"
#include "cxLookAndFeels.hpp"
#include "cxStyles.hpp"
#include "dxSkinBlack.hpp"
#include "dxSkinBlue.hpp"
#include "dxSkinBlueprint.hpp"
#include "dxSkinCaramel.hpp"
#include "dxSkinCoffee.hpp"
#include "dxSkinDarkRoom.hpp"
#include "dxSkinDarkSide.hpp"
#include "dxSkinDevExpressDarkStyle.hpp"
#include "dxSkinDevExpressStyle.hpp"
#include "dxSkinFoggy.hpp"
#include "dxSkinGlassOceans.hpp"
#include "dxSkinHighContrast.hpp"
#include "dxSkiniMaginary.hpp"
#include "dxSkinLilian.hpp"
#include "dxSkinLiquidSky.hpp"
#include "dxSkinLondonLiquidSky.hpp"
#include "dxSkinMcSkin.hpp"
#include "dxSkinMoneyTwins.hpp"
#include "dxSkinOffice2007Black.hpp"
#include "dxSkinOffice2007Blue.hpp"
#include "dxSkinOffice2007Green.hpp"
#include "dxSkinOffice2007Pink.hpp"
#include "dxSkinOffice2007Silver.hpp"
#include "dxSkinOffice2010Black.hpp"
#include "dxSkinOffice2010Blue.hpp"
#include "dxSkinOffice2010Silver.hpp"
#include "dxSkinPumpkin.hpp"
#include "dxSkinsCore.hpp"
#include "dxSkinscxPCPainter.hpp"
#include "dxSkinsDefaultPainters.hpp"
#include "dxSkinSeven.hpp"
#include "dxSkinSevenClassic.hpp"
#include "dxSkinSharp.hpp"
#include "dxSkinSharpPlus.hpp"
#include "dxSkinSilver.hpp"
#include "dxSkinSpringTime.hpp"
#include "dxSkinStardust.hpp"
#include "dxSkinSummer2008.hpp"
#include "dxSkinTheAsphaltWorld.hpp"
#include "dxSkinValentine.hpp"
#include "dxSkinVS2010.hpp"
#include "dxSkinWhiteprint.hpp"
#include "dxSkinXmas2008Blue.hpp"
#include <DB.hpp>
#include "cxCheckBox.hpp"
#include "cxDropDownEdit.hpp"
#include "cxCheckGroup.hpp"
#include "cxTextEdit.hpp"
#include "cxInplaceContainer.hpp"
#include "cxTL.hpp"
#include "cxTLdxBarBuiltInMenu.hpp"
#include <CheckLst.hpp>
#include <Dialogs.hpp>
#include <IdGlobalProtocols.hpp>
#include "cxBlobEdit.hpp"
#include "cxButtonEdit.hpp"
#include "cxHyperLinkEdit.hpp"
#include "cxCalc.hpp"
#include "cxCurrencyEdit.hpp"
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
  TTimer *TickTimer;
  TcxGridLevel *DevicesCXGridLevel1;
  TcxGrid *DevicesCXGrid;
  TcxGridTableView *DevicesCXGridTableView1;
  TcxGridColumn *NameColumn;
  TcxGridColumn *EnabledColumn;
  TcxGridColumn *TypeColumn;
  TOpenDialog *ImportOpenDialog;
  TcxGridColumn *OptionsColumn;
  TcxGridColumn *FileNameColumn;
  TcxGridColumn *ShowTstlanColumn;
  TMemo *LogMemo;
  TActionManager *ActionManager;
  TAction *DeleteDeviceAction;
  TAction *CopyDeviceAction;
  TAction *AddDeviceAction;
  TToolBar *ToolBar1;
  TSpeedButton *SpeedButton1;
  TSpeedButton *SpeedButton2;
  TSpeedButton *SpeedButton3;
  TAction *ImportAction;
  TSpeedButton *SpeedButton4;
  TSpeedButton *SpeedButton5;
  TAction *ShowChartAction;
  TAction *OptionsAction;
  TSpeedButton *SpeedButton6;
  void __fastcall TickTimerTimer(TObject *Sender);
  void __fastcall DeviceListValueListEditorSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall OptionsColumnPropertiesButtonClick(TObject *Sender, int AButtonIndex);
  void __fastcall ShowTstlanColumnPropertiesButtonClick(TObject *Sender, int AButtonIndex);
  void __fastcall NameColumnPropertiesValidate(TObject *Sender, Variant &DisplayValue,
          TCaption &ErrorText, bool &Error);
  void __fastcall DeleteDeviceActionExecute(TObject *Sender);
  void __fastcall CopyDeviceActionExecute(TObject *Sender);
  void __fastcall AddDeviceActionExecute(TObject *Sender);
  void __fastcall ImportActionExecute(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall EnabledColumnPropertiesChange(TObject *Sender);
  void __fastcall TypeColumnPropertiesChange(TObject *Sender);
  void __fastcall ShowChartActionExecute(TObject *Sender);
  void __fastcall OptionsActionExecute(TObject *Sender);


private:	// User declarations
  typedef irs::string_t string_type;
  typedef std::map<string_type, tstlan4::device_options_t> devices_type;
  void __fastcall DevicesCXGridDataControllerBeforeDelete(
    TcxCustomDataController* ADataController, int ARecordIndex);
  void __fastcall DevicesCXGridDataControllerAfterDelete(
    TcxCustomDataController* ADataController);
  void enum_assembly_types();
  void load_devices_list();
  void add_device(const String& a_file_name);
  string_type generate_new_unique_name(const string_type& a_device_name);
  String ExtractFileUltraShortName(const String& Name);
  String MakeFileFullName(const String& aUltraShortName);
  string_type make_file_full_name(const string_type& a_file_ultra_short_name);
  TPoint GetFocusedCellCoord();
  devices_type::iterator get_focused_device();

  irs::handle_t<irs::memobuf> mp_memo_buf;
  tstlan4::cfg_t m_cfg;
  tstlan4::app_t m_app;
  irs::ini_file_t m_ini_file;
  const string_type m_devices_config_dir;
  const string_type m_device_config_file_ext;
  const String m_device_options_section;
  vector<string_type> m_assembly_type_list;
  string_type m_assembly_type_default;
  devices_type m_devices;
public:		// User declarations
  __fastcall TMainForm(TComponent* Owner);
  __fastcall ~TMainForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;

template <class char_type>
char_type toloweru(char_type a_char)
{
  return use_facet< ctype<char_type> >(locale()).tolower(a_char);
}
//---------------------------------------------------------------------------
#endif
