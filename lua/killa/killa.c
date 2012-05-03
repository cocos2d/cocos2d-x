/* ========================================================================== */
/*   Killa stand-alone interpreter                                            */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KILLA_C_

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"

#if !defined(KILLA_PROMPT)
#define KILLA_PROMPT		"> "
#define KILLA_PROMPT2		">> "
#endif

#if !defined(KILLA_PROGNAME)
#define KILLA_PROGNAME		"killa"
#endif

#if !defined(KILLA_ARGS)
#define KILLA_ARGS          "arg"
#endif

#if !defined(KILLA_MAXINPUT)
#define KILLA_MAXINPUT		512
#endif

#if !defined(KILLA_INIT)
#define KILLA_INIT		"KILLA_INIT"
#endif

#define KILLA_INITVERSION  \
	KILLA_INIT "_" KILLA_VERSION_MAJOR "_" KILLA_VERSION_MINOR


/*
** killa_stdin_is_tty detects whether the standard input is a 'tty' (that
** is, whether we're running killa interactively).
*/
#if defined(KILLA_USE_ISATTY)
#include <unistd.h>
#define killa_stdin_is_tty()      isatty(0)
#elif defined(KILLA_WIN)
#include <io.h>
#include <stdio.h>
#define killa_stdin_is_tty()      _isatty(_fileno(stdin))
#else
#define killa_stdin_is_tty()      1  /* assume stdin is a tty */
#endif


/*
** killa_readline defines how to show a prompt and then read a line from
** the standard input.
** killa_saveline defines how to "save" a read line in a "history".
** killa_freeline defines how to free a line read by killa_readline.
*/
#if defined(KILLA_USE_READLINE)

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#define killa_readline(L,b,p)     ((void)L, ((b)=readline(p)) != NULL)
#define killa_saveline(L,idx) \
        if (killa_rawlen(L,idx) > 0)  /* non-empty line? */ \
          add_history(killa_tostring(L, idx));  /* add it to history */
#define killa_freeline(L,b)       ((void)L, free(b))

#elif !defined(killa_readline)

#define killa_readline(L,b,p)     \
        ((void)L, fputs(p, stdout), fflush(stdout),  /* show prompt */ \
        fgets(b, KILLA_MAXINPUT, stdin) != NULL)  /* get line */
#define killa_saveline(L,idx)     { (void)L; (void)idx; }
#define killa_freeline(L,b)       { (void)L; (void)b; }

#endif




static killa_State *globalL = NULL;

static const char *progname = KILLA_PROGNAME;



static void lstop (killa_State *L, killa_Debug *ar) {
  (void)ar;  /* unused arg. */
  killa_sethook(L, NULL, 0, 0);
  killaL_error(L, "interrupted!");
}


static void laction (int i) {
  signal(i, SIG_DFL); /* if another SIGINT happens before lstop,
                              terminate process (default action) */
  killa_sethook(globalL, lstop, KILLA_MASKCALL | KILLA_MASKRET | KILLA_MASKCOUNT, 1);
}


static void print_usage (const char *badoption) {
  killai_writestringerror("%s: ", progname);
  if (badoption[1] == 'e' || badoption[1] == 'l')
    killai_writestringerror("'%s' needs argument\n", badoption);
  else
    killai_writestringerror("unrecognized option '%s'\n", badoption);
  killai_writestringerror(
  "usage: %s [options] [script [args]]\n"
  "Available options are:\n"
  "  -e stat  execute string " KILLA_QL("stat") "\n"
  "  -i       enter interactive mode after executing " KILLA_QL("script") "\n"
  "  -l name  require library " KILLA_QL("name") "\n"
  "  -v       show version information\n"
  "  -E       ignore environment variables\n"
  "  --       stop handling options\n"
  "  -        stop handling options and execute stdin\n"
  ,
  progname);
}


static void l_message (const char *pname, const char *msg) {
  if (pname) killai_writestringerror("%s: ", pname);
  killai_writestringerror("%s\n", msg);
}


