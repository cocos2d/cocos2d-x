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

typedef struct cpHashSetBin {
	void *elt;
	cpHashValue hash;
	struct cpHashSetBin *next;
} cpHashSetBin;

struct cpHashSet {
	unsigned int entries, size;
	
	cpHashSetEqlFunc eql;
	void *default_value;
	
	cpHashSetBin **table;
	cpHashSetBin *pooledBins;
	
	cpArray *allocatedBuffers;
};

void
cpHashSetFree(cpHashSet *set)
{
	if(set){
		cpfree(set->table);
		
		cpArrayFreeEach(set->allocatedBuffers, cpfree);
		cpArrayFree(set->allocatedBuffers);
		
		cpfree(set);
	}
}

cpHashSet *
cpHashSetNew(int size, cpHashSetEqlFunc eqlFunc)
{
	cpHashSet *set = (cpHashSet *)cpcalloc(1, sizeof(cpHashSet));
	
	set->size = next_prime(size);
	set->entries = 0;
	
	set->eql = eqlFunc;
	set->default_value = NULL;
	
	set->table = (cpHashSetBin **)cpcalloc(set->size, sizeof(cpHashSetBin *));
	set->pooledBins = NULL;
	
	set->allocatedBuffers = cpArrayNew(0);
	
	return set;
}

void
cpHashSetSetDefaultValue(cpHashSet *set, void *default_value)
{
	set->default_value = default_value;
}

static int
setIsFull(cpHashSet *set)
{
	return (set->entries >= set->size);
}

static void
cpHashSetResize(cpHashSet *set)
{
	// Get the next approximate doubled prime.
	unsigned int newSize = next_prime(set->size + 1);
	// Allocate a new table.
	cpHashSetBin **newTable = (cpHashSetBin **)cpcalloc(newSize, sizeof(cpHashSetBin *));
	
	// Iterate over the chains.
	for(unsigned int i=0; i<set->size; i++){
		// Rehash the bins into the new table.
		cpHashSetBin *bin = set->table[i];
		while(bin){
			cpHashSetBin *next = bin->next;
			
			cpHashValue idx = bin->hash%newSize;
			bin->next = newTable[idx];
			newTable[idx] = bin;
			
			bin = next;
		}
	}
	
	cpfree(set->table);
	
	set->table = newTable;
	set->size = newSize;
}

static inline void
recycleBin(cpHashSet *set, cpHashSetBin *bin)
{
	bin->next = set->pooledBins;
	set->pooledBins = bin;
	bin->elt = NULL;
}

static cpHashSetBin *
getUnusedBin(cpHashSet *set)
{
	cpHashSetBin *bin = set->pooledBins;
	
	if(bin){
		set->pooledBins = bin->next;
		return bin;
	} else {
		// Pool is exhausted, make more
		int count = CP_BUFFER_BYTES/sizeof(cpHashSetBin);
		cpAssertHard(count, "Internal Error: Buffer size is too small.");
		
		cpHashSetBin *buffer = (cpHashSetBin *)cpcalloc(1, CP_BUFFER_BYTES);
		cpArrayPush(set->allocatedBuffers, buffer);
		
		// push all but the first one, return it instead
		for(int i=1; i<count; i++) recycleBin(set, buffer + i);
		return buffer;
	}
}

int
cpHashSetCount(cpHashSet *set)
{
	return set->entries;
}

void *
cpHashSetInsert(cpHashSet *set, cpHashValue hash, void *ptr, void *data, cpHashSetTransFunc trans)
{
	cpHashValue idx = hash%set->size;
	
	// Find the bin with the matching element.
	cpHashSetBin *bin = set->table[idx];
	while(bin && !set->eql(ptr, bin->elt))
		bin = bin->next;
	
	// Create it if necessary.
	if(!bin){
		bin = getUnusedBin(set);
		bin->hash = hash;
		bin->elt = (trans ? trans(ptr, data) : data);
		
		bin->next = set->table[idx];
		set->table[idx] = bin;
		
		set->entries++;
		if(setIsFull(set)) cpHashSetResize(set);
	}
	
	return bin->elt;
}

void *
cpHashSetRemove(cpHashSet *set, cpHashValue hash, void *ptr)
{
	cpHashValue idx = hash%set->size;
	
	cpHashSetBin **prev_ptr = &set->table[idx];
	cpHashSetBin *bin = set->table[idx];
	
	// Find the bin
	while(bin && !set->eql(ptr, bin->elt)){
		prev_ptr = &bin->next;
		bin = bin->next;
	}
	
	// Remove it if it exists.
	if(bin){
		// Update the previous linked list pointer
		(*prev_ptr) = bin->next;
		set->entries--;
		
		void *elt = bin->elt;
		recycleBin(set, bin);
		
		return elt;
	}
	
	return NULL;
}

void *
cpHashSetFind(cpHashSet *set, cpHashValue hash, void *ptr)
{	
	cpHashValue idx = hash%set->size;
	cpHashSetBin *bin = set->table[idx];
	while(bin && !set->eql(ptr, bin->elt))
		bin = bin->next;
		
	return (bin ? bin->elt : set->default_value);
}

void
cpHashSetEach(cpHashSet *set, cpHashSetIteratorFunc func, void *data)
{
	for(unsigned int i=0; i<set->size; i++){
		cpHashSetBin *bin = set->table[i];
		while(bin){
			cpHashSetBin *next = bin->next;
			func(bin->elt, data);
			bin = next;
		}
	}
}

void
cpHashSetFilter(cpHashSet *set, cpHashSetFilterFunc func, void *data)
{
	for(unsigned int i=0; i<set->size; i++){
		// The rest works similarly to cpHashSetRemove() above.
		cpHashSetBin **prev_ptr = &set->table[i];
		cpHashSetBin *bin = set->table[i];
		while(bin){
			cpHashSetBin *next = bin->next;
			
			if(func(bin->elt, data)){
				prev_ptr = &bin->next;
			} else {
				(*prev_ptr) = next;

				set->entries--;
				recycleBin(set, bin);
			}
			
			bin = next;
		}
	}
}
