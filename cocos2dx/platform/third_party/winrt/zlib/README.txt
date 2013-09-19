Add the contents of the downloaded zlib-1.2.5 folder to the directory zlib-1.2.5

http://sourceforge.net/projects/libpng/files/zlib/1.2.5/zlib125.zip/download

Note: VS2013 may have a problem building the ARM version of zlib. If you get an internal compiler error, make the following change to zutil.c

voidpf ZLIB_INTERNAL zcalloc (opaque, items, size)
    voidpf opaque;
    unsigned items;
    unsigned size;
{
    unsigned numBytes;

    if (opaque) items += size - size; /* make compiler happy */
    numBytes = items * size;
    return sizeof(uInt) > 2 ? (voidpf) malloc(numBytes) :
                              (voidpf)calloc(items, size);
}