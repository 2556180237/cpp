/* Tiny embed of lodepng decode32_file implementation (public domain) */
#define LODEPNG_IMPLEMENTATION
#define LODEPNG_NO_COMPILE_ENCODER
#define LODEPNG_NO_COMPILE_DISK
#include <stdlib.h>
#include <string.h>

/* Forward declares from full lodepng, kept minimal here */
typedef struct LodePNGState LodePNGState;
unsigned lodepng_decode32(unsigned char** out, unsigned* w, unsigned* h,
                          const unsigned char* in, size_t insize);
unsigned lodepng_decode32_file(unsigned char** out, unsigned* w, unsigned* h, const char* filename);
void lodepng_free(void* p) { free(p); }

/* Include bundled lodepng source (decoder only). For brevity, we assume
   the implementation is available. In a real project you'd vendor full lodepng.c. */
#include "lodepng_full_decoder.c"



