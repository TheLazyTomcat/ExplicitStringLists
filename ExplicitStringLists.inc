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
    Function GetLongStrText: TESLLongStringType; virtual;
    procedure SetLongStrText(const Value: TESLLongStringType); virtual;
    Function GetLongDelimitedText: TESLLongStringType; virtual;
    procedure SetLongDelimitedText(const Value: TESLLongStringType); virtual;
    Function GetLongCommaText: TESLLongStringType; virtual;
    procedure SetLongCommaText(const Value: TESLLongStringType); virtual;
    Function GetStrText: TESLStringType; virtual;
    procedure SetStrText(const Value: TESLStringType); virtual;
    Function GetDelimitedText: TESLStringType; virtual;
    procedure SetDelimitedText(const Value: TESLStringType); virtual;
    Function GetCommaText: TESLStringType; virtual;
    procedure SetCommaText(const Value: TESLStringType); virtual;
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
    Function CompareStrings(const Str1, Str2: TESLStringType): Integer; overload; virtual;
    Function SortCompare(Idx1,Idx2: Integer): Integer; override;
    Function GetWriteLength: TStrSize; override;
    procedure WriteItemToStream(Stream: TStream; Index: Integer; Endianness: TESLStringEndianness); override;
    procedure WriteLineBreakToStream(Stream: TStream; Endianness: TESLStringEndianness); override;
    procedure WriteBOMToStream(Stream: TStream; Endianness: TESLStringEndianness); override;
    class Function StrBufferSize(Buffer: Pointer): TMemSize; override;
    class Function CharSize: TMemSize; override;
    // internal methods
    Function InternalExtract(Index: Integer): TObject; override;        
  public
    // utility methods
    class Function ConvertFromString(const Str: String): TESLStringType; virtual;
    class Function ConvertToString(const Str: TESLStringType): String; virtual;
    class Function CompareStrings(const Str1, Str2: TESLStringType; CaseSensitive: Boolean): Integer; overload; virtual;
    // list index methods
    Function LowIndex: Integer; override;
    Function First: TESLStringType; virtual;
    Function Last: TESLStringType; virtual;
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
    Function Equals(Strings: TESLClassType): Boolean; reintroduce; virtual;
    // list assignment methods
    procedure SetStrings(Strings: TESLClassType); overload; virtual;
    procedure SetStrings(Strings: array of TESLStringType); overload; virtual;
    procedure SetDefStrings(Strings: TStrings); override;
    procedure SetDefStrings(Strings: array of String); override;
    procedure Assign(Source: TESLClassType); overload; virtual;
    procedure Assign(Source: TStrings); override;
    procedure AssignTo(Destination: TESLClassType); overload; virtual;
    procedure AssignTo(Destination: TStrings); override;
    // streaming methods
    procedure LoadFromStream(Stream: TStream; out Endianness: TESLStringEndianness); override;
    procedure BinarySaveToStream(Stream: TStream); override;
    procedure BinaryLoadFromStream(Stream: TStream); override;
    // other methods
    Function GetText(out Size: TMemSize): TESLPCharType; overload; virtual;
    Function GetText: TESLPCharType; overload; virtual;
    procedure SetText(Text: TESLPCharType; Size: TMemSize); overload; virtual;
    procedure SetText(Text: TESLPCharType); overload; virtual;
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
  {
    Long*Text and *Text are returning the same strings in most cases, only for
    short-string lists they are returning different type and possibly also
    string (one which is not limited in length).
    It is here because one might want text of short-string list without it
    being limited to 255 characters (max. length of short string).
    Note that returned short strings are only truncated from full length, they
    are not build separately, so there might be missing closing quotes and
    other problems. You have been warned.
  }
    property LongText: TESLLongStringType read GetLongStrText write SetLongStrText;
    property LongDelimitedText: TESLLongStringType read GetLongDelimitedText write SetLongDelimitedText;
    property LongCommaText: TESLLongStringType read GetLongCommaText write SetLongCommaText;
    property Text: TESLStringType read GetStrText write SetStrText;
    property DelimitedText: TESLStringType read GetDelimitedText write SetDelimitedText;
    property CommaText: TESLStringType read GetCommaText write SetCommaText;

{$ENDIF ESL_ClassDeclaration}

{$IFDEF ESL_ClassImplementation}

{$IF Defined(ESL_Short) or (Defined(ESL_Default) and Defined(ESL_DEFAULT_Short)))}
  {$DEFINE ESL_LOCAL_Short}
{$IFEND}

{$IF Defined(ESL_Wide) or Defined(ESL_Unicode) or (Defined(ESL_Default) and Defined(ESL_DEFAULT_Unicode))}
  {$DEFINE ESL_LOCAL_Wide}
{$IFEND}

const
  ESL_DEFVAL_NameValueSeparator = TESLCharType('=');
  ESL_DEFVAL_Delimiter          = TESLCharType(',');
  ESL_DEFVAL_LineBreak          = TESLStringType(sLineBreak);
  ESL_DEFVAL_QuoteChar          = TESLCharType('"');

type
  TStringsFeaturesChecker = class(Classes.TStrings)
  protected
    procedure FeatureChecks; virtual;
  end;
  
type
  TStringListFeaturesChecker = class(Classes.TStringList)
  protected
    procedure FeatureChecks; virtual;
  end;

