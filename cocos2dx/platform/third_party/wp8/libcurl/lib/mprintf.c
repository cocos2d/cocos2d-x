/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1999 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 *
 * Purpose:
 *  A merge of Bjorn Reese's format() function and Daniel's dsprintf()
 *  1.0. A full blooded printf() clone with full support for <num>$
 *  everywhere (parameters, widths and precisions) including variabled
 *  sized parameters (like doubles, long longs, long doubles and even
 *  void * in 64-bit architectures).
 *
 * Current restrictions:
 * - Max 128 parameters
 * - No 'long double' support.
 *
 * If you ever want truly portable and good *printf() clones, the project that
 * took on from here is named 'Trio' and you find more details on the trio web
 * page at http://daniel.haxx.se/trio/
 */

#include "curl_setup.h"

#if defined(DJGPP) && (DJGPP_MINOR < 4)
#undef _MPRINTF_REPLACE /* don't use x_was_used() here */
#endif

#include <curl/mprintf.h>

#include "curl_memory.h"
/* The last #include file should be: */
#include "memdebug.h"

#ifndef SIZEOF_LONG_DOUBLE
#define SIZEOF_LONG_DOUBLE 0
#endif

/*
 * If SIZEOF_SIZE_T has not been defined, default to the size of long.
 */

#ifndef SIZEOF_SIZE_T
#  define SIZEOF_SIZE_T CURL_SIZEOF_LONG
#endif

#ifdef HAVE_LONGLONG
#  define LONG_LONG_TYPE long long
#  define HAVE_LONG_LONG_TYPE
#else
#  if defined(_MSC_VER) && (_MSC_VER >= 900) && (_INTEGRAL_MAX_BITS >= 64)
#    define LONG_LONG_TYPE __int64
#    define HAVE_LONG_LONG_TYPE
#  else
#    undef LONG_LONG_TYPE
#    undef HAVE_LONG_LONG_TYPE
#  endif
#endif

/*
 * Max integer data types that mprintf.c is capable
 */

#ifdef HAVE_LONG_LONG_TYPE
#  define mp_intmax_t LONG_LONG_TYPE
#  define mp_uintmax_t unsigned LONG_LONG_TYPE
#else
#  define mp_intmax_t long
#  define mp_uintmax_t unsigned long
#endif

#define BUFFSIZE 256 /* buffer for long-to-str and float-to-str calcs */
#define MAX_PARAMETERS 128 /* lame static limit */

#ifdef __AMIGA__
# undef FORMAT_INT
#endif

/* Lower-case digits.  */
static const char lower_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

/* Upper-case digits.  */
static const char upper_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

#define OUTCHAR(x) \
  do{ \
    if(stream((unsigned char)(x), (FILE *)data) != -1) \
      done++; \
    else \
     return done; /* return immediately on failure */ \
  } WHILE_FALSE

/* Data type to read from the arglist */
typedef enum  {
  FORMAT_UNKNOWN = 0,
  FORMAT_STRING,
  FORMAT_PTR,
  FORMAT_INT,
  FORMAT_INTPTR,
  FORMAT_LONG,
  FORMAT_LONGLONG,
  FORMAT_DOUBLE,
  FORMAT_LONGDOUBLE,
  FORMAT_WIDTH /* For internal use */
} FormatType;

/* conversion and display flags */
enum {
  FLAGS_NEW        = 0,
  FLAGS_SPACE      = 1<<0,
  FLAGS_SHOWSIGN   = 1<<1,
  FLAGS_LEFT       = 1<<2,
  FLAGS_ALT        = 1<<3,
  FLAGS_SHORT      = 1<<4,
  FLAGS_LONG       = 1<<5,
  FLAGS_LONGLONG   = 1<<6,
  FLAGS_LONGDOUBLE = 1<<7,
  FLAGS_PAD_NIL    = 1<<8,
  FLAGS_UNSIGNED   = 1<<9,
  FLAGS_OCTAL      = 1<<10,
  FLAGS_HEX        = 1<<11,
  FLAGS_UPPER      = 1<<12,
  FLAGS_WIDTH      = 1<<13, /* '*' or '*<num>$' used */
  FLAGS_WIDTHPARAM = 1<<14, /* width PARAMETER was specified */
  FLAGS_PREC       = 1<<15, /* precision was specified */
  FLAGS_PRECPARAM  = 1<<16, /* precision PARAMETER was specified */
  FLAGS_CHAR       = 1<<17, /* %c story */
  FLAGS_FLOATE     = 1<<18, /* %e or %E */
  FLAGS_FLOATG     = 1<<19  /* %g or %G */
};

