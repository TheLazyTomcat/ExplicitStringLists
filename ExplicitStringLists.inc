{$IFDEF ESL_ClassTypes}
  TESLListItem = record
    Str:      TESLStringType;
    Obj:      TObject;
    Changed:  Boolean;
  end;
{$ENDIF ESL_ClassTypes}

{$IFDEF ESL_ClassDeclaration}
  protected
    fItems:               array of TESLListItem;
    fNameValueSeparator:  TESLCharType;
    fLineBreak:           TESLStringType;
    fDelimiter:           TESLCharType;
    fQuoteChar:           TESLCharType;
    // custom sorting
    fCompareFuncIndex:    TESLSortCompareIndexType;
    fCompareFuncString:   TESLSortCompareStringType;
    // getters, setters
    Function GetItem(Index: Integer): TESLListItem; virtual;
    Function GetString(Index: Integer): TESLStringType; virtual;
    procedure SetString(Index: Integer; const Value: TESLStringType); virtual;
    Function GetObject(Index: Integer): TObject; override;
    procedure SetObject(Index: Integer; Value: TObject); override;
    Function GetChanged(Index: Integer): Boolean; override;
    procedure SetChanged(Index: Integer; Value: Boolean); override;
    Function GetDefString(Index: Integer): String; override;
    procedure SetDefString(Index: Integer; const Value: String); override;
    Function GetName(Index: Integer): TESLStringType; virtual;
    procedure SetName(Index: Integer; const Value: TESLStringType); virtual;
    Function GetValue(const Name: TESLStringType): TESLStringType; virtual;
    procedure SetValue(const Name: TESLStringType; const Value: TESLStringType); virtual;
    Function GetValueFromIndex(Index: Integer): TESLStringType; virtual;
    procedure SetValueFromIndex(Index: Integer; const Value: TESLStringType); virtual;
    Function GetLineBreakStyle: TESLLineBreakStyle; override;
    procedure SetLineBreakStyle(Value: TESLLineBreakStyle); override;
    // inherited list methods
    Function GetCapacity: Integer; override;
    // list manipulation methods
    procedure SetArrayLength(NewLen: Integer); override;
    procedure ClearArrayItem(Index: Integer; CanFreeObj: Boolean = True); override;
    // initialization, finalization methods
    procedure Initialize; override;
    // auxiliary methods
    class Function IsBreakChar(C: TESLCharType; IncludeZero: Boolean = True): Boolean; virtual;
    class Function PosOfChar(const Str: TESLStringType; C: TESLCharType): TStrSize; virtual;
    Function ExtractNameStr(const Str: TESLStringType): TESLStringType; virtual;
    Function ExtractValueStr(const Str: TESLStringType): TESLStringType; virtual;
    Function ExtractNameAndValueStr(const Str: TESLStringType; out Name,Value: TESLStringType): Boolean; virtual;
    Function IndexForSortedAddition(const Str: TESLStringType): Integer; virtual;
    Function InternalExtract(Index: Integer): TObject; override;
    Function CompareStrings(const Str1, Str2: TESLStringType): Integer; overload; virtual;
    Function SortCompare(Idx1,Idx2: Integer): Integer; override;
    //Function GetWriteSize: TMemSize; override;
  public
    // utility methods
    class Function ConvertFromString(const Str: String): TESLStringType; virtual;
    class Function ConvertToString(const Str: TESLStringType): String; virtual;
    class Function CompareStrings(const Str1, Str2: TESLStringType; CaseSensitive: Boolean): Integer; overload; virtual;
    // list index methods
    Function LowIndex: Integer; override;      
    // list items methods
    Function IndexOf(const Str: TESLStringType): Integer; virtual;
    Function IndexOfDefString(const Str: String): Integer; override;
    Function IndexOfObject(Obj: TObject): Integer; override;
    Function IndexOfName(const Name: TESLStringType): Integer; virtual;
    Function IndexOfValue(const Value: TESLStringType): Integer; virtual;
    Function Find(const Str: TESLStringType; out Index: Integer): Boolean; virtual;
    Function FindDefString(const Str: String; out Index: Integer): Boolean; override;    
    Function FindObject(Obj: TObject; out Index: Integer): Boolean; override;
    Function FindName(const Name: TESLStringType; out Index: Integer): Boolean; virtual;
    Function FindValue(const Value: TESLStringType; out Index: Integer): Boolean; virtual;
    Function Add(const Str: TESLStringType): Integer; virtual;
    Function AddObject(const Str: TESLStringType; Obj: TObject): Integer; virtual;
    Function AddDefString(const Str: String): Integer; override;
    Function AddDefStringObject(const Str: String; Obj: TObject): Integer; override;
    Function AddNameValuePair(const Name,Value: TESLStringType): Integer; virtual;
    Function AddNameValuePairObject(const Name,Value: TESLStringType; Obj: TObject): Integer; virtual;
    procedure AddStrings(Strings: TESLClassType); overload; virtual;  // note, cannot use actual class
    procedure AddStrings(Strings: array of TESLStringType); overload; virtual;
    procedure Append(const Str: TESLStringType); virtual;
    procedure AppendObject(const Str: TESLStringType; Obj: TObject); virtual;
    procedure AppendDefString(const Str: String); override;
    procedure AppendDefStringObject(const Str: String; Obj: TObject); override;
    procedure AppendNameValuePair(const Name,Value: TESLStringType); virtual;
    procedure AppendNameValuePairObject(const Name,Value: TESLStringType; Obj: TObject); virtual;
    procedure AppendStrings(Strings: TESLClassType); overload; virtual;
    procedure AppendStrings(Strings: array of TESLStringType); overload; virtual;
    procedure Insert(Index: Integer; const Str: TESLStringType); virtual;
    procedure InsertObject(Index: Integer; const Str: TESLStringType; Obj: TObject); virtual;
    procedure InsertDefString(Index: Integer; const Str: String); override;
    procedure InsertDefStringObject(Index: Integer; const Str: String; Obj: TObject); override;
    procedure InsertNameValuePair(Index: Integer; const Name,Value: TESLStringType); virtual;
    procedure InsertNameValuePairObject(Index: Integer; const Name,Value: TESLStringType; Obj: TObject); virtual;
    procedure Move(SrcIdx,DstIdx: Integer); override;
    procedure Exchange(Idx1,Idx2: Integer); override;
    Function Extract(const Str: TESLStringType): TObject; virtual;
    Function ExtractDefString(const Str: String): TObject; override;
    Function ExtractObject(Obj: TObject): TObject; override;
    Function ExtractName(const Name: TESLStringType): TObject; virtual;
    Function ExtractValue(const Value: TESLStringType): TObject; virtual;
    Function Remove(const Str: TESLStringType): Integer; virtual;
    Function RemoveDefString(const Str: String): Integer; override;
    Function RemoveObject(Obj: TObject): Integer; override;
    Function RemoveName(const Name: TESLStringType): Integer; virtual;
    Function RemoveValue(const Value: TESLStringType): Integer; virtual;
    procedure Delete(Index: Integer); override;
    // list manipulation methods
    procedure Sort(Reversed: Boolean = False); override;
    procedure CustomSort(CompareFunc: TESLSortCompareIndexType; Reversed: Boolean = False); overload; virtual;
    procedure CustomSort(CompareFunc: TESLSortCompareStringType; Reversed: Boolean = False); overload; virtual;
    // list data properties
    property Items[Index: Integer]: TESLListItem read GetItem;
    property Strings[Index: Integer]: TESLStringType read GetString write SetString; default;
    property Names[Index: Integer]: TESLStringType read GetName write SetName;
    property Values[const Name: TESLStringType]: TESLStringType read GetValue write SetValue;
    property ValueFromIndex[Index: Integer]: TESLStringType read GetValueFromIndex write SetValueFromIndex;
    // settings properties
    property NameValueSeparator: TESLCharType read fNameValueSeparator write fNameValueSeparator;
    property LineBreak: TESLStringType read fLineBreak write fLineBreak;
    property Delimiter: TESLCharType read fDelimiter write fDelimiter;
    property QuoteChar: TESLCharType read fQuoteChar write fQuoteChar;
{$ENDIF ESL_ClassDeclaration}

