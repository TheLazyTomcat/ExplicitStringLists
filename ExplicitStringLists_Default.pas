{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Explicit string lists - Default

    Implementation of list of (default) strings.

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
unit ExplicitStringLists_Default;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes,
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Default}

type
  TESLCharType  = Char;
  TESLPCharType = PChar;

  TESLStringType  = String;
  TESLPStringType = PString;

  TESLLongStringType = String;

type
  TDefaultStringList = class;  // forward declaration

  TESLClassType = TDefaultStringList;

  TESLDefaultSortCompareIndex  = Function(List: TDefaultStringList; Idx1,Idx2: Integer): Integer;
  TESLDefaultSortCompareString = Function(List: TDefaultStringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLDefaultSortCompareIndex;
  TESLSortCompareStringType = TESLDefaultSortCompareString;

{$DEFINE ESL_ClassTypes}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassTypes}

  TESLDefaultItemBinaryIOEvent    = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem) of Object;
  TESLDefaultItemBinaryIOCallback = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem);

  TESLItemBinaryIOEventType    = TESLDefaultItemBinaryIOEvent;
  TESLItemBinaryIOCallbackType = TESLDefaultItemBinaryIOCallback;

  TDefaultStringList = class(TExplicitStringList)
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
  ESL_IMPLSTR_NAME = 'default';

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
