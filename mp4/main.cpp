
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG png;
  png.readFromFile("gengar.png");

  FloodFilledImage image(png);

  DFS dfs(png, Point(180, 110), 0.1);
  BFS bfs (png, Point(210, 180), 0.1);
  BFS bfs2 (png, Point(150, 180), 0.1);
  
  HSLAPixel color(260, 0.4, 0.21);
  SolidColorPicker solid (color);

  MyColorPicker mine(220, 0.41, 50, 10, 0.1);

  image.addFloodFill(dfs, solid);
  image.addFloodFill(bfs, mine);
  image.addFloodFill(bfs2, mine);
 
  Animation animation = image.animate(1500);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
