/*
 * libwebsockets - small server side websockets and web server implementation
 *
 * Copyright (C) 2010-2013 Andy Green <andy@warmcat.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation:
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include "private-libwebsockets.h"

#ifdef WIN32
#include <io.h>
#endif


static unsigned char lextable[] = {
	/* pos 0: state 0 */
	0x47 /* 'G' */, 0x07 /* to pos 14 state 1 */,
	0x48 /* 'H' */, 0x0A /* to pos 22 state 5 */,
	0x43 /* 'C' */, 0x0F /* to pos 34 state 10 */,
	0x53 /* 'S' */, 0x19 /* to pos 56 state 21 */,
	0x55 /* 'U' */, 0x3F /* to pos 134 state 51 */,
	0x4F /* 'O' */, 0x46 /* to pos 150 state 59 */,
	0x8D /* '.' */, 0x52 /* to pos 176 state 72 */,
	/* pos 14: state 1 */
	0xC5 /* 'E' */, 0x01 /* to pos 16 state 2 */,
	/* pos 16: state 2 */
	0xD4 /* 'T' */, 0x01 /* to pos 18 state 3 */,
	/* pos 18: state 3 */
	0xA0 /* ' ' */, 0x01 /* to pos 20 state 4 */,
	/* pos 20: state 4 */
	0x80, 0x00 /* terminal marker */,
	/* pos 22: state 5 */
	0x6F /* 'o' */, 0x02 /* to pos 26 state 6 */,
	0xD4 /* 'T' */, 0x76 /* to pos 260 state 114 */,
	/* pos 26: state 6 */
	0xF3 /* 's' */, 0x01 /* to pos 28 state 7 */,
	/* pos 28: state 7 */
	0xF4 /* 't' */, 0x01 /* to pos 30 state 8 */,
	/* pos 30: state 8 */
	0xBA /* ':' */, 0x01 /* to pos 32 state 9 */,
	/* pos 32: state 9 */
	0x81, 0x00 /* terminal marker */,
	/* pos 34: state 10 */
	0xEF /* 'o' */, 0x01 /* to pos 36 state 11 */,
	/* pos 36: state 11 */
	0xEE /* 'n' */, 0x01 /* to pos 38 state 12 */,
	/* pos 38: state 12 */
	0xEE /* 'n' */, 0x01 /* to pos 40 state 13 */,
	/* pos 40: state 13 */
	0xE5 /* 'e' */, 0x01 /* to pos 42 state 14 */,
	/* pos 42: state 14 */
	0xE3 /* 'c' */, 0x01 /* to pos 44 state 15 */,
	/* pos 44: state 15 */
	0xF4 /* 't' */, 0x01 /* to pos 46 state 16 */,
	/* pos 46: state 16 */
	0xE9 /* 'i' */, 0x01 /* to pos 48 state 17 */,
	/* pos 48: state 17 */
	0xEF /* 'o' */, 0x01 /* to pos 50 state 18 */,
	/* pos 50: state 18 */
	0xEE /* 'n' */, 0x01 /* to pos 52 state 19 */,
	/* pos 52: state 19 */
	0xBA /* ':' */, 0x01 /* to pos 54 state 20 */,
	/* pos 54: state 20 */
	0x82, 0x00 /* terminal marker */,
	/* pos 56: state 21 */
	0xE5 /* 'e' */, 0x01 /* to pos 58 state 22 */,
	/* pos 58: state 22 */
	0xE3 /* 'c' */, 0x01 /* to pos 60 state 23 */,
	/* pos 60: state 23 */
	0xAD /* '-' */, 0x01 /* to pos 62 state 24 */,
	/* pos 62: state 24 */
	0xD7 /* 'W' */, 0x01 /* to pos 64 state 25 */,
	/* pos 64: state 25 */
	0xE5 /* 'e' */, 0x01 /* to pos 66 state 26 */,
	/* pos 66: state 26 */
	0xE2 /* 'b' */, 0x01 /* to pos 68 state 27 */,
	/* pos 68: state 27 */
	0xD3 /* 'S' */, 0x01 /* to pos 70 state 28 */,
	/* pos 70: state 28 */
	0xEF /* 'o' */, 0x01 /* to pos 72 state 29 */,
	/* pos 72: state 29 */
	0xE3 /* 'c' */, 0x01 /* to pos 74 state 30 */,
	/* pos 74: state 30 */
	0xEB /* 'k' */, 0x01 /* to pos 76 state 31 */,
	/* pos 76: state 31 */
	0xE5 /* 'e' */, 0x01 /* to pos 78 state 32 */,
	/* pos 78: state 32 */
	0xF4 /* 't' */, 0x01 /* to pos 80 state 33 */,
	/* pos 80: state 33 */
	0xAD /* '-' */, 0x01 /* to pos 82 state 34 */,
	/* pos 82: state 34 */
	0x4B /* 'K' */, 0x08 /* to pos 98 state 35 */,
	0x50 /* 'P' */, 0x10 /* to pos 116 state 42 */,
	0x44 /* 'D' */, 0x27 /* to pos 164 state 66 */,
	0x56 /* 'V' */, 0x2F /* to pos 182 state 75 */,
	0x4F /* 'O' */, 0x36 /* to pos 198 state 83 */,
	0x45 /* 'E' */, 0x3C /* to pos 212 state 90 */,
	0x41 /* 'A' */, 0x46 /* to pos 234 state 101 */,
	0xCE /* 'N' */, 0x4C /* to pos 248 state 108 */,
	/* pos 98: state 35 */
	0xE5 /* 'e' */, 0x01 /* to pos 100 state 36 */,
	/* pos 100: state 36 */
	0xF9 /* 'y' */, 0x01 /* to pos 102 state 37 */,
	/* pos 102: state 37 */
	0x31 /* '1' */, 0x03 /* to pos 108 state 38 */,
	0x32 /* '2' */, 0x04 /* to pos 112 state 40 */,
	0xBA /* ':' */, 0x25 /* to pos 180 state 74 */,
	/* pos 108: state 38 */
	0xBA /* ':' */, 0x01 /* to pos 110 state 39 */,
	/* pos 110: state 39 */
	0x83, 0x00 /* terminal marker */,
	/* pos 112: state 40 */
	0xBA /* ':' */, 0x01 /* to pos 114 state 41 */,
	/* pos 114: state 41 */
	0x84, 0x00 /* terminal marker */,
	/* pos 116: state 42 */
	0xF2 /* 'r' */, 0x01 /* to pos 118 state 43 */,
	/* pos 118: state 43 */
	0xEF /* 'o' */, 0x01 /* to pos 120 state 44 */,
	/* pos 120: state 44 */
	0xF4 /* 't' */, 0x01 /* to pos 122 state 45 */,
	/* pos 122: state 45 */
	0xEF /* 'o' */, 0x01 /* to pos 124 state 46 */,
	/* pos 124: state 46 */
	0xE3 /* 'c' */, 0x01 /* to pos 126 state 47 */,
	/* pos 126: state 47 */
	0xEF /* 'o' */, 0x01 /* to pos 128 state 48 */,
	/* pos 128: state 48 */
	0xEC /* 'l' */, 0x01 /* to pos 130 state 49 */,
	/* pos 130: state 49 */
	0xBA /* ':' */, 0x01 /* to pos 132 state 50 */,
	/* pos 132: state 50 */
	0x85, 0x00 /* terminal marker */,
	/* pos 134: state 51 */
	0xF0 /* 'p' */, 0x01 /* to pos 136 state 52 */,
	/* pos 136: state 52 */
	0xE7 /* 'g' */, 0x01 /* to pos 138 state 53 */,
	/* pos 138: state 53 */
	0xF2 /* 'r' */, 0x01 /* to pos 140 state 54 */,
	/* pos 140: state 54 */
	0xE1 /* 'a' */, 0x01 /* to pos 142 state 55 */,
	/* pos 142: state 55 */
	0xE4 /* 'd' */, 0x01 /* to pos 144 state 56 */,
	/* pos 144: state 56 */
	0xE5 /* 'e' */, 0x01 /* to pos 146 state 57 */,
	/* pos 146: state 57 */
	0xBA /* ':' */, 0x01 /* to pos 148 state 58 */,
	/* pos 148: state 58 */
	0x86, 0x00 /* terminal marker */,
	/* pos 150: state 59 */
	0xF2 /* 'r' */, 0x01 /* to pos 152 state 60 */,
	/* pos 152: state 60 */
	0xE9 /* 'i' */, 0x01 /* to pos 154 state 61 */,
	/* pos 154: state 61 */
	0xE7 /* 'g' */, 0x01 /* to pos 156 state 62 */,
	/* pos 156: state 62 */
	0xE9 /* 'i' */, 0x01 /* to pos 158 state 63 */,
	/* pos 158: state 63 */
	0xEE /* 'n' */, 0x01 /* to pos 160 state 64 */,
	/* pos 160: state 64 */
	0xBA /* ':' */, 0x01 /* to pos 162 state 65 */,
	/* pos 162: state 65 */
	0x87, 0x00 /* terminal marker */,
	/* pos 164: state 66 */
	0xF2 /* 'r' */, 0x01 /* to pos 166 state 67 */,
	/* pos 166: state 67 */
	0xE1 /* 'a' */, 0x01 /* to pos 168 state 68 */,
	/* pos 168: state 68 */
	0xE6 /* 'f' */, 0x01 /* to pos 170 state 69 */,
	/* pos 170: state 69 */
	0xF4 /* 't' */, 0x01 /* to pos 172 state 70 */,
	/* pos 172: state 70 */
	0xBA /* ':' */, 0x01 /* to pos 174 state 71 */,
	/* pos 174: state 71 */
	0x88, 0x00 /* terminal marker */,
	/* pos 176: state 72 */
	0x8A /* '.' */, 0x01 /* to pos 178 state 73 */,
	/* pos 178: state 73 */
	0x89, 0x00 /* terminal marker */,
	/* pos 180: state 74 */
	0x8A, 0x00 /* terminal marker */,
	/* pos 182: state 75 */
	0xE5 /* 'e' */, 0x01 /* to pos 184 state 76 */,
	/* pos 184: state 76 */
	0xF2 /* 'r' */, 0x01 /* to pos 186 state 77 */,
	/* pos 186: state 77 */
	0xF3 /* 's' */, 0x01 /* to pos 188 state 78 */,
	/* pos 188: state 78 */
	0xE9 /* 'i' */, 0x01 /* to pos 190 state 79 */,
	/* pos 190: state 79 */
	0xEF /* 'o' */, 0x01 /* to pos 192 state 80 */,
	/* pos 192: state 80 */
	0xEE /* 'n' */, 0x01 /* to pos 194 state 81 */,
	/* pos 194: state 81 */
	0xBA /* ':' */, 0x01 /* to pos 196 state 82 */,
	/* pos 196: state 82 */
	0x8B, 0x00 /* terminal marker */,
	/* pos 198: state 83 */
	0xF2 /* 'r' */, 0x01 /* to pos 200 state 84 */,
	/* pos 200: state 84 */
	0xE9 /* 'i' */, 0x01 /* to pos 202 state 85 */,
	/* pos 202: state 85 */
	0xE7 /* 'g' */, 0x01 /* to pos 204 state 86 */,
	/* pos 204: state 86 */
	0xE9 /* 'i' */, 0x01 /* to pos 206 state 87 */,
	/* pos 206: state 87 */
	0xEE /* 'n' */, 0x01 /* to pos 208 state 88 */,
	/* pos 208: state 88 */
	0xBA /* ':' */, 0x01 /* to pos 210 state 89 */,
	/* pos 210: state 89 */
	0x8C, 0x00 /* terminal marker */,
	/* pos 212: state 90 */
	0xF8 /* 'x' */, 0x01 /* to pos 214 state 91 */,
	/* pos 214: state 91 */
	0xF4 /* 't' */, 0x01 /* to pos 216 state 92 */,
	/* pos 216: state 92 */
	0xE5 /* 'e' */, 0x01 /* to pos 218 state 93 */,
	/* pos 218: state 93 */
	0xEE /* 'n' */, 0x01 /* to pos 220 state 94 */,
	/* pos 220: state 94 */
	0xF3 /* 's' */, 0x01 /* to pos 222 state 95 */,
	/* pos 222: state 95 */
	0xE9 /* 'i' */, 0x01 /* to pos 224 state 96 */,
	/* pos 224: state 96 */
	0xEF /* 'o' */, 0x01 /* to pos 226 state 97 */,
	/* pos 226: state 97 */
	0xEE /* 'n' */, 0x01 /* to pos 228 state 98 */,
	/* pos 228: state 98 */
	0xF3 /* 's' */, 0x01 /* to pos 230 state 99 */,
	/* pos 230: state 99 */
	0xBA /* ':' */, 0x01 /* to pos 232 state 100 */,
	/* pos 232: state 100 */
	0x8D, 0x00 /* terminal marker */,
	/* pos 234: state 101 */
	0xE3 /* 'c' */, 0x01 /* to pos 236 state 102 */,
	/* pos 236: state 102 */
	0xE3 /* 'c' */, 0x01 /* to pos 238 state 103 */,
	/* pos 238: state 103 */
	0xE5 /* 'e' */, 0x01 /* to pos 240 state 104 */,
	/* pos 240: state 104 */
	0xF0 /* 'p' */, 0x01 /* to pos 242 state 105 */,
	/* pos 242: state 105 */
	0xF4 /* 't' */, 0x01 /* to pos 244 state 106 */,
	/* pos 244: state 106 */
	0xBA /* ':' */, 0x01 /* to pos 246 state 107 */,
	/* pos 246: state 107 */
	0x8E, 0x00 /* terminal marker */,
	/* pos 248: state 108 */
	0xEF /* 'o' */, 0x01 /* to pos 250 state 109 */,
	/* pos 250: state 109 */
	0xEE /* 'n' */, 0x01 /* to pos 252 state 110 */,
	/* pos 252: state 110 */
	0xE3 /* 'c' */, 0x01 /* to pos 254 state 111 */,
	/* pos 254: state 111 */
	0xE5 /* 'e' */, 0x01 /* to pos 256 state 112 */,
	/* pos 256: state 112 */
	0xBA /* ':' */, 0x01 /* to pos 258 state 113 */,
	/* pos 258: state 113 */
	0x8F, 0x00 /* terminal marker */,
	/* pos 260: state 114 */
	0xD4 /* 'T' */, 0x01 /* to pos 262 state 115 */,
	/* pos 262: state 115 */
	0xD0 /* 'P' */, 0x01 /* to pos 264 state 116 */,
	/* pos 264: state 116 */
	0xAF /* '/' */, 0x01 /* to pos 266 state 117 */,
	/* pos 266: state 117 */
	0xB1 /* '1' */, 0x01 /* to pos 268 state 118 */,
	/* pos 268: state 118 */
	0xAE /* '.' */, 0x01 /* to pos 270 state 119 */,
	/* pos 270: state 119 */
	0xB1 /* '1' */, 0x01 /* to pos 272 state 120 */,
	/* pos 272: state 120 */
	0xA0 /* ' ' */, 0x01 /* to pos 274 state 121 */,
	/* pos 274: state 121 */
	0x90, 0x00 /* terminal marker */,
	/* total size 276 bytes */
};

