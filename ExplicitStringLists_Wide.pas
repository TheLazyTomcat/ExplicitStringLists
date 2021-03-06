{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Explicit string lists - Wide

    Implementation of list of wide strings.

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
unit ExplicitStringLists_Wide;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes,
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_Wide}

type
  TESLCharType   = WideChar;
  TESLPCharType  = PWideChar;

  TESLStringType  = WideString;
  TESLPStringType = PWideString;

  TESLLongStringType = WideString;

type
  TWideStringList = class;  // forward declaration

  TESLClassType = TWideStringList;

  TESLWideSortCompareIndex  = Function(List: TWideStringList; Idx1,Idx2: Integer): Integer;
  TESLWideSortCompareString = Function(List: TWideStringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLWideSortCompareIndex;
  TESLSortCompareStringType = TESLWideSortCompareString;

{$DEFINE ESL_ClassTypes}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassTypes}

  TESLWideItemBinaryIOEvent    = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem) of Object;
  TESLWideItemBinaryIOCallback = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem);

  TESLItemBinaryIOEventType    = TESLWideItemBinaryIOEvent;
  TESLItemBinaryIOCallbackType = TESLWideItemBinaryIOCallback;

  TWideStringList = class(TExplicitStringList)
  {$DEFINE ESL_ClassDeclaration}
    {$INCLUDE './ExplicitStringLists.inc'}
  {$UNDEF ESL_ClassDeclaration}
  end; 

implementation

uses
  SysUtils,
  StrRect, BinaryStreaming, MemoryBuffer, StaticMemoryStream;

{$IFDEF FPC_DisableWarns}
  {$DEFINE FPCDWM}
  {$DEFINE W5024:={$WARN 5024 OFF}} // Parameter "$1" not used
{$ENDIF}

{===============================================================================
    Main implementation
===============================================================================}

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
