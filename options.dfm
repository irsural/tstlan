object OptionsForm: TOptionsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 524
  ClientWidth = 654
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object OptionsPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 654
    Height = 483
    ActivePage = DeviceListSheet
    Align = alClient
    TabOrder = 0
    object GeneralSheet: TTabSheet
      Caption = #1054#1073#1097#1080#1077
      DesignSize = (
        646
        455)
      object GeneralOptionsButton: TButton
        Left = 16
        Top = 24
        Width = 616
        Height = 25
        ParentCustomHint = False
        Anchors = [akLeft, akTop, akRight]
        Caption = #1054#1073#1097#1080#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
        TabOrder = 0
        OnClick = GeneralOptionsButtonClick
      end
      object InnerButton: TButton
        Left = 16
        Top = 65
        Width = 616
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        Caption = #1042#1085#1091#1090#1088#1077#1085#1085#1080#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
        TabOrder = 1
      end
    end
    object DeviceListSheet: TTabSheet
      Caption = #1057#1087#1080#1089#1086#1082' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
      ImageIndex = 1
    end
  end
  object ButtonPanel: TPanel
    Left = 0
    Top = 483
    Width = 654
    Height = 41
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      654
      41)
    object OkButton: TButton
      Left = 399
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
      OnClick = OkButtonClick
    end
    object CancelButton: TButton
      Left = 561
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = #1054#1090#1084#1077#1085#1072
      ModalResult = 2
      TabOrder = 2
      OnClick = CancelButtonClick
    end
    object ApplyButton: TButton
      Left = 480
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
      TabOrder = 1
      OnClick = OkButtonClick
    end
  end
end
