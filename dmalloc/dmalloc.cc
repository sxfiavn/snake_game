#define DMALLOC_DISABLE 1
#include "dmalloc.hh"
#include <cassert>
#include <cstring>
#include <stdio.h>
#include <climits>
#include <map>

// metadata struct
// keep track of the data for each allocation
struct metadata
{
    long line;         // 8 bytes
    const char *file;  // 8 bytes
    int freeing_count; // 4 bytes
    size_t memory_size;
};

static std::map<void *, metadata> pointerM; // map void* to numbers for line, file, freeing count and memory size

dmalloc_stats malloc_stats{
    .nactive = 0,            // number of active allocations [#malloc - #free]
    .active_size = 0,        // number of bytes in active allocations
    .ntotal = 0,             // number of allocations, total
    .total_size = 0,         // number of bytes in allocations, total
    .nfail = 0,              // number of failed allocation attempts
    .fail_size = 0,          // number of bytes in failed allocation attempts
    .heap_min = UINTPTR_MAX, // smallest address in any region ever allocated
    .heap_max = 0            // largest address in any region ever allocated
};

// int g_nactive = 0;
// int g_ntotal = 0;

/**
 * dmalloc(sz,file,line)
 *      malloc() wrapper. Dynamically allocate the requested amount `sz` of memory and
 *      return a pointer to it
 *
 * @arg size_t sz : the amount of memory requested
 * @arg const char *file : a string containing the filename from which dmalloc was called
 * @arg long line : the line number from which dmalloc was called
 *
 * @return a pointer to the heap where the memory was reserved
 */
void *dmalloc(size_t sz, const char *file, long line)
{
    (void)file, (void)line; // avoid uninitialized variable warnings
    // Your code here.
    // g_nactive++;
    // g_ntotal++;

    int metadata_size = sizeof(metadata);

    // Metadata pointer
    void *metadata_pointer = base_malloc(sz + metadata_size + 300);

    // Data pointer (start)
    void *data_index = (char *)metadata_pointer + metadata_size;
    // finds address of the metadata pointer and adds the metadata size to get to the end of the block.

    // Deal with the exception first
    if (sz == 0 || sz > UINT_MAX - sizeof(malloc_stats) || (!data_index))
    // If the size is 0 or if the size of the attempted allocation is bigger than the memory space available or data index null
    {
        malloc_stats.fail_size += sz; // Add the size of the current failed attempt
        malloc_stats.nfail++;         // Increase the failed number of allocations attempted
        return nullptr;
    }

    // The metadata will be stored at the beginning of an allocated block, but dmalloc
    // should still return a pointer to the “payload” of the block, i.e., to the space
    // after the metadata.

    // secret value to check

    if (!data_index)
    {
        malloc_stats.nfail++;
        malloc_stats.fail_size += sz;
    }
    else
    {
        // Active stats
        malloc_stats.nactive++;
        malloc_stats.active_size += sz;

        // Total stats
        malloc_stats.ntotal++;
        malloc_stats.total_size += sz;

        // Pointer to the Metadata
        pointerM[data_index] = {
            .line = line,
            .file = file,
            .freeing_count = 0,
            .memory_size = sz,
        };

        // if (data_index > malloc_stats.heap_max)
        // {
        //     malloc_stats.heap_max = data_index + sz;
        // }

        // if (data_index < malloc_stats.heap_min)
        // {
        //     malloc_stats.heap_min = data_index;
        // }

        if ((uintptr_t)data_index > malloc_stats.heap_max)
        {
            malloc_stats.heap_max = (uintptr_t)data_index + sz; // largest address in any region ever allocated
        }

        if ((uintptr_t)data_index < malloc_stats.heap_min)
        {
            malloc_stats.heap_min = (uintptr_t)data_index; // smallest address in any region ever allocated
        }

        // malloc_stats.nfail = 0;       // number of failed allocation attempts
        // malloc_stats.fail_size = 0;   // number of bytes in failed allocation attempts
        // malloc_stats.heap_min = NULL; // smallest address in any region ever allocated
        // malloc_stats.heap_max = 0;    // largest address in any region ever allocated
    }

    metadata now{
        .line = line,
        .file = file,
        .freeing_count = 0,
        .memory_size = sz,
    };

    for (int i = 0; i < 200; i++)
    {
        *((char *)data_index + i + sz) = 'r'; // Fill each with a letter
    }

    // Update Metadata
    *(metadata *)metadata_pointer = now;

    return (data_index);
}

