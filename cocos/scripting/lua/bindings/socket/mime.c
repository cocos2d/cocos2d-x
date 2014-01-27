/*=========================================================================*\
* MIME support functions
* LuaSocket toolkit
\*=========================================================================*/
#include <string.h>

#include "lua.h"
#include "lauxlib.h"

#if !defined(LUA_VERSION_NUM) || (LUA_VERSION_NUM < 501)
#include "compat-5.1.h"
#endif

#include "mime.h"

/*=========================================================================*\
* Don't want to trust escape character constants
\*=========================================================================*/
typedef unsigned char UC;
static const char CRLF[] = "\r\n";
static const char EQCRLF[] = "=\r\n";

/*=========================================================================*\
* Internal function prototypes.
\*=========================================================================*/
static int mime_global_wrp(lua_State *L);
static int mime_global_b64(lua_State *L);
static int mime_global_unb64(lua_State *L);
static int mime_global_qp(lua_State *L);
static int mime_global_unqp(lua_State *L);
static int mime_global_qpwrp(lua_State *L);
static int mime_global_eol(lua_State *L);
static int mime_global_dot(lua_State *L);

static size_t dot(int c, size_t state, luaL_Buffer *buffer);
static void b64setup(UC *base);
static size_t b64encode(UC c, UC *input, size_t size, luaL_Buffer *buffer);
static size_t b64pad(const UC *input, size_t size, luaL_Buffer *buffer);
static size_t b64decode(UC c, UC *input, size_t size, luaL_Buffer *buffer);

static void qpsetup(UC *class, UC *unbase);
static void qpquote(UC c, luaL_Buffer *buffer);
static size_t qpdecode(UC c, UC *input, size_t size, luaL_Buffer *buffer);
static size_t qpencode(UC c, UC *input, size_t size, 
        const char *marker, luaL_Buffer *buffer);
static size_t qppad(UC *input, size_t size, luaL_Buffer *buffer);

/* code support functions */
static luaL_Reg func[] = {
    { "dot", mime_global_dot },
    { "b64", mime_global_b64 },
    { "eol", mime_global_eol },
    { "qp", mime_global_qp },
    { "qpwrp", mime_global_qpwrp },
    { "unb64", mime_global_unb64 },
    { "unqp", mime_global_unqp },
    { "wrp", mime_global_wrp },
    { NULL, NULL }
};

/*-------------------------------------------------------------------------*\
* Quoted-printable globals
\*-------------------------------------------------------------------------*/
static UC qpclass[256];
static UC qpbase[] = "0123456789ABCDEF";
static UC qpunbase[256];
enum {QP_PLAIN, QP_QUOTED, QP_CR, QP_IF_LAST};

