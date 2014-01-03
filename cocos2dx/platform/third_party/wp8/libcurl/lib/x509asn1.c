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

#if defined(USE_QSOSSL) || defined(USE_GSKIT) || defined(USE_NSS)

#include <curl/curl.h>
#include "urldata.h"
#include "strequal.h"
#include "hostcheck.h"
#include "sslgen.h"
#include "sendf.h"
#include "inet_pton.h"
#include "curl_base64.h"
#include "x509asn1.h"

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

#include "curl_memory.h"
/* The last #include file should be: */
#include "memdebug.h"


/* ASN.1 OIDs. */
static const char       cnOID[] = "2.5.4.3";    /* Common name. */
static const char       sanOID[] = "2.5.29.17"; /* Subject alternative name. */

static const curl_OID   OIDtable[] = {
  { "1.2.840.10040.4.1",        "dsa" },
  { "1.2.840.10040.4.3",        "dsa-with-sha1" },
  { "1.2.840.10045.2.1",        "ecPublicKey" },
  { "1.2.840.10045.3.0.1",      "c2pnb163v1" },
  { "1.2.840.10045.4.1",        "ecdsa-with-SHA1" },
  { "1.2.840.10046.2.1",        "dhpublicnumber" },
  { "1.2.840.113549.1.1.1",     "rsaEncryption" },
  { "1.2.840.113549.1.1.2",     "md2WithRSAEncryption" },
  { "1.2.840.113549.1.1.4",     "md5WithRSAEncryption" },
  { "1.2.840.113549.1.1.5",     "sha1WithRSAEncryption" },
  { "1.2.840.113549.1.1.10",    "RSASSA-PSS" },
  { "1.2.840.113549.1.1.14",    "sha224WithRSAEncryption" },
  { "1.2.840.113549.1.1.11",    "sha256WithRSAEncryption" },
  { "1.2.840.113549.1.1.12",    "sha384WithRSAEncryption" },
  { "1.2.840.113549.1.1.13",    "sha512WithRSAEncryption" },
  { "1.2.840.113549.2.2",       "md2" },
  { "1.2.840.113549.2.5",       "md5" },
  { "1.3.14.3.2.26",            "sha1" },
  { cnOID,                      "CN" },
  { "2.5.4.4",                  "SN" },
  { "2.5.4.5",                  "serialNumber" },
  { "2.5.4.6",                  "C" },
  { "2.5.4.7",                  "L" },
  { "2.5.4.8",                  "ST" },
  { "2.5.4.9",                  "streetAddress" },
  { "2.5.4.10",                 "O" },
  { "2.5.4.11",                 "OU" },
  { "2.5.4.12",                 "title" },
  { "2.5.4.13",                 "description" },
  { "2.5.4.17",                 "postalCode" },
  { "2.5.4.41",                 "name" },
  { "2.5.4.42",                 "givenName" },
  { "2.5.4.43",                 "initials" },
  { "2.5.4.44",                 "generationQualifier" },
  { "2.5.4.45",                 "X500UniqueIdentifier" },
  { "2.5.4.46",                 "dnQualifier" },
  { "2.5.4.65",                 "pseudonym" },
  { "1.2.840.113549.1.9.1",     "emailAddress" },
  { "2.5.4.72",                 "role" },
  { sanOID,                     "subjectAltName" },
  { "2.5.29.18",                "issuerAltName" },
  { "2.5.29.19",                "basicConstraints" },
  { "2.16.840.1.101.3.4.2.4",   "sha224" },
  { "2.16.840.1.101.3.4.2.1",   "sha256" },
  { "2.16.840.1.101.3.4.2.2",   "sha384" },
  { "2.16.840.1.101.3.4.2.3",   "sha512" },
  { (const char *) NULL,        (const char *) NULL }
};

/*
 * Lightweight ASN.1 parser.
 * In particular, it does not check for syntactic/lexical errors.
 * It is intended to support certificate information gathering for SSL backends
 * that offer a mean to get certificates as a whole, but do not supply
 * entry points to get particular certificate sub-fields.
 * Please note there is no pretention here to rewrite a full SSL library.
 */


