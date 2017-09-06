unit ExplicitStringListsA;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes, AuxTypes, ExplicitStringListsBase;

{$DEFINE ESL_Declaration}

type
  TShortStringList = class(TExplicitStringList)
  protected
    Function GetAnsiText: AnsiString;
    procedure SetAnsiText(Value: AnsiString);
    Function GetAnsiDelimitedText: AnsiString;
    procedure SetAnsiDelimitedText(Value: AnsiString);
    Function GetAnsiCommaText: AnsiString;
    procedure SetAnsiCommaText(Value: AnsiString);
  {$DEFINE ESL_Short}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Short}
  published
    property AnsiText: AnsiString read GetAnsiText write SetAnsiText;
    property AnsiDelimitedText: AnsiString read GetAnsiDelimitedText write SetAnsiDelimitedText;
    property AnsiCommaText: AnsiString read GetAnsiCommaText write SetAnsiCommaText;
  end;

  TAnsiStringList = class(TExplicitStringList)
  {$DEFINE ESL_Ansi}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Ansi}
  end;

  TUTF8StringList = class(TExplicitStringList)
  {$DEFINE ESL_UTF8}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_UTF8}
  end;

{$UNDEF ESL_Declaration}

implementation

uses
{$IF not Defined(FPC) and (CompilerVersion >= 20)}
  (* Delphi2009+ *) Windows, AnsiStrings,
{$IFEND}
  SysUtils, StrRect, BinaryStreaming;

{$DEFINE ESL_Implementation}

{$DEFINE ESL_Short}
  {$I ExplicitStringLists.inc}
{$UNDEF ESL_Short}

Function TShortStringList.GetAnsiText: AnsiString;
var
  i:    Integer;
  Len:  Integer;
begin
Len := 0;
// count size for preallocation
For i := LowIndex to HighIndex do
  Inc(Len,Length(fStrings[i]));
Inc(Len,fCount * Length(fLineBreak));
If not TrailingLineBreak then
  Dec(Len,Length(fLineBreak));
// preallocate
SetLength(Result,Len);
// store data
Len := 1;
For i := LowIndex to HighIndex do
  begin
    System.Move(fStrings[i][1],Addr(Result[Len])^,Length(fStrings[i]) * SizeOf(AnsiChar));
    Inc(Len,Length(fStrings[i]));
    If (i < HighIndex) or TrailingLineBreak and (Length(fLineBreak) > 0) then
      begin
        System.Move(fLineBreak[1],Addr(Result[Len])^,Length(fLineBreak) * SizeOf(AnsiChar));
        Inc(Len,Length(fLineBreak));
      end;
  end;
end;

//------------------------------------------------------------------------------

procedure TShortStringList.SetAnsiText(Value: AnsiString);
var
  C,S:  PAnsiChar;
  Buff: AnsiString;
begin
BeginUpdate;
try
  Clear;
  C := PAnsiChar(Value);
  If C <> nil then
    while Ord(C^) <> 0 do
      begin
        S := C;
        while not IsBreak(C^) do Inc(C);
        If ({%H-}PtrUInt(C) - {%H-}PtrUInt(S)) > 0 then
          begin
            SetLength(Buff,({%H-}PtrUInt(C) - {%H-}PtrUInt(S)) div SizeOf(AnsiChar));
            System.Move(S^,PAnsiChar(Buff)^,Length(Buff) * SizeOf(AnsiChar));        
            Add(ShortString(Buff));
          end
        else Add('');
        If Ord(C^) = 13 then Inc(C);
        If Ord(C^) = 10 then Inc(C);
      end;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

Function TShortStringList.GetAnsiDelimitedText: AnsiString;
begin
{$message 'implement'}
end;

//------------------------------------------------------------------------------

procedure TShortStringList.SetAnsiDelimitedText(Value: AnsiString);
begin
{$message 'implement'}
end;

//------------------------------------------------------------------------------

Function TShortStringList.GetAnsiCommaText: AnsiString;
var
  OldDelimiter: AnsiChar;
  OldQuoteChar: AnsiChar;
begin
OldDelimiter := fDelimiter;
OldQuoteChar := fQuoteChar;
try
  fDelimiter := def_Delimiter;
  fQuoteChar := def_QuoteChar;
  Result := GetAnsiDelimitedText;
finally
  fDelimiter := OldDelimiter;
  fQuoteChar := OldquoteChar;
end;
end;

//------------------------------------------------------------------------------

procedure TShortStringList.SetAnsiCommaText(Value: AnsiString);
var
  OldDelimiter: AnsiChar;
  OldQuoteChar: AnsiChar;
begin
OldDelimiter := fDelimiter;
OldQuoteChar := fQuoteChar;
try
  fDelimiter := def_Delimiter;
  fQuoteChar := def_QuoteChar;
  SetAnsiDelimitedText(Value);
finally
  fDelimiter := OldDelimiter;
  fQuoteChar := OldquoteChar;
end;
end;

{$DEFINE ESL_Ansi}
  {$I ExplicitStringLists.inc}
{$UNDEF ESL_Ansi}

{$DEFINE ESL_UTF8}
  {$I ExplicitStringLists.inc}
{$UNDEF ESL_UTF8}

{$UNDEF ESL_Implementation}

end.
