unit ExplicitStringLists_Short;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes,
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Short}

type
  TESLCharType   = AnsiChar;
  TESLPCharType  = PAnsiChar;

  TESLStringType     = ShortString;
  TESLPStringType    = PShortString;
{
  TESLLongStringType is used where limited length of short strings would pose
  a problem.
}
  TESLLongStringType = AnsiString;

type
  TShortStringList = class; // forward declaration

  TESLClassType = TShortStringList;

  TESLShortSortCompareIndex  = Function(List: TShortStringList; Idx1,Idx2: Integer): Integer;
  TESLShortSortCompareString = Function(List: TShortStringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLShortSortCompareIndex;
  TESLSortCompareStringType = TESLShortSortCompareString;

{$DEFINE ESL_ClassTypes}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassTypes}

  TShortStringList = class(TExplicitStringList)
  {$DEFINE ESL_ClassDeclaration}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassDeclaration}
  end;

implementation

uses
  SysUtils,  
  StrRect, MemoryBuffer, StaticMemoryStream;

{$IFDEF FPC_DisableWarns}
  {$DEFINE FPCDWM}
  {$DEFINE W5024:={$WARN 5024 OFF}} // Parameter "$1" not used
{$ENDIF}

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.
