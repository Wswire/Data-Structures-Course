#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(double hue, double sat, double lum, double inc, double inc2): hue(hue), sat(sat), lum(lum), inc(inc), inc2(inc2){
} 

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pix (hue, sat, lum );
  hue += inc;
  sat += inc2;
  
  if (sat==1)
    sat -= 0.6;

  return pix;
}
