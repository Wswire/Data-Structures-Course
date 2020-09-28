/* Your code here! */

#include <iostream>
#include "dsets.h"

void DisjointSets::addelements (int num){
  for (int i = 0; i<num; i++){
    setVec.push_back(-1);
  }
}

int DisjointSets::find (int elem){
  if (setVec[elem] < 0)
    return elem;
  else{  
    setVec[elem] = find(setVec[elem]);
    return setVec[elem];
  }
}

void DisjointSets::setunion (int a, int b){
  int sizeA = (setVec[find(a)]);
  int sizeB = (setVec[find(b)]);

  if (find(a) == find(b))
    return;

  if (sizeA < sizeB){                          //equal case?????
    setVec[find(b)] = find(a);
    setVec[find(a)] = (sizeA + sizeB);
  }else{
    setVec[find(a)] = find(b);
    setVec[find(b)] = (sizeA + sizeB);
  }
}

int DisjointSets::size (int elem){
  return setVec[find(elem)];
}
