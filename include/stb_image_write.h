/* stb_image_write - v1.16 - public domain - http://nothings.org/stb
   no warranty implied; use at your own risk

   QUICKSTART:
      #define STB_IMAGE_WRITE_IMPLEMENTATION
      #include "stb_image_write.h"

   Will output PNG files.

   More documentation at the end of this file.

LICENSE

  See end of file for license information.

REVISION HISTORY

      1.16  (2021-07-11) fix gcc -Wstringop-overflow warning
      1.15  (2019-03-04) fix warnings
      1.14  (2018-02-11) fix warnings
      1.13  (2017-07-23) document stbi_write_* functions
      1.12  (2017-03-03) anonymous review
      1.11  (2016-09-19) anonymous review
      1.10  (2016-08-27) fix memory leaks in monochrome BMP
      1.09  (2016-05-25) fix memory leak in tga monochrome
      1.08  (2016-04-02) fix typo in zlib quality API, improve STB_I_W_STATIC in C++
      1.07  (2015-08-27) fix bug in GIF palette that caused a worse-quality second image
      1.06  (2015-08-03) fix bug in where we used the 'sizeof' operator from the wrong variable
      1.05  (2015-07-07) fix compiler warning from unsigned char overflow
      1.04  (2015-04-19) fix warning and platform-specific compile issue
      1.03  (2014-09-14) fix to write BMP when alpha != 0
      1.02  (2014-05-31) fix warnings; fix compiler crash on some platforms
      1.01  (2014-05-25) fix bug in GIF writer that corrupted the image
      1.00  (2014-05-22) first public release
*/

#ifndef INCLUDE_STB_IMAGE_WRITE_H
#define INCLUDE_STB_IMAGE_WRITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STB_IMAGE_WRITE_STATIC
#define STBIWDEF static
#else
#define STBIWDEF extern
#endif

#ifndef STBI_WRITE_NO_STDIO
STBIWDEF int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
STBIWDEF int stbi_write_bmp(char const *filename, int w, int h, int comp, const void *data);
STBIWDEF int stbi_write_tga(char const *filename, int w, int h, int comp, const void *data);
STBIWDEF int stbi_write_hdr(char const *filename, int w, int h, int comp, const float *data);
STBIWDEF int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
#endif

typedef void stbi_write_func(void *context, void *data, int size);

STBIWDEF int stbi_write_png_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const void *data, int stride_in_bytes);
STBIWDEF int stbi_write_bmp_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const void *data);
STBIWDEF int stbi_write_tga_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const void *data);
STBIWDEF int stbi_write_hdr_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const float *data);
STBIWDEF int stbi_write_jpg_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const void *data, int quality);

#define STBI_WRITE_NO_STDIO
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifdef __cplusplus
}
#endif

#endif//INCLUDE_STB_IMAGE_WRITE_H