const char * Curl_getASN1Element(curl_asn1Element * elem,
                                 const char * beg, const char * end)
{
  unsigned char b;
  unsigned long len;
  curl_asn1Element lelem;

  /* Get a single ASN.1 element into `elem', parse ASN.1 string at `beg'
     ending at `end'.
     Returns a pointer in source string after the parsed element, or NULL
     if an error occurs. */

  if(beg >= end || !*beg)
    return (const char *) NULL;

  /* Process header byte. */
  b = (unsigned char) *beg++;
  elem->constructed = (b & 0x20) != 0;
  elem->class = (b >> 6) & 3;
  b &= 0x1F;
  if(b == 0x1F)
    return (const char *) NULL; /* Long tag values not supported here. */
  elem->tag = b;

  /* Process length. */
  if(beg >= end)
    return (const char *) NULL;
  b = (unsigned char) *beg++;
  if(!(b & 0x80))
    len = b;
  else if(!(b &= 0x7F)) {
    /* Unspecified length. Since we have all the data, we can determine the
       effective length by skipping element until an end element is found. */
    if(!elem->constructed)
      return (const char *) NULL;
    elem->beg = beg;
    while(beg < end && *beg) {
      beg = Curl_getASN1Element(&lelem, beg, end);
      if(!beg)
        return (const char *) NULL;
    }
    if(beg >= end)
      return (const char *) NULL;
    elem->end = beg;
    return beg + 1;
  }
  else if(beg + b > end)
    return (const char *) NULL; /* Does not fit in source. */
  else {
    /* Get long length. */
    len = 0;
    do {
      if(len & 0xFF000000L)
        return (const char *) NULL;  /* Lengths > 32 bits are not supported. */
      len = (len << 8) | (unsigned char) *beg++;
    } while(--b);
  }
  if((unsigned long) (end - beg) < len)
    return (const char *) NULL;  /* Element data does not fit in source. */
  elem->beg = beg;
  elem->end = beg + len;
  return elem->end;
}

static const curl_OID * searchOID(const char * oid)
{
  const curl_OID * op;

  /* Search the null terminated OID or OID identifier in local table.
     Return the table entry pointer or NULL if not found. */

  for(op = OIDtable; op->numoid; op++)
    if(!strcmp(op->numoid, oid) || curl_strequal(op->textoid, oid))
      return op;

  return (const curl_OID *) NULL;
}

static const char * bool2str(const char * beg, const char * end)
{
  /* Convert an ASN.1 Boolean value into its string representation.
     Return the dynamically allocated string, or NULL if source is not an
     ASN.1 Boolean value. */

  if(end - beg != 1)
    return (const char *) NULL;
  return strdup(*beg? "TRUE": "FALSE");
}

static const char * octet2str(const char * beg, const char * end)
{
  size_t n = end - beg;
  char * buf;

  /* Convert an ASN.1 octet string to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  buf = malloc(3 * n + 1);
  if(buf)
    for(n = 0; beg < end; n += 3)
      snprintf(buf + n, 4, "%02x:", *(const unsigned char *) beg++);
  return buf;
}

static const char * bit2str(const char * beg, const char * end)

{
  /* Convert an ASN.1 bit string to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(++beg > end)
    return (const char *) NULL;
  return octet2str(beg, end);
}

static const char * int2str(const char * beg, const char * end)
{
  long val = 0;
  size_t n = end - beg;

  /* Convert an ASN.1 integer value into its string representation.
     Return the dynamically allocated string, or NULL if source is not an
     ASN.1 integer value. */

  if(!n)
    return (const char *) NULL;

  if(n > 4)
    return octet2str(beg, end);

  /* Represent integers <= 32-bit as a single value. */
  if(*beg & 0x80)
    val = ~val;

  do
    val = (val << 8) | *(const unsigned char *) beg++;
  while(beg < end);
  return curl_maprintf("%s%lx", (val < 0 || val >= 10)? "0x": "", val);
}

