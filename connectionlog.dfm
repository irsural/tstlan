object ConnectionLogForm: TConnectionLogForm
  Left = 0
  Top = 0
  Caption = #1051#1086#1075' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103
  ClientHeight = 592
  ClientWidth = 940
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 300
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  DesignSize = (
    940
    592)
  PixelsPerInch = 96
  TextHeight = 13
  object ClearButton: TButton
    Left = 133
    Top = 8
    Width = 75
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 0
    OnClick = ClearButtonClick
  end
  object LogMemo: TMemo
    Left = 8
    Top = 39
    Width = 928
    Height = 515
    Anchors = [akLeft, akTop, akRight, akBottom]
    Constraints.MinHeight = 300
    Constraints.MinWidth = 300
    ScrollBars = ssVertical
    TabOrder = 1
    ExplicitWidth = 1007
    ExplicitHeight = 606
  end
  object CloseButton: TButton
    Left = 857
    Top = 563
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 2
    OnClick = CloseButtonClick
    ExplicitLeft = 936
    ExplicitTop = 654
  end
  object AutoUpdateCheckBox: TCheckBox
    Left = 8
    Top = 8
    Width = 119
    Height = 17
    Caption = #1040#1074#1090#1086#1086#1073#1085#1086#1074#1083#1077#1085#1080#1077
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
  object MainTimer: TTimer
    Interval = 1
    OnTimer = MainTimerTimer
    Left = 984
    Top = 8
  end
end
