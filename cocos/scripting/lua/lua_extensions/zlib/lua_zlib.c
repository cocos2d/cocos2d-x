#include <ctype.h>
#include "lauxlib.h"
#include "lua.h"
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

/*
 * ** compatibility with Lua 5.2
 * */
#if (LUA_VERSION_NUM == 502)
#undef luaL_register
#define luaL_register(L,n,f) \
               { if ((n) == NULL) luaL_setfuncs(L,f,0); else luaL_newlib(L,f); }

#endif

typedef uLong (*checksum_t)        (uLong crc, const Bytef *buf, uInt len);
typedef uLong (*checksum_combine_t)(uLong crc1, uLong crc2, z_off_t len2);


static int lz_deflate(lua_State *L);
static int lz_deflate_delete(lua_State *L);
static int lz_inflate_delete(lua_State *L);
static int lz_inflate(lua_State *L);
static int lz_checksum(lua_State *L);
static int lz_checksum_new(lua_State *L, checksum_t checksum, checksum_combine_t combine);
static int lz_adler32(lua_State *L);
static int lz_crc32(lua_State *L);

static int lz_version(lua_State *L) {
    const char* version = zlibVersion();
    int         count   = (int)strlen(version) + 1;
    char*       cur     = (char*)memcpy(lua_newuserdata(L, count),
                                        version, count);

    count = 0;
    while ( *cur ) {
        char* begin = cur;
        /* Find all digits: */
        while ( isdigit(*cur) ) cur++;
        if ( begin != cur ) {
            int is_end = *cur == '\0';
            *cur = '\0';
            lua_pushnumber(L, atoi(begin));
            count++;
            if ( is_end ) break;
            cur++;
        }
        while ( *cur && ! isdigit(*cur) ) cur++;
    }

    return count;
}

static int lz_assert(lua_State *L, int result, const z_stream* stream, const char* file, int line) {
    /* Both of these are "normal" return codes: */
    if ( result == Z_OK || result == Z_STREAM_END ) return result;
    switch ( result ) {
    case Z_NEED_DICT:
        lua_pushfstring(L, "RequiresDictionary: input stream requires a dictionary to be deflated (%s) at %s line %d",
                        stream->msg, file, line);
        break;
    case Z_STREAM_ERROR:
        lua_pushfstring(L, "InternalError: inconsistent internal zlib stream (%s) at %s line %d",
                        stream->msg, file, line);
        break;
    case Z_DATA_ERROR:
        lua_pushfstring(L, "InvalidInput: input string does not conform to zlib format or checksum failed at %s line %d",
                        file, line);
        break;
    case Z_MEM_ERROR:
        lua_pushfstring(L, "OutOfMemory: not enough memory (%s) at %s line %d",
                        stream->msg, file, line);
        break;
    case Z_BUF_ERROR:
        lua_pushfstring(L, "InternalError: no progress possible (%s) at %s line %d",
                        stream->msg, file, line);
        break;
    case Z_VERSION_ERROR:
        lua_pushfstring(L, "IncompatibleLibrary: built with version %s, but dynamically linked with version %s (%s) at %s line %d",
                        ZLIB_VERSION,  zlibVersion(), stream->msg, file, line);
        break;
    default:
        lua_pushfstring(L, "ZLibError: unknown code %d (%s) at %s line %d",
                        result, stream->msg, file, line);
    }
    lua_error(L);
    return result;
}

/**
 * @upvalue z_stream - Memory for the z_stream.
 * @upvalue remainder - Any remainder from the last deflate call.
 *
 * @param string - "print" to deflate stream.
 * @param int - flush output buffer? Z_SYNC_FLUSH, Z_FULL_FLUSH, or Z_FINISH.
 *
 * if no params, terminates the stream (as if we got empty string and Z_FINISH).
 */
