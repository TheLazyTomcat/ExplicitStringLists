{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Explicit string lists - UCS4

    Implementation of list of UCS4 strings.

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
unit ExplicitStringLists_UCS4;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  Classes,
  AuxTypes,
  ExplicitStringLists_Base;

{$DEFINE ESL_UCS4}

{$IF not Declared(PUCS4String)}
type
  PUCS4String = ^UCS4String;
{$IFEND}

type
  TESLCharType  = UCS4Char;
  TESLPCharType = PUCS4Char;

  TESLStringType  = UCS4String;
  TESLPStringType = PUCS4String;

  TESLLongStringType = UCS4String;

type
  TUCS4StringList = class; // forward declaration

  TESLClassType = TUCS4StringList;

  TESLUCS4SortCompareIndex  = Function(List: TUCS4StringList; Idx1,Idx2: Integer): Integer;
  TESLUCS4SortCompareString = Function(List: TUCS4StringList; const Str1,Str2: TESLStringType): Integer;

  TESLSortCompareIndexType  = TESLUCS4SortCompareIndex;
  TESLSortCompareStringType = TESLUCS4SortCompareString;

{$DEFINE ESL_ClassTypes}
  {$INCLUDE './ExplicitStringLists.inc'}
{$UNDEF ESL_ClassTypes}

  TESLUCS4ItemBinaryIOEvent    = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem) of Object;
  TESLUCS4ItemBinaryIOCallback = procedure(Sender: TObject; Stream: TStream; var Item: TESLListItem);

  TESLItemBinaryIOEventType    = TESLUCS4ItemBinaryIOEvent;
  TESLItemBinaryIOCallbackType = TESLUCS4ItemBinaryIOCallback;

  TUCS4StringList = class(TExplicitStringList)
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