typedef struct {
  FormatType type;
  int flags;
  long width;     /* width OR width parameter number */
  long precision; /* precision OR precision parameter number */
  union {
    char *str;
    void *ptr;
    union {
      mp_intmax_t as_signed;
      mp_uintmax_t as_unsigned;
    } num;
    double dnum;
  } data;
} va_stack_t;

struct nsprintf {
  char *buffer;
  size_t length;
  size_t max;
};

struct asprintf {
  char *buffer; /* allocated buffer */
  size_t len;   /* length of string */
  size_t alloc; /* length of alloc */
  int fail;     /* (!= 0) if an alloc has failed and thus
                   the output is not the complete data */
};

static long dprintf_DollarString(char *input, char **end)
{
  int number=0;
  while(ISDIGIT(*input)) {
    number *= 10;
    number += *input-'0';
    input++;
  }
  if(number && ('$'==*input++)) {
    *end = input;
    return number;
  }
  return 0;
}

static int dprintf_IsQualifierNoDollar(char c)
{
  switch (c) {
  case '-': case '+': case ' ': case '#': case '.':
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  case 'h': case 'l': case 'L': case 'z': case 'q':
  case '*': case 'O':
    return 1; /* true */
  default:
    return 0; /* false */
  }
}

/******************************************************************
 *
 * Pass 1:
 * Create an index with the type of each parameter entry and its
 * value (may vary in size)
 *
 ******************************************************************/

