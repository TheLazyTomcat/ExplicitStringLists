unit ExplicitStringLists_Default;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Default}

type
  TESLCharType   = Char;
  TESLStringType = String;

type
  TDefaultStringList = class;

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

type
  TESLClassType = TDefaultStringList;

implementation

uses
  SysUtils,
  StrRect;

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.