static int report (killa_State *L, int status) {
  if (status != KILLA_OK && !killa_isnull(L, -1)) {
    const char *msg = killa_tostring(L, -1);
    if (msg == NULL) msg = "(error object is not a string)";
    l_message(progname, msg);
    killa_pop(L, 1);
    /* force a complete garbage collection in case of errors */
    killa_gc(L, KILLA_GCCOLLECT, 0);
  }
  return status;
}


/* the next function is called unprotected, so it must avoid errors */
static void finalreport (killa_State *L, int status) {
  if (status != KILLA_OK) {
    const char *msg = (killa_type(L, -1) == KILLA_TSTRING) ? killa_tostring(L, -1)
                                                       : NULL;
    if (msg == NULL) msg = "(error object is not a string)";
    l_message(progname, msg);
    killa_pop(L, 1);
  }
}


static int traceback (killa_State *L) {
  const char *msg = killa_tostring(L, 1);
  if (msg)
    killaL_traceback(L, L, msg, 1);
  else if (!killa_isnoneornull(L, 1)) {  /* is there an error object? */
    if (!killaL_callmeta(L, 1, "__tostring"))  /* try its 'tostring' metamethod */
      killa_pushliteral(L, "(no error message)");
  }
  return 1;
}


static int docall (killa_State *L, int narg, int nres) {
  int status;
  int base = killa_gettop(L) - narg;  /* function index */
  killa_pushcfunction(L, traceback);  /* push traceback function */
  killa_insert(L, base);  /* put it under chunk and args */
  globalL = L;  /* to be available to 'laction' */
  signal(SIGINT, laction);
  status = killa_pcall(L, narg, nres, base);
  signal(SIGINT, SIG_DFL);
  killa_remove(L, base);  /* remove traceback function */
  return status;
}


static void print_version (void) {
  killai_writestring(KILLA_COPYRIGHT, strlen(KILLA_COPYRIGHT));
  killai_writeline();
}


static int getargs (killa_State *L, char **argv, int n) {
  int narg;
  int i;
  int argc = 0;
  while (argv[argc]) argc++;  /* count total number of arguments */
  narg = argc - (n + 1);  /* number of arguments to the script */
  killaL_checkstack(L, narg + 3, "too many arguments to script");
  for (i=n+1; i < argc; i++)
    killa_pushstring(L, argv[i]);
  killa_createtable(L, narg, n + 1);
  for (i=0; i < argc; i++) {
    killa_pushstring(L, argv[i]);
    killa_rawseti(L, -2, i - n + KILLA_BASE - 1);
  }
  return narg;
}


static int dofile (killa_State *L, const char *name) {
  int status = killaL_loadfile(L, name);
  if (status == KILLA_OK) status = docall(L, 0, 0);
  return report(L, status);
}


static int dostring (killa_State *L, const char *s, const char *name) {
  int status = killaL_loadbuffer(L, s, strlen(s), name);
  if (status == KILLA_OK) status = docall(L, 0, 0);
  return report(L, status);
}


static int dolibrary (killa_State *L, const char *name) {
  int status;
  killa_pushglobaltable(L);
  killa_getfield(L, -1, "require");
  killa_pushstring(L, name);
  status = docall(L, 1, 1);
  if (status == KILLA_OK) {
    killa_setfield(L, -2, name);  /* global[name] = require return */
    killa_pop(L, 1);  /* remove global table */
  }
  else
    killa_remove(L, -2);  /* remove global table (below error msg.) */
  return report(L, status);
}


static const char *get_prompt (killa_State *L, int firstline) {
  const char *p;
  killa_getglobal(L, firstline ? "_PROMPT" : "_PROMPT2");
  p = killa_tostring(L, -1);
  if (p == NULL) p = (firstline ? KILLA_PROMPT : KILLA_PROMPT2);
  killa_pop(L, 1);  /* remove global */
  return p;
}

/* mark in error messages for incomplete statements */
#define EOFMARK		"<eof>"
#define marklen		(sizeof(EOFMARK)/sizeof(char) - 1)

static int incomplete (killa_State *L, int status) {
  if (status == KILLA_ERRSYNTAX) {
    size_t lmsg;
    const char *msg = killa_tolstring(L, -1, &lmsg);
    if (lmsg >= marklen && strcmp(msg + lmsg - marklen, EOFMARK) == 0) {
      killa_pop(L, 1);
      return 1;
    }
  }
  return 0;  /* else... */
}


