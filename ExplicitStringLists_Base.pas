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
  EESLInvalidValue     = class(EESLException);

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
    fObjects:                 array of TObject;
    fCount:                   Integer;
    // updating/changing
    fUpdateCounter:           Integer;
    fChangeFlags:             array of Boolean;
    fChanged:                 Boolean;
    // list settings
    fOwnsObjects:             Boolean;
    fCaseSensitive:           Boolean;  // affects sorting and searching
    fStrictDelimiter:         Boolean;
    fTrailingLineBreak:       Boolean;
    fDuplicates:              TDuplicates;
    fSorted:                  Boolean;
    // change events
    fOnItemChangingCallback:  TIndexCallback;
    fOnItemChangingEvent:     TIndexEvent;
    fOnItemChangeCallback:    TIndexCallback;
    fOnItemChangeEvent:       TIndexEvent;
    fOnChangingCallback:      TNotifyCallback;
    fOnChangingEvent:         TNotifyEvent;
    fOnChangeCallback:        TNotifyCallback;
    fOnChangeEvent:           TNotifyEvent;
    // getters, setters
    Function GetObject(Index: Integer): TObject; virtual;
    procedure SetObject(Index: Integer; Value: TObject); virtual;
    Function GetString(Index: Integer): String; virtual; abstract;
    procedure SetString(Index: Integer; const Value: String); virtual; abstract;
    Function GetUpdating: Boolean; virtual;
    procedure SetSorted(Value: Boolean); virtual;
    Function GetLineBreakStyle: TESLLineBreakStyle; virtual; abstract;
    procedure SetLineBreakStyle(Value: TESLLineBreakStyle); virtual; abstract;
    // list methods
    Function GetCapacity: Integer; override;
    procedure SetCapacity(Value: Integer); override;
    Function GetCount: Integer; override;
    procedure SetCount(Value: Integer); override;
    // list manipulation
    procedure SetArraysLength(NewLen: Integer); virtual;
    procedure ClearArrayItem(Index: Integer); virtual;
    // change events
    procedure DoItemChanging(Index: Integer); virtual;  
    procedure DoItemChange(Index: Integer); virtual;
    procedure DoChanging; virtual;
    procedure DoChange; virtual;
    // initialization, finalalization
    procedure Initialize; virtual;
    procedure Finalize; virtual;
    // auxiliary methods
    Function CompareItems(Idx1,Idx2: Integer): Integer; virtual; abstract;  // for sorting
    Function GetWriteSize: TMemSize; virtual; abstract;                     // for preallocations    
    class procedure WideSwapEndian(Data: PWideChar; Count: TStrSize); virtual;
  public
    class Function GetSystemEndianness: TESLStringEndianness; virtual;      // can only return seLittle or seBig, never seSystem
    constructor Create;
    destructor Destroy; override;
    // update methods
    Function BeginUpdate: Integer; virtual;
    Function EndUpdate: Integer; virtual;
    // list index methods
    Function LowIndex: Integer; override;
    Function HighIndex: Integer; override;
    // list item methods
    Function IndexOf(Obj: TObject): Integer; overload; virtual;
    Function Find(Obj: TObject; out Index: Integer): Boolean; overload; virtual;
    Function AddDef(const Str: String): Integer; overload; virtual; abstract;
    Function AddObjectDef(const Str: String; Obj: TObject): Integer; overload; virtual; abstract;
    procedure AddStrings(Strings: TStrings); overload; virtual;
    procedure AddStringsDef(Strings: TStrings); overload; virtual; abstract;
    procedure AddStringsDef(Strings: array of String); overload; virtual; abstract;
    procedure Insert(Index: Integer; const Str: String); overload; virtual; abstract;
    procedure InsertObject(Index: Integer; const Str: String); overload; virtual; abstract;
    procedure Move(Src,Dst: Integer); virtual; abstract;
    procedure Exchange(Idx1,Idx2: Integer); virtual; abstract;
    Function Extract(Obj: TObject): TObject; overload; virtual;
    Function Remove(Obj: TObject): Integer; overload; virtual;
    procedure Delete(Index: Integer); virtual; abstract;
    procedure Clear; virtual;
    // list manipulation
    procedure Sort(Reversed: Boolean = False); virtual;
    // procedure Assign(Source: TExplicitStringList); overload; virtual;
    // procedure Assign(Source: TStrings); overload; virtual;
    // procedure AssignTo(Destination: TExplicitStringList); overload; virtual;
    // procedure AssignTo(Destination: TStrings); overload; virtual;
    // streaming
    //procedure LoadFromStream(Stream: TStream; out Endianness: TStringEndianness); overload; virtual; abstract;
    //procedure LoadFromStream(Stream: TStream); overload; virtual;
    //procedure LoadFromFile(const FileName: String; out Endianness: TStringEndianness); overload; virtual;
    //procedure LoadFromFile(const FileName: String); overload; virtual;
  {
    BOM is written only for UTF8-, Wide- and UnicodeStrings.
    Endiannes affects only Wide- and UnicodeStrings, it has no meaning for
    single-byte-character strings.
  }
    //procedure SaveToStream(Stream: TStream; WriteBOM: Boolean = True; Endianness: TStringEndianness = seSystem); virtual;
    //procedure SaveToFile(const FileName: String; WriteBOM: Boolean = True; Endianness: TStringEndianness = seSystem); virtual;
    // list data
    property Objects[Index: Integer]: TObject read GetObject write SetObject;
    property Strings[Index: Integer]: String read GetString write SetString;
    // updating
    property Updating: Boolean read GetUpdating;
    // list settings
    property OwnsObjects: Boolean read fOwnsObjects write fOwnsObjects;
    property CaseSensitive: Boolean read fCaseSensitive write fCaseSensitive;
    property StrictDelimiter: Boolean read fStrictDelimiter write fStrictDelimiter;
    property TrailingLineBreak: Boolean read fTrailingLineBreak write fTrailingLineBreak;
    property Duplicates: TDuplicates read fDuplicates write fDuplicates;
    property Sorted: Boolean read fSorted write SetSorted;
    property LineBreakStyle: TESLLineBreakStyle read GetLineBreakStyle write SetLineBreakStyle;
    // change events
    property OnItemChangingCallback: TIndexCallback read fOnItemChangingCallback write fOnItemChangingCallback;
    property OnItemChangingEvent: TIndexEvent read fOnItemChangingEvent write fOnItemChangingEvent;
    property OnItemChanging: TIndexEvent read fOnItemChangingEvent write fOnItemChangingEvent;
    property OnItemChangeCallback: TIndexCallback read fOnItemChangeCallback write fOnItemChangeCallback;
    property OnItemChangeEvent: TIndexEvent read fOnItemChangeEvent write fOnItemChangeEvent;
    property OnItemChange: TIndexEvent read fOnItemChangeEvent write fOnItemChangeEvent;
    property OnChangingCallback: TNotifyCallback read fOnChangingCallback write fOnChangingCallback;
    property OnChangingEvent: TNotifyEvent read fOnChangingEvent write fOnChangingEvent;
    property OnChanging: TNotifyEvent read fOnChangingEvent write fOnChangingEvent;
    property OnChangeCallback: TNotifyCallback read fOnChangeCallback write fOnChangeCallback;
    property OnChangeEvent: TNotifyEvent read fOnChangeEvent write fOnChangeEvent;
    property OnChange: TNotifyEvent read fOnChangeEvent write fOnChangeEvent;
  end;

