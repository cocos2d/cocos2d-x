/* ========================================================================== */
/*   Lexical Analyzer                                                         */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <locale.h>
#include <string.h>

#define KILLA_CORE

#include "killa.h"

#include "kctype.h"
#include "kdo.h"
#include "klex.h"
#include "kobject.h"
#include "kparser.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"
#include "kzio.h"



#define next(ls) (ls->current = killa_zgetc(ls->z))



#define currIsNewline(ls)	(ls->current == '\n' || ls->current == '\r')


/* ORDER RESERVED */
static const char *const killaX_tokens [] = {
    "break", "do", "each",
    "else", "false", "for", "function", "goto",
    "if", "in", "null", "private", "public",
    "return", "to", "true", "var", "while", 
    /* FUTURE RESERVED */
    "case", "catch", "class", "const", "continue", 
    "default", "extends", "finally", "implements", "import",
    "interface", "new", "object", "override", "protected", 
    "super", "switch", "throw", "try", "undefined", 
    "void",
    /* other terminal symbols */
    "!", "&&", "||", "**", "::", 
    "..", "...", "==", ">=", "<=", "!=",
    "+=", "-=", "*=", "/=", "%=",
    "<eof>", "<number>", "<name>", "<string>"
};


#define save_and_next(ls) (save(ls, ls->current), next(ls))


static killa_noret lexerror (killa_LexState *ls, const char *msg, int token);


static void save (killa_LexState *ls, int c) {
  killa_Mbuffer *b = ls->buff;
  if (killaZ_bufflen(b) + 1 > killaZ_sizebuffer(b)) {
    size_t newsize;
    if (killaZ_sizebuffer(b) >= KILLA_MAX_SIZET/2)
      lexerror(ls, "lexical element too long", 0);
    newsize = killaZ_sizebuffer(b) * 2;
    killaZ_resizebuffer(ls->L, b, newsize);
  }
  b->buffer[killaZ_bufflen(b)++] = killa_cast(char, c);
}


void killaX_init (killa_State *L) {
  int i;
  for (i=0; i<KILLA_NUM_RESERVED; i++) {
    killa_TString *ts = killaS_new(L, killaX_tokens[i]);
    killaS_fix(ts);  /* reserved words are never collected */
    ts->tsv.reserved = killa_cast_byte(i+1);  /* reserved word */
  }
}


const char *killaX_token2str (killa_LexState *ls, int token) {
  if (token < KILLA_FIRST_RESERVED) {
    killa_assert(token == killa_cast(unsigned char, token));
    return (killa_isprint(token)) ? killaO_pushfstring(ls->L, KILLA_QL("%c"), token) :
                              killaO_pushfstring(ls->L, "char(%d)", token);
  }
  else {
    const char *s = killaX_tokens[token - KILLA_FIRST_RESERVED];
    if (token < TK_EOS)
      return killaO_pushfstring(ls->L, KILLA_QS, s);
    else
      return s;
  }
}


static const char *txtToken (killa_LexState *ls, int token) {
  switch (token) {
    case TK_NAME:
    case TK_STRING:
    case TK_NUMBER:
      save(ls, '\0');
      return killaO_pushfstring(ls->L, KILLA_QS, killaZ_buffer(ls->buff));
    default:
      return killaX_token2str(ls, token);
  }
}


static killa_noret lexerror (killa_LexState *ls, const char *msg, int token) {
  char buff[KILLA_IDSIZE];
  killaO_chunkid(buff, killa_getstr(ls->source), KILLA_IDSIZE);
  msg = killaO_pushfstring(ls->L, "%s:%d: %s", buff, ls->linenumber, msg);
  if (token)
    killaO_pushfstring(ls->L, "%s near %s", msg, txtToken(ls, token));
  killaD_throw(ls->L, KILLA_ERRSYNTAX);
}


killa_noret killaX_syntaxerror (killa_LexState *ls, const char *msg) {
  lexerror(ls, msg, ls->t.token);
}


/*
** creates a new string and anchors it in function's table so that
** it will not be collected until the end of the function's compilation
** (by that time it should be anchored in function's prototype)
*/
killa_TString *killaX_newstring (killa_LexState *ls, const char *str, size_t l) {
  killa_State *L = ls->L;
  killa_TValue *o;  /* entry for `str' */
  killa_TString *ts = killaS_newlstr(L, str, l);  /* create new string */
  killa_setsvalue2s(L, L->top++, ts);  /* temporarily anchor it in stack */
  o = killaH_set(L, ls->fs->h, L->top - 1);
  if (killa_ttisnil(o)) {  /* not in use yet? (see 'addK') */
    /* boolean value does not need GC barrier;
       table has no metatable, so it does not need to invalidate cache */
    killa_setbvalue(o, 1);  /* t[string] = true */
    killaC_checkGC(L);
  }
  L->top--;  /* remove string from stack */
  return ts;
}


