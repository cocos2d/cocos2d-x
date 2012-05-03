/* ========================================================================== */
/*   Standard I/O (and system) library                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

/*
** POSIX idiosyncrasy!
** This definition must come before the inclusion of 'stdio.h'; it
** should not affect non-POSIX systems
*/
#if !defined(_FILE_OFFSET_BITS)
#define _FILE_OFFSET_BITS 64
#endif


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"



/*
** {======================================================
** killa_popen spawns a new process connected to the current
** one through the file streams.
** =======================================================
*/

#if !defined(killa_popen)	/* { */

#if defined(KILLA_USE_POPEN)	/* { */

#define killa_popen(L,c,m)	((void)L, fflush(NULL), popen(c,m))
#define killa_pclose(L,file)	((void)L, pclose(file))

#elif defined(KILLA_WIN)		/* }{ */

#define killa_popen(L,c,m)		((void)L, _popen(c,m))
#define killa_pclose(L,file)		((void)L, _pclose(file))


#else				/* }{ */

#define killa_popen(L,c,m)		((void)((void)c, m),  \
		killaL_error(L, KILLA_QL("popen") " not supported"), (FILE*)0)
#define killa_pclose(L,file)		((void)((void)L, file), -1)


#endif				/* } */

#endif			/* } */

/* }====================================================== */


/*
** {======================================================
** killa_fseek/killa_ftell: configuration for longer offsets
** =======================================================
*/

#if !defined(killa_fseek)	/* { */

#if defined(KILLA_USE_POSIX)

#define l_fseek(f,o,w)		fseeko(f,o,w)
#define l_ftell(f)		ftello(f)
#define l_seeknum		off_t

#elif defined(KILLA_WIN) && !defined(_CRTIMP_TYPEINFO) \
   && defined(_MSC_VER) && (_MSC_VER >= 1400)
/* Windows (but not DDK) and Visual C++ 2005 or higher */

#define l_fseek(f,o,w)		_fseeki64(f,o,w)
#define l_ftell(f)		_ftelli64(f)
#define l_seeknum		__int64

#else

#define l_fseek(f,o,w)		fseek(f,o,w)
#define l_ftell(f)		ftell(f)
#define l_seeknum		long

#endif

#endif			/* } */

/* }====================================================== */


#define IO_PREFIX	"_IO_"
#define IO_INPUT	(IO_PREFIX "input")
#define IO_OUTPUT	(IO_PREFIX "output")


typedef killaL_Stream LStream;


#define tolstream(L)	((LStream *)killaL_checkudata(L, 1, KILLA_FILEHANDLE))

#define isclosed(p)	((p)->closef == NULL)


static int io_type (killa_State *L) {
  LStream *p;
  killaL_checkany(L, 1);
  p = (LStream *)killaL_testudata(L, 1, KILLA_FILEHANDLE);
  if (p == NULL)
    killa_pushnull(L);  /* not a file */
  else if (isclosed(p))
    killa_pushliteral(L, "closed file");
  else
    killa_pushliteral(L, "file");
  return 1;
}


static int f_tostring (killa_State *L) {
  LStream *p = tolstream(L);
  if (isclosed(p))
    killa_pushliteral(L, "file (closed)");
  else
    killa_pushfstring(L, "file (%p)", p->f);
  return 1;
}


static FILE *tofile (killa_State *L) {
  LStream *p = tolstream(L);
  if (isclosed(p))
    killaL_error(L, "attempt to use a closed file");
  killa_assert(p->f);
  return p->f;
}


/*
** When creating file handles, always creates a `closed' file handle
** before opening the actual file; so, if there is a memory error, the
** file is not left opened.
*/
static LStream *newprefile (killa_State *L) {
  LStream *p = (LStream *)killa_newuserdata(L, sizeof(LStream));
  p->closef = NULL;  /* mark file handle as 'closed' */
  killaL_setmetatable(L, KILLA_FILEHANDLE);
  return p;
}


static int aux_close (killa_State *L) {
  LStream *p = tolstream(L);
  killa_CFunction cf = p->closef;
  p->closef = NULL;  /* mark stream as closed */
  return (*cf)(L);  /* close it */
}


