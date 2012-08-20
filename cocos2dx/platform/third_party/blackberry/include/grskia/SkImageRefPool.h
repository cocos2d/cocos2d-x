#ifndef SkImageRefPool_DEFINED
#define SkImageRefPool_DEFINED

#include "SkTypes.h"

class SkImageRef;
class SkImageRef_GlobalPool;

class SkImageRefPool {
public:
    SkImageRefPool();
    ~SkImageRefPool();
    
    size_t  getRAMBudget() const { return fRAMBudget; }
    void    setRAMBudget(size_t);
    
    size_t  getRAMUsed() const { return fRAMUsed; }
    void    setRAMUsed(size_t limit);
    
    void addToHead(SkImageRef*);
    void addToTail(SkImageRef*);
    void detach(SkImageRef*);

    void dump() const;
    
private:
    size_t fRAMBudget;
    size_t fRAMUsed;
    
    int         fCount;
    SkImageRef* fHead, *fTail;
    
    int computeCount() const;
    
    friend class SkImageRef_GlobalPool;
    
    void justAddedPixels(SkImageRef*);
    void canLosePixels(SkImageRef*);
    void purgeIfNeeded();
};

#endif