implementation

uses
  ListSorters;

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

Function TExplicitStringList.GetObject(Index: Integer): TObject;
begin
If CheckIndex(Index) then
  Result := fObjects[Index]
else
  raise EESLIndexOutOfBounds.CreateFmt('TExplicitStringList.GetObject: Index (%d) out of bounds.',[Index]);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SetObject(Index: Integer; Value: TObject);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    If Assigned(fObjects[Index]) and fOwnsObjects then
      FreeAndNil(fObjects[Index]);
    fObjects[Index] := Value;
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('TExplicitStringList.SetObject: Index (%d) out of bounds.',[Index]);
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.GetUpdating: Boolean;
begin
Result := fUpdateCounter > 0;
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

Function TExplicitStringList.GetCapacity: Integer;
begin
Result := Length(fObjects);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SetCapacity(Value: Integer);
var
  OldCap: Integer;
  i:      Integer;
begin
If Value >= 0 then
  begin
    OldCap := Length(fObjects);
    If Value > OldCap then
      begin
        // increasing capacity
        SetArraysLength(Value);
        For i := OldCap to Pred(Value) do
          ClearArrayItem(i);
      end
    else If Value < OldCap then
      begin
        // decreasing capacity
        If Value < fCount then
          begin
            DoChanging;
            For i := Value to Pred(fCount) do
              ClearArrayItem(i);
          end;
        SetArraysLength(Value);
        If Value < fCount then
          begin
            fCount := Value;
            DoChange;
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
        DoChanging;
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
        DoChange;
      end;
  end
else raise EESLInvalidValue.CreateFmt('TExplicitStringList.SetCount: Invalid count (%d).',[Value]);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SetArraysLength(NewLen: Integer);
begin
SetLength(fObjects,NewLen);
SetLength(fChangeFlags,NewLen);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.ClearArrayItem(Index: Integer);
begin
If Assigned(fObjects[Index]) and fOwnsObjects then
  FreeAndNil(fObjects[Index])