static int io_close (killa_State *L) {
  if (killa_isnone(L, 1))  /* no argument? */
    killa_getfield(L, KILLA_REGISTRYINDEX, IO_OUTPUT);  /* use standard output */
  tofile(L);  /* make sure argument is an open stream */
  return aux_close(L);
}


static int f_gc (killa_State *L) {
  LStream *p = tolstream(L);
  if (!isclosed(p) && p->f != NULL)
    aux_close(L);  /* ignore closed and incompletely open files */
  return 0;
}


/*
** function to close regular files
*/
static int io_fclose (killa_State *L) {
  LStream *p = tolstream(L);
  int res = fclose(p->f);
  return killaL_fileresult(L, (res == 0), NULL);
}


static LStream *newfile (killa_State *L) {
  LStream *p = newprefile(L);
  p->f = NULL;
  p->closef = &io_fclose;
  return p;
}


static void opencheck (killa_State *L, const char *fname, const char *mode) {
  LStream *p = newfile(L);
  p->f = fopen(fname, mode);
  if (p->f == NULL)
    killaL_error(L, "cannot open file " KILLA_QS " (%s)", fname, strerror(errno));
}


static int io_open (killa_State *L) {
  const char *filename = killaL_checkstring(L, 1);
  const char *mode = killaL_optstring(L, 2, "r");
  LStream *p = newfile(L);
  int i = 0;
  /* check whether 'mode' matches '[rwa]%+?b?' */
  if (!(mode[i] != '\0' && strchr("rwa", mode[i++]) != NULL &&
       (mode[i] != '+' || ++i) &&  /* skip if char is '+' */
       (mode[i] != 'b' || ++i) &&  /* skip if char is 'b' */
       (mode[i] == '\0')))
    return killaL_error(L, "invalid mode " KILLA_QS
                         " (should match " KILLA_QL("[rwa]%%+?b?") ")", mode);
  p->f = fopen(filename, mode);
  return (p->f == NULL) ? killaL_fileresult(L, 0, filename) : 1;
}


/*
** function to close 'popen' files
*/
static int io_pclose (killa_State *L) {
  LStream *p = tolstream(L);
  return killaL_execresult(L, killa_pclose(L, p->f));
}


static int io_popen (killa_State *L) {
  const char *filename = killaL_checkstring(L, 1);
  const char *mode = killaL_optstring(L, 2, "r");
  LStream *p = newprefile(L);
  p->f = killa_popen(L, filename, mode);
  p->closef = &io_pclose;
  return (p->f == NULL) ? killaL_fileresult(L, 0, filename) : 1;
}


static int io_tmpfile (killa_State *L) {
  LStream *p = newfile(L);
  p->f = tmpfile();
  return (p->f == NULL) ? killaL_fileresult(L, 0, NULL) : 1;
}


static FILE *getiofile (killa_State *L, const char *findex) {
  LStream *p;
  killa_getfield(L, KILLA_REGISTRYINDEX, findex);
  p = (LStream *)killa_touserdata(L, -1);
  if (isclosed(p))
    killaL_error(L, "standard %s file is closed", findex + strlen(IO_PREFIX));
  return p->f;
}


static int g_iofile (killa_State *L, const char *f, const char *mode) {
  if (!killa_isnoneornull(L, 1)) {
    const char *filename = killa_tostring(L, 1);
    if (filename)
      opencheck(L, filename, mode);
    else {
      tofile(L);  /* check that it's a valid file handle */
      killa_pushvalue(L, 1);
    }
    killa_setfield(L, KILLA_REGISTRYINDEX, f);
  }
  /* return current value */
  killa_getfield(L, KILLA_REGISTRYINDEX, f);
  return 1;
}


static int io_input (killa_State *L) {
  return g_iofile(L, IO_INPUT, "r");
}


static int io_output (killa_State *L) {
  return g_iofile(L, IO_OUTPUT, "w");
}


static int io_readline (killa_State *L);


