#include <stdlib.h>

#include "chipmunk_private.h"

void
cpSpatialIndexFree(cpSpatialIndex *index)
{
	if(index){
		cpSpatialIndexDestroy(index);
		cpfree(index);
	}
}

cpSpatialIndex *
cpSpatialIndexInit(cpSpatialIndex *index, cpSpatialIndexClass *klass, cpSpatialIndexBBFunc bbfunc, cpSpatialIndex *staticIndex)
{
	index->klass = klass;
	index->bbfunc = bbfunc;
	index->staticIndex = staticIndex;
	
	if(staticIndex){
		cpAssertHard(!staticIndex->dynamicIndex, "This static index is already associated with a dynamic index.");
		staticIndex->dynamicIndex = index;
	}
	
	return index;
}

typedef struct dynamicToStaticContext {
	cpSpatialIndexBBFunc bbfunc;
	cpSpatialIndex *staticIndex;
	cpSpatialIndexQueryFunc queryFunc;
	void *data;
} dynamicToStaticContext;

static void
dynamicToStaticIter(void *obj, dynamicToStaticContext *context)
{
	cpSpatialIndexQuery(context->staticIndex, obj, context->bbfunc(obj), context->queryFunc, context->data);
}

void
cpSpatialIndexCollideStatic(cpSpatialIndex *dynamicIndex, cpSpatialIndex *staticIndex, cpSpatialIndexQueryFunc func, void *data)
{
	if(cpSpatialIndexCount(staticIndex) > 0){
		dynamicToStaticContext context = {dynamicIndex->bbfunc, staticIndex, func, data};
		cpSpatialIndexEach(dynamicIndex, (cpSpatialIndexIteratorFunc)dynamicToStaticIter, &context);
	}
}

