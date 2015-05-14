/*--
 Copyright 2009-2010 by Stefan Rusterholz.
 All rights reserved.
 You can choose between MIT and BSD-3-Clause license. License file will be added later.
 --*/

/**
 * See cc.Codec.GZip.gunzip.
 * @param {Array | String} data The bytestream to decompress
 * Constructor
 */
cc.Codec.GZip = function Jacob__GZip(data) {
    this.data = data;

    this.debug = false;
    this.gpflags = undefined;
    this.files = 0;
    this.unzipped = [];
    this.buf32k = new Array(32768);
    this.bIdx = 0;
    this.modeZIP = false;
    this.bytepos = 0;
    this.bb = 1;
    this.bits = 0;
    this.nameBuf = [];
    this.fileout = undefined;
    this.literalTree = new Array(cc.Codec.GZip.LITERALS);
    this.distanceTree = new Array(32);
    this.treepos = 0;
    this.Places = null;
    this.len = 0;
    this.fpos = new Array(17);
    this.fpos[0] = 0;
    this.flens = undefined;
    this.fmax = undefined;
};

/**
 * Unzips the gzipped data of the 'data' argument.
 * @param string  The bytestream to decompress. Either an array of Integers between 0 and 255, or a String.
 * @return {String}
 */
cc.Codec.GZip.gunzip = function (string) {
    if (string.constructor === Array) {
    } else if (string.constructor === String) {
    }
    var gzip = new cc.Codec.GZip(string);
    return gzip.gunzip()[0][0];
};

cc.Codec.GZip.HufNode = function () {
    this.b0 = 0;
    this.b1 = 0;
    this.jump = null;
    this.jumppos = -1;
};

/**
 * @constant
 * @type Number
 */
cc.Codec.GZip.LITERALS = 288;
/**
 * @constant
 * @type Number
 */
cc.Codec.GZip.NAMEMAX = 256;

cc.Codec.GZip.bitReverse = [
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
];
cc.Codec.GZip.cplens = [
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
    35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0
];
cc.Codec.GZip.cplext = [
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 99, 99
];
/* 99==invalid */
cc.Codec.GZip.cpdist = [
    0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0007, 0x0009, 0x000d,
    0x0011, 0x0019, 0x0021, 0x0031, 0x0041, 0x0061, 0x0081, 0x00c1,
    0x0101, 0x0181, 0x0201, 0x0301, 0x0401, 0x0601, 0x0801, 0x0c01,
    0x1001, 0x1801, 0x2001, 0x3001, 0x4001, 0x6001
];
cc.Codec.GZip.cpdext = [
    0, 0, 0, 0, 1, 1, 2, 2,
    3, 3, 4, 4, 5, 5, 6, 6,
    7, 7, 8, 8, 9, 9, 10, 10,
    11, 11, 12, 12, 13, 13
];
cc.Codec.GZip.border = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15];


/**
 * gunzip
 * @return {Array}
 */
cc.Codec.GZip.prototype.gunzip = function () {
    this.outputArr = [];

    //convertToByteArray(input);
    //if (this.debug) alert(this.data);

    this.nextFile();
    return this.unzipped;
};

cc.Codec.GZip.prototype.readByte = function () {
    this.bits += 8;
    if (this.bytepos < this.data.length) {
        //return this.data[this.bytepos++]; // Array
        return this.data.charCodeAt(this.bytepos++);
    } else {
        return -1;
    }
};

cc.Codec.GZip.prototype.byteAlign = function () {
    this.bb = 1;
};

cc.Codec.GZip.prototype.readBit = function () {
    var carry;
    this.bits++;
    carry = (this.bb & 1);
    this.bb >>= 1;
    if (this.bb === 0) {
        this.bb = this.readByte();
        carry = (this.bb & 1);
        this.bb = (this.bb >> 1) | 0x80;
    }
    return carry;
};

cc.Codec.GZip.prototype.readBits = function (a) {
    var res = 0,
        i = a;

    while (i--) res = (res << 1) | this.readBit();
    if (a) res = cc.Codec.GZip.bitReverse[res] >> (8 - a);

    return res;
};

cc.Codec.GZip.prototype.flushBuffer = function () {
    this.bIdx = 0;
};

cc.Codec.GZip.prototype.addBuffer = function (a) {
    this.buf32k[this.bIdx++] = a;
    this.outputArr.push(String.fromCharCode(a));
    if (this.bIdx === 0x8000) this.bIdx = 0;
};

