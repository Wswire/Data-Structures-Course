/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include "dsets.h"
#include "cs225/PNG.h"
#include <unordered_map>

using namespace cs225;

class SquareMaze{
  public:
    SquareMaze ();

    void makeMaze (int width, int height);
    bool canTravel (int x, int y, int dir) const;
    void setWall (int x, int y, int dir, bool exists);
    vector<int> solveMaze ();
    cs225::PNG* drawMaze() const;
    cs225::PNG* drawMazeWithSolution();

    void drawCreative(int width, int height);

  private:
    int w;
    int h;
    int currX;
    int currY;
    std::vector<std::pair<bool, bool>> walls;
    DisjointSets sets;
    std::unordered_map<int, int> map;
};

#endif
