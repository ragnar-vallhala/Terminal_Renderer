
#include "image.h"
#include "loadimage.h"
#include "image2ascii.h"
#include <iostream>

int main (int argc, char *argv[]) {
  std::cout<<"Image Path: "<<argv[1]<<std::endl;
  Image *img = new Image();
  loadimage(argv[1],img);

  std::cout<<img->channel<<std::endl;
  Image* dst = image2ascii(img);
 /* for(int i{};i<dst->height;i++)
  {
    for(int j{};j<dst->width;j++)
    {
      std::cout<<dst->matrix[i*dst->width+j];
    }
      std::cout<<std::endl;
  }*/
  delete dst;
  freeimage(img);
  delete img;

  return 0;
}
