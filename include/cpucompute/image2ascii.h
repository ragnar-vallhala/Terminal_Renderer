#ifndef IMAGE2ASCII_H
#define IMAGE2ASCII_H
#include "image.h"
#include <string>

Image* image2ascii(Image *img, size_t width=-1, size_t height=-1, std::string ascii=" .-+:*%#@");

#endif // !IMAGE2ASCII_H