static long dprintf_Pass1(const char *format, va_stack_t *vto, char **endpos,
                          va_list arglist)
{
  char *fmt = (char *)format;
  int param_num = 0;
  long this_param;
  long width;
  long precision;
  int flags;
  long max_param=0;
  long i;

  while(*fmt) {
    if(*fmt++ == '%') {
      if(*fmt == '%') {
        fmt++;
        continue; /* while */
      }

      flags = FLAGS_NEW;

      /* Handle the positional case (N$) */

      param_num++;

      this_param = dprintf_DollarString(fmt, &fmt);
      if(0 == this_param)
        /* we got no positional, get the next counter */
        this_param = param_num;

      if(this_param > max_param)
        max_param = this_param;

      /*
       * The parameter with number 'i' should be used. Next, we need
       * to get SIZE and TYPE of the parameter. Add the information
       * to our array.
       */

      width = 0;
      precision = 0;

      /* Handle the flags */

      while(dprintf_IsQualifierNoDollar(*fmt)) {
        switch (*fmt++) {
        case ' ':
          flags |= FLAGS_SPACE;
          break;
        case '+':
          flags |= FLAGS_SHOWSIGN;
          break;
        case '-':
          flags |= FLAGS_LEFT;
          flags &= ~FLAGS_PAD_NIL;
          break;
        case '#':
          flags |= FLAGS_ALT;
          break;
        case '.':
          flags |= FLAGS_PREC;
          if('*' == *fmt) {
            /* The precision is picked from a specified parameter */

            flags |= FLAGS_PRECPARAM;
            fmt++;
            param_num++;

            i = dprintf_DollarString(fmt, &fmt);
            if(i)
              precision = i;
            else
              precision = param_num;

            if(precision > max_param)
              max_param = precision;
          }
          else {
            flags |= FLAGS_PREC;
            precision = strtol(fmt, &fmt, 10);
          }
          break;
        case 'h':
          flags |= FLAGS_SHORT;
          break;
        case 'l':
          if(flags & FLAGS_LONG)
            flags |= FLAGS_LONGLONG;
          else
            flags |= FLAGS_LONG;
          break;
        case 'L':
          flags |= FLAGS_LONGDOUBLE;
          break;
        case 'q':
          flags |= FLAGS_LONGLONG;
          break;
        case 'z':
          /* the code below generates a warning if -Wunreachable-code is
             used */
#if (SIZEOF_SIZE_T > CURL_SIZEOF_LONG)
          flags |= FLAGS_LONGLONG;
#else
          flags |= FLAGS_LONG;
#endif
          break;
        case 'O':
#if (CURL_SIZEOF_CURL_OFF_T > CURL_SIZEOF_LONG)
          flags |= FLAGS_LONGLONG;
#else
          flags |= FLAGS_LONG;
#endif
          break;
        case '0':
          if(!(flags & FLAGS_LEFT))
            flags |= FLAGS_PAD_NIL;
          /* FALLTHROUGH */
        case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
          flags |= FLAGS_WIDTH;
          width = strtol(fmt-1, &fmt, 10);
          break;
        case '*':  /* Special case */
          flags |= FLAGS_WIDTHPARAM;
          param_num++;

          i = dprintf_DollarString(fmt, &fmt);
          if(i)
            width = i;
          else
            width = param_num;
          if(width > max_param)
            max_param=width;
          break;
        default:
          break;
        }
      } /* switch */

      /* Handle the specifier */

      i = this_param - 1;

      switch (*fmt) {
      case 'S':
        flags |= FLAGS_ALT;
        /* FALLTHROUGH */
      case 's':
        vto[i].type = FORMAT_STRING;
        break;
      case 'n':
        vto[i].type = FORMAT_INTPTR;
        break;
      case 'p':
        vto[i].type = FORMAT_PTR;
        break;
      case 'd': case 'i':
        vto[i].type = FORMAT_INT;
        break;
      case 'u':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_UNSIGNED;
        break;
      case 'o':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_OCTAL;
        break;
      case 'x':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_HEX|FLAGS_UNSIGNED;
        break;
      case 'X':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_HEX|FLAGS_UPPER|FLAGS_UNSIGNED;
        break;
      case 'c':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_CHAR;
        break;
      case 'f':
        vto[i].type = FORMAT_DOUBLE;
        break;
      case 'e':
        vto[i].type = FORMAT_DOUBLE;
        flags |= FLAGS_FLOATE;
        break;
      case 'E':
        vto[i].type = FORMAT_DOUBLE;
        flags |= FLAGS_FLOATE|FLAGS_UPPER;
        break;
      case 'g':
        vto[i].type = FORMAT_DOUBLE;
        flags |= FLAGS_FLOATG;
        break;
      case 'G':
        vto[i].type = FORMAT_DOUBLE;
        flags |= FLAGS_FLOATG|FLAGS_UPPER;
        break;
      default:
        vto[i].type = FORMAT_UNKNOWN;
        break;
      } /* switch */

      vto[i].flags = flags;
      vto[i].width = width;
      vto[i].precision = precision;

      if(flags & FLAGS_WIDTHPARAM) {
        /* we have the width specified from a parameter, so we make that
           parameter's info setup properly */
        vto[i].width = width - 1;
        i = width - 1;
        vto[i].type = FORMAT_WIDTH;
        vto[i].flags = FLAGS_NEW;
        vto[i].precision = vto[i].width = 0; /* can't use width or precision
                                                of width! */
      }
      if(flags & FLAGS_PRECPARAM) {
        /* we have the precision specified from a parameter, so we make that
           parameter's info setup properly */
        vto[i].precision = precision - 1;
        i = precision - 1;
        vto[i].type = FORMAT_WIDTH;
        vto[i].flags = FLAGS_NEW;
        vto[i].precision = vto[i].width = 0; /* can't use width or precision
                                                of width! */
      }
      *endpos++ = fmt + 1; /* end of this sequence */
    }
  }

  /* Read the arg list parameters into our data list */
  for(i=0; i<max_param; i++) {
    if((i + 1 < max_param) && (vto[i + 1].type == FORMAT_WIDTH)) {
      /* Width/precision arguments must be read before the main argument
       * they are attached to
       */
      vto[i + 1].data.num.as_signed = (mp_intmax_t)va_arg(arglist, int);
    }

    switch (vto[i].type) {
    case FORMAT_STRING:
      vto[i].data.str = va_arg(arglist, char *);
      break;

    case FORMAT_INTPTR:
    case FORMAT_UNKNOWN:
    case FORMAT_PTR:
      vto[i].data.ptr = va_arg(arglist, void *);
      break;

    case FORMAT_INT:
#ifdef HAVE_LONG_LONG_TYPE
      if((vto[i].flags & FLAGS_LONGLONG) && (vto[i].flags & FLAGS_UNSIGNED))
        vto[i].data.num.as_unsigned =
          (mp_uintmax_t)va_arg(arglist, mp_uintmax_t);
      else if(vto[i].flags & FLAGS_LONGLONG)
        vto[i].data.num.as_signed =
          (mp_intmax_t)va_arg(arglist, mp_intmax_t);
      else
#endif
      {
        if((vto[i].flags & FLAGS_LONG) && (vto[i].flags & FLAGS_UNSIGNED))
          vto[i].data.num.as_unsigned =
            (mp_uintmax_t)va_arg(arglist, unsigned long);
        else if(vto[i].flags & FLAGS_LONG)
          vto[i].data.num.as_signed =
            (mp_intmax_t)va_arg(arglist, long);
        else if(vto[i].flags & FLAGS_UNSIGNED)
          vto[i].data.num.as_unsigned =
            (mp_uintmax_t)va_arg(arglist, unsigned int);
        else
          vto[i].data.num.as_signed =
            (mp_intmax_t)va_arg(arglist, int);
      }
      break;

    case FORMAT_DOUBLE:
      vto[i].data.dnum = va_arg(arglist, double);
      break;

    case FORMAT_WIDTH:
      /* Argument has been read. Silently convert it into an integer
       * for later use
       */
      vto[i].type = FORMAT_INT;
      break;

    default:
      break;
    }
  }

  return max_param;

}