cc.Codec.GZip.prototype.IsPat = function () {
    while (1) {
        if (this.fpos[this.len] >= this.fmax)       return -1;
        if (this.flens[this.fpos[this.len]] === this.len) return this.fpos[this.len]++;
        this.fpos[this.len]++;
    }
};

cc.Codec.GZip.prototype.Rec = function () {
    var curplace = this.Places[this.treepos];
    var tmp;
    //if (this.debug) document.write("<br>len:"+this.len+" treepos:"+this.treepos);
    if (this.len === 17) { //war 17
        return -1;
    }
    this.treepos++;
    this.len++;

    tmp = this.IsPat();
    //if (this.debug) document.write("<br>IsPat "+tmp);
    if (tmp >= 0) {
        curplace.b0 = tmp;
        /* leaf cell for 0-bit */
        //if (this.debug) document.write("<br>b0 "+curplace.b0);
    } else {
        /* Not a Leaf cell */
        curplace.b0 = 0x8000;
        //if (this.debug) document.write("<br>b0 "+curplace.b0);
        if (this.Rec()) return -1;
    }
    tmp = this.IsPat();
    if (tmp >= 0) {
        curplace.b1 = tmp;
        /* leaf cell for 1-bit */
        //if (this.debug) document.write("<br>b1 "+curplace.b1);
        curplace.jump = null;
        /* Just for the display routine */
    } else {
        /* Not a Leaf cell */
        curplace.b1 = 0x8000;
        //if (this.debug) document.write("<br>b1 "+curplace.b1);
        curplace.jump = this.Places[this.treepos];
        curplace.jumppos = this.treepos;
        if (this.Rec()) return -1;
    }
    this.len--;
    return 0;
};

cc.Codec.GZip.prototype.CreateTree = function (currentTree, numval, lengths, show) {
    var i;
    /* Create the Huffman decode tree/table */
    //if (this.debug) document.write("currentTree "+currentTree+" numval "+numval+" lengths "+lengths+" show "+show);
    this.Places = currentTree;
    this.treepos = 0;
    this.flens = lengths;
    this.fmax = numval;
    for (i = 0; i < 17; i++) this.fpos[i] = 0;
    this.len = 0;
    if (this.Rec()) {
        //if (this.debug) alert("invalid huffman tree\n");
        return -1;
    }
    // if (this.debug) {
    //   document.write('<br>Tree: '+this.Places.length);
    //   for (var a=0;a<32;a++){
    //     document.write("Places["+a+"].b0="+this.Places[a].b0+"<br>");
    //     document.write("Places["+a+"].b1="+this.Places[a].b1+"<br>");
    //   }
    // }

    return 0;
};

cc.Codec.GZip.prototype.DecodeValue = function (currentTree) {
    var len, i,
        xtreepos = 0,
        X = currentTree[xtreepos],
        b;

    /* decode one symbol of the data */
    while (1) {
        b = this.readBit();
        // if (this.debug) document.write("b="+b);
        if (b) {
            if (!(X.b1 & 0x8000)) {
                // if (this.debug) document.write("ret1");
                return X.b1;
                /* If leaf node, return data */
            }
            X = X.jump;
            len = currentTree.length;
            for (i = 0; i < len; i++) {
                if (currentTree[i] === X) {
                    xtreepos = i;
                    break;
                }
            }
        } else {
            if (!(X.b0 & 0x8000)) {
                // if (this.debug) document.write("ret2");
                return X.b0;
                /* If leaf node, return data */
            }
            xtreepos++;
            X = currentTree[xtreepos];
        }
    }
    // if (this.debug) document.write("ret3");

    return -1;
};

