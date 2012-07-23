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
 
// cpHashSet uses a chained hashtable implementation.
// Other than the transformation functions, there is nothing fancy going on.

// cpHashSetBin's form the linked lists in the chained hash table.
typedef struct cpHashSetBin {
	// Pointer to the element.
	CP_PRIVATE(void *elt);
	// Hash value of the element.
	CP_PRIVATE(cpHashValue hash);
	// Next element in the chain.
	CP_PRIVATE(struct cpHashSetBin *next);
} cpHashSetBin;

// Equality function. Returns true if ptr is equal to elt.
typedef cpBool (*cpHashSetEqlFunc)(void *ptr, void *elt);
// Used by cpHashSetInsert(). Called to transform the ptr into an element.
typedef void *(*cpHashSetTransFunc)(void *ptr, void *data);

typedef struct cpHashSet {
	// Number of elements stored in the table.
	CP_PRIVATE(int entries);
	// Number of cells in the table.
	CP_PRIVATE(int size);
	
	CP_PRIVATE(cpHashSetEqlFunc eql);
	CP_PRIVATE(cpHashSetTransFunc trans);
	
	// Default value returned by cpHashSetFind() when no element is found.
	// Defaults to NULL.
	CP_PRIVATE(void *default_value);
	
	// The table and recycled bins
	CP_PRIVATE(cpHashSetBin **table);
	CP_PRIVATE(cpHashSetBin *pooledBins);
	
	CP_PRIVATE(cpArray *allocatedBuffers);
} cpHashSet;

// Basic allocation/destruction functions.
void cpHashSetDestroy(cpHashSet *set);
void cpHashSetFree(cpHashSet *set);

cpHashSet *cpHashSetAlloc(void);
cpHashSet *cpHashSetInit(cpHashSet *set, int size, cpHashSetEqlFunc eqlFunc, cpHashSetTransFunc trans);
cpHashSet *cpHashSetNew(int size, cpHashSetEqlFunc eqlFunc, cpHashSetTransFunc trans);

// Insert an element into the set, returns the element.
// If it doesn't already exist, the transformation function is applied.
void *cpHashSetInsert(cpHashSet *set, cpHashValue hash, void *ptr, void *data);
// Remove and return an element from the set.
void *cpHashSetRemove(cpHashSet *set, cpHashValue hash, void *ptr);
// Find an element in the set. Returns the default value if the element isn't found.
void *cpHashSetFind(cpHashSet *set, cpHashValue hash, void *ptr);

// Iterate over a hashset.
typedef void (*cpHashSetIterFunc)(void *elt, void *data);
void cpHashSetEach(cpHashSet *set, cpHashSetIterFunc func, void *data);

// Iterate over a hashset, drop the element if the func returns false.
typedef cpBool (*cpHashSetFilterFunc)(void *elt, void *data);
void cpHashSetFilter(cpHashSet *set, cpHashSetFilterFunc func, void *data);