static ssize_t
utf8asn1str(char * * to, int type, const char * from, const char * end)
{
  size_t inlength = end - from;
  int size = 1;
  size_t outlength;
  int charsize;
  unsigned int wc;
  char * buf;

  /* Perform a lazy conversion from an ASN.1 typed string to UTF8. Allocate the
     destination buffer dynamically. The allocation size will normally be too
     large: this is to avoid buffer overflows.
     Terminate the string with a nul byte and return the converted
     string length. */

  *to = (char *) NULL;
  switch (type) {
  case CURL_ASN1_BMP_STRING:
    size = 2;
    break;
  case CURL_ASN1_UNIVERSAL_STRING:
    size = 4;
    break;
  case CURL_ASN1_NUMERIC_STRING:
  case CURL_ASN1_PRINTABLE_STRING:
  case CURL_ASN1_TELETEX_STRING:
  case CURL_ASN1_IA5_STRING:
  case CURL_ASN1_VISIBLE_STRING:
  case CURL_ASN1_UTF8_STRING:
    break;
  default:
    return -1;  /* Conversion not supported. */
  }

  if(inlength % size)
    return -1;  /* Length inconsistent with character size. */
  buf = malloc(4 * (inlength / size) + 1);
  if(!buf)
    return -1;  /* Not enough memory. */

  if(type == CURL_ASN1_UTF8_STRING) {
    /* Just copy. */
    outlength = inlength;
    if(outlength)
      memcpy(buf, from, outlength);
  }
  else {
    for(outlength = 0; from < end;) {
      wc = 0;
      switch (size) {
      case 4:
        wc = (wc << 8) | *(const unsigned char *) from++;
        wc = (wc << 8) | *(const unsigned char *) from++;
      case 2:
        wc = (wc << 8) | *(const unsigned char *) from++;
      default: /* case 1: */
        wc = (wc << 8) | *(const unsigned char *) from++;
      }
      charsize = 1;
      if(wc >= 0x00000080) {
        if(wc >= 0x00000800) {
          if(wc >= 0x00010000) {
            if(wc >= 0x00200000) {
              free(buf);
              return -1;        /* Invalid char. size for target encoding. */
            }
            buf[outlength + 3] = (char) (0x80 | (wc & 0x3F));
            wc = (wc >> 6) | 0x00010000;
            charsize++;
          }
          buf[outlength + 2] = (char) (0x80 | (wc & 0x3F));
          wc = (wc >> 6) | 0x00000800;
          charsize++;
        }
        buf[outlength + 1] = (char) (0x80 | (wc & 0x3F));
        wc = (wc >> 6) | 0x000000C0;
        charsize++;
      }
      buf[outlength] = (char) wc;
      outlength += charsize;
    }
  }
  buf[outlength] = '\0';
  *to = buf;
  return outlength;
}

static const char * string2str(int type, const char * beg, const char * end)
{
  char * buf;

  /* Convert an ASN.1 String into its UTF-8 string representation.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(utf8asn1str(&buf, type, beg, end) < 0)
    return (const char *) NULL;
  return buf;
}

static int encodeUint(char * buf, int n, unsigned int x)
{
  int i = 0;
  unsigned int y = x / 10;

  /* Decimal ASCII encode unsigned integer `x' in the `n'-byte buffer at `buf'.
     Return the total number of encoded digits, even if larger than `n'. */

  if(y) {
    i += encodeUint(buf, n, y);
    x -= y * 10;
  }
  if(i < n)
    buf[i] = (char) ('0' + x);
  i++;
  if(i < n)
    buf[i] = '\0';      /* Store a terminator if possible. */
  return i;
}

static int encodeOID(char * buf, int n, const char * beg, const char * end)
{
  int i = 0;
  unsigned int x;
  unsigned int y;

  /* Convert an ASN.1 OID into its dotted string representation.
     Store the result in th `n'-byte buffer at `buf'.
     Return the converted string length, or -1 if an error occurs. */

  /* Process the first two numbers. */
  y = *(const unsigned char *) beg++;
  x = y / 40;
  y -= x * 40;
  i += encodeUint(buf + i, n - i, x);
  if(i < n)
    buf[i] = '.';
  i++;
  i += encodeUint(buf + i, n - i, y);

  /* Process the trailing numbers. */
  while(beg < end) {
    if(i < n)
      buf[i] = '.';
    i++;
    x = 0;
    do {
      if(x & 0xFF000000)
        return -1;
      y = *(const unsigned char *) beg++;
      x = (x << 7) | (y & 0x7F);
    } while(y & 0x80);
    i += encodeUint(buf + i, n - i, x);
  }
  if(i < n)
    buf[i] = '\0';
  return i;
}

static const char * OID2str(const char * beg, const char * end, bool symbolic)
{
  char * buf = (char *) NULL;
  const curl_OID * op;
  int n;

  /* Convert an ASN.1 OID into its dotted or symbolic string representation.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(beg < end) {
    n = encodeOID((char *) NULL, -1, beg, end);
    if(n >= 0) {
      buf = malloc(n + 1);
      if(buf) {
        encodeOID(buf, n, beg, end);
        buf[n] = '\0';

        if(symbolic) {
          op = searchOID(buf);
          if(op) {
            free(buf);
            buf = strdup(op->textoid);
          }
        }
      }
    }
  }
  return buf;
}

static const char * GTime2str(const char * beg, const char * end)
{
  const char * tzp;
  const char * fracp;
  char sec1, sec2;
  size_t fracl;
  size_t tzl;
  const char * sep = "";

  /* Convert an ASN.1 Generalized time to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  for(fracp = beg; fracp < end && *fracp >= '0' && *fracp <= '9'; fracp++)
    ;

  /* Get seconds digits. */
  sec1 = '0';
  switch (fracp - beg - 12) {
  case 0:
    sec2 = '0';
    break;
  case 2:
    sec1 = fracp[-2];
  case 1:
    sec2 = fracp[-1];
    break;
  default:
    return (const char *) NULL;
  }

  /* Scan for timezone, measure fractional seconds. */
  tzp = fracp;
  fracl = 0;
  if(fracp < end && (*fracp == '.' || *fracp == ',')) {
    fracp++;
    do
      tzp++;
    while(tzp < end && *tzp >= '0' && *tzp <= '9');
    /* Strip leading zeroes in fractional seconds. */
    for(fracl = tzp - fracp - 1; fracl && fracp[fracl - 1] == '0'; fracl--)
      ;
  }

  /* Process timezone. */
  if(tzp >= end)
    ;           /* Nothing to do. */
  else if(*tzp == 'Z') {
    tzp = " GMT";
    end = tzp + 4;
  }
  else {
    sep = " ";
    tzp++;
  }

  tzl = end - tzp;
  return curl_maprintf("%.4s-%.2s-%.2s %.2s:%.2s:%c%c%s%.*s%s%.*s",
                       beg, beg + 4, beg + 6,
                       beg + 8, beg + 10, sec1, sec2,
                       fracl? ".": "", fracl, fracp,
                       sep, tzl, tzp);
}