/**
 * dfree(ptr, file, line)
 *      free() wrapper. Release the block of heap memory pointed to by `ptr`. This should
 *      be a pointer that was previously allocated on the heap. If `ptr` is a nullptr do nothing.
 *
 * @arg void *ptr : a pointer to the heap
 * @arg const char *file : a string containing the filename from which dfree was called
 * @arg long line : the line number from which dfree was called
 */
void dfree(void *ptr, const char *file, long line)
{
    (void)file, (void)line; // avoid uninitialized variable warnings
    // Your code here.
    // g_nactive--;

    // malloc_stats.nactive--;
    // malloc_stats.active_size -= sz;

    // Idea
    // If the pointer is not null (we aren't trying to free something that is already free)
    // Then update the statistics with the new values

    // Metadata Block Size
    int sz2 = sizeof(metadata);

    if (ptr)
    {
        // size_t metadata_size = pointerM[ptr].memory_size;

        // Invalid Pointer (out of bounds)
        if ((uintptr_t)ptr > malloc_stats.heap_max || malloc_stats.heap_min > (uintptr_t)ptr)
        {
            fprintf(stderr, "MEMORY BUG: %s:%ld: invalid free of pointer %p, not in heap", file, line, ptr);
            abort();
        }

        // Tests 21 through 23
        //! Bad pointer ??{0x\w+}=ptr??
        //! MEMORY BUG???: invalid free of pointer ??ptr??, not allocated

        //  Expected `MEMORY BUG: test???.cc:10: invalid free of pointer ??ptr??, not allocated out
        //  Got `MEMORY BUG: test023.cc:10: detected wild write during free of pointer 0x2784ef4f`
        // Tests 31 through 33
        if (pointerM.count(ptr) == 0) // If count 0
        {
            for (auto const &[key, value] : pointerM)
            {
                if (ptr > key && ptr < (((char *)key) + value.memory_size))
                {
                    int pointerVSkey = (char *)ptr - ((char *)key);
                    // fprintf(stderr, "MEMORY BUG???: invalid free of pointer ??ptr??, not allocated\n");
                    // fprintf(stderr, "MEMORY BUG: test???.cc:%ld: invalid free of pointer ??ptr??, not allocated\n", line);
                    // fprintf(stderr, "MEMORY BUG: %s:%ld: invalid free of pointer %p, not allocated\n", file, line, ptr);
                    fprintf(stderr, "MEMORY BUG: %s:%ld: invalid free of pointer %p, not allocated\n", file, line, ptr);
                    fprintf(stderr, "%s:%ld: %p is %d bytes inside a %ld byte region allocated here", value.file, value.line, ptr, pointerVSkey, value.memory_size);
                    abort();
                }
            }
        }

        // Double free
        // if the free count for a metadata block > 0
        if (pointerM[ptr].freeing_count > 0)
        {
            fprintf(stderr, "MEMORY BUG: %s:%ld: invalid free of pointer %p, double free", file, line, ptr);
            abort();
        }

        size_t metadata_size = pointerM[ptr].memory_size; // Threw error if I defined it

        if (*(metadata_size + (char *)ptr) != 'r') // If the header is not r
        {
            fprintf(stderr, "MEMORY BUG: %s:%ld: detected wild write during free of pointer %p", file, line, ptr);
            abort();
        }

        // Only if no errors aborted program:
        base_free((char *)ptr - sz2);
        pointerM[ptr].freeing_count++;               // Increase number of time memory has been freed
        malloc_stats.nactive--;                      // Decrease number of allocations active
        malloc_stats.active_size -= (metadata_size); // Decrease the size of the freed allocation
    }

    // base_free(ptr);
}

