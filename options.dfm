object OptionsForm: TOptionsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 491
  ClientWidth = 620
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object OptionsPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 620
    Height = 450
    ActivePage = GeneralSheet
    Align = alClient
    TabOrder = 0
    object GeneralSheet: TTabSheet
      Caption = #1054#1073#1097#1080#1077
      DesignSize = (
        612
        422)
      object GeneralOptionsButton: TButton
        Left = 16
        Top = 24
        Width = 582
        Height = 25
        ParentCustomHint = False
        Anchors = [akLeft, akTop, akRight]
        Caption = #1054#1073#1097#1080#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
        TabOrder = 0
        OnClick = GeneralOptionsButtonClick
      end
      object DeviceOptionsButton: TButton
        Left = 16
        Top = 64
        Width = 582
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072
        TabOrder = 1
        OnClick = DeviceOptionsButtonClick
      end
    end
    object DeviceListSheet: TTabSheet
      Caption = #1057#1087#1080#1089#1086#1082' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
      ImageIndex = 1
      DesignSize = (
        612
        422)
      object NameLabel: TLabel
        Left = 341
        Top = 21
        Width = 109
        Height = 13
        Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072
      end
      object DeviceListValueListEditor: TValueListEditor
        Left = 16
        Top = 56
        Width = 582
        Height = 350
        Anchors = [akLeft, akTop, akRight, akBottom]
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goColSizing, goRowMoving, goEditing, goAlwaysShowEditor, goThumbTracking]
        TabOrder = 4
        OnSelectCell = DeviceListValueListEditorSelectCell
        ColWidths = (
          288
          288)
      end
      object AddButton: TButton
        Left = 16
        Top = 16
        Width = 75
        Height = 25
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 0
        OnClick = AddButtonClick
      end
      object DeleteButton: TButton
        Left = 97
        Top = 16
        Width = 75
        Height = 25
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 1
        OnClick = DeleteButtonClick
      end
      object RenameButton: TButton
        Left = 178
        Top = 16
        Width = 95
        Height = 25
        Caption = #1055#1077#1088#1077#1080#1084#1077#1085#1086#1074#1072#1090#1100
        TabOrder = 2
        OnClick = RenameButtonClick
      end
      object NameEdit: TEdit
        Left = 456
        Top = 18
        Width = 142
        Height = 21
        Anchors = [akTop, akRight]
        TabOrder = 3
      end
    end
  end
  object ButtonPanel: TPanel
    Left = 0
    Top = 450
    Width = 620
    Height = 41
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      620
      41)
    object OkButton: TButton
      Left = 365
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
      Left = 527
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
      Left = 446
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
      TabOrder = 1
      OnClick = ApplyButtonClick
    end
  end
end
