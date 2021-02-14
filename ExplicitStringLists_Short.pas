unit ExplicitStringLists_Short;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Short}

type
  TESLCharType   = AnsiChar;
  TESLStringType = ShortString;

type
  TShortStringList = class;

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

type
  TESLClassType = TShortStringList;

implementation

uses
  SysUtils,
  StrRect;

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.

