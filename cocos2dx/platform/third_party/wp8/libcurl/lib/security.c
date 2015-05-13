/* This source code was modified by Martin Hedenfalk <mhe@stacken.kth.se> for
 * use in Curl. His latest changes were done 2000-09-18.
 *
 * It has since been patched and modified a lot by Daniel Stenberg
 * <daniel@haxx.se> to make it better applied to curl conditions, and to make
 * it not use globals, pollute name space and more. This source code awaits a
 * rewrite to work around the paragraph 2 in the BSD licenses as explained
 * below.
 *
 * Copyright (c) 1998, 1999, 2013 Kungliga Tekniska H�gskolan
 * (Royal Institute of Technology, Stockholm, Sweden).
 *
 * Copyright (C) 2001 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.  */

#include "curl_setup.h"

#ifndef CURL_DISABLE_FTP
#ifdef HAVE_GSSAPI

#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif

#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif

#include "urldata.h"
#include "curl_base64.h"
#include "curl_memory.h"
#include "curl_sec.h"
#include "ftp.h"
#include "sendf.h"
#include "rawstr.h"
#include "warnless.h"

/* The last #include file should be: */
#include "memdebug.h"

static const struct {
  enum protection_level level;
  const char *name;
} level_names[] = {
  { PROT_CLEAR, "clear" },
  { PROT_SAFE, "safe" },
  { PROT_CONFIDENTIAL, "confidential" },
  { PROT_PRIVATE, "private" }
};

static enum protection_level
name_to_level(const char *name)
{
  int i;
  for(i = 0; i < (int)sizeof(level_names)/(int)sizeof(level_names[0]); i++)
    if(checkprefix(name, level_names[i].name))
      return level_names[i].level;
  return PROT_NONE;
}

/* Convert a protocol |level| to its char representation.
   We take an int to catch programming mistakes. */
static char level_to_char(int level) {
  switch(level) {
  case PROT_CLEAR:
    return 'C';
  case PROT_SAFE:
    return 'S';
  case PROT_CONFIDENTIAL:
    return 'E';
  case PROT_PRIVATE:
    return 'P';
  case PROT_CMD:
    /* Fall through */
  default:
    /* Those 2 cases should not be reached! */
    break;
  }
  DEBUGASSERT(0);
  /* Default to the most secure alternative. */
  return 'P';
}

static const struct Curl_sec_client_mech * const mechs[] = {
#ifdef HAVE_GSSAPI
  &Curl_krb5_client_mech,
#endif
  NULL
};

/* Send an FTP command defined by |message| and the optional arguments. The
   function returns the ftp_code. If an error occurs, -1 is returned. */
static int ftp_send_command(struct connectdata *conn, const char *message, ...)
{
  int ftp_code;
  ssize_t nread;
  va_list args;
  char print_buffer[50];

  va_start(args, message);
  vsnprintf(print_buffer, sizeof(print_buffer), message, args);
  va_end(args);

  if(Curl_ftpsendf(conn, print_buffer) != CURLE_OK) {
    ftp_code = -1;
  }
  else {
    if(Curl_GetFTPResponse(&nread, conn, &ftp_code) != CURLE_OK)
      ftp_code = -1;
  }

  (void)nread; /* Unused */
  return ftp_code;
}

/* Read |len| from the socket |fd| and store it in |to|. Return a CURLcode
   saying whether an error occurred or CURLE_OK if |len| was read. */
static CURLcode
socket_read(curl_socket_t fd, void *to, size_t len)
{
  char *to_p = to;
  CURLcode code;
  ssize_t nread;

  while(len > 0) {
    code = Curl_read_plain(fd, to_p, len, &nread);
    if(code == CURLE_OK) {
      len -= nread;
      to_p += nread;
    }
    else {
      /* FIXME: We are doing a busy wait */
      if(code == CURLE_AGAIN)
        continue;
      return code;
    }
  }
  return CURLE_OK;
}


/* Write |len| bytes from the buffer |to| to the socket |fd|. Return a
   CURLcode saying whether an error occurred or CURLE_OK if |len| was
   written. */
