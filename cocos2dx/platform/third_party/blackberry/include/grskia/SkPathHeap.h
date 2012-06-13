#ifndef SkPathHeap_DEFINED
#define SkPathHeap_DEFINED

#include "SkRefCnt.h"
#include "SkChunkAlloc.h"
#include "SkTDArray.h"

class SkPath;
class SkFlattenableReadBuffer;
class SkFlattenableWriteBuffer;

class SkPathHeap : public SkRefCnt {
public:
            SkPathHeap();
            SkPathHeap(SkFlattenableReadBuffer&);
    virtual ~SkPathHeap();

    /** Copy the path into the heap, and return the new total number of paths.
        Thus, the returned value will be index+1, where index is the index of
        this newly added (copied) path.
     */
    int append(const SkPath&);
    
    // called during picture-playback
    int count() const { return fPaths.count(); }
    const SkPath& operator[](int index) const {
        return *fPaths[index];
    }
    
    void flatten(SkFlattenableWriteBuffer&) const;
        
private:
    // we store the paths in the heap (placement new)
    SkChunkAlloc        fHeap;
    // we just store ptrs into fHeap here
    SkTDArray<SkPath*>  fPaths;
};

#endif