static int dprintf_formatf(
  void *data, /* untouched by format(), just sent to the stream() function in
                 the second argument */
  /* function pointer called for each output character */
  int (*stream)(int, FILE *),
  const char *format,    /* %-formatted string */
  va_list ap_save) /* list of parameters */
{
  /* Base-36 digits for numbers.  */
  const char *digits = lower_digits;

  /* Pointer into the format string.  */
  char *f;

  /* Number of characters written.  */
  int done = 0;

  long param; /* current parameter to read */
  long param_num=0; /* parameter counter */

  va_stack_t vto[MAX_PARAMETERS];
  char *endpos[MAX_PARAMETERS];
  char **end;

  char work[BUFFSIZE];

  va_stack_t *p;

  /* Do the actual %-code parsing */
  dprintf_Pass1(format, vto, endpos, ap_save);

  end = &endpos[0]; /* the initial end-position from the list dprintf_Pass1()
                       created for us */

  f = (char *)format;
  while(*f != '\0') {
    /* Format spec modifiers.  */
    int is_alt;

    /* Width of a field.  */
    long width;

    /* Precision of a field.  */
    long prec;

    /* Decimal integer is negative.  */
    int is_neg;

    /* Base of a number to be written.  */
    long base;

    /* Integral values to be written.  */
    mp_uintmax_t num;

    /* Used to convert negative in positive.  */
    mp_intmax_t signed_num;

    if(*f != '%') {
      /* This isn't a format spec, so write everything out until the next one
         OR end of string is reached.  */
      do {
        OUTCHAR(*f);
      } while(*++f && ('%' != *f));
      continue;
    }

    ++f;

    /* Check for "%%".  Note that although the ANSI standard lists
       '%' as a conversion specifier, it says "The complete format
       specification shall be `%%'," so we can avoid all the width
       and precision processing.  */
    if(*f == '%') {
      ++f;
      OUTCHAR('%');
      continue;
    }

    /* If this is a positional parameter, the position must follow immediately
       after the %, thus create a %<num>$ sequence */
    param=dprintf_DollarString(f, &f);

    if(!param)
      param = param_num;
    else
      --param;

    param_num++; /* increase this always to allow "%2$s %1$s %s" and then the
                    third %s will pick the 3rd argument */

    p = &vto[param];

    /* pick up the specified width */
    if(p->flags & FLAGS_WIDTHPARAM)
      width = (long)vto[p->width].data.num.as_signed;
    else
      width = p->width;

    /* pick up the specified precision */
    if(p->flags & FLAGS_PRECPARAM) {
      prec = (long)vto[p->precision].data.num.as_signed;
      param_num++; /* since the precision is extraced from a parameter, we
                      must skip that to get to the next one properly */
    }
    else if(p->flags & FLAGS_PREC)
      prec = p->precision;
    else
      prec = -1;

    is_alt = (p->flags & FLAGS_ALT) ? 1 : 0;

    switch (p->type) {
    case FORMAT_INT:
      num = p->data.num.as_unsigned;
      if(p->flags & FLAGS_CHAR) {
        /* Character.  */
        if(!(p->flags & FLAGS_LEFT))
          while(--width > 0)
            OUTCHAR(' ');
        OUTCHAR((char) num);
        if(p->flags & FLAGS_LEFT)
          while(--width > 0)
            OUTCHAR(' ');
        break;
      }
      if(p->flags & FLAGS_OCTAL) {
        /* Octal unsigned integer.  */
        base = 8;
        goto unsigned_number;
      }
      else if(p->flags & FLAGS_HEX) {
        /* Hexadecimal unsigned integer.  */

        digits = (p->flags & FLAGS_UPPER)? upper_digits : lower_digits;
        base = 16;
        goto unsigned_number;
      }
      else if(p->flags & FLAGS_UNSIGNED) {
        /* Decimal unsigned integer.  */
        base = 10;
        goto unsigned_number;
      }

      /* Decimal integer.  */
      base = 10;

      is_neg = (p->data.num.as_signed < (mp_intmax_t)0) ? 1 : 0;
      if(is_neg) {
        /* signed_num might fail to hold absolute negative minimum by 1 */
        signed_num = p->data.num.as_signed + (mp_intmax_t)1;
        signed_num = -signed_num;
        num = (mp_uintmax_t)signed_num;
        num += (mp_uintmax_t)1;
      }

      goto number;

      unsigned_number:
      /* Unsigned number of base BASE.  */
      is_neg = 0;

      number:
      /* Number of base BASE.  */
      {
        char *workend = &work[sizeof(work) - 1];
        char *w;

        /* Supply a default precision if none was given.  */
        if(prec == -1)
          prec = 1;

        /* Put the number in WORK.  */
        w = workend;
        while(num > 0) {
          *w-- = digits[num % base];
          num /= base;
        }
        width -= (long)(workend - w);
        prec -= (long)(workend - w);

        if(is_alt && base == 8 && prec <= 0) {
          *w-- = '0';
          --width;
        }

        if(prec > 0) {
          width -= prec;
          while(prec-- > 0)
            *w-- = '0';
        }

        if(is_alt && base == 16)
          width -= 2;

        if(is_neg || (p->flags & FLAGS_SHOWSIGN) || (p->flags & FLAGS_SPACE))
          --width;

        if(!(p->flags & FLAGS_LEFT) && !(p->flags & FLAGS_PAD_NIL))
          while(width-- > 0)
            OUTCHAR(' ');

        if(is_neg)
          OUTCHAR('-');
        else if(p->flags & FLAGS_SHOWSIGN)
          OUTCHAR('+');
        else if(p->flags & FLAGS_SPACE)
          OUTCHAR(' ');

        if(is_alt && base == 16) {
          OUTCHAR('0');
          if(p->flags & FLAGS_UPPER)
            OUTCHAR('X');
          else
            OUTCHAR('x');
        }

        if(!(p->flags & FLAGS_LEFT) && (p->flags & FLAGS_PAD_NIL))
          while(width-- > 0)
            OUTCHAR('0');

        /* Write the number.  */
        while(++w <= workend) {
          OUTCHAR(*w);
        }

        if(p->flags & FLAGS_LEFT)
          while(width-- > 0)
            OUTCHAR(' ');
      }
      break;

    case FORMAT_STRING:
            /* String.  */
      {
        static const char null[] = "(nil)";
        const char *str;
        size_t len;

        str = (char *) p->data.str;
        if(str == NULL) {
          /* Write null[] if there's space.  */
          if(prec == -1 || prec >= (long) sizeof(null) - 1) {
            str = null;
            len = sizeof(null) - 1;
            /* Disable quotes around (nil) */
            p->flags &= (~FLAGS_ALT);
          }
          else {
            str = "";
            len = 0;
          }
        }
        else
          len = strlen(str);

        if(prec != -1 && (size_t) prec < len)
          len = (size_t)prec;
        width -= (long)len;

        if(p->flags & FLAGS_ALT)
          OUTCHAR('"');

        if(!(p->flags&FLAGS_LEFT))
          while(width-- > 0)
            OUTCHAR(' ');

        while(len-- > 0)
          OUTCHAR(*str++);
        if(p->flags&FLAGS_LEFT)
          while(width-- > 0)
            OUTCHAR(' ');

        if(p->flags & FLAGS_ALT)
          OUTCHAR('"');
      }
      break;

    case FORMAT_PTR:
      /* Generic pointer.  */
      {
        void *ptr;
        ptr = (void *) p->data.ptr;
        if(ptr != NULL) {
          /* If the pointer is not NULL, write it as a %#x spec.  */
          base = 16;
          digits = (p->flags & FLAGS_UPPER)? upper_digits : lower_digits;
          is_alt = 1;
          num = (size_t) ptr;
          is_neg = 0;
          goto number;
        }
        else {
          /* Write "(nil)" for a nil pointer.  */
          static const char strnil[] = "(nil)";
          const char *point;

          width -= (long)(sizeof(strnil) - 1);
          if(p->flags & FLAGS_LEFT)
            while(width-- > 0)
              OUTCHAR(' ');
          for(point = strnil; *point != '\0'; ++point)
            OUTCHAR(*point);
          if(! (p->flags & FLAGS_LEFT))
            while(width-- > 0)
              OUTCHAR(' ');
        }
      }
      break;

    case FORMAT_DOUBLE:
      {
        char formatbuf[32]="%";
        char *fptr = &formatbuf[1];
        size_t left = sizeof(formatbuf)-strlen(formatbuf);
        int len;

        width = -1;
        if(p->flags & FLAGS_WIDTH)
          width = p->width;
        else if(p->flags & FLAGS_WIDTHPARAM)
          width = (long)vto[p->width].data.num.as_signed;

        prec = -1;
        if(p->flags & FLAGS_PREC)
          prec = p->precision;
        else if(p->flags & FLAGS_PRECPARAM)
          prec = (long)vto[p->precision].data.num.as_signed;

        if(p->flags & FLAGS_LEFT)
          *fptr++ = '-';
        if(p->flags & FLAGS_SHOWSIGN)
          *fptr++ = '+';
        if(p->flags & FLAGS_SPACE)
          *fptr++ = ' ';
        if(p->flags & FLAGS_ALT)
          *fptr++ = '#';

        *fptr = 0;

        if(width >= 0) {
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, "%ld", width);
          fptr += len;
          left -= len;
        }
        if(prec >= 0) {
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, ".%ld", prec);
          fptr += len;
        }
        if(p->flags & FLAGS_LONG)
          *fptr++ = 'l';

        if(p->flags & FLAGS_FLOATE)
          *fptr++ = (char)((p->flags & FLAGS_UPPER) ? 'E':'e');
        else if(p->flags & FLAGS_FLOATG)
          *fptr++ = (char)((p->flags & FLAGS_UPPER) ? 'G' : 'g');
        else
          *fptr++ = 'f';

        *fptr = 0; /* and a final zero termination */

        /* NOTE NOTE NOTE!! Not all sprintf implementations return number of
           output characters */
        (sprintf)(work, formatbuf, p->data.dnum);

        for(fptr=work; *fptr; fptr++)
          OUTCHAR(*fptr);
      }
      break;

    case FORMAT_INTPTR:
      /* Answer the count of characters written.  */
#ifdef HAVE_LONG_LONG_TYPE
      if(p->flags & FLAGS_LONGLONG)
        *(LONG_LONG_TYPE *) p->data.ptr = (LONG_LONG_TYPE)done;
      else
#endif
        if(p->flags & FLAGS_LONG)
          *(long *) p->data.ptr = (long)done;
      else if(!(p->flags & FLAGS_SHORT))
        *(int *) p->data.ptr = (int)done;
      else
        *(short *) p->data.ptr = (short)done;
      break;

    default:
      break;
    }
    f = *end++; /* goto end of %-code */

  }
  return done;
}