/*-------------------------------------------------------------------------*\
* Base64 globals
\*-------------------------------------------------------------------------*/
static const UC b64base[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static UC b64unbase[256];

/*=========================================================================*\
* Exported functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Initializes module
\*-------------------------------------------------------------------------*/
MIME_API int luaopen_mime_core(lua_State *L)
{
    luaL_openlib(L, "mime", func, 0);
    /* make version string available to scripts */
    lua_pushstring(L, "_VERSION");
    lua_pushstring(L, MIME_VERSION);
    lua_rawset(L, -3);
    /* initialize lookup tables */
    qpsetup(qpclass, qpunbase);
    b64setup(b64unbase);
    return 1;
}

/*=========================================================================*\
* Global Lua functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Incrementaly breaks a string into lines. The string can have CRLF breaks.
* A, n = wrp(l, B, length)
* A is a copy of B, broken into lines of at most 'length' bytes. 
* 'l' is how many bytes are left for the first line of B. 
* 'n' is the number of bytes left in the last line of A. 
\*-------------------------------------------------------------------------*/
static int mime_global_wrp(lua_State *L)
{
    size_t size = 0;
    int left = (int) luaL_checknumber(L, 1);
    const UC *input = (UC *) luaL_optlstring(L, 2, NULL, &size);
    const UC *last = input + size;
    int length = (int) luaL_optnumber(L, 3, 76);
    luaL_Buffer buffer;
    /* end of input black-hole */
    if (!input) {
        /* if last line has not been terminated, add a line break */
        if (left < length) lua_pushstring(L, CRLF);
        /* otherwise, we are done */
        else lua_pushnil(L);
        lua_pushnumber(L, length);
        return 2;
    } 
    luaL_buffinit(L, &buffer);
    while (input < last) {
        switch (*input) {
            case '\r':
                break;
            case '\n':
                luaL_addstring(&buffer, CRLF);
                left = length;
                break;
            default:
                if (left <= 0) {
                    left = length;
                    luaL_addstring(&buffer, CRLF);
                }
                luaL_addchar(&buffer, *input);
                left--;
                break;
        }
        input++;
    }
    luaL_pushresult(&buffer);
    lua_pushnumber(L, left);
    return 2;
}

/*-------------------------------------------------------------------------*\
* Fill base64 decode map. 
\*-------------------------------------------------------------------------*/
static void b64setup(UC *unbase) 
{
    int i;
    for (i = 0; i <= 255; i++) unbase[i] = (UC) 255;
    for (i = 0; i < 64; i++) unbase[b64base[i]] = (UC) i;
    unbase['='] = 0;
}

/*-------------------------------------------------------------------------*\
* Acumulates bytes in input buffer until 3 bytes are available. 
* Translate the 3 bytes into Base64 form and append to buffer.
* Returns new number of bytes in buffer.
\*-------------------------------------------------------------------------*/
static size_t b64encode(UC c, UC *input, size_t size, 
        luaL_Buffer *buffer)
{
    input[size++] = c;
    if (size == 3) {
        UC code[4];
        unsigned long value = 0;
        value += input[0]; value <<= 8;
        value += input[1]; value <<= 8;
        value += input[2]; 
        code[3] = b64base[value & 0x3f]; value >>= 6;
        code[2] = b64base[value & 0x3f]; value >>= 6;
        code[1] = b64base[value & 0x3f]; value >>= 6;
        code[0] = b64base[value];
        luaL_addlstring(buffer, (char *) code, 4);
        size = 0;
    }
    return size;
}

/*-------------------------------------------------------------------------*\
* Encodes the Base64 last 1 or 2 bytes and adds padding '=' 
* Result, if any, is appended to buffer.
* Returns 0.
\*-------------------------------------------------------------------------*/
static size_t b64pad(const UC *input, size_t size, 
        luaL_Buffer *buffer)
{
    unsigned long value = 0;
    UC code[4] = {'=', '=', '=', '='};
    switch (size) {
        case 1:
            value = input[0] << 4;
            code[1] = b64base[value & 0x3f]; value >>= 6;
            code[0] = b64base[value];
            luaL_addlstring(buffer, (char *) code, 4);
            break;
        case 2:
            value = input[0]; value <<= 8; 
            value |= input[1]; value <<= 2;
            code[2] = b64base[value & 0x3f]; value >>= 6;
            code[1] = b64base[value & 0x3f]; value >>= 6;
            code[0] = b64base[value];
            luaL_addlstring(buffer, (char *) code, 4);
            break;
        default:
            break;
    }
    return 0;
}

/*-------------------------------------------------------------------------*\
* Acumulates bytes in input buffer until 4 bytes are available. 
* Translate the 4 bytes from Base64 form and append to buffer.
* Returns new number of bytes in buffer.
\*-------------------------------------------------------------------------*/
static size_t b64decode(UC c, UC *input, size_t size, 
        luaL_Buffer *buffer)
{
    /* ignore invalid characters */
    if (b64unbase[c] > 64) return size;
    input[size++] = c;
    /* decode atom */
    if (size == 4) {
        UC decoded[3];
        int valid, value = 0;
        value =  b64unbase[input[0]]; value <<= 6;
        value |= b64unbase[input[1]]; value <<= 6;
        value |= b64unbase[input[2]]; value <<= 6;
        value |= b64unbase[input[3]];
        decoded[2] = (UC) (value & 0xff); value >>= 8;
        decoded[1] = (UC) (value & 0xff); value >>= 8;
        decoded[0] = (UC) value;
        /* take care of paddding */
        valid = (input[2] == '=') ? 1 : (input[3] == '=') ? 2 : 3; 
        luaL_addlstring(buffer, (char *) decoded, valid);
        return 0;
    /* need more data */
    } else return size;
}

/*-------------------------------------------------------------------------*\
* Incrementally applies the Base64 transfer content encoding to a string
* A, B = b64(C, D)
* A is the encoded version of the largest prefix of C .. D that is
* divisible by 3. B has the remaining bytes of C .. D, *without* encoding.
* The easiest thing would be to concatenate the two strings and 
* encode the result, but we can't afford that or Lua would dupplicate
* every chunk we received.
\*-------------------------------------------------------------------------*/
static int mime_global_b64(lua_State *L)
{
    UC atom[3];
    size_t isize = 0, asize = 0;
    const UC *input = (UC *) luaL_optlstring(L, 1, NULL, &isize);
    const UC *last = input + isize;
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* make sure we don't confuse buffer stuff with arguments */
    lua_settop(L, 2);
    /* process first part of the input */
    luaL_buffinit(L, &buffer);
    while (input < last) 
        asize = b64encode(*input++, atom, asize, &buffer);
    input = (UC *) luaL_optlstring(L, 2, NULL, &isize);
    /* if second part is nil, we are done */
    if (!input) {
        size_t osize = 0;
        asize = b64pad(atom, asize, &buffer);
        luaL_pushresult(&buffer);
        /* if the output is empty  and the input is nil, return nil */
        lua_tolstring(L, -1, &osize);
        if (osize == 0) lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* otherwise process the second part */
    last = input + isize;
    while (input < last) 
        asize = b64encode(*input++, atom, asize, &buffer);
    luaL_pushresult(&buffer);
    lua_pushlstring(L, (char *) atom, asize);
    return 2;
}

/*-------------------------------------------------------------------------*\
* Incrementally removes the Base64 transfer content encoding from a string
* A, B = b64(C, D)
* A is the encoded version of the largest prefix of C .. D that is
* divisible by 4. B has the remaining bytes of C .. D, *without* encoding.
\*-------------------------------------------------------------------------*/
static int mime_global_unb64(lua_State *L)
{
    UC atom[4];
    size_t isize = 0, asize = 0;
    const UC *input = (UC *) luaL_optlstring(L, 1, NULL, &isize);
    const UC *last = input + isize;
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* make sure we don't confuse buffer stuff with arguments */
    lua_settop(L, 2);
    /* process first part of the input */
    luaL_buffinit(L, &buffer);
    while (input < last) 
        asize = b64decode(*input++, atom, asize, &buffer);
    input = (UC *) luaL_optlstring(L, 2, NULL, &isize);
    /* if second is nil, we are done */
    if (!input) {
        size_t osize = 0;
        luaL_pushresult(&buffer);
        /* if the output is empty  and the input is nil, return nil */
        lua_tolstring(L, -1, &osize);
        if (osize == 0) lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* otherwise, process the rest of the input */
    last = input + isize;
    while (input < last) 
        asize = b64decode(*input++, atom, asize, &buffer);
    luaL_pushresult(&buffer);
    lua_pushlstring(L, (char *) atom, asize);
    return 2;
}

/*-------------------------------------------------------------------------*\
* Quoted-printable encoding scheme
* all (except CRLF in text) can be =XX
* CLRL in not text must be =XX=XX
* 33 through 60 inclusive can be plain
* 62 through 126 inclusive can be plain
* 9 and 32 can be plain, unless in the end of a line, where must be =XX
* encoded lines must be no longer than 76 not counting CRLF
* soft line-break are =CRLF
* To encode one byte, we need to see the next two. 
* Worst case is when we see a space, and wonder if a CRLF is comming
\*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*\
* Split quoted-printable characters into classes
* Precompute reverse map for encoding
\*-------------------------------------------------------------------------*/
static void qpsetup(UC *cl, UC *unbase)
{
    int i;
    for (i = 0; i < 256; i++) cl[i] = QP_QUOTED;
    for (i = 33; i <= 60; i++) cl[i] = QP_PLAIN;
    for (i = 62; i <= 126; i++) cl[i] = QP_PLAIN;
    cl['\t'] = QP_IF_LAST; 
    cl[' '] = QP_IF_LAST;
    cl['\r'] = QP_CR;
    for (i = 0; i < 256; i++) unbase[i] = 255;
    unbase['0'] = 0; unbase['1'] = 1; unbase['2'] = 2;
    unbase['3'] = 3; unbase['4'] = 4; unbase['5'] = 5;
    unbase['6'] = 6; unbase['7'] = 7; unbase['8'] = 8;
    unbase['9'] = 9; unbase['A'] = 10; unbase['a'] = 10;
    unbase['B'] = 11; unbase['b'] = 11; unbase['C'] = 12;
    unbase['c'] = 12; unbase['D'] = 13; unbase['d'] = 13;
    unbase['E'] = 14; unbase['e'] = 14; unbase['F'] = 15;
    unbase['f'] = 15;
}

/*-------------------------------------------------------------------------*\
* Output one character in form =XX
\*-------------------------------------------------------------------------*/
static void qpquote(UC c, luaL_Buffer *buffer)
{
    luaL_addchar(buffer, '=');
    luaL_addchar(buffer, qpbase[c >> 4]);
    luaL_addchar(buffer, qpbase[c & 0x0F]);
}

/*-------------------------------------------------------------------------*\
* Accumulate characters until we are sure about how to deal with them.
* Once we are sure, output to the buffer, in the correct form. 
\*-------------------------------------------------------------------------*/
static size_t qpencode(UC c, UC *input, size_t size, 
        const char *marker, luaL_Buffer *buffer)
{
    input[size++] = c;
    /* deal with all characters we can have */
    while (size > 0) {
        switch (qpclass[input[0]]) {
            /* might be the CR of a CRLF sequence */
            case QP_CR:
                if (size < 2) return size;
                if (input[1] == '\n') {
                    luaL_addstring(buffer, marker);
                    return 0;
                } else qpquote(input[0], buffer);
                break;
            /* might be a space and that has to be quoted if last in line */
            case QP_IF_LAST:
                if (size < 3) return size;
                /* if it is the last, quote it and we are done */
                if (input[1] == '\r' && input[2] == '\n') {
                    qpquote(input[0], buffer);
                    luaL_addstring(buffer, marker);
                    return 0;
                } else luaL_addchar(buffer, input[0]);
                break;
                /* might have to be quoted always */
            case QP_QUOTED:
                qpquote(input[0], buffer);
                break;
                /* might never have to be quoted */
            default:
                luaL_addchar(buffer, input[0]);
                break;
        }
        input[0] = input[1]; input[1] = input[2];
        size--;
    }
    return 0;
}

/*-------------------------------------------------------------------------*\
* Deal with the final characters 
\*-------------------------------------------------------------------------*/
static size_t qppad(UC *input, size_t size, luaL_Buffer *buffer)
{
    size_t i;
    for (i = 0; i < size; i++) {
        if (qpclass[input[i]] == QP_PLAIN) luaL_addchar(buffer, input[i]);
        else qpquote(input[i], buffer);
    }
    if (size > 0) luaL_addstring(buffer, EQCRLF);
    return 0;
}

/*-------------------------------------------------------------------------*\
* Incrementally converts a string to quoted-printable
* A, B = qp(C, D, marker)
* Marker is the text to be used to replace CRLF sequences found in A.
* A is the encoded version of the largest prefix of C .. D that 
* can be encoded without doubts. 
* B has the remaining bytes of C .. D, *without* encoding.
\*-------------------------------------------------------------------------*/
static int mime_global_qp(lua_State *L)
{

    size_t asize = 0, isize = 0;
    UC atom[3];
    const UC *input = (UC *) luaL_optlstring(L, 1, NULL, &isize);
    const UC *last = input + isize;
    const char *marker = luaL_optstring(L, 3, CRLF);
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* make sure we don't confuse buffer stuff with arguments */
    lua_settop(L, 3);
    /* process first part of input */
    luaL_buffinit(L, &buffer);
    while (input < last)
        asize = qpencode(*input++, atom, asize, marker, &buffer);
    input = (UC *) luaL_optlstring(L, 2, NULL, &isize);
    /* if second part is nil, we are done */
    if (!input) {
        asize = qppad(atom, asize, &buffer);
        luaL_pushresult(&buffer);
        if (!(*lua_tostring(L, -1))) lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* otherwise process rest of input */
    last = input + isize;
    while (input < last)
        asize = qpencode(*input++, atom, asize, marker, &buffer);
    luaL_pushresult(&buffer);
    lua_pushlstring(L, (char *) atom, asize);
    return 2;
}

/*-------------------------------------------------------------------------*\
* Accumulate characters until we are sure about how to deal with them.
* Once we are sure, output the to the buffer, in the correct form. 
\*-------------------------------------------------------------------------*/
static size_t qpdecode(UC c, UC *input, size_t size, luaL_Buffer *buffer) {
    int d;
    input[size++] = c;
    /* deal with all characters we can deal */
    switch (input[0]) {
        /* if we have an escape character */
        case '=': 
            if (size < 3) return size; 
            /* eliminate soft line break */
            if (input[1] == '\r' && input[2] == '\n') return 0;
            /* decode quoted representation */
            c = qpunbase[input[1]]; d = qpunbase[input[2]];
            /* if it is an invalid, do not decode */
            if (c > 15 || d > 15) luaL_addlstring(buffer, (char *)input, 3);
            else luaL_addchar(buffer, (char) ((c << 4) + d));
            return 0;
        case '\r':
            if (size < 2) return size; 
            if (input[1] == '\n') luaL_addlstring(buffer, (char *)input, 2);
            return 0;
        default:
            if (input[0] == '\t' || (input[0] > 31 && input[0] < 127))
                luaL_addchar(buffer, input[0]);
            return 0;
    }
}

/*-------------------------------------------------------------------------*\
* Incrementally decodes a string in quoted-printable
* A, B = qp(C, D)
* A is the decoded version of the largest prefix of C .. D that 
* can be decoded without doubts. 
* B has the remaining bytes of C .. D, *without* decoding.
\*-------------------------------------------------------------------------*/
static int mime_global_unqp(lua_State *L)
{
    size_t asize = 0, isize = 0;
    UC atom[3];
    const UC *input = (UC *) luaL_optlstring(L, 1, NULL, &isize);
    const UC *last = input + isize;
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* make sure we don't confuse buffer stuff with arguments */
    lua_settop(L, 2);
    /* process first part of input */
    luaL_buffinit(L, &buffer);
    while (input < last)
        asize = qpdecode(*input++, atom, asize, &buffer);
    input = (UC *) luaL_optlstring(L, 2, NULL, &isize);
    /* if second part is nil, we are done */
    if (!input) {
        luaL_pushresult(&buffer);
        if (!(*lua_tostring(L, -1))) lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    } 
    /* otherwise process rest of input */
    last = input + isize;
    while (input < last)
        asize = qpdecode(*input++, atom, asize, &buffer);
    luaL_pushresult(&buffer);
    lua_pushlstring(L, (char *) atom, asize);
    return 2;
}

/*-------------------------------------------------------------------------*\
* Incrementally breaks a quoted-printed string into lines
* A, n = qpwrp(l, B, length)
* A is a copy of B, broken into lines of at most 'length' bytes. 
* 'l' is how many bytes are left for the first line of B. 
* 'n' is the number of bytes left in the last line of A. 
* There are two complications: lines can't be broken in the middle
* of an encoded =XX, and there might be line breaks already
\*-------------------------------------------------------------------------*/
static int mime_global_qpwrp(lua_State *L)
{
    size_t size = 0;
    int left = (int) luaL_checknumber(L, 1);
    const UC *input = (UC *) luaL_optlstring(L, 2, NULL, &size);
    const UC *last = input + size;
    int length = (int) luaL_optnumber(L, 3, 76);
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        if (left < length) lua_pushstring(L, EQCRLF);
        else lua_pushnil(L);
        lua_pushnumber(L, length);
        return 2;
    }
    /* process all input */
    luaL_buffinit(L, &buffer);
    while (input < last) {
        switch (*input) {
            case '\r':
                break;
            case '\n':
                left = length;
                luaL_addstring(&buffer, CRLF);
                break;
            case '=':
                if (left <= 3) {
                    left = length;
                    luaL_addstring(&buffer, EQCRLF);
                } 
                luaL_addchar(&buffer, *input);
                left--;
                break;
            default: 
                if (left <= 1) {
                    left = length;
                    luaL_addstring(&buffer, EQCRLF);
                }
                luaL_addchar(&buffer, *input);
                left--;
                break;
        }
        input++;
    }
    luaL_pushresult(&buffer);
    lua_pushnumber(L, left);
    return 2;
}

/*-------------------------------------------------------------------------*\
* Here is what we do: \n, and \r are considered candidates for line
* break. We issue *one* new line marker if any of them is seen alone, or
* followed by a different one. That is, \n\n and \r\r will issue two
* end of line markers each, but \r\n, \n\r etc will only issue *one*
* marker.  This covers Mac OS, Mac OS X, VMS, Unix and DOS, as well as
* probably other more obscure conventions.
*
* c is the current character being processed
* last is the previous character
\*-------------------------------------------------------------------------*/
#define eolcandidate(c) (c == '\r' || c == '\n')
static int eolprocess(int c, int last, const char *marker, 
        luaL_Buffer *buffer)
{
    if (eolcandidate(c)) {
        if (eolcandidate(last)) {
            if (c == last) luaL_addstring(buffer, marker);
            return 0;
        } else {
            luaL_addstring(buffer, marker);
            return c;
        }
    } else {
        luaL_addchar(buffer, (char) c);
        return 0;
    }
}

/*-------------------------------------------------------------------------*\
* Converts a string to uniform EOL convention. 
* A, n = eol(o, B, marker)
* A is the converted version of the largest prefix of B that can be
* converted unambiguously. 'o' is the context returned by the previous 
* call. 'n' is the new context.
\*-------------------------------------------------------------------------*/
static int mime_global_eol(lua_State *L)
{
    int ctx = luaL_checkint(L, 1);
    size_t isize = 0;
    const char *input = luaL_optlstring(L, 2, NULL, &isize);
    const char *last = input + isize;
    const char *marker = luaL_optstring(L, 3, CRLF);
    luaL_Buffer buffer;
    luaL_buffinit(L, &buffer);
    /* end of input blackhole */
    if (!input) {
       lua_pushnil(L);
       lua_pushnumber(L, 0);
       return 2;
    }
    /* process all input */
    while (input < last)
        ctx = eolprocess(*input++, ctx, marker, &buffer);
    luaL_pushresult(&buffer);
    lua_pushnumber(L, ctx);
    return 2;
}

/*-------------------------------------------------------------------------*\
* Takes one byte and stuff it if needed. 
\*-------------------------------------------------------------------------*/
static size_t dot(int c, size_t state, luaL_Buffer *buffer)
{
    luaL_addchar(buffer, (char) c);
    switch (c) {
        case '\r': 
            return 1;
        case '\n': 
            return (state == 1)? 2: 0; 
        case '.':  
            if (state == 2) 
                luaL_addchar(buffer, '.');
        default:
            return 0;
    }
}

/*-------------------------------------------------------------------------*\
* Incrementally applies smtp stuffing to a string
* A, n = dot(l, D)
\*-------------------------------------------------------------------------*/
static int mime_global_dot(lua_State *L)
{
    size_t isize = 0, state = (size_t) luaL_checknumber(L, 1);
    const char *input = luaL_optlstring(L, 2, NULL, &isize);
    const char *last = input + isize;
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        lua_pushnil(L);
        lua_pushnumber(L, 2);
        return 2;
    }
    /* process all input */
    luaL_buffinit(L, &buffer);
    while (input < last) 
        state = dot(*input++, state, &buffer);
    luaL_pushresult(&buffer);
    lua_pushnumber(L, (lua_Number) state);
    return 2;
}