static const char * UTime2str(const char * beg, const char * end)
{
  const char * tzp;
  size_t tzl;
  const char * sec;

  /* Convert an ASN.1 UTC time to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  for(tzp = beg; tzp < end && *tzp >= '0' && *tzp <= '9'; tzp++)
    ;
  /* Get the seconds. */
  sec = beg + 10;
  switch (tzp - sec) {
  case 0:
    sec = "00";
  case 2:
    break;
  default:
    return (const char *) NULL;
  }

  /* Process timezone. */
  if(tzp >= end)
    return (const char *) NULL;
  if(*tzp == 'Z') {
    tzp = "GMT";
    end = tzp + 3;
  }
  else
    tzp++;

  tzl = end - tzp;
  return curl_maprintf("%u%.2s-%.2s-%.2s %.2s:%.2s:%.2s %.*s",
                       20 - (*beg >= '5'), beg, beg + 2, beg + 4,
                       beg + 6, beg + 8, sec,
                       tzl, tzp);
}

const char * Curl_ASN1tostr(curl_asn1Element * elem, int type)
{
  static const char zero = '\0';

  /* Convert an ASN.1 element to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(elem->constructed)
    return (const char *) NULL; /* No conversion of structured elements. */

  if(!type)
    type = elem->tag;   /* Type not forced: use element tag as type. */

  switch (type) {
  case CURL_ASN1_BOOLEAN:
    return bool2str(elem->beg, elem->end);
  case CURL_ASN1_INTEGER:
  case CURL_ASN1_ENUMERATED:
    return int2str(elem->beg, elem->end);
  case CURL_ASN1_BIT_STRING:
    return bit2str(elem->beg, elem->end);
  case CURL_ASN1_OCTET_STRING:
    return octet2str(elem->beg, elem->end);
  case CURL_ASN1_NULL:
    return strdup(&zero);
  case CURL_ASN1_OBJECT_IDENTIFIER:
    return OID2str(elem->beg, elem->end, TRUE);
  case CURL_ASN1_UTC_TIME:
    return UTime2str(elem->beg, elem->end);
  case CURL_ASN1_GENERALIZED_TIME:
    return GTime2str(elem->beg, elem->end);
  case CURL_ASN1_UTF8_STRING:
  case CURL_ASN1_NUMERIC_STRING:
  case CURL_ASN1_PRINTABLE_STRING:
  case CURL_ASN1_TELETEX_STRING:
  case CURL_ASN1_IA5_STRING:
  case CURL_ASN1_VISIBLE_STRING:
  case CURL_ASN1_UNIVERSAL_STRING:
  case CURL_ASN1_BMP_STRING:
    return string2str(type, elem->beg, elem->end);
  }

  return (const char *) NULL;   /* Unsupported. */
}

