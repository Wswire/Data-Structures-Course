#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);
  MyColorPicker(double hue, double sat, double lum, double inc, double inc2);
private:
  double hue;
  double sat;
  double lum;
  double inc;
  double inc2;
};

#endif
