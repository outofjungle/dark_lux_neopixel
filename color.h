#ifndef COLOR_H_
#define COLOR_H_
#include <stdint.h>

typedef struct color {
  uint32_t r;
  uint32_t g;
  uint32_t b;
  float h;
  float s;
  float v;
};

void getHSV(color *);
void getRGB(color *);

#endif  // COLOR_H_