procedure TStringsFeaturesChecker.FeatureChecks;
begin
{$IF Declared(LineBreak)}         {$DEFINE ESL_STRINGS_LineBreak}         {$IFEND}
{$IF Declared(TrailingLineBreak)} {$DEFINE ESL_STRINGS_TrailingLineBreak} {$IFEND}
{$IF Declared(NameValueSeparator)}{$DEFINE ESL_STRINGS_NameValueSeparator}{$IFEND}
{$IF Declared(Delimiter)}         {$DEFINE ESL_STRINGS_Delimiter}         {$IFEND}
{$IF Declared(StrictDelimiter)}   {$DEFINE ESL_STRINGS_StrictDelimiter}   {$IFEND}
{$IF Declared(QuoteChar)}         {$DEFINE ESL_STRINGS_QuoteChar}         {$IFEND}
raise Exception.Create('TStringsFeaturesChecker.FeatureChecks: This method is not supposed to be called.');
end;

procedure TStringListFeaturesChecker.FeatureChecks;
begin
{$IF Declared(OwnsObjects)}  {$DEFINE ESL_STRINGLIST_OwnsObjects}  {$IFEND}
{$IF Declared(CaseSensitive)}{$DEFINE ESL_STRINGLIST_CaseSensitive}{$IFEND}
{$IF Declared(Duplicates)}   {$DEFINE ESL_STRINGLIST_Duplicates}   {$IFEND}
{$IF Declared(Sorted)}       {$DEFINE ESL_STRINGLIST_Sorted}       {$IFEND}
raise Exception.Create('TStringListFeaturesChecker.FeatureChecks: This method is not supposed to be called.');
end;

type
  TESLDelimitedTextParserEvent = procedure(const Str: TESLStringType) of object;

type
  TESLDelimitedTextParser = class(TESLDelimitedTextParserBase)
  protected
    fDelimiter:       TESLCharType;
    fQuoteChar:       TESLCharType;
    fStrictDelimiter: Boolean;
    fOnNewString:     TESLDelimitedTextParserEvent;
    // parsing vars
    fParsedString:    TESLLongStringType;
    Function RemoveDoubleQuotes(const Str: TESLLongStringType): TESLLongStringType; virtual;
    Function LookAhead(IsChar: TESLCharType): Boolean; virtual;
    Function CurrCharType: TESLDelimitedTextParserCharType; virtual;
    procedure DoNewString(const Str: TESLLongStringType); virtual;
    procedure Parse; override;
    procedure Parse_Initial; override;
    procedure Parse_WhiteSpace; override;
    procedure Parse_Delimiter; override;
    procedure Parse_NormalText; override;
    procedure Parse_QuotedText; override;
  public
    constructor Create(Delimiter,QuoteChar: TESLCharType; StrictDelimiter: Boolean);
    procedure Parse(const Text: TESLLongStringType); overload; virtual;
    property OnNewString: TESLDelimitedTextParserEvent read fOnNewString write fOnNewString;
  end;

{-------------------------------------------------------------------------------
    TESLDelimitedTextParserSpec - protected methods
-------------------------------------------------------------------------------}

Function TESLDelimitedTextParser.RemoveDoubleQuotes(const Str: TESLLongStringType): TESLLongStringType;
var
  i,ResPos: TStrSize;
  LastChar: TESLCharType;
begin
If Length(Str) > 0 then
  begin
    SetLength(Result,Length(Str));
    ResPos := 1;
    LastChar := TESLCharType(not Ord(fQuoteChar));
    For i := 1 to Length(Str) do
      If not((Str[i] = fQuoteChar) and (LastChar = fQuoteChar)) then
        begin
          Result[ResPos] := Str[i];
          Inc(ResPos);
          LastChar := Str[i];
        end
      else LastChar := TESLCharType(not Ord(fQuoteChar));
    SetLength(Result,ResPos - 1);
  end
else Result := '';
end;

//------------------------------------------------------------------------------

Function TESLDelimitedTextParser.LookAhead(IsChar: TESLCharType): Boolean;
begin
If (fPosition >= 1) and (fPosition < Length(fParsedString)) then
  Result := fParsedString[fPosition + 1] = IsChar
else
  Result := False;
end;

//------------------------------------------------------------------------------

Function TESLDelimitedTextParser.CurrCharType: TESLDelimitedTextParserCharType;
begin
If Ord(fParsedString[fPosition]) in [0..32] then
  Result := dtpcWhiteSpace
else If fParsedString[fPosition] = fDelimiter then
  Result := dtpcDelimiter
else If fParsedString[fPosition] = fQuoteChar then
  Result := dtpcQuoteChar
else
  Result := dtpcGeneral;
end;

//------------------------------------------------------------------------------

procedure TESLDelimitedTextParser.DoNewString(const Str: TESLLongStringType);
begin
If Assigned(fOnNewString) then
  fOnNewString({$IFDEF ESL_LOCAL_Short}TESLStringType{$ENDIF}(Str));
end;

//------------------------------------------------------------------------------

procedure TESLDelimitedTextParser.Parse;
begin
fParserState := dtpsInitial;
fPosition := 0;
while fPosition <= Length(fParsedString) do
  inherited Parse;
case fParserState of
  dtpsDelimiter:  DoNewString('');
  dtpsNormalText: DoNewString(Copy(fParsedString,fItemStart,fItemLength));
  dtpsQuotedText: DoNewString(RemoveDoubleQuotes(Copy(fParsedString,fItemStart,fItemLength)));
end;
end;

//------------------------------------------------------------------------------

procedure TESLDelimitedTextParser.Parse_Initial;
begin
fParserState := dtpsDelimiter;
fPosition := 0;
fItemStart := 0;
fItemLength := 0;
end;

