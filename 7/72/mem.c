#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "mem.h"

typedef struct metablock_s metablock;

struct metablock_s {
	size_t size;
	int free;
	metablock *next;
	metablock *prev;
};

#define META_SIZE sizeof(struct metablock_s)

metablock *base = NULL;
metablock *tail = NULL;

metablock *find_first_free(size_t size) {
	metablock *it = base;
	while (it) {
		if (it->free && it->size >= size) {
			return it;
		}
		it = it->next;
	}
	return NULL;
}

metablock *append_block(size_t size) {
  printf("> append_block: size: %ld\n", (long) size);
	metablock *new = sbrk(0);
	if (new == (void *) -1) {
		fprintf(stderr, "append_block: sbrk(0)");
		return NULL;
	}
	if (sbrk(size + META_SIZE) == (void *) -1) {
		fprintf(stderr, "append_block: sbrk(META_SIZE)");
		return NULL;
	}
	new->size = size;
	new->free = 1;
	new->prev = tail;
	if (tail) tail->next = new;
	return (tail = new);
}

void *mmalloc(size_t size) {
	metablock *block;
	if (base == NULL) {
		base = append_block(size);
	}
	block = find_first_free(size);
	if (block == NULL) {
		block = append_block(size);
	}
  block->free = 0;
	return (block + 1);
}

void merge_block(metablock *retain, metablock *merged) {
	// TODO: Implement merge block
}

void mfree(void *ptr) {
	if (!ptr) return;

	metablock *block = (metablock *) ptr - 1;
	assert(block->free == 0);
	block->free = 1;

	if (block->next && block->next->free) {
		merge_block(block, block->next);
	}
	if (block->prev && block->prev->free) {
		merge_block(block->prev, block);
	}
}

void debug() {
  printf("===================\n");
	metablock *it = base;
	int count = 0;
	while (it) {
		printf("[node: %d] size: %ld, free: %d\n", count++, (long) it->size, it->free);
		it = it->next;
	}
  printf("===================\n");
}