static ssize_t encodeDN(char * buf, size_t n, curl_asn1Element * dn)
{
  curl_asn1Element rdn;
  curl_asn1Element atv;
  curl_asn1Element oid;
  curl_asn1Element value;
  size_t l = 0;
  const char * p1;
  const char * p2;
  const char * p3;
  const char * str;

  /* ASCII encode distinguished name at `dn' into the `n'-byte buffer at `buf'.
     Return the total string length, even if larger than `n'. */

  for(p1 = dn->beg; p1 < dn->end;) {
    p1 = Curl_getASN1Element(&rdn, p1, dn->end);
    for(p2 = rdn.beg; p2 < rdn.end;) {
      p2 = Curl_getASN1Element(&atv, p2, rdn.end);
      p3 = Curl_getASN1Element(&oid, atv.beg, atv.end);
      Curl_getASN1Element(&value, p3, atv.end);
      str = Curl_ASN1tostr(&oid, 0);
      if(!str)
        return -1;

      /* Encode delimiter.
         If attribute has a short uppercase name, delimiter is ", ". */
      if(l) {
        for(p3 = str; isupper(*p3); p3++)
          ;
        for(p3 = (*p3 || p3 - str > 2)? "/": ", "; *p3; p3++) {
          if(l < n)
            buf[l] = *p3;
          l++;
        }
      }

      /* Encode attribute name. */
      for(p3 = str; *p3; p3++) {
        if(l < n)
          buf[l] = *p3;
        l++;
      }
      free((char *) str);

      /* Generate equal sign. */
      if(l < n)
        buf[l] = '=';
      l++;

      /* Generate value. */
      str = Curl_ASN1tostr(&value, 0);
      if(!str)
        return -1;
      for(p3 = str; *p3; p3++) {
        if(l < n)
          buf[l] = *p3;
        l++;
      }
      free((char *) str);
    }
  }

  return l;
}

const char * Curl_DNtostr(curl_asn1Element * dn)
{
  char * buf = (char *) NULL;
  ssize_t n = encodeDN(buf, 0, dn);

  /* Convert an ASN.1 distinguished name into a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(n >= 0) {
    buf = malloc(n + 1);
    if(buf) {
      encodeDN(buf, n + 1, dn);
      buf[n] = '\0';
    }
  }
  return (const char *) buf;
}

static const char * checkOID(const char * beg, const char * end,
                             const char * oid)
{
  curl_asn1Element e;
  const char * ccp;
  const char * p;
  bool matched;

  /* Check if first ASN.1 element at `beg' is the given OID.
     Return a pointer in the source after the OID if found, else NULL. */

  ccp = Curl_getASN1Element(&e, beg, end);
  if(!ccp || e.tag != CURL_ASN1_OBJECT_IDENTIFIER)
    return (const char *) NULL;

  p = OID2str(e.beg, e.end, FALSE);
  if(!p)
    return (const char *) NULL;

  matched = !strcmp(p, oid);
  free((char *) p);
  return matched? ccp: (const char *) NULL;
}


/*
 * X509 parser.
 */

void Curl_parseX509(curl_X509certificate * cert,
                    const char * beg, const char * end)
{
  curl_asn1Element elem;
  curl_asn1Element tbsCertificate;
  const char * ccp;
  static const char defaultVersion = 0;  /* v1. */

  /* ASN.1 parse an X509 certificate into structure subfields.
     Syntax is assumed to have already been checked by the SSL backend.
     See RFC 5280. */

  cert->certificate.beg = beg;
  cert->certificate.end = end;

  /* Get the sequence content. */
  Curl_getASN1Element(&elem, beg, end);
  beg = elem.beg;
  end = elem.end;

  /* Get tbsCertificate. */
  beg = Curl_getASN1Element(&tbsCertificate, beg, end);
  /* Skip the signatureAlgorithm. */
  beg = Curl_getASN1Element(&cert->signatureAlgorithm, beg, end);
  /* Get the signatureValue. */
  Curl_getASN1Element(&cert->signature, beg, end);

  /* Parse TBSCertificate. */
  beg = tbsCertificate.beg;
  end = tbsCertificate.end;
  /* Get optional version, get serialNumber. */
  cert->version.beg = &defaultVersion;
  cert->version.end = &defaultVersion + sizeof defaultVersion;;
  beg = Curl_getASN1Element(&elem, beg, end);
  if(elem.tag == 0) {
    Curl_getASN1Element(&cert->version, elem.beg, elem.end);
    beg = Curl_getASN1Element(&elem, beg, end);
  }
  cert->serialNumber = elem;
  /* Get signature algorithm. */
  beg = Curl_getASN1Element(&cert->signatureAlgorithm, beg, end);
  /* Get issuer. */
  beg = Curl_getASN1Element(&cert->issuer, beg, end);
  /* Get notBefore and notAfter. */
  beg = Curl_getASN1Element(&elem, beg, end);
  ccp = Curl_getASN1Element(&cert->notBefore, elem.beg, elem.end);
  Curl_getASN1Element(&cert->notAfter, ccp, elem.end);
  /* Get subject. */
  beg = Curl_getASN1Element(&cert->subject, beg, end);
  /* Get subjectPublicKeyAlgorithm and subjectPublicKey. */
  beg = Curl_getASN1Element(&elem, beg, end);
  ccp = Curl_getASN1Element(&cert->subjectPublicKeyAlgorithm,
                            elem.beg, elem.end);
  Curl_getASN1Element(&cert->subjectPublicKey, ccp, elem.end);
  /* Get optional issuerUiqueID, subjectUniqueID and extensions. */
  cert->issuerUniqueID.tag = cert->subjectUniqueID.tag = 0;
  cert->extensions.tag = elem.tag = 0;
  cert->issuerUniqueID.beg = cert->issuerUniqueID.end = "";
  cert->subjectUniqueID.beg = cert->subjectUniqueID.end = "";
  cert->extensions.beg = cert->extensions.end = "";
  if(beg < end)
    beg = Curl_getASN1Element(&elem, beg, end);
  if(elem.tag == 1) {
    cert->issuerUniqueID = elem;
    if(beg < end)
      beg = Curl_getASN1Element(&elem, beg, end);
  }
  if(elem.tag == 2) {
    cert->subjectUniqueID = elem;
    if(beg < end)
      beg = Curl_getASN1Element(&elem, beg, end);
  }
  if(elem.tag == 3)
    Curl_getASN1Element(&cert->extensions, elem.beg, elem.end);
}

