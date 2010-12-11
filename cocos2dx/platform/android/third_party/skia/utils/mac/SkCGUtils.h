#ifndef SkCGUtils_DEFINED
#define SkCGUtils_DEFINED

#include <Carbon/Carbon.h>

class SkBitmap;

CGImageRef SkCreateCGImageRef(const SkBitmap&);

#endif
