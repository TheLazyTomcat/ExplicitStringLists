unit ExplicitStringLists_Unicode;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Unicode}

type
  TESLCharType   = UnicodeChar;
  TESLStringType = UnicodeString;

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
  SysUtils, Classes,
  StrRect;

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.

