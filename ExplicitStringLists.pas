unit ExplicitStringLists;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  ExplicitStringListsA, ExplicitStringListsW;

type
  TShortStringList = ExplicitStringListsA.TShortStringList;
  TAnsiStringList = ExplicitStringListsA.TAnsiStringList;
  TUTF8StringList = ExplicitStringListsA.TUTF8StringList;

  TWideStringList = ExplicitStringListsW.TWideStringList;
  TUnicodeStringList = ExplicitStringListsW.TUnicodeStringList;
  TDefaultStringList = ExplicitStringListsW.TDefaultStringList;

implementation

end.




