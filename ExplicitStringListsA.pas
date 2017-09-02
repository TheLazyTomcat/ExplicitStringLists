unit ExplicitStringListsA;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes, AuxTypes, ExplicitStringListsBase;

{$DEFINE ESL_Declaration}

type
  TShortStringList = class(TExplicitStringList)
  {$DEFINE ESL_Short}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Short}
  end;

  TAnsiStringList = class(TExplicitStringList)
  {$DEFINE ESL_Ansi}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Ansi}
  end;

  TUTF8StringList = class(TExplicitStringList)
  {$DEFINE ESL_UTF8}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_UTF8}
  end;

{$UNDEF ESL_Declaration}

implementation

uses
{$IF not Defined(FPC) and (CompilerVersion >= 20)}
  (* Delphi2009+ *) Windows, AnsiStrings,
{$IFEND}
  SysUtils, StrRect;

{$DEFINE ESL_Implementation}

  {$DEFINE ESL_Short}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Short}

  {$DEFINE ESL_Ansi}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Ansi}

  {$DEFINE ESL_UTF8}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_UTF8}

{$UNDEF ESL_Implementation}

end.