//------------------------------------------------------------------------------

procedure TESLDelimitedTextParser.Parse_WhiteSpace;
begin
case CurrCharType of
  dtpcWhiteSpace:;// ignore
  dtpcDelimiter:  fParserState := dtpsDelimiter;
  dtpcQuoteChar:  If not fStrictDelimiter then
                    begin
                      fItemStart := fPosition + 1;
                      fItemLength := 0;
                      fParserState := dtpsQuotedText;
                    end;
  dtpcGeneral:    If not fStrictDelimiter then
                    begin
                      fItemStart := fPosition;
                      fItemLength := 1;
                      fParserState := dtpsNormalText;
                    end;  
end;
end;

//------------------------------------------------------------------------------

procedure TESLDelimitedTextParser.Parse_Delimiter;
begin
case CurrCharType of
  dtpcWhiteSpace: If fStrictDelimiter then
                    begin
                      fItemStart := fPosition;
                      fItemLength := 1;
                      fParserState := dtpsNormalText;
                    end;
  dtpcDelimiter:  DoNewString('');
  dtpcQuoteChar:  begin
                    fItemStart := fPosition + 1;
                    fItemLength := 0;
                    fParserState := dtpsQuotedText;
                  end;
  dtpcGeneral:    begin
                    fItemStart := fPosition;
                    fItemLength := 1;
                    fParserState := dtpsNormalText;
                  end;
end;
end;

//------------------------------------------------------------------------------

procedure TESLDelimitedTextParser.Parse_NormalText;
begin
case CurrCharType of
  dtpcWhiteSpace: If not fStrictDelimiter then
                    begin
                      DoNewString(Copy(fParsedString,fItemStart,fItemLength));
                      fParserState := dtpsWhiteSpace;
                    end
                  else Inc(fItemLength);
  dtpcDelimiter:  begin
                    DoNewString(Copy(fParsedString,fItemStart,fItemLength));
                    fParserState := dtpsDelimiter;
                  end;
  dtpcQuoteChar,
  dtpcGeneral:    Inc(fItemLength);
end;
end;

//------------------------------------------------------------------------------

procedure TESLDelimitedTextParser.Parse_QuotedText;
begin
If CurrCharType = dtpcQuoteChar then
  begin
    If LookAhead(fQuoteChar) then
      begin
        Inc(fPosition);
        Inc(fItemLength,2);
      end
    else
      begin
        DoNewString(RemoveDoubleQuotes(Copy(fParsedString,fItemStart,fItemLength)));
        fParserState := dtpsWhiteSpace;
      end;
  end
else Inc(fItemLength);
end;

{-------------------------------------------------------------------------------
    TESLDelimitedTextParserSpec - public methods
-------------------------------------------------------------------------------}

constructor TESLDelimitedTextParser.Create(Delimiter,QuoteChar: TESLCharType; StrictDelimiter: Boolean);
begin
inherited Create;
fDelimiter := Delimiter;
fQuoteChar := QuoteChar;
fStrictDelimiter := StrictDelimiter;
end;

//------------------------------------------------------------------------------

procedure TESLDelimitedTextParser.Parse(const Text: TESLLongStringType);
begin
fParsedString := Text;
Parse;
end;

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
  fItems[Index].Changed := Value
else
  raise EESLIndexOutOfBounds.CreateFmt('%s.SetChanged: Index (%d) out of bounds.',[Self.ClassName,Index]);
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
    fItems[Index].Str := Value + TESLStringType(fNameValueSeparator) + ExtractValueStr(fItems[Index].Str);
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
    fItems[Index].Str := ExtractNameStr(fItems[Index].Str) + TESLStringType(fNameValueSeparator) + Value;
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
    fItems[Index].Str := ExtractNameStr(fItems[Index].Str) + TESLStringType(fNameValueSeparator) + Value;
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

Function TESLClassType.GetLongStrText: TESLLongStringType;
var
  Stream: TWritableStaticMemoryStream;
begin
SetLength(Result,GetWriteLength);
If Length(Result) > 0 then
  begin
    Stream := TWritableStaticMemoryStream.Create(Addr(Result[1]),Length(Result) * SizeOf(TESLCharType));
    try
      Stream.Seek(0,soBeginning);
      SaveToStream(Stream,False,seSystem);
    finally
      Stream.Free;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetLongStrText(const Value: TESLLongStringType);
