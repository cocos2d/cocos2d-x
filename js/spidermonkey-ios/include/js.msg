/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/*
 * This is the JavaScript error message file.
 *
 * The format for each JS error message is:
 *
 * MSG_DEF(<SYMBOLIC_NAME>, <ERROR_NUMBER>, <ARGUMENT_COUNT>, <EXCEPTION_NAME>,
 *         <FORMAT_STRING>)
 *
 * where ;
 * <SYMBOLIC_NAME> is a legal C identifer that will be used in the
 * JS engine source.
 *
 * <ERROR_NUMBER> is an unique integral value identifying this error.
 *
 * <ARGUMENT_COUNT> is an integer literal specifying the total number of
 * replaceable arguments in the following format string.
 *
 * <EXCEPTION_NAME> is an exception index from the enum in jsexn.c;
 * JSEXN_NONE for none.  The given exception index will be raised by the
 * engine when the corresponding error occurs.
 *
 * <FORMAT_STRING> is a string literal, optionally containing sequences
 * {X} where X  is an integer representing the argument number that will
 * be replaced with a string value when the error is reported.
 *
 * e.g.
 *
 * MSG_DEF(JSMSG_NOT_A_SUBSPECIES, 73, JSEXN_NONE, 2,
 *         "{0} is not a member of the {1} family")
 *
 * can be used:
 *
 * JS_ReportErrorNumber(JSMSG_NOT_A_SUBSPECIES, "Rhino", "Monkey");
 *
 * to report:
 *
 * "Rhino is not a member of the Monkey family"
 *
 * When removing MSG_DEFs, convert them to JSMSG_UNUSED<n> placeholders:
 *
 *    MSG_DEF(JSMSG_UNUSED7,                  7, 0, JSEXN_NONE, "")
 *
 * Before adding a new MSG_DEF at the end, look for existing JSMSG_UNUSED<n>
 * free index placeholders in the middle of the list.
 */

