/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


/*
    These are our vertex-indices for a series of "quads", which we implement
    as a series of pairs of triangles. See setRectFan() for the
    vertex order.

    The largest value is 255, so we could store these in any size
    (byte, short, int). Since the table is small, we just choose the size
    that we think will be fastest (e.g. some drivers don't have native support
    for byte-indices, so byte may not be the fastest)
*/
static const uint16_t gQuadIndexTable[] = {
      0,   1,   2,   0,   2,   3,
      4,   5,   6,   4,   6,   7,
      8,   9,  10,   8,  10,  11,
     12,  13,  14,  12,  14,  15,
     16,  17,  18,  16,  18,  19,
     20,  21,  22,  20,  22,  23,
     24,  25,  26,  24,  26,  27,
     28,  29,  30,  28,  30,  31,
     32,  33,  34,  32,  34,  35,
     36,  37,  38,  36,  38,  39,
     40,  41,  42,  40,  42,  43,
     44,  45,  46,  44,  46,  47,
     48,  49,  50,  48,  50,  51,
     52,  53,  54,  52,  54,  55,
     56,  57,  58,  56,  58,  59,
     60,  61,  62,  60,  62,  63,
     64,  65,  66,  64,  66,  67,
     68,  69,  70,  68,  70,  71,
     72,  73,  74,  72,  74,  75,
     76,  77,  78,  76,  78,  79,
     80,  81,  82,  80,  82,  83,
     84,  85,  86,  84,  86,  87,
     88,  89,  90,  88,  90,  91,
     92,  93,  94,  92,  94,  95,
     96,  97,  98,  96,  98,  99,
    100, 101, 102, 100, 102, 103,
    104, 105, 106, 104, 106, 107,
    108, 109, 110, 108, 110, 111,
    112, 113, 114, 112, 114, 115,
    116, 117, 118, 116, 118, 119,
    120, 121, 122, 120, 122, 123,
    124, 125, 126, 124, 126, 127,
    128, 129, 130, 128, 130, 131,
    132, 133, 134, 132, 134, 135,
    136, 137, 138, 136, 138, 139,
    140, 141, 142, 140, 142, 143,
    144, 145, 146, 144, 146, 147,
    148, 149, 150, 148, 150, 151,
    152, 153, 154, 152, 154, 155,
    156, 157, 158, 156, 158, 159,
    160, 161, 162, 160, 162, 163,
    164, 165, 166, 164, 166, 167,
    168, 169, 170, 168, 170, 171,
    172, 173, 174, 172, 174, 175,
    176, 177, 178, 176, 178, 179,
    180, 181, 182, 180, 182, 183,
    184, 185, 186, 184, 186, 187,
    188, 189, 190, 188, 190, 191,
    192, 193, 194, 192, 194, 195,
    196, 197, 198, 196, 198, 199,
    200, 201, 202, 200, 202, 203,
    204, 205, 206, 204, 206, 207,
    208, 209, 210, 208, 210, 211,
    212, 213, 214, 212, 214, 215,
    216, 217, 218, 216, 218, 219,
    220, 221, 222, 220, 222, 223,
    224, 225, 226, 224, 226, 227,
    228, 229, 230, 228, 230, 231,
    232, 233, 234, 232, 234, 235,
    236, 237, 238, 236, 238, 239,
    240, 241, 242, 240, 242, 243,
    244, 245, 246, 244, 246, 247,
    248, 249, 250, 248, 250, 251,
    252, 253, 254, 252, 254, 255,
};

#define GR_COUNT_QUADINDEXTABLE    GR_ARRAY_COUNT(gQuadIndexTable)