static void aux_lines (killa_State *L, int toclose) {
  int i;
  int n = killa_gettop(L) - 1;  /* number of arguments to read */
  /* ensure that arguments will fit here and into 'io_readline' stack */
  killaL_argcheck(L, n <= KILLA_MINSTACK - 3, KILLA_MINSTACK - 3, "too many options");
  killa_pushvalue(L, 1);  /* file handle */
  killa_pushinteger(L, n);  /* number of arguments to read */
  killa_pushboolean(L, toclose);  /* close/not close file when finished */
  for (i = 1; i <= n; i++) killa_pushvalue(L, i + 1);  /* copy arguments */
  killa_pushcclosure(L, io_readline, 3 + n);
}


static int f_lines (killa_State *L) {
  tofile(L);  /* check that it's a valid file handle */
  aux_lines(L, 0);
  return 1;
}


static int io_lines (killa_State *L) {
  int toclose;
  if (killa_isnone(L, 1)) killa_pushnull(L);  /* at least one argument */
  if (killa_isnull(L, 1)) {  /* no file name? */
    killa_getfield(L, KILLA_REGISTRYINDEX, IO_INPUT);  /* get default input */
    killa_replace(L, 1);  /* put it at index 1 */
    tofile(L);  /* check that it's a valid file handle */
    toclose = 0;  /* do not close it after iteration */
  }
  else {  /* open a new file */
    const char *filename = killaL_checkstring(L, 1);
    opencheck(L, filename, "r");
    killa_replace(L, 1);  /* put file at index 1 */
    toclose = 1;  /* close it after iteration */
  }
  aux_lines(L, toclose);
  return 1;
}


/*
** {======================================================
** READ
** =======================================================
*/


static int read_number (killa_State *L, FILE *f) {
  killa_Number d;
  if (fscanf(f, KILLA_NUMBER_SCAN, &d) == 1) {
    killa_pushnumber(L, d);
    return 1;
  }
  else {
   killa_pushnull(L);  /* "result" to be removed */
   return 0;  /* read fails */
  }
}


static int test_eof (killa_State *L, FILE *f) {
  int c = getc(f);
  ungetc(c, f);
  killa_pushlstring(L, NULL, 0);
  return (c != EOF);
}


static int read_line (killa_State *L, FILE *f, int chop) {
  killaL_Buffer b;
  killaL_buffinit(L, &b);
  for (;;) {
    size_t l;
    char *p = killaL_prepbuffer(&b);
    if (fgets(p, KILLAL_BUFFERSIZE, f) == NULL) {  /* eof? */
      killaL_pushresult(&b);  /* close buffer */
      return (killa_rawlen(L, -1) > 0);  /* check whether read something */
    }
    l = strlen(p);
    if (l == 0 || p[l-1] != '\n')
      killaL_addsize(&b, l);
    else {
      killaL_addsize(&b, l - chop);  /* chop 'eol' if needed */
      killaL_pushresult(&b);  /* close buffer */
      return 1;  /* read at least an `eol' */
    }
  }
}


#define MAX_SIZE_T	(~(size_t)0)

static void read_all (killa_State *L, FILE *f) {
  size_t rlen = KILLAL_BUFFERSIZE;  /* how much to read in each cycle */
  killaL_Buffer b;
  killaL_buffinit(L, &b);
  for (;;) {
    char *p = killaL_prepbuffsize(&b, rlen);
    size_t nr = fread(p, sizeof(char), rlen, f);
    killaL_addsize(&b, nr);
    if (nr < rlen) break;  /* eof? */
    else if (rlen <= (MAX_SIZE_T / 4))  /* avoid buffers too large */
      rlen *= 2;  /* double buffer size at each iteration */
  }
  killaL_pushresult(&b);  /* close buffer */
}


static int read_chars (killa_State *L, FILE *f, size_t n) {
  size_t nr;  /* number of chars actually read */
  char *p;
  killaL_Buffer b;
  killaL_buffinit(L, &b);
  p = killaL_prepbuffsize(&b, n);  /* prepare buffer to read whole block */
  nr = fread(p, sizeof(char), n, f);  /* try to read 'n' chars */
  killaL_addsize(&b, nr);
  killaL_pushresult(&b);  /* close buffer */
  return (nr > 0);  /* true iff read something */
}


