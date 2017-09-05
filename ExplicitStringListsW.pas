unit ExplicitStringListsW;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes, AuxTypes, ExplicitStringListsBase;

{$DEFINE ESL_Declaration}

type
  TWideStringList = class(TExplicitStringList)
  {$DEFINE ESL_Wide}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Wide}
  end;

  TUnicodeStringList = class(TExplicitStringList)
  {$DEFINE ESL_Unicode}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Unicode}
  end;

  TDefaultStringList = class(TExplicitStringList)
  {$DEFINE ESL_Default}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Default}
  end;

{$UNDEF ESL_Declaration}

implementation

uses
{$IF not Defined(FPC) and (CompilerVersion >= 20)}
  (* Delphi2009+ *) Windows, AnsiStrings,
{$IFEND}
  SysUtils, StrRect, BinaryStreaming;

{$DEFINE ESL_Implementation}

  {$DEFINE ESL_Wide}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Wide}

  {$DEFINE ESL_Unicode}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Unicode}

  {$DEFINE ESL_Default}
    {$I ExplicitStringLists.inc}
  {$UNDEF ESL_Default}

{$UNDEF ESL_Implementation}

end.
