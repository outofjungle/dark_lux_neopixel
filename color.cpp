#include "Arduino.h"
#include "color.h"

float Min(float r, float g, float b) {
  float result;
  result = min(r, g);
  result = min(result, b);
}

float Max(float r, float g, float b) {
  float result;
  result = max(r, g);
  result = max(result, b);
}

void getHSV(color *c) {
  float r, g, b, minimum, maximum, delta;

  r = c->r / 255;
  g = c->g / 255;
  b = c->b / 255;

  minimum = Min(r, g, b);
  maximum = Max(r, g, b);
  c->v = maximum;
  delta = maximum - minimum;

  if (maximum != 0) {
    c->s = delta / maximum;
  } else {
    c->s = 0;
    c->h = -1;
    return;
  }

  if (r == maximum) {
    c->h = (g - b) / delta;
  } else if (g == maximum) {
    c->h = 2 + (b - r) / delta;
  } else {
    c->h = 4 + (r - g) / delta;
    c->h *= 60;
  }

  if (c->h < 0) {
    c->h += 360;
  }
}

void getRGB(color *c) {
  int i;
  float f, p, q, t;
  if (c->s == 0) {
    c->r = c->g = c->b = c->v;
    return;
  }

  c->h /= 60;
  i = floor(c->h);

  f = c->h - i;
  p = c->v * (1 - c->s);
  q = c->v * (1 - c->s * f);
  t = c->v * (1 - c->s * (1 - f));

  switch (i) {
    case 0:
      c->r = c->v;
      c->g = t;
      c->b = p;
      break;
    case 1:
      c->r = q;
      c->g = c->v;
      c->b = p;
      break;
    case 2:
      c->r = p;
      c->g = c->v;
      c->b = t;
      break;
    case 3:
      c->r = p;
      c->g = q;
      c->b = c->v;
      break;
    case 4:
      c->r = t;
      c->g = p;
      c->b = c->v;
      break;
    default:
      c->r = c->v;
      c->g = p;
      c->b = q;
      break;
  }
}