/**
 * dcalloc(nmemb, sz, file, line)
 *      calloc() wrapper. Dynamically allocate enough memory to store an array of `nmemb`
 *      number of elements with wach element being `sz` bytes. The memory should be initialized
 *      to zero
 *
 * @arg size_t nmemb : the number of items that space is requested for
 * @arg size_t sz : the size in bytes of the items that space is requested for
 * @arg const char *file : a string containing the filename from which dcalloc was called
 * @arg long line : the line number from which dcalloc was called
 *
 * @return a pointer to the heap where the memory was reserved
 */
void *dcalloc(size_t nmemb, size_t sz, const char *file, long line)
{
    // Your code here (to fix test014).
    if (sz == 0 || nmemb == 0 || sz > UINTPTR_MAX / nmemb)
    // if no size or no items, or of size is bigger than the max memory for uintpters / number of elements
    {
        malloc_stats.nfail++;
        malloc_stats.fail_size++;
        return nullptr;
    }
    void *ptr = dmalloc(nmemb * sz, file, line);
    if (ptr)
    {
        memset(ptr, 0, nmemb * sz);
    }
    return ptr;
}

/**
 * get_statistics(stats)
 *      fill a dmalloc_stats pointer with the current memory statistics
 *
 * @arg dmalloc_stats *stats : a pointer to the the dmalloc_stats struct we want to fill
 */
void get_statistics(dmalloc_stats *stats)
{
    // Stub: set all statistics to enormous numbers
    // memset(stats, 255, sizeof(dmalloc_stats));
    // Your code here.

    *stats = malloc_stats; // points the stats pointer to the malloc_stats struct.
}

/**
 * print_statistics()
 *      print the current memory statistics to stdout
 */
void print_statistics()
{
    dmalloc_stats stats;
    get_statistics(&stats);

    printf("alloc count: active %10llu   total %10llu   fail %10llu\n",
           stats.nactive, stats.ntotal, stats.nfail);
    printf("alloc size:  active %10llu   total %10llu   fail %10llu\n",
           stats.active_size, stats.total_size, stats.fail_size);
}

/**
 * print_leak_report()
 *      Print a report of all currently-active allocated blocks of dynamic
 *      memory.
 */
void print_leak_report()
{
    // Your code here.
    for (auto const &[key, value] : pointerM) // for each key value pair in pointer M
    {
        if (value.freeing_count == 0) // If the memory has neven been freed (aka. is still active)
        {
            printf("LEAK CHECK: %s:%ld: allocated object %p with size %ld\n", value.file, value.line, key, value.memory_size);
        }
    }
}

// Extra Credit
/// drealloc(ptr, sz, file, line)
///    Reallocate the dynamic memory pointed to by `ptr` to hold at least
///    `sz` bytes, returning a pointer to the new block. If `ptr` is
///    `nullptr`, behaves like `dmalloc(sz, file, line)`. If `sz` is 0,
///    behaves like `dfree(ptr, file, line)`. The allocation request
///    was at location `file`:`line`.

void *drealloc(void *ptr, size_t sz, const char *file, long line)
{

    // Deal with exceptions first
    if (!ptr) // If pointer doesn't exist
    {
        return dmalloc(sz, file, line);
    }
    else if (sz == 0)
    {
        dfree(ptr, file, line);
        return nullptr;
    }
    else
    {
        /* code */
        /// Reallocate the dynamic memory pointed to by `ptr` to hold at least
        ///  `sz` bytes, returning a pointer to the new block.
        if (pointerM[ptr].memory_size < sz) // If sz its actually bigger than out current size
        {
            // Get the difference in sizes
            size_t need_to_add = sz - pointerM[ptr].memory_size;

            // Check that none of the continuos memory is being used

            size_t metadata_size = pointerM[ptr].memory_size; // Threw error if I defined it

            if (*(metadata_size + (char *)ptr) + need_to_add != 'r')
            {
                // If the memory is used, throw this error:
                fprintf(stderr, "MEMORY BUG: %s:%ld: Trying to overwrite memory through %p, that is currently being occupied", file, line, ptr);
                abort();
            }

            // Else, add that memory to the memory size
            pointerM[ptr].memory_size += need_to_add;
        }
    }
    return ptr;
}