int lextable_decode(int pos, char c)
{
	while (pos >= 0) {
		if (lextable[pos + 1] == 0) /* terminal marker */
			return pos;

		if ((lextable[pos] & 0x7f) == c)
			return pos + (lextable[pos + 1] << 1);

		if (lextable[pos] & 0x80)
			return -1;

		pos += 2;
	}
	return pos;
}

int lws_allocate_header_table(struct libwebsocket *wsi)
{
	wsi->u.hdr.ah = malloc(sizeof(*wsi->u.hdr.ah));
	if (wsi->u.hdr.ah == NULL) {
		lwsl_err("Out of memory\n");
		return -1;
	}
	memset(wsi->u.hdr.ah->frag_index, 0, sizeof(wsi->u.hdr.ah->frag_index));
	wsi->u.hdr.ah->next_frag_index = 0;
	wsi->u.hdr.ah->pos = 0;

	return 0;
}

LWS_VISIBLE int lws_hdr_total_length(struct libwebsocket *wsi, enum lws_token_indexes h)
{
	int n;
	int len = 0;

	n = wsi->u.hdr.ah->frag_index[h];
	if (n == 0)
		return 0;

	do {
		len += wsi->u.hdr.ah->frags[n].len;
		n = wsi->u.hdr.ah->frags[n].next_frag_index;
	} while (n);

	return len;
}