/*
** increment line number and skips newline sequence (any of
** \n, \r, \n\r, or \r\n)
*/
static void inclinenumber (killa_LexState *ls) {
  int old = ls->current;
  killa_assert(currIsNewline(ls));
  next(ls);  /* skip `\n' or `\r' */
  if (currIsNewline(ls) && ls->current != old)
    next(ls);  /* skip `\n\r' or `\r\n' */
  if (++ls->linenumber >= KILLA_MAX_INT)
    killaX_syntaxerror(ls, "chunk has too many lines");
}


void killaX_setinput (killa_State *L, killa_LexState *ls, killa_ZIO *z, killa_TString *source,
                    int firstchar) {
  ls->decpoint = '.';
  ls->L = L;
  ls->current = firstchar;
  ls->lookahead.token = TK_EOS;  /* no look-ahead token */
  ls->z = z;
  ls->fs = NULL;
  ls->linenumber = 1;
  ls->lastline = 1;
  ls->source = source;
  ls->envn = killaS_new(L, KILLA_ENV);  /* create env name */
  killaS_fix(ls->envn);  /* never collect this name */
  killaZ_resizebuffer(ls->L, ls->buff, KILLA_MINBUFFER);  /* initialize buffer */
}



/*
** =======================================================
** LEXICAL ANALYZER
** =======================================================
*/



static int check_next (killa_LexState *ls, const char *set) {
  if (ls->current == '\0' || !strchr(set, ls->current))
    return 0;
  save_and_next(ls);
  return 1;
}


/*
** change all characters 'from' in buffer to 'to'
*/
static void buffreplace (killa_LexState *ls, char from, char to) {
  size_t n = killaZ_bufflen(ls->buff);
  char *p = killaZ_buffer(ls->buff);
  while (n--)
    if (p[n] == from) p[n] = to;
}


#if !defined(getlocaledecpoint)
#define getlocaledecpoint()	(localeconv()->decimal_point[0])
#endif


#define buff2d(b,e)	killaO_str2d(killaZ_buffer(b), killaZ_bufflen(b) - 1, e)

/*
** in case of format error, try to change decimal point separator to
** the one defined in the current locale and check again
*/
static void trydecpoint (killa_LexState *ls, killa_SemInfo *seminfo) {
  char old = ls->decpoint;
  ls->decpoint = getlocaledecpoint();
  buffreplace(ls, old, ls->decpoint);  /* try new decimal separator */
  if (!buff2d(ls->buff, &seminfo->r)) {
    /* format error with correct decimal point: no more options */
    buffreplace(ls, ls->decpoint, '.');  /* undo change (for error message) */
    lexerror(ls, "malformed number", TK_NUMBER);
  }
}


/* KILLA_NUMBER */
static void read_numeral (killa_LexState *ls, killa_SemInfo *seminfo) {
  killa_assert(killa_isdigit(ls->current) || (ls->current == '_'));
  do {
    if(ls->current == '_')
      next(ls); /* ignore underscores */
    else
      save_and_next(ls);

    if (check_next(ls, "EePp"))  /* exponent part? */
      check_next(ls, "+-");  /* optional exponent sign */
  } while (killa_islalnum(ls->current) || (ls->current == '.') || (ls->current == '_'));
  save(ls, '\0');
  buffreplace(ls, '.', ls->decpoint);  /* follow locale for decimal point */
  if (!buff2d(ls->buff, &seminfo->r))  /* format error? */
    trydecpoint(ls, seminfo); /* try to update decimal point separator */
}


/*
** skip a sequence '[=*[' or ']=*]' and return its number of '='s or
** -1 if sequence is malformed
*/
static int skip_sep (killa_LexState *ls) {
  int count = 0;
  int s = ls->current;
  killa_assert(s == '[' || s == ']');
  save_and_next(ls);
  while (ls->current == '=') {
    save_and_next(ls);
    count++;
  }
  return (ls->current == s) ? count : (-count) - 1;
}


static void read_long_string (killa_LexState *ls, killa_SemInfo *seminfo, int sep) {
  save_and_next(ls);  /* skip 2nd `[' */
  if (currIsNewline(ls))  /* string starts with a newline? */
    inclinenumber(ls);  /* skip it */
  for (;;) {
    switch (ls->current) {
      case KILLA_EOZ:
        lexerror(ls, (seminfo) ? "unfinished long string" :
                                 "unfinished long comment", TK_EOS);
        break;  /* to avoid warnings */
      case ']': {
        if (skip_sep(ls) == sep) {
          save_and_next(ls);  /* skip 2nd `]' */
          goto endloop;
        }
        break;
      }
      case '\n': case '\r': {
        save(ls, '\n');
        inclinenumber(ls);
        if (!seminfo) killaZ_resetbuffer(ls->buff);  /* avoid wasting space */
        break;
      }
      default: {
        if (seminfo) save_and_next(ls);
        else next(ls);
      }
    }
  } endloop:
  if (seminfo)
    seminfo->ts = killaX_newstring(ls, killaZ_buffer(ls->buff) + (2 + sep),
                                     killaZ_bufflen(ls->buff) - 2*(2 + sep));
}


