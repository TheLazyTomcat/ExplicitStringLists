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
  TESLCharType   = UCS4Char;
  TESLPCharType  = PUCS4Char;

  TESLStringType     = UCS4String;
  TESLPStringType    = PUCS4String;

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

  TUCS4StringList = class(TExplicitStringList)
//  {$DEFINE ESL_ClassDeclaration}
//    {$INCLUDE './ExplicitStringLists.inc'}
//  {$UNDEF ESL_ClassDeclaration}
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
    Auxiliary functions
===============================================================================}

Function StrLow: TStrSize;
begin
Result := 0;
end;

//------------------------------------------------------------------------------

Function StrHigh(const Str: TESLStringType): TStrSize;
begin
Result := Pred(Length(Str));
end;

//------------------------------------------------------------------------------

Function StrAddr(const Str: TESLStringType; Offset: TStrSize = 0): Pointer;
begin
If Length(Str) > 0 then
  begin
    If Offset < Length(Str) then
      Result := Addr(Str[StrLow + Offset])
    else
      raise EESLInvalidValue.CreateFmt('StrAddr: Offset (%d) out of bounds.',[Offset]);
  end
else raise EESLInvalidValue.Create('StrAddr: Empty string.');
end;

{===============================================================================
    Main implementation
===============================================================================}

//{$DEFINE ESL_ClassImplementation}
//  {$INCLUDE './ExplicitStringLists.inc'}
//{$UNDEF ESL_ClassImplementation}

end.
