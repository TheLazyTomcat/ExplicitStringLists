unit ExplicitStringListsO;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes, AuxTypes, ExplicitStringListsBase;

{===============================================================================
--------------------------------------------------------------------------------
                                  T*StringList
--------------------------------------------------------------------------------
===============================================================================}

{===============================================================================
    T*StringList - declaration
===============================================================================}

{$DEFINE ESL_Declaration}

type
{$DEFINE ESL_UTF8}
  {$I 'ESL_inc\ESL_CompFuncType.inc'} = Function(const Str1,Str2: {$I 'ESL_inc\ESL_StringType.inc'}): Integer;

  {$I 'ESL_inc\ESL_ListType.inc'} = class(TExplicitStringList)
    {$I ExplicitStringLists.inc}
  end;
{$UNDEF ESL_UTF8}

{$DEFINE ESL_Default}
  {$I 'ESL_inc\ESL_CompFuncType.inc'} = Function(const Str1,Str2: {$I 'ESL_inc\ESL_StringType.inc'}): Integer;

  {$I 'ESL_inc\ESL_ListType.inc'} = class(TExplicitStringList)
    {$I ExplicitStringLists.inc}
  end;
{$UNDEF ESL_Default}

{$UNDEF ESL_Declaration}

implementation

uses
  SysUtils, StrRect, BinaryStreaming, ExplicitStringListsParser;

{===============================================================================
--------------------------------------------------------------------------------
                                  T*StringList
--------------------------------------------------------------------------------
===============================================================================}

{===============================================================================
    T*StringList - declaration
===============================================================================}

{$DEFINE ESL_Implementation}

{$DEFINE ESL_UTF8}
  {$I ExplicitStringLists.inc}
{$UNDEF ESL_UTF8}

{$DEFINE ESL_Default}
  {$I ExplicitStringLists.inc}
{$UNDEF ESL_Default}

{$UNDEF ESL_Implementation}

end.
