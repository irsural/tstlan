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
    ExplicitWidth = 620
    ExplicitHeight = 450
    object GeneralSheet: TTabSheet
      Caption = #1054#1073#1097#1080#1077
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 612
      ExplicitHeight = 422
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
        ExplicitWidth = 582
      end
      object DeviceOptionsButton: TButton
        Left = 16
        Top = 104
        Width = 616
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072
        TabOrder = 1
        OnClick = DeviceOptionsButtonClick
        ExplicitWidth = 582
      end
      object InnerButton: TButton
        Left = 16
        Top = 65
        Width = 616
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        Caption = #1042#1085#1091#1090#1088#1077#1085#1085#1080#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
        TabOrder = 2
        OnClick = InnerButtonClick
        ExplicitWidth = 582
      end
      object ImportButton: TButton
        Left = 16
        Top = 144
        Width = 616
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        Caption = #1048#1084#1087#1086#1088#1090
        TabOrder = 3
        OnClick = ImportButtonClick
        ExplicitWidth = 582
      end
    end
    object DeviceListSheet: TTabSheet
      Caption = #1057#1087#1080#1089#1086#1082' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 612
      ExplicitHeight = 422
      DesignSize = (
        646
        455)
      object NameLabel: TLabel
        Left = 375
        Top = 21
        Width = 109
        Height = 13
        Anchors = [akTop, akRight]
        Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072
        ExplicitLeft = 442
      end
      object DeviceListValueListEditor: TValueListEditor
        Left = 16
        Top = 56
        Width = 616
        Height = 383
        Anchors = [akLeft, akTop, akRight, akBottom]
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goColSizing, goRowMoving, goEditing, goAlwaysShowEditor, goThumbTracking]
        TabOrder = 4
        OnSelectCell = DeviceListValueListEditorSelectCell
        ExplicitWidth = 618
        ColWidths = (
          288
          322)
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
        Left = 490
        Top = 18
        Width = 142
        Height = 21
        Anchors = [akTop, akRight]
        TabOrder = 3
        ExplicitLeft = 456
      end
      object CopyButton: TButton
        Left = 279
        Top = 16
        Width = 82
        Height = 25
        Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
        TabOrder = 5
        OnClick = CopyButtonClick
      end
    end
  end
  object ButtonPanel: TPanel
    Left = 0
    Top = 483
    Width = 654
    Height = 41
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 450
    ExplicitWidth = 620
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
      ExplicitLeft = 365
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
      ExplicitLeft = 527
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
      ExplicitLeft = 446
    end
  end
  object ImportOpenDialog: TOpenDialog
    Left = 40
    Top = 384
  end
end