cc.Codec.GZip.prototype.DeflateLoop = function () {
    var last, c, type, i, len;
    do {
        last = this.readBit();
        type = this.readBits(2);

        if (type === 0) {
            var blockLen, cSum;

            // Stored
            this.byteAlign();
            blockLen = this.readByte();
            blockLen |= (this.readByte() << 8);

            cSum = this.readByte();
            cSum |= (this.readByte() << 8);

            if (((blockLen ^ ~cSum) & 0xffff)) {
                document.write("BlockLen checksum mismatch\n"); // FIXME: use throw
            }
            while (blockLen--) {
                c = this.readByte();
                this.addBuffer(c);
            }
        } else if (type === 1) {
            var j;

            /* Fixed Huffman tables -- fixed decode routine */
            while (1) {
                /*
                 256    0000000        0
                 :   :     :
                 279    0010111        23
                 0   00110000    48
                 :    :      :
                 143    10111111    191
                 280 11000000    192
                 :    :      :
                 287 11000111    199
                 144    110010000    400
                 :    :       :
                 255    111111111    511

                 Note the bit order!
                 */
                j = (cc.Codec.GZip.bitReverse[this.readBits(7)] >> 1);
                if (j > 23) {
                    j = (j << 1) | this.readBit();
                    /* 48..255 */

                    if (j > 199) {              /* 200..255 */
                        j -= 128;
                        /*  72..127 */
                        j = (j << 1) | this.readBit();
                        /* 144..255 << */
                    } else {                    /*  48..199 */
                        j -= 48;
                        /*   0..151 */
                        if (j > 143) {
                            j = j + 136;
                            /* 280..287 << */
                            /*   0..143 << */
                        }
                    }
                } else {                      /*   0..23 */
                    j += 256;
                    /* 256..279 << */
                }
                if (j < 256) {
                    this.addBuffer(j);
                } else if (j === 256) {
                    /* EOF */
                    break; // FIXME: make this the loop-condition
                } else {
                    var len, dist;

                    j -= 256 + 1;
                    /* bytes + EOF */
                    len = this.readBits(cc.Codec.GZip.cplext[j]) + cc.Codec.GZip.cplens[j];

                    j = cc.Codec.GZip.bitReverse[this.readBits(5)] >> 3;
                    if (cc.Codec.GZip.cpdext[j] > 8) {
                        dist = this.readBits(8);
                        dist |= (this.readBits(cc.Codec.GZip.cpdext[j] - 8) << 8);
                    } else {
                        dist = this.readBits(cc.Codec.GZip.cpdext[j]);
                    }
                    dist += cc.Codec.GZip.cpdist[j];

                    for (j = 0; j < len; j++) {
                        var c = this.buf32k[(this.bIdx - dist) & 0x7fff];
                        this.addBuffer(c);
                    }
                }
            } // while

        } else if (type === 2) {
            var j, n, literalCodes, distCodes, lenCodes;
            var ll = new Array(288 + 32);    // "static" just to preserve stack

            // Dynamic Huffman tables

            literalCodes = 257 + this.readBits(5);
            distCodes = 1 + this.readBits(5);
            lenCodes = 4 + this.readBits(4);
            for (j = 0; j < 19; j++) {
                ll[j] = 0;
            }

            // Get the decode tree code lengths

            for (j = 0; j < lenCodes; j++) {
                ll[cc.Codec.GZip.border[j]] = this.readBits(3);
            }
            len = this.distanceTree.length;
            for (i = 0; i < len; i++) this.distanceTree[i] = new cc.Codec.GZip.HufNode();
            if (this.CreateTree(this.distanceTree, 19, ll, 0)) {
                this.flushBuffer();
                return 1;
            }
            // if (this.debug) {
            //   document.write("<br>distanceTree");
            //   for(var a=0;a<this.distanceTree.length;a++){
            //     document.write("<br>"+this.distanceTree[a].b0+" "+this.distanceTree[a].b1+" "+this.distanceTree[a].jump+" "+this.distanceTree[a].jumppos);
            //   }
            // }

            //read in literal and distance code lengths
            n = literalCodes + distCodes;
            i = 0;
            var z = -1;
            // if (this.debug) document.write("<br>n="+n+" bits: "+this.bits+"<br>");
            while (i < n) {
                z++;
                j = this.DecodeValue(this.distanceTree);
                // if (this.debug) document.write("<br>"+z+" i:"+i+" decode: "+j+"    bits "+this.bits+"<br>");
                if (j < 16) {    // length of code in bits (0..15)
                    ll[i++] = j;
                } else if (j === 16) {    // repeat last length 3 to 6 times
                    var l;
                    j = 3 + this.readBits(2);
                    if (i + j > n) {
                        this.flushBuffer();
                        return 1;
                    }
                    l = i ? ll[i - 1] : 0;
                    while (j--) {
                        ll[i++] = l;
                    }
                } else {
                    if (j === 17) {        // 3 to 10 zero length codes
                        j = 3 + this.readBits(3);
                    } else {        // j == 18: 11 to 138 zero length codes
                        j = 11 + this.readBits(7);
                    }
                    if (i + j > n) {
                        this.flushBuffer();
                        return 1;
                    }
                    while (j--) {
                        ll[i++] = 0;
                    }
                }
            } // while

            // Can overwrite tree decode tree as it is not used anymore
            len = this.literalTree.length;
            for (i = 0; i < len; i++)
                this.literalTree[i] = new cc.Codec.GZip.HufNode();
            if (this.CreateTree(this.literalTree, literalCodes, ll, 0)) {
                this.flushBuffer();
                return 1;
            }
            len = this.literalTree.length;
            for (i = 0; i < len; i++) this.distanceTree[i] = new cc.Codec.GZip.HufNode();
            var ll2 = new Array();
            for (i = literalCodes; i < ll.length; i++) ll2[i - literalCodes] = ll[i];
            if (this.CreateTree(this.distanceTree, distCodes, ll2, 0)) {
                this.flushBuffer();
                return 1;
            }
            // if (this.debug) document.write("<br>literalTree");
            while (1) {
                j = this.DecodeValue(this.literalTree);
                if (j >= 256) {        // In C64: if carry set
                    var len, dist;
                    j -= 256;
                    if (j === 0) {
                        // EOF
                        break;
                    }
                    j--;
                    len = this.readBits(cc.Codec.GZip.cplext[j]) + cc.Codec.GZip.cplens[j];

                    j = this.DecodeValue(this.distanceTree);
                    if (cc.Codec.GZip.cpdext[j] > 8) {
                        dist = this.readBits(8);
                        dist |= (this.readBits(cc.Codec.GZip.cpdext[j] - 8) << 8);
                    } else {
                        dist = this.readBits(cc.Codec.GZip.cpdext[j]);
                    }
                    dist += cc.Codec.GZip.cpdist[j];
                    while (len--) {
                        var c = this.buf32k[(this.bIdx - dist) & 0x7fff];
                        this.addBuffer(c);
                    }
                } else {
                    this.addBuffer(j);
                }
            } // while
        }
    } while (!last);
    this.flushBuffer();

    this.byteAlign();
    return 0;
};

