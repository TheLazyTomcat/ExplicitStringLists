unit ExplicitStringLists_UTF8;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_UTF8}

type
  TESLCharType   = UTF8Char;
  TESLStringType = UTF8String;
  
type
  TUTF8StringList = class;  // forward declaration

  TESLClassType = TUTF8StringList;

  TESLUTF8SortCompareIndex  = Function(List: TUTF8StringList; Idx1,Idx2: Integer): Integer;
  TESLUTF8SortCompareString = Function(List: TUTF8StringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLUTF8SortCompareIndex;
  TESLSortCompareStringType = TESLUTF8SortCompareString;

  {$DEFINE ESL_ClassTypes}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassTypes}

  TUTF8StringList = class(TExplicitStringList)
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