LWS_VISIBLE int lws_hdr_copy(struct libwebsocket *wsi, char *dest, int len,
						enum lws_token_indexes h)
{
	int toklen = lws_hdr_total_length(wsi, h);
	int n;

	if (toklen >= len)
		return -1;

	n = wsi->u.hdr.ah->frag_index[h];
	if (n == 0)
		return 0;

	do {
		strcpy(dest,
			&wsi->u.hdr.ah->data[wsi->u.hdr.ah->frags[n].offset]);
		dest += wsi->u.hdr.ah->frags[n].len;
		n = wsi->u.hdr.ah->frags[n].next_frag_index;
	} while (n);

	return toklen;
}

char *lws_hdr_simple_ptr(struct libwebsocket *wsi, enum lws_token_indexes h)
{
	int n;

	n = wsi->u.hdr.ah->frag_index[h];
	if (!n)
		return NULL;

	return &wsi->u.hdr.ah->data[wsi->u.hdr.ah->frags[n].offset];
}

int lws_hdr_simple_create(struct libwebsocket *wsi,
				enum lws_token_indexes h, const char *s)
{
	wsi->u.hdr.ah->next_frag_index++;
	if (wsi->u.hdr.ah->next_frag_index ==
	       sizeof(wsi->u.hdr.ah->frags) / sizeof(wsi->u.hdr.ah->frags[0])) {
		lwsl_warn("More hdr frags than we can deal with, dropping\n");
		return -1;
	}

