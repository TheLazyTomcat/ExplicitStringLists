unit ExplicitStringListsW;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes, AuxTypes, ExplicitStringListsBase;

{$DEFINE ESL_Declaration}

type

{$DEFINE ESL_Wide}
  {$I ESL_CompFuncType.inc} = Function(const Str1,Str2: {$I ESL_StringType.inc}): Integer;

  {$I ESL_ListType.inc} = class(TExplicitStringList)
    {$I ExplicitStringLists.inc}
  end;
{$UNDEF ESL_Wide}

{$DEFINE ESL_Unicode}
  {$I ESL_CompFuncType.inc} = Function(const Str1,Str2: {$I ESL_StringType.inc}): Integer;

  {$I ESL_ListType.inc} = class(TExplicitStringList)
    {$I ExplicitStringLists.inc}
  end;
{$UNDEF ESL_Unicode}

{$DEFINE ESL_Default}
  {$I ESL_CompFuncType.inc} = Function(const Str1,Str2: {$I ESL_StringType.inc}): Integer;

  {$I ESL_ListType.inc} = class(TExplicitStringList)
    {$I ExplicitStringLists.inc}
  end;
{$UNDEF ESL_Default}

{$UNDEF ESL_Declaration}

implementation

uses
{$IF not Defined(FPC) and (CompilerVersion >= 20)}
  (* Delphi2009+ *) Windows, AnsiStrings,
{$IFEND}
  SysUtils, StrRect, BinaryStreaming, ExplicitStringListsParser;

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
