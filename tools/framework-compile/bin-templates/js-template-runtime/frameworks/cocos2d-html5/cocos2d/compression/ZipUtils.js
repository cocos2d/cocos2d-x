/*--
 Copyright 2009-2010 by Stefan Rusterholz.
 All rights reserved.
 You can choose between MIT and BSD-3-Clause license. License file will be added later.
 --*/

/**
 * mixin cc.Codec
 */
cc.Codec = {name:'Jacob__Codec'};

/**
 * Unpack a gzipped byte array
 * @param {Array} input Byte array
 * @returns {String} Unpacked byte string
 */
cc.unzip = function () {
    return cc.Codec.GZip.gunzip.apply(cc.Codec.GZip, arguments);
};

/**
 * Unpack a gzipped byte string encoded as base64
 * @param {String} input Byte string encoded as base64
 * @returns {String} Unpacked byte string
 */
cc.unzipBase64 = function () {
    var tmpInput = cc.Codec.Base64.decode.apply(cc.Codec.Base64, arguments);
    return   cc.Codec.GZip.gunzip.apply(cc.Codec.GZip, [tmpInput]);
};

/**
 * Unpack a gzipped byte string encoded as base64
 * @param {String} input Byte string encoded as base64
 * @param {Number} bytes Bytes per array item
 * @returns {Array} Unpacked byte array
 */
cc.unzipBase64AsArray = function (input, bytes) {
    bytes = bytes || 1;

    var dec = this.unzipBase64(input),
        ar = [], i, j, len;
    for (i = 0, len = dec.length / bytes; i < len; i++) {
        ar[i] = 0;
        for (j = bytes - 1; j >= 0; --j) {
            ar[i] += dec.charCodeAt((i * bytes) + j) << (j * 8);
        }
    }
    return ar;
};

/**
 * Unpack a gzipped byte array
 * @param {Array} input Byte array
 * @param {Number} bytes Bytes per array item
 * @returns {Array} Unpacked byte array
 */
cc.unzipAsArray = function (input, bytes) {
    bytes = bytes || 1;

    var dec = this.unzip(input),
        ar = [], i, j, len;
    for (i = 0, len = dec.length / bytes; i < len; i++) {
        ar[i] = 0;
        for (j = bytes - 1; j >= 0; --j) {
            ar[i] += dec.charCodeAt((i * bytes) + j) << (j * 8);
        }
    }
    return ar;
};

/**
 * string to array
 * @param {String} input
 * @returns {Array} array
 */
cc.StringToArray = function (input) {
    var tmp = input.split(","), ar = [], i;
    for (i = 0; i < tmp.length; i++) {
        ar.push(parseInt(tmp[i]));
    }
    return ar;
};