static int pushline (killa_State *L, int firstline) {
  char buffer[KILLA_MAXINPUT];
  char *b = buffer;
  size_t l;
  const char *prmt = get_prompt(L, firstline);
  if (killa_readline(L, b, prmt) == 0)
    return 0;  /* no input */
  l = strlen(b);
  if (l > 0 && b[l-1] == '\n')  /* line ends with newline? */
    b[l-1] = '\0';  /* remove it */
  if (firstline && b[0] == '=')  /* first line starts with `=' ? */
    killa_pushfstring(L, "return %s", b+1);  /* change it to `return' */
  else
    killa_pushstring(L, b);
  killa_freeline(L, b);
  return 1;
}


static int loadline (killa_State *L) {
  int status;
  killa_settop(L, 0);
  if (!pushline(L, 1))
    return -1;  /* no input */
  for (;;) {  /* repeat until gets a complete line */
    size_t l;
    const char *line = killa_tolstring(L, 1, &l);
    status = killaL_loadbuffer(L, line, l, "=stdin");
    if (!incomplete(L, status)) break;  /* cannot try to add lines? */
    if (!pushline(L, 0))  /* no more input? */
      return -1;
    killa_pushliteral(L, "\n");  /* add a new line... */
    killa_insert(L, -2);  /* ...between the two lines */
    killa_concat(L, 3);  /* join them */
  }
  killa_saveline(L, 1);
  killa_remove(L, 1);  /* remove line */
  return status;
}


static void dotty (killa_State *L) {
  int status;
  const char *oldprogname = progname;
  progname = NULL;
  while ((status = loadline(L)) != -1) {
    if (status == KILLA_OK) status = docall(L, 0, KILLA_MULTRET);
    report(L, status);
    if (status == KILLA_OK && killa_gettop(L) > 0) {  /* any result to print? */
      killaL_checkstack(L, KILLA_MINSTACK, "too many results to print");
      killa_getglobal(L, "print");
      killa_insert(L, 1);
      if (killa_pcall(L, killa_gettop(L)-1, 0, 0) != KILLA_OK)
        l_message(progname, killa_pushfstring(L,
                               "error calling " KILLA_QL("print") " (%s)",
                               killa_tostring(L, -1)));
    }
  }
  killa_settop(L, 0);  /* clear stack */
  killai_writeline();
  progname = oldprogname;
}


static int handle_script (killa_State *L, char **argv, int n) {
  int status;
  const char *fname;
  int narg = getargs(L, argv, n);  /* collect arguments */
  killa_setglobal(L, KILLA_ARGS);
  fname = argv[n];
  if (strcmp(fname, "-") == 0 && strcmp(argv[n-1], "--") != 0)
    fname = NULL;  /* stdin */
  status = killaL_loadfile(L, fname);
  killa_insert(L, -(narg+1));
  if (status == KILLA_OK)
    status = docall(L, narg, KILLA_MULTRET);
  else
    killa_pop(L, narg);
  return report(L, status);
}


/* check that argument has no extra characters at the end */
#define noextrachars(x)		{if ((x)[2] != '\0') return -1;}


/* indices of various argument indicators in array args */
#define has_i		0	/* -i */
#define has_v		1	/* -v */
#define has_e		2	/* -e */
#define has_E		3	/* -E */

#define num_has		4	/* number of 'has_*' */


static int collectargs (char **argv, int *args) {
  int i;
  for (i = 1; argv[i] != NULL; i++) {
    if (argv[i][0] != '-')  /* not an option? */
        return i;
    switch (argv[i][1]) {  /* option */
      case '-':
        noextrachars(argv[i]);
        return (argv[i+1] != NULL ? i+1 : 0);
      case '\0':
        return i;
      case 'E':
        args[has_E] = 1;
        break;
      case 'i':
        noextrachars(argv[i]);
        args[has_i] = 1;  /* go through */
      case 'v':
        noextrachars(argv[i]);
        args[has_v] = 1;
        break;
      case 'e':
        args[has_e] = 1;  /* go through */
      case 'l':  /* both options need an argument */
        if (argv[i][2] == '\0') {  /* no concatenated argument? */
          i++;  /* try next 'argv' */
          if (argv[i] == NULL || argv[i][0] == '-')
            return -(i - 1);  /* no next argument or it is another option */
        }
        break;
      default:  /* invalid option; return its index... */
        return -i;  /* ...as a negative value */
    }
  }
  return 0;
}


