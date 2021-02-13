{$IFDEF ESL_ClassAuxiliary}

const
  ESL_DEFVAL_Delimiter = TESLCharType(',');
  ESL_DEFVAL_LineBreak = TESLStringType(sLineBreak);
  ESL_DEFVAL_QuoteChar = TESLCharType('"');

{$ENDIF ESL_ClassAuxiliary}

{$IFDEF ESL_ClassDeclaration}
  private
    fStrings:   array of TESLStringType;
    fDelimiter: TESLCharType;
    fLineBreak: TESLStringType;
    fQuoteChar: TESLCharType;
    // getters, setters
    Function GetItem(Index: Integer): TESLStringType;
    procedure SetItem(Index: Integer; const Value: TESLStringType);
  protected
    // protected getters and setters
    Function GetString(Index: Integer): String; override;
    procedure SetString(Index: Integer; const Value: String); override;
    Function GetLineBreakStyle: TESLLineBreakStyle; override;
    procedure SetLineBreakStyle(Value: TESLLineBreakStyle); override;
    // list manipulation
    procedure SetArraysLength(NewLen: Integer); override;
    procedure ClearArrayItem(Index: Integer); override;
    // initialization
    procedure Initialize; override;
    // auxiliary methods
    class Function IsBreak(C: TESLCharType; IncludeZero: Boolean = True): Boolean; virtual;
    class Function ConvertFromString(const Str: String): TESLStringType; virtual;
    class Function ConvertToString(const Str: TESLStringType): String; virtual;
    class Function CompareStrings(const Str1, Str2: TESLStringType; CaseSensitive: Boolean): Integer; overload; virtual;
    Function CompareStrings(const Str1, Str2: TESLStringType): Integer; overload; virtual;
    Function CompareItems(Idx1,Idx2: Integer): Integer; override;
    Function GetWriteSize: TMemSize; override;
  public
    property Items[Index: Integer]: TESLStringType read GetItem write SetItem; default;
    property Delimiter: TESLCharType read fDelimiter write fDelimiter;
    property LineBreak: TESLStringType read fLineBreak write fLineBreak;
    property QuoteChar: TESLCharType read fQuoteChar write fQuoteChar;
{$ENDIF ESL_ClassDeclaration}

{$IFDEF ESL_ClassImplementation}

{-------------------------------------------------------------------------------
    TESLClassType - private methods
-------------------------------------------------------------------------------}

Function TESLClassType.GetItem(Index: Integer): TESLStringType;
begin
If CheckIndex(Index) then
  Result := fStrings[Index]
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetItem: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetItem(Index: Integer; const Value: TESLStringType);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fStrings[Index] := Value;
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetItem: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

{-------------------------------------------------------------------------------
    TESLClassType - protected methods
-------------------------------------------------------------------------------}

Function TESLClassType.GetString(Index: Integer): String;
begin
If CheckIndex(Index) then
  Result := ConvertToString(fStrings[Index])
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.GetString: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetString(Index: Integer; const Value: String);
begin
If CheckIndex(Index) then
  begin
    DoItemChanging(Index);
    fStrings[Index] := ConvertFromString(Value);
    DoItemChange(Index);
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.SetString: Index (%d) out of bounds.',[Self.ClassName,Index]);
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

procedure TESLClassType.SetArraysLength(NewLen: Integer);
begin
inherited;
SetLength(fStrings,NewLen);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.ClearArrayItem(Index: Integer);
begin
inherited;
fStrings[Index] := '';
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Initialize;
begin
SetLength(fStrings,0);
fDelimiter := ESL_DEFVAL_Delimiter;
fLineBreak := ESL_DEFVAL_LineBreak;
fQuoteChar := ESL_DEFVAL_QuoteChar;
inherited;
end;

//------------------------------------------------------------------------------

class Function TESLClassType.IsBreak(C: TESLCharType; IncludeZero: Boolean = True): Boolean;
begin
If IncludeZero then
  Result := Ord(C) in [0,10,13]
else
  Result := Ord(C) in [10,13];
end;

//------------------------------------------------------------------------------

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
  {$MESSAGE FATAL 'Invalid string type.'}
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
  {$MESSAGE FATAL 'Invalid string type.'}
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
  {$MESSAGE FATAL 'Invalid string type.'}
{$IFEND}
end;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Function TESLClassType.CompareStrings(const Str1, Str2: TESLStringType): Integer;
begin
Result := CompareStrings(Str1,Str2,fCaseSensitive);
end;

//------------------------------------------------------------------------------

Function TESLClassType.CompareItems(Idx1,Idx2: Integer): Integer;
begin
Result := CompareStrings(fStrings[Idx1],fStrings[Idx2]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetWriteSize: TMemSize;
begin
end;

{-------------------------------------------------------------------------------
    TESLClassType - public methods
-------------------------------------------------------------------------------}

{$ENDIF ESL_ClassImplementation}