/* fputc() look-alike */
static int addbyter(int output, FILE *data)
{
  struct nsprintf *infop=(struct nsprintf *)data;
  unsigned char outc = (unsigned char)output;

  if(infop->length < infop->max) {
    /* only do this if we haven't reached max length yet */
    infop->buffer[0] = outc; /* store */
    infop->buffer++; /* increase pointer */
    infop->length++; /* we are now one byte larger */
    return outc;     /* fputc() returns like this on success */
  }
  return -1;
}

int curl_mvsnprintf(char *buffer, size_t maxlength, const char *format,
                    va_list ap_save)
{
  int retcode;
  struct nsprintf info;

  info.buffer = buffer;
  info.length = 0;
  info.max = maxlength;

  retcode = dprintf_formatf(&info, addbyter, format, ap_save);
  if(info.max) {
    /* we terminate this with a zero byte */
    if(info.max == info.length)
      /* we're at maximum, scrap the last letter */
      info.buffer[-1] = 0;
    else
      info.buffer[0] = 0;
  }
  return retcode;
}

int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...)
{
  int retcode;
  va_list ap_save; /* argument pointer */
  va_start(ap_save, format);
  retcode = curl_mvsnprintf(buffer, maxlength, format, ap_save);
  va_end(ap_save);
  return retcode;
}

