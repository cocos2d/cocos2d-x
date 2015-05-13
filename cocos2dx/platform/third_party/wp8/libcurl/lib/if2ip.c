/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
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
 ***************************************************************************/

#include "curl_setup.h"

#ifdef HAVE_NETINET_IN_H
#  include <netinet/in.h>
#endif
#ifdef HAVE_ARPA_INET_H
#  include <arpa/inet.h>
#endif
#ifdef HAVE_NET_IF_H
#  include <net/if.h>
#endif
#ifdef HAVE_SYS_IOCTL_H
#  include <sys/ioctl.h>
#endif
#ifdef HAVE_NETDB_H
#  include <netdb.h>
#endif
#ifdef HAVE_SYS_SOCKIO_H
#  include <sys/sockio.h>
#endif
#ifdef HAVE_IFADDRS_H
#  include <ifaddrs.h>
#endif
#ifdef HAVE_STROPTS_H
#  include <stropts.h>
#endif
#ifdef __VMS
#  include <inet.h>
#endif

#include "inet_ntop.h"
#include "strequal.h"
#include "if2ip.h"

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

#include "curl_memory.h"
/* The last #include file should be: */
#include "memdebug.h"

/* ------------------------------------------------------------------ */

#if defined(HAVE_GETIFADDRS)

bool Curl_if_is_interface_name(const char *interf)
{
  bool result = FALSE;

  struct ifaddrs *iface, *head;

  if(getifaddrs(&head) >= 0) {
    for(iface=head; iface != NULL; iface=iface->ifa_next) {
      if(curl_strequal(iface->ifa_name, interf)) {
        result = TRUE;
        break;
      }
    }
    freeifaddrs(head);
  }
  return result;
}

if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
                          const char *interf, char *buf, int buf_size)
{
  struct ifaddrs *iface, *head;
  if2ip_result_t res = IF2IP_NOT_FOUND;

#ifndef ENABLE_IPV6
  (void) remote_scope;
#endif

  if(getifaddrs(&head) >= 0) {
    for(iface=head; iface != NULL; iface=iface->ifa_next) {
      if(iface->ifa_addr != NULL) {
        if(iface->ifa_addr->sa_family == af) {
          if(curl_strequal(iface->ifa_name, interf)) {
            void *addr;
            char *ip;
            char scope[12]="";
            char ipstr[64];
#ifdef ENABLE_IPV6
            if(af == AF_INET6) {
              unsigned int scopeid = 0;
              addr = &((struct sockaddr_in6 *)iface->ifa_addr)->sin6_addr;
#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
              /* Include the scope of this interface as part of the address */
              scopeid =
                ((struct sockaddr_in6 *)iface->ifa_addr)->sin6_scope_id;
#endif
              if(scopeid != remote_scope) {
                /* We are interested only in interface addresses whose
                   scope ID matches the remote address we want to
                   connect to: global (0) for global, link-local for
                   link-local, etc... */
                if(res == IF2IP_NOT_FOUND) res = IF2IP_AF_NOT_SUPPORTED;
                continue;
              }
              if(scopeid)
                snprintf(scope, sizeof(scope), "%%%u", scopeid);
            }
            else
#endif
              addr = &((struct sockaddr_in *)iface->ifa_addr)->sin_addr;
            res = IF2IP_FOUND;
            ip = (char *) Curl_inet_ntop(af, addr, ipstr, sizeof(ipstr));
            snprintf(buf, buf_size, "%s%s", ip, scope);
            break;
          }
        }
        else if((res == IF2IP_NOT_FOUND) &&
                curl_strequal(iface->ifa_name, interf)) {
          res = IF2IP_AF_NOT_SUPPORTED;
        }
      }
    }
    freeifaddrs(head);
  }
  return res;
}

#elif defined(HAVE_IOCTL_SIOCGIFADDR)

bool Curl_if_is_interface_name(const char *interf)
{
  /* This is here just to support the old interfaces */
  char buf[256];

  return (Curl_if2ip(AF_INET, 0, interf, buf, sizeof(buf)) ==
          IF2IP_NOT_FOUND) ? FALSE : TRUE;
}

if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
                          const char *interf, char *buf, int buf_size)
{
  struct ifreq req;
  struct in_addr in;
  struct sockaddr_in *s;
  curl_socket_t dummy;
  size_t len;

  (void)remote_scope;

  if(!interf || (af != AF_INET))
    return IF2IP_NOT_FOUND;

  len = strlen(interf);
  if(len >= sizeof(req.ifr_name))
    return IF2IP_NOT_FOUND;

  dummy = socket(AF_INET, SOCK_STREAM, 0);
  if(CURL_SOCKET_BAD == dummy)
    return IF2IP_NOT_FOUND;

  memset(&req, 0, sizeof(req));
  memcpy(req.ifr_name, interf, len+1);
  req.ifr_addr.sa_family = AF_INET;

  if(ioctl(dummy, SIOCGIFADDR, &req) < 0) {
    sclose(dummy);
    /* With SIOCGIFADDR, we cannot tell the difference between an interface
       that does not exist and an interface that has no address of the
       correct family. Assume the interface does not exist */
    return IF2IP_NOT_FOUND;
  }

  s = (struct sockaddr_in *)&req.ifr_addr;
  memcpy(&in, &s->sin_addr, sizeof(in));
  Curl_inet_ntop(s->sin_family, &in, buf, buf_size);

  sclose(dummy);
  return IF2IP_FOUND;
}

#else

bool Curl_if_is_interface_name(const char *interf)
{
  (void) interf;

  return FALSE;
}

if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
                          const char *interf, char *buf, int buf_size)
{
    (void) af;
    (void) remote_scope;
    (void) interf;
    (void) buf;
    (void) buf_size;
    return IF2IP_NOT_FOUND;
}

#endif
