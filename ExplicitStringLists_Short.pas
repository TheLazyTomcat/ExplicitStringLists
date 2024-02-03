{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Explicit string lists - Short

    Implementation of list of short strings.

  Version 1.1.2 (2021-11-22)

  Last change 2024-02-03

  ©2017-2024 František Milt

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
    AuxTypes            - github.com/TheLazyTomcat/Lib.AuxTypes
    AuxClasses          - github.com/TheLazyTomcat/Lib.AuxClasses
    StrRect             - github.com/TheLazyTomcat/Lib.StrRect
    ListSorters         - github.com/TheLazyTomcat/Lib.ListSorters
    StaticMemoryStream  - github.com/TheLazyTomcat/Lib.StaticMemoryStream
  * BinaryStreamingLite - github.com/TheLazyTomcat/Lib.BinaryStreamingLite
    MemoryBuffer        - github.com/TheLazyTomcat/Lib.MemoryBuffer

  BinaryStreamingLite can be replaced by full BinaryStreaming.

===============================================================================}
unit ExplicitStringLists_Short;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes,
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Short}

type
  TESLCharType  = AnsiChar;
  TESLPCharType = PAnsiChar;

  TESLStringType  = ShortString;
  TESLPStringType = PShortString;
{
  TESLLongStringType is used where limited length of short strings would pose
  a problem.
}
  TESLLongStringType = AnsiString;

type
  TShortStringList = class; // forward declaration

  TESLClassType = TShortStringList;

  TESLShortSortCompareIndex  = Function(List: TShortStringList; Idx1,Idx2: Integer): Integer;
  TESLShortSortCompareString = Function(List: TShortStringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLShortSortCompareIndex;
  TESLSortCompareStringType = TESLShortSortCompareString;

{$DEFINE ESL_ClassTypes}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassTypes}

  TESLShortItemBinaryIOEvent    = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem) of Object;
  TESLShortItemBinaryIOCallback = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem);

  TESLItemBinaryIOEventType    = TESLShortItemBinaryIOEvent;
  TESLItemBinaryIOCallbackType = TESLShortItemBinaryIOCallback;

  TShortStringList = class(TExplicitStringList)
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
  ESL_IMPLSTR_NAME = 'short';

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