static CURLcode
socket_write(struct connectdata *conn, curl_socket_t fd, const void *to,
             size_t len)
{
  const char *to_p = to;
  CURLcode code;
  ssize_t written;

  while(len > 0) {
    code = Curl_write_plain(conn, fd, to_p, len, &written);
    if(code == CURLE_OK) {
      len -= written;
      to_p += written;
    }
    else {
      /* FIXME: We are doing a busy wait */
      if(code == CURLE_AGAIN)
        continue;
      return code;
    }
  }
  return CURLE_OK;
}

static CURLcode read_data(struct connectdata *conn,
                          curl_socket_t fd,
                          struct krb5buffer *buf)
{
  int len;
  void* tmp;
  CURLcode ret;

  ret = socket_read(fd, &len, sizeof(len));
  if(ret != CURLE_OK)
    return ret;

  len = ntohl(len);
  tmp = realloc(buf->data, len);
  if(tmp == NULL)
    return CURLE_OUT_OF_MEMORY;

  buf->data = tmp;
  ret = socket_read(fd, buf->data, len);
  if(ret != CURLE_OK)
    return ret;
  buf->size = conn->mech->decode(conn->app_data, buf->data, len,
                                 conn->data_prot, conn);
  buf->index = 0;
  return CURLE_OK;
}

static size_t
buffer_read(struct krb5buffer *buf, void *data, size_t len)
{
  if(buf->size - buf->index < len)
    len = buf->size - buf->index;
  memcpy(data, (char*)buf->data + buf->index, len);
  buf->index += len;
  return len;
}

/* Matches Curl_recv signature */
static ssize_t sec_recv(struct connectdata *conn, int sockindex,
                        char *buffer, size_t len, CURLcode *err)
{
  size_t bytes_read;
  size_t total_read = 0;
  curl_socket_t fd = conn->sock[sockindex];

  *err = CURLE_OK;

  /* Handle clear text response. */
  if(conn->sec_complete == 0 || conn->data_prot == PROT_CLEAR)
      return read(fd, buffer, len);

  if(conn->in_buffer.eof_flag) {
    conn->in_buffer.eof_flag = 0;
    return 0;
  }

  bytes_read = buffer_read(&conn->in_buffer, buffer, len);
  len -= bytes_read;
  total_read += bytes_read;
  buffer += bytes_read;

  while(len > 0) {
    if(read_data(conn, fd, &conn->in_buffer) != CURLE_OK)
      return -1;
    if(conn->in_buffer.size == 0) {
      if(bytes_read > 0)
        conn->in_buffer.eof_flag = 1;
      return bytes_read;
    }
    bytes_read = buffer_read(&conn->in_buffer, buffer, len);
    len -= bytes_read;
    total_read += bytes_read;
    buffer += bytes_read;
  }
  /* FIXME: Check for overflow */
  return total_read;
}

/* Send |length| bytes from |from| to the |fd| socket taking care of encoding
   and negociating with the server. |from| can be NULL. */
/* FIXME: We don't check for errors nor report any! */
static void do_sec_send(struct connectdata *conn, curl_socket_t fd,
                        const char *from, int length)
{
  int bytes, htonl_bytes; /* 32-bit integers for htonl */
  char *buffer = NULL;
  char *cmd_buffer;
  size_t cmd_size = 0;
  CURLcode error;
  enum protection_level prot_level = conn->data_prot;
  bool iscmd = (prot_level == PROT_CMD)?TRUE:FALSE;

  DEBUGASSERT(prot_level > PROT_NONE && prot_level < PROT_LAST);

  if(iscmd) {
    if(!strncmp(from, "PASS ", 5) || !strncmp(from, "ACCT ", 5))
      prot_level = PROT_PRIVATE;
    else
      prot_level = conn->command_prot;
  }
  bytes = conn->mech->encode(conn->app_data, from, length, prot_level,
                             (void**)&buffer, conn);
  if(!buffer || bytes <= 0)
    return; /* error */

  if(iscmd) {
    error = Curl_base64_encode(conn->data, buffer, curlx_sitouz(bytes),
                               &cmd_buffer, &cmd_size);
    if(error) {
      free(buffer);
      return; /* error */
    }
    if(cmd_size > 0) {
      static const char *enc = "ENC ";
      static const char *mic = "MIC ";
      if(prot_level == PROT_PRIVATE)
        socket_write(conn, fd, enc, 4);
      else
        socket_write(conn, fd, mic, 4);

      socket_write(conn, fd, cmd_buffer, cmd_size);
      socket_write(conn, fd, "\r\n", 2);
      infof(conn->data, "Send: %s%s\n", prot_level == PROT_PRIVATE?enc:mic,
            cmd_buffer);
      free(cmd_buffer);
    }
  }
  else {
    htonl_bytes = htonl(bytes);
    socket_write(conn, fd, &htonl_bytes, sizeof(htonl_bytes));
    socket_write(conn, fd, buffer, curlx_sitouz(bytes));
  }
  free(buffer);
}

