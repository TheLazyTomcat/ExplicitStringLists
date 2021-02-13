unit ExplicitStringLists_Ansi;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Ansi}

type
  TESLCharType   = AnsiChar;
  TESLStringType = AnsiString;

{$DEFINE ESL_ClassAuxiliary}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassAuxiliary}

type
  TAnsiStringList = class(TExplicitStringList)
  {$DEFINE ESL_ClassDeclaration}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassDeclaration}
  end;

type
  TESLClassType = TAnsiStringList;

implementation

uses
  StrRect;

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.
