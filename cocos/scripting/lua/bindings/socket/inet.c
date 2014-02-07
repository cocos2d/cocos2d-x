/*=========================================================================*\
* Internet domain functions
* LuaSocket toolkit
\*=========================================================================*/
#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"

#include "inet.h"

/*=========================================================================*\
* Internal function prototypes.
\*=========================================================================*/
static int inet_global_toip(lua_State *L);
static int inet_global_getaddrinfo(lua_State *L);
static int inet_global_tohostname(lua_State *L);
static int inet_global_getnameinfo(lua_State *L);
static void inet_pushresolved(lua_State *L, struct hostent *hp);
static int inet_global_gethostname(lua_State *L);

/* DNS functions */
static luaL_Reg func[] = {
    { "toip", inet_global_toip},
    { "getaddrinfo", inet_global_getaddrinfo},
    { "tohostname", inet_global_tohostname},
    { "getnameinfo", inet_global_getnameinfo},
    { "gethostname", inet_global_gethostname},
    { NULL, NULL}
};

#ifdef _WINDOWS_
/****luodx patch for windows xp start**/
char* win32xp_inet_ntop(int family, PVOID src, char* dest, size_t length)
{
	char* result = inet_ntoa(*(IN_ADDR*)src);
	if (result != NULL){
		strcpy(dest, result);
	}
	return result;
}

int win32xp_inet_pton(int family, const char* string, PVOID dest) {
	return inet_aton(string, (IN_ADDR*)dest);
}
/****luodx patch for windows xp end**/
#endif


/*=========================================================================*\
* Exported functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Initializes module
\*-------------------------------------------------------------------------*/
int inet_open(lua_State *L)
{
    lua_pushstring(L, "dns");
    lua_newtable(L);
    luaL_openlib(L, NULL, func, 0);
    lua_settable(L, -3);
    return 0;
}

/*=========================================================================*\
* Global Lua functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Returns all information provided by the resolver given a host name
* or ip address
\*-------------------------------------------------------------------------*/
static int inet_gethost(const char *address, struct hostent **hp) {
    struct in_addr addr;
    if (inet_aton(address, &addr))
        return socket_gethostbyaddr((char *) &addr, sizeof(addr), hp);
    else
        return socket_gethostbyname(address, hp);
}

/*-------------------------------------------------------------------------*\
* Returns all information provided by the resolver given a host name
* or ip address
\*-------------------------------------------------------------------------*/
static int inet_global_tohostname(lua_State *L) {
    const char *address = luaL_checkstring(L, 1);
    struct hostent *hp = NULL;
    int err = inet_gethost(address, &hp);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, socket_hoststrerror(err));
        return 2;
    }
    lua_pushstring(L, hp->h_name);
    inet_pushresolved(L, hp);
    return 2;
}

static int inet_global_getnameinfo(lua_State *L) {
    int i, ret;
    char host[1024];
    char serv[32];
    struct addrinfo hints;
    struct addrinfo *resolved, *iter;
    const char *node = luaL_optstring(L, 1, NULL);
    const char *service = luaL_optstring(L, 2, NULL);

    if (!(node || service))
        luaL_error(L, "You have to specify a hostname, a service, or both");

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = PF_UNSPEC;

    /* getaddrinfo must get a node and a service argument */
    ret = getaddrinfo(node ? node : "127.0.0.1", service ? service : "7",
        &hints, &resolved);
    if (ret != 0) {
        lua_pushnil(L);
        lua_pushstring(L, socket_gaistrerror(ret));
        return 2;
    }

    lua_newtable(L);
    for (i = 1, iter = resolved; iter; i++, iter = iter->ai_next) {
        getnameinfo(iter->ai_addr, (socklen_t) iter->ai_addrlen, host,
            node ? (socklen_t) sizeof(host) : 0, serv, service ? (socklen_t) sizeof(serv) : 0, 0);

        if (node) {
            lua_pushnumber(L, i);
            lua_pushstring(L, host);
            lua_settable(L, -3);
        }
    }
    freeaddrinfo(resolved);

    if (service) {
        lua_pushstring(L, serv);
        return 2;
    } else {
        return 1;
    }
}

