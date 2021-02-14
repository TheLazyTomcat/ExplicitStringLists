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
    //fDelimiter: TESLCharType;
    //fLineBreak: TESLStringType;
    //fQuoteChar: TESLCharType;
    // custom sorting
    fCompareFuncIndex:    TESLSortCompareIndexType;
    fCompareFuncString:   TESLSortCompareStringType;
    // getters, setters
    Function GetItem(Index: Integer): TESLStringType; virtual;
    procedure SetItem(Index: Integer; const Value: TESLStringType); virtual;
    Function GetObject(Index: Integer): TObject; override;
    procedure SetObject(Index: Integer; Value: TObject); override;
    Function GetChanged(Index: Integer): Boolean; override;
    procedure SetChanged(Index: Integer; Value: Boolean); override;
    Function GetString(Index: Integer): String; override;
    procedure SetString(Index: Integer; const Value: String); override;
    //Function GetLineBreakStyle: TESLLineBreakStyle; override;
    //procedure SetLineBreakStyle(Value: TESLLineBreakStyle); override;
    // inherited list methods
    Function GetCapacity: Integer; override;
    // list manipulation methods
    procedure SetArrayLength(NewLen: Integer); override;
    procedure ClearArrayItem(Index: Integer; CanFreeObj: Boolean = True); override;
    // initialization, finalization methods
    procedure Initialize; override;
    // auxiliary methods
    //class Function IsBreak(C: TESLCharType; IncludeZero: Boolean = True): Boolean; virtual;
    class Function PosOfChar(const Str: TESLStringType; C: TESLCharType): TStrSize; virtual;
    Function ExtractName(const Str: TESLStringType): TESLStringType; virtual;
    Function ExtractValue(const Str: TESLStringType): TESLStringType; virtual;
    Function ExtractNameAndValue(const Str: TESLStringType; out Name,Value: TESLStringType): Boolean; virtual;
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
    Function IndexOfObject(Obj: TObject): Integer; override;
    Function IndexOfString(const Str: String): Integer; override;
    Function IndexOfName(const Name: TESLStringType): Integer; virtual;
    Function IndexOfValue(const Value: TESLStringType): Integer; virtual;
    Function Find(const Str: TESLStringType; out Index: Integer): Boolean; virtual;
    Function FindObject(Obj: TObject; out Index: Integer): Boolean; override;
    Function FindString(const Str: String; out Index: Integer): Boolean; override;
    Function FindName(const Name: TESLStringType; out Index: Integer): Boolean; virtual;
    Function FindValue(const Value: TESLStringType; out Index: Integer): Boolean; virtual;

    //Function Add(const Str: TESLStringType): Integer; virtual;
    //Function AddObject(const Str: TESLStringType; Obj: TObject): Integer; virtual;
    //Function AddString(const Str: String): Integer; override;
    //Function AddStringObject(const Str: String; Obj: TObject): Integer; override;
    //Function AddNamedValue(const Name,Value: String): Integer; virtual;
    //Function AddNamedValueObject(const Name,Value: String; Obj: TObject): Integer; virtual;

    procedure Delete(Index: Integer); override;
    // list manipulation methods
    procedure Sort(Reversed: Boolean = False); override;
    procedure CustomSort(CompareFunc: TESLSortCompareIndexType; Reversed: Boolean = False); overload; virtual;
    procedure CustomSort(CompareFunc: TESLSortCompareStringType; Reversed: Boolean = False); overload; virtual;
    // list data properties
    property Items[Index: Integer]: TESLStringType read GetItem write SetItem; default;
  //property Names[Index: Integer]: TESLStringType read GetName write SetName;
  //property Values[const Name: TESLStringType]: TESLStringType read GetValue write SetValue;
  //property ValueFromIndex[Index: Integer]: TESLStringType read GetValueFromIndex write SetValueFromIndex;
    // settings properties
    property NameValueSeparator: TESLCharType read fNameValueSeparator write fNameValueSeparator;
    //property Delimiter: TESLCharType read fDelimiter write fDelimiter;
    //property LineBreak: TESLStringType read fLineBreak write fLineBreak;
    //property QuoteChar: TESLCharType read fQuoteChar write fQuoteChar;
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

Function TESLClassType.GetItem(Index: Integer): TESLStringType;
begin
If CheckIndex(Index) then
  Result := fItems[Index].Str
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetItem: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetItem(Index: Integer; const Value: TESLStringType);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fItems[Index].Str := Value;
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetItem: Index (%d) out of bounds.',[Self.ClassName,Index]);
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

Function TESLClassType.GetString(Index: Integer): String;
begin
If CheckIndex(Index) then
  Result := {$IFNDEF ESL_Default}ConvertToString{$ENDIF}(fItems[Index].Str)
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetString: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetString(Index: Integer; const Value: String);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fItems[Index].Str := {$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Value);
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetString: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------
(*
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
*)
//------------------------------------------------------------------------------
(*
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
*)

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
//fDelimiter := ESL_DEFVAL_Delimiter;
//fLineBreak := ESL_DEFVAL_LineBreak;
//fQuoteChar := ESL_DEFVAL_QuoteChar;
end;

//------------------------------------------------------------------------------
(*
class Function TESLClassType.IsBreak(C: TESLCharType; IncludeZero: Boolean = True): Boolean;
begin
If IncludeZero then
  Result := Ord(C) in [0,10,13]
else
  Result := Ord(C) in [10,13];
end;
*)

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

Function TESLClassType.ExtractName(const Str: TESLStringType): TESLStringType;
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

Function TESLClassType.ExtractValue(const Str: TESLStringType): TESLStringType;
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

Function TESLClassType.ExtractNameAndValue(const Str: TESLStringType; out Name,Value: TESLStringType): Boolean;
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
          L := i + 1
        else If D < 0 then
          R := i - 1
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

Function TESLClassType.IndexOfString(const Str: String): Integer;
begin
Result := IndexOf({$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Str));
end;

//------------------------------------------------------------------------------

Function TESLClassType.IndexOfName(const Name: TESLStringType): Integer;
var
  i:  Integer;
begin
Result := -1;
For i := LowIndex to HighIndex do
  If CompareStrings(Name,ExtractName(fItems[i].Str)) = 0 then
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
  If CompareStrings(Value,ExtractValue(fItems[i].Str)) = 0 then
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

Function TESLClassType.FindObject(Obj: TObject; out Index: Integer): Boolean;
begin
Index := IndexOfObject(Obj);
Result := CheckIndex(Index);
end;  

//------------------------------------------------------------------------------

Function TESLClassType.FindString(const Str: String; out Index: Integer): Boolean;
begin
Index := IndexOfString(Str);
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

