/*
 * LoggerCommon.h
 *
 * version 1.5-RC2 22-NOV-2013
 *
 * Definitions common to NSLogger Viewer and NSLoggerClient
 * for the binary messages format
 * https://github.com/fpillet/NSLogger
 *
 * BSD license follows (http://www.opensource.org/licenses/bsd-license.php)
 * 
 * Copyright (c) 2010-2013 Florent Pillet All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of  source code  must retain  the above  copyright notice,
 * this list of  conditions and the following  disclaimer. Redistributions in
 * binary  form must  reproduce  the  above copyright  notice,  this list  of
 * conditions and the following disclaimer  in the documentation and/or other
 * materials  provided with  the distribution.  Neither the  name of  Florent
 * Pillet nor the names of its contributors may be used to endorse or promote
 * products  derived  from  this  software  without  specific  prior  written
 * permission.  THIS  SOFTWARE  IS  PROVIDED BY  THE  COPYRIGHT  HOLDERS  AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A  PARTICULAR PURPOSE  ARE DISCLAIMED.  IN  NO EVENT  SHALL THE  COPYRIGHT
 * HOLDER OR  CONTRIBUTORS BE  LIABLE FOR  ANY DIRECT,  INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY,  OR CONSEQUENTIAL DAMAGES (INCLUDING,  BUT NOT LIMITED
 * TO, PROCUREMENT  OF SUBSTITUTE GOODS  OR SERVICES;  LOSS OF USE,  DATA, OR
 * PROFITS; OR  BUSINESS INTERRUPTION)  HOWEVER CAUSED AND  ON ANY  THEORY OF
 * LIABILITY,  WHETHER  IN CONTRACT,  STRICT  LIABILITY,  OR TORT  (INCLUDING
 * NEGLIGENCE  OR OTHERWISE)  ARISING  IN ANY  WAY  OUT OF  THE  USE OF  THIS
 * SOFTWARE,   EVEN  IF   ADVISED  OF   THE  POSSIBILITY   OF  SUCH   DAMAGE.
 * 
 */

/* NSLogger native binary message format:
 * Each message is a dictionary encoded in a compact format. All values are stored
 * in network order (big endian). A message is made of several "parts", which are
 * typed chunks of data, each with a specific purpose (partKey), data type (partType)
 * and data size (partSize).
 *
 *	uint32_t	totalSize		(total size for the whole message excluding this 4-byte count)
 *	uint16_t	partCount		(number of parts below)
 *  [repeat partCount times]:
 *		uint8_t		partKey		the part key
 *		uint8_t		partType	(string, binary, image, int16, int32, int64)
 *		uint32_t	partSize	(only for string, binary and image types, others are implicit)
 *		.. `partSize' data bytes
 *
 * Complete message is usually made of:
 *	- a PART_KEY_MESSAGE_TYPE (mandatory) which contains one of the LOGMSG_TYPE_* values
 *  - a PART_KEY_TIMESTAMP_S (mandatory) which is the timestamp returned by gettimeofday() (seconds from 01.01.1970 00:00)
 *	- a PART_KEY_TIMESTAMP_MS (optional) complement of the timestamp seconds, in milliseconds
 *	- a PART_KEY_TIMESTAMP_US (optional) complement of the timestamp seconds and milliseconds, in microseconds
 *	- a PART_KEY_THREAD_ID (mandatory) the ID of the user thread that produced the log entry
 *	- a PART_KEY_TAG (optional) a tag that helps categorizing and filtering logs from your application, and shows up in viewer logs
 *	- a PART_KEY_LEVEL (optional) a log level that helps filtering logs from your application (see as few or as much detail as you need)
 *	- a PART_KEY_MESSAGE which is the message text, binary data or image
 *  - a PART_KEY_MESSAGE_SEQ which is the message sequence number (message# sent by client)
 *	- a PART_KEY_FILENAME (optional) with the filename from which the log was generated
 *	- a PART_KEY_LINENUMBER (optional) the linenumber in the filename at which the log was generated
 *	- a PART_KEY_FUNCTIONNAME (optional) the function / method / selector from which the log was generated
 *  - if logging an image, PART_KEY_IMAGE_WIDTH and PART_KEY_IMAGE_HEIGHT let the desktop know the image size without having to actually decode it
 */

// Constants for the "part key" field
#define	PART_KEY_MESSAGE_TYPE	0
#define	PART_KEY_TIMESTAMP_S	1			// "seconds" component of timestamp
#define PART_KEY_TIMESTAMP_MS	2			// milliseconds component of timestamp (optional, mutually exclusive with PART_KEY_TIMESTAMP_US)
#define PART_KEY_TIMESTAMP_US	3			// microseconds component of timestamp (optional, mutually exclusive with PART_KEY_TIMESTAMP_MS)
#define PART_KEY_THREAD_ID		4
#define	PART_KEY_TAG			5
#define	PART_KEY_LEVEL			6
#define	PART_KEY_MESSAGE		7
#define PART_KEY_IMAGE_WIDTH	8			// messages containing an image should also contain a part with the image size
#define PART_KEY_IMAGE_HEIGHT	9			// (this is mainly for the desktop viewer to compute the cell size without having to immediately decode the image)
#define PART_KEY_MESSAGE_SEQ	10			// the sequential number of this message which indicates the order in which messages are generated
#define PART_KEY_FILENAME		11			// when logging, message can contain a file name
#define PART_KEY_LINENUMBER		12			// as well as a line number
#define PART_KEY_FUNCTIONNAME	13			// and a function or method name

// Constants for parts in LOGMSG_TYPE_CLIENTINFO
#define PART_KEY_CLIENT_NAME	20
#define PART_KEY_CLIENT_VERSION	21
#define PART_KEY_OS_NAME		22
#define PART_KEY_OS_VERSION		23
#define PART_KEY_CLIENT_MODEL	24			// For iPhone, device model (i.e 'iPhone', 'iPad', etc)
#define PART_KEY_UNIQUEID		25			// for remote device identification, part of LOGMSG_TYPE_CLIENTINFO

// Area starting at which you may define your own constants
#define PART_KEY_USER_DEFINED	100

// Constants for the "partType" field
#define	PART_TYPE_STRING		0			// Strings are stored as UTF-8 data
#define PART_TYPE_BINARY		1			// A block of binary data
#define PART_TYPE_INT16			2
#define PART_TYPE_INT32			3
#define	PART_TYPE_INT64			4
#define PART_TYPE_IMAGE			5			// An image, stored in PNG format

// Data values for the PART_KEY_MESSAGE_TYPE parts
#define LOGMSG_TYPE_LOG			0			// A standard log message
#define	LOGMSG_TYPE_BLOCKSTART	1			// The start of a "block" (a group of log entries)
#define	LOGMSG_TYPE_BLOCKEND	2			// The end of the last started "block"
#define LOGMSG_TYPE_CLIENTINFO	3			// Information about the client app
#define LOGMSG_TYPE_DISCONNECT	4			// Pseudo-message on the desktop side to identify client disconnects
#define LOGMSG_TYPE_MARK		5			// Pseudo-message that defines a "mark" that users can place in the log flow

// Default Bonjour service identifiers
#define LOGGER_SERVICE_TYPE_SSL	CFSTR("_nslogger-ssl._tcp")
#define LOGGER_SERVICE_TYPE		CFSTR("_nslogger._tcp")