cc.Codec.GZip.prototype.unzipFile = function (name) {
    var i;
    this.gunzip();
    for (i = 0; i < this.unzipped.length; i++) {
        if (this.unzipped[i][1] === name) {
            return this.unzipped[i][0];
        }
    }
};

cc.Codec.GZip.prototype.nextFile = function () {
    // if (this.debug) alert("NEXTFILE");

    this.outputArr = [];
    this.modeZIP = false;

    var tmp = [];
    tmp[0] = this.readByte();
    tmp[1] = this.readByte();
    // if (this.debug) alert("type: "+tmp[0]+" "+tmp[1]);

    if (tmp[0] === 0x78 && tmp[1] === 0xda) { //GZIP
        // if (this.debug) alert("GEONExT-GZIP");
        this.DeflateLoop();
        // if (this.debug) alert(this.outputArr.join(''));
        this.unzipped[this.files] = [this.outputArr.join(''), "geonext.gxt"];
        this.files++;
    }
    if (tmp[0] === 0x1f && tmp[1] === 0x8b) { //GZIP
        // if (this.debug) alert("GZIP");
        this.skipdir();
        // if (this.debug) alert(this.outputArr.join(''));
        this.unzipped[this.files] = [this.outputArr.join(''), "file"];
        this.files++;
    }
    if (tmp[0] === 0x50 && tmp[1] === 0x4b) { //ZIP
        this.modeZIP = true;
        tmp[2] = this.readByte();
        tmp[3] = this.readByte();
        if (tmp[2] === 0x03 && tmp[3] === 0x04) {
            //MODE_ZIP
            tmp[0] = this.readByte();
            tmp[1] = this.readByte();
            // if (this.debug) alert("ZIP-Version: "+tmp[1]+" "+tmp[0]/10+"."+tmp[0]%10);

            this.gpflags = this.readByte();
            this.gpflags |= (this.readByte() << 8);
            // if (this.debug) alert("gpflags: "+this.gpflags);

            var method = this.readByte();
            method |= (this.readByte() << 8);
            // if (this.debug) alert("method: "+method);

            this.readByte();
            this.readByte();
            this.readByte();
            this.readByte();

//       var crc = this.readByte();
//       crc |= (this.readByte()<<8);
//       crc |= (this.readByte()<<16);
//       crc |= (this.readByte()<<24);

            var compSize = this.readByte();
            compSize |= (this.readByte() << 8);
            compSize |= (this.readByte() << 16);
            compSize |= (this.readByte() << 24);

            var size = this.readByte();
            size |= (this.readByte() << 8);
            size |= (this.readByte() << 16);
            size |= (this.readByte() << 24);

            // if (this.debug) alert("local CRC: "+crc+"\nlocal Size: "+size+"\nlocal CompSize: "+compSize);

            var filelen = this.readByte();
            filelen |= (this.readByte() << 8);

            var extralen = this.readByte();
            extralen |= (this.readByte() << 8);

            // if (this.debug) alert("filelen "+filelen);
            i = 0;
            this.nameBuf = [];
            while (filelen--) {
                var c = this.readByte();
                if (c === "/" | c === ":") {
                    i = 0;
                } else if (i < cc.Codec.GZip.NAMEMAX - 1) {
                    this.nameBuf[i++] = String.fromCharCode(c);
                }
            }
            // if (this.debug) alert("nameBuf: "+this.nameBuf);

            if (!this.fileout) this.fileout = this.nameBuf;

            var i = 0;
            while (i < extralen) {
                c = this.readByte();
                i++;
            }

            // if (size = 0 && this.fileOut.charAt(this.fileout.length-1)=="/"){
            //   //skipdir
            //   // if (this.debug) alert("skipdir");
            // }
            if (method === 8) {
                this.DeflateLoop();
                // if (this.debug) alert(this.outputArr.join(''));
                this.unzipped[this.files] = [this.outputArr.join(''), this.nameBuf.join('')];
                this.files++;
            }
            this.skipdir();
        }
    }
};

