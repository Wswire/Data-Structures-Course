#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance): toler(tolerance), start(start), png(png) {  
  /** @todo [Part 1] */
  bfs.push (start);
  visited = new bool *[png.height()];
  for (unsigned int i = 0; i< png.height(); i++){
    visited[i] = new bool[png.width()];
  }

  for (unsigned int y = 0; y< png.height(); y++){
    for (unsigned int x = 0; x< png.width(); x++){
      visited[y][x] = false;
    }
  }
  visited[start.y][start.x] = true;
}

BFS::~BFS(){
  for (unsigned int i =0; i< png.height(); i++){
     delete[] visited[i]; visited[i] = NULL;
  }
  delete[] visited; visited = NULL;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS* bfsItBegin = new BFS(png, start, toler);
  return  ImageTraversal::Iterator(bfsItBegin);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  double delta = 0.0;

if (point.x +1 < png.width()){
  delta = calculateDelta(png.getPixel(start.x, start.y), png.getPixel(point.x+1, point.y));
  if (!visited[point.y][point.x+1] && delta<toler){
    Point p2(point.x, point.y);
    p2.x = p2.x +1;
    bfs.push(p2);
    visited[point.y][point.x+1] = true;
  }
}

if (point.y +1 < png.height()){
  delta = calculateDelta(png.getPixel(start.x, start.y), png.getPixel(point.x, point.y+1));
  if (!visited[point.y+1][point.x] && delta<toler){
    Point p3(point.x, point.y);
    p3.y = p3.y+1;
    bfs.push(p3);
    visited[point.y+1][point.x] = true;
  }
}

if (point.x != 0){
  delta = calculateDelta(png.getPixel(start.x, start.y), png.getPixel(point.x-1, point.y));
  if (!visited[point.y][point.x-1] && delta<toler){
    Point p4 (point.x, point.y);
    p4.x = p4.x-1;
    bfs.push(p4);
    visited[point.y][point.x-1] = true;
  }
}

if (point.y != 0){
  delta = calculateDelta(png.getPixel(start.x, start.y), png.getPixel(point.x, point.y-1));
  if (!visited[point.y-1][point.x] && delta<toler){
    Point p5(point.x, point.y);
    p5.y = p5.y-1;
    bfs.push(p5);
    visited[point.y-1][point.x] = true;
  }
}
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point result = bfs.front();
  bfs.pop();
  visited[result.y][result.x] = true;
 
  return result;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return bfs.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return bfs.empty();
}