static int lz_filter_impl(lua_State *L, int (*filter)(z_streamp, int), int (*end)(z_streamp), char* name) {
    int flush = Z_NO_FLUSH, result;
    z_stream* stream;
    luaL_Buffer buff;
    size_t avail_in = 0;

    if ( filter == deflate ) {
        const char *const opts[] = { "none", "sync", "full", "finish", NULL };
        flush = luaL_checkoption(L, 2, opts[0], opts);
        if ( flush ) flush++; 
        /* Z_NO_FLUSH(0) Z_SYNC_FLUSH(2), Z_FULL_FLUSH(3), Z_FINISH (4) */

        /* No arguments or nil, we are terminating the stream: */
        if ( lua_gettop(L) == 0 || lua_isnil(L, 1) ) {
            flush = Z_FINISH;
        }
    }

    stream = (z_stream*)lua_touserdata(L, lua_upvalueindex(1));
    if ( stream == NULL ) {
        if ( lua_gettop(L) >= 1 && lua_isstring(L, 1) ) {
            lua_pushfstring(L, "IllegalState: calling %s function when stream was previously closed", name);
            lua_error(L);
        }
        lua_pushstring(L, "");
        lua_pushboolean(L, 1);
        return 2; /* Ignore duplicate calls to "close". */
    }

    luaL_buffinit(L, &buff);

    if ( lua_gettop(L) > 1 ) lua_pushvalue(L, 1);

    if ( lua_isstring(L, lua_upvalueindex(2)) ) {
        lua_pushvalue(L, lua_upvalueindex(2));
        if ( lua_gettop(L) > 1 && lua_isstring(L, -2) ) {
            lua_concat(L, 2);
        }
    }

    /*  Do the actual deflate'ing: */
    stream->next_in = lua_gettop(L) > 0 ?
        (unsigned char*)lua_tolstring(L, -1, &avail_in) :
        NULL;
    stream->avail_in = (uInt)avail_in;

    if ( ! stream->avail_in && ! flush ) {
        /*  Passed empty string, make it a noop instead of erroring out. */
        lua_pushstring(L, "");
        lua_pushboolean(L, 0);
        lua_pushinteger(L, stream->total_in);
        lua_pushinteger(L, stream->total_out);
        return 4;
    }

    do {
        stream->next_out  = (unsigned char*)luaL_prepbuffer(&buff);
        stream->avail_out = LUAL_BUFFERSIZE;
        result = filter(stream, flush);
        if ( Z_BUF_ERROR != result ) {
            /* Ignore Z_BUF_ERROR since that just indicates that we
             * need a larger buffer in order to proceed.  Thanks to
             * Tobias Markmann for finding this bug!
             */
            lz_assert(L, result, stream, __FILE__, __LINE__);
        }
        luaL_addsize(&buff, LUAL_BUFFERSIZE - stream->avail_out);
    } while ( stream->avail_out == 0 );

    /*  Need to do this before we alter the stack: */
    luaL_pushresult(&buff);

    /*  Save remainder in lua_upvalueindex(2): */
    if ( NULL != stream->next_in ) {
        lua_pushlstring(L, (char*)stream->next_in, stream->avail_in);
        lua_replace(L, lua_upvalueindex(2));
    }

    /*  "close" the stream/remove finalizer: */
    if ( result == Z_STREAM_END ) {
        /*  Clear-out the metatable so end is not called twice: */
        lua_pushnil(L);
        lua_setmetatable(L, lua_upvalueindex(1));

        /*  nil the upvalue: */
        lua_pushnil(L);
        lua_replace(L, lua_upvalueindex(1));

        /*  Close the stream: */
        lz_assert(L, end(stream), stream, __FILE__, __LINE__);

        lua_pushboolean(L, 1);
    } else {
        lua_pushboolean(L, 0);
    }
    lua_pushinteger(L, stream->total_in);
    lua_pushinteger(L, stream->total_out);
    return 4;
}

static void lz_create_deflate_mt(lua_State *L) {
    luaL_newmetatable(L, "lz.deflate.meta"); /*  {} */

    lua_pushcfunction(L, lz_deflate_delete);
    lua_setfield(L, -2, "__gc");

    lua_pop(L, 1); /*  <empty> */
}

static int lz_deflate_new(lua_State *L) {
    int level = luaL_optint(L, 1, Z_DEFAULT_COMPRESSION);

    /*  Allocate the stream: */
    z_stream* stream = (z_stream*)lua_newuserdata(L, sizeof(z_stream));

    stream->zalloc = Z_NULL;
    stream->zfree  = Z_NULL;
    lz_assert(L, deflateInit(stream, level), stream, __FILE__, __LINE__);

    /*  Don't allow destructor to execute unless deflateInit was successful: */
    luaL_getmetatable(L, "lz.deflate.meta");
    lua_setmetatable(L, -2);

    lua_pushnil(L);
    lua_pushcclosure(L, lz_deflate, 2);
    return 1;
}

static int lz_deflate(lua_State *L) {
    return lz_filter_impl(L, deflate, deflateEnd, "deflate");
}

static int lz_deflate_delete(lua_State *L) {
    z_stream* stream  = (z_stream*)lua_touserdata(L, 1);

    /*  Ignore errors. */
    deflateEnd(stream);

    return 0;
}


static void lz_create_inflate_mt(lua_State *L) {
    luaL_newmetatable(L, "lz.inflate.meta"); /*  {} */

    lua_pushcfunction(L, lz_inflate_delete);
    lua_setfield(L, -2, "__gc");

    lua_pop(L, 1); /*  <empty> */
}

