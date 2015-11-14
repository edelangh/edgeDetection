#pragma once

#include "img2.h"

#ifdef __cplusplus
extern "C" {
#endif
t_img2*		img2_load_raw(const char* src, int width, int height, int bpp);

#ifdef __cplusplus
}
#endif