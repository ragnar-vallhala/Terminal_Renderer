#ifndef IMAGE_H
#define IMAGE_H
#include <cstddef>
#include <cstdlib>
typedef struct Image {
  size_t height;
  size_t width;
  size_t channel;
  unsigned char* matrix;
  Image()=default;
  Image(size_t height, size_t width, size_t channel, unsigned char* matrix)
  {
    height = height;
    width = width;
    channel = channel;
    matrix = matrix;
  }

  Image(size_t height, size_t width, size_t channel)
  {
    matrix = (unsigned char*) malloc(height*width*channel*sizeof(unsigned char));
  }
  ~Image()
  {
    if(matrix!=nullptr) free(matrix);
  };
} Image;

#endif // !IMAGE_H
//




