# Malloc
In this homework assignment, you will build a jank memory allocator. You will implement two functions: jalloc() and jfree() (jank alloc and jank free).


Requirements
------------

1. Your memory allocator will serve memory requests out of a heap that should be declared as a global char array (example below). All of the data structures that track which memory is used and which is available should live inside the heap (like we discussed in class). Memory in the heap will be divided into free blocks and used blocks. Each allocated or free block will be preceeded by a header containing metadata about that block.


char heap[8192];

The metadata struct should contain the following members:
  * prev, next: pointers to metadata structures describing adjacent blocks
  * size: the size of the block of memory
  * free: a boolean variable describing whether this block is free (optional)


  |---------------------------|
  |                           |
  |     Block of allocated    |
  |     memory                |
  |                           |
  |                           |
  |                           |
  |---------------------------|
  |     Metadata              |
  |---------------------------|
  |                           |
  |     Block of free memory  |
  |                           |
  |---------------------------|
  |     Metadata              |
  |---------------------------|
  |     Block of allocated    |
  |     memory                |
  |---------------------------|
  |     Metadata              |
  |---------------------------|


2. void *jalloc(unsigned int size)

This function returns either the address of a block of memory from inside the heap that is size bytes long. To find a block, jalloc() traverses the linked list of free blocks, looking for a block that is at least size bytes long (possibly longer). When it finds a long enough block, it divides the block in two: the first part will be size bytes long, the second part will be the remainder of the block. jalloc() should create a new metadata structure on the heap for the new block that got created by splitting the old block up. The block that is size bytes long can be unlinked from the free list, and its address should be returned by jalloc(). The other part of the block that was split up should be linked in to the free list.

If no memory block is big enough to satisfy the request, jalloc() should return NULL.

3. jfree(void *p)

This function should return a block of memory pointed to by p to the free list. It should be linked into the free list in address order (don't just put it at the beginning of the free list). After returning the block to the free list, jfree() should check to see if the neighboring blocks are also free. If neighboring blocks are also free, jfree() should combine adjacent free blocks into a single free block represented by a single metadata struct.
