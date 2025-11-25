#include <stddef.h>

void *mmalloc(size_t size);
void mfree(void *ptr);

#ifdef DEBUG_MMALOC
void printlist();
#endif
