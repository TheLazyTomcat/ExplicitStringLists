unit ExplicitStringListsBase;

{$INCLUDE '.\ExplicitStringLists_defs.inc'}

interface

uses
  SysUtils, Classes, AuxTypes;

{$IF not Declared(UTF8ToString)}
Function UTF8ToString(const Str: UTF8String): UnicodeString;{$IFDEF CanInline} inline; {$ENDIF}
{$DEFINE UTF8ToString_Implement}
{$IFEND}

type
  EExplicitStringListError = Exception;

  TExplicitStringList = class(TPersistent)
  private
    fOnChanging:  TNotifyEvent;
    fOnChange:    TNotifyEvent;
  protected
    fCount:             Integer;
    fUpdateCount:       Integer;
    fChanged:           Boolean;
    fCaseSensitive:     Boolean;
    fStrictDelimiter:   Boolean;
    fTrailingLineBreak: Boolean;
    fDuplicates:        TDuplicates;
    fSorted:            Boolean;
    Function GetUpdating: Boolean;
    Function CompareItems(Index1,Index2: Integer): Integer; virtual; abstract;
    procedure WriteItemToStream(Stream: TStream; Index: Integer); virtual; abstract;
    procedure WriteLineBreakToStream(Stream: TStream); virtual; abstract;
    procedure WriteBOMToStream(Stream: TStream); virtual; abstract;
    procedure SetUpdateState({%H-}Updating: Boolean); virtual;
    procedure Error(const Msg: string; Data: array of const); virtual;
    procedure DoChange; virtual;
    procedure DoChanging; virtual;
  public
    constructor Create;
    Function BeginUpdate: Integer; virtual;
    Function EndUpdate: Integer; virtual;
    Function LowIndex: Integer; virtual; abstract;
    Function HighIndex: Integer; virtual; abstract;
    procedure Exchange(Idx1, Idx2: Integer); virtual; abstract;
    procedure Sort(Reversed: Boolean = False); virtual;
    procedure LoadFromStream(Stream: TStream); virtual; abstract;
    procedure LoadFromFile(const FileName: String); virtual;
    procedure SaveToStream(Stream: TStream; WriteBOM: Boolean = True); virtual;
    procedure SaveToFile(const FileName: String; WriteBOM: Boolean = True); virtual;
  published
    property Count: Integer read fCount;
    property UpdateCount: Integer read fUpdateCount;
    property Updating: Boolean read GetUpdating;
    property Changed: Boolean read fChanged;
    property CaseSensitive: Boolean read fCaseSensitive write fCaseSensitive;
    property StrictDelimiter: Boolean read fStrictDelimiter write fStrictDelimiter;
    property TrailingLineBreak: Boolean read fTrailingLineBreak write fTrailingLineBreak;
    property Duplicates: TDuplicates read fDuplicates write fDuplicates;
    property Sorted: Boolean read fSorted;
    property OnChanging: TNotifyEvent read fOnChanging write fOnChanging;
    property OnChange: TNotifyEvent read fOnChange write fOnChange;    
  end;

implementation

uses
  StrRect;

{$IFDEF UTF8ToString_Implement}
Function UTF8ToString(const Str: UTF8String): UnicodeString;
begin
Result := UTF8Decode(Str);
end;
{$ENDIF}

//==============================================================================

Function TExplicitStringList.GetUpdating: Boolean;
begin
Result := fUpdateCount > 0;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SetUpdateState(Updating: Boolean);
begin
// nothing to do here
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Error(const Msg: string; Data: array of const);
begin
raise EExplicitStringListError.CreateFmt(ClassName + '.' + Msg,Data);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoChanging;
begin
If fUpdateCount <= 0 then
  If Assigned(fOnChanging) then
    fOnChanging(Self);
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.DoChange;
begin
If fUpdateCount <= 0 then
  begin
    If Assigned(fOnChange) then
      fOnChange(Self);
  end
else fChanged := True;
end;

//==============================================================================

constructor TExplicitStringList.Create;
begin
inherited;
fOnChanging := nil;
fOnChange := nil;
fCount := 0;
fUpdateCount := 0;
fChanged := False;
fCaseSensitive := False;
fStrictDelimiter := False;
fTrailingLineBreak := True;
fDuplicates := dupAccept;
fSorted := False;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.BeginUpdate: Integer;
begin
DoChanging;
If fUpdateCount = 0 then
  SetUpdateState(True);
fChanged := False;
Inc(fUpdateCount);
Result := fUpdateCount;
end;

//------------------------------------------------------------------------------

Function TExplicitStringList.EndUpdate: Integer;
begin
Dec(fUpdateCount);
If fUpdateCount = 0 then
  begin
    SetUpdateState(False);
    If fChanged then DoChange;
    fChanged := False;
  end;
Result := fUpdateCount;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.Sort(Reversed: Boolean = False);

  procedure QuickSort(LeftIdx,RightIdx,Coef: Integer);
  var
    Idx,i:  Integer;
  begin
    If LeftIdx < RightIdx then
      begin
        Exchange((LeftIdx + RightIdx) shr 1,RightIdx);
        Idx := LeftIdx;
        For i := LeftIdx to Pred(RightIdx) do
          If (CompareItems(RightIdx,i) * Coef) > 0 then
            begin
              Exchange(i,idx);
              Inc(Idx);
            end;
        Exchange(Idx,RightIdx);
        QuickSort(LeftIdx,Idx - 1,Coef);
        QuickSort(Idx + 1,RightIdx,Coef);
      end;
  end;
  
begin
If fCount > 1 then
  begin
    BeginUpdate;
    try
      If Reversed then
        QuickSort(LowIndex,HighIndex,-1)
      else
        QuickSort(LowIndex,HighIndex,1);
      fSorted := not Reversed;
    finally
      EndUpdate;
    end;
  end
else fSorted := True;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.LoadFromFile(const FileName: String);
var
  FileStream: TFileStream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmOpenRead or fmShareDenyWrite);
try
  LoadFromStream(FileStream);
finally
  FileStream.Free;
end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SaveToStream(Stream: TStream; WriteBOM: Boolean = True);
var
  i:  Integer;
begin
If WriteBOM then
  WriteBOMToStream(Stream);
For i := LowIndex to HighIndex do
  begin
    WriteItemToStream(Stream,i);
    If (i < HighIndex) or fTrailingLineBreak then
      WriteLineBreakToStream(Stream);
  end;
end;

//------------------------------------------------------------------------------

procedure TExplicitStringList.SaveToFile(const FileName: String; WriteBOM: Boolean = True);
var
  FileStream: TFileStream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmCreate or fmShareDenyWrite);
try
  SaveToStream(FileStream, WriteBOM);
finally
  FileStream.Free;
end;
end;

end.