static ssize_t sec_write(struct connectdata *conn, curl_socket_t fd,
                         const char *buffer, size_t length)
{
  /* FIXME: Check for overflow */
  ssize_t tx = 0, len = conn->buffer_size;

  len -= conn->mech->overhead(conn->app_data, conn->data_prot,
                              curlx_sztosi(len));
  if(len <= 0)
    len = length;
  while(length) {
    if(len >= 0 || length < (size_t)len) {
      /* FIXME: Check for overflow. */
      len = length;
    }
    do_sec_send(conn, fd, buffer, curlx_sztosi(len));
    length -= len;
    buffer += len;
    tx += len;
  }
  return tx;
}

/* Matches Curl_send signature */
static ssize_t sec_send(struct connectdata *conn, int sockindex,
                        const void *buffer, size_t len, CURLcode *err)
{
  curl_socket_t fd = conn->sock[sockindex];
  *err = CURLE_OK;
  return sec_write(conn, fd, buffer, len);
}

int Curl_sec_read_msg(struct connectdata *conn, char *buffer,
                      enum protection_level level)
{
  /* decoded_len should be size_t or ssize_t but conn->mech->decode returns an
     int */
  int decoded_len;
  char *buf;
  int ret_code;
  size_t decoded_sz = 0;
  CURLcode error;

  DEBUGASSERT(level > PROT_NONE && level < PROT_LAST);

  error = Curl_base64_decode(buffer + 4, (unsigned char **)&buf, &decoded_sz);
  if(error || decoded_sz == 0)
    return -1;

  if(decoded_sz > (size_t)INT_MAX) {
    free(buf);
    return -1;
  }
  decoded_len = curlx_uztosi(decoded_sz);

  decoded_len = conn->mech->decode(conn->app_data, buf, decoded_len,
                                   level, conn);
  if(decoded_len <= 0) {
    free(buf);
    return -1;
  }

  if(conn->data->set.verbose) {
    buf[decoded_len] = '\n';
    Curl_debug(conn->data, CURLINFO_HEADER_IN, buf, decoded_len + 1, conn);
  }

  buf[decoded_len] = '\0';
  DEBUGASSERT(decoded_len > 3);
  if(buf[3] == '-')
    ret_code = 0;
  else {
    /* Check for error? */
    sscanf(buf, "%d", &ret_code);
  }

  if(buf[decoded_len - 1] == '\n')
    buf[decoded_len - 1] = '\0';
  /* FIXME: Is |buffer| length always greater than |decoded_len|? */
  strcpy(buffer, buf);
  free(buf);
  return ret_code;
}

/* FIXME: The error code returned here is never checked. */
static int sec_set_protection_level(struct connectdata *conn)
{
  int code;
  char* pbsz;
  static unsigned int buffer_size = 1 << 20; /* 1048576 */
  enum protection_level level = conn->request_data_prot;

  DEBUGASSERT(level > PROT_NONE && level < PROT_LAST);

  if(!conn->sec_complete) {
    infof(conn->data, "Trying to change the protection level after the"
                      "completion of the data exchange.\n");
    return -1;
  }

  /* Bail out if we try to set up the same level */
  if(conn->data_prot == level)
    return 0;

  if(level) {
    code = ftp_send_command(conn, "PBSZ %u", buffer_size);
    if(code < 0)
      return -1;

    if(code/100 != 2) {
      failf(conn->data, "Failed to set the protection's buffer size.");
      return -1;
    }
    conn->buffer_size = buffer_size;

    pbsz = strstr(conn->data->state.buffer, "PBSZ=");
    if(pbsz) {
      /* FIXME: Checks for errors in sscanf? */
      sscanf(pbsz, "PBSZ=%u", &buffer_size);
      if(buffer_size < conn->buffer_size)
        conn->buffer_size = buffer_size;
    }
  }

  /* Now try to negiociate the protection level. */
  code = ftp_send_command(conn, "PROT %c", level_to_char(level));

  if(code < 0)
    return -1;

  if(code/100 != 2) {
    failf(conn->data, "Failed to set the protection level.");
    return -1;
  }

  conn->data_prot = level;
  if(level == PROT_PRIVATE)
    conn->command_prot = level;

  return 0;
}

