/* Your code here! */

#include "maze.h"
#include <iostream>
#include "dsets.h"
#include <stdlib.h>
#include <time.h>
#include <queue>

using std::queue;
using std::pair;
using std::vector;
using cs225::HSLAPixel;
using cs225::PNG;

SquareMaze::SquareMaze(){
  w = 0;
  h = 0;
  currX = 0;
  currY = 0;
}

void SquareMaze::makeMaze(int width, int height){
  w = width;
  h = height;

 std::cout<<w<<std::endl;

  sets.setVec.erase(sets.setVec.begin(), sets.setVec.end());    //clear existing maze
  sets.addelements (w*h);

  for (int i = 0; i <(w*h) ;i++){
    pair<bool, bool> p(true, true);                  //make all walls true
    walls.push_back(p);                              //this is a vector of bool bool pairs to keep track of right  and bottom walls
  }

  int randnum = 0;
  for (int j =0; j<(w*h)*10; j++){            // (w*h)*10 to make sure the randomness removes all the walls it possibly can
      size_t i = (rand()%(w*h));
      randnum = (rand() % 2);
      if (randnum == 0  &&  i%w !=(size_t)w-1  &&  sets.find(i) != sets.find(i+1)){            //delete right wall without creating cycles
        this->setWall (i%w, i/w, randnum, false);
        sets.setunion(i, i+1);
      }else if (randnum == 1  &&  i/w != (size_t)h-1 &&  sets.find(i) != sets.find(i+w)){      // delete bottom w/o cycles
        this->setWall (i%w, i/w, randnum, false);
        sets.setunion(i, i+w);
      }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
if ((x == 0 && dir == 2) || (x == w-1 && dir == 0) || (y == 0 && dir == 3) || (y == h-1 && dir == 1))
  return false;            //cant delete edges of maze

if (x<w  &&  y<h && y>=0 && x>=0){
  if (dir == 0){
    if (walls[(y*w)+x].first == false)
      return true;
    else
      return false;
  }else if (dir == 1){
    if (walls[(y*w)+x].second == false)
      return true;
    else
      return false;
  }else if(dir == 2){
    if (walls[(y*w)+x-1].first == false)
      return true;
    else 
      return false;
  }else{
    if (walls[(y*w)+x-w].second == false)
      return true;
    else
      return false;
  }
}else
  return false;
}

void SquareMaze::setWall (int x, int y, int dir, bool exists){
  if (x<w && y<h && x>=0 && y>=0){                        // within maze bounds
    if (dir == 0)
      walls[(y*w)+x].first = exists;
    else if (dir == 1)
      walls[(y*w)+x].second = exists;
  }
}

vector<int> SquareMaze::solveMaze(){
 std::cout<<"solveMaze begin"<<std::endl;

  currX = 0;
  currY = currX/w;
  queue<int> q;                 //Queue for BFS
  vector<bool> visited;         //to make sure we arent visiting the same nodes twice
  for (int i = 0; i<w*h; i++)
    visited.push_back(false);

  q.push(0);
  visited[0] = true; 

  while (!q.empty()){
    int curr = q.front();
    q.pop();
    for (int i =0; i<4; i++){
      if (canTravel(curr%w, curr/w, i)){            //if we can travel to a node that has not been visited, then map its parents and push it on the queue
//std::cout<<"heyo"<<std::endl;
        if (i == 0 && visited[curr+1] == false){
          map[curr+1] = curr;
          q.push(curr+1);
          visited[curr+1] = true;
        }
        if (i ==1 && visited[curr+w] == false){
          map[curr+w] = curr;
          q.push(curr+w);
          visited[curr+w] = true;
        }
        if (i ==2 && visited[curr-1] == false){
          map[curr-1] = curr;
          q.push(curr-1);
          visited[curr-1] = true;
        }
        if (i ==3 && visited[curr-w] == false){
          map[curr-w] = curr;
          q.push(curr-w);
          visited[curr-w] = true;
        }
      }
    }
  }


  int best = 0;
  int idx = 0;
  for (int i = w*(h-1); i<(w*h); i++){
    int curr = i;
    int ct = 0;
    while (curr != 0){         //follow the map of each nodes parent starting from the end node, this gives the shortest path to the start node.
      ct++;
      curr = map[curr];
//      if (curr != 0)
//        std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;
    }
    if (ct > best){          //update best route
      best = ct;
      idx = i;
    }
  }

  vector<int> path;              //push path taken into vector form
  int parent = idx;
  while (parent != 0){
    int temp = parent;
    parent = map[parent];
    if (parent == temp+1)
      path.push_back (2);
    else if (parent == temp-1)
      path.push_back(0);
    else if (parent == temp +w)
      path.push_back(3);
    else if (parent == temp-w)
      path.push_back(1);
  }

 std::cout<<path.size()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
 std::cout<<sets.setVec.size()<<std::endl;
 std::cout<<map.size()<<std::endl;

 vector<int> rpath;                                         //reverse vector order
  for (vector<int>::reverse_iterator it = path.rbegin(); it!=path.rend(); it++){
    rpath.push_back(*it);
  }
  return rpath;
}

PNG* SquareMaze::drawMaze() const{
 std::cout<<"drawMaze begin"<<std::endl;

  PNG* png = new PNG(w*10+1, h*10+1);
  for (unsigned int i = 0; i<png->width(); i++){                     //set top row to black pixels
    HSLAPixel& pix = png->getPixel(i, 0);
    pix.l  = 0;
//std::cout<<"1"<<std::endl;

  }
  for (unsigned int i = 0; i<png->height(); i++){                    // set left column to black pixels
    HSLAPixel& pix = png->getPixel(0, i);
    pix.l  = 0;
// std::cout<<"2"<<std::endl;
  }
  for (unsigned int i = 1; i<10; i++){                               //set entrance to white pix
    HSLAPixel& pix = png->getPixel(i, 0);
    pix.l  = 1;
// std::cout<<"3"<<std::endl;

  }

  for (size_t i = 0; i< walls.size(); i++){
    if (walls[i].first == true){                                     //right wall exists
      for (int k = 0; k<=10; k++){     
        HSLAPixel& pix = png->getPixel(((i%w)+1)*10, (i/w)*10 +k);
        pix.l = 0;
      }
    }
    if (walls[i].second == true){
      for (int k = 0; k<=10; k++){
        HSLAPixel& pix = png->getPixel((i%w)*10+k, ((i/w)+1)*10);
        pix.l = 0;
      }
    }
  }
 std::cout<<"drawMaze end"<<std::endl;
  return png;
}

PNG* SquareMaze::drawMazeWithSolution(){
 std::cout<<"drawMazewithSoln begin"<<std::endl;


  vector<int> soln = solveMaze();                           //get vector of soln
// std::cout<<soln.size()<<std::endl;
  PNG* png = drawMaze();
  currX = 5;
  currY = 5;
   
  for (vector<int>::iterator x = soln.begin(); x != soln.end(); x++){      //for each index of vector, draw the path in red
    if (*x == 0){
      for (int i = 0; i<=10; i++){
        HSLAPixel& pix = png->getPixel(currX, currY);
        pix.h = 0;
        pix.s = 1;
        pix.l = 0.5;
        pix.a = 1;
        currX++;
      }
      currX--;
    }else if (*x == 1){
      for (int i = 0; i<=10; i++){
        HSLAPixel& pix = png->getPixel(currX, currY);
        pix.h = 0;
        pix.s = 1;
        pix.l = 0.5;
        pix.a = 1;
        currY++;
      }
      currY--;
    }else if (*x == 2){
      for (int i = 0; i<=10; i++){
        HSLAPixel& pix = png->getPixel(currX, currY);
        pix.h = 0;
        pix.s = 1;
        pix.l = 0.5;
        pix.a = 1;
        currX--;
      }
      currX++;
    }else if (*x == 3){
      for (int i = 0; i<=10; i++){
        HSLAPixel& pix = png->getPixel(currX, currY);
        pix.h = 0;
        pix.s = 1;
        pix.l = 0.5;
        pix.a = 1;
        currY--;
      }
      currY++;
    }
  }
  for (int i = 1; i<10; i++){                              //create opening at end of the maze
    HSLAPixel& pix = png->getPixel((currX/10)*10+i, (h-1+1)*10);
    pix.l  = 1;
  }
  
  return png;
}


void SquareMaze::drawCreative(int width, int height){
  w = width;
  h = height;

 std::cout<<w<<std::endl;

  sets.setVec.erase(sets.setVec.begin(), sets.setVec.end());    //clear existing maze
  sets.addelements (w*h);

  for (int i = 0; i <(w*h) ;i++){
    pair<bool, bool> p(true, true);                  //make all walls true
    walls.push_back(p);                              //this is a vector of bool bool pairs to keep track of right  and bottom walls
  }

  int randnum = 0;
  for (int j =0; j<(w*h)*20; j++){            // (w*h)*10 to make sure the randomness removes all the walls it possibly can
      size_t i = (rand()%(w*h));
      randnum = (rand() % 2);
      if (randnum == 0  &&  i%w !=(size_t)w-1  &&  sets.find(i) != sets.find(i+1)){            //delete right wall without creating cycles
        this->setWall (i%w, i/w, randnum, false);
        sets.setunion(i, i+1);
      }else if (randnum == 1  &&  i/w != (size_t)h-1 &&  sets.find(i) != sets.find(i+w)){      // delete bottom w/o cycles
        this->setWall (i%w, i/w, randnum, false);
        sets.setunion(i, i+w);
      }
  }
  
}