	wsi->u.hdr.ah->frag_index[h] = wsi->u.hdr.ah->next_frag_index;

	wsi->u.hdr.ah->frags[wsi->u.hdr.ah->next_frag_index].offset =
							     wsi->u.hdr.ah->pos;
	wsi->u.hdr.ah->frags[wsi->u.hdr.ah->next_frag_index].len = 0;
	wsi->u.hdr.ah->frags[wsi->u.hdr.ah->next_frag_index].next_frag_index =
									      0;

	do {
		if (wsi->u.hdr.ah->pos == sizeof(wsi->u.hdr.ah->data)) {
			lwsl_err("Ran out of header data space\n");
			return -1;
		}
		wsi->u.hdr.ah->data[wsi->u.hdr.ah->pos++] = *s;
		if (*s)
			wsi->u.hdr.ah->frags[
					wsi->u.hdr.ah->next_frag_index].len++;
	} while (*s++);

	return 0;
}

int libwebsocket_parse(struct libwebsocket *wsi, unsigned char c)
{
	int n;

	switch (wsi->u.hdr.parser_state) {
	case WSI_TOKEN_GET_URI:
	case WSI_TOKEN_HOST:
	case WSI_TOKEN_CONNECTION:
	case WSI_TOKEN_KEY1:
	case WSI_TOKEN_KEY2:
	case WSI_TOKEN_PROTOCOL:
	case WSI_TOKEN_UPGRADE:
	case WSI_TOKEN_ORIGIN:
	case WSI_TOKEN_SWORIGIN:
	case WSI_TOKEN_DRAFT:
	case WSI_TOKEN_CHALLENGE:
	case WSI_TOKEN_KEY:
	case WSI_TOKEN_VERSION:
	case WSI_TOKEN_ACCEPT:
	case WSI_TOKEN_NONCE:
	case WSI_TOKEN_EXTENSIONS:
	case WSI_TOKEN_HTTP:

		lwsl_parser("WSI_TOK_(%d) '%c'\n", wsi->u.hdr.parser_state, c);

		/* collect into malloc'd buffers */
		/* optional initial space swallow */
		if (!wsi->u.hdr.ah->frags[wsi->u.hdr.ah->frag_index[
				      wsi->u.hdr.parser_state]].len && c == ' ')
			break;

		/* special case space terminator for get-uri */
		if (wsi->u.hdr.parser_state == WSI_TOKEN_GET_URI && c == ' ') {
			c = '\0';
			wsi->u.hdr.parser_state = WSI_TOKEN_SKIPPING;
		}

		/* bail at EOL */
		if (wsi->u.hdr.parser_state != WSI_TOKEN_CHALLENGE &&
								  c == '\x0d') {
			c = '\0';
			wsi->u.hdr.parser_state = WSI_TOKEN_SKIPPING_SAW_CR;
			lwsl_parser("*\n");
		}

		if (wsi->u.hdr.ah->pos == sizeof(wsi->u.hdr.ah->data)) {
			lwsl_warn("excessive header content\n");
			return -1;
		}
		wsi->u.hdr.ah->data[wsi->u.hdr.ah->pos++] = c;
		if (c)
			wsi->u.hdr.ah->frags[
					wsi->u.hdr.ah->next_frag_index].len++;

		/* per-protocol end of headers management */

		if (wsi->u.hdr.parser_state == WSI_TOKEN_CHALLENGE)
			goto set_parsing_complete;
		break;

		/* collecting and checking a name part */
	case WSI_TOKEN_NAME_PART:
		lwsl_parser("WSI_TOKEN_NAME_PART '%c'\n", c);

		wsi->u.hdr.lextable_pos =
				lextable_decode(wsi->u.hdr.lextable_pos, c);

		if (wsi->u.hdr.lextable_pos < 0) {
			/* this is not a header we know about */
			if (wsi->u.hdr.ah->frag_index[WSI_TOKEN_GET_URI] ||
				    wsi->u.hdr.ah->frag_index[WSI_TOKEN_HTTP]) {
				/*
				 * altready had the method, no idea what
				 * this crap is, ignore
				 */
				wsi->u.hdr.parser_state = WSI_TOKEN_SKIPPING;
				break;
			}
			/*
			 * hm it's an unknown http method in fact,
			 * treat as dangerous
			 */

			lwsl_info("Unknown method - dropping\n");
			return -1;
		}
		if (lextable[wsi->u.hdr.lextable_pos + 1] == 0) {

			/* terminal state */

			n = lextable[wsi->u.hdr.lextable_pos] & 0x7f;

			lwsl_parser("known hdr %d\n", n);

			if (n == WSI_TOKEN_GET_URI &&
				wsi->u.hdr.ah->frag_index[WSI_TOKEN_GET_URI]) {
				lwsl_warn("Duplicated GET\n");
				return -1;
			}

			/*
			 * WSORIGIN is protocol equiv to ORIGIN,
			 * JWebSocket likes to send it, map to ORIGIN
			 */
			if (n == WSI_TOKEN_SWORIGIN)
				n = WSI_TOKEN_ORIGIN;

			wsi->u.hdr.parser_state = (enum lws_token_indexes)
							(WSI_TOKEN_GET_URI + n);
			if (wsi->u.hdr.parser_state == WSI_TOKEN_CHALLENGE)
				goto set_parsing_complete;

			goto start_fragment;
		}
		break;

start_fragment:
		wsi->u.hdr.ah->next_frag_index++;
		if (wsi->u.hdr.ah->next_frag_index ==
				sizeof(wsi->u.hdr.ah->frags) /
					      sizeof(wsi->u.hdr.ah->frags[0])) {
			lwsl_warn("More hdr frags than we can deal with\n");
			return -1;
		}

		wsi->u.hdr.ah->frags[wsi->u.hdr.ah->next_frag_index].offset =
							     wsi->u.hdr.ah->pos;
		wsi->u.hdr.ah->frags[wsi->u.hdr.ah->next_frag_index].len = 0;
		wsi->u.hdr.ah->frags[
			    wsi->u.hdr.ah->next_frag_index].next_frag_index = 0;

		n = wsi->u.hdr.ah->frag_index[wsi->u.hdr.parser_state];
		if (!n) { /* first fragment */
			wsi->u.hdr.ah->frag_index[wsi->u.hdr.parser_state] =
						 wsi->u.hdr.ah->next_frag_index;
		} else { /* continuation */
			while (wsi->u.hdr.ah->frags[n].next_frag_index)
				n = wsi->u.hdr.ah->frags[n].next_frag_index;
			wsi->u.hdr.ah->frags[n].next_frag_index =
						 wsi->u.hdr.ah->next_frag_index;

			if (wsi->u.hdr.ah->pos == sizeof(wsi->u.hdr.ah->data)) {
				lwsl_warn("excessive header content\n");
				return -1;
			}

			wsi->u.hdr.ah->data[wsi->u.hdr.ah->pos++] = ' ';
			wsi->u.hdr.ah->frags[
					  wsi->u.hdr.ah->next_frag_index].len++;
		}

		break;


		/* skipping arg part of a name we didn't recognize */
	case WSI_TOKEN_SKIPPING:
		lwsl_parser("WSI_TOKEN_SKIPPING '%c'\n", c);
		if (c == '\x0d')
			wsi->u.hdr.parser_state = WSI_TOKEN_SKIPPING_SAW_CR;
		break;

	case WSI_TOKEN_SKIPPING_SAW_CR:
		lwsl_parser("WSI_TOKEN_SKIPPING_SAW_CR '%c'\n", c);
		if (c == '\x0a') {
			wsi->u.hdr.parser_state = WSI_TOKEN_NAME_PART;
			wsi->u.hdr.lextable_pos = 0;
		} else
			wsi->u.hdr.parser_state = WSI_TOKEN_SKIPPING;
		break;
		/* we're done, ignore anything else */
	case WSI_PARSING_COMPLETE:
		lwsl_parser("WSI_PARSING_COMPLETE '%c'\n", c);
		break;

	default:	/* keep gcc happy */
		break;
	}

	return 0;

set_parsing_complete:

	if (lws_hdr_total_length(wsi, WSI_TOKEN_UPGRADE)) {
		if (lws_hdr_total_length(wsi, WSI_TOKEN_VERSION))
			wsi->ietf_spec_revision =
			       atoi(lws_hdr_simple_ptr(wsi, WSI_TOKEN_VERSION));

		lwsl_parser("v%02d hdrs completed\n", wsi->ietf_spec_revision);
	}
	wsi->u.hdr.parser_state = WSI_PARSING_COMPLETE;
	wsi->hdr_parsing_completed = 1;

	return 0;
}