/*-------------------------------------------------------------------------*\
* Returns all information provided by the resolver given a host name
* or ip address
\*-------------------------------------------------------------------------*/
static int inet_global_toip(lua_State *L)
{
    const char *address = luaL_checkstring(L, 1);
    struct hostent *hp = NULL;
    int err = inet_gethost(address, &hp);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, socket_hoststrerror(err));
        return 2;
    }
    lua_pushstring(L, inet_ntoa(*((struct in_addr *) hp->h_addr)));
    inet_pushresolved(L, hp);
    return 2;
}

int inet_optfamily(lua_State* L, int narg, const char* def)
{
    static const char* optname[] = { "unspec", "inet", "inet6", NULL };
    static int optvalue[] = { PF_UNSPEC, PF_INET, PF_INET6, 0 };

    return optvalue[luaL_checkoption(L, narg, def, optname)];
}

int inet_optsocktype(lua_State* L, int narg, const char* def)
{
    static const char* optname[] = { "stream", "dgram", NULL };
    static int optvalue[] = { SOCK_STREAM, SOCK_DGRAM, 0 };

    return optvalue[luaL_checkoption(L, narg, def, optname)];
}

static int inet_global_getaddrinfo(lua_State *L)
{
    const char *hostname = luaL_checkstring(L, 1);
    struct addrinfo *iterator = NULL, *resolved = NULL;
    struct addrinfo hints;
    int i = 1, ret = 0;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = PF_UNSPEC;
    ret = getaddrinfo(hostname, NULL, &hints, &resolved);
    if (ret != 0) {
        lua_pushnil(L);
        lua_pushstring(L, socket_gaistrerror(ret));
        return 2;
    }
    lua_newtable(L);
    for (iterator = resolved; iterator; iterator = iterator->ai_next) {
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        getnameinfo(iterator->ai_addr, (socklen_t) iterator->ai_addrlen, hbuf, 
            (socklen_t) sizeof(hbuf), sbuf, 0, NI_NUMERICHOST);
        lua_pushnumber(L, i);
        lua_newtable(L);
        switch (iterator->ai_family) {
            case AF_INET:
                lua_pushliteral(L, "family");
                lua_pushliteral(L, "inet");
                lua_settable(L, -3);
                break;
            case AF_INET6:
                lua_pushliteral(L, "family");
                lua_pushliteral(L, "inet6");
                lua_settable(L, -3);
                break;;
        }
        lua_pushliteral(L, "addr");
        lua_pushstring(L, hbuf);
        lua_settable(L, -3);
        lua_settable(L, -3);
        i++;
    }
    freeaddrinfo(resolved);
    return 1;
}


/*-------------------------------------------------------------------------*\
* Gets the host name
\*-------------------------------------------------------------------------*/
static int inet_global_gethostname(lua_State *L)
{
    char name[257];
    name[256] = '\0';
    if (gethostname(name, 256) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(errno));
        return 2;
    } else {
        lua_pushstring(L, name);
        return 1;
    }
}



/*=========================================================================*\
* Lua methods
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Retrieves socket peer name
\*-------------------------------------------------------------------------*/
int inet_meth_getpeername(lua_State *L, p_socket ps, int family)
{
    switch (family) {
        case PF_INET: {
            struct sockaddr_in peer;
            socklen_t peer_len = sizeof(peer);
            char name[INET_ADDRSTRLEN];
            if (getpeername(*ps, (SA *) &peer, &peer_len) < 0) {
                lua_pushnil(L);
                lua_pushstring(L, socket_strerror(errno));
                return 2;
            } else {
                my_inet_ntop(family, &peer.sin_addr, name, sizeof(name));
                lua_pushstring(L, name); 
                lua_pushnumber(L, ntohs(peer.sin_port));
                lua_pushliteral(L, "inet");
                return 3;
            }
        }
        case PF_INET6: {
            struct sockaddr_in6 peer;
            socklen_t peer_len = sizeof(peer);
            char name[INET6_ADDRSTRLEN];
            if (getpeername(*ps, (SA *) &peer, &peer_len) < 0) {
                lua_pushnil(L);
                lua_pushstring(L, socket_strerror(errno));
                return 2;
            } else {
                my_inet_ntop(family, &peer.sin6_addr, name, sizeof(name));
                lua_pushstring(L, name); 
                lua_pushnumber(L, ntohs(peer.sin6_port));
                lua_pushliteral(L, "inet6");
                return 3;
            }
        }
        default:
            lua_pushnil(L);
            lua_pushfstring(L, "unknown family %d", family);
            return 2;
    }
}

