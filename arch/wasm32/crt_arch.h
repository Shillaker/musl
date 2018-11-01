#ifndef SHARED

#include <alloca.h>

// ------------------------------------
// Faasm-specific
// ------------------------------------

extern size_t __faasm_read_state(const char *key, unsigned char *buffer, size_t bufferLen);
extern void __faasm_write_state(const char *key, unsigned char *data, size_t dataLen);
extern void __faasm_write_state_offset(const char *key, size_t offset, unsigned char *data, size_t dataLen);
extern void __faasm_read_state_offset(const char *key, size_t offset, unsigned char *buffer, size_t bufferLen);
extern size_t __faasm_read_input(unsigned char *buffer, size_t bufferLen);
extern void __faasm_write_output(const unsigned char *output, size_t outputLen);
extern void __faasm_chain_function(const char *name, const unsigned char *inputData, size_t inputDataSize);


void _start_c(long *p);

void _start(void) {
  long p = 0;
  _start_c(&p);
}
#endif