static size_t copySubstring(char * to, const char * from)
{
  size_t i;

  /* Copy at most 64-characters, terminate with a newline and returns the
     effective number of stored characters. */

  for(i = 0; i < 64; i++) {
    to[i] = *from;
    if(!*from++)
      break;
  }

  to[i++] = '\n';
  return i;
}

static const char * dumpAlgo(curl_asn1Element * param,
                             const char * beg, const char * end)
{
  curl_asn1Element oid;

  /* Get algorithm parameters and return algorithm name. */

  beg = Curl_getASN1Element(&oid, beg, end);
  param->tag = 0;
  param->beg = param->end = end;
  if(beg < end)
    Curl_getASN1Element(param, beg, end);
  return OID2str(oid.beg, oid.end, TRUE);
}

static void do_pubkey_field(struct SessionHandle * data, int certnum,
                            const char * label, curl_asn1Element * elem)
{
  const char * output;

  /* Generate a certificate information record for the public key. */

  output = Curl_ASN1tostr(elem, 0);
  if(output) {
    if(data->set.ssl.certinfo)
      Curl_ssl_push_certinfo(data, certnum, label, output);
    if(!certnum)
      infof(data, "   %s: %s\n", label, output);
    free((char *) output);
  }
}

static void do_pubkey(struct SessionHandle * data, int certnum,
                      const char * algo, curl_asn1Element * param,
                      curl_asn1Element * pubkey)
{
  curl_asn1Element elem;
  curl_asn1Element pk;
  const char * p;
  const char * q;
  unsigned long len;
  unsigned int i;

  /* Generate all information records for the public key. */

  /* Get the public key (single element). */
  Curl_getASN1Element(&pk, pubkey->beg + 1, pubkey->end);

  if(curl_strequal(algo, "rsaEncryption")) {
    p = Curl_getASN1Element(&elem, pk.beg, pk.end);
    /* Compute key length. */
    for(q = elem.beg; !*q && q < elem.end; q++)
      ;
    len = (elem.end - q) * 8;
    if(len)
      for(i = *(unsigned char *) q; !(i & 0x80); i <<= 1)
        len--;
    if(len > 32)
      elem.beg = q;     /* Strip leading zero bytes. */
    if(!certnum)
      infof(data, "   RSA Public Key (%lu bits)\n", len);
    if(data->set.ssl.certinfo) {
      q = curl_maprintf("%lu", len);
      if(q) {
        Curl_ssl_push_certinfo(data, certnum, "RSA Public Key", q);
        free((char *) q);
      }
    }
    /* Generate coefficients. */
    do_pubkey_field(data, certnum, "rsa(n)", &elem);
    Curl_getASN1Element(&elem, p, pk.end);
    do_pubkey_field(data, certnum, "rsa(e)", &elem);
  }
  else if(curl_strequal(algo, "dsa")) {
    p = Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dsa(p)", &elem);
    p = Curl_getASN1Element(&elem, p, param->end);
    do_pubkey_field(data, certnum, "dsa(q)", &elem);
    Curl_getASN1Element(&elem, p, param->end);
    do_pubkey_field(data, certnum, "dsa(g)", &elem);
    do_pubkey_field(data, certnum, "dsa(pub_key)", &pk);
  }
  else if(curl_strequal(algo, "dhpublicnumber")) {
    p = Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dh(p)", &elem);
    Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dh(g)", &elem);
    do_pubkey_field(data, certnum, "dh(pub_key)", &pk);
  }
#if 0 /* Patent-encumbered. */
  else if(curl_strequal(algo, "ecPublicKey")) {
    /* Left TODO. */
  }
#endif
}

