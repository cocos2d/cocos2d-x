/* ========================================================================== */
/*   Lexical Analyzer                                                         */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KLEX_H_
#define KLEX_H_

#include "kobject.h"
#include "kzio.h"


#define KILLA_FIRST_RESERVED    257



/*
* WARNING: if you change the order of this enumeration,
* grep "ORDER RESERVED"
*/
enum KILLA_RESERVED {
  /* terminal symbols denoted by reserved words */
  TK_BREAK = KILLA_FIRST_RESERVED, TK_DO, TK_EACH, 
  TK_ELSE, TK_FALSE, TK_FOR, TK_FUNCTION, TK_GOTO, 
  TK_IF, TK_IN, TK_NULL, TK_PRIVATE, TK_PUBLIC, 
  TK_RETURN, TK_TO, TK_TRUE, TK_VAR, TK_WHILE, 
  /* FUTURE RESERVED */
  TK_CASE, TK_CATCH, TK_CLASS, TK_CONST, TK_CONTINUE, 
  TK_DEFAULT, TK_EXTENDS, TK_FINALLY, TK_IMPLEMENTS, TK_IMPORT,
  TK_INTERFACE, TK_NEW, TK_OBJECT, TK_OVERRIDE, TK_PROTECTED, 
  TK_SUPER, TK_SWITCH, TK_THROW, TK_TRY, TK_UNDEFINED, 
  TK_VOID,
  /* other terminal symbols */
  TK_NOT, TK_AND, TK_OR, TK_POW, TK_DBCOLON, 
  TK_CONCAT, TK_DOTS, TK_EQ, TK_GE, TK_LE, TK_NE, 
  TK_CADD, TK_CSUB, TK_CMUL, TK_CDIV, TK_CMOD,
  TK_EOS, TK_NUMBER, TK_NAME, TK_STRING
};

/* number of reserved words */
#define KILLA_NUM_RESERVED	(killa_cast(int, TK_VOID - KILLA_FIRST_RESERVED + 1))


typedef union {
  killa_Number r;
  killa_TString *ts;
} killa_SemInfo;  /* semantics information */


typedef struct killa_Token {
  int token;
  killa_SemInfo seminfo;
} killa_Token;


/* state of the lexer plus state of the parser when shared by all
   functions */
typedef struct killa_LexState {
  int current;  /* current character (charint) */
  int linenumber;  /* input line counter */
  int lastline;  /* line of last token `consumed' */
  killa_Token t;  /* current token */
  killa_Token lookahead;  /* look ahead token */
  struct killa_FuncState *fs;  /* current function (parser) */
  struct killa_State *L;
  killa_ZIO *z;  /* input stream */
  killa_Mbuffer *buff;  /* buffer for tokens */
  struct killa_Dyndata *dyd;  /* dynamic structures used by the parser */
  killa_TString *source;  /* current source name */
  killa_TString *envn;  /* environment variable name */
  char decpoint;  /* locale decimal point */
} killa_LexState;


KILLAI_FUNC void killaX_init (killa_State *L);
KILLAI_FUNC void killaX_setinput (killa_State *L, killa_LexState *ls, killa_ZIO *z,
                                  killa_TString *source, int firstchar);
KILLAI_FUNC killa_TString *killaX_newstring (killa_LexState *ls, const char *str, size_t l);
KILLAI_FUNC void killaX_next (killa_LexState *ls);
KILLAI_FUNC int killaX_lookahead (killa_LexState *ls);
KILLAI_FUNC killa_noret killaX_syntaxerror (killa_LexState *ls, const char *s);
KILLAI_FUNC const char *killaX_token2str (killa_LexState *ls, int token);


#endif
