object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #1058#1077#1089#1090' '#1089#1077#1090#1080' 4'
  ClientHeight = 552
  ClientWidth = 800
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object DevicesCXGrid: TcxGrid
    Left = 0
    Top = 29
    Width = 800
    Height = 434
    Align = alClient
    TabOrder = 0
    ExplicitTop = 28
    object DevicesCXGridTableView1: TcxGridTableView
      Navigator.Buttons.CustomButtons = <>
      DataController.Filter.Options = [fcoCaseInsensitive]
      DataController.Summary.DefaultGroupSummaryItems = <>
      DataController.Summary.FooterSummaryItems = <>
      DataController.Summary.SummaryGroups = <>
      OptionsData.Deleting = False
      OptionsData.DeletingConfirmation = False
      OptionsView.ShowEditButtons = gsebAlways
      object NameColumn: TcxGridColumn
        Caption = #1059#1089#1090#1088#1086#1081#1089#1090#1074#1086
        PropertiesClassName = 'TcxTextEditProperties'
        Properties.OnValidate = NameColumnPropertiesValidate
        Width = 355
      end
      object FileNameColumn: TcxGridColumn
        Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072
        PropertiesClassName = 'TcxBlobEditProperties'
        Properties.BlobEditKind = bekMemo
        Properties.BlobPaintStyle = bpsText
        Properties.ReadOnly = True
        Width = 69
      end
      object EnabledColumn: TcxGridColumn
        Caption = #1042#1082#1083'./'#1042#1099#1082#1083'.'
        DataBinding.ValueType = 'Boolean'
        PropertiesClassName = 'TcxCheckBoxProperties'
        Properties.OnChange = EnabledColumnPropertiesChange
        Width = 61
      end
      object TypeColumn: TcxGridColumn
        Caption = #1058#1080#1087
        PropertiesClassName = 'TcxComboBoxProperties'
        Properties.DropDownListStyle = lsFixedList
        Properties.ReadOnly = False
        Properties.OnChange = TypeColumnPropertiesChange
        OnGetProperties = TypeColumnGetProperties
        Width = 149
      end
      object OptionsColumn: TcxGridColumn
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
        PropertiesClassName = 'TcxBlobEditProperties'
        Properties.BlobEditKind = bekBlob
        Properties.OnButtonClick = OptionsColumnPropertiesButtonClick
      end
      object ShowTstlanColumn: TcxGridColumn
        Caption = 'tstlan'
        PropertiesClassName = 'TcxBlobEditProperties'
        Properties.BlobEditKind = bekBlob
        Properties.OnButtonClick = ShowTstlanColumnPropertiesButtonClick
      end
    end
    object DevicesCXGridLevel1: TcxGridLevel
      GridView = DevicesCXGridTableView1
    end
  end
  object LogMemo: TMemo
    Left = 0
    Top = 463
    Width = 800
    Height = 89
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 800
    Height = 29
    ButtonWidth = 89
    Caption = 'ToolBar1'
    TabOrder = 2
    object SpeedButton1: TSpeedButton
      Left = 0
      Top = 0
      Width = 89
      Height = 22
      Action = AddDeviceAction
    end
    object SpeedButton2: TSpeedButton
      Left = 89
      Top = 0
      Width = 72
      Height = 22
      Action = CopyDeviceAction
    end
    object SpeedButton3: TSpeedButton
      Left = 161
      Top = 0
      Width = 64
      Height = 22
      Action = DeleteDeviceAction
    end
    object SpeedButton4: TSpeedButton
      Left = 225
      Top = 0
      Width = 64
      Height = 22
      Action = ImportAction
    end
  end
  object TickTimer: TTimer
    Interval = 10
    OnTimer = TickTimerTimer
    Left = 748
    Top = 1
  end
  object ImportOpenDialog: TOpenDialog
    Left = 680
  end
  object ActionManager: TActionManager
    Left = 712
    StyleName = 'Platform Default'
    object AddDeviceAction: TAction
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      OnExecute = AddDeviceActionExecute
    end
    object CopyDeviceAction: TAction
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      OnExecute = CopyDeviceActionExecute
    end
    object DeleteDeviceAction: TAction
      Caption = #1059#1076#1072#1083#1080#1090#1100
      ShortCut = 16430
      OnExecute = DeleteDeviceActionExecute
    end
    object ImportAction: TAction
      Caption = #1048#1084#1087#1086#1088#1090
      OnExecute = ImportActionExecute
    end
  end
end
