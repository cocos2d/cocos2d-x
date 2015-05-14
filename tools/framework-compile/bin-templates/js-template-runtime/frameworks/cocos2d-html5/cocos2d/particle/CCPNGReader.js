/****************************************************************************
 Copyright (c) 2011 Devon Govett
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org


 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/**
 * A png file reader
 * @name cc.tiffReader
 */
cc.PNGReader = cc.Class.extend({
    ctor:function(data){
        var chunkSize, colors, delayDen, delayNum, frame, i, index, key, section, ccshort, text, _i, _j, _ref;
        this.data = data;
        this.pos = 8;
        this.palette = [];
        this.imgData = [];
        this.transparency = {};
        this.animation = null;
        this.text = {};
        frame = null;
        while (true) {
            chunkSize = this.readUInt32();
            section = ((function() {
                var _i, _results;
                _results = [];
                for (i = _i = 0; _i < 4; i = ++_i) {
                    _results.push(String.fromCharCode(this.data[this.pos++]));
                }
                return _results;
            }).call(this)).join('');
            switch (section) {
                case 'IHDR':
                    this.width = this.readUInt32();
                    this.height = this.readUInt32();
                    this.bits = this.data[this.pos++];
                    this.colorType = this.data[this.pos++];
                    this.compressionMethod = this.data[this.pos++];
                    this.filterMethod = this.data[this.pos++];
                    this.interlaceMethod = this.data[this.pos++];
                    break;
                case 'acTL':
                    this.animation = {
                        numFrames: this.readUInt32(),
                        numPlays: this.readUInt32() || Infinity,
                        frames: []
                    };
                    break;
                case 'PLTE':
                    this.palette = this.read(chunkSize);
                    break;
                case 'fcTL':
                    if (frame) {
                        this.animation.frames.push(frame);
                    }
                    this.pos += 4;
                    frame = {
                        width: this.readUInt32(),
                        height: this.readUInt32(),
                        xOffset: this.readUInt32(),
                        yOffset: this.readUInt32()
                    };
                    delayNum = this.readUInt16();
                    delayDen = this.readUInt16() || 100;
                    frame.delay = 1000 * delayNum / delayDen;
                    frame.disposeOp = this.data[this.pos++];
                    frame.blendOp = this.data[this.pos++];
                    frame.data = [];
                    break;
                case 'IDAT':
                case 'fdAT':
                    if (section === 'fdAT') {
                        this.pos += 4;
                        chunkSize -= 4;
                    }
                    data = (frame != null ? frame.data : void 0) || this.imgData;
                    for (i = _i = 0; 0 <= chunkSize ? _i < chunkSize : _i > chunkSize; i = 0 <= chunkSize ? ++_i : --_i) {
                        data.push(this.data[this.pos++]);
                    }
                    break;
                case 'tRNS':
                    this.transparency = {};
                    switch (this.colorType) {
                        case 3:
                            this.transparency.indexed = this.read(chunkSize);
                            ccshort = 255 - this.transparency.indexed.length;
                            if (ccshort > 0) {
                                for (i = _j = 0; 0 <= ccshort ? _j < ccshort : _j > ccshort; i = 0 <= ccshort ? ++_j : --_j) {
                                    this.transparency.indexed.push(255);
                                }
                            }
                            break;
                        case 0:
                            this.transparency.grayscale = this.read(chunkSize)[0];
                            break;
                        case 2:
                            this.transparency.rgb = this.read(chunkSize);
                    }
                    break;
                case 'tEXt':
                    text = this.read(chunkSize);
                    index = text.indexOf(0);
                    key = String.fromCharCode.apply(String, text.slice(0, index));
                    this.text[key] = String.fromCharCode.apply(String, text.slice(index + 1));
                    break;
                case 'IEND':
                    if (frame) {
                        this.animation.frames.push(frame);
                    }
                    this.colors = (function() {
                        switch (this.colorType) {
                            case 0:
                            case 3:
                            case 4:
                                return 1;
                            case 2:
                            case 6:
                                return 3;
                        }
                    }).call(this);
                    this.hasAlphaChannel = (_ref = this.colorType) === 4 || _ref === 6;
                    colors = this.colors + (this.hasAlphaChannel ? 1 : 0);
                    this.pixelBitlength = this.bits * colors;
                    this.colorSpace = (function() {
                        switch (this.colors) {
                            case 1:
                                return 'DeviceGray';
                            case 3:
                                return 'DeviceRGB';
                        }
                    }).call(this);
                    if(Uint8Array != Array)
                        this.imgData = new Uint8Array(this.imgData);
                    return;
                default:
                    this.pos += chunkSize;
            }
            this.pos += 4;
            if (this.pos > this.data.length) {
                throw new Error("Incomplete or corrupt PNG file");
            }
        }
    },
    read:function(bytes){
        var i, _i, _results;
        _results = [];
        for (i = _i = 0; 0 <= bytes ? _i < bytes : _i > bytes; i = 0 <= bytes ? ++_i : --_i) {
            _results.push(this.data[this.pos++]);
        }
        return _results;
    },
    readUInt32:function(){
        var b1, b2, b3, b4;
        b1 = this.data[this.pos++] << 24;
        b2 = this.data[this.pos++] << 16;
        b3 = this.data[this.pos++] << 8;
        b4 = this.data[this.pos++];
        return b1 | b2 | b3 | b4;
    },
    readUInt16:function(){
        var b1, b2;
        b1 = this.data[this.pos++] << 8;
        b2 = this.data[this.pos++];
        return b1 | b2;
    },
    decodePixels:function(data){
        var ccbyte, c, col, i, left, length, p, pa, paeth, pb, pc, pixelBytes, pixels, pos, row, scanlineLength, upper, upperLeft, _i, _j, _k, _l, _m;
        if (data == null) {
            data = this.imgData;
        }
        if (data.length === 0) {
            return new Uint8Array(0);
        }
        var inflate = new Zlib.Inflate(data,{index:0, verify:false});
        data = inflate.decompress();

        pixelBytes = this.pixelBitlength / 8;
        scanlineLength = pixelBytes * this.width;
        pixels = new Uint8Array(scanlineLength * this.height);
        length = data.length;
        row = 0;
        pos = 0;
        c = 0;
        while (pos < length) {
            switch (data[pos++]) {
                case 0:
                    for (i = _i = 0; _i < scanlineLength; i = _i += 1) {
                        pixels[c++] = data[pos++];
                    }
                    break;
                case 1:
                    for (i = _j = 0; _j < scanlineLength; i = _j += 1) {
                        ccbyte = data[pos++];
                        left = i < pixelBytes ? 0 : pixels[c - pixelBytes];
                        pixels[c++] = (ccbyte + left) % 256;
                    }
                    break;
                case 2:
                    for (i = _k = 0; _k < scanlineLength; i = _k += 1) {
                        ccbyte = data[pos++];
                        col = (i - (i % pixelBytes)) / pixelBytes;
                        upper = row && pixels[(row - 1) * scanlineLength + col * pixelBytes + (i % pixelBytes)];
                        pixels[c++] = (upper + ccbyte) % 256;
                    }
                    break;
                case 3:
                    for (i = _l = 0; _l < scanlineLength; i = _l += 1) {
                        ccbyte = data[pos++];
                        col = (i - (i % pixelBytes)) / pixelBytes;
                        left = i < pixelBytes ? 0 : pixels[c - pixelBytes];
                        upper = row && pixels[(row - 1) * scanlineLength + col * pixelBytes + (i % pixelBytes)];
                        pixels[c++] = (ccbyte + Math.floor((left + upper) / 2)) % 256;
                    }
                    break;
                case 4:
                    for (i = _m = 0; _m < scanlineLength; i = _m += 1) {
                        ccbyte = data[pos++];
                        col = (i - (i % pixelBytes)) / pixelBytes;
                        left = i < pixelBytes ? 0 : pixels[c - pixelBytes];
                        if (row === 0) {
                            upper = upperLeft = 0;
                        } else {
                            upper = pixels[(row - 1) * scanlineLength + col * pixelBytes + (i % pixelBytes)];
                            upperLeft = col && pixels[(row - 1) * scanlineLength + (col - 1) * pixelBytes + (i % pixelBytes)];
                        }
                        p = left + upper - upperLeft;
                        pa = Math.abs(p - left);
                        pb = Math.abs(p - upper);
                        pc = Math.abs(p - upperLeft);
                        if (pa <= pb && pa <= pc) {
                            paeth = left;
                        } else if (pb <= pc) {
                            paeth = upper;
                        } else {
                            paeth = upperLeft;
                        }
                        pixels[c++] = (ccbyte + paeth) % 256;
                    }
                    break;
                default:
                    throw new Error("Invalid filter algorithm: " + data[pos - 1]);
            }
            row++;
        }
        return pixels;
    },
    copyToImageData:function(imageData,pixels){
        var alpha, colors, data, i, input, j, k, length, palette, v, _ref;
        colors = this.colors;
        palette = null;
        alpha = this.hasAlphaChannel;
        if (this.palette.length) {
            palette = (_ref = this._decodedPalette) != null ? _ref : this._decodedPalette = this.decodePalette();
            colors = 4;
            alpha = true;
        }
        data = imageData.data || imageData;
        length = data.length;
        input = palette || pixels;
        i = j = 0;
        if (colors === 1) {
            while (i < length) {
                k = palette ? pixels[i / 4] * 4 : j;
                v = input[k++];
                data[i++] = v;
                data[i++] = v;
                data[i++] = v;
                data[i++] = alpha ? input[k++] : 255;
                j = k;
            }
        } else {
            while (i < length) {
                k = palette ? pixels[i / 4] * 4 : j;
                data[i++] = input[k++];
                data[i++] = input[k++];
                data[i++] = input[k++];
                data[i++] = alpha ? input[k++] : 255;
                j = k;
            }
        }
    },
    decodePalette:function(){
        var c, i, palette, pos, ret, transparency, _i, _ref, _ref1;
        palette = this.palette;
        transparency = this.transparency.indexed || [];
        ret = new Uint8Array((transparency.length || 0) + palette.length);
        pos = 0;
        c = 0;
        for (i = _i = 0, _ref = palette.length; _i < _ref; i = _i += 3) {
            ret[pos++] = palette[i];
            ret[pos++] = palette[i + 1];
            ret[pos++] = palette[i + 2];
            ret[pos++] = (_ref1 = transparency[c++]) != null ? _ref1 : 255;
        }
        return ret;
    },
    render: function (canvas) {
        var ctx, data;
        canvas.width = this.width;
        canvas.height = this.height;
        ctx = canvas.getContext("2d");
        data = ctx.createImageData(this.width, this.height);
        this.copyToImageData(data, this.decodePixels());
        return ctx.putImageData(data, 0, 0);

    }
});