cc.Codec.GZip.prototype.skipdir = function () {
    var tmp = [];
    var compSize, size, os, i, c;

    if ((this.gpflags & 8)) {
        tmp[0] = this.readByte();
        tmp[1] = this.readByte();
        tmp[2] = this.readByte();
        tmp[3] = this.readByte();

//     if (tmp[0] == 0x50 && tmp[1] == 0x4b && tmp[2] == 0x07 && tmp[3] == 0x08) {
//       crc = this.readByte();
//       crc |= (this.readByte()<<8);
//       crc |= (this.readByte()<<16);
//       crc |= (this.readByte()<<24);
//     } else {
//       crc = tmp[0] | (tmp[1]<<8) | (tmp[2]<<16) | (tmp[3]<<24);
//     }

        compSize = this.readByte();
        compSize |= (this.readByte() << 8);
        compSize |= (this.readByte() << 16);
        compSize |= (this.readByte() << 24);

        size = this.readByte();
        size |= (this.readByte() << 8);
        size |= (this.readByte() << 16);
        size |= (this.readByte() << 24);
    }

    if (this.modeZIP) this.nextFile();

    tmp[0] = this.readByte();
    if (tmp[0] !== 8) {
        // if (this.debug) alert("Unknown compression method!");
        return 0;
    }

    this.gpflags = this.readByte();
    // if (this.debug && (this.gpflags & ~(0x1f))) alert("Unknown flags set!");

    this.readByte();
    this.readByte();
    this.readByte();
    this.readByte();

    this.readByte();
    os = this.readByte();

    if ((this.gpflags & 4)) {
        tmp[0] = this.readByte();
        tmp[2] = this.readByte();
        this.len = tmp[0] + 256 * tmp[1];
        // if (this.debug) alert("Extra field size: "+this.len);
        for (i = 0; i < this.len; i++)
            this.readByte();
    }

    if ((this.gpflags & 8)) {
        i = 0;
        this.nameBuf = [];
        while (c = this.readByte()) {
            if (c === "7" || c === ":")
                i = 0;
            if (i < cc.Codec.GZip.NAMEMAX - 1)
                this.nameBuf[i++] = c;
        }
        //this.nameBuf[i] = "\0";
        // if (this.debug) alert("original file name: "+this.nameBuf);
    }

    if ((this.gpflags & 16)) {
        while (c = this.readByte()) { // FIXME: looks like they read to the end of the stream, should be doable more efficiently
            //FILE COMMENT
        }
    }

    if ((this.gpflags & 2)) {
        this.readByte();
        this.readByte();
    }

    this.DeflateLoop();

//   crc = this.readByte();
//   crc |= (this.readByte()<<8);
//   crc |= (this.readByte()<<16);
//   crc |= (this.readByte()<<24);

    size = this.readByte();
    size |= (this.readByte() << 8);
    size |= (this.readByte() << 16);
    size |= (this.readByte() << 24);

    if (this.modeZIP) this.nextFile();
};
