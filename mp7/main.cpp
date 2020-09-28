#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze m;
    m.drawCreative(100, 50);

    PNG* unsolved = m.drawMaze();
    delete unsolved;

    std::vector<int> sol = m.solveMaze();

    PNG* solved = m.drawMazeWithSolution();


    solved->writeToFile("creative.png");
    delete solved;
  
  return 0;
}
