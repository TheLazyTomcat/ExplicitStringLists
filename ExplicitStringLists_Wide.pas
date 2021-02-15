unit ExplicitStringLists_Wide;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Wide}

type
  TESLCharType   = WideChar;
  TESLStringType = WideString;

type
  TWideStringList = class;  // forward declaration

  TESLClassType = TWideStringList;

  TESLWideSortCompareIndex  = Function(List: TWideStringList; Idx1,Idx2: Integer): Integer;
  TESLWideSortCompareString = Function(List: TWideStringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLWideSortCompareIndex;
  TESLSortCompareStringType = TESLWideSortCompareString;

  {$DEFINE ESL_ClassTypes}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassTypes}

  TWideStringList = class(TExplicitStringList)
  {$DEFINE ESL_ClassDeclaration}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassDeclaration}
  end; 

implementation

uses
  SysUtils, Classes,
  StrRect;

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.