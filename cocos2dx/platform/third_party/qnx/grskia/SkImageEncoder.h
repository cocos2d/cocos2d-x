#ifndef SkImageEncoder_DEFINED
#define SkImageEncoder_DEFINED

#include "SkTypes.h"

class SkBitmap;
class SkWStream;

class SkImageEncoder {
public:
    enum Type {
        kJPEG_Type,
        kPNG_Type
    };
    static SkImageEncoder* Create(Type);

    virtual ~SkImageEncoder();
    
    /*  Quality ranges from 0..100 */
    enum {
        kDefaultQuality = 80
    };

    bool encodeFile(const char file[], const SkBitmap&, int quality);
    bool encodeStream(SkWStream*, const SkBitmap&, int quality);

    static bool EncodeFile(const char file[], const SkBitmap&, Type,
                           int quality);
    static bool EncodeStream(SkWStream*, const SkBitmap&, Type,
                           int quality);

protected:
    virtual bool onEncode(SkWStream*, const SkBitmap&, int quality) = 0;
};

#endif
