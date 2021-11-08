Caches are used to reduce the average time to access data from main memory in a computer.
When the memory block requested is present in a cache, it is called a hit. When the memory
block is not in the cache, it is called a miss, and the requested memory block is loaded into the
cache. In this problem, you will write a program to determine the hits and misses for four
different types of caches, and determine which one has the highest ratio of hits to misses for a
given set of memory accesses:

1-way set associative, 2-way set associative, 4-way set associative, 8-way set associative
An m-way set associative cache contains m cache blocks per set. You are given four types of
caches where each cache contains total of 8 cache blocks.

Your program should the input file that contains the memory block addresses and report the total
hits and missed for each cache configuration and the type of cache with the largest number of
hits:

Test case 1: 1-way set associative hits: # misses: #
2-way set associative hits: # misses: #
4-way set associative hits: # misses: #
8-way set associative hits: # misses: #
Best scheme: #-way set associative
Test case 2:
1-way set associative hits: # misses: #
2-way set associative hits: # misses: #
4-way set associative hits: # misses: #
8-way set associative hits: # misses: #
Best scheme: #-way set associative
and so on.

The test file has this format:
# number of test cases
# number of accesses
# memory block addresses
5