var
  Stream: TStaticMemoryStream;
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  If Length(Value) > 0 then
    begin
      Stream := TStaticMemoryStream.Create(Addr(Value[1]),Length(Value) * SizeOf(TESLCharType));
      try
        Stream.Seek(0,soBeginning);
        LoadFromStream(Stream);
      finally
        Stream.Free;
      end;
    end;
  DoListChange;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetLongDelimitedText: TESLLongStringType;

  Function GetRectifiedStringLength(Index: Integer): TStrSize;
  var
    ii:     TStrSize;
    Quoted: Boolean;
  begin
    Quoted := False;
    Result := Length(fItems[Index].Str);
    For ii := 1 to Length(fItems[Index].Str) do
      If (fItems[Index].Str[ii] = fQuoteChar) or
        (fItems[Index].Str[ii] = fDelimiter) or
        (Ord(fItems[Index].Str[ii]) in [0..32]) then
        begin
          If not Quoted then
            Inc(Result,2);  // for quotechars at the start and end
          If fItems[Index].Str[ii] = fQuoteChar then
            Inc(Result);    // doubling quotechar
          Quoted := True;
        end;
  end;

  Function GetRectifiedString(Index: Integer): TESLLongStringType;
  var
    ii:     TStrSize;
    ResPos: TStrSize;    
    Quoted: Boolean;
  begin
    SetLength(Result,GetRectifiedStringLength(Index));
    ResPos := 1;
    Quoted := False;    
    For ii := 1 to Length(fItems[Index].Str) do
      If ResPos <= Length(Result) then
        begin
          If fItems[Index].Str[ii] = fQuoteChar then
            begin
              If ResPos < Length(Result) then
                begin
                  Result[ResPos] := fItems[Index].Str[ii];
                  Inc(ResPos);
                  Result[ResPos] := fItems[Index].Str[ii];
                  Quoted := True;
                end
              else Dec(ResPos);
            end
          else If (fItems[Index].Str[ii] = fDelimiter) or
            (Ord(fItems[Index].Str[ii]) in [0..32]) then
            begin
              Result[ResPos] := fItems[Index].Str[ii];
              Quoted := True;
            end
          else Result[ResPos] := fItems[Index].Str[ii];
          Inc(ResPos);
        end
      else Break{For ii};
    SetLength(Result,ResPos - 1);
    If Quoted then
      Result := TESLLongStringType(fQuoteChar) + Result + TESLLongStringType(fQuoteChar);
  end;

var
  i:    Integer;
  Len:  TStrSize;
  Temp: TESLLongStringType;
begin
Len := 0;
// count size for preallocation
For i := LowIndex to HighIndex do
  If i < HighIndex then
    Inc(Len,GetRectifiedStringLength(i) + 1{delimiter})
  else
    Inc(Len,GetRectifiedStringLength(i));
// preallocate
SetLength(Result,Len);
// store items
Len := 0;
For i := LowIndex to HighIndex do
  begin
    Temp := GetRectifiedString(i);
    If Length(Temp) > 0 then
      System.Move(TESLPCharType(Temp)^,Addr(Result[Len + 1])^,Length(Temp) * SizeOf(TESLCharType));
    Inc(Len,Length(Temp));
    If i < HighIndex then
      begin
        If Len < Length(Result) then
          Result[Len + 1] := fDelimiter
        else
          Break{For i};
        Inc(Len);
      end;    
  end;
// to be sure...
If Len < Length(Result) then
  SetLength(Result,Len);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetLongDelimitedText(const Value: TESLLongStringType);
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  with TESLDelimitedTextParser.Create(fDelimiter,fQuoteChar,fStrictDelimiter) do
  try
    fSorted := False;
    OnNewString := Self.Append;
    Parse(Value);
  finally
    Free;
  end;
  DoListChange;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetLongCommaText: TESLLongStringType;
var
  OldDelimiter: TESLCharType;
  OldQuoteChar: TESLCharType;
begin
OldDelimiter := fDelimiter;
OldQuoteChar := fQuoteChar;
try
  fDelimiter := ESL_DEFVAL_Delimiter;
  fQuoteChar := ESL_DEFVAL_QuoteChar;
  Result := GetLongDelimitedText;
finally
  fDelimiter := OldDelimiter;
  fQuoteChar := OldquoteChar;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetLongCommaText(const Value: TESLLongStringType);
var
  OldDelimiter: TESLCharType;
  OldQuoteChar: TESLCharType;
begin
OldDelimiter := fDelimiter;
OldQuoteChar := fQuoteChar;
try
  fDelimiter := ESL_DEFVAL_Delimiter;
  fQuoteChar := ESL_DEFVAL_QuoteChar;
  SetLongDelimitedText(Value);
finally
  fDelimiter := OldDelimiter;
  fQuoteChar := OldquoteChar;
end;
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetStrText: TESLStringType;
begin
// for short strings, this will truncate the long string
Result := {$IFDEF ESL_LOCAL_Short}TESLStringType{$ENDIF}(LongText);
{
  for some bizzare reason, I cannot directly use getter (GetLongStrText) when
  compiling in Delphi 7, it will fail with invalid typecast
}
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetStrText(const Value: TESLStringType);
begin
LongText := {$IFDEF ESL_LOCAL_Short}TESLLongStringType{$ENDIF}(Value);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetDelimitedText: TESLStringType;
begin
Result := {$IFDEF ESL_LOCAL_Short}TESLStringType{$ENDIF}(LongDelimitedText);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetDelimitedText(const Value: TESLStringType);
begin
LongDelimitedText := {$IFDEF ESL_LOCAL_Short}TESLLongStringType{$ENDIF}(Value);
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetCommaText: TESLStringType;
begin
Result := {$IFDEF ESL_LOCAL_Short}TESLStringType{$ENDIF}(LongCommaText);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetCommaText(const Value: TESLStringType);
begin
DelimitedText := {$IFDEF ESL_LOCAL_Short}TESLLongStringType{$ENDIF}(Value);
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

Function TESLClassType.GetWriteLength: TStrSize;
var
  i:  Integer;
begin
Result := 0;
For i := LowIndex to HighIndex do
  begin
    Inc(Result,Length(fItems[i].Str));
    If (i < HighIndex) or fTrailingLineBreak then
      Inc(Result,Length(fLineBreak));
  end;
end;

//------------------------------------------------------------------------------

