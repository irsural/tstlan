object OptionsForm: TOptionsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 497
  ClientWidth = 623
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object OptionsPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 623
    Height = 456
    ActivePage = DeviceListSheet
    Align = alClient
    TabOrder = 0
    ExplicitLeft = 288
    ExplicitTop = 72
    ExplicitHeight = 241
    object GeneralSheet: TTabSheet
      Caption = #1054#1073#1097#1080#1077
      ExplicitWidth = 605
      ExplicitHeight = 459
    end
    object DeviceListSheet: TTabSheet
      Caption = #1057#1087#1080#1089#1086#1082' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
      ImageIndex = 1
      ExplicitWidth = 605
      ExplicitHeight = 459
      object ValueListEditor1: TValueListEditor
        Left = 16
        Top = 16
        Width = 585
        Height = 396
        TabOrder = 0
        ColWidths = (
          277
          302)
      end
    end
  end
  object ButtonPanel: TPanel
    Left = 0
    Top = 456
    Width = 623
    Height = 41
    Align = alBottom
    TabOrder = 1
    object OkButton: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
    end
    object CancelButton: TButton
      Left = 97
      Top = 8
      Width = 75
      Height = 25
      Cancel = True
      Caption = #1054#1090#1084#1077#1085#1072
      ModalResult = 2
      TabOrder = 1
    end
  end
end
