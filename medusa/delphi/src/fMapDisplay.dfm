object Form1: TForm1
  Left = 415
  Top = 268
  Width = 918
  Height = 682
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 8
    Top = 8
    Width = 445
    Height = 393
    HorzScrollBar.Increment = 39
    HorzScrollBar.Tracking = True
    VertScrollBar.Tracking = True
    TabOrder = 0
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 300
      Height = 200
      AutoSize = True
    end
    object Image2: TImage
      Left = 56
      Top = 32
      Width = 32
      Height = 32
      AutoSize = True
      Center = True
      Picture.Data = {
        07544269746D617076020000424D760200000000000076000000280000002000
        0000200000000100040000000000000200000000000000000000100000000000
        0000000000000000800000800000008080008000000080008000808000008080
        8000C0C0C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
        FF00FFFFFFFFFFF999999999FFFFFFFFFFFFFFFFFFFF9999999F99999999FFFF
        FFFFFFFFFFF99999FFFF9FFFF9999FFFFFFFFFFFF9999FFFFFFF9FFFFFF9999F
        FFFFFFFF9999FFFFFFFF9FFFFFFF9999FFFFFFFF99FFFFFFFFFF9FFFFFFFFF99
        FFFFFFF99FFFFFFFFFFF9FFFFFFFFFF99FFFFF999FFFFFFFFFFF9FFFFFFFFFF9
        99FFFF99FFFFFFFFFFFF9FFFFFFFFFFF99FFF99FFFFFFFFFFFFF9FFFFFFFFFFF
        F99FF99FFFFFFFFFFFFF9FFFFFFFFFFFF99F99FFFFFFFFFFFFFF9FFFFFFFFFFF
        FF9999FFFFFFFFFFFFFFFFFFFFFFFFFFFF9999FFFFFFFFFFFFFF9FFFFFFFFFFF
        FF9999FFFFFFFFFFFFFF9FFFFFFFFFFFFF999999999999999F99999F99999999
        999999FFFFFFFFFFFFFF9FFFFFFFFFFFFF9999FFFFFFFFFFFFFF9FFFFFFFFFFF
        FF9999FFFFFFFFFFFFFFFFFFFFFFFFFFFF9999FFFFFFFFFFFFFF9FFFFFFFFFFF
        FF9999FFFFFFFFFFFFFF9FFFFFFFFFFFFF99F99FFFFFFFFFFFFF9FFFFFFFFFFF
        F99FF99FFFFFFFFFFFFF9FFFFFFFFFFFF99FFF99FFFFFFFFFFFF9FFFFFFFFFFF
        99FFFF999FFFFFFFFFFF9FFFFFFFFFF999FFFFF99FFFFFFFFFFF9FFFFFFFFFF9
        9FFFFFFF99FFFFFFFFFF9FFFFFFFFF99FFFFFFFF9999FFFFFFFF9FFFFFFF9999
        FFFFFFFFF9999FFFFFFF9FFFFFF9999FFFFFFFFFFFF99999FFFF9FFFF9999FFF
        FFFFFFFFFFFF9999999999999999FFFFFFFFFFFFFFFFFFF999999999FFFFFFFF
        FFFF}
      Transparent = True
    end
  end
  object ScrollBar1: TScrollBar
    Left = 8
    Top = 404
    Width = 445
    Height = 17
    PageSize = 0
    TabOrder = 1
    OnChange = ScrollBar1Change
  end
  object ScrollBar2: TScrollBar
    Left = 456
    Top = 8
    Width = 17
    Height = 393
    Kind = sbVertical
    PageSize = 0
    TabOrder = 2
    OnChange = ScrollBar2Change
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 444
    Top = 328
  end
end
