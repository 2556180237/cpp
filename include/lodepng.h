/* Minimal embed of lodepng interface (public domain, https://lodev.org/lodepng/) */
#ifndef LODEPNG_MIN_H
#define LODEPNG_MIN_H
#ifdef __cplusplus
extern "C" {
#endif
unsigned lodepng_decode32_file(unsigned char** out, unsigned* w, unsigned* h, const char* filename);
void lodepng_free(void* p);
#ifdef __cplusplus
}
#endif
#endif