static int lz_inflate_new(lua_State *L) {
    /* Allocate the stream */
    z_stream* stream = (z_stream*)lua_newuserdata(L, sizeof(z_stream));

    /*  By default, we will do gzip header detection w/ max window size */
    lua_Integer window_size = lua_isnumber(L, 1) ? lua_tointeger(L, 1) : MAX_WBITS + 32;

    stream->zalloc   = Z_NULL;
    stream->zfree    = Z_NULL;
    stream->next_in  = Z_NULL;
    stream->avail_in = 0;

    lz_assert(L, inflateInit2(stream, window_size), stream, __FILE__, __LINE__);

    /*  Don't allow destructor to execute unless deflateInit was successful: */
    luaL_getmetatable(L, "lz.inflate.meta");
    lua_setmetatable(L, -2);

    lua_pushnil(L);
    lua_pushcclosure(L, lz_inflate, 2);
    return 1;
}

static int lz_inflate(lua_State *L) {
    return lz_filter_impl(L, inflate, inflateEnd, "inflate");
}

static int lz_inflate_delete(lua_State *L) {
    z_stream* stream  = (z_stream*)lua_touserdata(L, 1);

    /*  Ignore errors: */
    inflateEnd(stream);

    return 0;
}

static int lz_checksum(lua_State *L) {
    if ( lua_gettop(L) <= 0 ) {
        lua_pushvalue(L, lua_upvalueindex(3));
        lua_pushvalue(L, lua_upvalueindex(4));
    } else if ( lua_isfunction(L, 1) ) {
        checksum_combine_t combine = (checksum_combine_t)
            lua_touserdata(L, lua_upvalueindex(2));

        lua_pushvalue(L, 1);
        lua_call(L, 0, 2);
        if ( ! lua_isnumber(L, -2) || ! lua_isnumber(L, -1) ) {
            luaL_argerror(L, 1, "expected function to return two numbers");
        }

        /* Calculate and replace the checksum */
        lua_pushnumber(L,
                       combine((uLong)lua_tonumber(L, lua_upvalueindex(3)),
                               (uLong)lua_tonumber(L, -2),
                               (z_off_t)lua_tonumber(L, -1)));
        lua_pushvalue(L, -1);
        lua_replace(L, lua_upvalueindex(3));

        /* Calculate and replace the length */
        lua_pushnumber(L,
                       lua_tonumber(L, lua_upvalueindex(4)) + lua_tonumber(L, -2));
        lua_pushvalue(L, -1);
        lua_replace(L, lua_upvalueindex(4));
    } else {
        const Bytef* str;
        size_t       len;

        checksum_t checksum = (checksum_t)
            lua_touserdata(L, lua_upvalueindex(1));
        str = (const Bytef*)luaL_checklstring(L, 1, &len);
 
        /* Calculate and replace the checksum */
        lua_pushnumber(L,
                       checksum((uLong)lua_tonumber(L, lua_upvalueindex(3)),
                                str,
                                (int)len));
        lua_pushvalue(L, -1);
        lua_replace(L, lua_upvalueindex(3));
        
        /* Calculate and replace the length */
        lua_pushnumber(L,
                       lua_tonumber(L, lua_upvalueindex(4)) + len);
        lua_pushvalue(L, -1);
        lua_replace(L, lua_upvalueindex(4));
    }
    return 2;
}

static int lz_checksum_new(lua_State *L, checksum_t checksum, checksum_combine_t combine) {
    lua_pushlightuserdata(L, checksum);
    lua_pushlightuserdata(L, combine);
    lua_pushnumber(L, checksum(0L, Z_NULL, 0));
    lua_pushnumber(L, 0);
    lua_pushcclosure(L, lz_checksum, 4);
    return 1;
}

static int lz_adler32(lua_State *L) {
    return lz_checksum_new(L, adler32, adler32_combine);
}

static int lz_crc32(lua_State *L) {
    return lz_checksum_new(L, crc32, crc32_combine);
}

static const luaL_Reg zlib_functions[] = {
    { "deflate", lz_deflate_new },
    { "inflate", lz_inflate_new },
    { "adler32", lz_adler32     },
    { "crc32",   lz_crc32       },
    { "version", lz_version     },
    { NULL,      NULL           }
};

#define SETLITERAL(n,v) (lua_pushliteral(L, n), lua_pushliteral(L, v), lua_settable(L, -3))
#define SETINT(n,v) (lua_pushliteral(L, n), lua_pushinteger(L, v), lua_settable(L, -3))

LUALIB_API int luaopen_zlib(lua_State * const L) {
    lz_create_deflate_mt(L);
    lz_create_inflate_mt(L);

    luaL_register(L, "zlib", zlib_functions);

    SETINT("BEST_SPEED", Z_BEST_SPEED);
    SETINT("BEST_COMPRESSION", Z_BEST_COMPRESSION);

    SETLITERAL("_COPYRIGHT", "Copyright (c) 2009-2010 Brian Maher");
    SETLITERAL("_DESCRIPTION", "Yet another binding to the zlib library");
    SETLITERAL("_VERSION", "lua-zlib $Id: c9f86792ac86380927af9b2393a874e0a2c3f9e5 $  (HEAD, master)");

    /* Expose this to lua so we can do a test: */
    SETINT("_TEST_BUFSIZ", LUAL_BUFFERSIZE);

    return 1;
}
