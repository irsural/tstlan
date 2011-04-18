object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #1058#1077#1089#1090' '#1089#1077#1090#1080' 4'
  ClientHeight = 529
  ClientWidth = 557
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object TickTimer: TTimer
    Interval = 10
    OnTimer = TickTimerTimer
    Left = 20
    Top = 25
  end
end
