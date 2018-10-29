#ifndef SHARED

#include <alloca.h>

// ------------------------------------
// Faasm-specific
// ------------------------------------

size_t __faasm_read_state(const char *key, uint8_t *buffer, size_t bufferLen);
void __faasm_write_state(const char *key, uint8_t *data, size_t dataLen);
void __faasm_write_state_offset(const char *key, size_t offset, uint8_t *data, size_t dataLen);
void __faasm_read_state_offset(const char *key, size_t offset, uint8_t *buffer, size_t bufferLen);


void _start_c(long *p);

void _start(void) {
  long p = 0;
  _start_c(&p);
}
#endif
