#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance):toler(tolerance), start(start), png(png) {  
  /** @todo [Part 1] */
  dfs.push(start);
  visited = new bool *[png.height()];
  for (unsigned int i = 0; i< png.height(); i++){
    visited[i] = new bool[png.width()];
  }
  for (unsigned int x = 0; x< png.height();x++){
    for (unsigned int y = 0; y< png.width(); y++){
      visited[x][y] = false;
    }
  }
}

DFS::~DFS(){
  for (unsigned int i =0; i< png.height(); i++){
     delete[] visited[i]; visited[i] = NULL;
  }
  delete[] visited; visited = NULL;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS * dfsItBegin = new DFS (png, start, toler);
  return ImageTraversal::Iterator(dfsItBegin);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();

}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */

  double delta = 0.0;
if (point.x +1 < png.width()){ 
  delta = calculateDelta(png.getPixel(start.x, start.y), png.getPixel(point.x+1, point.y));
  if (!visited[point.y][point.x +1] && delta<toler){
    Point p2(point.x, point.y);
    p2.x = p2.x +1;
    dfs.push(p2);
  }
}

if (point.y +1 < png.height()){
  delta = calculateDelta(png.getPixel(start.x, start.y), png.getPixel(point.x, point.y+1));
  if (!visited[point.y+1][point.x] && delta<toler){
    Point  p3 (point.x, point.y);
    p3.y = p3.y+1;
    dfs.push(p3);

  }
}

if (point.x != 0){
  delta = calculateDelta(png.getPixel(start.x, start.y), png.getPixel(point.x-1, point.y));
  if (!visited[point.y][point.x-1] && delta<toler){
    Point p4(point.x, point.y);
    p4.x = p4.x-1;
    dfs.push(p4);

  }
}

if (point.y != 0){
  delta = calculateDelta(png.getPixel(start.x, start.y), png.getPixel(point.x, point.y-1));
  if (!visited[point.y-1][point.x] && delta<toler){
    Point p5(point.x, point.y);
    p5.y = p5.y-1;
    dfs.push(p5);
  }
}
}
/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point result = dfs.top();
  dfs.pop();
  while (!dfs.empty()){
    if (result == dfs.top())
      dfs.pop();
    else
      break;
  }
  while (visited[result.y][result.x]){
    if (!dfs.empty()){
      result = dfs.top();
      dfs.pop();
    }else 
      break;
  }
 
  if (dfs.empty())
    if (visited[result.y][result.x])
      return Point(9999999, 9999999);

    visited[result.y][result.x] = true;
  return result;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
     return dfs.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return dfs.empty();
}
