#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma;
  alma.cs225::PNG::readFromFile("alma.png");
  Image cpp;
  cpp.cs225::PNG::readFromFile("cpp_logo.png");
  Image I;
  I.cs225::PNG::readFromFile("i.png");
  Image tests;
  tests.cs225::PNG::readFromFile("alltestspass.png");

  StickerSheet sheet(alma,4);
  cpp.scale(0.3);
  sheet.addSticker(cpp, 0,0);
  sheet.addSticker(tests, 200,500);
  sheet.addSticker(I, 650,100);

  Image result = sheet.render();
  result.writeToFile("myImage.png");
 
  return 0;
}