/*-------------------------------------------------------------------------*\
* Retrieves socket local name
\*-------------------------------------------------------------------------*/
int inet_meth_getsockname(lua_State *L, p_socket ps, int family)
{
    switch (family) {
        case PF_INET: {
            struct sockaddr_in local;
            socklen_t local_len = sizeof(local);
            char name[INET_ADDRSTRLEN];
            if (getsockname(*ps, (SA *) &local, &local_len) < 0) {
                lua_pushnil(L);
                lua_pushstring(L, socket_strerror(errno));
                return 2;
            } else {
                my_inet_ntop(family, &local.sin_addr, name, sizeof(name));
                lua_pushstring(L, name); 
                lua_pushnumber(L, ntohs(local.sin_port));
                lua_pushliteral(L, "inet");
                return 3;
            }
        }
        case PF_INET6: {
            struct sockaddr_in6 local;
            socklen_t local_len = sizeof(local);
            char name[INET6_ADDRSTRLEN];
            if (getsockname(*ps, (SA *) &local, &local_len) < 0) {
                lua_pushnil(L);
                lua_pushstring(L, socket_strerror(errno));
                return 2;
            } else {
                my_inet_ntop(family, &local.sin6_addr, name, sizeof(name));
                lua_pushstring(L, name); 
                lua_pushnumber(L, ntohs(local.sin6_port));
                lua_pushliteral(L, "inet6");
                return 3;
            }
        }
        default:
            lua_pushnil(L);
            lua_pushfstring(L, "unknown family %d", family);
            return 2;
    }
}

/*=========================================================================*\
* Internal functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Passes all resolver information to Lua as a table
\*-------------------------------------------------------------------------*/
static void inet_pushresolved(lua_State *L, struct hostent *hp)
{
    char **alias;
    struct in_addr **addr;
    int i, resolved;
    lua_newtable(L); resolved = lua_gettop(L);
    lua_pushstring(L, "name");
    lua_pushstring(L, hp->h_name);
    lua_settable(L, resolved);
    lua_pushstring(L, "ip");
    lua_pushstring(L, "alias");
    i = 1;
    alias = hp->h_aliases;
    lua_newtable(L);
    if (alias) {
        while (*alias) {
            lua_pushnumber(L, i);
            lua_pushstring(L, *alias);
            lua_settable(L, -3);
            i++; alias++;
        }
    }
    lua_settable(L, resolved);
    i = 1;
    lua_newtable(L);
    addr = (struct in_addr **) hp->h_addr_list;
    if (addr) {
        while (*addr) {
            lua_pushnumber(L, i);
            lua_pushstring(L, inet_ntoa(**addr));
            lua_settable(L, -3);
            i++; addr++;
        }
    }
    lua_settable(L, resolved);
}

/*-------------------------------------------------------------------------*\
* Tries to create a new inet socket
\*-------------------------------------------------------------------------*/
const char *inet_trycreate(p_socket ps, int family, int type) {
    return socket_strerror(socket_create(ps, family, type, 0));
}

/*-------------------------------------------------------------------------*\
* "Disconnects" a DGRAM socket
\*-------------------------------------------------------------------------*/
const char *inet_trydisconnect(p_socket ps, int family, p_timeout tm)
{
    switch (family) {
        case PF_INET: {
            struct sockaddr_in sin;
            memset((char *) &sin, 0, sizeof(sin));
            sin.sin_family = AF_UNSPEC;
            sin.sin_addr.s_addr = INADDR_ANY;
            return socket_strerror(socket_connect(ps, (SA *) &sin, 
                sizeof(sin), tm));
        }
        case PF_INET6: {
            struct sockaddr_in6 sin6;
            struct in6_addr addrany = IN6ADDR_ANY_INIT; 
            memset((char *) &sin6, 0, sizeof(sin6));
            sin6.sin6_family = AF_UNSPEC;
fprintf(stderr, "disconnecting\n");
            sin6.sin6_addr = addrany;
            return socket_strerror(socket_connect(ps, (SA *) &sin6, 
                sizeof(sin6), tm));
        }
    }
    return NULL;
}

