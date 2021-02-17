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
  TESLStringType = ShortString;

  TESLPCharType = ^TESLCharType;

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
  StrRect, BinaryStreaming, MemoryBuffer;

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.