MSG_DEF(JSMSG_NOT_AN_ERROR,             0, 0, JSEXN_NONE, "<Error #0 is reserved>")
MSG_DEF(JSMSG_NOT_DEFINED,              1, 1, JSEXN_REFERENCEERR, "{0} is not defined")
MSG_DEF(JSMSG_INACTIVE,                 2, 0, JSEXN_INTERNALERR, "nothing active on context")
MSG_DEF(JSMSG_MORE_ARGS_NEEDED,         3, 3, JSEXN_TYPEERR, "{0} requires more than {1} argument{2}")
MSG_DEF(JSMSG_BAD_CHAR,                 4, 1, JSEXN_INTERNALERR, "invalid format character {0}")
MSG_DEF(JSMSG_BAD_TYPE,                 5, 1, JSEXN_TYPEERR, "unknown type {0}")
MSG_DEF(JSMSG_ALLOC_OVERFLOW,           6, 0, JSEXN_INTERNALERR, "allocation size overflow")
MSG_DEF(JSMSG_MISSING_HEXDIGITS,        7, 0, JSEXN_SYNTAXERR, "missing hexadecimal digits after '0x'")
MSG_DEF(JSMSG_INCOMPATIBLE_PROTO,       8, 3, JSEXN_TYPEERR, "{0}.prototype.{1} called on incompatible {2}")
MSG_DEF(JSMSG_NO_CONSTRUCTOR,           9, 1, JSEXN_TYPEERR, "{0} has no constructor")
MSG_DEF(JSMSG_CANT_ALIAS,              10, 3, JSEXN_TYPEERR, "can't alias {0} to {1} in class {2}")
MSG_DEF(JSMSG_NOT_SCRIPTED_FUNCTION,   11, 1, JSEXN_TYPEERR, "{0} is not a scripted function")
MSG_DEF(JSMSG_BAD_SORT_ARG,            12, 0, JSEXN_TYPEERR, "invalid Array.prototype.sort argument")
MSG_DEF(JSMSG_BAD_ATOMIC_NUMBER,       13, 1, JSEXN_INTERNALERR, "internal error: no index for atom {0}")
MSG_DEF(JSMSG_TOO_MANY_LITERALS,       14, 0, JSEXN_INTERNALERR, "too many literals")
MSG_DEF(JSMSG_CANT_WATCH,              15, 1, JSEXN_TYPEERR, "can't watch non-native objects of class {0}")
MSG_DEF(JSMSG_STACK_UNDERFLOW,         16, 2, JSEXN_INTERNALERR, "internal error compiling {0}: stack underflow at pc {1}")
MSG_DEF(JSMSG_NEED_DIET,               17, 1, JSEXN_INTERNALERR, "{0} too large")
MSG_DEF(JSMSG_TOO_MANY_LOCAL_ROOTS,    18, 0, JSEXN_ERR, "out of local root space")
MSG_DEF(JSMSG_READ_ONLY,               19, 1, JSEXN_TYPEERR, "{0} is read-only")
MSG_DEF(JSMSG_BAD_FORMAL,              20, 0, JSEXN_SYNTAXERR, "malformed formal parameter")
MSG_DEF(JSMSG_CANT_DELETE,             21, 1, JSEXN_TYPEERR, "property {0} is non-configurable and can't be deleted")
MSG_DEF(JSMSG_NOT_FUNCTION,            22, 1, JSEXN_TYPEERR, "{0} is not a function")
MSG_DEF(JSMSG_NOT_CONSTRUCTOR,         23, 1, JSEXN_TYPEERR, "{0} is not a constructor")
MSG_DEF(JSMSG_INVALID_DATE,            24, 0, JSEXN_RANGEERR, "invalid date")
MSG_DEF(JSMSG_TOO_DEEP,                25, 1, JSEXN_INTERNALERR, "{0} nested too deeply")
MSG_DEF(JSMSG_OVER_RECURSED,           26, 0, JSEXN_INTERNALERR, "too much recursion")
MSG_DEF(JSMSG_IN_NOT_OBJECT,           27, 1, JSEXN_TYPEERR, "invalid 'in' operand {0}")
MSG_DEF(JSMSG_BAD_NEW_RESULT,          28, 1, JSEXN_TYPEERR, "invalid new expression result {0}")
MSG_DEF(JSMSG_BAD_SHARP_DEF,           29, 1, JSEXN_ERR, "invalid sharp variable definition #{0}=")
MSG_DEF(JSMSG_BAD_SHARP_USE,           30, 1, JSEXN_ERR, "invalid sharp variable use #{0}#")
MSG_DEF(JSMSG_BAD_INSTANCEOF_RHS,      31, 1, JSEXN_TYPEERR, "invalid 'instanceof' operand {0}")
MSG_DEF(JSMSG_BAD_BYTECODE,            32, 1, JSEXN_INTERNALERR, "unimplemented JavaScript bytecode {0}")
MSG_DEF(JSMSG_BAD_RADIX,               33, 0, JSEXN_RANGEERR, "radix must be an integer at least 2 and no greater than 36")
MSG_DEF(JSMSG_PAREN_BEFORE_LET,        34, 0, JSEXN_SYNTAXERR, "missing ( before let head")
MSG_DEF(JSMSG_CANT_CONVERT,            35, 1, JSEXN_ERR, "can't convert {0} to an integer")
MSG_DEF(JSMSG_CYCLIC_VALUE,            36, 1, JSEXN_TYPEERR, "cyclic {0} value")
MSG_DEF(JSMSG_COMPILE_EXECED_SCRIPT,   37, 0, JSEXN_TYPEERR, "can't compile over a script that is currently executing")
MSG_DEF(JSMSG_CANT_CONVERT_TO,         38, 2, JSEXN_TYPEERR, "can't convert {0} to {1}")
MSG_DEF(JSMSG_NO_PROPERTIES,           39, 1, JSEXN_TYPEERR, "{0} has no properties")
MSG_DEF(JSMSG_CANT_FIND_CLASS,         40, 1, JSEXN_TYPEERR, "can't find class id {0}")
MSG_DEF(JSMSG_UNUSED41      ,          41, 0, JSEXN_NONE,    "")
MSG_DEF(JSMSG_BYTECODE_TOO_BIG,        42, 2, JSEXN_INTERNALERR, "bytecode {0} too large (limit {1})")
MSG_DEF(JSMSG_UNKNOWN_FORMAT,          43, 1, JSEXN_INTERNALERR, "unknown bytecode format {0}")
MSG_DEF(JSMSG_TOO_MANY_CON_ARGS,       44, 0, JSEXN_SYNTAXERR, "too many constructor arguments")
MSG_DEF(JSMSG_TOO_MANY_FUN_ARGS,       45, 0, JSEXN_SYNTAXERR, "too many function arguments")
MSG_DEF(JSMSG_BAD_QUANTIFIER,          46, 0, JSEXN_SYNTAXERR, "invalid quantifier")
MSG_DEF(JSMSG_MIN_TOO_BIG,             47, 1, JSEXN_SYNTAXERR, "overlarge minimum {0}")
MSG_DEF(JSMSG_MAX_TOO_BIG,             48, 1, JSEXN_SYNTAXERR, "overlarge maximum {0}")
MSG_DEF(JSMSG_OUT_OF_ORDER,            49, 1, JSEXN_SYNTAXERR, "maximum {0} less than minimum")
MSG_DEF(JSMSG_BAD_DESTRUCT_DECL,       50, 0, JSEXN_SYNTAXERR, "missing = in destructuring declaration")
MSG_DEF(JSMSG_BAD_DESTRUCT_ASS,        51, 0, JSEXN_REFERENCEERR, "invalid destructuring assignment operator")
MSG_DEF(JSMSG_PAREN_AFTER_LET,         52, 0, JSEXN_SYNTAXERR, "missing ) after let head")
MSG_DEF(JSMSG_CURLY_AFTER_LET,         53, 0, JSEXN_SYNTAXERR, "missing } after let block")
MSG_DEF(JSMSG_MISSING_PAREN,           54, 0, JSEXN_SYNTAXERR, "unterminated parenthetical")
MSG_DEF(JSMSG_UNTERM_CLASS,            55, 1, JSEXN_SYNTAXERR, "unterminated character class {0}")
MSG_DEF(JSMSG_TRAILING_SLASH,          56, 0, JSEXN_SYNTAXERR, "trailing \\ in regular expression")
MSG_DEF(JSMSG_BAD_CLASS_RANGE,         57, 0, JSEXN_SYNTAXERR, "invalid range in character class")
MSG_DEF(JSMSG_BAD_REGEXP_FLAG,         58, 1, JSEXN_SYNTAXERR, "invalid regular expression flag {0}")
MSG_DEF(JSMSG_NO_INPUT,                59, 5, JSEXN_SYNTAXERR, "no input for /{0}/{1}{2}{3}{4}")
MSG_DEF(JSMSG_CANT_OPEN,               60, 2, JSEXN_ERR, "can't open {0}: {1}")
MSG_DEF(JSMSG_TOO_MANY_FUN_APPLY_ARGS, 61, 0, JSEXN_RANGEERR, "arguments array passed to Function.prototype.apply is too large")
MSG_DEF(JSMSG_UNMATCHED_RIGHT_PAREN,   62, 0, JSEXN_SYNTAXERR, "unmatched ) in regular expression")
MSG_DEF(JSMSG_END_OF_DATA,             63, 0, JSEXN_INTERNALERR, "unexpected end of data")
MSG_DEF(JSMSG_SEEK_BEYOND_START,       64, 0, JSEXN_INTERNALERR, "illegal seek beyond start")
MSG_DEF(JSMSG_SEEK_BEYOND_END,         65, 0, JSEXN_INTERNALERR, "illegal seek beyond end")
MSG_DEF(JSMSG_END_SEEK,                66, 0, JSEXN_INTERNALERR, "illegal end-based seek")
MSG_DEF(JSMSG_WHITHER_WHENCE,          67, 1, JSEXN_INTERNALERR, "unknown seek whence: {0}")
MSG_DEF(JSMSG_BAD_SCRIPT_MAGIC,        68, 0, JSEXN_INTERNALERR, "bad script XDR magic number")
MSG_DEF(JSMSG_PAREN_BEFORE_FORMAL,     69, 0, JSEXN_SYNTAXERR, "missing ( before formal parameters")
MSG_DEF(JSMSG_MISSING_FORMAL,          70, 0, JSEXN_SYNTAXERR, "missing formal parameter")
MSG_DEF(JSMSG_PAREN_AFTER_FORMAL,      71, 0, JSEXN_SYNTAXERR, "missing ) after formal parameters")
MSG_DEF(JSMSG_CURLY_BEFORE_BODY,       72, 0, JSEXN_SYNTAXERR, "missing { before function body")
MSG_DEF(JSMSG_CURLY_AFTER_BODY,        73, 0, JSEXN_SYNTAXERR, "missing } after function body")
MSG_DEF(JSMSG_PAREN_BEFORE_COND,       74, 0, JSEXN_SYNTAXERR, "missing ( before condition")
MSG_DEF(JSMSG_PAREN_AFTER_COND,        75, 0, JSEXN_SYNTAXERR, "missing ) after condition")
MSG_DEF(JSMSG_DESTRUCT_DUP_ARG,        76, 0, JSEXN_SYNTAXERR, "duplicate argument is mixed with destructuring pattern")
MSG_DEF(JSMSG_NAME_AFTER_DOT,          77, 0, JSEXN_SYNTAXERR, "missing name after . operator")
MSG_DEF(JSMSG_BRACKET_IN_INDEX,        78, 0, JSEXN_SYNTAXERR, "missing ] in index expression")
MSG_DEF(JSMSG_XML_WHOLE_PROGRAM,       79, 0, JSEXN_SYNTAXERR, "XML can't be the whole program")
MSG_DEF(JSMSG_PAREN_BEFORE_SWITCH,     80, 0, JSEXN_SYNTAXERR, "missing ( before switch expression")
MSG_DEF(JSMSG_PAREN_AFTER_SWITCH,      81, 0, JSEXN_SYNTAXERR, "missing ) after switch expression")
MSG_DEF(JSMSG_CURLY_BEFORE_SWITCH,     82, 0, JSEXN_SYNTAXERR, "missing { before switch body")
MSG_DEF(JSMSG_COLON_AFTER_CASE,        83, 0, JSEXN_SYNTAXERR, "missing : after case label")
MSG_DEF(JSMSG_WHILE_AFTER_DO,          84, 0, JSEXN_SYNTAXERR, "missing while after do-loop body")
MSG_DEF(JSMSG_PAREN_AFTER_FOR,         85, 0, JSEXN_SYNTAXERR, "missing ( after for")
MSG_DEF(JSMSG_SEMI_AFTER_FOR_INIT,     86, 0, JSEXN_SYNTAXERR, "missing ; after for-loop initializer")
MSG_DEF(JSMSG_SEMI_AFTER_FOR_COND,     87, 0, JSEXN_SYNTAXERR, "missing ; after for-loop condition")
MSG_DEF(JSMSG_PAREN_AFTER_FOR_CTRL,    88, 0, JSEXN_SYNTAXERR, "missing ) after for-loop control")
MSG_DEF(JSMSG_CURLY_BEFORE_TRY,        89, 0, JSEXN_SYNTAXERR, "missing { before try block")
MSG_DEF(JSMSG_CURLY_AFTER_TRY,         90, 0, JSEXN_SYNTAXERR, "missing } after try block")
MSG_DEF(JSMSG_PAREN_BEFORE_CATCH,      91, 0, JSEXN_SYNTAXERR, "missing ( before catch")
MSG_DEF(JSMSG_CATCH_IDENTIFIER,        92, 0, JSEXN_SYNTAXERR, "missing identifier in catch")
MSG_DEF(JSMSG_PAREN_AFTER_CATCH,       93, 0, JSEXN_SYNTAXERR, "missing ) after catch")
MSG_DEF(JSMSG_CURLY_BEFORE_CATCH,      94, 0, JSEXN_SYNTAXERR, "missing { before catch block")
MSG_DEF(JSMSG_CURLY_AFTER_CATCH,       95, 0, JSEXN_SYNTAXERR, "missing } after catch block")
MSG_DEF(JSMSG_CURLY_BEFORE_FINALLY,    96, 0, JSEXN_SYNTAXERR, "missing { before finally block")
MSG_DEF(JSMSG_CURLY_AFTER_FINALLY,     97, 0, JSEXN_SYNTAXERR, "missing } after finally block")
MSG_DEF(JSMSG_CATCH_OR_FINALLY,        98, 0, JSEXN_SYNTAXERR, "missing catch or finally after try")
MSG_DEF(JSMSG_PAREN_BEFORE_WITH,       99, 0, JSEXN_SYNTAXERR, "missing ( before with-statement object")
MSG_DEF(JSMSG_PAREN_AFTER_WITH,       100, 0, JSEXN_SYNTAXERR, "missing ) after with-statement object")
MSG_DEF(JSMSG_CURLY_IN_COMPOUND,      101, 0, JSEXN_SYNTAXERR, "missing } in compound statement")
MSG_DEF(JSMSG_NO_VARIABLE_NAME,       102, 0, JSEXN_SYNTAXERR, "missing variable name")
MSG_DEF(JSMSG_COLON_IN_COND,          103, 0, JSEXN_SYNTAXERR, "missing : in conditional expression")
MSG_DEF(JSMSG_PAREN_AFTER_ARGS,       104, 0, JSEXN_SYNTAXERR, "missing ) after argument list")
MSG_DEF(JSMSG_BRACKET_AFTER_LIST,     105, 0, JSEXN_SYNTAXERR, "missing ] after element list")
MSG_DEF(JSMSG_COLON_AFTER_ID,         106, 0, JSEXN_SYNTAXERR, "missing : after property id")
MSG_DEF(JSMSG_CURLY_AFTER_LIST,       107, 0, JSEXN_SYNTAXERR, "missing } after property list")
MSG_DEF(JSMSG_PAREN_IN_PAREN,         108, 0, JSEXN_SYNTAXERR, "missing ) in parenthetical")
MSG_DEF(JSMSG_SEMI_BEFORE_STMNT,      109, 0, JSEXN_SYNTAXERR, "missing ; before statement")
MSG_DEF(JSMSG_NO_RETURN_VALUE,        110, 1, JSEXN_TYPEERR, "function {0} does not always return a value")
MSG_DEF(JSMSG_DUPLICATE_FORMAL,       111, 1, JSEXN_SYNTAXERR, "duplicate formal argument {0}")
MSG_DEF(JSMSG_EQUAL_AS_ASSIGN,        112, 0, JSEXN_SYNTAXERR, "test for equality (==) mistyped as assignment (=)?")
MSG_DEF(JSMSG_OPTIMIZED_CLOSURE_LEAK, 113, 0, JSEXN_INTERNALERR, "can't access optimized closure")
MSG_DEF(JSMSG_TOO_MANY_DEFAULTS,      114, 0, JSEXN_SYNTAXERR, "more than one switch default")
MSG_DEF(JSMSG_TOO_MANY_CASES,         115, 0, JSEXN_INTERNALERR, "too many switch cases")
MSG_DEF(JSMSG_BAD_SWITCH,             116, 0, JSEXN_SYNTAXERR, "invalid switch statement")
MSG_DEF(JSMSG_BAD_FOR_LEFTSIDE,       117, 0, JSEXN_SYNTAXERR, "invalid for/in left-hand side")
MSG_DEF(JSMSG_CATCH_AFTER_GENERAL,    118, 0, JSEXN_SYNTAXERR, "catch after unconditional catch")
MSG_DEF(JSMSG_CATCH_WITHOUT_TRY,      119, 0, JSEXN_SYNTAXERR, "catch without try")
MSG_DEF(JSMSG_FINALLY_WITHOUT_TRY,    120, 0, JSEXN_SYNTAXERR, "finally without try")
MSG_DEF(JSMSG_LABEL_NOT_FOUND,        121, 0, JSEXN_SYNTAXERR, "label not found")
MSG_DEF(JSMSG_TOUGH_BREAK,            122, 0, JSEXN_SYNTAXERR, "unlabeled break must be inside loop or switch")
MSG_DEF(JSMSG_BAD_CONTINUE,           123, 0, JSEXN_SYNTAXERR, "continue must be inside loop")
MSG_DEF(JSMSG_BAD_RETURN_OR_YIELD,    124, 1, JSEXN_SYNTAXERR, "{0} not in function")
MSG_DEF(JSMSG_BAD_LABEL,              125, 0, JSEXN_SYNTAXERR, "invalid label")
MSG_DEF(JSMSG_DUPLICATE_LABEL,        126, 0, JSEXN_SYNTAXERR, "duplicate label")
MSG_DEF(JSMSG_VAR_HIDES_ARG,          127, 1, JSEXN_TYPEERR, "variable {0} redeclares argument")
MSG_DEF(JSMSG_BAD_VAR_INIT,           128, 0, JSEXN_SYNTAXERR, "invalid variable initialization")
MSG_DEF(JSMSG_BAD_LEFTSIDE_OF_ASS,    129, 0, JSEXN_REFERENCEERR, "invalid assignment left-hand side")
MSG_DEF(JSMSG_BAD_OPERAND,            130, 1, JSEXN_SYNTAXERR, "invalid {0} operand")
MSG_DEF(JSMSG_BAD_PROP_ID,            131, 0, JSEXN_SYNTAXERR, "invalid property id")
MSG_DEF(JSMSG_RESERVED_ID,            132, 1, JSEXN_SYNTAXERR, "{0} is a reserved identifier")
MSG_DEF(JSMSG_SYNTAX_ERROR,           133, 0, JSEXN_SYNTAXERR, "syntax error")
MSG_DEF(JSMSG_BAD_SHARP_VAR_DEF,      134, 0, JSEXN_SYNTAXERR, "invalid sharp variable definition")
MSG_DEF(JSMSG_BAD_PROTOTYPE,          135, 1, JSEXN_TYPEERR,   "'prototype' property of {0} is not an object")
MSG_DEF(JSMSG_MISSING_EXPONENT,       136, 0, JSEXN_SYNTAXERR, "missing exponent")
MSG_DEF(JSMSG_OUT_OF_MEMORY,          137, 0, JSEXN_ERR, "out of memory")
MSG_DEF(JSMSG_UNTERMINATED_STRING,    138, 0, JSEXN_SYNTAXERR, "unterminated string literal")
MSG_DEF(JSMSG_TOO_MANY_PARENS,        139, 0, JSEXN_INTERNALERR, "too many parentheses in regular expression")
MSG_DEF(JSMSG_UNTERMINATED_COMMENT,   140, 0, JSEXN_SYNTAXERR, "unterminated comment")
MSG_DEF(JSMSG_UNTERMINATED_REGEXP,    141, 0, JSEXN_SYNTAXERR, "unterminated regular expression literal")
MSG_DEF(JSMSG_BAD_CLONE_FUNOBJ_SCOPE, 142, 0, JSEXN_TYPEERR, "bad cloned function scope chain")
MSG_DEF(JSMSG_SHARPVAR_TOO_BIG,       143, 0, JSEXN_SYNTAXERR, "overlarge sharp variable number")
MSG_DEF(JSMSG_ILLEGAL_CHARACTER,      144, 0, JSEXN_SYNTAXERR, "illegal character")
MSG_DEF(JSMSG_BAD_OCTAL,              145, 1, JSEXN_SYNTAXERR, "{0} is not a legal ECMA-262 octal constant")
MSG_DEF(JSMSG_BAD_INDIRECT_CALL,      146, 1, JSEXN_EVALERR, "function {0} must be called directly, and not by way of a function of another name")
MSG_DEF(JSMSG_UNCAUGHT_EXCEPTION,     147, 1, JSEXN_INTERNALERR, "uncaught exception: {0}")
MSG_DEF(JSMSG_INVALID_BACKREF,        148, 0, JSEXN_SYNTAXERR, "non-octal digit in an escape sequence that doesn't match a back-reference")
MSG_DEF(JSMSG_BAD_BACKREF,            149, 0, JSEXN_SYNTAXERR, "back-reference exceeds number of capturing parentheses")
MSG_DEF(JSMSG_PRECISION_RANGE,        150, 1, JSEXN_RANGEERR, "precision {0} out of range")
MSG_DEF(JSMSG_BAD_GETTER_OR_SETTER,   151, 1, JSEXN_TYPEERR, "invalid {0} usage")
MSG_DEF(JSMSG_BAD_ARRAY_LENGTH,       152, 0, JSEXN_RANGEERR, "invalid array length")
MSG_DEF(JSMSG_CANT_DESCRIBE_PROPS,    153, 1, JSEXN_TYPEERR, "can't describe non-native properties of class {0}")
MSG_DEF(JSMSG_BAD_APPLY_ARGS,         154, 1, JSEXN_TYPEERR, "second argument to Function.prototype.{0} must be an array")
MSG_DEF(JSMSG_REDECLARED_VAR,         155, 2, JSEXN_TYPEERR, "redeclaration of {0} {1}")
MSG_DEF(JSMSG_UNDECLARED_VAR,         156, 1, JSEXN_REFERENCEERR, "assignment to undeclared variable {0}")
MSG_DEF(JSMSG_ANON_NO_RETURN_VALUE,   157, 0, JSEXN_TYPEERR, "anonymous function does not always return a value")
MSG_DEF(JSMSG_DEPRECATED_USAGE,       158, 1, JSEXN_REFERENCEERR, "deprecated {0} usage")
MSG_DEF(JSMSG_BAD_URI,                159, 0, JSEXN_URIERR, "malformed URI sequence")
MSG_DEF(JSMSG_GETTER_ONLY,            160, 0, JSEXN_TYPEERR, "setting a property that has only a getter")
MSG_DEF(JSMSG_IDSTART_AFTER_NUMBER,   161, 0, JSEXN_SYNTAXERR, "identifier starts immediately after numeric literal")
MSG_DEF(JSMSG_UNDEFINED_PROP,         162, 1, JSEXN_REFERENCEERR, "reference to undefined property {0}")
MSG_DEF(JSMSG_USELESS_EXPR,           163, 0, JSEXN_TYPEERR, "useless expression")
MSG_DEF(JSMSG_REDECLARED_PARAM,       164, 1, JSEXN_TYPEERR, "redeclaration of formal parameter {0}")
MSG_DEF(JSMSG_NEWREGEXP_FLAGGED,      165, 0, JSEXN_TYPEERR, "can't supply flags when constructing one RegExp from another")
MSG_DEF(JSMSG_RESERVED_SLOT_RANGE,    166, 0, JSEXN_RANGEERR, "reserved slot index out of range")
MSG_DEF(JSMSG_CANT_DECODE_PRINCIPALS, 167, 0, JSEXN_INTERNALERR, "can't decode JSPrincipals")
MSG_DEF(JSMSG_CANT_SEAL_OBJECT,       168, 1, JSEXN_ERR, "can't seal {0} objects")
MSG_DEF(JSMSG_TOO_MANY_CATCH_VARS,    169, 0, JSEXN_SYNTAXERR, "too many catch variables")
MSG_DEF(JSMSG_BAD_XML_MARKUP,         170, 0, JSEXN_SYNTAXERR, "invalid XML markup")
MSG_DEF(JSMSG_BAD_XML_CHARACTER,      171, 0, JSEXN_SYNTAXERR, "illegal XML character")
MSG_DEF(JSMSG_BAD_DEFAULT_XML_NAMESPACE,172,0,JSEXN_SYNTAXERR, "invalid default XML namespace")
MSG_DEF(JSMSG_BAD_XML_NAME_SYNTAX,    173, 0, JSEXN_SYNTAXERR, "invalid XML name")
MSG_DEF(JSMSG_BRACKET_AFTER_ATTR_EXPR,174, 0, JSEXN_SYNTAXERR, "missing ] after attribute expression")
MSG_DEF(JSMSG_NESTING_GENERATOR,      175, 1, JSEXN_TYPEERR, "already executing generator {0}")
MSG_DEF(JSMSG_CURLY_IN_XML_EXPR,      176, 0, JSEXN_SYNTAXERR, "missing } in XML expression")
MSG_DEF(JSMSG_BAD_XML_NAMESPACE,      177, 1, JSEXN_TYPEERR, "invalid XML namespace {0}")
MSG_DEF(JSMSG_BAD_XML_ATTR_NAME,      178, 1, JSEXN_TYPEERR, "invalid XML attribute name {0}")
MSG_DEF(JSMSG_BAD_XML_NAME,           179, 1, JSEXN_TYPEERR, "invalid XML name {0}")
MSG_DEF(JSMSG_BAD_XML_CONVERSION,     180, 1, JSEXN_TYPEERR, "can't convert {0} to XML")
MSG_DEF(JSMSG_BAD_XMLLIST_CONVERSION, 181, 1, JSEXN_TYPEERR, "can't convert {0} to XMLList")
MSG_DEF(JSMSG_BAD_GENERATOR_SEND,     182, 1, JSEXN_TYPEERR, "attempt to send {0} to newborn generator")
MSG_DEF(JSMSG_NO_ASSIGN_IN_XML_ATTR,  183, 0, JSEXN_SYNTAXERR, "missing = in XML attribute")
MSG_DEF(JSMSG_BAD_XML_ATTR_VALUE,     184, 0, JSEXN_SYNTAXERR, "invalid XML attribute value")
MSG_DEF(JSMSG_XML_TAG_NAME_MISMATCH,  185, 1, JSEXN_SYNTAXERR, "XML tag name mismatch (expected {0})")
MSG_DEF(JSMSG_BAD_XML_TAG_SYNTAX,     186, 0, JSEXN_SYNTAXERR, "invalid XML tag syntax")
MSG_DEF(JSMSG_BAD_XML_LIST_SYNTAX,    187, 0, JSEXN_SYNTAXERR, "invalid XML list syntax")
MSG_DEF(JSMSG_INCOMPATIBLE_METHOD,    188, 3, JSEXN_TYPEERR, "{0} {1} called on incompatible {2}")
MSG_DEF(JSMSG_CANT_SET_XML_ATTRS,     189, 0, JSEXN_INTERNALERR, "can't set XML property attributes")
MSG_DEF(JSMSG_END_OF_XML_SOURCE,      190, 0, JSEXN_SYNTAXERR, "unexpected end of XML source")
MSG_DEF(JSMSG_END_OF_XML_ENTITY,      191, 0, JSEXN_SYNTAXERR, "unexpected end of XML entity")
MSG_DEF(JSMSG_BAD_XML_QNAME,          192, 0, JSEXN_SYNTAXERR, "invalid XML qualified name")
MSG_DEF(JSMSG_BAD_FOR_EACH_LOOP,      193, 0, JSEXN_SYNTAXERR, "invalid for each loop")
MSG_DEF(JSMSG_BAD_XMLLIST_PUT,        194, 1, JSEXN_TYPEERR, "can't set property {0} in XMLList")
MSG_DEF(JSMSG_UNKNOWN_XML_ENTITY,     195, 1, JSEXN_TYPEERR, "unknown XML entity {0}")
MSG_DEF(JSMSG_BAD_XML_NCR,            196, 1, JSEXN_TYPEERR, "malformed XML character {0}")
MSG_DEF(JSMSG_UNDEFINED_XML_NAME,     197, 1, JSEXN_REFERENCEERR, "reference to undefined XML name {0}")
MSG_DEF(JSMSG_DUPLICATE_XML_ATTR,     198, 1, JSEXN_TYPEERR, "duplicate XML attribute {0}")
MSG_DEF(JSMSG_TOO_MANY_LOCALS,        199, 0, JSEXN_SYNTAXERR, "too many local variables")
MSG_DEF(JSMSG_ARRAY_INIT_TOO_BIG,     200, 0, JSEXN_INTERNALERR, "array initialiser too large")
MSG_DEF(JSMSG_REGEXP_TOO_COMPLEX,     201, 0, JSEXN_INTERNALERR, "regular expression too complex")
MSG_DEF(JSMSG_BUFFER_TOO_SMALL,       202, 0, JSEXN_INTERNALERR, "buffer too small")
MSG_DEF(JSMSG_BAD_SURROGATE_CHAR,     203, 1, JSEXN_TYPEERR, "bad surrogate character {0}")
MSG_DEF(JSMSG_UTF8_CHAR_TOO_LARGE,    204, 1, JSEXN_TYPEERR, "UTF-8 character {0} too large")
MSG_DEF(JSMSG_MALFORMED_UTF8_CHAR,    205, 1, JSEXN_TYPEERR, "malformed UTF-8 character sequence at offset {0}")
MSG_DEF(JSMSG_USER_DEFINED_ERROR,     206, 0, JSEXN_ERR, "JS_ReportError was called")
MSG_DEF(JSMSG_WRONG_CONSTRUCTOR,      207, 1, JSEXN_TYPEERR, "wrong constructor called for {0}")
MSG_DEF(JSMSG_BAD_GENERATOR_RETURN,   208, 1, JSEXN_TYPEERR, "generator function {0} returns a value")
MSG_DEF(JSMSG_BAD_ANON_GENERATOR_RETURN, 209, 0, JSEXN_TYPEERR, "anonymous generator function returns a value")
MSG_DEF(JSMSG_NAME_AFTER_FOR_PAREN,   210, 0, JSEXN_SYNTAXERR, "missing name after for (")
MSG_DEF(JSMSG_IN_AFTER_FOR_NAME,      211, 0, JSEXN_SYNTAXERR, "missing 'in' or 'of' after for")
MSG_DEF(JSMSG_BAD_TRAP_RETURN_VALUE,  212, 2, JSEXN_TYPEERR,"trap {1} for {0} returned a primitive value")
MSG_DEF(JSMSG_KEYWORD_NOT_NS,         213, 0, JSEXN_SYNTAXERR, "keyword is used as namespace")
MSG_DEF(JSMSG_BAD_GENERATOR_YIELD,    214, 1, JSEXN_TYPEERR, "yield from closing generator {0}")
MSG_DEF(JSMSG_BAD_GENERATOR_SYNTAX,   215, 1, JSEXN_SYNTAXERR, "{0} expression must be parenthesized")
MSG_DEF(JSMSG_ARRAY_COMP_LEFTSIDE,    216, 0, JSEXN_SYNTAXERR, "invalid array comprehension left-hand side")
MSG_DEF(JSMSG_NON_XML_FILTER,         217, 1, JSEXN_TYPEERR, "XML filter is applied to non-XML value {0}")
MSG_DEF(JSMSG_EMPTY_ARRAY_REDUCE,     218, 0, JSEXN_TYPEERR, "reduce of empty array with no initial value")
MSG_DEF(JSMSG_NON_LIST_XML_METHOD,    219, 2, JSEXN_TYPEERR, "can't call {0} method on an XML list with {1} elements")
MSG_DEF(JSMSG_BAD_DELETE_OPERAND,     220, 0, JSEXN_REFERENCEERR, "invalid delete operand")
MSG_DEF(JSMSG_BAD_INCOP_OPERAND,      221, 0, JSEXN_REFERENCEERR, "invalid increment/decrement operand")
MSG_DEF(JSMSG_UNEXPECTED_TYPE,        222, 2, JSEXN_TYPEERR, "{0} is {1}")
MSG_DEF(JSMSG_LET_DECL_NOT_IN_BLOCK,  223, 0, JSEXN_SYNTAXERR, "let declaration not directly within block")
MSG_DEF(JSMSG_BAD_OBJECT_INIT,        224, 0, JSEXN_SYNTAXERR, "invalid object initializer")
MSG_DEF(JSMSG_CANT_SET_ARRAY_ATTRS,   225, 0, JSEXN_INTERNALERR, "can't set attributes on indexed array properties")
MSG_DEF(JSMSG_EVAL_ARITY,             226, 0, JSEXN_TYPEERR, "eval accepts only one parameter")
MSG_DEF(JSMSG_MISSING_FUN_ARG,        227, 2, JSEXN_TYPEERR, "missing argument {0} when calling function {1}")
MSG_DEF(JSMSG_JSON_BAD_PARSE,         228, 1, JSEXN_SYNTAXERR, "JSON.parse: {0}")
MSG_DEF(JSMSG_JSON_BAD_STRINGIFY,     229, 0, JSEXN_ERR, "JSON.stringify")
MSG_DEF(JSMSG_NOT_CALLABLE_OR_UNDEFINED, 230, 0, JSEXN_TYPEERR, "value is not a function or undefined")
MSG_DEF(JSMSG_NOT_NONNULL_OBJECT,     231, 0, JSEXN_TYPEERR, "value is not a non-null object")
MSG_DEF(JSMSG_DEPRECATED_OCTAL,       232, 0, JSEXN_SYNTAXERR, "octal literals and octal escape sequences are deprecated")
MSG_DEF(JSMSG_STRICT_CODE_WITH,       233, 0, JSEXN_SYNTAXERR, "strict mode code may not contain 'with' statements")
MSG_DEF(JSMSG_DUPLICATE_PROPERTY,     234, 1, JSEXN_SYNTAXERR, "property name {0} appears more than once in object literal")
MSG_DEF(JSMSG_DEPRECATED_DELETE_OPERAND, 235, 0, JSEXN_SYNTAXERR, "applying the 'delete' operator to an unqualified name is deprecated")
MSG_DEF(JSMSG_DEPRECATED_ASSIGN,      236, 1, JSEXN_SYNTAXERR, "assignment to {0} is deprecated")
MSG_DEF(JSMSG_BAD_BINDING,            237, 1, JSEXN_SYNTAXERR, "redefining {0} is deprecated")
MSG_DEF(JSMSG_INVALID_DESCRIPTOR,     238, 0, JSEXN_TYPEERR, "property descriptors must not specify a value or be writable when a getter or setter has been specified")
MSG_DEF(JSMSG_OBJECT_NOT_EXTENSIBLE,  239, 1, JSEXN_TYPEERR, "{0} is not extensible")
MSG_DEF(JSMSG_CANT_REDEFINE_PROP,     240, 1, JSEXN_TYPEERR, "can't redefine non-configurable property '{0}'")
MSG_DEF(JSMSG_CANT_APPEND_TO_ARRAY,   241, 0, JSEXN_TYPEERR, "can't add elements past the end of an array if its length property is unwritable")
MSG_DEF(JSMSG_CANT_DEFINE_ARRAY_LENGTH,242, 0, JSEXN_INTERNALERR, "defining the length property on an array is not currently supported")
MSG_DEF(JSMSG_CANT_DEFINE_ARRAY_INDEX,243, 0, JSEXN_TYPEERR, "can't define array index property")
MSG_DEF(JSMSG_TYPED_ARRAY_BAD_INDEX,  244, 0, JSEXN_ERR, "invalid or out-of-range index")
MSG_DEF(JSMSG_TYPED_ARRAY_NEGATIVE_ARG, 245, 1, JSEXN_ERR, "argument {0} must be >= 0")
MSG_DEF(JSMSG_TYPED_ARRAY_BAD_ARGS,   246, 0, JSEXN_ERR, "invalid arguments")
MSG_DEF(JSMSG_CSP_BLOCKED_FUNCTION,   247, 0, JSEXN_ERR, "call to Function() blocked by CSP")
MSG_DEF(JSMSG_BAD_GET_SET_FIELD,      248, 1, JSEXN_TYPEERR, "property descriptor's {0} field is neither undefined nor a function")
MSG_DEF(JSMSG_BAD_PROXY_FIX,          249, 0, JSEXN_TYPEERR, "proxy was fixed while executing the handler")
MSG_DEF(JSMSG_INVALID_EVAL_SCOPE_ARG, 250, 0, JSEXN_EVALERR, "invalid eval scope argument")
MSG_DEF(JSMSG_ACCESSOR_WRONG_ARGS,    251, 3, JSEXN_SYNTAXERR, "{0} functions must have {1} argument{2}")
MSG_DEF(JSMSG_THROW_TYPE_ERROR,       252, 0, JSEXN_TYPEERR, "'caller', 'callee', and 'arguments' properties may not be accessed on strict mode functions or the arguments objects for calls to them")
MSG_DEF(JSMSG_BAD_TOISOSTRING_PROP,   253, 0, JSEXN_TYPEERR, "toISOString property is not callable")
MSG_DEF(JSMSG_BAD_PARSE_NODE,         254, 0, JSEXN_INTERNALERR, "bad parse node")
MSG_DEF(JSMSG_NOT_EXPECTED_TYPE,      255, 3, JSEXN_TYPEERR, "{0}: expected {1}, got {2}")
MSG_DEF(JSMSG_CALLER_IS_STRICT,       256, 0, JSEXN_TYPEERR, "access to strict mode caller function is censored")
MSG_DEF(JSMSG_NEED_DEBUG_MODE,        257, 0, JSEXN_ERR, "function can be called only in debug mode")
MSG_DEF(JSMSG_STRICT_CODE_LET_EXPR_STMT, 258, 0, JSEXN_ERR, "strict mode code may not contain unparenthesized let expression statements")
MSG_DEF(JSMSG_CANT_CHANGE_EXTENSIBILITY, 259, 0, JSEXN_TYPEERR, "can't change object's extensibility")
MSG_DEF(JSMSG_SC_BAD_SERIALIZED_DATA, 260, 1, JSEXN_INTERNALERR, "bad serialized structured data ({0})")
MSG_DEF(JSMSG_SC_UNSUPPORTED_TYPE,    261, 0, JSEXN_TYPEERR, "unsupported type for structured data")
MSG_DEF(JSMSG_SC_RECURSION,           262, 0, JSEXN_INTERNALERR, "recursive object")
MSG_DEF(JSMSG_CANT_WRAP_XML_OBJECT,   263, 0, JSEXN_TYPEERR, "can't wrap XML objects")
MSG_DEF(JSMSG_BAD_CLONE_VERSION,      264, 0, JSEXN_ERR, "unsupported structured clone version")
MSG_DEF(JSMSG_CANT_CLONE_OBJECT,      265, 0, JSEXN_TYPEERR, "can't clone object")
MSG_DEF(JSMSG_NON_NATIVE_SCOPE,       266, 0, JSEXN_TYPEERR, "non-native scope object")
MSG_DEF(JSMSG_STRICT_FUNCTION_STATEMENT, 267, 0, JSEXN_SYNTAXERR, "in strict mode code, functions may be declared only at top level or immediately within another function")
MSG_DEF(JSMSG_INVALID_FOR_IN_INIT,    268, 0, JSEXN_SYNTAXERR, "for-in loop let declaration may not have an initializer")
MSG_DEF(JSMSG_CLEARED_SCOPE,          269, 0, JSEXN_TYPEERR, "attempt to run compile-and-go script on a cleared scope")
MSG_DEF(JSMSG_MALFORMED_ESCAPE,       270, 1, JSEXN_SYNTAXERR, "malformed {0} character escape sequence")
MSG_DEF(JSMSG_BAD_GENEXP_BODY,        271, 1, JSEXN_SYNTAXERR, "illegal use of {0} in generator expression")
MSG_DEF(JSMSG_XML_PROTO_FORBIDDEN,    272, 0, JSEXN_TYPEERR, "can't set prototype of an object to an XML value")
MSG_DEF(JSMSG_UNNAMED_FUNCTION_STMT,  273, 0, JSEXN_SYNTAXERR, "function statement requires a name")
MSG_DEF(JSMSG_CCW_REQUIRED,           274, 1, JSEXN_TYPEERR, "{0}: argument must be an object from a different compartment")
MSG_DEF(JSMSG_DEBUG_BAD_RESUMPTION,   275, 0, JSEXN_TYPEERR, "debugger resumption value must be undefined, {throw: val}, {return: val}, or null")
MSG_DEF(JSMSG_ASSIGN_FUNCTION_OR_NULL, 276, 1, JSEXN_TYPEERR, "value assigned to {0} must be a function or null")
MSG_DEF(JSMSG_DEBUG_NOT_LIVE,         277, 1, JSEXN_ERR, "{0} is not live")
MSG_DEF(JSMSG_DEBUG_OBJECT_WRONG_OWNER, 278, 0, JSEXN_TYPEERR, "Debugger.Object belongs to a different Debugger")
MSG_DEF(JSMSG_DEBUG_OBJECT_PROTO,     279, 0, JSEXN_TYPEERR, "Debugger.Object.prototype is not a valid Debugger.Object")
MSG_DEF(JSMSG_DEBUG_LOOP,             280, 0, JSEXN_TYPEERR, "cannot debug an object in same compartment as debugger or a compartment that is already debugging the debugger")
MSG_DEF(JSMSG_DEBUG_NOT_IDLE,         281, 0, JSEXN_ERR, "can't start debugging: a debuggee script is on the stack")
MSG_DEF(JSMSG_DEBUG_BAD_OFFSET,       282, 0, JSEXN_TYPEERR, "invalid script offset")
MSG_DEF(JSMSG_DEBUG_BAD_LINE,         283, 0, JSEXN_TYPEERR, "invalid line number")
MSG_DEF(JSMSG_DEBUG_NOT_DEBUGGING,    284, 0, JSEXN_ERR, "can't set breakpoint: script global is not a debuggee")
MSG_DEF(JSMSG_DEBUG_COMPARTMENT_MISMATCH, 285, 2, JSEXN_TYPEERR, "{0}: descriptor .{1} property is an object in a different compartment than the target object")
MSG_DEF(JSMSG_DEBUG_NOT_SCRIPT_FRAME, 286, 0, JSEXN_ERR, "stack frame is not running JavaScript code")
MSG_DEF(JSMSG_CANT_WATCH_PROP,        287, 0, JSEXN_TYPEERR, "properties whose names are objects can't be watched")
MSG_DEF(JSMSG_CSP_BLOCKED_EVAL,       288, 0, JSEXN_ERR, "call to eval() blocked by CSP")
MSG_DEF(JSMSG_DEBUG_NO_SCOPE_OBJECT,  289, 0, JSEXN_TYPEERR, "declarative Environments don't have binding objects")
MSG_DEF(JSMSG_EMPTY_CONSEQUENT,       290, 0, JSEXN_SYNTAXERR, "mistyped ; after conditional?")
MSG_DEF(JSMSG_NOT_ITERABLE,           291, 1, JSEXN_TYPEERR, "{0} is not iterable")
