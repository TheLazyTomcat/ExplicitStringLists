unit ExplicitStringLists_Unicode;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes,
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Unicode}

type
  TESLCharType   = UnicodeChar;
  TESLPCharType  = PUnicodeChar;

  TESLStringType     = UnicodeString;
  TESLPStringType    = PUnicodeString;
  TESLLongStringType = UnicodeString;

type
  TUnicodeStringList = class; // forward declaration

  TESLClassType = TUnicodeStringList;

  TESLUnicodeSortCompareIndex  = Function(List: TUnicodeStringList; Idx1,Idx2: Integer): Integer;
  TESLUnicodeSortCompareString = Function(List: TUnicodeStringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLUnicodeSortCompareIndex;
  TESLSortCompareStringType = TESLUnicodeSortCompareString;

{$DEFINE ESL_ClassTypes}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassTypes}

  TUnicodeStringList = class(TExplicitStringList)
  {$DEFINE ESL_ClassDeclaration}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassDeclaration}
  end;

implementation

uses
  SysUtils, 
  StrRect, BinaryStreaming, MemoryBuffer, StaticMemoryStream;

{$IFDEF FPC_DisableWarns}
  {$DEFINE FPCDWM}
  {$DEFINE W5024:={$WARN 5024 OFF}} // Parameter "$1" not used
{$ENDIF}

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.