CURLcode Curl_extract_certinfo(struct connectdata * conn,
                               int certnum,
                               const char * beg,
                               const char * end)
{
  curl_X509certificate cert;
  struct SessionHandle * data = conn->data;
  curl_asn1Element param;
  const char * ccp;
  char * cp1;
  size_t cl1;
  char * cp2;
  CURLcode cc;
  unsigned long version;
  size_t i;
  size_t j;

  if(!data->set.ssl.certinfo)
    if(certnum)
      return CURLE_OK;

  /* Prepare the certificate information for curl_easy_getinfo(). */

  /* Extract the certificate ASN.1 elements. */
  Curl_parseX509(&cert, beg, end);

  /* Subject. */
  ccp = Curl_DNtostr(&cert.subject);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Subject", ccp);
  if(!certnum)
    infof(data, "%2d Subject: %s\n", certnum, ccp);
  free((char *) ccp);

  /* Issuer. */
  ccp = Curl_DNtostr(&cert.issuer);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Issuer", ccp);
  if(!certnum)
    infof(data, "   Issuer: %s\n", ccp);
  free((char *) ccp);

  /* Version (always fits in less than 32 bits). */
  version = 0;
  for(ccp = cert.version.beg; ccp < cert.version.end; ccp++)
    version = (version << 8) | *(const unsigned char *) ccp;
  if(data->set.ssl.certinfo) {
    ccp = curl_maprintf("%lx", version);
    if(!ccp)
      return CURLE_OUT_OF_MEMORY;
    Curl_ssl_push_certinfo(data, certnum, "Version", ccp);
    free((char *) ccp);
  }
  if(!certnum)
    infof(data, "   Version: %lu (0x%lx)\n", version + 1, version);

  /* Serial number. */
  ccp = Curl_ASN1tostr(&cert.serialNumber, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Serial Number", ccp);
  if(!certnum)
    infof(data, "   Serial Number: %s\n", ccp);
  free((char *) ccp);

  /* Signature algorithm .*/
  ccp = dumpAlgo(&param, cert.signatureAlgorithm.beg,
                 cert.signatureAlgorithm.end);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Signature Algorithm", ccp);
  if(!certnum)
    infof(data, "   Signature Algorithm: %s\n", ccp);
  free((char *) ccp);

  /* Start Date. */
  ccp = Curl_ASN1tostr(&cert.notBefore, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Start Date", ccp);
  if(!certnum)
    infof(data, "   Start Date: %s\n", ccp);
  free((char *) ccp);

  /* Expire Date. */
  ccp = Curl_ASN1tostr(&cert.notAfter, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Expire Date", ccp);
  if(!certnum)
    infof(data, "   Expire Date: %s\n", ccp);
  free((char *) ccp);

  /* Public Key Algorithm. */
  ccp = dumpAlgo(&param, cert.subjectPublicKeyAlgorithm.beg,
                 cert.subjectPublicKeyAlgorithm.end);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Public Key Algorithm", ccp);
  if(!certnum)
    infof(data, "   Public Key Algorithm: %s\n", ccp);
  do_pubkey(data, certnum, ccp, &param, &cert.subjectPublicKey);
  free((char *) ccp);

/* TODO: extensions. */

  /* Signature. */
  ccp = Curl_ASN1tostr(&cert.signature, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Signature", ccp);
  if(!certnum)
    infof(data, "   Signature: %s\n", ccp);
  free((char *) ccp);

  /* Generate PEM certificate. */
  cc = Curl_base64_encode(data, cert.certificate.beg,
                          cert.certificate.end - cert.certificate.beg,
                          &cp1, &cl1);
  if(cc != CURLE_OK)
    return cc;
  /* Compute the number of characters in final certificate string. Format is:
     -----BEGIN CERTIFICATE-----\n
     <max 64 base64 characters>\n
     .
     .
     .
     -----END CERTIFICATE-----\n
   */
  i = 28 + cl1 + (cl1 + 64 - 1) / 64 + 26;
  cp2 = malloc(i + 1);
  if(!cp2) {
    free(cp1);
    return CURLE_OUT_OF_MEMORY;
  }
  /* Build the certificate string. */
  i = copySubstring(cp2, "-----BEGIN CERTIFICATE-----");
  for(j = 0; j < cl1; j += 64)
    i += copySubstring(cp2 + i, cp1 + j);
  i += copySubstring(cp2 + i, "-----END CERTIFICATE-----");
  cp2[i] = '\0';
  free(cp1);
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Cert", cp2);
  if(!certnum)
    infof(data, "%s\n", cp2);
  free(cp2);
  return CURLE_OK;
}


CURLcode Curl_verifyhost(struct connectdata * conn,
                         const char * beg, const char * end)
{
  struct SessionHandle * data = conn->data;
  curl_X509certificate cert;
  curl_asn1Element dn;
  curl_asn1Element elem;
  curl_asn1Element ext;
  curl_asn1Element name;
  int i;
  const char * p;
  const char * q;
  char * dnsname;
  int matched = -1;
  size_t addrlen = (size_t) -1;
  ssize_t len;
#ifdef ENABLE_IPV6
  struct in6_addr addr;
#else
  struct in_addr addr;
#endif

  /* Verify that connection server matches info in X509 certificate at
     `beg'..`end'. */

  if(!data->set.ssl.verifyhost)
    return CURLE_OK;

  if(!beg)
    return CURLE_PEER_FAILED_VERIFICATION;
  Curl_parseX509(&cert, beg, end);

  /* Get the server IP address. */
#ifdef ENABLE_IPV6
  if(conn->bits.ipv6_ip && Curl_inet_pton(AF_INET6, conn->host.name, &addr))
    addrlen = sizeof(struct in6_addr);
  else
#endif
  if(Curl_inet_pton(AF_INET, conn->host.name, &addr))
    addrlen = sizeof(struct in_addr);

  /* Process extensions. */
  for(p = cert.extensions.beg; p < cert.extensions.end && matched != 1;) {
    p = Curl_getASN1Element(&ext, p, cert.extensions.end);
    /* Check if extension is a subjectAlternativeName. */
    ext.beg = checkOID(ext.beg, ext.end, sanOID);
    if(ext.beg) {
      ext.beg = Curl_getASN1Element(&elem, ext.beg, ext.end);
      /* Skip critical if present. */
      if(elem.tag == CURL_ASN1_BOOLEAN)
        ext.beg = Curl_getASN1Element(&elem, ext.beg, ext.end);
      /* Parse the octet string contents: is a single sequence. */
      Curl_getASN1Element(&elem, elem.beg, elem.end);
      /* Check all GeneralNames. */
      for(q = elem.beg; matched != 1 && q < elem.end;) {
        q = Curl_getASN1Element(&name, q, elem.end);
        switch (name.tag) {
        case 2: /* DNS name. */
          i = 0;
          len = utf8asn1str(&dnsname, CURL_ASN1_IA5_STRING,
                            name.beg, name.end);
          if(len > 0)
            if(strlen(dnsname) == (size_t) len)
              i = Curl_cert_hostcheck((const char *) dnsname, conn->host.name);
          if(dnsname)
            free(dnsname);
          if(!i)
            return CURLE_PEER_FAILED_VERIFICATION;
          matched = i;
          break;

        case 7: /* IP address. */
          matched = (size_t) (name.end - q) == addrlen &&
                    !memcmp(&addr, q, addrlen);
          break;
        }
      }
    }
  }

  switch (matched) {
  case 1:
    /* an alternative name matched the server hostname */
    infof(data, "\t subjectAltName: %s matched\n", conn->host.dispname);
    return CURLE_OK;
  case 0:
    /* an alternative name field existed, but didn't match and then
       we MUST fail */
    infof(data, "\t subjectAltName does not match %s\n", conn->host.dispname);
    return CURLE_PEER_FAILED_VERIFICATION;
  }

  /* Process subject. */
  name.beg = name.end = "";
  q = cert.subject.beg;
  /* we have to look to the last occurrence of a commonName in the
     distinguished one to get the most significant one. */
  while(q < cert.subject.end) {
    q = Curl_getASN1Element(&dn, q, cert.subject.end);
    for(p = dn.beg; p < dn.end;) {
      p = Curl_getASN1Element(&elem, p, dn.end);
      /* We have a DN's AttributeTypeAndValue: check it in case it's a CN. */
      elem.beg = checkOID(elem.beg, elem.end, cnOID);
      if(elem.beg)
        name = elem;    /* Latch CN. */
    }
  }

  /* Check the CN if found. */
  if(!Curl_getASN1Element(&elem, name.beg, name.end))
    failf(data, "SSL: unable to obtain common name from peer certificate");
  else {
    len = utf8asn1str(&dnsname, elem.tag, elem.beg, elem.end);
    if(len < 0) {
      free(dnsname);
      return CURLE_OUT_OF_MEMORY;
    }
    if(strlen(dnsname) != (size_t) len)         /* Nul byte in string ? */
      failf(data, "SSL: illegal cert name field");
    else if(Curl_cert_hostcheck((const char *) dnsname, conn->host.name)) {
      infof(data, "\t common name: %s (matched)\n", dnsname);
      free(dnsname);
      return CURLE_OK;
    }
    else
      failf(data, "SSL: certificate subject name '%s' does not match "
            "target host name '%s'", dnsname, conn->host.dispname);
    free(dnsname);
  }

  return CURLE_PEER_FAILED_VERIFICATION;
}

#endif /* USE_QSOSSL or USE_GSKIT or USE_NSS */
