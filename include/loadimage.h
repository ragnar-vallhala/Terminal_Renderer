
#ifndef LOADIMAGE_H
#define LOADIMAGE_H
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "image.h"
#endif
void loadimage(const char* path, Image *img);
void freeimage(Image* img);
#endif // !LOADIMAGE_H


