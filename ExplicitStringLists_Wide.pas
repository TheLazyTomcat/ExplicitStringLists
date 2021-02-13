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

{$DEFINE ESL_ClassAuxiliary}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassAuxiliary}

type
  TWideStringList = class(TExplicitStringList)
  {$DEFINE ESL_ClassDeclaration}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassDeclaration}
  end;

type
  TESLClassType = TWideStringList;

implementation

uses
  StrRect;

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.