{$IFDEF FPCDWM}{$PUSH}W5024{$ENDIF}
procedure TESLClassType.WriteItemToStream(Stream: TStream; Index: Integer; Endianness: TESLStringEndianness);
{$IFDEF ESL_LOCAL_Wide}
var
  Temp: UnicodeString;
{$ENDIF}
begin
If CheckIndex(Index) then
  begin
    If Length(fItems[Index].Str) > 0 then
      begin
      {$IF Defined(ESL_LOCAL_Short)}
        Stream.WriteBuffer(fItems[Index].Str[1],Length(fItems[Index].Str) * SizeOf(TESLCharType));
      {$ELSEIF Defined(ESL_LOCAL_Wide)}
        If (Endianness <> seSystem) and (Endianness <> GetSystemEndianness) then
          begin
            Temp := fItems[Index].Str;
            UniqueString(Temp);
            WideSwapEndian(PWideChar(Temp),Length(Temp));
            Stream.WriteBuffer(TESLPCharType(Temp)^,Length(Temp) * SizeOf(TESLCharType));
          end
        else Stream.WriteBuffer(TESLPCharType(fItems[Index].Str)^,Length(fItems[Index].Str) * SizeOf(TESLCharType));
      {$ELSE}
        Stream.WriteBuffer(TESLPCharType(fItems[Index].Str)^,Length(fItems[Index].Str) * SizeOf(TESLCharType));
      {$IFEND}
      end;
  end
else raise EESLIndexOutOfBounds.CreateFmt('%s.WriteItemToStream: Index (%d) out of bounds.',[Self.ClassName,Index]);
end;
{$IFDEF FPCDWM}{$POP}{$ENDIF}

//------------------------------------------------------------------------------

{$IFDEF FPCDWM}{$PUSH}W5024{$ENDIF}
procedure TESLClassType.WriteLineBreakToStream(Stream: TStream; Endianness: TESLStringEndianness);
{$IFDEF ESL_LOCAL_Wide}
var
  Temp: UnicodeString;
{$ENDIF}
begin
If Length(fLineBreak) > 0 then
  begin
  {$IF Defined(ESL_LOCAL_Short)}
    Stream.WriteBuffer(fLineBreak[1],Length(fLineBreak) * SizeOf(TESLCharType));
  {$ELSEIF Defined(ESL_LOCAL_Wide)}
    If (Endianness <> seSystem) and (Endianness <> GetSystemEndianness) then
      begin         
        Temp := fLineBreak;
        UniqueString(Temp);
        WideSwapEndian(PWideChar(Temp),Length(Temp));
        Stream.WriteBuffer(TESLPCharType(Temp)^,Length(Temp) * SizeOf(TESLCharType));
      end
    else Stream.WriteBuffer(TESLPCharType(fLineBreak)^,Length(fLineBreak) * SizeOf(TESLCharType));
  {$ELSE}
    Stream.WriteBuffer(TESLPCharType(fLineBreak)^,Length(fLineBreak) * SizeOf(TESLCharType));
  {$IFEND}  
  end;
end;
{$IFDEF FPCDWM}{$POP}{$ENDIF}

//------------------------------------------------------------------------------

{$IFDEF FPCDWM}{$PUSH}W5024{$ENDIF}
procedure TESLClassType.WriteBOMToStream(Stream: TStream; Endianness: TESLStringEndianness);
begin
{$IF Defined(ESL_UTF8)}
Stream_WriteUInt8(Stream,$EF);
Stream_WriteUInt8(Stream,$BB);
Stream_WriteUInt8(Stream,$BF);
{$ELSEIF Defined(ESL_LOCAL_Wide)}
If Endianness = seSystem then
  Endianness := GetSystemEndianness;
case Endianness of
  seLittle: begin
              Stream_WriteUInt8(Stream,$FF);
              Stream_WriteUInt8(Stream,$FE);
            end;
  seBig:    begin
              Stream_WriteUInt8(Stream,$FE);
              Stream_WriteUInt8(Stream,$FF);
            end;
else
  raise EESLInvalidValue.CreateFmt('%s.WriteBOMToStream: Invalid endianness (%d).',[Self.ClassName,Ord(Endianness)]);
end;
{$IFEND}
end;
{$IFDEF FPCDWM}{$POP}{$ENDIF}

//------------------------------------------------------------------------------

class Function TESLClassType.StrBufferSize(Buffer: Pointer): TMemSize;
var
  CharBuff: TESLPCharType;
begin
{
  there are absolutely no checks, this function simply reads memory until zero
  is encountered or something bad happens :P
}
Result := 0;
If Assigned(Buffer) then
  begin
    CharBuff := TESLPCharType(Buffer);
    while Ord(CharBuff^) <> 0 do
      begin
        Inc(Result);
        Inc(CharBuff);
      end
  end;
Result := Result * SizeOf(TESLCharType);
end;

//------------------------------------------------------------------------------

class Function TESLClassType.CharSize: TMemSize;
begin
Result := SizeOf(TESLCharType);
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

Function TESLClassType.First: TESLStringType;
begin
Result := GetString(LowIndex);
end;

//------------------------------------------------------------------------------

Function TESLClassType.Last: TESLStringType;
begin
Result := GetString(HighIndex);
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
Result := AddObject(Name + TESLStringType(fNameValueSeparator) + Value,Obj);
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
AppendObject(Name + TESLStringType(fNameValueSeparator) + Value,Obj);
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
InsertObject(Index,Name +  TESLStringType(fNameValueSeparator) + Value,Obj);
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
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    fCompareFuncIndex := nil;
    fCompareFuncString := nil;
    InternalSort(Reversed);
  end