static int g_read (killa_State *L, FILE *f, int first) {
  int nargs = killa_gettop(L) - 1;
  int success;
  int n;
  clearerr(f);
  if (nargs == 0) {  /* no arguments? */
    success = read_line(L, f, 1);
    n = first+1;  /* to return 1 result */
  }
  else {  /* ensure stack space for all results and for auxlib's buffer */
    killaL_checkstack(L, nargs+KILLA_MINSTACK, "too many arguments");
    success = 1;
    for (n = first; nargs-- && success; n++) {
      if (killa_type(L, n) == KILLA_TNUMBER) {
        size_t l = (size_t)killa_tointeger(L, n);
        success = (l == 0) ? test_eof(L, f) : read_chars(L, f, l);
      }
      else {
        const char *p = killa_tostring(L, n);
        killaL_argcheck(L, p && p[0] == '*', n, "invalid option");
        switch (p[1]) {
          case 'n':  /* number */
            success = read_number(L, f);
            break;
          case 'l':  /* line */
            success = read_line(L, f, 1);
            break;
          case 'L':  /* line with end-of-line */
            success = read_line(L, f, 0);
            break;
          case 'a':  /* file */
            read_all(L, f);  /* read entire file */
            success = 1; /* always success */
            break;
          default:
            return killaL_argerror(L, n, "invalid format");
        }
      }
    }
  }
  if (ferror(f))
    return killaL_fileresult(L, 0, NULL);
  if (!success) {
    killa_pop(L, 1);  /* remove last result */
    killa_pushnull(L);  /* push nil instead */
  }
  return n - first;
}


static int io_read (killa_State *L) {
  return g_read(L, getiofile(L, IO_INPUT), 1);
}


static int f_read (killa_State *L) {
  return g_read(L, tofile(L), 2);
}


static int io_readline (killa_State *L) {
  LStream *p = (LStream *)killa_touserdata(L, killa_upvalueindex(1));
  int i;
  int n = (int)killa_tointeger(L, killa_upvalueindex(2));
  if (isclosed(p))  /* file is already closed? */
    return killaL_error(L, "file is already closed");
  killa_settop(L , 1);
  for (i = 1; i <= n; i++)  /* push arguments to 'g_read' */
    killa_pushvalue(L, killa_upvalueindex(3 + i));
  n = g_read(L, p->f, 2);  /* 'n' is number of results */
  killa_assert(n > 0);  /* should return at least a nil */
  if (!killa_isnull(L, -n))  /* read at least one value? */
    return n;  /* return them */
  else {  /* first result is nil: EOF or error */
    if (n > 1) {  /* is there error information? */
      /* 2nd result is error message */
      return killaL_error(L, "%s", killa_tostring(L, -n + 1));
    }
    if (killa_toboolean(L, killa_upvalueindex(3))) {  /* generator created file? */
      killa_settop(L, 0);
      killa_pushvalue(L, killa_upvalueindex(1));
      aux_close(L);  /* close it */
    }
    return 0;
  }
}

/* }====================================================== */


static int g_write (killa_State *L, FILE *f, int arg) {
  int nargs = killa_gettop(L) - arg;
  int status = 1;
  for (; nargs--; arg++) {
    if (killa_type(L, arg) == KILLA_TNUMBER) {
      /* optimization: could be done exactly as for strings */
      status = status &&
          fprintf(f, KILLA_NUMBER_FMT, killa_tonumber(L, arg)) > 0;
    }
    else {
      size_t l;
      const char *s = killaL_checklstring(L, arg, &l);
      status = status && (fwrite(s, sizeof(char), l, f) == l);
    }
  }
  if (status) return 1;  /* file handle already on stack top */
  else return killaL_fileresult(L, status, NULL);
}


static int io_write (killa_State *L) {
  return g_write(L, getiofile(L, IO_OUTPUT), 1);
}


