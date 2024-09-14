#include "image2ascii.h"

Image* image2ascii(Image *img, size_t width, size_t height, std::string ascii)
{
  Image *dst = new Image(img->width, img->height, img->channel);
  int n = ascii.length();
  unsigned char* srcmat = img->matrix;
  unsigned char* dstmat = dst->matrix;
  int divider = 255/n;
  for(int i{};i<img->width*img->height*img->channel;i++)
  {
    unsigned char value = srcmat[i]/divider;
    if(value>=ascii.length()) value = ascii.length();
    dstmat[i] = ascii[value];
  }
  return dst;
}