else raise EESLSortedList.CreateFmt('%s.Sort: Cannot sort sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.CustomSort(CompareFunc: TESLSortCompareIndexType; Reversed: Boolean = False);
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    fCompareFuncIndex := CompareFunc;
    fCompareFuncString := nil;
    InternalSort(Reversed);
  end
else raise EESLSortedList.CreateFmt('%s.CustomSort: Cannot sort sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.CustomSort(CompareFunc: TESLSortCompareStringType; Reversed: Boolean = False);
begin
If not fSorted or not fStrictSorted then
  begin
    fSorted := False;
    fCompareFuncIndex := nil;
    fCompareFuncString := CompareFunc;
    InternalSort(Reversed);
  end
else raise EESLSortedList.CreateFmt('%s.CustomSort: Cannot sort sorted list.',[Self.ClassName]);
end;

//------------------------------------------------------------------------------

Function TESLClassType.Equals(Strings: TESLClassType): Boolean;
var
  i:  Integer;
begin
If fCount = Strings.Count then
  begin
    Result := True;
    For i := Strings.LowIndex to Strings.HighIndex do
      If CompareStrings(fItems[i].Str,Strings[i]) <> 0 then
        begin
          Result := False;
          Break{For i};
        end;
  end
else Result := False;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetStrings(Strings: TESLClassType);
var
  i:  Integer;
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  SetCount(Strings.Count);
  For i := Strings.LowIndex to Strings.HighIndex do
    begin
      fItems[i].Str := Strings[i];
      fItems[i].Obj := Strings.Objects[i];
    end;
  If fSorted then
    Sort;
  DoListChange;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetStrings(Strings: array of TESLStringType);
var
  i:  Integer;
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  SetCount(Length(Strings));
  For i := Low(Strings) to High(Strings) do
    fItems[i].Str := Strings[i];
  If fSorted then
    Sort;
  DoListChange;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetDefStrings(Strings: TStrings);
var
  i:  Integer;
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  SetCount(Strings.Count);
  For i := 0 to Pred(Strings.Count) do
    begin
      fItems[i].Str := {$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Strings[i]);
      fItems[i].Obj := Strings.Objects[i];
    end;
  If fSorted then
    Sort;
  DoListChange;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetDefStrings(Strings: array of String);
var
  i:  Integer;
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  SetCount(Length(Strings));
  For i := Low(Strings) to High(Strings) do
    fItems[i].Str := {$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Strings[i]);
  If fSorted then
    Sort;
  DoListChange;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Assign(Source: TESLClassType);
var
  i:  Integer;
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  // copy properties
  fOwnsObjects := Source.OwnsObjects;
  fCaseSensitive := Source.CaseSensitive;
  fDuplicates := Source.Duplicates;
  fSorted := Source.Sorted;
  fStrictSorted := Source.StrictSorted;
  fStrictDelimiter := Source.StrictDelimiter;
  fTrailingLineBreak := Source.TrailingLineBreak;
  fNameValueSeparator := Source.NameValueSeparator;
  fLineBreak := Source.LineBreak;
  fDelimiter := Source.Delimiter;
  fQuoteChar := Source.QuoteChar;
  // copy data
  SetCount(Source.Count);
  For i := Source.LowIndex to Source.HighIndex do
    begin
      fItems[i].Str := Source[i];
      fItems[i].Obj := Source.Objects[i];
    end;
  DoListChange;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.Assign(Source: TStrings);
var
  i:  Integer;
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  fSorted := False;
  // copy properties
  If Source is TStringList then
    begin
    {$IFDEF ESL_STRINGLIST_OwnsObjects}
      fOwnsObjects := TStringList(Source).OwnsObjects;{$ENDIF}
    {$IFDEF ESL_STRINGLIST_CaseSensitive}
      fCaseSensitive := TStringList(Source).CaseSensitive;{$ENDIF}
    {$IFDEF ESL_STRINGLIST_Duplicates}
      fDuplicates := TStringList(Source).Duplicates;{$ENDIF}
    {$IFDEF ESL_STRINGLIST_Sorted}
      fSorted := TStringList(Source).Sorted;{$ENDIF}
    end;
{$IFDEF ESL_STRINGS_LineBreak}
  fLineBreak := {$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Source.LineBreak);{$ENDIF}
{$IFDEF ESL_STRINGS_TrailingLineBreak}
  fTrailingLineBreak := Source.TrailingLineBreak;{$ENDIF}
{$IFDEF ESL_STRINGS_NameValueSeparator}
  fNameValueSeparator := TESLCharType(Source.NameValueSeparator);{$ENDIF}
{$IFDEF ESL_STRINGS_Delimiter}
  fDelimiter := TESLCharType(Source.Delimiter);{$ENDIF}
{$IFDEF ESL_STRINGS_StrictDelimiter}
  fStrictDelimiter := Source.StrictDelimiter;{$ENDIF}
{$IFDEF ESL_STRINGS_QuoteChar}
  fQuoteChar := TESLCharType(Source.QuoteChar);{$ENDIF}
  // copy data
  SetCount(Source.Count);
  For i := 0 to Pred(Source.Count) do
    begin
      fItems[i].Str := {$IFNDEF ESL_Default}ConvertFromString{$ENDIF}(Source[i]);
      fItems[i].Obj := Source.Objects[i];
    end;
  DoListChange;
finally
  EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AssignTo(Destination: TESLClassType);
begin
Destination.Assign(Self);
end;

//------------------------------------------------------------------------------

procedure TESLClassType.AssignTo(Destination: TStrings);
var
  i:  Integer;
begin
Destination.BeginUpdate;
try
  Destination.Clear;
  // copy properties
  If Destination is TStringList then
    begin
    {$IFDEF ESL_STRINGLIST_OwnsObjects}
      TStringList(Destination).OwnsObjects := fOwnsObjects;{$ENDIF}
    {$IFDEF ESL_STRINGLIST_CaseSensitive}
      TStringList(Destination).CaseSensitive := fCaseSensitive;{$ENDIF}
    {$IFDEF ESL_STRINGLIST_Duplicates}
      TStringList(Destination).Duplicates := fDuplicates;{$ENDIF}
    {$IFDEF ESL_STRINGLIST_Sorted}
      TStringList(Destination).Sorted := fSorted;{$ENDIF}
    end;
{$IFDEF ESL_STRINGS_LineBreak}
  Destination.LineBreak := {$IFNDEF ESL_Default}ConvertToString{$ENDIF}(fLineBreak);{$ENDIF}
{$IFDEF ESL_STRINGS_TrailingLineBreak}
  Destination.TrailingLineBreak:= fTrailingLineBreak;{$ENDIF}
{$IFDEF ESL_STRINGS_NameValueSeparator}
  Destination.NameValueSeparator := Char(fNameValueSeparator);{$ENDIF}
{$IFDEF ESL_STRINGS_Delimiter}
  Destination.Delimiter := Char(fDelimiter);{$ENDIF}
{$IFDEF ESL_STRINGS_StrictDelimiter}
  Destination.StrictDelimiter := fStrictDelimiter;{$ENDIF}
{$IFDEF ESL_STRINGS_QuoteChar}
  Destination.QuoteChar := Char(fQuoteChar);{$ENDIF}
  // copy data
  Destination.Capacity := fCount; // preallocate
  For i := LowIndex to HighIndex do
    Destination.AddObject({$IFNDEF ESL_Default}ConvertToString{$ENDIF}(fItems[i].Str),fItems[i].Obj);
finally
  Destination.EndUpdate;
end;
end;

//------------------------------------------------------------------------------

procedure TESLClassType.LoadFromStream(Stream: TStream; out Endianness: TESLStringEndianness);
const
  ReadBufferSize = 64 * 1024; // 64KiB
var
  BytesRead:    Integer;
  CharsRead:    Integer;
  Buffer:       TMemoryBuffer;
  BufferOff:    TMemSize;
  StrBuffer:    TESLLongStringType;
  StrBufferOff: TStrSize;

  procedure ProcessStringBuffer(var StringBuffer: TESLLongStringType);

    Function BreakPos(const Str: TESLLongStringType; StartFrom: Integer): Integer;
    var
      ii: Integer;
    begin
      Result := 0;
      For ii := StartFrom to Length(Str) do
        If IsBreakChar(Str[ii]) then
          begin
            Result := ii;
            Break{For ii};
          end;
    end;
    
  var
    WorkingOffset:  TStrSize;
    BreakPosition:  TStrSize;
  begin
  {
    folloving are all recognized linebreak sequences:

      #10#13
      #13#10
      #10 not followed by #13 or #0
      #13 not followed by #10 or #0
      #0 not followed by #10 or #13
  }
    If Length(StringBuffer) > 0 then
      begin
      {$IFDEF FPC}
        BreakPosition := 0;
      {$ENDIF}
        WorkingOffset := 1;
        repeat
          If not IsBreakChar(StringBuffer[WorkingOffset],False) or
            ((Length(StringBuffer) - WorkingOffset) >= 1) then
            begin
              BreakPosition := BreakPos(StrBuffer,WorkingOffset);
              If BreakPosition > 0 then
                begin
                  If BreakPosition > WorkingOffset then
                    Add({$IFDEF ESL_LOCAL_Short}TESLStringType{$ENDIF}(Copy(StringBuffer,WorkingOffset,BreakPosition - WorkingOffset)))
                  else
                    Add(TESLStringType(''));
                  If BreakPosition < Length(StringBuffer) then
                    begin
                      If (StringBuffer[BreakPosition] <> StringBuffer[Succ(BreakPosition)]) and
                         IsBreakChar(StringBuffer[Succ(BreakPosition)],False) and
                         (Ord(StringBuffer[BreakPosition]) <> 0) then
                        Inc(BreakPosition);
                    end;
                  WorkingOffset := Succ(BreakPosition);
                end;
            end
          else Break{repeat}
        until BreakPosition <= 0;
        System.Delete(StringBuffer,1,Pred(WorkingOffset));
      end;
  end;

begin
Endianness := seSystem;
BeginUpdate;
try
  DoListChanging;
  Clear;
  fSorted := False;
  If Stream.Position < Stream.Size then // is there anything to read?
    begin
      BufferInit(Buffer);
      BufferGet(Buffer,ReadBufferSize);
      try
        BufferOff := 0;
      {$IF Defined(ESL_UTF8)}
        // read BOM if present
        BytesRead := Stream.Read(BufferMemory(Buffer)^,3{length of UTF8 BOM});
        If BytesRead = 3 then
          begin
            If (PByte(BufferMemory(Buffer))^ <> $EF) or
               (PByte(BufferMemory(Buffer,1))^ <> $BB) or
               (PByte(BufferMemory(Buffer,2))^ <> $BF) then
              BufferOff := 3;
          end
        else BufferOff := BytesRead;
      {$ELSEIF Defined(ESL_LOCAL_Wide)}
        // read BOM and set endianness according to it
        BytesRead := Stream.Read(BufferMemory(Buffer)^,2{length of UTF16 BOM});
        If BytesRead = 2 then
          begin
            case PUInt16(BufferMemory(Buffer))^ of
              $FFFE:  If GetSystemEndianness = seLittle then
                        Endianness := seBig
                      else
                        Endianness := seLittle;
              $FEFF:  Endianness := GetSystemEndianness;
            else
              BufferOff := 2;
            end;
          end
        else BufferOff := BytesRead;
      {$IFEND}
        StrBuffer := '';
        while Stream.Position < Stream.Size do
          begin
            BytesRead := Stream.Read(BufferMemory(Buffer,BufferOff)^,BufferSize(Buffer) - BufferOff) + LongInt(BufferOff);
            CharsRead := BytesRead div SizeOf(TESLCharType);
          {$IFDEF ESL_LOCAL_Wide}
            // correct endianness
            If (Endianness <> seSystem) and (Endianness <> GetSystemEndianness) then
              WideSwapEndian(PWideChar(BufferMemory(Buffer,BufferOff)),CharsRead);
          {$ENDIF}
            // copy read bytes from read buffer into string buffer
            StrBufferOff := Length(StrBuffer);
            SetLength(StrBuffer,StrBufferOff + CharsRead);
            If (Length(StrBuffer) > StrBufferOff) and (Length(StrBuffer) > 0) then
              System.Move(BufferMemory(Buffer)^,StrBuffer[StrBufferOff + 1],CharsRead * SizeOf(TESLCharType));
          {$IFDEF ESL_LOCAL_Wide}
            // discard bytes copied from general buffer into string buffer, move remaining bytes down
            BufferOff := BytesRead mod SizeOf(TESLCharType);
            If BufferOff <> 0 then
              System.Move(BufferMemory(Buffer,BufferSize(Buffer)- BufferOff)^,BufferMemory(Buffer)^,BufferOff);
          {$ENDIF}
            ProcessStringBuffer(StrBuffer);
          end;
        If Length(StrBuffer) > 0 then
          begin
            If IsBreakChar(StrBuffer[1]) then
              Add(TESLStringType(''))
            else
              Add({$IFDEF ESL_LOCAL_Short}TESLStringType{$ENDIF}(StrBuffer));
          end;
      finally
        BufferFinal(Buffer);
      end;
		end;
  DoListChange;
finally
  EndUpdate;
end
end;

//------------------------------------------------------------------------------

procedure TESLClassType.BinarySaveToStream(Stream: TStream);
var
  i:  Integer;
begin
Stream_WriteInt32(Stream,fCount);
For i := LowIndex to HighIndex do
{$IF Defined(ESL_Short)}
  Stream_WriteShortString(Stream,fItems[i].Str);
{$ELSEIF Defined(ESL_Ansi)}
  Stream_WriteAnsiString(Stream,fItems[i].Str);
{$ELSEIF Defined(ESL_UTF8)}
  Stream_WriteUTF8String(Stream,fItems[i].Str);
{$ELSEIF Defined(ESL_Wide)}
  Stream_WriteWideString(Stream,fItems[i].Str);
{$ELSEIF Defined(ESL_Unicode)}
  Stream_WriteUnicodeString(Stream,fItems[i].Str);
{$ELSEIF Defined(ESL_Default)}
  Stream_WriteString(Stream,fItems[i].Str);
{$ELSE}
  {$MESSAGE FATAL 'Unknown string type.'}
{$IFEND}
end;

//------------------------------------------------------------------------------

procedure TESLClassType.BinaryLoadFromStream(Stream: TStream);
var
  i:  Integer;
begin
BeginUpdate;
try
  DoListChanging;
  Clear;
  fSorted := False;
  SetCount(Stream_ReadInt32(Stream));
  For i := LowIndex to HighIndex do
  {$IF Defined(ESL_Short)}
    Stream_ReadShortString(Stream,fItems[i].Str);
  {$ELSEIF Defined(ESL_Ansi)}
    Stream_ReadAnsiString(Stream,fItems[i].Str);
  {$ELSEIF Defined(ESL_UTF8)}
    Stream_ReadUTF8String(Stream,fItems[i].Str);
  {$ELSEIF Defined(ESL_Wide)}
    Stream_ReadWideString(Stream,fItems[i].Str);
  {$ELSEIF Defined(ESL_Unicode)}
    Stream_ReadUnicodeString(Stream,fItems[i].Str);
  {$ELSEIF Defined(ESL_Default)}
    Stream_ReadString(Stream,fItems[i].Str);
  {$ELSE}
    {$MESSAGE FATAL 'Unknown string type.'}
  {$IFEND}
  DoListChange;
finally
  EndUpdate;
end
end;

//------------------------------------------------------------------------------

Function TESLClassType.GetText(out Size: TMemSize): TESLPCharType;
begin
Result := TESLPCharType(InternalGetText(Size));
end;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Function TESLClassType.GetText: TESLPCharType;
var
  Size: TMemSize;
begin
Result := TESLPCharType(InternalGetText(Size));
end;

//------------------------------------------------------------------------------

procedure TESLClassType.SetText(Text: TESLPCharType; Size: TMemSize);
begin
InternalSetText(Pointer(Text),Size);
end;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

procedure TESLClassType.SetText(Text: TESLPCharType);
begin
InternalSetText(Pointer(Text),StrBufferSize(Pointer(Text)));
end;

{$ENDIF ESL_ClassImplementation}

