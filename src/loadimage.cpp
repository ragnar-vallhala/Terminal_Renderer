#include "loadimage.h"
void loadimage(const char* path, Image *img)
{
  int height{},width{},channel{};
  img->matrix = stbi_load(path,&width,&height,&channel,0);
  img->height = height;
  img->width = width;
  img->channel = channel;
  assert(img->matrix!=nullptr);
}

void freeimage(Image* img)
{
  stbi_image_free(img->matrix);
}


