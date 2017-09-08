{
  todo:

  * - add custom sort capability
  * - implement delimited text property
    - some methods can be class methods
    - re-arrange some methods
  * - for short, allow ansistring as large in/out
  * - revisit implementation of Get/SetText for short strings
  * - add property LineBreakStype (write only, duh!)
  * - check implementation when default string is shortstring
}
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




