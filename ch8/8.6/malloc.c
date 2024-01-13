#include <stdlib.h>

#define NALLOC 1024     // minimum units to request

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *mmalloc(unsigned);
void *mcalloc(unsigned, unsigned);
void mfree(void *);
Header *morecore(unsigned);

// mmalloc: general purpose storage allocator
void *mmalloc(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { // no free list yet
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {  // big enough
            if (p->s.size == nunits) {  // exactly
                prevp->s.ptr = p->s.ptr;
            } else {    // allocate tail end
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) {   // wrapped around free list
            if ((p = morecore(nunits)) == NULL) {
                return NULL;
            }
        }
    }
}

// morecore: ask system for more memory
Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    mfree((void *)(up+1));
    return freep;
}

// mfree: put block ap in free list
void mfree(void *ap) {
    Header *bp, *p;

    bp = (Header *)ap - 1;  // point to block header
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            // freed block at start or end of arena
            break;
        }
    }

    // join to upper nbr
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    // join to lower nbr
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }

    freep = p;
}

void *mcalloc(unsigned n, unsigned size) {
    char *p, *ptr;
    if ((p = ptr = mmalloc(n * size)) != NULL) {
        for (int i = 0; i < n * size; i++) {
            *ptr++ = 0;
        }
    }
    return p;
}