/* fputc() look-alike */
static int alloc_addbyter(int output, FILE *data)
{
  struct asprintf *infop=(struct asprintf *)data;
  unsigned char outc = (unsigned char)output;

  if(!infop->buffer) {
    infop->buffer = malloc(32);
    if(!infop->buffer) {
      infop->fail = 1;
      return -1; /* fail */
    }
    infop->alloc = 32;
    infop->len =0;
  }
  else if(infop->len+1 >= infop->alloc) {
    char *newptr;

    newptr = realloc(infop->buffer, infop->alloc*2);

    if(!newptr) {
      infop->fail = 1;
      return -1; /* fail */
    }
    infop->buffer = newptr;
    infop->alloc *= 2;
  }

  infop->buffer[ infop->len ] = outc;

  infop->len++;

  return outc; /* fputc() returns like this on success */
}

char *curl_maprintf(const char *format, ...)
{
  va_list ap_save; /* argument pointer */
  int retcode;
  struct asprintf info;

  info.buffer = NULL;
  info.len = 0;
  info.alloc = 0;
  info.fail = 0;

  va_start(ap_save, format);
  retcode = dprintf_formatf(&info, alloc_addbyter, format, ap_save);
  va_end(ap_save);
  if((-1 == retcode) || info.fail) {
    if(info.alloc)
      free(info.buffer);
    return NULL;
  }
  if(info.alloc) {
    info.buffer[info.len] = 0; /* we terminate this with a zero byte */
    return info.buffer;
  }
  else
    return strdup("");
}

