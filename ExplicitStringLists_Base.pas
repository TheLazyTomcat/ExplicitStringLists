{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Explicit string lists - Base

    Base classes and types for all lists and utility classes (eg. delimited
    text parser).

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
unit ExplicitStringLists_Base;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  SysUtils, Classes,
  AuxTypes, AuxClasses;

{===============================================================================
    Framework-specific exceptions
===============================================================================}
type
  EESLException = class(Exception);

  EESLIndexOutOfBounds = class(EESLException);
  EESLUnknownValue     = class(EESLException);
  EESLInvalidValue     = class(EESLException);
  EESLDuplicitValue    = class(EESLException);
  EESLSortedList       = class(EESLException);

{===============================================================================
--------------------------------------------------------------------------------
                          TESLDelimitedTextParserBase
--------------------------------------------------------------------------------
===============================================================================}
type
  TESLDelimitedTextParserState = (dtpsInitial,dtpsWhiteSpace,dtpsDelimiter,
                                  dtpsNormalText,dtpsQuotedText);

  TESLDelimitedTextParserCharType = (dtpcWhiteSpace,dtpcDelimiter,dtpcQuoteChar,
                                     dtpcGeneral);

{===============================================================================
    TESLDelimitedTextParserBase - class declaration
===============================================================================}
type
  TESLDelimitedTextParserBase = class(TObject)
  protected
    // parsing vars
    fParserState: TESLDelimitedTextParserState;
    fPosition:    TStrSize;
    fItemStart:   TStrSize;
    fItemLength:  TStrSize;
    procedure Parse; overload; virtual;
    procedure Parse_Initial; virtual; abstract;
    procedure Parse_WhiteSpace; virtual; abstract;
    procedure Parse_Delimiter; virtual; abstract;
    procedure Parse_NormalText; virtual; abstract;
    procedure Parse_QuotedText; virtual; abstract;
  end;

{===============================================================================
--------------------------------------------------------------------------------
                              TExplicitStringList
--------------------------------------------------------------------------------
===============================================================================}
type
  TESLStringEndianness = (seSystem,seLittle,seBig);
  TESLLineBreakStyle   = (lbsUnknown,lbsWIN,lbsUNIX,lbsMAC,lbsRISC,
                          lbsCRLF,lbsLF,lbsCR,lbsLFCR);

{===============================================================================
    TExplicitStringList - class declaration
===============================================================================}
type
  TExplicitStringList = class(TCustomListObject)
  protected
    // list data
    fCount:                   Integer;
    // updating/changing
    fUpdateCount:             Integer;
    fListChanged:             Boolean;
    // list settings
    fOwnsObjects:             Boolean;
    fCaseSensitive:           Boolean;  // affects sorting and searching
    fDuplicates:              TDuplicates;
    fSorted:                  Boolean;
    fStrictSorted:            Boolean;
    fStrictDelimiter:         Boolean;
    fTrailingLineBreak:       Boolean;
    // IO parameters
    fFileSaveShareMode:       Word;
    fFileLoadShareMode:       Word;
    // change events
    fOnItemChangingCallback:  TIndexCallback;
    fOnItemChangingEvent:     TIndexEvent;
    fOnItemChangeCallback:    TIndexCallback;
    fOnItemChangeEvent:       TIndexEvent;
    fOnListChangingCallback:  TNotifyCallback;
    fOnListChangingEvent:     TNotifyEvent;
    fOnListChangeCallback:    TNotifyCallback;
    fOnListChangeEvent:       TNotifyEvent;
    fOnChangingCallback:      TNotifyCallback;
    fOnChangingEvent:         TNotifyEvent;
    fOnChangeCallback:        TNotifyCallback;
    fOnChangeEvent:           TNotifyEvent;
    // getters, setters
    Function GetObject(Index: Integer): TObject; virtual; abstract;
    procedure SetObject(Index: Integer; Value: TObject); virtual; abstract;
    Function GetItemUserData(Index: Integer): PtrInt; virtual; abstract;
    procedure SetItemUserData(Index: Integer; Value: PtrInt); virtual; abstract;
    Function GetChanged(Index: Integer): Boolean; virtual; abstract;
    procedure SetChanged(Index: Integer; Value: Boolean); virtual; abstract;
    Function GetDefString(Index: Integer): String; virtual; abstract;
    procedure SetDefString(Index: Integer; const Value: String); virtual; abstract;
    Function GetUpdating: Boolean; virtual;
    procedure SetSorted(Value: Boolean); virtual;
    Function GetLineBreakStyle: TESLLineBreakStyle; virtual; abstract;
    procedure SetLineBreakStyle(Value: TESLLineBreakStyle); virtual; abstract;
    // inherited list methods
    procedure SetCapacity(Value: Integer); override;
    Function GetCount: Integer; override;
    procedure SetCount(Value: Integer); override;
    // list manipulation methods
    procedure SetArrayLength(NewLen: Integer); virtual; abstract;
    procedure ClearArrayItem(Index: Integer; CanFreeObj: Boolean = True); virtual; abstract;
    // change events methods
    procedure DoItemChanging(Index: Integer; CallChanging: Boolean = True); virtual;
    procedure DoItemChange(Index: Integer; CallChange: Boolean = True); virtual;
    procedure DoListChanging(CallChanging: Boolean = True); virtual;
    procedure DoListChange(CallChange: Boolean = True); virtual;
    procedure DoChanging; virtual;
    procedure DoChange; virtual;
    // initialization, finalization methods
    procedure Initialize; virtual;
    procedure Finalize; virtual;
    // auxiliary methods
    class procedure WideSwapEndian(Data: PUInt16; Count: TStrSize); virtual;
    class procedure LongSwapEndian(Data: PUInt32; Count: TStrSize); virtual;
    class Function StrBufferSize(Buffer: Pointer): TMemSize; virtual; abstract;
    class Function CharSize: TMemSize; virtual; abstract;
    Function SortCompare(Idx1,Idx2: Integer): Integer; virtual; abstract;
    Function GetWriteLength: TStrSize; virtual; abstract; // for preallocations
    Function GetWriteSize: TMemSize; virtual;
    procedure WriteItemToStream(Stream: TStream; Index: Integer; Endianness: TESLStringEndianness); virtual; abstract;
    procedure WriteLineBreakToStream(Stream: TStream; Endianness: TESLStringEndianness); virtual; abstract;
    procedure WriteBOMToStream(Stream: TStream; Endianness: TESLStringEndianness); virtual; abstract;
    // internal methods
    Function InternalExtract(Index: Integer): TObject; virtual; abstract;
    procedure InternalSort(Reversed: Boolean = False); virtual;
    Function InternalGetText(out Size: TMemSize): Pointer; virtual;
    procedure InternalSetText(Text: Pointer; Size: TMemSize); virtual;
  public
    class Function GetSystemEndianness: TESLStringEndianness; virtual;  // can only return seLittle or seBig, never seSystem
    constructor Create;
    destructor Destroy; override;
    // update methods
    Function BeginUpdate: Integer; virtual;
    Function EndUpdate: Integer; virtual;
    // list index methods
    Function HighIndex: Integer; override;
    // list items methods
    Function IndexOfDefString(const Str: String): Integer; virtual; abstract;
    Function IndexOfObject(Obj: TObject): Integer; virtual; abstract;
    Function IndexOfUserData(UserData: PtrInt): Integer; virtual; abstract;
    Function FindDefString(const Str: String; out Index: Integer): Boolean; virtual; abstract;
    Function FindObject(Obj: TObject; out Index: Integer): Boolean; virtual; abstract;
    Function FindUserData(UserData: PtrInt; out Index: Integer): Boolean; virtual; abstract;
    Function AddDefString(const Str: String): Integer; virtual; abstract;
    Function AddDefStringObject(const Str: String; Obj: TObject): Integer; virtual; abstract;
    procedure AddStrings(Strings: TStrings); overload; virtual;
    procedure AddDefStrings(Strings: TStrings); overload; virtual;
    procedure AddDefStrings(Strings: array of String); overload; virtual;
    procedure AppendDefString(const Str: String); virtual; abstract;
    procedure AppendDefStringObject(const Str: String; Obj: TObject); virtual; abstract;
    procedure AppendStrings(Strings: TStrings); overload; virtual;
    procedure AppendDefStrings(Strings: TStrings); overload; virtual;
    procedure AppendDefStrings(Strings: array of String); overload; virtual;
    procedure InsertDefString(Index: Integer; const Str: String); virtual; abstract;
    procedure InsertDefStringObject(Index: Integer; const Str: String; Obj: TObject); virtual; abstract;
    procedure Move(SrcIdx,DstIdx: Integer); virtual; abstract;
    procedure Exchange(Idx1,Idx2: Integer); virtual; abstract;
    Function ExtractDefString(const Str: String): TObject; virtual; abstract;
    Function ExtractObject(Obj: TObject): TObject; virtual; abstract;
    Function ExtractUserData(UserData: PtrInt): TObject; virtual; abstract;
    Function RemoveDefString(const Str: String): Integer; virtual; abstract;
    Function RemoveObject(Obj: TObject): Integer; virtual; abstract;
    Function RemoveUserData(UserData: PtrInt): Integer; virtual; abstract;
    procedure Delete(Index: Integer); virtual; abstract;
    procedure Clear; virtual;
    // list manipulation methods
    procedure Sort(Reversed: Boolean = False); virtual; abstract;
    procedure Reverse; virtual;
    // list assignment
    procedure SetStrings(Strings: TStrings); overload; virtual;
    procedure SetDefStrings(Strings: TStrings); overload; virtual; abstract;
    procedure SetDefStrings(Strings: array of String); overload; virtual; abstract;
    procedure Assign(Source: TStrings); overload; virtual; abstract;
    procedure AssignTo(Destination: TStrings); overload; virtual; abstract;
    // streaming methods
  {
    BOM is written only for UTF8, Wide, Unicode and UCS4Strings.
    Endiannes affects only Wide, Unicode and UCS4Strings, it has no meaning for
    single-byte-character strings.
  }
    procedure SaveToStream(Stream: TStream; WriteBOM: Boolean = True; Endianness: TESLStringEndianness = seSystem); virtual;
    procedure SaveToFile(const FileName: String; WriteBOM: Boolean = True; Endianness: TESLStringEndianness = seSystem); virtual;
    procedure LoadFromStream(Stream: TStream; out Endianness: TESLStringEndianness); overload; virtual; abstract;
    procedure LoadFromStream(Stream: TStream); overload; virtual;
    procedure LoadFromFile(const FileName: String; out Endianness: TESLStringEndianness); overload; virtual;
    procedure LoadFromFile(const FileName: String); overload; virtual;
    procedure BinarySaveToStream(Stream: TStream); virtual; abstract;
    procedure BinarySaveToFile(const FileName: String); virtual;
    procedure BinaryLoadFromStream(Stream: TStream); virtual; abstract;
    procedure BinaryLoadFromFile(const FileName: String); virtual;
    // list data properties
    property Objects[Index: Integer]: TObject read GetObject write SetObject;
    property ItemUserData[Index: Integer]: PtrInt read GetItemUserData write SetItemUserData;
    property DefStrings[Index: Integer]: String read GetDefString write SetDefString;
    // updating properties
    property Updating: Boolean read GetUpdating;
    property UpdateCount: Integer read fUpdateCount;
    // settings properties
    property OwnsObjects: Boolean read fOwnsObjects write fOwnsObjects;
    property CaseSensitive: Boolean read fCaseSensitive write fCaseSensitive;
    property Duplicates: TDuplicates read fDuplicates write fDuplicates;
    property Sorted: Boolean read fSorted write SetSorted;
    property StrictSorted: Boolean read fStrictSorted write fStrictSorted;
    property StrictDelimiter: Boolean read fStrictDelimiter write fStrictDelimiter;
    property TrailingLineBreak: Boolean read fTrailingLineBreak write fTrailingLineBreak;
    property LineBreakStyle: TESLLineBreakStyle read GetLineBreakStyle write SetLineBreakStyle;
    // IO parameters
    property FileSaveShareMode: Word read fFileSaveShareMode write fFileSaveShareMode;
    property FileLoadShareMode: Word read fFileLoadShareMode write fFileLoadShareMode;
    // change events properties
    property OnItemChangingCallback: TIndexCallback read fOnItemChangingCallback write fOnItemChangingCallback;
    property OnItemChangingEvent: TIndexEvent read fOnItemChangingEvent write fOnItemChangingEvent;
    property OnItemChanging: TIndexEvent read fOnItemChangingEvent write fOnItemChangingEvent;
    property OnItemChangeCallback: TIndexCallback read fOnItemChangeCallback write fOnItemChangeCallback;
    property OnItemChangeEvent: TIndexEvent read fOnItemChangeEvent write fOnItemChangeEvent;
    property OnItemChange: TIndexEvent read fOnItemChangeEvent write fOnItemChangeEvent;
    property OnListChangingCallback: TNotifyCallback read fOnListChangingCallback write fOnListChangingCallback;
    property OnListChangingEvent: TNotifyEvent read fOnListChangingEvent write fOnListChangingEvent;
    property OnListChanging: TNotifyEvent read fOnListChangingEvent write fOnListChangingEvent;
    property OnListChangeCallback: TNotifyCallback read fOnListChangeCallback write fOnListChangeCallback;
    property OnListChangeEvent: TNotifyEvent read fOnListChangeEvent write fOnListChangeEvent;
    property OnListChange: TNotifyEvent read fOnListChangeEvent write fOnListChangeEvent;
    property OnChangingCallback: TNotifyCallback read fOnChangingCallback write fOnChangingCallback;
    property OnChangingEvent: TNotifyEvent read fOnChangingEvent write fOnChangingEvent;
    property OnChanging: TNotifyEvent read fOnChangingEvent write fOnChangingEvent;
    property OnChangeCallback: TNotifyCallback read fOnChangeCallback write fOnChangeCallback;
    property OnChangeEvent: TNotifyEvent read fOnChangeEvent write fOnChangeEvent;
    property OnChange: TNotifyEvent read fOnChangeEvent write fOnChangeEvent;
  end;

implementation

uses
  StrRect, ListSorters, StaticMemoryStream;

{===============================================================================
--------------------------------------------------------------------------------
                          TESLDelimitedTextParserBase
--------------------------------------------------------------------------------
===============================================================================}
{===============================================================================
    TESLDelimitedTextParserBase - class implementation
===============================================================================}
{-------------------------------------------------------------------------------
    TESLDelimitedTextParserBase - protected methods
-------------------------------------------------------------------------------}

procedure TESLDelimitedTextParserBase.Parse;
begin
case fParserState of
  dtpsInitial:    Parse_Initial;
  dtpsWhiteSpace: Parse_WhiteSpace;
  dtpsDelimiter:  Parse_Delimiter;
  dtpsNormalText: Parse_NormalText;
  dtpsQuotedText: Parse_QuotedText;
else
  raise EESLInvalidValue.CreateFmt('%s.Parse: Invalid parser state (%d).',[Self.ClassName,Ord(fParserState)]);
end;
Inc(fPosition);
end;

{===============================================================================
--------------------------------------------------------------------------------
                              TExplicitStringList
--------------------------------------------------------------------------------
===============================================================================}
{===============================================================================
    TExplicitStringList - class implementation
===============================================================================}
{-------------------------------------------------------------------------------
    TExplicitStringList - protected methods
-------------------------------------------------------------------------------}

Function TExplicitStringList.GetUpdating: Boolean;
begin
Result := fUpdateCount > 0;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SetSorted(Value: Boolean);
begin
If Value <> fSorted then
  begin
    If Value then
      Sort(False);
    fSorted := Value;
  end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SetCapacity(Value: Integer);
var
  OldCap: Integer;
  i:      Integer;
begin
If Value >= 0 then
  begin
    OldCap := Capacity;
    If Value > OldCap then
      begin
        // increasing capacity
        SetArrayLength(Value);
        For i := OldCap to Pred(Value) do
          ClearArrayItem(i);
      end
    else If Value < OldCap then
      begin
        // decreasing capacity
        If Value < fCount then
          begin
            DoListChanging;
            For i := Value to Pred(fCount) do
              ClearArrayItem(i);
          end;
        SetArrayLength(Value);
        If Value < fCount then
          begin
            fCount := Value;
            DoListChange;
          end;
      end;
  end
else raise EESLInvalidValue.CreateFmt('TExplicitStringList.SetCapacity: Invalid capacity (%d).',[Value]);
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.GetCount: Integer;
begin
Result := fCount;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SetCount(Value: Integer);
var
  i:  Integer;
begin
If Value >= 0 then
  begin
    If Value <> fCount then
      begin
        DoListChanging;
        If Value > fCount then
          begin
            If Value > Capacity then
              SetCapacity(Value);
            For i := fCount to Pred(Value) do
              ClearArrayItem(i);
          end
        else If Value < fCount then
          For i := Value to Pred(fCount) do
            ClearArrayItem(i);
        fCount := Value;
        DoListChange;
      end;
  end
else raise EESLInvalidValue.CreateFmt('TExplicitStringList.SetCount: Invalid count (%d).',[Value]);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoItemChanging(Index: Integer; CallChanging: Boolean = True);
begin
If CallChanging then
  DoChanging;
If Assigned(fOnItemChangingCallback) then
  fOnItemChangingCallback(Self,Index);
If Assigned(fOnItemChangingEvent) then
  fOnItemChangingEvent(Self,Index);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoItemChange(Index: Integer; CallChange: Boolean = True);
begin
SetChanged(Index,True);
If fUpdateCount <= 0 then
  begin
    If Assigned(fOnItemChangeCallback) then
      fOnItemChangeCallback(Self,Index);
    If Assigned(fOnItemChangeEvent) then
      fOnItemChangeEvent(Self,Index);
  end;
If CallChange then
  DoChange;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoListChanging(CallChanging: Boolean = True);
begin
If CallChanging then
  DoChanging;
If Assigned(fOnListChangingCallback) then
  fOnListChangingCallback(Self);
If Assigned(fOnListChangingEvent) then
  fOnListChangingEvent(Self);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoListChange(CallChange: Boolean = True);
begin
fListChanged := True;
If fUpdateCount <= 0 then
  begin
    If Assigned(fOnListChangeCallback) then
      fOnListChangeCallback(Self);
    If Assigned(fOnListChangeEvent) then
      fOnListChangeEvent(Self);
  end;
If CallChange then
  DoChange;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoChanging;
begin
If Assigned(fOnChangingCallback) then
  fOnChangingCallback(Self);
If Assigned(fOnChangingEvent) then
  fOnChangingEvent(Self);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoChange;
begin
If fUpdateCount <= 0 then
  begin
    If Assigned(fOnChangeCallback) then
      fOnChangeCallback(Self);
    If Assigned(fOnChangeEvent) then
      fOnChangeEvent(Self);
  end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Initialize;
begin
fCount := 0;
fUpdateCount := 0;
fListChanged := False;
fOwnsObjects := False;
fCaseSensitive := False;
fDuplicates := dupAccept;
fSorted := False;
fStrictSorted := True;
fStrictDelimiter := False;
fTrailingLineBreak := True;
fFileSaveShareMode := fmShareDenyWrite;
fFileLoadShareMode := fmShareDenyWrite;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Finalize;
begin
// prevent change events
fOnItemChangingCallback := nil;
fOnItemChangingEvent := nil;
fOnItemChangeCallback := nil;
fOnItemChangeEvent := nil;
fOnListChangingCallback := nil;
fOnListChangingEvent := nil;
fOnListChangeCallback := nil;
fOnListChangeEvent := nil;
fOnChangingCallback := nil;
fOnChangingEvent := nil;
fOnChangeCallback := nil;
fOnChangeEvent := nil;
Clear;
end;

//------------------------------------------------------------------------------

class procedure TExplicitStringList.WideSwapEndian(Data: PUInt16; Count: TStrSize);
var
  i:  TStrSize;
begin
If Count > 0 then
  For i := 0 to Pred(Count) do
    begin
      PUInt16(Data)^ := (Data^ shr 8) or (Data^ shl 8);
      Inc(Data);
    end;
end;

//------------------------------------------------------------------------------

class procedure TExplicitStringList.LongSwapEndian(Data: PUInt32; Count: TStrSize);
var
  i:  TStrSize;
begin
If Count > 0 then
  For i := 0 to Pred(Count) do
    begin
      PUInt32(Data)^ := ((Data^ and $FF000000) shr 24) or ((Data^ and $00FF0000) shr 8) or 
                        ((Data^ and $0000FF00) shl 8) or ((Data^ and $000000FF) shl 24);
      Inc(Data);
    end;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.GetWriteSize: TMemSize;
begin
// GetWriteLength should newer return a negative value
Result := TMemSize(GetWriteLength) * CharSize;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.InternalSort(Reversed: Boolean = False);
var
  Sorter: TListSorter;
begin
If fCount > 1 then
  begin
    BeginUpdate;
    try
      DoListChanging;
      Sorter := TListQuickSorter.Create(SortCompare,Exchange);
      try
        Sorter.Reversed := Reversed;
        Sorter.Sort(LowIndex,HighIndex);
      finally
        Sorter.Free;
      end;
      DoListChange;
    finally
      EndUpdate;
    end;
  end;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.InternalGetText(out Size: TMemSize): Pointer;
var
  Stream: TWritableStaticMemoryStream;
begin
Size := GetWriteSize;
If Size > 0 then
  begin
    Inc(Size,CharSize);         // CharSize for a terminating zero
    Result := AllocMem(Size);   // also zeroes memory
    Stream := TWritableStaticMemoryStream.Create(Result,Size - CharSize);
    try
      Stream.Seek(0,soBeginning);
      SaveToStream(Stream,False,seSystem);
    finally
      Stream.Free;
    end;
  end
else
  begin
    Result := AllocMem(CharSize); // string consisting only of a terminating zero
    Size := CharSize;
  end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.InternalSetText(Text: Pointer; Size: TMemSize);
var
  Stream: TStaticMemoryStream;
begin
If Assigned(Text) and (Size >= CharSize) then
  begin
    BeginUpdate;
    try
      DoListChanging;
      Clear;
      // subtract CharSize for a terminating zero
      Stream := TStaticMemoryStream.Create(Text,Size - CharSize);
      try
        Stream.Seek(0,soBeginning);
        LoadFromStream(Stream);
      finally
        Stream.Free;
      end;
      DoListChange;
    finally
      EndUpdate;
    end;
  end;
end;

{-------------------------------------------------------------------------------
    TExplicitStringList - public methods
-------------------------------------------------------------------------------}

class Function TExplicitStringList.GetSystemEndianness: TESLStringEndianness;
begin
Result := {$IFDEF ENDIAN_BIG}seBig{$ELSE}seLittle{$ENDIF};
end;

//------------------------------------------------------------------------------

constructor TExplicitStringList.Create;
begin
inherited Create;
Initialize;
end;

//------------------------------------------------------------------------------

destructor TExplicitStringList.Destroy;
begin
Finalize;
inherited;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.BeginUpdate: Integer;
var
  i:  Integer;
begin
If fUpdateCount <= 0 then
  begin
    fUpdateCount := 0;
    For i := LowIndex to HighIndex do
      SetChanged(i,False);
    fListChanged := False;
  end;
Inc(fUpdateCount);
Result := fUpdateCount;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.EndUpdate: Integer;
var
  i:  Integer;
begin
Dec(fUpdateCount);
If fUpdateCount <= 0 then
  begin
    fUpdateCount := 0;
    For i := LowIndex to HighIndex do
      If GetChanged(i) then
        begin
          DoItemChange(i);
          SetChanged(i,False);
        end;
    If fListChanged then
      DoListChange(False);
    fListChanged := False;
    DoChange;
  end;
Result := fUpdateCount;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.HighIndex: Integer;
begin
Result := Pred(fCount);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.AddStrings(Strings: TStrings);
begin
AddDefStrings(Strings);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.AddDefStrings(Strings: TStrings);
var
  i:  Integer;
begin
BeginUpdate;
try
  Grow(Strings.Count);
  For i := 0 to Pred(Strings.Count) do
    AddDefStringObject(Strings[i],Strings.Objects[i]);
finally
  EndUpdate;
end;
end;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

procedure TExplicitStringList.AddDefStrings(Strings: array of String);
var
  i:  Integer;
begin
BeginUpdate;
try
  Grow(Length(Strings));
  For i := Low(Strings) to High(Strings) do
    AddDefString(Strings[i]);
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.AppendStrings(Strings: TStrings);
begin
AppendDefStrings(Strings);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.AppendDefStrings(Strings: TStrings);
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    AddDefStrings(Strings);
  end
else raise EESLSortedList.CreateFmt('%s.AppendDefStrings: Cannot append to sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.AppendDefStrings(Strings: array of String);
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    AddDefStrings(Strings);
  end
else raise EESLSortedList.CreateFmt('%s.AppendDefStrings: Cannot append to sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Clear;
var
  i:  Integer;
begin
If fCount > 0 then
  begin
    DoListChanging;
    // fOwnsObjects is checked again in ClearArrayItem, but can prevent useless for cycle
    If fOwnsObjects then
      For i := LowIndex to HighIndex do
        ClearArrayItem(i);
    SetArrayLength(0);
    fCount := 0;
    DoListChange;
  end
else SetArrayLength(0); // to be sure
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Reverse;
var
  i:  Integer;
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    If fCount > 1 then
      begin
        BeginUpdate;
        try
          DoListChanging;
          For i := LowIndex to Pred(fCount shr 1) do
            Exchange(i,HighIndex - i);
          DoListChange;            
        finally
          EndUpdate;
        end;
      end;
  end
else raise EESLSortedList.CreateFmt('%s.Reverse: Cannot reverse sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SetStrings(Strings: TStrings);
begin
SetDefStrings(Strings);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SaveToStream(Stream: TStream; WriteBOM: Boolean = True; Endianness: TESLStringEndianness = seSystem);
var
  WriteSize:    UInt64;
  PositionTemp: Int64;
  i:            Integer;
begin
If WriteBOM then
  WriteBOMToStream(Stream,Endianness);
WriteSize := GetWriteSize;
// preallocate space
If Stream.Size < (Stream.Position + WriteSize) then
  begin
    PositionTemp := Stream.Position;
    try
      Stream.Size := Stream.Position + WriteSize;
    finally
      Stream.Position := PositionTemp;
    end;
  end;
// write data
For i := LowIndex to HighIndex do
  begin
    WriteItemToStream(Stream,i,Endianness);
    If (i < HighIndex) or fTrailingLineBreak then
      WriteLineBreakToStream(Stream,Endianness);
  end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SaveToFile(const FileName: String; WriteBOM: Boolean = True; Endianness: TESLStringEndianness = seSystem);
var
  FileStream: TFileStream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmCreate or fFileSaveShareMode);
try
  FileStream.Seek(0,soBeginning);
  SaveToStream(FileStream,WriteBOM,Endianness);
finally
  FileStream.Free;
end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.LoadFromStream(Stream: TStream);
var
  Endianness: TESLStringEndianness;
begin
LoadFromStream(Stream,Endianness);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.LoadFromFile(const FileName: String; out Endianness: TESLStringEndianness);
var
  FileStream: TFileStream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmOpenRead or fFileLoadShareMode);
try
  FileStream.Seek(0,soBeginning);
  LoadFromStream(FileStream,Endianness);
finally
  FileStream.Free;
end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.LoadFromFile(const FileName: String);
var
  Endianness: TESLStringEndianness;
begin
LoadFromFile(FileName,Endianness);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.BinarySaveToFile(const FileName: String);
var
  FileStream: TFileStream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmCreate or fFileSaveShareMode);
try
  FileStream.Seek(0,soBeginning);
  BinarySaveToStream(FileStream);
finally
  FileStream.Free;
end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.BinaryLoadFromFile(const FileName: String);
var
  FileStream: TFileStream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmOpenRead or fFileLoadShareMode);
try
  FileStream.Seek(0,soBeginning);
  BinaryLoadFromStream(FileStream);
finally
  FileStream.Free;
end;
end;

end.