/*-------------------------------------------------------------------------*\
* Tries to connect to remote address (address, port)
\*-------------------------------------------------------------------------*/
const char *inet_tryconnect(p_socket ps, const char *address,
        const char *serv, p_timeout tm, struct addrinfo *connecthints)
{
    struct addrinfo *iterator = NULL, *resolved = NULL;
    const char *err = NULL;
    /* try resolving */
    err = socket_gaistrerror(getaddrinfo(address, serv,
                connecthints, &resolved));
    if (err != NULL) {
        if (resolved) freeaddrinfo(resolved);
        return err;
    }
    for (iterator = resolved; iterator; iterator = iterator->ai_next) {
        timeout_markstart(tm);
        /* try connecting to remote address */
        err = socket_strerror(socket_connect(ps, (SA *) iterator->ai_addr, 
            (socklen_t) iterator->ai_addrlen, tm));
        /* if success, break out of loop */
        if (err == NULL) break;
    }
    freeaddrinfo(resolved);
    /* here, if err is set, we failed */
    return err;
}

/*-------------------------------------------------------------------------*\
* Tries to accept a socket
\*-------------------------------------------------------------------------*/
const char *inet_tryaccept(p_socket server, int family, p_socket client, p_timeout tm)
{
	socklen_t len;
	t_sockaddr_storage addr;
	if (family == PF_INET6) {
		len = sizeof(struct sockaddr_in6);
	} else {
		len = sizeof(struct sockaddr_in);
	}
	return socket_strerror(socket_accept(server, client, (SA *) &addr, &len, tm));
}

/*-------------------------------------------------------------------------*\
* Tries to bind socket to (address, port)
\*-------------------------------------------------------------------------*/
const char *inet_trybind(p_socket ps, const char *address, const char *serv,
        struct addrinfo *bindhints)
{
    struct addrinfo *iterator = NULL, *resolved = NULL;
    const char *err = NULL;
    t_socket sock = *ps;
    /* try resolving */
    err = socket_gaistrerror(getaddrinfo(address, serv, bindhints, &resolved));
    if (err) {
        if (resolved) freeaddrinfo(resolved);
        return err;
    }
    /* iterate over resolved addresses until one is good */
    for (iterator = resolved; iterator; iterator = iterator->ai_next) {
        if(sock == SOCKET_INVALID) {
            err = socket_strerror(socket_create(&sock, iterator->ai_family,
                        iterator->ai_socktype, iterator->ai_protocol));
            if(err)
                continue;
        }
        /* try binding to local address */
        err = socket_strerror(socket_bind(&sock,
            (SA *) iterator->ai_addr,
            (socklen_t) iterator->ai_addrlen));

        /* keep trying unless bind succeeded */
        if (err) {
            if(sock != *ps)
                socket_destroy(&sock);
        } else {
            /* remember what we connected to, particularly the family */
            *bindhints = *iterator;
            break;
        }
    }
    /* cleanup and return error */
    freeaddrinfo(resolved);
    *ps = sock;
    return err;
}

/*-------------------------------------------------------------------------*\
* Some systems do not provide this so that we provide our own. It's not
* marvelously fast, but it works just fine.
\*-------------------------------------------------------------------------*/
#ifdef INET_ATON
int inet_aton(const char *cp, struct in_addr *inp)
{
    unsigned int a = 0, b = 0, c = 0, d = 0;
    int n = 0, r;
    unsigned long int addr = 0;
    r = sscanf(cp, "%u.%u.%u.%u%n", &a, &b, &c, &d, &n);
    if (r == 0 || n == 0) return 0;
    cp += n;
    if (*cp) return 0;
    if (a > 255 || b > 255 || c > 255 || d > 255) return 0;
    if (inp) {
        addr += a; addr <<= 8;
        addr += b; addr <<= 8;
        addr += c; addr <<= 8;
        addr += d;
        inp->s_addr = htonl(addr);
    }
    return 1;
}
#endif