char *curl_mvaprintf(const char *format, va_list ap_save)
{
  int retcode;
  struct asprintf info;

  info.buffer = NULL;
  info.len = 0;
  info.alloc = 0;
  info.fail = 0;

  retcode = dprintf_formatf(&info, alloc_addbyter, format, ap_save);
  if((-1 == retcode) || info.fail) {
    if(info.alloc)
      free(info.buffer);
    return NULL;
  }

  if(info.alloc) {
    info.buffer[info.len] = 0; /* we terminate this with a zero byte */
    return info.buffer;
  }
  else
    return strdup("");
}

static int storebuffer(int output, FILE *data)
{
  char **buffer = (char **)data;
  unsigned char outc = (unsigned char)output;
  **buffer = outc;
  (*buffer)++;
  return outc; /* act like fputc() ! */
}

int curl_msprintf(char *buffer, const char *format, ...)
{
  va_list ap_save; /* argument pointer */
  int retcode;
  va_start(ap_save, format);
  retcode = dprintf_formatf(&buffer, storebuffer, format, ap_save);
  va_end(ap_save);
  *buffer=0; /* we terminate this with a zero byte */
  return retcode;
}

int curl_mprintf(const char *format, ...)
{
  int retcode;
  va_list ap_save; /* argument pointer */
  va_start(ap_save, format);

  retcode = dprintf_formatf(stdout, fputc, format, ap_save);
  va_end(ap_save);
  return retcode;
}

int curl_mfprintf(FILE *whereto, const char *format, ...)
{
  int retcode;
  va_list ap_save; /* argument pointer */
  va_start(ap_save, format);
  retcode = dprintf_formatf(whereto, fputc, format, ap_save);
  va_end(ap_save);
  return retcode;
}

int curl_mvsprintf(char *buffer, const char *format, va_list ap_save)
{
  int retcode;
  retcode = dprintf_formatf(&buffer, storebuffer, format, ap_save);
  *buffer=0; /* we terminate this with a zero byte */
  return retcode;
}

int curl_mvprintf(const char *format, va_list ap_save)
{
  return dprintf_formatf(stdout, fputc, format, ap_save);
}

int curl_mvfprintf(FILE *whereto, const char *format, va_list ap_save)
{
  return dprintf_formatf(whereto, fputc, format, ap_save);
}