int
Curl_sec_request_prot(struct connectdata *conn, const char *level)
{
  enum protection_level l = name_to_level(level);
  if(l == PROT_NONE)
    return -1;
  DEBUGASSERT(l > PROT_NONE && l < PROT_LAST);
  conn->request_data_prot = l;
  return 0;
}

static CURLcode choose_mech(struct connectdata *conn)
{
  int ret;
  struct SessionHandle *data = conn->data;
  const struct Curl_sec_client_mech * const *mech;
  void *tmp_allocation;
  const char *mech_name;

  for(mech = mechs; (*mech); ++mech) {
    mech_name = (*mech)->name;
    /* We have no mechanism with a NULL name but keep this check */
    DEBUGASSERT(mech_name != NULL);
    if(mech_name == NULL) {
      infof(data, "Skipping mechanism with empty name (%p)\n", (void *)mech);
      continue;
    }
    tmp_allocation = realloc(conn->app_data, (*mech)->size);
    if(tmp_allocation == NULL) {
      failf(data, "Failed realloc of size %u", (*mech)->size);
      mech = NULL;
      return CURLE_OUT_OF_MEMORY;
    }
    conn->app_data = tmp_allocation;

    if((*mech)->init) {
      ret = (*mech)->init(conn->app_data);
      if(ret != 0) {
        infof(data, "Failed initialization for %s. Skipping it.\n", mech_name);
        continue;
      }
    }

    infof(data, "Trying mechanism %s...\n", mech_name);
    ret = ftp_send_command(conn, "AUTH %s", mech_name);
    if(ret < 0)
      /* FIXME: This error is too generic but it is OK for now. */
      return CURLE_COULDNT_CONNECT;

    if(ret/100 != 3) {
      switch(ret) {
      case 504:
        infof(data, "Mechanism %s is not supported by the server (server "
                    "returned ftp code: 504).\n", mech_name);
        break;
      case 534:
        infof(data, "Mechanism %s was rejected by the server (server returned "
                    "ftp code: 534).\n", mech_name);
        break;
      default:
        if(ret/100 == 5) {
          infof(data, "server does not support the security extensions\n");
          return CURLE_USE_SSL_FAILED;
        }
        break;
      }
      continue;
    }

    /* Authenticate */
    ret = (*mech)->auth(conn->app_data, conn);

    if(ret == AUTH_CONTINUE)
      continue;
    else if(ret != AUTH_OK) {
      /* Mechanism has dumped the error to stderr, don't error here. */
      return -1;
    }
    DEBUGASSERT(ret == AUTH_OK);

    conn->mech = *mech;
    conn->sec_complete = 1;
    conn->recv[FIRSTSOCKET] = sec_recv;
    conn->send[FIRSTSOCKET] = sec_send;
    conn->recv[SECONDARYSOCKET] = sec_recv;
    conn->send[SECONDARYSOCKET] = sec_send;
    conn->command_prot = PROT_SAFE;
    /* Set the requested protection level */
    /* BLOCKING */
    (void)sec_set_protection_level(conn);
    break;
  }

  return mech != NULL ? CURLE_OK : CURLE_FAILED_INIT;
}

CURLcode
Curl_sec_login(struct connectdata *conn)
{
  return choose_mech(conn);
}


void
Curl_sec_end(struct connectdata *conn)
{
  if(conn->mech != NULL && conn->mech->end)
    conn->mech->end(conn->app_data);
  if(conn->app_data) {
    free(conn->app_data);
    conn->app_data = NULL;
  }
  if(conn->in_buffer.data) {
    free(conn->in_buffer.data);
    conn->in_buffer.data = NULL;
    conn->in_buffer.size = 0;
    conn->in_buffer.index = 0;
    /* FIXME: Is this really needed? */
    conn->in_buffer.eof_flag = 0;
  }
  conn->sec_complete = 0;
  conn->data_prot = PROT_CLEAR;
  conn->mech = NULL;
}

#endif /* HAVE_GSSAPI */

#endif /* CURL_DISABLE_FTP */