static void escerror (killa_LexState *ls, int *c, int n, const char *msg) {
  int i;
  killaZ_resetbuffer(ls->buff);  /* prepare error message */
  save(ls, '\\');
  for (i = 0; i < n && c[i] != KILLA_EOZ; i++)
    save(ls, c[i]);
  lexerror(ls, msg, TK_STRING);
}


static int readhexaesc (killa_LexState *ls) {
  int c[3], i;  /* keep input for error message */
  int r = 0;  /* result accumulator */
  c[0] = 'x';  /* for error message */
  for (i = 1; i < 3; i++) {  /* read two hexa digits */
    c[i] = next(ls);
    if (!killa_isxdigit(c[i]))
      escerror(ls, c, i + 1, "hexadecimal digit expected");
    r = (r << 4) + killaO_hexavalue(c[i]);
  }
  return r;
}


static int readdecesc (killa_LexState *ls) {
  int c[3], i;
  int r = 0;  /* result accumulator */
  for (i = 0; i < 3 && killa_isdigit(ls->current); i++) {  /* read up to 3 digits */
    c[i] = ls->current;
    r = 10*r + c[i] - '0';
    next(ls);
  }
  if (r > UCHAR_MAX)
    escerror(ls, c, i, "decimal escape too large");
  return r;
}


static void read_string (killa_LexState *ls, int del, killa_SemInfo *seminfo) {
  save_and_next(ls);  /* keep delimiter (for error messages) */
  while (ls->current != del) {
    switch (ls->current) {
      case KILLA_EOZ:
        lexerror(ls, "unfinished string", TK_EOS);
        break;  /* to avoid warnings */
      case '\n':
      case '\r':
        lexerror(ls, "unfinished string", TK_STRING);
        break;  /* to avoid warnings */
      case '\\': {  /* escape sequences */
        int c;  /* final character to be saved */
        next(ls);  /* do not save the `\' */
        switch (ls->current) {
          case 'a': c = '\a'; goto read_save;
          case 'b': c = '\b'; goto read_save;
          case 'f': c = '\f'; goto read_save;
          case 'n': c = '\n'; goto read_save;
          case 'r': c = '\r'; goto read_save;
          case 't': c = '\t'; goto read_save;
          case 'v': c = '\v'; goto read_save;
          case 'x': c = readhexaesc(ls); goto read_save;
          case '\n': case '\r':
            inclinenumber(ls); c = '\n'; goto only_save;
          case '\\': case '\"': case '\'':
            c = ls->current; goto read_save;
          case KILLA_EOZ: goto no_save;  /* will raise an error next loop */
          case 'z': {  /* zap following span of spaces */
            next(ls);  /* skip the 'z' */
            while (killa_isspace(ls->current)) {
              if (currIsNewline(ls)) inclinenumber(ls);
              else next(ls);
            }
            goto no_save;
          }
          default: {
            if (!killa_isdigit(ls->current))
              escerror(ls, &ls->current, 1, "invalid escape sequence");
            /* digital escape \ddd */
            c = readdecesc(ls);
            goto only_save;
          }
        }
       read_save: next(ls);  /* read next character */
       only_save: save(ls, c);  /* save 'c' */
       no_save: break;
      }
      default:
        save_and_next(ls);
    }
  }
  save_and_next(ls);  /* skip delimiter */
  seminfo->ts = killaX_newstring(ls, killaZ_buffer(ls->buff) + 1,
                                   killaZ_bufflen(ls->buff) - 2);
}


