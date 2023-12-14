#include <stdio.h>
#include <time.h>

#define TESTS 10000
#define ELEMENTS 10000

int bin_search(int target, const int list[], int n);
int bin_search_modified(int target, const int list[], int n);

// profiling does not show any meaningful performance difference between
// the two bin_search methods.
int main(void) {
    int list[ELEMENTS];
    for (int i = 0; i < ELEMENTS; i++) {
        list[i] = i;
    }

    // test bin_search
    clock_t cycles = clock();
    for (int i = 0; i < TESTS; i++) {
        // test case where target is not in list
        bin_search(-1, list, ELEMENTS);
    }
    cycles = clock() - cycles;
    printf("bin_search\n");
    printf("(cycles: %lu) (time: %.4f)\n", cycles, (double) cycles / CLOCKS_PER_SEC);

    // test bin_search_modified
    cycles = clock();
    for (int i = 0; i < TESTS; i++) {
        // test case where target is not in list
        bin_search_modified(-1, list, ELEMENTS);
    }
    cycles = clock() - cycles;
    printf("\nbin_search_modified\n");
    printf("(cycles: %lu) (time: %.4f)\n", cycles, (double) cycles / CLOCKS_PER_SEC);

    int list_test[] = {1,2,4,5,6,8,10};
    printf("%d\n", bin_search_modified(1, list_test, 7));
}


// precondition: list is sorted; n is length of list
int bin_search(int target, const int list[], int n) {
    int lo, hi, mid;

    lo = 0;
    hi = n;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (target < list[mid]) {
            hi = mid;
        } else if (target > list[mid]) {
            lo = mid+1;
        } else {
            return mid;
        }
    }
    return -1;
}

// precondition: list is sorted; n is length of list
int bin_search_modified(int target, const int list[], int n) {
    int lo, hi, mid;

    lo = 0;
    hi = n;
    mid = lo + (hi - lo) / 2;
    while (lo < hi && target != list[mid]) {
        if (target < list[mid]) {
            hi = mid;
        } else {
            lo = mid+1;
        }
        mid = lo + (hi - lo) / 2;
    }

    if (list[mid] == target) {
        return mid;
    }

    return -1;
}