/**
 * lws_frame_is_binary: true if the current frame was sent in binary mode
 *
 * @wsi: the connection we are inquiring about
 *
 * This is intended to be called from the LWS_CALLBACK_RECEIVE callback if
 * it's interested to see if the frame it's dealing with was sent in binary
 * mode.
 */

LWS_VISIBLE int lws_frame_is_binary(struct libwebsocket *wsi)
{
	return wsi->u.ws.frame_is_binary;
}

int
libwebsocket_rx_sm(struct libwebsocket *wsi, unsigned char c)
{
	int n;
	struct lws_tokens eff_buf;
	int ret = 0;
#ifndef LWS_NO_EXTENSIONS
	int handled;
	int m;
#endif

#if 0
	lwsl_debug("RX: %02X ", c);
#endif

	switch (wsi->lws_rx_parse_state) {
	case LWS_RXPS_NEW:

		switch (wsi->ietf_spec_revision) {
		case 13:
			/*
			 * no prepended frame key any more
			 */
			wsi->u.ws.all_zero_nonce = 1;
			goto handle_first;

		default:
			lwsl_warn("lws_rx_sm: unknown spec version %d\n",
						       wsi->ietf_spec_revision);
			break;
		}
		break;
	case LWS_RXPS_04_MASK_NONCE_1:
		wsi->u.ws.frame_masking_nonce_04[1] = c;
		if (c)
			wsi->u.ws.all_zero_nonce = 0;
		wsi->lws_rx_parse_state = LWS_RXPS_04_MASK_NONCE_2;
		break;
	case LWS_RXPS_04_MASK_NONCE_2:
		wsi->u.ws.frame_masking_nonce_04[2] = c;
		if (c)
			wsi->u.ws.all_zero_nonce = 0;
		wsi->lws_rx_parse_state = LWS_RXPS_04_MASK_NONCE_3;
		break;
	case LWS_RXPS_04_MASK_NONCE_3:
		wsi->u.ws.frame_masking_nonce_04[3] = c;
		if (c)
			wsi->u.ws.all_zero_nonce = 0;

		/*
		 * start from the zero'th byte in the XOR key buffer since
		 * this is the start of a frame with a new key
		 */

		wsi->u.ws.frame_mask_index = 0;

		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_1;
		break;

	/*
	 *  04 logical framing from the spec (all this is masked when incoming
	 *  and has to be unmasked)
	 *
	 * We ignore the possibility of extension data because we don't
	 * negotiate any extensions at the moment.
	 *
	 *    0                   1                   2                   3
	 *    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	 *   +-+-+-+-+-------+-+-------------+-------------------------------+
	 *   |F|R|R|R| opcode|R| Payload len |    Extended payload length    |
	 *   |I|S|S|S|  (4)  |S|     (7)     |             (16/63)           |
	 *   |N|V|V|V|       |V|             |   (if payload len==126/127)   |
	 *   | |1|2|3|       |4|             |                               |
	 *   +-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
	 *   |     Extended payload length continued, if payload len == 127  |
	 *   + - - - - - - - - - - - - - - - +-------------------------------+
	 *   |                               |         Extension data        |
	 *   +-------------------------------+ - - - - - - - - - - - - - - - +
	 *   :                                                               :
	 *   +---------------------------------------------------------------+
	 *   :                       Application data                        :
	 *   +---------------------------------------------------------------+
	 *
	 *  We pass payload through to userland as soon as we get it, ignoring
	 *  FIN.  It's up to userland to buffer it up if it wants to see a
	 *  whole unfragmented block of the original size (which may be up to
	 *  2^63 long!)
	 */

	case LWS_RXPS_04_FRAME_HDR_1:
handle_first:

		wsi->u.ws.opcode = c & 0xf;
		wsi->u.ws.rsv = c & 0x70;
		wsi->u.ws.final = !!((c >> 7) & 1);

		switch (wsi->u.ws.opcode) {
		case LWS_WS_OPCODE_07__TEXT_FRAME:
		case LWS_WS_OPCODE_07__BINARY_FRAME:
			wsi->u.ws.frame_is_binary =
			     wsi->u.ws.opcode == LWS_WS_OPCODE_07__BINARY_FRAME;
			break;
		}
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN:

		wsi->u.ws.this_frame_masked = !!(c & 0x80);

		switch (c & 0x7f) {
		case 126:
			/* control frames are not allowed to have big lengths */
			if (wsi->u.ws.opcode & 8)
				goto illegal_ctl_length;

			wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN16_2;
			break;
		case 127:
			/* control frames are not allowed to have big lengths */
			if (wsi->u.ws.opcode & 8)
				goto illegal_ctl_length;

			wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN64_8;
			break;
		default:
			wsi->u.ws.rx_packet_length = c & 0x7f;
			if (wsi->u.ws.this_frame_masked)
				wsi->lws_rx_parse_state =
						LWS_RXPS_07_COLLECT_FRAME_KEY_1;
			else
				wsi->lws_rx_parse_state =
					LWS_RXPS_PAYLOAD_UNTIL_LENGTH_EXHAUSTED;
			break;
		}
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN16_2:
		wsi->u.ws.rx_packet_length = c << 8;
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN16_1;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN16_1:
		wsi->u.ws.rx_packet_length |= c;
		if (wsi->u.ws.this_frame_masked)
			wsi->lws_rx_parse_state =
					LWS_RXPS_07_COLLECT_FRAME_KEY_1;
		else
			wsi->lws_rx_parse_state =
				LWS_RXPS_PAYLOAD_UNTIL_LENGTH_EXHAUSTED;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN64_8:
		if (c & 0x80) {
			lwsl_warn("b63 of length must be zero\n");
			/* kill the connection */
			return -1;
		}
#if defined __LP64__
		wsi->u.ws.rx_packet_length = ((size_t)c) << 56;
#else
		wsi->u.ws.rx_packet_length = 0;
#endif
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN64_7;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN64_7:
#if defined __LP64__
		wsi->u.ws.rx_packet_length |= ((size_t)c) << 48;
#endif
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN64_6;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN64_6:
#if defined __LP64__
		wsi->u.ws.rx_packet_length |= ((size_t)c) << 40;
#endif
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN64_5;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN64_5:
#if defined __LP64__
		wsi->u.ws.rx_packet_length |= ((size_t)c) << 32;
#endif
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN64_4;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN64_4:
		wsi->u.ws.rx_packet_length |= ((size_t)c) << 24;
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN64_3;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN64_3:
		wsi->u.ws.rx_packet_length |= ((size_t)c) << 16;
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN64_2;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN64_2:
		wsi->u.ws.rx_packet_length |= ((size_t)c) << 8;
		wsi->lws_rx_parse_state = LWS_RXPS_04_FRAME_HDR_LEN64_1;
		break;

	case LWS_RXPS_04_FRAME_HDR_LEN64_1:
		wsi->u.ws.rx_packet_length |= ((size_t)c);
		if (wsi->u.ws.this_frame_masked)
			wsi->lws_rx_parse_state =
					LWS_RXPS_07_COLLECT_FRAME_KEY_1;
		else
			wsi->lws_rx_parse_state =
				LWS_RXPS_PAYLOAD_UNTIL_LENGTH_EXHAUSTED;
		break;

	case LWS_RXPS_07_COLLECT_FRAME_KEY_1:
		wsi->u.ws.frame_masking_nonce_04[0] = c;
		if (c)
			wsi->u.ws.all_zero_nonce = 0;
		wsi->lws_rx_parse_state = LWS_RXPS_07_COLLECT_FRAME_KEY_2;
		break;

	case LWS_RXPS_07_COLLECT_FRAME_KEY_2:
		wsi->u.ws.frame_masking_nonce_04[1] = c;
		if (c)
			wsi->u.ws.all_zero_nonce = 0;
		wsi->lws_rx_parse_state = LWS_RXPS_07_COLLECT_FRAME_KEY_3;
		break;

	case LWS_RXPS_07_COLLECT_FRAME_KEY_3:
		wsi->u.ws.frame_masking_nonce_04[2] = c;
		if (c)
			wsi->u.ws.all_zero_nonce = 0;
		wsi->lws_rx_parse_state = LWS_RXPS_07_COLLECT_FRAME_KEY_4;
		break;

	case LWS_RXPS_07_COLLECT_FRAME_KEY_4:
		wsi->u.ws.frame_masking_nonce_04[3] = c;
		if (c)
			wsi->u.ws.all_zero_nonce = 0;
		wsi->lws_rx_parse_state =
					LWS_RXPS_PAYLOAD_UNTIL_LENGTH_EXHAUSTED;
		wsi->u.ws.frame_mask_index = 0;
		if (wsi->u.ws.rx_packet_length == 0)
			goto spill;
		break;


	case LWS_RXPS_PAYLOAD_UNTIL_LENGTH_EXHAUSTED:

		if (!wsi->u.ws.rx_user_buffer)
			lwsl_err("NULL user buffer...\n");

		if (wsi->u.ws.all_zero_nonce)
			wsi->u.ws.rx_user_buffer[LWS_SEND_BUFFER_PRE_PADDING +
			       (wsi->u.ws.rx_user_buffer_head++)] = c;
		else
			wsi->u.ws.rx_user_buffer[LWS_SEND_BUFFER_PRE_PADDING +
			       (wsi->u.ws.rx_user_buffer_head++)] =
				   c ^ wsi->u.ws.frame_masking_nonce_04[
					    (wsi->u.ws.frame_mask_index++) & 3];

		if (--wsi->u.ws.rx_packet_length == 0) {
			/* spill because we have the whole frame */
			wsi->lws_rx_parse_state = LWS_RXPS_NEW;
			goto spill;
		}

		/*
		 * if there's no protocol max frame size given, we are
		 * supposed to default to LWS_MAX_SOCKET_IO_BUF
		 */

		if (!wsi->protocol->rx_buffer_size &&
			 		wsi->u.ws.rx_user_buffer_head !=
			 				  LWS_MAX_SOCKET_IO_BUF)
			break;
		else
			if (wsi->protocol->rx_buffer_size &&
					wsi->u.ws.rx_user_buffer_head !=
						  wsi->protocol->rx_buffer_size)
			break;

		/* spill because we filled our rx buffer */
spill:
		/*
		 * is this frame a control packet we should take care of at this
		 * layer?  If so service it and hide it from the user callback
		 */

		lwsl_parser("spill on %s\n", wsi->protocol->name);

		switch (wsi->u.ws.opcode) {
		case LWS_WS_OPCODE_07__CLOSE:
			/* is this an acknowledgement of our close? */
			if (wsi->state == WSI_STATE_AWAITING_CLOSE_ACK) {
				/*
				 * fine he has told us he is closing too, let's
				 * finish our close
				 */
				lwsl_parser("seen client close ack\n");
				return -1;
			}
			lwsl_parser("server sees client close packet\n");
			/* parrot the close packet payload back */
			n = libwebsocket_write(wsi, (unsigned char *)
				&wsi->u.ws.rx_user_buffer[
					LWS_SEND_BUFFER_PRE_PADDING],
					wsi->u.ws.rx_user_buffer_head,
							       LWS_WRITE_CLOSE);
			if (n < 0)
				lwsl_info("write of close ack failed %d\n", n);
			wsi->state = WSI_STATE_RETURNED_CLOSE_ALREADY;
			/* close the connection */
			return -1;

		case LWS_WS_OPCODE_07__PING:
			lwsl_info("received %d byte ping, sending pong\n",
						 wsi->u.ws.rx_user_buffer_head);
			lwsl_hexdump(&wsi->u.ws.rx_user_buffer[
					LWS_SEND_BUFFER_PRE_PADDING],
						 wsi->u.ws.rx_user_buffer_head);
			/* parrot the ping packet payload back as a pong */
			n = libwebsocket_write(wsi, (unsigned char *)
			&wsi->u.ws.rx_user_buffer[LWS_SEND_BUFFER_PRE_PADDING],
				 wsi->u.ws.rx_user_buffer_head, LWS_WRITE_PONG);
			if (n < 0)
				return -1;
			/* ... then just drop it */
			wsi->u.ws.rx_user_buffer_head = 0;
			return 0;

		case LWS_WS_OPCODE_07__PONG:
			/* ... then just drop it */
			wsi->u.ws.rx_user_buffer_head = 0;
			return 0;

		case LWS_WS_OPCODE_07__TEXT_FRAME:
		case LWS_WS_OPCODE_07__BINARY_FRAME:
		case LWS_WS_OPCODE_07__CONTINUATION:
			break;

		default:
#ifndef LWS_NO_EXTENSIONS
			lwsl_parser("passing opc %x up to exts\n",
							wsi->u.ws.opcode);

			/*
			 * It's something special we can't understand here.
			 * Pass the payload up to the extension's parsing
			 * state machine.
			 */

			eff_buf.token = &wsi->u.ws.rx_user_buffer[
						   LWS_SEND_BUFFER_PRE_PADDING];
			eff_buf.token_len = wsi->u.ws.rx_user_buffer_head;

			handled = 0;
			for (n = 0; n < wsi->count_active_extensions; n++) {
				m = wsi->active_extensions[n]->callback(
					wsi->protocol->owning_server,
					wsi->active_extensions[n], wsi,
					LWS_EXT_CALLBACK_EXTENDED_PAYLOAD_RX,
					    wsi->active_extensions_user[n],
								   &eff_buf, 0);
				if (m)
					handled = 1;
			}

			if (!handled)
#endif
				lwsl_ext("ext opc opcode 0x%x unknown\n",
							      wsi->u.ws.opcode);

			wsi->u.ws.rx_user_buffer_head = 0;
			return 0;
		}

		/*
		 * No it's real payload, pass it up to the user callback.
		 * It's nicely buffered with the pre-padding taken care of
		 * so it can be sent straight out again using libwebsocket_write
		 */

		eff_buf.token = &wsi->u.ws.rx_user_buffer[
						LWS_SEND_BUFFER_PRE_PADDING];
		eff_buf.token_len = wsi->u.ws.rx_user_buffer_head;
#ifndef LWS_NO_EXTENSIONS
		for (n = 0; n < wsi->count_active_extensions; n++) {
			m = wsi->active_extensions[n]->callback(
				wsi->protocol->owning_server,
				wsi->active_extensions[n], wsi,
				LWS_EXT_CALLBACK_PAYLOAD_RX,
				wsi->active_extensions_user[n],
				&eff_buf, 0);
			if (m < 0) {
				lwsl_ext(
				 "Extension '%s' failed to handle payload!\n",
					      wsi->active_extensions[n]->name);
				return -1;
			}
		}
#endif
		if (eff_buf.token_len > 0) {
			eff_buf.token[eff_buf.token_len] = '\0';

			if (wsi->protocol->callback)
				ret = user_callback_handle_rxflow(
						wsi->protocol->callback,
						wsi->protocol->owning_server,
						wsi, LWS_CALLBACK_RECEIVE,
						wsi->user_space,
						eff_buf.token,
						eff_buf.token_len);
		    else
			    lwsl_err("No callback on payload spill!\n");
		}

		wsi->u.ws.rx_user_buffer_head = 0;
		break;
	}

	return ret;

illegal_ctl_length:

	lwsl_warn("Control frame with xtended length is illegal\n");
	/* kill the connection */
	return -1;
}


