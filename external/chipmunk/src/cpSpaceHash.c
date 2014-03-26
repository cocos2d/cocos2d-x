/* Copyright (c) 2007 Scott Lembcke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "chipmunk_private.h"
#include "prime.h"

typedef struct cpSpaceHashBin cpSpaceHashBin;
typedef struct cpHandle cpHandle;

struct cpSpaceHash {
	cpSpatialIndex spatialIndex;
	
	int numcells;
	cpFloat celldim;
	
	cpSpaceHashBin **table;
	cpHashSet *handleSet;
	
	cpSpaceHashBin *pooledBins;
	cpArray *pooledHandles;
	cpArray *allocatedBuffers;
	
	cpTimestamp stamp;
};


//MARK: Handle Functions

struct cpHandle {
	void *obj;
	int retain;
	cpTimestamp stamp;
};

static cpHandle*
cpHandleInit(cpHandle *hand, void *obj)
{
	hand->obj = obj;
	hand->retain = 0;
	hand->stamp = 0;
	
	return hand;
}

static inline void cpHandleRetain(cpHandle *hand){hand->retain++;}

static inline void
cpHandleRelease(cpHandle *hand, cpArray *pooledHandles)
{
	hand->retain--;
	if(hand->retain == 0) cpArrayPush(pooledHandles, hand);
}

static int handleSetEql(void *obj, cpHandle *hand){return (obj == hand->obj);}

static void *
handleSetTrans(void *obj, cpSpaceHash *hash)
{
	if(hash->pooledHandles->num == 0){
		// handle pool is exhausted, make more
		int count = CP_BUFFER_BYTES/sizeof(cpHandle);
		cpAssertHard(count, "Internal Error: Buffer size is too small.");
		
		cpHandle *buffer = (cpHandle *)cpcalloc(1, CP_BUFFER_BYTES);
		cpArrayPush(hash->allocatedBuffers, buffer);
		
		for(int i=0; i<count; i++) cpArrayPush(hash->pooledHandles, buffer + i);
	}
	
	cpHandle *hand = cpHandleInit((cpHandle *)cpArrayPop(hash->pooledHandles), obj);
	cpHandleRetain(hand);
	
	return hand;
}

//MARK: Bin Functions

struct cpSpaceHashBin {
	cpHandle *handle;
	cpSpaceHashBin *next;
};

static inline void
recycleBin(cpSpaceHash *hash, cpSpaceHashBin *bin)
{
	bin->next = hash->pooledBins;
	hash->pooledBins = bin;
}

static inline void
clearTableCell(cpSpaceHash *hash, int idx)
{
	cpSpaceHashBin *bin = hash->table[idx];
	while(bin){
		cpSpaceHashBin *next = bin->next;
		
		cpHandleRelease(bin->handle, hash->pooledHandles);
		recycleBin(hash, bin);
		
		bin = next;
	}
	
	hash->table[idx] = NULL;
}

static void
clearTable(cpSpaceHash *hash)
{
	for(int i=0; i<hash->numcells; i++) clearTableCell(hash, i);
}

// Get a recycled or new bin.
static inline cpSpaceHashBin *
getEmptyBin(cpSpaceHash *hash)
{
	cpSpaceHashBin *bin = hash->pooledBins;
	
	if(bin){
		hash->pooledBins = bin->next;
		return bin;
	} else {
		// Pool is exhausted, make more
		int count = CP_BUFFER_BYTES/sizeof(cpSpaceHashBin);
		cpAssertHard(count, "Internal Error: Buffer size is too small.");
		
		cpSpaceHashBin *buffer = (cpSpaceHashBin *)cpcalloc(1, CP_BUFFER_BYTES);
		cpArrayPush(hash->allocatedBuffers, buffer);
		
		// push all but the first one, return the first instead
		for(int i=1; i<count; i++) recycleBin(hash, buffer + i);
		return buffer;
	}
}

//MARK: Memory Management Functions

cpSpaceHash *
cpSpaceHashAlloc(void)
{
	return (cpSpaceHash *)cpcalloc(1, sizeof(cpSpaceHash));
}

// Frees the old table, and allocate a new one.
static void
cpSpaceHashAllocTable(cpSpaceHash *hash, int numcells)
{
	cpfree(hash->table);
	
	hash->numcells = numcells;
	hash->table = (cpSpaceHashBin **)cpcalloc(numcells, sizeof(cpSpaceHashBin *));
}

static inline cpSpatialIndexClass *Klass();

cpSpatialIndex *
cpSpaceHashInit(cpSpaceHash *hash, cpFloat celldim, int numcells, cpSpatialIndexBBFunc bbfunc, cpSpatialIndex *staticIndex)
{
	cpSpatialIndexInit((cpSpatialIndex *)hash, Klass(), bbfunc, staticIndex);
	
	cpSpaceHashAllocTable(hash, next_prime(numcells));
	hash->celldim = celldim;
	
	hash->handleSet = cpHashSetNew(0, (cpHashSetEqlFunc)handleSetEql);
	
	hash->pooledHandles = cpArrayNew(0);
	
	hash->pooledBins = NULL;
	hash->allocatedBuffers = cpArrayNew(0);
	
	hash->stamp = 1;
	
	return (cpSpatialIndex *)hash;
}

cpSpatialIndex *
cpSpaceHashNew(cpFloat celldim, int cells, cpSpatialIndexBBFunc bbfunc, cpSpatialIndex *staticIndex)
{
	return cpSpaceHashInit(cpSpaceHashAlloc(), celldim, cells, bbfunc, staticIndex);
}

static void
cpSpaceHashDestroy(cpSpaceHash *hash)
{
	if(hash->table) clearTable(hash);
	cpfree(hash->table);
	
	cpHashSetFree(hash->handleSet);
	
	cpArrayFreeEach(hash->allocatedBuffers, cpfree);
	cpArrayFree(hash->allocatedBuffers);
	cpArrayFree(hash->pooledHandles);
}

//MARK: Helper Functions

static inline cpBool
containsHandle(cpSpaceHashBin *bin, cpHandle *hand)
{
	while(bin){
		if(bin->handle == hand) return cpTrue;
		bin = bin->next;
	}
	
	return cpFalse;
}

// The hash function itself.
static inline cpHashValue
hash_func(cpHashValue x, cpHashValue y, cpHashValue n)
{
	return (x*1640531513ul ^ y*2654435789ul) % n;
}

// Much faster than (int)floor(f)
// Profiling showed floor() to be a sizable performance hog
static inline int
floor_int(cpFloat f)
{
	int i = (int)f;
	return (f < 0.0f && f != i ? i - 1 : i);
}

static inline void
hashHandle(cpSpaceHash *hash, cpHandle *hand, cpBB bb)
{
	// Find the dimensions in cell coordinates.
	cpFloat dim = hash->celldim;
	int l = floor_int(bb.l/dim); // Fix by ShiftZ
	int r = floor_int(bb.r/dim);
	int b = floor_int(bb.b/dim);
	int t = floor_int(bb.t/dim);
	
	int n = hash->numcells;
	for(int i=l; i<=r; i++){
		for(int j=b; j<=t; j++){
			cpHashValue idx = hash_func(i,j,n);
			cpSpaceHashBin *bin = hash->table[idx];
			
			// Don't add an object twice to the same cell.
			if(containsHandle(bin, hand)) continue;

			cpHandleRetain(hand);
			// Insert a new bin for the handle in this cell.
			cpSpaceHashBin *newBin = getEmptyBin(hash);
			newBin->handle = hand;
			newBin->next = bin;
			hash->table[idx] = newBin;
		}
	}
}

//MARK: Basic Operations

static void
cpSpaceHashInsert(cpSpaceHash *hash, void *obj, cpHashValue hashid)
{
	cpHandle *hand = (cpHandle *)cpHashSetInsert(hash->handleSet, hashid, obj, hash, (cpHashSetTransFunc)handleSetTrans);
	hashHandle(hash, hand, hash->spatialIndex.bbfunc(obj));
}

static void
cpSpaceHashRehashObject(cpSpaceHash *hash, void *obj, cpHashValue hashid)
{
	cpHandle *hand = (cpHandle *)cpHashSetRemove(hash->handleSet, hashid, obj);
	
	if(hand){
		hand->obj = NULL;
		cpHandleRelease(hand, hash->pooledHandles);
		
		cpSpaceHashInsert(hash, obj, hashid);
	}
}

static void
rehash_helper(cpHandle *hand, cpSpaceHash *hash)
{
	hashHandle(hash, hand, hash->spatialIndex.bbfunc(hand->obj));
}

static void
cpSpaceHashRehash(cpSpaceHash *hash)
{
	clearTable(hash);
	cpHashSetEach(hash->handleSet, (cpHashSetIteratorFunc)rehash_helper, hash);
}

static void
cpSpaceHashRemove(cpSpaceHash *hash, void *obj, cpHashValue hashid)
{
	cpHandle *hand = (cpHandle *)cpHashSetRemove(hash->handleSet, hashid, obj);
	
	if(hand){
		hand->obj = NULL;
		cpHandleRelease(hand, hash->pooledHandles);
	}
}

typedef struct eachContext {
	cpSpatialIndexIteratorFunc func;
	void *data;
} eachContext;

static void eachHelper(cpHandle *hand, eachContext *context){context->func(hand->obj, context->data);}

static void
cpSpaceHashEach(cpSpaceHash *hash, cpSpatialIndexIteratorFunc func, void *data)
{
	eachContext context = {func, data};
	cpHashSetEach(hash->handleSet, (cpHashSetIteratorFunc)eachHelper, &context);
}

static void
remove_orphaned_handles(cpSpaceHash *hash, cpSpaceHashBin **bin_ptr)
{
	cpSpaceHashBin *bin = *bin_ptr;
	while(bin){
		cpHandle *hand = bin->handle;
		cpSpaceHashBin *next = bin->next;
		
		if(!hand->obj){
			// orphaned handle, unlink and recycle the bin
			(*bin_ptr) = bin->next;
			recycleBin(hash, bin);
			
			cpHandleRelease(hand, hash->pooledHandles);
		} else {
			bin_ptr = &bin->next;
		}
		
		bin = next;
	}
}

//MARK: Query Functions

static inline void
query_helper(cpSpaceHash *hash, cpSpaceHashBin **bin_ptr, void *obj, cpSpatialIndexQueryFunc func, void *data)
{
	restart:
	for(cpSpaceHashBin *bin = *bin_ptr; bin; bin = bin->next){
		cpHandle *hand = bin->handle;
		void *other = hand->obj;
		
		if(hand->stamp == hash->stamp || obj == other){
			continue;
		} else if(other){
			func(obj, other, 0, data);
			hand->stamp = hash->stamp;
		} else {
			// The object for this handle has been removed
			// cleanup this cell and restart the query
			remove_orphaned_handles(hash, bin_ptr);
			goto restart; // GCC not smart enough/able to tail call an inlined function.
		}
	}
}

static void
cpSpaceHashQuery(cpSpaceHash *hash, void *obj, cpBB bb, cpSpatialIndexQueryFunc func, void *data)
{
	// Get the dimensions in cell coordinates.
	cpFloat dim = hash->celldim;
	int l = floor_int(bb.l/dim);  // Fix by ShiftZ
	int r = floor_int(bb.r/dim);
	int b = floor_int(bb.b/dim);
	int t = floor_int(bb.t/dim);
	
	int n = hash->numcells;
	cpSpaceHashBin **table = hash->table;
	
	// Iterate over the cells and query them.
	for(int i=l; i<=r; i++){
		for(int j=b; j<=t; j++){
			query_helper(hash, &table[hash_func(i,j,n)], obj, func, data);
		}
	}
	
	hash->stamp++;
}

// Similar to struct eachPair above.
typedef struct queryRehashContext {
	cpSpaceHash *hash;
	cpSpatialIndexQueryFunc func;
	void *data;
} queryRehashContext;

// Hashset iterator func used with cpSpaceHashQueryRehash().
static void
queryRehash_helper(cpHandle *hand, queryRehashContext *context)
{
	cpSpaceHash *hash = context->hash;
	cpSpatialIndexQueryFunc func = context->func;
	void *data = context->data;

	cpFloat dim = hash->celldim;
	int n = hash->numcells;

	void *obj = hand->obj;
	cpBB bb = hash->spatialIndex.bbfunc(obj);

	int l = floor_int(bb.l/dim);
	int r = floor_int(bb.r/dim);
	int b = floor_int(bb.b/dim);
	int t = floor_int(bb.t/dim);
	
	cpSpaceHashBin **table = hash->table;

	for(int i=l; i<=r; i++){
		for(int j=b; j<=t; j++){
			cpHashValue idx = hash_func(i,j,n);
			cpSpaceHashBin *bin = table[idx];
			
			if(containsHandle(bin, hand)) continue;
			
			cpHandleRetain(hand); // this MUST be done first in case the object is removed in func()
			query_helper(hash, &bin, obj, func, data);
			
			cpSpaceHashBin *newBin = getEmptyBin(hash);
			newBin->handle = hand;
			newBin->next = bin;
			table[idx] = newBin;
		}
	}
	
	// Increment the stamp for each object hashed.
	hash->stamp++;
}

static void
cpSpaceHashReindexQuery(cpSpaceHash *hash, cpSpatialIndexQueryFunc func, void *data)
{
	clearTable(hash);
	
	queryRehashContext context = {hash, func, data};
	cpHashSetEach(hash->handleSet, (cpHashSetIteratorFunc)queryRehash_helper, &context);
	
	cpSpatialIndexCollideStatic((cpSpatialIndex *)hash, hash->spatialIndex.staticIndex, func, data);
}

static inline cpFloat
segmentQuery_helper(cpSpaceHash *hash, cpSpaceHashBin **bin_ptr, void *obj, cpSpatialIndexSegmentQueryFunc func, void *data)
{
	cpFloat t = 1.0f;
	 
	restart:
	for(cpSpaceHashBin *bin = *bin_ptr; bin; bin = bin->next){
		cpHandle *hand = bin->handle;
		void *other = hand->obj;
		
		// Skip over certain conditions
		if(hand->stamp == hash->stamp){
			continue;
		} else if(other){
			t = cpfmin(t, func(obj, other, data));
			hand->stamp = hash->stamp;
		} else {
			// The object for this handle has been removed
			// cleanup this cell and restart the query
			remove_orphaned_handles(hash, bin_ptr);
			goto restart; // GCC not smart enough/able to tail call an inlined function.
		}
	}
	
	return t;
}

// modified from http://playtechs.blogspot.com/2007/03/raytracing-on-grid.html
static void
cpSpaceHashSegmentQuery(cpSpaceHash *hash, void *obj, cpVect a, cpVect b, cpFloat t_exit, cpSpatialIndexSegmentQueryFunc func, void *data)
{
	a = cpvmult(a, 1.0f/hash->celldim);
	b = cpvmult(b, 1.0f/hash->celldim);
	
	int cell_x = floor_int(a.x), cell_y = floor_int(a.y);

	cpFloat t = 0;

	int x_inc, y_inc;
	cpFloat temp_v, temp_h;

	if (b.x > a.x){
		x_inc = 1;
		temp_h = (cpffloor(a.x + 1.0f) - a.x);
	} else {
		x_inc = -1;
		temp_h = (a.x - cpffloor(a.x));
	}

	if (b.y > a.y){
		y_inc = 1;
		temp_v = (cpffloor(a.y + 1.0f) - a.y);
	} else {
		y_inc = -1;
		temp_v = (a.y - cpffloor(a.y));
	}
	
	// Division by zero is *very* slow on ARM
	cpFloat dx = cpfabs(b.x - a.x), dy = cpfabs(b.y - a.y);
	cpFloat dt_dx = (dx ? 1.0f/dx : INFINITY), dt_dy = (dy ? 1.0f/dy : INFINITY);
	
	// fix NANs in horizontal directions
	cpFloat next_h = (temp_h ? temp_h*dt_dx : dt_dx);
	cpFloat next_v = (temp_v ? temp_v*dt_dy : dt_dy);
	
	int n = hash->numcells;
	cpSpaceHashBin **table = hash->table;

	while(t < t_exit){
		cpHashValue idx = hash_func(cell_x, cell_y, n);
		t_exit = cpfmin(t_exit, segmentQuery_helper(hash, &table[idx], obj, func, data));

		if (next_v < next_h){
			cell_y += y_inc;
			t = next_v;
			next_v += dt_dy;
		} else {
			cell_x += x_inc;
			t = next_h;
			next_h += dt_dx;
		}
	}
	
	hash->stamp++;
}

//MARK: Misc

void
cpSpaceHashResize(cpSpaceHash *hash, cpFloat celldim, int numcells)
{
	if(hash->spatialIndex.klass != Klass()){
		cpAssertWarn(cpFalse, "Ignoring cpSpaceHashResize() call to non-cpSpaceHash spatial index.");
		return;
	}
	
	clearTable(hash);
	
	hash->celldim = celldim;
	cpSpaceHashAllocTable(hash, next_prime(numcells));
}

static int
cpSpaceHashCount(cpSpaceHash *hash)
{
	return cpHashSetCount(hash->handleSet);
}

static int
cpSpaceHashContains(cpSpaceHash *hash, void *obj, cpHashValue hashid)
{
	return cpHashSetFind(hash->handleSet, hashid, obj) != NULL;
}

static cpSpatialIndexClass klass = {
	(cpSpatialIndexDestroyImpl)cpSpaceHashDestroy,
	
	(cpSpatialIndexCountImpl)cpSpaceHashCount,
	(cpSpatialIndexEachImpl)cpSpaceHashEach,
	(cpSpatialIndexContainsImpl)cpSpaceHashContains,
	
	(cpSpatialIndexInsertImpl)cpSpaceHashInsert,
	(cpSpatialIndexRemoveImpl)cpSpaceHashRemove,
	
	(cpSpatialIndexReindexImpl)cpSpaceHashRehash,
	(cpSpatialIndexReindexObjectImpl)cpSpaceHashRehashObject,
	(cpSpatialIndexReindexQueryImpl)cpSpaceHashReindexQuery,
	
	(cpSpatialIndexQueryImpl)cpSpaceHashQuery,
	(cpSpatialIndexSegmentQueryImpl)cpSpaceHashSegmentQuery,
};

static inline cpSpatialIndexClass *Klass(){return &klass;}

//MARK: Debug Drawing

//#define CP_BBTREE_DEBUG_DRAW
#ifdef CP_BBTREE_DEBUG_DRAW
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include <GLUT/glut.h>

void
cpSpaceHashRenderDebug(cpSpatialIndex *index)
{
	if(index->klass != &klass){
		cpAssertWarn(cpFalse, "Ignoring cpSpaceHashRenderDebug() call to non-spatial hash spatial index.");
		return;
	}
	
	cpSpaceHash *hash = (cpSpaceHash *)index;
	cpBB bb = cpBBNew(-320, -240, 320, 240);
	
	cpFloat dim = hash->celldim;
	int n = hash->numcells;
	
	int l = (int)floor(bb.l/dim);
	int r = (int)floor(bb.r/dim);
	int b = (int)floor(bb.b/dim);
	int t = (int)floor(bb.t/dim);
	
	for(int i=l; i<=r; i++){
		for(int j=b; j<=t; j++){
			int cell_count = 0;
			
			int index = hash_func(i,j,n);
			for(cpSpaceHashBin *bin = hash->table[index]; bin; bin = bin->next)
				cell_count++;
			
			GLfloat v = 1.0f - (GLfloat)cell_count/10.0f;
			glColor3f(v,v,v);
			glRectf(i*dim, j*dim, (i + 1)*dim, (j + 1)*dim);
		}
	}
}
#endif
