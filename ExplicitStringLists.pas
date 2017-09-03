{
  todo:
  
    - add custom sort capability
    - implement delimited text property
    - more effective (and also working in case of ShortString) LoadFromStream (parse BOM)
    - some methods can be class methods
    - re-arrange some methods
}
unit ExplicitStringLists;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  ExplicitStringListsBase, ExplicitStringListsA, ExplicitStringListsW;

type
  TExplicitStringList = ExplicitStringListsBase.TExplicitStringList;

  TShortStringList = ExplicitStringListsA.TShortStringList;
  TAnsiStringList = ExplicitStringListsA.TAnsiStringList;
  TUTF8StringList = ExplicitStringListsA.TUTF8StringList;

  TWideStringList = ExplicitStringListsW.TWideStringList;
  TUnicodeStringList = ExplicitStringListsW.TUnicodeStringList;
  TDefaultStringList = ExplicitStringListsW.TDefaultStringList;

implementation

end.




