/* Copyright (c) 2010 Scott Lembcke
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

static inline cpSpatialIndexClass *Klass();

//MARK: Basic Structures

typedef struct Bounds {
	cpFloat min, max;
} Bounds;

typedef struct TableCell {
	void *obj;
	Bounds bounds;
} TableCell;

struct cpSweep1D
{
	cpSpatialIndex spatialIndex;
	
	int num;
	int max;
	TableCell *table;
};

static inline cpBool
BoundsOverlap(Bounds a, Bounds b)
{
	return (a.min <= b.max && b.min <= a.max);
}

static inline Bounds
BBToBounds(cpSweep1D *sweep, cpBB bb)
{
	Bounds bounds = {bb.l, bb.r};
	return bounds;
}

static inline TableCell
MakeTableCell(cpSweep1D *sweep, void *obj)
{
	TableCell cell = {obj, BBToBounds(sweep, sweep->spatialIndex.bbfunc(obj))};
	return cell;
}

//MARK: Memory Management Functions

cpSweep1D *
cpSweep1DAlloc(void)
{
	return (cpSweep1D *)cpcalloc(1, sizeof(cpSweep1D));
}

static void
ResizeTable(cpSweep1D *sweep, int size)
{
	sweep->max = size;
	sweep->table = (TableCell *)cprealloc(sweep->table, size*sizeof(TableCell));
}

cpSpatialIndex *
cpSweep1DInit(cpSweep1D *sweep, cpSpatialIndexBBFunc bbfunc, cpSpatialIndex *staticIndex)
{
	cpSpatialIndexInit((cpSpatialIndex *)sweep, Klass(), bbfunc, staticIndex);
	
	sweep->num = 0;
	ResizeTable(sweep, 32);
	
	return (cpSpatialIndex *)sweep;
}

cpSpatialIndex *
cpSweep1DNew(cpSpatialIndexBBFunc bbfunc, cpSpatialIndex *staticIndex)
{
	return cpSweep1DInit(cpSweep1DAlloc(), bbfunc, staticIndex);
}

static void
cpSweep1DDestroy(cpSweep1D *sweep)
{
	cpfree(sweep->table);
	sweep->table = NULL;
}

//MARK: Misc

static int
cpSweep1DCount(cpSweep1D *sweep)
{
	return sweep->num;
}

static void
cpSweep1DEach(cpSweep1D *sweep, cpSpatialIndexIteratorFunc func, void *data)
{
	TableCell *table = sweep->table;
	for(int i=0, count=sweep->num; i<count; i++) func(table[i].obj, data);
}

static int
cpSweep1DContains(cpSweep1D *sweep, void *obj, cpHashValue hashid)
{
	TableCell *table = sweep->table;
	for(int i=0, count=sweep->num; i<count; i++){
		if(table[i].obj == obj) return cpTrue;
	}
	
	return cpFalse;
}

//MARK: Basic Operations

static void
cpSweep1DInsert(cpSweep1D *sweep, void *obj, cpHashValue hashid)
{
	if(sweep->num == sweep->max) ResizeTable(sweep, sweep->max*2);
	
	sweep->table[sweep->num] = MakeTableCell(sweep, obj);
	sweep->num++;
}

static void
cpSweep1DRemove(cpSweep1D *sweep, void *obj, cpHashValue hashid)
{
	TableCell *table = sweep->table;
	for(int i=0, count=sweep->num; i<count; i++){
		if(table[i].obj == obj){
			int num = --sweep->num;
			
			table[i] = table[num];
			table[num].obj = NULL;
			
			return;
		}
	}
}

//MARK: Reindexing Functions

static void
cpSweep1DReindexObject(cpSweep1D *sweep, void *obj, cpHashValue hashid)
{
	// Nothing to do here
}

static void
cpSweep1DReindex(cpSweep1D *sweep)
{
	// Nothing to do here
	// Could perform a sort, but queries are not accelerated anyway.
}

//MARK: Query Functions

static void
cpSweep1DQuery(cpSweep1D *sweep, void *obj, cpBB bb, cpSpatialIndexQueryFunc func, void *data)
{
	// Implementing binary search here would allow you to find an upper limit
	// but not a lower limit. Probably not worth the hassle.
	
	Bounds bounds = BBToBounds(sweep, bb);
	
	TableCell *table = sweep->table;
	for(int i=0, count=sweep->num; i<count; i++){
		TableCell cell = table[i];
		if(BoundsOverlap(bounds, cell.bounds) && obj != cell.obj) func(obj, cell.obj, 0, data);
	}
}

static void
cpSweep1DSegmentQuery(cpSweep1D *sweep, void *obj, cpVect a, cpVect b, cpFloat t_exit, cpSpatialIndexSegmentQueryFunc func, void *data)
{
	cpBB bb = cpBBExpand(cpBBNew(a.x, a.y, a.x, a.y), b);
	Bounds bounds = BBToBounds(sweep, bb);
	
	TableCell *table = sweep->table;
	for(int i=0, count=sweep->num; i<count; i++){
		TableCell cell = table[i];
		if(BoundsOverlap(bounds, cell.bounds)) func(obj, cell.obj, data);
	}
}

//MARK: Reindex/Query

static int
TableSort(TableCell *a, TableCell *b)
{
	return (a->bounds.min < b->bounds.min ? -1 : (a->bounds.min > b->bounds.min ? 1 : 0));
}

static void
cpSweep1DReindexQuery(cpSweep1D *sweep, cpSpatialIndexQueryFunc func, void *data)
{
	TableCell *table = sweep->table;
	int count = sweep->num;
	
	// Update bounds and sort
	for(int i=0; i<count; i++) table[i] = MakeTableCell(sweep, table[i].obj);
	qsort(table, count, sizeof(TableCell), (int (*)(const void *, const void *))TableSort); // TODO use insertion sort instead
	
	for(int i=0; i<count; i++){
		TableCell cell = table[i];
		cpFloat max = cell.bounds.max;
		
		for(int j=i+1; table[j].bounds.min < max && j<count; j++){
			func(cell.obj, table[j].obj, 0, data);
		}
	}
	
	// Reindex query is also responsible for colliding against the static index.
	// Fortunately there is a helper function for that.
	cpSpatialIndexCollideStatic((cpSpatialIndex *)sweep, sweep->spatialIndex.staticIndex, func, data);
}

static cpSpatialIndexClass klass = {
	(cpSpatialIndexDestroyImpl)cpSweep1DDestroy,
	
	(cpSpatialIndexCountImpl)cpSweep1DCount,
	(cpSpatialIndexEachImpl)cpSweep1DEach,
	(cpSpatialIndexContainsImpl)cpSweep1DContains,
	
	(cpSpatialIndexInsertImpl)cpSweep1DInsert,
	(cpSpatialIndexRemoveImpl)cpSweep1DRemove,
	
	(cpSpatialIndexReindexImpl)cpSweep1DReindex,
	(cpSpatialIndexReindexObjectImpl)cpSweep1DReindexObject,
	(cpSpatialIndexReindexQueryImpl)cpSweep1DReindexQuery,
	
	(cpSpatialIndexQueryImpl)cpSweep1DQuery,
	(cpSpatialIndexSegmentQueryImpl)cpSweep1DSegmentQuery,
};

static inline cpSpatialIndexClass *Klass(){return &klass;}