{$IFDEF ESL_ClassImplementation}

const
  ESL_DEFVAL_NameValueSeparator = TESLCharType('=');
  ESL_DEFVAL_Delimiter          = TESLCharType(',');
  ESL_DEFVAL_LineBreak          = TESLStringType(sLineBreak);
  ESL_DEFVAL_QuoteChar          = TESLCharType('"');

{-------------------------------------------------------------------------------
    TESLClassType - protected methods
-------------------------------------------------------------------------------}

Function TESLClassType.GetItem(Index: Integer): TESLListItem;
begin
If CheckIndex(Index) then
  Result := fItems[Index]
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetItem: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetString(Index: Integer): TESLStringType;
begin
If CheckIndex(Index) then
  Result := fItems[Index].Str
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetString: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetString(Index: Integer; const Value: TESLStringType);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fItems[Index].Str := Value;
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetString: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetObject(Index: Integer): TObject;
begin
If CheckIndex(Index) then
  Result := fItems[Index].Obj
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetObject: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetObject(Index: Integer; Value: TObject);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    If Assigned(fItems[Index].Obj) and fOwnsObjects then
      FreeAndNil(fItems[Index].Obj);
    fItems[Index].Obj := Value;
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetObject: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetChanged(Index: Integer): Boolean;
begin
If CheckIndex(Index) then
  Result := fItems[Index].Changed
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetChanged: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetChanged(Index: Integer; Value: Boolean);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fItems[Index].Changed := Value;
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetChanged: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetDefString(Index: Integer): String;
begin
If CheckIndex(Index) then
  Result := {$IFNDEF ESL_Default}ConvertToString{$ENDIF}(fItems[Index].Str)
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetDefString: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetDefString(Index: Integer; const Value: String);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fItems[Index].Str := {$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Value);
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetDefString: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetName(Index: Integer): TESLStringType;
begin
If CheckIndex(Index) then
  Result := ExtractNameStr(fItems[Index].Str)
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetName: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetName(Index: Integer; const Value: TESLStringType);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fItems[Index].Str := Value + fNameValueSeparator + ExtractValueStr(fItems[Index].Str);
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetName: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetValue(const Name: TESLStringType): TESLStringType;
var
  Index:  Integer;
