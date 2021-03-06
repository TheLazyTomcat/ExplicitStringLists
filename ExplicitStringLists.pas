{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Explicit string lists

    This library/framework implements and provides string list classes, where
    the individual items/strings have explicitly defined type - that is, they
    are NOT of default type String, which might be defined differently
    depending on compiler and its settings.
    The classes are created to be maximally similar in function and interface
    to a standard TStrings and TStringList classes, but are completely
    unrelated to them.
    They are meant for situation, where there is a need for storing strings of
    type that differs from default type String in a list, and any implicit or
    explicit conversion is undesirable or impossible.
    Individual classes are implemented on the same codebase using template and
    type aliases. It is not done using generics because of backward
    compatibility with compilers that do not support generics.

    At this moment, lists for the following string types are implemented:

      ShortString   - TShortStringList in ExplicitStringLists_Short.pas
      AnsiString    - TAnsiStringList in ExplicitStringLists_Ansi.pas
      UTF8String    - TUTF8StringList in ExplicitStringLists_UTF8.pas
      WideString    - TWideStringList in ExplicitStringLists_Wide.pas
      UnicodeString - TUnicodeStringList in ExplicitStringLists_Unicode.pas
      String        - TDefaultStringList in ExplicitStringLists_Default.pas
      UCS4String    - TUCS4StringList in ExplicitStringLists_UCS4.pas

    NOTE - TDefaultStringList is pretty much identical to standard TStringList,
           and can be, to some extent, used as its replacement.

    Note that this unit does not implement anything, it is only forwarding list
    classes that otherwise reside in their own separate units.
    Also, some other types that might be needed, eg. enumerated types or
    records, are declared in ExplicitStringLists_Base or in respective units
    for each class.

  Version 1.1.1 (2021-03-06)

  Last change 2021-03-06

  ©2017-2021 František Milt

  Contacts:
    František Milt: frantisek.milt@gmail.com

  Support:
    If you find this code useful, please consider supporting its author(s) by
    making a small donation using the following link(s):

      https://www.paypal.me/FMilt

  Changelog:
    For detailed changelog and history please refer to this git repository:

      github.com/TheLazyTomcat/ExplicitStringLists

  Dependencies:
    AuxTypes           - github.com/TheLazyTomcat/Lib.AuxTypes
    AuxClasses         - github.com/TheLazyTomcat/Lib.AuxClasses
    StrRect            - github.com/TheLazyTomcat/Lib.StrRect
    ListSorters        - github.com/TheLazyTomcat/Lib.ListSorters
    StaticMemoryStream - github.com/TheLazyTomcat/Lib.StaticMemoryStream
    BinaryStreaming    - github.com/TheLazyTomcat/Lib.BinaryStreaming
    MemoryBuffer       - github.com/TheLazyTomcat/Lib.MemoryBuffer

===============================================================================}
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
  ExplicitStringLists_Default,
  ExplicitStringLists_UCS4;

{===============================================================================
    Forwarded classes
===============================================================================}
type
  // common ancestor
  TExplicitStringList = ExplicitStringLists_Base.TExplicitStringList;

  // specialized classes...
  TShortStringList = ExplicitStringLists_Short.TShortStringList;

  TAnsiStringList = ExplicitStringLists_Ansi.TAnsiStringList;

  TUTF8StringList = ExplicitStringLists_UTF8.TUTF8StringList;

  TWideStringList = ExplicitStringLists_Wide.TWideStringList;

  TUnicodeStringList = ExplicitStringLists_Unicode.TUnicodeStringList;

  TDefaultStringList = ExplicitStringLists_Default.TDefaultStringList;

  TUCS4StringList = ExplicitStringLists_UCS4.TUCS4StringList;

implementation

end.
