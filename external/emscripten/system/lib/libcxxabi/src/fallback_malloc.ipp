//===------------------------ fallback_malloc.ipp -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//  
//  This file implements the "Exception Handling APIs"
//  http://www.codesourcery.com/public/cxx-abi/abi-eh.html
//  
//===----------------------------------------------------------------------===//

//  A small, simple heap manager based (loosely) on 
//  the startup heap manager from FreeBSD, optimized for space.
//
//  Manages a fixed-size memory pool, supports malloc and free only.
//  No support for realloc.
//
//  Allocates chunks in multiples of four bytes, with a four byte header
//  for each chunk. The overhead of each chunk is kept low by keeping pointers
//  as two byte offsets within the heap, rather than (4 or 8 byte) pointers.

namespace {

static pthread_mutex_t heap_mutex = PTHREAD_MUTEX_INITIALIZER;

class mutexor {
public:
    mutexor ( pthread_mutex_t *m ) : mtx_(m) { pthread_mutex_lock ( mtx_ ); }
    ~mutexor () { pthread_mutex_unlock ( mtx_ ); }
private:
    mutexor ( const mutexor &rhs );
    mutexor & operator = ( const mutexor &rhs );
    pthread_mutex_t *mtx_;
    };

        
#define HEAP_SIZE   512
char heap [ HEAP_SIZE ];

typedef unsigned short heap_offset;
typedef unsigned short heap_size;

struct heap_node {
    heap_offset next_node;  // offset into heap
    heap_size   len;        // size in units of "sizeof(heap_node)"
};

static const heap_node *list_end = (heap_node *) ( &heap [ HEAP_SIZE ] );   // one past the end of the heap
static heap_node *freelist = NULL;

heap_node *node_from_offset ( const heap_offset offset )
    { return (heap_node *) ( heap + ( offset * sizeof (heap_node))); }

heap_offset offset_from_node ( const heap_node *ptr )
    { return static_cast<heap_offset>(static_cast<size_t>(((char *) ptr ) - heap)  / sizeof (heap_node)); }
 
void init_heap () {
    freelist = (heap_node *) heap;
    freelist->next_node = offset_from_node ( list_end );
    freelist->len = HEAP_SIZE / sizeof (heap_node);
    }
    
//  How big a chunk we allocate
size_t alloc_size (size_t len)
    { return (len + sizeof(heap_node) - 1) / sizeof(heap_node) + 1; }

bool is_fallback_ptr ( void *ptr )
    { return ptr >= heap && ptr < ( heap + HEAP_SIZE ); }

void *fallback_malloc(size_t len) {
    heap_node *p, *prev;
    const size_t nelems = alloc_size ( len );
    mutexor mtx ( &heap_mutex );
    
    if ( NULL == freelist )
        init_heap ();

//  Walk the free list, looking for a "big enough" chunk
    for (p = freelist, prev = 0; 
            p && p != list_end;     prev = p, p = node_from_offset ( p->next_node)) {

        if (p->len > nelems) {  //  chunk is larger, shorten, and return the tail
            heap_node *q;
            
            p->len -= nelems;
            q = p + p->len;
            q->next_node = 0;
            q->len = static_cast<heap_size>(nelems);
            return (void *) (q + 1);
        }
        
        if (p->len == nelems) { // exact size match
            if (prev == 0)
                freelist = node_from_offset(p->next_node);
            else
                prev->next_node = p->next_node;
            p->next_node = 0;
            return (void *) (p + 1);
        }
    }
    return NULL;    // couldn't find a spot big enough
}

//  Return the start of the next block
heap_node *after ( struct heap_node *p ) { return p + p->len; }

void fallback_free (void *ptr) {
    struct heap_node *cp = ((struct heap_node *) ptr) - 1;      // retrieve the chunk
    struct heap_node *p, *prev;

    mutexor mtx ( &heap_mutex );

#ifdef DEBUG_FALLBACK_MALLOC
        std::cout << "Freeing item at " << offset_from_node ( cp ) << " of size " << cp->len << std::endl;
#endif

    for (p = freelist, prev = 0; 
            p && p != list_end;     prev = p, p = node_from_offset (p->next_node)) {
#ifdef DEBUG_FALLBACK_MALLOC
        std::cout << "  p, cp, after (p), after(cp) "
            << offset_from_node ( p ) << ' '
            << offset_from_node ( cp ) << ' '
            << offset_from_node ( after ( p )) << ' '
            << offset_from_node ( after ( cp )) << std::endl;
#endif
        if ( after ( p ) == cp ) {
#ifdef DEBUG_FALLBACK_MALLOC
            std::cout << "  Appending onto chunk at " << offset_from_node ( p ) << std::endl;
#endif
            p->len += cp->len;  // make the free heap_node larger
            return;
            }
        else if ( after ( cp ) == p ) { // there's a free heap_node right after
#ifdef DEBUG_FALLBACK_MALLOC
            std::cout << "  Appending free chunk at " << offset_from_node ( p ) << std::endl;
#endif
            cp->len += p->len;
            if ( prev == 0 ) {
                freelist = cp;
                cp->next_node = p->next_node;
                }
            else
                prev->next_node = offset_from_node(cp);
            return;
            }
        }
//  Nothing to merge with, add it to the start of the free list
#ifdef DEBUG_FALLBACK_MALLOC
            std::cout << "  Making new free list entry " << offset_from_node ( cp ) << std::endl;
#endif
    cp->next_node = offset_from_node ( freelist );
    freelist = cp;
}

#ifdef INSTRUMENT_FALLBACK_MALLOC
size_t print_free_list () {
    struct heap_node *p, *prev;
    heap_size total_free = 0;
    if ( NULL == freelist )
        init_heap ();
    
    for (p = freelist, prev = 0; 
            p && p != list_end;     prev = p, p = node_from_offset (p->next_node)) {
        std::cout << ( prev == 0 ? "" : "  ")  << "Offset: " << offset_from_node ( p ) 
                << "\tsize: " << p->len << " Next: " << p->next_node << std::endl;
        total_free += p->len;
        }
    std::cout << "Total Free space: " << total_free << std::endl;
    return total_free;
    }
#endif
}  // end unnamed namespace
