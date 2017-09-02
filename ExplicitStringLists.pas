// add custom sort capability
// implemt BOM
// add endiannes select
// implement delimited text
unit ExplicitStringLists;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  ExplicitStringListsBase, ExplicitStringListsA, ExplicitStringListsW;

type
  EExplicitStringListError = ExplicitStringListsBase.EExplicitStringListError;

  TExplicitStringList = ExplicitStringListsBase.TExplicitStringList;

  TShortStringList = ExplicitStringListsA.TShortStringList;
  TAnsiStringList = ExplicitStringListsA.TAnsiStringList;
  TUTF8StringList = ExplicitStringListsA.TUTF8StringList;

  TWideStringList = ExplicitStringListsW.TWideStringList;
  TUnicodeStringList = ExplicitStringListsW.TUnicodeStringList;
  TDefaultStringList = ExplicitStringListsW.TDefaultStringList;

implementation

end.




