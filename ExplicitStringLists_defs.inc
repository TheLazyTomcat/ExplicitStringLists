{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Explicit string lists - defines

  Version 1.1.3 (2024-05-05)

  Last change 2024-05-05

  ©2017-2024 František Milt

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
    AuxClasses          - github.com/TheLazyTomcat/Lib.AuxClasses
  * AuxExceptions       - github.com/TheLazyTomcat/Lib.AuxExceptions
    AuxTypes            - github.com/TheLazyTomcat/Lib.AuxTypes
  * BinaryStreamingLite - github.com/TheLazyTomcat/Lib.BinaryStreamingLite
    ListSorters         - github.com/TheLazyTomcat/Lib.ListSorters
    MemoryBuffer        - github.com/TheLazyTomcat/Lib.MemoryBuffer
    StaticMemoryStream  - github.com/TheLazyTomcat/Lib.StaticMemoryStream
    StrRect             - github.com/TheLazyTomcat/Lib.StrRect

  Library AuxExceptions is required only when rebasing local exception classes
  (see symbol ExplicitStringLists_UseAuxExceptions for details).

  BinaryStreamingLite can be replaced by full BinaryStreaming.

  Library AuxExceptions might also be required as an indirect dependency.

  Indirect dependencies:
    SimpleCPUID - github.com/TheLazyTomcat/Lib.SimpleCPUID
    UInt64Utils - github.com/TheLazyTomcat/Lib.UInt64Utils
    WinFileInfo - github.com/TheLazyTomcat/Lib.WinFileInfo

===============================================================================}
{!tun_end!} // ignore this line      
{
  ExplicitStringLists_UseAuxExceptions

  If you want library-specific exceptions to be based on more advanced classes
  provided by AuxExceptions library instead of basic Exception class, and don't
  want to or cannot change code in this unit, you can define global symbol
  ExplicitStringLists_UseAuxExceptions to achieve this.
}
{$IF Defined(ExplicitStringLists_UseAuxExceptions)}
  {$DEFINE UseAuxExceptions}
{$IFEND}

//------------------------------------------------------------------------------

{$IFDEF FPC}
  {$MODE ObjFPC}
  {$MODESWITCH CLASSICPROCVARS+}
  {$MODESWITCH DUPLICATELOCALS+}
  {$INLINE ON}
  {$DEFINE CanInline}
  {$DEFINE FPC_DisableWarns}
  {$MACRO ON}
{$ELSE}
  {$IF CompilerVersion >= 17} // Delphi 2005+
    {$DEFINE CanInline}
  {$ELSE}
    {$UNDEF CanInline}
  {$IFEND}
{$ENDIF}
{$H+}

//- don't touch following ------------------------------------------------------

{$UNDEF ESL_STRINGLIST_OwnsObjects}
{$UNDEF ESL_STRINGLIST_CaseSensitive}
{$UNDEF ESL_STRINGLIST_Duplicates}
{$UNDEF ESL_STRINGLIST_Sorted}

{$UNDEF ESL_STRINGS_LineBreak}
{$UNDEF ESL_STRINGS_TrailingLineBreak}
{$UNDEF ESL_STRINGS_NameValueSeparator}
{$UNDEF ESL_STRINGS_Delimiter}
{$UNDEF ESL_STRINGS_StrictDelimiter}
{$UNDEF ESL_STRINGS_QuoteChar}

{$UNDEF ESL_ClassTypes}
{$UNDEF ESL_ClassDeclaration}
{$UNDEF ESL_ClassAuxiliary}
{$UNDEF ESL_ClassDelimitedTextParser}
{$UNDEF ESL_ClassImplementation}

{$UNDEF ESL_Short}
{$UNDEF ESL_Ansi}
{$UNDEF ESL_UTF8}
{$UNDEF ESL_Wide}
{$UNDEF ESL_Unicode}
{$UNDEF ESL_Default}
{$UNDEF ESL_UCS4}

{$UNDEF ESL_DEFAULT_Short}
{$UNDEF ESL_DEFAULT_Ansi}
{$UNDEF ESL_DEFAULT_Unicode}

{$IFOPT H+}
  // long strings...
  {$IFDEF Unicode}
    // ...Unicode
    {$DEFINE ESL_DEFAULT_Unicode}
  {$ELSE}
    // ...Ansi
    {$DEFINE ESL_DEFAULT_Ansi}
  {$ENDIF}
{$ELSE}
  // short strings
  {$DEFINE ESL_DEFAULT_Short}
{$ENDIF}