static int llex (killa_LexState *ls, killa_SemInfo *seminfo) {
  killaZ_resetbuffer(ls->buff);
  for (;;) {
    switch (ls->current) {
      case '\n': case '\r': {  /* line breaks */
        inclinenumber(ls);
        break;
      }
      case ' ': case '\f': case '\t': case '\v': {  /* spaces */
        next(ls);
        break;
      }
      case '/': {
        next(ls);
        if (ls->current == '/') {
          /* Short comment */
          while (!currIsNewline(ls) && ls->current != KILLA_EOZ) {
            next(ls);  /* skip until end of line (or end of file) */
          }
        }
        else if (ls->current == '*') {
          /* Long comment */
          next(ls);
          for (;;) {
            switch (ls->current) {
              case KILLA_EOZ:
                lexerror(ls, "unfinished long comment", TK_EOS);
                break;  /* to avoid warnings */
              case '*':
                next(ls);
                if (ls->current == '/') {
                  next(ls);
                  goto end_long_comment;
                }
                break;
              case '\n':
              case '\r': {
                save(ls, '\n');
                inclinenumber(ls);
                killaZ_resetbuffer(ls->buff);  /* avoid wasting space */
                break;
              }
              default:
                next(ls);
            }
          }
        }
        else {
          if (ls->current != '=') return '/';
          else { next(ls); return TK_CDIV; }
        }
        end_long_comment: break;
      }
      case '[': {  /* long string or simply '[' */
        int sep = skip_sep(ls);
        if (sep >= 0) {
          read_long_string(ls, seminfo, sep);
          return TK_STRING;
        }
        else if (sep == -1) return '[';
        else lexerror(ls, "invalid long string delimiter", TK_STRING);
      }
      case '+': {
        next(ls);
        if (ls->current != '=') return '+';
        else { next(ls); return TK_CADD; }
      }
      case '-': {
        next(ls);
        if (ls->current != '=') return '-';
        else { next(ls); return TK_CSUB; }
      }
      case '*': {
        next(ls);
        if (ls->current == '=') { 
            next(ls);
            return TK_CMUL;
        }
        if (ls->current != '*') return '*';
        else { next(ls); return TK_POW; }
      }
      case '%': {
        next(ls);
        if (ls->current != '=') return '%';
        else { next(ls); return TK_CMOD; }
      }
      case '=': {
        next(ls);
        if (ls->current != '=') return '=';
        else { next(ls); return TK_EQ; }
      }
      case '<': {
        next(ls);
        if (ls->current != '=') return '<';
        else { next(ls); return TK_LE; }
      }
      case '>': {
        next(ls);
        if (ls->current != '=') return '>';
        else { next(ls); return TK_GE; }
      }
      case '!': {
        next(ls);
        if (ls->current != '=') return TK_NOT;
        else { next(ls); return TK_NE; }
      }
      case '&': {
        next(ls);
        if (ls->current != '&') return '&';
        else { next(ls); return TK_AND; }
      }
      case '|': {
        next(ls);
        if (ls->current != '|') return '|';
        else { next(ls); return TK_OR; }
      }
      case ':': {
        next(ls);
        if (ls->current != ':') return ':';
        else { next(ls); return TK_DBCOLON; }
      }
      case '"': case '\'': {  /* short literal strings */
        read_string(ls, ls->current, seminfo);
        return TK_STRING;
      }
      case '.': {  /* '.', '..', '...', or number */
        save_and_next(ls);
        if (check_next(ls, ".")) {
          if (check_next(ls, "."))
            return TK_DOTS;   /* '...' */
          else return TK_CONCAT;   /* '..' */
        }
        else if (!killa_isdigit(ls->current)) return '.';
        /* else go through */
      }
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': {
        read_numeral(ls, seminfo);
        return TK_NUMBER;
      }
      case KILLA_EOZ: {
        return TK_EOS;
      }
      default: {
        if (killa_islalpha(ls->current)) {  /* identifier or reserved word? */
          killa_TString *ts;
          do {
            save_and_next(ls);
          } while (killa_islalnum(ls->current));
          ts = killaX_newstring(ls, killaZ_buffer(ls->buff),
                                  killaZ_bufflen(ls->buff));
          seminfo->ts = ts;
          if (ts->tsv.reserved > 0) { /* reserved word? */
            int tokenid = ts->tsv.reserved + KILLA_FIRST_RESERVED - 1;
            /* FUTURE RESERVED */
            if ((tokenid >= TK_CASE) && (tokenid <= TK_VOID)) {
              const char *msg = killaO_pushfstring(ls->L, "using not implemented word " KILLA_QS, killa_getstr(ts));
              lexerror(ls, msg, 0);
            }
            else {
              return tokenid;
            }
          }
          else {
            return TK_NAME;
          }
        }
        else {  /* single-char tokens (+ - / ...) */
          int c = ls->current;
          next(ls);
          return c;
        }
      }
    }
  }
}


void killaX_next (killa_LexState *ls) {
  ls->lastline = ls->linenumber;
  if (ls->lookahead.token != TK_EOS) {  /* is there a look-ahead token? */
    ls->t = ls->lookahead;  /* use this one */
    ls->lookahead.token = TK_EOS;  /* and discharge it */
  }
  else
    ls->t.token = llex(ls, &ls->t.seminfo);  /* read next token */
}


int killaX_lookahead (killa_LexState *ls) {
  killa_assert(ls->lookahead.token == TK_EOS);
  ls->lookahead.token = llex(ls, &ls->lookahead.seminfo);
  return ls->lookahead.token;
}

