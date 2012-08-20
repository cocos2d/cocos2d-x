#ifndef skiagm_DEFINED
#define skiagm_DEFINED

#include "SkCanvas.h"
#include "SkPaint.h"
#include "SkRefCnt.h"
#include "SkSize.h"
#include "SkString.h"
#include "SkTRegistry.h"

namespace skiagm {
	
	static inline SkISize make_isize(int w, int h) {
		SkISize sz;
		sz.set(w, h);
		return sz;
	}

    class GM {
    public:
        GM();
        virtual ~GM();
		
		void draw(SkCanvas*);
		SkISize getISize() { return this->onISize(); }
        const char* shortName() {
            if (fShortName.size() == 0) {
                fShortName = this->onShortName();
            }
            return fShortName.c_str();
        }

	protected:
		virtual void onDraw(SkCanvas*) = 0;
		virtual SkISize onISize() = 0;
        virtual SkString onShortName() = 0;
        
    private:
        SkString fShortName;
    };

    typedef SkTRegistry<GM*, void*> GMRegistry;
}

#endif