begin
If FindName(Name,Index) then
  Result := ExtractValueStr(fItems[Index].Str)
else
  raise EESLUnknownValue.CreateFmt('%s.GetValue: Name "%s" not found.',[Self.ClassName,ConvertToString(Name)]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetValue(const Name: TESLStringType; const Value: TESLStringType);
var
  Index:  Integer;
begin
If FindName(Name,Index) then
  begin
    DoItemChanging(Index);
    fItems[Index].Str := ExtractNameStr(fItems[Index].Str) + fNameValueSeparator + Value;
    DoItemChange(Index);
  end
else raise EESLUnknownValue.CreateFmt('%s.SetValue: Name "%s" not found.',[Self.ClassName,ConvertToString(Name)]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetValueFromIndex(Index: Integer): TESLStringType;
begin
If CheckIndex(Index) then
  Result := ExtractValueStr(fItems[Index].Str)
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetValueFromIndex: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetValueFromIndex(Index: Integer; const Value: TESLStringType);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fItems[Index].Str := ExtractNameStr(fItems[Index].Str) + fNameValueSeparator + Value;
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetValueFromIndex: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetLineBreakStyle: TESLLineBreakStyle;
begin
If CompareStrings(fLineBreak,TESLStringType(#13#10),True) = 0 then
  Result := lbsWIN
else If CompareStrings(fLineBreak,TESLStringType(#10),True) = 0 then
  Result := lbsUNIX
else If CompareStrings(fLineBreak,TESLStringType(#13),True) = 0 then
  Result := lbsMAC
else If CompareStrings(fLineBreak,TESLStringType(#10#13),True) = 0 then
  Result := lbsRISC
else
  Result := lbsUnknown;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetLineBreakStyle(Value: TESLLineBreakStyle);
begin
case Value of
  lbsWIN,lbsCRLF:   fLineBreak := TESLStringType(#13#10);
  lbsUNIX,lbsLF:    fLineBreak := TESLStringType(#10);
  lbsMAC,lbsCR:     fLineBreak := TESLStringType(#13);
  lbsRISC,lbsLFCR:  fLineBreak := TESLStringType(#10#13);
else
  raise EESLInvalidValue.CreateFmt('%s.SetLineBreakStyle: Invalid line-break style (%d).',[Self.ClassName,Ord(Value)]);
end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetCapacity: Integer;
begin
Result := Length(fItems);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetArrayLength(NewLen: Integer);
begin
SetLength(fItems,NewLen);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.ClearArrayItem(Index: Integer; CanFreeObj: Boolean = True);
begin
If Assigned(fItems[Index].Obj) and fOwnsObjects and CanFreeObj then
  FreeAndNil(fItems[Index].Obj)
else
  fItems[Index].Obj := nil;
fItems[Index].Str := '';
fItems[Index].Changed := False;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Initialize;
begin
inherited;
SetLength(fItems,0);
fNameValueSeparator := ESL_DEFVAL_NameValueSeparator;
fDelimiter := ESL_DEFVAL_Delimiter;
fLineBreak := ESL_DEFVAL_LineBreak;
fQuoteChar := ESL_DEFVAL_QuoteChar;
end;

//------------------------------------------------------------------------------

class Function TESLClassType.IsBreakChar(C: TESLCharType; IncludeZero: Boolean = True): Boolean;
begin
If IncludeZero then
  Result := Ord(C) in [0,10,13]
else
  Result := Ord(C) in [10,13];
end;

//------------------------------------------------------------------------------

class Function TESLClassType.PosOfChar(const Str: TESLStringType; C: TESLCharType): TStrSize;
var
  i:  TStrSize;
begin
Result := 0;
For i := 1 to Length(Str) do
  If Str[i] = C then
    begin
      Result := i;
      Break{For i};
    end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.ExtractNameStr(const Str: TESLStringType): TESLStringType;
var
  SeparatorPos: TStrSize;
begin
SeparatorPos := PosOfChar(Str,fNameValueSeparator);
If SeparatorPos > 0 then
  Result := Copy(Str,1,Pred(SeparatorPos))
else
  Result := '';
end;

//------------------------------------------------------------------------------

Function TESLClassType.ExtractValueStr(const Str: TESLStringType): TESLStringType;
var
  SeparatorPos: TStrSize;
begin
SeparatorPos := PosOfChar(Str,fNameValueSeparator);
If SeparatorPos > 0 then
  Result := Copy(Str,Succ(SeparatorPos),Length(Str) - SeparatorPos)
else
  Result := '';
end;

//------------------------------------------------------------------------------

Function TESLClassType.ExtractNameAndValueStr(const Str: TESLStringType; out Name,Value: TESLStringType): Boolean;
var
  SeparatorPos: TStrSize;
begin
SeparatorPos := PosOfChar(Str,fNameValueSeparator);
If SeparatorPos > 0 then
  begin
    Name := Copy(Str,1,Pred(SeparatorPos));
    Value := Copy(Str,Succ(SeparatorPos),Length(Str) - SeparatorPos);
    Result := True;
  end
else Result := False;
end;

//------------------------------------------------------------------------------

Function TESLClassType.IndexForSortedAddition(const Str: TESLStringType): Integer;
var
  M,L,R,D:  Integer;
begin
If fSorted then
  begin
    If fCount > 0 then
      begin
        L := LowIndex;
        R := HighIndex;
        M := L;
        while L <= R do
          begin
            M := (L + R) shr 1;
            D := CompareStrings(Str,fItems[M].Str);
            If D < 0 then
              begin
                R := Pred(M);
                Dec(M);
              end
            else If D > 0 then
              L := Succ(M)
            else
              Break;
          end;
        Result := Succ(M);
      end
    else Result := 0;
  end
else raise EESLInvalidValue.CreateFmt('%s.IndexForSortedAddition: List is not sorted.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.InternalExtract(Index: Integer): TObject;
begin
If CheckIndex(Index) then
  begin
    Result := fItems[Index].Obj;
    fItems[Index].Obj := nil;
    Delete(Index);
  end
else Result := nil;
end;

//------------------------------------------------------------------------------

Function TESLClassType.CompareStrings(const Str1, Str2: TESLStringType): Integer;
begin
Result := CompareStrings(Str1,Str2,fCaseSensitive);
end;

//------------------------------------------------------------------------------

Function TESLClassType.SortCompare(Idx1,Idx2: Integer): Integer;
begin
If Assigned(fCompareFuncIndex) then
  Result := fCompareFuncIndex(Self,Idx1,Idx2)
else If Assigned(fCompareFuncString) then
  Result := fCompareFuncString(Self,fItems[Idx1].Str,fItems[Idx2].Str)
else
  Result := CompareStrings(fItems[Idx1].Str,fItems[Idx2].Str);
end;

//------------------------------------------------------------------------------
(*
Function TESLClassType.GetWriteSize: TMemSize;
begin
{$MESSAGE 'implement'}
end;
*)
{-------------------------------------------------------------------------------
    TESLClassType - public methods
-------------------------------------------------------------------------------}

class Function TESLClassType.ConvertFromString(const Str: String): TESLStringType;
begin
{$IF Defined(ESL_Short)}
  Result := StrRect.StrToShort(Str);
{$ELSEIF Defined(ESL_Ansi)}
  Result := StrRect.StrToAnsi(Str);
{$ELSEIF Defined(ESL_UTF8)}
  Result := StrRect.StrToUTF8(Str);
{$ELSEIF Defined(ESL_Wide)}
  Result := StrRect.StrToWide(Str);
{$ELSEIF Defined(ESL_Unicode)}
  Result := StrRect.StrToUnicode(Str);
{$ELSEIF Defined(ESL_Default)}
  Result := Str;
{$ELSE}
  {$MESSAGE FATAL 'Unknown string type.'}
{$IFEND}
end;

//------------------------------------------------------------------------------

class Function TESLClassType.ConvertToString(const Str: TESLStringType): String;
begin
{$IF Defined(ESL_Short)}
  Result := StrRect.ShortToStr(Str);
{$ELSEIF Defined(ESL_Ansi)}
  Result := StrRect.AnsiToStr(Str);
{$ELSEIF Defined(ESL_UTF8)}
  Result := StrRect.UTF8ToStr(Str);
{$ELSEIF Defined(ESL_Wide)}
  Result := StrRect.WideToStr(Str);
{$ELSEIF Defined(ESL_Unicode)}
  Result := StrRect.UnicodeToStr(Str);
{$ELSEIF Defined(ESL_Default)}
  Result := Str;
{$ELSE}
  {$MESSAGE FATAL 'Unknown string type.'}
{$IFEND}
end;

//------------------------------------------------------------------------------

class Function TESLClassType.CompareStrings(const Str1, Str2: TESLStringType; CaseSensitive: Boolean): Integer;
begin
{$IF Defined(ESL_Short)}
  Result := StrRect.ShortStringCompare(Str1,Str2,CaseSensitive);
{$ELSEIF Defined(ESL_Ansi)}
  Result := StrRect.AnsiStringCompare(Str1,Str2,CaseSensitive);
{$ELSEIF Defined(ESL_UTF8)}
  Result := StrRect.UTF8StringCompare(Str1,Str2,CaseSensitive);
{$ELSEIF Defined(ESL_Wide)}
  Result := StrRect.WideStringCompare(Str1,Str2,CaseSensitive);
{$ELSEIF Defined(ESL_Unicode)}
  Result := StrRect.UnicodeStringCompare(Str1,Str2,CaseSensitive);
{$ELSEIF Defined(ESL_Default)}
  Result := StrRect.StringCompare(Str1,Str2,CaseSensitive);
{$ELSE}
  {$MESSAGE FATAL 'Unknown string type.'}
{$IFEND}
end;

//------------------------------------------------------------------------------

Function TESLClassType.LowIndex: Integer;
begin
Result := Low(fItems);  // should be always 0
end;

//------------------------------------------------------------------------------

Function TESLClassType.IndexOf(const Str: TESLStringType): Integer;
var
  i,L,R,D:  Integer;
begin
Result := -1;
If fSorted and (fCount >= 10) then
  begin
    L := LowIndex;
    R := HighIndex;
    while L <= R do
      begin
        i := (L + R) shr 1;
        D := CompareStrings(Str,fItems[i].Str);
        If D > 0 then
          L := Succ(i)
        else If D < 0 then
          R := Pred(i)
        else
          begin
            Result := i;
            Break{L <= R};
          end;
      end;
  end
else
  begin
    For i := LowIndex to HighIndex do
      If CompareStrings(Str,fItems[i].Str) = 0 then
        begin
          Result := i;
          Break{For i};
        end;
  end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.IndexOfDefString(const Str: String): Integer;
begin
Result := IndexOf({$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Str));
end;

//------------------------------------------------------------------------------

Function TESLClassType.IndexOfObject(Obj: TObject): Integer;
var
  i:  Integer;
begin
Result := -1;
For i := LowIndex to HighIndex do
  If fItems[i].Obj = Obj then
    begin
      Result := i;
      Break{For i};
    end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.IndexOfName(const Name: TESLStringType): Integer;
var
  i:  Integer;
begin
Result := -1;
For i := LowIndex to HighIndex do
  If CompareStrings(Name,ExtractNameStr(fItems[i].Str)) = 0 then
    begin
      Result := i;
      Break{For i};
    end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.IndexOfValue(const Value: TESLStringType): Integer;
var
  i:  Integer;
begin
Result := -1;
For i := LowIndex to HighIndex do
  If CompareStrings(Value,ExtractValueStr(fItems[i].Str)) = 0 then
    begin
      Result := i;
      Break{For i};
    end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.Find(const Str: TESLStringType; out Index: Integer): Boolean;
begin
Index := IndexOf(Str);
Result := CheckIndex(Index);
end;

//------------------------------------------------------------------------------

Function TESLClassType.FindDefString(const Str: String; out Index: Integer): Boolean;
begin
Index := IndexOfDefString(Str);
Result := CheckIndex(Index);
end;

//------------------------------------------------------------------------------

Function TESLClassType.FindObject(Obj: TObject; out Index: Integer): Boolean;
begin
Index := IndexOfObject(Obj);
Result := CheckIndex(Index);
end;

//------------------------------------------------------------------------------

Function TESLClassType.FindName(const Name: TESLStringType; out Index: Integer): Boolean;
begin
Index := IndexOfName(Name);
Result := CheckIndex(Index);
end; 

//------------------------------------------------------------------------------

Function TESLClassType.FindValue(const Value: TESLStringType; out Index: Integer): Boolean;
begin
Index := IndexOfValue(Value);
Result := CheckIndex(Index);
end;

//------------------------------------------------------------------------------

Function TESLClassType.Add(const Str: TESLStringType): Integer;
begin
Result := AddObject(Str,nil);
end;

//------------------------------------------------------------------------------

Function TESLClassType.AddObject(const Str: TESLStringType; Obj: TObject): Integer;
var
  i:  Integer;
begin
If fDuplicates <> dupAccept then
  If Find(Str,Result) then
    case fDuplicates of
      dupIgnore:  begin
                    Result := -1;
                    Exit;
                  end;
      dupError:   raise EESLDuplicitValue.CreateFmt('%s.AddObject: Duplicit string.',[Self.ClassName]);
    end;
Grow;
DoListChanging;
If fSorted then
  begin
    Result := IndexForSortedAddition(Str);
    For i := HighIndex downto Result do
      fItems[i + 1] := fItems[i];
  end
else Result := fCount;
fItems[Result].Str := Str;
fItems[Result].Obj := Obj;
Inc(fCount);
DoListChange;
end;

//------------------------------------------------------------------------------

Function TESLClassType.AddDefString(const Str: String): Integer;
begin
Result := AddDefStringObject(Str,nil);
end;

//------------------------------------------------------------------------------

Function TESLClassType.AddDefStringObject(const Str: String; Obj: TObject): Integer;
begin
Result := AddObject({$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Str),Obj);
end;

//------------------------------------------------------------------------------

Function TESLClassType.AddNameValuePair(const Name,Value: TESLStringType): Integer;
begin
Result := AddNameValuePairObject(Name,Value,nil);
end;

//------------------------------------------------------------------------------

Function TESLClassType.AddNameValuePairObject(const Name,Value: TESLStringType; Obj: TObject): Integer;
begin
Result := AddObject(Name + fNameValueSeparator + Value,Obj);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AddStrings(Strings: TESLClassType);
var
  i:  Integer;
begin
BeginUpdate;
try
  Grow(Strings.Count);
  For i := 0 to Pred(Strings.Count) do
    AddObject(Strings[i],Strings.Objects[i]);
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AddStrings(Strings: array of TESLStringType);
var
  i:  Integer;
begin
BeginUpdate;
try
  Grow(Length(Strings));
  For i := Low(Strings) to High(Strings) do
    Add(Strings[i]);
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Append(const Str: TESLStringType);
begin
AppendObject(Str,nil);
end;  

//------------------------------------------------------------------------------

procedure TESLClassType.AppendObject(const Str: TESLStringType; Obj: TObject);
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    AddObject(Str,Obj);
  end
else raise EESLSortedList.CreateFmt('%s.AppendObject: Cannot append to sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AppendDefString(const Str: String);
begin
AppendDefStringObject(Str,nil);
end; 

//------------------------------------------------------------------------------

procedure TESLClassType.AppendDefStringObject(const Str: String; Obj: TObject);
begin
AppendObject({$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Str),Obj);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AppendNameValuePair(const Name,Value: TESLStringType);
begin
AppendNameValuePairObject(Name,Value,nil);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AppendNameValuePairObject(const Name,Value: TESLStringType; Obj: TObject);
begin
AppendObject(Name + fNameValueSeparator + Value,Obj);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AppendStrings(Strings: TESLClassType);
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    AddStrings(Strings);
  end
else raise EESLSortedList.CreateFmt('%s.AppendStrings: Cannot append to sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AppendStrings(Strings: array of TESLStringType);
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    AddStrings(Strings);
  end
else raise EESLSortedList.CreateFmt('%s.AppendStrings: Cannot append to sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Insert(Index: Integer; const Str: TESLStringType);
begin
InsertObject(Index,Str,nil);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.InsertObject(Index: Integer; const Str: TESLStringType; Obj: TObject);
var
  i:  Integer;
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    If CheckIndex(Index) then
      begin
        If fDuplicates <> dupAccept then
          If Find(Str,i) then
            case fDuplicates of
              dupIgnore:  Exit;
              dupError:   raise EESLDuplicitValue.CreateFmt('%s.InsertObject: Duplicit string.',[Self.ClassName]);
            end;
        Grow;
        DoListChanging;
        For i := HighIndex downto Index do
          fItems[i + 1] := fItems[i];
        fItems[Index].Str := Str;
        fItems[Index].Obj := Obj;
        Inc(fCount);
        DoListChange;
      end
    else If Index = fCount then
      AddObject(Str,Obj)
    else
      raise EESLIndexOutOfBounds.CreateFmt('%s.InsertObject: Index (%d) out of bounds.',[Self.ClassName,Index]);
  end
else raise EESLSortedList.CreateFmt('%s.InsertObject: Cannot insert to sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.InsertDefString(Index: Integer; const Str: String);
begin
InsertDefStringObject(Index,Str,nil);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.InsertDefStringObject(Index: Integer; const Str: String; Obj: TObject);
begin
InsertObject(Index,{$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Str),Obj);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.InsertNameValuePair(Index: Integer; const Name,Value: TESLStringType);
begin
InsertNameValuePairObject(Index,Name,Value,nil);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.InsertNameValuePairObject(Index: Integer; const Name,Value: TESLStringType; Obj: TObject);
begin
InsertObject(Index,Name + fNameValueSeparator + Value,Obj);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Move(SrcIdx,DstIdx: Integer);
var
  i:    Integer;
  Temp: TESLListItem;
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    If SrcIdx <> DstIdx then
      begin
        If not CheckIndex(SrcIdx) then
          raise EESLIndexOutOfBounds.CreateFmt('%s.Move: Source index (%d) out of bounds.',[Self.ClassName,SrcIdx]);
        If not CheckIndex(DstIdx) then
          raise EESLIndexOutOfBounds.CreateFmt('%s.Move: Destination index (%d) out of bounds.',[Self.ClassName,DstIdx]);
        DoListChanging;
        Temp := fItems[SrcIdx];
        If SrcIdx > DstIdx then
          For i := SrcIdx downto Succ(DstIdx) do
            fItems[i] := fItems[i - 1]
        else
          For i := SrcIdx to Pred(DstIdx) do
            fItems[i] := fItems[i + 1];
        fItems[DstIdx] := Temp;
        DoListChange;
      end;
  end
else raise EESLSortedList.CreateFmt('%s.Move: Cannot move items in sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Exchange(Idx1,Idx2: Integer);
var
  Temp: TESLListItem;
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    If Idx1 <> Idx2 then
      begin
        If not CheckIndex(Idx1) then
          raise EESLIndexOutOfBounds.CreateFmt('%s.Exchange: Index #1 (%d) out of bounds.',[Self.ClassName,Idx1]);
        If not CheckIndex(Idx2) then
          raise EESLIndexOutOfBounds.CreateFmt('%s.Exchange: Index #2 (%d) out of bounds.',[Self.ClassName,Idx2]);
        DoListChanging;
        Temp := fItems[Idx1];
        fItems[Idx1] := fItems[Idx2];
        fItems[Idx2] := Temp;
        DoListChange;
      end;
  end
else raise EESLSortedList.CreateFmt('%s.Exchange: Cannot exchange items in sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.Extract(const Str: TESLStringType): TObject;
begin
Result := InternalExtract(IndexOf(Str));
end;

//------------------------------------------------------------------------------

Function TESLClassType.ExtractDefString(const Str: String): TObject;
begin
Result := InternalExtract(IndexOfDefString(Str));
end;

//------------------------------------------------------------------------------

Function TESLClassType.ExtractObject(Obj: TObject): TObject;
begin
Result := InternalExtract(IndexOfObject(Obj));
end;

//------------------------------------------------------------------------------

Function TESLClassType.ExtractName(const Name: TESLStringType): TObject;
begin
Result := InternalExtract(IndexOfName(Name));
end;

//------------------------------------------------------------------------------

Function TESLClassType.ExtractValue(const Value: TESLStringType): TObject;
begin
Result := InternalExtract(IndexOfValue(Value));
end;

//------------------------------------------------------------------------------

Function TESLClassType.Remove(const Str: TESLStringType): Integer;
begin
If Find(Str,Result) then
  Delete(Result);
end;

//------------------------------------------------------------------------------

Function TESLClassType.RemoveDefString(const Str: String): Integer;
begin
If FindDefString(Str,Result) then
  Delete(Result);
end; 

//------------------------------------------------------------------------------

Function TESLClassType.RemoveObject(Obj: TObject): Integer;
begin
If FindObject(Obj,Result) then
  Delete(Result);
end; 

//------------------------------------------------------------------------------

Function TESLClassType.RemoveName(const Name: TESLStringType): Integer;
begin
If FindName(Name,Result) then
  Delete(Result);
end; 

//------------------------------------------------------------------------------

Function TESLClassType.RemoveValue(const Value: TESLStringType): Integer;
begin
If FindValue(Value,Result) then
  Delete(Result);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Delete(Index: Integer);
var
  i:  Integer;
begin
If CheckIndex(Index) then
  begin
    DoListChanging;
    ClearArrayItem(Index);
    For i := Index to Pred(HighIndex) do
      fItems[i] := fItems[i + 1];
    ClearArrayItem(HighIndex,False);
    Dec(fCount);
    Shrink;
    DoListChange;
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.Delete: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Sort(Reversed: Boolean = False);
begin
fCompareFuncIndex := nil;
fCompareFuncString := nil;
SortItems(Reversed);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.CustomSort(CompareFunc: TESLSortCompareIndexType; Reversed: Boolean = False);
begin
fCompareFuncIndex := CompareFunc;
fCompareFuncString := nil;
SortItems(Reversed);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.CustomSort(CompareFunc: TESLSortCompareStringType; Reversed: Boolean = False);
begin
fCompareFuncIndex := nil;
fCompareFuncString := CompareFunc;
SortItems(Reversed);
end;

{$ENDIF ESL_ClassImplementation}

