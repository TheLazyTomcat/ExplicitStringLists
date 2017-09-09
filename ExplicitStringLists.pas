unit ExplicitStringLists;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  ExplicitStringListsA, ExplicitStringListsW, ExplicitStringListsO;

{===============================================================================
    Forwarded classes
===============================================================================}
type
  TShortStringList = ExplicitStringListsA.TShortStringList;
  TAnsiStringList = ExplicitStringListsA.TAnsiStringList;

  TWideStringList = ExplicitStringListsW.TWideStringList;
  TUnicodeStringList = ExplicitStringListsW.TUnicodeStringList;

  TUTF8StringList = ExplicitStringListsO.TUTF8StringList;
  TDefaultStringList = ExplicitStringListsO.TDefaultStringList;

implementation

end.




