unit ExplicitStringLists;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}   

interface

uses
  ExplicitStringLists_Base,
  ExplicitStringLists_Short,
  ExplicitStringLists_Ansi,
  ExplicitStringLists_UTF8,
  ExplicitStringLists_Wide,
  ExplicitStringLists_Unicode,
  ExplicitStringLists_Default;

type
  TExplicitStringList = ExplicitStringLists_Base.TExplicitStringList;

  TShortStringList = ExplicitStringLists_Short.TShortStringList;

  TAnsiStringList = ExplicitStringLists_Ansi.TAnsiStringList;

  TUTF8StringList = ExplicitStringLists_UTF8.TUTF8StringList;

  TWideStringList = ExplicitStringLists_Wide.TWideStringList;

  TUnicodeStringList = ExplicitStringLists_Unicode.TUnicodeStringList;

  TDefaultStringList = ExplicitStringLists_Default.TDefaultStringList;

implementation

end.
