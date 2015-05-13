//"use strict";

// Implementation details for the 'runtime environment' we generate in
// JavaScript. The Runtime object itself is used both during compilation,
// and is available at runtime (dynamic compilation). The RuntimeGenerator
// helps to create the Runtime object (written so that the Runtime object
// itself is as optimized as possible - no unneeded runtime checks).

var RuntimeGenerator = {
  alloc: function(size, type, init, sep, ignoreAlign) {
    sep = sep || ';';
    var ret = type + 'TOP';
    if (init) {
      ret += sep + '_memset(' + type + 'TOP, 0, ' + size + ')';
    }
    ret += sep + type + 'TOP = (' + type + 'TOP + ' + size + ')|0';
    if ({{{ STACK_ALIGN }}} > 1 && !ignoreAlign) {
      ret += sep + RuntimeGenerator.alignMemory(type + 'TOP', {{{ STACK_ALIGN }}});
    }
    return ret;
  },

  // An allocation that lives as long as the current function call
  stackAlloc: function(size, sep) {
    sep = sep || ';';
    var ret = RuntimeGenerator.alloc(size, 'STACK', false, sep, USE_TYPED_ARRAYS != 2 || (isNumber(size) && parseInt(size) % {{{ STACK_ALIGN }}} == 0));
    if (ASSERTIONS) {
      ret += sep + 'assert(' + asmCoercion('(STACKTOP|0) < (STACK_MAX|0)', 'i32') + ')';
    }
    return ret;
  },

  stackEnter: function(initial, force) {
    if (initial === 0 && SKIP_STACK_IN_SMALL && !force) return '';
    var ret = 'var __stackBase__  = ' + (ASM_JS ? '0; __stackBase__ = ' : '') + 'STACKTOP';
    if (initial > 0) ret += '; STACKTOP = (STACKTOP + ' + initial + ')|0';
    if (USE_TYPED_ARRAYS == 2) {
      assert(initial % Runtime.STACK_ALIGN == 0);
      if (ASSERTIONS && Runtime.STACK_ALIGN == 4) {
        ret += '; assert(' + asmCoercion('!(STACKTOP&3)', 'i32') + ')';
      }
    }
    if (ASSERTIONS) {
      ret += '; assert(' + asmCoercion('(STACKTOP|0) < (STACK_MAX|0)', 'i32') + ')';
    }
    if (false) {
      ret += '; _memset(' + asmCoercion('__stackBase__', 'i32') + ', 0, ' + initial + ')';
    }
    return ret;
  },

  stackExit: function(initial, force) {
    if (initial === 0 && SKIP_STACK_IN_SMALL && !force) return '';
    var ret = '';
    if (SAFE_HEAP) {
      ret += 'var i = __stackBase__; while ((i|0) < (STACKTOP|0)) { SAFE_HEAP_CLEAR(i|0); i = (i+1)|0 }';
    }
    return ret += 'STACKTOP = __stackBase__';
  },

  // An allocation that cannot normally be free'd (except through sbrk, which once
  // called, takes control of STATICTOP)
  staticAlloc: function(size) {
    if (ASSERTIONS) size = '(assert(!staticSealed),' + size + ')'; // static area must not be sealed
    var ret = RuntimeGenerator.alloc(size, 'STATIC', INIT_HEAP);
    return ret;
  },

  // allocation on the top of memory, adjusted dynamically by sbrk
  dynamicAlloc: function(size) {
    if (ASSERTIONS) size = '(assert(DYNAMICTOP > 0),' + size + ')'; // dynamic area must be ready
    var ret = RuntimeGenerator.alloc(size, 'DYNAMIC', INIT_HEAP);
    if (USE_TYPED_ARRAYS) ret += '; if (DYNAMICTOP >= TOTAL_MEMORY) enlargeMemory();'
    return ret;
  },

  alignMemory: function(target, quantum) {
    if (typeof quantum !== 'number') {
      quantum = '(quantum ? quantum : {{{ STACK_ALIGN }}})';
    }
    return target + ' = ' + Runtime.forceAlign(target, quantum);
  },

  // Given two 32-bit unsigned parts of an emulated 64-bit number, combine them into a JS number (double).
  // Rounding is inevitable if the number is large. This is a particular problem for small negative numbers
  // (-1 will be rounded!), so handle negatives separately and carefully
  makeBigInt: function(low, high, unsigned) {
    var unsignedRet = '(' + asmCoercion(makeSignOp(low, 'i32', 'un', 1, 1), 'float') + '+(' + asmCoercion(makeSignOp(high, 'i32', 'un', 1, 1), 'float') + '*' + asmEnsureFloat(4294967296, 'float') + '))';
    var signedRet = '(' + asmCoercion(makeSignOp(low, 'i32', 'un', 1, 1), 'float') + '+(' + asmCoercion(makeSignOp(high, 'i32', 're', 1, 1), 'float') + '*' + asmEnsureFloat(4294967296, 'float') + '))';
    if (typeof unsigned === 'string') return '(' + unsigned + ' ? ' + unsignedRet + ' : ' + signedRet + ')';
    return unsigned ? unsignedRet : signedRet;
  }
};

