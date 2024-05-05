{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Explicit string lists - Unicode

    Implementation of list of unicode strings.

  Version 1.1.3 (2024-05-05)

  Last change 2024-05-05

  �2017-2024 Franti�ek Milt

  Contacts:
    Franti�ek Milt: frantisek.milt@gmail.com

  Support:
    If you find this code useful, please consider supporting its author(s) by
    making a small donation using the following link(s):

      https://www.paypal.me/FMilt

  Changelog:
    For detailed changelog and history please refer to this git repository:

      github.com/TheLazyTomcat/ExplicitStringLists

  Dependencies:
    AuxClasses          - github.com/TheLazyTomcat/Lib.AuxClasses
  * AuxExceptions       - github.com/TheLazyTomcat/Lib.AuxExceptions
    AuxTypes            - github.com/TheLazyTomcat/Lib.AuxTypes
  * BinaryStreamingLite - github.com/TheLazyTomcat/Lib.BinaryStreamingLite
    ListSorters         - github.com/TheLazyTomcat/Lib.ListSorters
    MemoryBuffer        - github.com/TheLazyTomcat/Lib.MemoryBuffer
    StaticMemoryStream  - github.com/TheLazyTomcat/Lib.StaticMemoryStream
    StrRect             - github.com/TheLazyTomcat/Lib.StrRect

  Library AuxExceptions is required only when rebasing local exception classes
  (see symbol ExplicitStringLists_UseAuxExceptions for details).

  BinaryStreamingLite can be replaced by full BinaryStreaming.

  Library AuxExceptions might also be required as an indirect dependency.

  Indirect dependencies:
    SimpleCPUID - github.com/TheLazyTomcat/Lib.SimpleCPUID
    UInt64Utils - github.com/TheLazyTomcat/Lib.UInt64Utils
    WinFileInfo - github.com/TheLazyTomcat/Lib.WinFileInfo

===============================================================================}
unit ExplicitStringLists_Unicode;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes,
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Unicode}

type
  TESLCharType  = UnicodeChar;
  TESLPCharType = PUnicodeChar;

  TESLStringType  = UnicodeString;
  TESLPStringType = PUnicodeString;

  TESLLongStringType = UnicodeString;

type
  TUnicodeStringList = class; // forward declaration

  TESLClassType = TUnicodeStringList;

  TESLUnicodeSortCompareIndex  = Function(List: TUnicodeStringList; Idx1,Idx2: Integer): Integer;
  TESLUnicodeSortCompareString = Function(List: TUnicodeStringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLUnicodeSortCompareIndex;
  TESLSortCompareStringType = TESLUnicodeSortCompareString;

{$DEFINE ESL_ClassTypes}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassTypes}

  TESLUnicodeItemBinaryIOEvent    = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem) of Object;
  TESLUnicodeItemBinaryIOCallback = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem);

  TESLItemBinaryIOEventType    = TESLUnicodeItemBinaryIOEvent;
  TESLItemBinaryIOCallbackType = TESLUnicodeItemBinaryIOCallback;

  TUnicodeStringList = class(TExplicitStringList)
  {$DEFINE ESL_ClassDeclaration}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassDeclaration}
  end;

implementation

uses
  SysUtils, 
  StrRect, BinaryStreamingLite, MemoryBuffer, StaticMemoryStream;

{$IFDEF FPC_DisableWarns}
  {$DEFINE FPCDWM}
  {$DEFINE W5024:={$WARN 5024 OFF}} // Parameter "$1" not used
{$ENDIF}

{===============================================================================
    Main implementation
===============================================================================}
const
  ESL_IMPLSTR_NAME = 'unicode';

//------------------------------------------------------------------------------

{$DEFINE ESL_ClassAuxiliary}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassAuxiliary}

//------------------------------------------------------------------------------

{$DEFINE ESL_ClassDelimitedTextParser}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassDelimitedTextParser}

//------------------------------------------------------------------------------

{$DEFINE ESL_ClassImplementation}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassImplementation}

end.