static int runargs (killa_State *L, char **argv, int n) {
  int i;
  for (i = 1; i < n; i++) {
    killa_assert(argv[i][0] == '-');
    switch (argv[i][1]) {  /* option */
      case 'e': {
        const char *chunk = argv[i] + 2;
        if (*chunk == '\0') chunk = argv[++i];
        killa_assert(chunk != NULL);
        if (dostring(L, chunk, "=(command line)") != KILLA_OK)
          return 0;
        break;
      }
      case 'l': {
        const char *filename = argv[i] + 2;
        if (*filename == '\0') filename = argv[++i];
        killa_assert(filename != NULL);
        if (dolibrary(L, filename) != KILLA_OK)
          return 0;  /* stop if file fails */
        break;
      }
      default: break;
    }
  }
  return 1;
}


static int handle_killainit (killa_State *L) {
  const char *name = "=" KILLA_INITVERSION;
  const char *init = getenv(name + 1);
  if (init == NULL) {
    name = "=" KILLA_INIT;
    init = getenv(name + 1);  /* try alternative name */
  }
  if (init == NULL) return KILLA_OK;
  else if (init[0] == '@')
    return dofile(L, init+1);
  else
    return dostring(L, init, name);
}


static int pmain (killa_State *L) {
  int argc = (int)killa_tointeger(L, 1);
  char **argv = (char **)killa_touserdata(L, 2);
  int script;
  int args[num_has];
  args[has_i] = args[has_v] = args[has_e] = args[has_E] = 0;
  if (argv[0] && argv[0][0]) progname = argv[0];
  script = collectargs(argv, args);
  if (script < 0) {  /* invalid arg? */
    print_usage(argv[-script]);
    return 0;
  }
  if (args[has_v]) print_version();
  if (args[has_E]) {  /* option '-E'? */
    killa_pushboolean(L, 1);  /* signal for libraries to ignore env. vars. */
    killa_setfield(L, KILLA_REGISTRYINDEX, "KILLA_NOENV");
  }
  /* open standard libraries */
  killaL_checkversion(L);
  killa_gc(L, KILLA_GCSTOP, 0);  /* stop collector during initialization */
  killaL_openlibs(L);  /* open libraries */
  killa_gc(L, KILLA_GCRESTART, 0);
  if (!args[has_E] && handle_killainit(L) != KILLA_OK)
    return 0;  /* error running KILLA_INIT */
  /* execute arguments -e and -l */
  if (!runargs(L, argv, (script > 0) ? script : argc)) return 0;
  /* execute main script (if there is one) */
  if (script && handle_script(L, argv, script) != KILLA_OK) return 0;
  if (args[has_i])  /* -i option? */
    dotty(L);
  else if (script == 0 && !args[has_e] && !args[has_v]) {  /* no arguments? */
    if (killa_stdin_is_tty()) {
      print_version();
      dotty(L);
    }
    else dofile(L, NULL);  /* executes stdin as a file */
  }
  killa_pushboolean(L, 1);  /* signal no errors */
  return 1;
}


int main (int argc, char **argv) {
  int status, result;
  killa_State *L = killaL_newstate();  /* create state */
  if (L == NULL) {
    l_message(argv[0], "cannot create state: not enough memory");
    return EXIT_FAILURE;
  }
  /* call 'pmain' in protected mode */
  killa_pushcfunction(L, &pmain);
  killa_pushinteger(L, argc);  /* 1st argument */
  killa_pushlightuserdata(L, argv); /* 2nd argument */
  status = killa_pcall(L, 2, 1, 0);
  result = killa_toboolean(L, -1);  /* get result */
  finalreport(L, status);
  killa_close(L);
  return (result && status == KILLA_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
}