int libwebsocket_interpret_incoming_packet(struct libwebsocket *wsi,
						 unsigned char *buf, size_t len)
{
	size_t n = 0;
	int m;

#if 0
	lwsl_parser("received %d byte packet\n", (int)len);
	lwsl_hexdump(buf, len);
#endif

	/* let the rx protocol state machine have as much as it needs */

	while (n < len) {
		/*
		 * we were accepting input but now we stopped doing so
		 */
		if (!(wsi->u.ws.rxflow_change_to & LWS_RXFLOW_ALLOW)) {
			/* his RX is flowcontrolled, don't send remaining now */
			if (!wsi->u.ws.rxflow_buffer) {
				/* a new rxflow, buffer it and warn caller */
				lwsl_info("new rxflow input buffer len %d\n",
								       len - n);
				wsi->u.ws.rxflow_buffer =
					       (unsigned char *)malloc(len - n);
				wsi->u.ws.rxflow_len = len - n;
				wsi->u.ws.rxflow_pos = 0;
				memcpy(wsi->u.ws.rxflow_buffer,
							buf + n, len - n);
			} else
				/* rxflow while we were spilling prev rxflow */
				lwsl_info("stalling in existing rxflow buf\n");

			return 1;
		}

		/* account for what we're using in rxflow buffer */
		if (wsi->u.ws.rxflow_buffer)
			wsi->u.ws.rxflow_pos++;

		/* process the byte */
		m = libwebsocket_rx_sm(wsi, buf[n++]);
		if (m < 0)
			return -1;
	}

	return 0;
}


/**
 * libwebsockets_remaining_packet_payload() - Bytes to come before "overall"
 *					      rx packet is complete
 * @wsi:		Websocket instance (available from user callback)
 *
 *	This function is intended to be called from the callback if the
 *  user code is interested in "complete packets" from the client.
 *  libwebsockets just passes through payload as it comes and issues a buffer
 *  additionally when it hits a built-in limit.  The LWS_CALLBACK_RECEIVE
 *  callback handler can use this API to find out if the buffer it has just
 *  been given is the last piece of a "complete packet" from the client --
 *  when that is the case libwebsockets_remaining_packet_payload() will return
 *  0.
 *
 *  Many protocols won't care becuse their packets are always small.
 */

LWS_VISIBLE size_t
libwebsockets_remaining_packet_payload(struct libwebsocket *wsi)
{
	return wsi->u.ws.rx_packet_length;
}