else
  fObjects[Index] := nil;
fChangeFlags[Index] := False;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoItemChanging(Index: Integer);
begin
If fUpdateCounter <= 0 then
  begin
    If Assigned(fOnItemChangingCallback) then
      fOnItemChangingCallback(Self,Index);
    If Assigned(fOnItemChangingEvent) then
      fOnItemChangingEvent(Self,Index);
  end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoItemChange(Index: Integer);
begin
fChangeFlags[Index] := True;
fChanged := True;
If fUpdateCounter <= 0 then
  begin
    If Assigned(fOnItemChangeCallback) then
      fOnItemChangeCallback(Self,Index);
    If Assigned(fOnItemChangeEvent) then
      fOnItemChangeEvent(Self,Index);
  end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoChanging;
begin
If fUpdateCounter <= 0 then
  begin
    If Assigned(fOnChangingCallback) then
      fOnChangingCallback(Self);
    If Assigned(fOnChangingEvent) then
      fOnChangingEvent(Self);
  end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoChange;
begin
fChanged := True;
If fUpdateCounter <= 0 then
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
SetLength(fObjects,0);
SetLength(fChangeFlags,0);
fCount := 0;
fUpdateCounter := 0;
fChanged := False;
fOwnsObjects := False;
fCaseSensitive := False;
fStrictDelimiter := False;
fTrailingLineBreak := True;
fDuplicates := dupAccept;
fSorted := False;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Finalize;
begin
// prevent change events
fOnItemChangingCallback := nil;
fOnItemChangingEvent := nil;
fOnItemChangeCallback := nil;
fOnItemChangeEvent := nil;
fOnChangingCallback := nil;
fOnChangingEvent := nil;
fOnChangeCallback := nil;
fOnChangeEvent := nil;
Clear;
end;

//------------------------------------------------------------------------------

class procedure TExplicitStringList.WideSwapEndian(Data: PWideChar; Count: TStrSize);
var
  i:  Integer;
begin
If Count > 0 then
  For i := 0 to Pred(Count) do
    begin
      PUInt16(Data)^ := UInt16(PUInt16(Data)^ shr 8) or UInt16(PUInt16(Data)^ shl 8);
      Inc(Data);
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
If fUpdateCounter <= 0 then
  begin
    fUpdateCounter := 0;
    For i := LowIndex to HighIndex do
      fChangeFlags[i] := False;
    fChanged := False;
  end;
Inc(fUpdateCounter);
Result := fUpdateCounter;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.EndUpdate: Integer;
var
  i:  Integer;
begin
Dec(fUpdateCounter);
If fUpdateCounter <= 0 then
  begin
    fUpdateCounter := 0;
    For i := LowIndex to HighIndex do
      If fChangeFlags[i] then
        begin
          DoItemChange(i);
          fChangeFlags[i] := False;
        end;
    If fChanged then
      DoChange;
  end;
Result := fUpdateCounter;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.LowIndex: Integer;
begin
Result := Low(fObjects);  // should be always 0
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.HighIndex: Integer;
begin
Result := Pred(fCount);
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.IndexOf(Obj: TObject): Integer;
var
  i:  Integer;
begin
Result := -1;
For i := LowIndex to HighIndex do
  If fObjects[i] = Obj then
    begin
      Result := i;
      Break{For i};
    end;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.Find(Obj: TObject; out Index: Integer): Boolean;
begin
Index := IndexOf(Obj);
Result := CheckIndex(Index);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.AddStrings(Strings: TStrings);
begin
AddStringsDef(Strings);
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.Extract(Obj: TObject): TObject;
var
  Index:  Integer;
begin
Index := IndexOf(Obj);
If CheckIndex(Index) then
  begin
    Result := fObjects[Index];
    fObjects[Index] := nil;
    Delete(Index);
  end
else Result := nil;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.Remove(Obj: TObject): Integer;
begin
Result := IndexOf(Obj);
If CheckIndex(Result) then
  Delete(Result);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Clear;
var
  i:  Integer;
begin
If fCount > 0 then
  begin
    DoChanging;
    If fOwnsObjects then
      For i := LowIndex to HighIndex do
        ClearArrayItem(i);
    SetArraysLength(0);
    fCount := 0;
    DoChange;
  end
else SetArraysLength(0);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Sort(Reversed: Boolean = False);
var
  Sorter: TListSorter;
begin
If fCount > 1 then
  begin
    BeginUpdate;
    try
      Sorter := TListQuickSorter.Create(CompareItems,Exchange);
      try
        Sorter.Reversed := Reversed;
        Sorter.Sort(LowIndex,HighIndex);
      finally
        Sorter.Free;
      end;
    finally
      EndUpdate;
    end;
  end
else fSorted := True;
end;

end.
