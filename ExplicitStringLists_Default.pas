unit ExplicitStringLists_Default;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes,
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Default}

type
  TESLCharType   = Char;
  TESLPCharType  = PChar;

  TESLStringType     = String;
  TESLPStringType    = PString;
  TESLLongStringType = String;

type
  TDefaultStringList = class;  // forward declaration

  TESLClassType = TDefaultStringList;

  TESLDefaultSortCompareIndex  = Function(List: TDefaultStringList; Idx1,Idx2: Integer): Integer;
  TESLDefaultSortCompareString = Function(List: TDefaultStringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLDefaultSortCompareIndex;
  TESLSortCompareStringType = TESLDefaultSortCompareString;

{$DEFINE ESL_ClassTypes}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassTypes}

  TDefaultStringList = class(TExplicitStringList)
  {$DEFINE ESL_ClassDeclaration}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassDeclaration}
  end;

implementation

uses
  SysUtils,
{$IFDEF ESL_DEFAULT_Unicode}
  BinaryStreaming,
{$ENDIF}
  StrRect, MemoryBuffer, StaticMemoryStream;

{$IFDEF FPC_DisableWarns}
  {$DEFINE FPCDWM}
  {$DEFINE W5024:={$WARN 5024 OFF}} // Parameter "$1" not used
{$ENDIF}

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.