function unInline(name_, params) {
  var src = '(function(' + params + ') { var ret = ' + RuntimeGenerator[name_].apply(null, params) + '; return ret; })';
  var ret = eval(src);
  return ret;
}

var Runtime = {
  stackSave: function() {
    return STACKTOP;
  },
  stackRestore: function(stackTop) {
    STACKTOP = stackTop;
  },

  forceAlign: function(target, quantum) {
    quantum = quantum || {{{ QUANTUM_SIZE }}};
    if (quantum == 1) return target;
    if (isNumber(target) && isNumber(quantum)) {
      return Math.ceil(target/quantum)*quantum;
    } else if (isNumber(quantum) && isPowerOfTwo(quantum)) {
      var logg = log2(quantum);
      return '((((' +target + ')+' + (quantum-1) + ')>>' + logg + ')<<' + logg + ')';
    }
    return 'Math.ceil((' + target + ')/' + quantum + ')*' + quantum;
  },

  isNumberType: function(type) {
    return type in Runtime.INT_TYPES || type in Runtime.FLOAT_TYPES;
  },

  isPointerType: isPointerType,
  isStructType: isStructType,

  INT_TYPES: set('i1', 'i8', 'i16', 'i32', 'i64'),
  FLOAT_TYPES: set('float', 'double'),

  // Imprecise bitops utilities
  or64: function(x, y) {
    var l = (x | 0) | (y | 0);
    var h = (Math.round(x / 4294967296) | Math.round(y / 4294967296)) * 4294967296;
    return l + h;
  },
  and64: function(x, y) {
    var l = (x | 0) & (y | 0);
    var h = (Math.round(x / 4294967296) & Math.round(y / 4294967296)) * 4294967296;
    return l + h;
  },
  xor64: function(x, y) {
    var l = (x | 0) ^ (y | 0);
    var h = (Math.round(x / 4294967296) ^ Math.round(y / 4294967296)) * 4294967296;
    return l + h;
  },

  //! Returns the size of a type, as C/C++ would have it (in 32-bit, for now), in bytes.
  //! @param type The type, by name.
  getNativeTypeSize: function(type, quantumSize) {
    if (Runtime.QUANTUM_SIZE == 1) return 1;
    var size = {
      '%i1': 1,
      '%i8': 1,
      '%i16': 2,
      '%i32': 4,
      '%i64': 8,
      "%float": 4,
      "%double": 8
    }['%'+type]; // add '%' since float and double confuse Closure compiler as keys, and also spidermonkey as a compiler will remove 's from '_i8' etc
    if (!size) {
      if (type.charAt(type.length-1) == '*') {
        size = Runtime.QUANTUM_SIZE; // A pointer
      } else if (type[0] == 'i') {
        var bits = parseInt(type.substr(1));
        assert(bits % 8 == 0);
        size = bits/8;
      }
    }
    return size;
  },

  //! Returns the size of a structure field, as C/C++ would have it (in 32-bit,
  //! for now).
  //! @param type The type, by name.
  getNativeFieldSize: function(type) {
    return Math.max(Runtime.getNativeTypeSize(type), Runtime.QUANTUM_SIZE);
  },

  dedup: dedup,

  set: set,

  STACK_ALIGN: {{{ STACK_ALIGN }}},

  // type can be a native type or a struct (or null, for structs we only look at size here)
  getAlignSize: function(type, size, vararg) {
    // we align i64s and doubles on 64-bit boundaries, unlike x86
#if TARGET_LE32
    if (type == 'i64' || type == 'double' || vararg) return 8;
    if (!type) return Math.min(size, 8); // align structures internally to 64 bits
#endif
    return Math.min(size || (type ? Runtime.getNativeFieldSize(type) : 0), Runtime.QUANTUM_SIZE);
  },

  // Calculate aligned size, just like C structs should be. TODO: Consider
  // requesting that compilation be done with #pragma pack(push) /n #pragma pack(1),
  // which would remove much of the complexity here.
  calculateStructAlignment: function calculateStructAlignment(type) {
    type.flatSize = 0;
    type.alignSize = 0;
    var diffs = [];
    var prev = -1;
    type.flatIndexes = type.fields.map(function(field) {
      var size, alignSize;
      if (Runtime.isNumberType(field) || Runtime.isPointerType(field)) {
        size = Runtime.getNativeTypeSize(field); // pack char; char; in structs, also char[X]s.
        alignSize = Runtime.getAlignSize(field, size);
      } else if (Runtime.isStructType(field)) {
        size = Types.types[field].flatSize;
        alignSize = Runtime.getAlignSize(null, Types.types[field].alignSize);
      } else if (field[0] == 'b') {
        // bN, large number field, like a [N x i8]
        size = field.substr(1)|0;
        alignSize = 1;
      } else {
        throw 'Unclear type in struct: ' + field + ', in ' + type.name_ + ' :: ' + dump(Types.types[type.name_]);
      }
      if (type.packed) alignSize = 1;
      type.alignSize = Math.max(type.alignSize, alignSize);
      var curr = Runtime.alignMemory(type.flatSize, alignSize); // if necessary, place this on aligned memory
      type.flatSize = curr + size;
      if (prev >= 0) {
        diffs.push(curr-prev);
      }
      prev = curr;
      return curr;
    });
    type.flatSize = Runtime.alignMemory(type.flatSize, type.alignSize);
    if (diffs.length == 0) {
      type.flatFactor = type.flatSize;
    } else if (Runtime.dedup(diffs).length == 1) {
      type.flatFactor = diffs[0];
    }
    type.needsFlattening = (type.flatFactor != 1);
    return type.flatIndexes;
  },

  // Given details about a structure, returns its alignment. For example,
  // generateStructInfo(
  //    [
  //      ['i32', 'field1'],
  //      ['i8', 'field2']
  //    ]
  // ) will return
  //    { field1: 0, field2: 4 } (depending on QUANTUM_SIZE)
  //
  // Instead of [type, name], you can also provide just [name]. In that case
  // it will use type information present in LLVM bitcode. (It is safer to
  // specify the type though, as it will then check the type.) You must then
  // also specify the second parameter to generateStructInfo, which is the
  // LLVM structure name.
  //
  // Note that LLVM optimizations can remove some of the debug info generated
  // by -g.
  //
  // Note that you will need the full %struct.* name here at compile time,
  // but not at runtime. The reason is that during compilation we cannot
  // simplify the type names yet. At runtime, you can provide either the short
  // or the full name.
  //
  // When providing a typeName, you can generate information for nested
  // structs, for example, struct = ['field1', { field2: ['sub1', 'sub2', 'sub3'] }, 'field3']
  // which represents a structure whose 2nd field is another structure.
  generateStructInfo: function(struct, typeName, offset) {
    var type, alignment;
    if (typeName) {
      offset = offset || 0;
      type = (typeof Types === 'undefined' ? Runtime.typeInfo : Types.types)[typeName];
      if (!type) return null;
      if (type.fields.length != struct.length) {
        printErr('Number of named fields must match the type for ' + typeName + ': possibly duplicate struct names. Cannot return structInfo');
        return null;
      }
      alignment = type.flatIndexes;
    } else {
      var type = { fields: struct.map(function(item) { return item[0] }) };
      alignment = Runtime.calculateStructAlignment(type);
    }
    var ret = {
      __size__: type.flatSize
    };
    if (typeName) {
      struct.forEach(function(item, i) {
        if (typeof item === 'string') {
          ret[item] = alignment[i] + offset;
        } else {
          // embedded struct
          var key;
          for (var k in item) key = k;
          ret[key] = Runtime.generateStructInfo(item[key], type.fields[i], alignment[i]);
        }
      });
    } else {
      struct.forEach(function(item, i) {
        ret[item[1]] = alignment[i];
      });
    }
    return ret;
  },

  dynCall: function(sig, ptr, args) {
    if (args && args.length) {
#if ASSERTIONS
      assert(args.length == sig.length-1);
#endif
#if ASM_JS
      if (!args.splice) args = Array.prototype.slice.call(args);
      args.splice(0, 0, ptr);
      return Module['dynCall_' + sig].apply(null, args);
#else
      return FUNCTION_TABLE[ptr].apply(null, args);
#endif
    } else {
#if ASSERTIONS
      assert(sig.length == 1);
#endif
#if ASM_JS
      return Module['dynCall_' + sig].call(null, ptr);
#else
      return FUNCTION_TABLE[ptr]();
#endif
    }
  },

#if ASM_JS
  functionPointers: new Array(RESERVED_FUNCTION_POINTERS),
#endif

  addFunction: function(func) {
#if ASM_JS
    for (var i = 0; i < Runtime.functionPointers.length; i++) {
      if (!Runtime.functionPointers[i]) {
        Runtime.functionPointers[i] = func;
        return 2 + 2*i;
      }
    }
    throw 'Finished up all reserved function pointers. Use a higher value for RESERVED_FUNCTION_POINTERS.';
#else
    var table = FUNCTION_TABLE;
    var ret = table.length;
    table.push(func);
    table.push(0);
    return ret;
#endif
  },

  removeFunction: function(index) {
#if ASM_JS
    Runtime.functionPointers[(index-2)/2] = null;
#else
    var table = FUNCTION_TABLE;
    table[index] = null;
#endif
  },

  warnOnce: function(text) {
    if (!Runtime.warnOnce.shown) Runtime.warnOnce.shown = {};
    if (!Runtime.warnOnce.shown[text]) {
      Runtime.warnOnce.shown[text] = 1;
      Module.printErr(text);
    }
  },

  funcWrappers: {},

  getFuncWrapper: function(func, sig) {
    assert(sig);
    if (!Runtime.funcWrappers[func]) {
      Runtime.funcWrappers[func] = function() {
        return Runtime.dynCall(sig, func, arguments);
      };
    }
    return Runtime.funcWrappers[func];
  },

  // Returns a processor of UTF.
  // processCChar() receives characters from a C-like UTF representation and returns JS string fragments.
  // processJSString() receives a JS string and returns a C-like UTF representation in an array
  UTF8Processor: function() {
    var buffer = [];
    var needed = 0;
    this.processCChar = function (code) {
      code = code & 0xff;
      if (needed) {
        buffer.push(code);
        needed--;
      }
      if (buffer.length == 0) {
        if (code < 128) return String.fromCharCode(code);
        buffer.push(code);
        if (code > 191 && code < 224) {
          needed = 1;
        } else {
          needed = 2;
        }
        return '';
      }
      if (needed > 0) return '';
      var c1 = buffer[0];
      var c2 = buffer[1];
      var c3 = buffer[2];
      var ret;
      if (c1 > 191 && c1 < 224) {
        ret = String.fromCharCode(((c1 & 31) << 6) | (c2 & 63));
      } else {
        ret = String.fromCharCode(((c1 & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
      }
      buffer.length = 0;
      return ret;
    }
    this.processJSString = function(string) {
      string = unescape(encodeURIComponent(string));
      var ret = [];
      for (var i = 0; i < string.length; i++) {
        ret.push(string.charCodeAt(i));
      }
      return ret;
    }
  },

#if RUNTIME_DEBUG
  debug: true, // Switch to false at runtime to disable logging at the right times

  printObjectList: [],

  prettyPrint: function(arg) {
    if (typeof arg == 'undefined') return '!UNDEFINED!';
    if (typeof arg == 'boolean') arg = arg + 0;
    if (!arg) return arg;
    var index = Runtime.printObjectList.indexOf(arg);
    if (index >= 0) return '<' + arg + '|' + index + '>';
    if (arg.toString() == '[object HTMLImageElement]') {
      return arg + '\n\n';
    }
    if (arg.byteLength) {
      return '{' + Array.prototype.slice.call(arg, 0, Math.min(arg.length, 400)) + '}'; // Useful for correct arrays, less so for compiled arrays, see the code below for that
      var buf = new ArrayBuffer(32);
      var i8buf = new Int8Array(buf);
      var i16buf = new Int16Array(buf);
      var f32buf = new Float32Array(buf);
      switch(arg.toString()) {
        case '[object Uint8Array]':
          i8buf.set(arg.subarray(0, 32));
          break;
        case '[object Float32Array]':
          f32buf.set(arg.subarray(0, 5));
          break;
        case '[object Uint16Array]':
          i16buf.set(arg.subarray(0, 16));
          break;
        default:
          alert('unknown array for debugging: ' + arg);
          throw 'see alert';
      }
      var ret = '{' + arg.byteLength + ':\n';
      var arr = Array.prototype.slice.call(i8buf);
      ret += 'i8:' + arr.toString().replace(/,/g, ',') + '\n';
      arr = Array.prototype.slice.call(f32buf, 0, 8);
      ret += 'f32:' + arr.toString().replace(/,/g, ',') + '}';
      return ret;
    }
    if (typeof arg == 'object') {
      Runtime.printObjectList.push(arg);
      return '<' + arg + '|' + (Runtime.printObjectList.length-1) + '>';
    }
    if (typeof arg == 'number') {
      if (arg > 0) return '0x' + arg.toString(16) + ' (' + arg + ')';
    }
    return arg;
  }
#endif
};

Runtime.stackAlloc = unInline('stackAlloc', ['size']);
Runtime.staticAlloc = unInline('staticAlloc', ['size']);
Runtime.dynamicAlloc = unInline('dynamicAlloc', ['size']);
Runtime.alignMemory = unInline('alignMemory', ['size', 'quantum']);
Runtime.makeBigInt = unInline('makeBigInt', ['low', 'high', 'unsigned']);

function getRuntime() {
  var ret = 'var Runtime = {\n';
  for (i in Runtime) {
    var item = Runtime[i];
    ret += '  ' + i + ': ';
    if (typeof item === 'function') {
      ret += item.toString();
    } else {
      ret += JSON.stringify(item);
    }
    ret += ',\n';
  }
  return ret + '  __dummy__: 0\n}\n';
}

// Additional runtime elements, that need preprocessing

// Converts a value we have as signed, into an unsigned value. For
// example, -1 in int32 would be a very large number as unsigned.
function unSign(value, bits, ignore, sig) {
  if (value >= 0) {
    return value;
  }
#if CHECK_SIGNS
  if (!ignore) throw 'UnSign';
#endif
  return bits <= 32 ? 2*Math.abs(1 << (bits-1)) + value // Need some trickery, since if bits == 32, we are right at the limit of the bits JS uses in bitshifts
                    : Math.pow(2, bits)         + value;
}

// Converts a value we have as unsigned, into a signed value. For
// example, 200 in a uint8 would be a negative number.
function reSign(value, bits, ignore, sig) {
  if (value <= 0) {
    return value;
  }
  var half = bits <= 32 ? Math.abs(1 << (bits-1)) // abs is needed if bits == 32
                        : Math.pow(2, bits-1);
#if CHECK_SIGNS
  var noted = false;
#endif
  if (value >= half && (bits <= 32 || value > half)) { // for huge values, we can hit the precision limit and always get true here. so don't do that
                                                       // but, in general there is no perfect solution here. With 64-bit ints, we get rounding and errors
                                                       // TODO: In i64 mode 1, resign the two parts separately and safely
#if CHECK_SIGNS
    if (!ignore) throw 'ReSign';
#endif
    value = -2*half + value; // Cannot bitshift half, as it may be at the limit of the bits JS uses in bitshifts
  }
#if CHECK_SIGNS
  // If this is a 32-bit value, then it should be corrected at this point. And,
  // without CHECK_SIGNS, we would just do the |0 shortcut, so check that that
  // would indeed give the exact same result.
  if (bits === 32 && (value|0) !== value && typeof value !== 'boolean') {
    if (!ignore) throw 'ReSign';
  }
#endif
  return value;
}

// The address globals begin at. Very low in memory, for code size and optimization opportunities.
// Above 0 is static memory, starting with globals.
// Then the stack.
// Then 'dynamic' memory for sbrk.
Runtime.GLOBAL_BASE = Runtime.alignMemory(1);