static int f_write (killa_State *L) {
  FILE *f = tofile(L);
  killa_pushvalue(L, 1);  /* push file at the stack top (to be returned) */
  return g_write(L, f, 2);
}


static int f_seek (killa_State *L) {
  static const int mode[] = {SEEK_SET, SEEK_CUR, SEEK_END};
  static const char *const modenames[] = {"set", "cur", "end", NULL};
  FILE *f = tofile(L);
  int op = killaL_checkoption(L, 2, "cur", modenames);
  killa_Number p3 = killaL_optnumber(L, 3, 0);
  l_seeknum offset = (l_seeknum)p3;
  killaL_argcheck(L, (killa_Number)offset == p3, 3,
                  "not an integer in proper range");
  op = l_fseek(f, offset, mode[op]);
  if (op)
    return killaL_fileresult(L, 0, NULL);  /* error */
  else {
    killa_pushnumber(L, (killa_Number)l_ftell(f));
    return 1;
  }
}


static int f_setvbuf (killa_State *L) {
  static const int mode[] = {_IONBF, _IOFBF, _IOLBF};
  static const char *const modenames[] = {"no", "full", "line", NULL};
  FILE *f = tofile(L);
  int op = killaL_checkoption(L, 2, NULL, modenames);
  killa_Integer sz = killaL_optinteger(L, 3, KILLAL_BUFFERSIZE);
  int res = setvbuf(f, NULL, mode[op], sz);
  return killaL_fileresult(L, res == 0, NULL);
}



static int io_flush (killa_State *L) {
  return killaL_fileresult(L, fflush(getiofile(L, IO_OUTPUT)) == 0, NULL);
}


static int f_flush (killa_State *L) {
  return killaL_fileresult(L, fflush(tofile(L)) == 0, NULL);
}


/*
** functions for 'io' library
*/
static const killaL_Reg iolib[] = {
  {"close", io_close},
  {"flush", io_flush},
  {"input", io_input},
  {"lines", io_lines},
  {"open", io_open},
  {"output", io_output},
  {"popen", io_popen},
  {"read", io_read},
  {"tmpfile", io_tmpfile},
  {"type", io_type},
  {"write", io_write},
  {NULL, NULL}
};


/*
** methods for file handles
*/
static const killaL_Reg flib[] = {
  {"close", io_close},
  {"flush", f_flush},
  {"lines", f_lines},
  {"read", f_read},
  {"seek", f_seek},
  {"setvbuf", f_setvbuf},
  {"write", f_write},
  {"__gc", f_gc},
  {"__tostring", f_tostring},
  {NULL, NULL}
};


static void createmeta (killa_State *L) {
  killaL_newmetatable(L, KILLA_FILEHANDLE);  /* create metatable for file handles */
  killa_pushvalue(L, -1);  /* push metatable */
  killa_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  killaL_setfuncs(L, flib, 0);  /* add file methods to new metatable */
  killa_pop(L, 1);  /* pop new metatable */
}


/*
** function to (not) close the standard files stdin, stdout, and stderr
*/
static int io_noclose (killa_State *L) {
  LStream *p = tolstream(L);
  p->closef = &io_noclose;  /* keep file opened */
  killa_pushnull(L);
  killa_pushliteral(L, "cannot close standard file");
  return 2;
}


static void createstdfile (killa_State *L, FILE *f, const char *k,
                           const char *fname) {
  LStream *p = newprefile(L);
  p->f = f;
  p->closef = &io_noclose;
  if (k != NULL) {
    killa_pushvalue(L, -1);
    killa_setfield(L, KILLA_REGISTRYINDEX, k);  /* add file to registry */
  }
  killa_setfield(L, -2, fname);  /* add file to module */
}


KILLAMOD_API int killaopen_io (killa_State *L) {
  killaL_newlib(L, iolib);  /* new module */
  createmeta(L);
  /* create (and set) default files */
  createstdfile(L, stdin, IO_INPUT, "stdin");
  createstdfile(L, stdout, IO_OUTPUT, "stdout");
  createstdfile(L, stderr, NULL, "stderr");
  return 1;
}

