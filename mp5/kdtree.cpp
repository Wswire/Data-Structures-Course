/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <array>
#include <utility>
#include <algorithm>
#include <cmath>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
  if (first[curDim] <= second[curDim])
    return true;
  else
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
  
  double currDis = 0;
  double potDis = 0;
 
  for (int i = 0; i<Dim ; i++){
    currDis += pow(target[i] - currentBest[i], 2); // sum of squares
  }

  for (int i = 0; i<Dim ; i++){
    potDis += pow(target[i] - potential[i], 2);
  }

  if (abs(currDis) > abs(potDis))
    return true;
  else if( abs(currDis) == abs(potDis))
    return (potential<currentBest);  //break with <
  else
     return false;
}

template <int Dim>
int KDTree<Dim>::partition (vector<Point<Dim>>& newPoints, int start, int end, int dim){
//cout<<"partition:  "<<start<<"   "<<end<<"  "<<dim<< endl;

  double pivot = newPoints[start][dim];  //point to be pivot
  int storeIndex = start;

  Point<Dim> temp = newPoints[start];  // swap point to end of array
  newPoints[start] = newPoints[end];
  newPoints[end] = temp;

  for(int i = start; i < end ;i++){
    if (newPoints[i][dim] < pivot){
      Point<Dim> temp = newPoints[storeIndex];  //All points less than pivot on left and larger points on right
      newPoints[storeIndex] = newPoints[i];
      newPoints[i] = temp;
      storeIndex++;
    }
  }
  temp = newPoints[storeIndex]; // final swap
  newPoints[storeIndex] = newPoints[end];
  newPoints[end] = temp;
  return storeIndex;
}


template <int Dim>
Point <Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& newPoints, int start, int end, int median_idx, int dim){
  
//cout<<"quickselect:  "<<start<<"   "<<end<<"  "<<dim<<"                    "<<median_idx<< endl;

  if (start == end)
    return newPoints[start];   //called on only one index val

//cout<<"old:   "<<newPoints[median_idx]<<endl;
  int idx = partition (newPoints, start, end, dim);
//cout<<"new:   "<<newPoints[median_idx]<<endl;
//cout<<"       "<<endl;

  if (idx == median_idx)  //the spot we want is sorted with smaller points to the left and larger to the right
    return newPoints[median_idx];
  else if (median_idx < idx)      // the spot we want is less than pivot
    return quickSelect(newPoints, start, idx-1, median_idx, dim);  // call again on smaller subset of array
  else
    return quickSelect(newPoints, idx+1, end, median_idx, dim); 
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::helper(vector<Point<Dim>>& copy, int start, int end, int dimCount){

//cout<<"33333333333333333333333333333333    "<<start<<"    "<<end<<endl;
  KDTreeNode* newNode = new KDTreeNode();
  if (start>end)  //doesnt make sense to call if start>end
    return NULL;
 
  if (dimCount > Dim-1)  //makes sure dimCount is never greater than Dim
    dimCount = 0;
  int middle = floor((end +start)/2);

  if (start == end){  //One index, so there is no right or left child
//cout<<"start==end   "<<start<<endl;
    newNode->point = copy[start];
    newNode->left = NULL;
    newNode->right = NULL; 
    return newNode;
  }else{
    newNode->point = quickSelect(copy, start, end, middle, dimCount);  //finds the value that should be in median
    newNode->left = helper (copy, start, middle -1, dimCount+1);  // calls on left child to make left branch of tree, same idea for the right tree
//cout<<"IN BETWEEN LEFT AND RIGHT    "<<start<<"    "<<end<<endl;

    newNode->right = helper (copy, middle+1, end, dimCount+1);
    return newNode;
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
 *      * @todo Implement this function!
 *           */


  if (newPoints.size() == 0){
    size = 0;
    root = NULL;
  }else{
    vector<Point<Dim>> copy;
    copy.assign(newPoints.begin(), newPoints.end());   // copy bc original is const
    size = newPoints.size();
    root = helper(copy, 0, newPoints.size()-1, 0);  // calls helper functions for recursion
  }
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  if (other.size == 0){
    size = 0;
    root = NULL;
  }
  size = other.size;
  root = copyHelper(other.root);  //copy tree
  
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copyHelper (KDTreeNode *& subroot){
  KDTreeNode* newNode = new KDTreeNode;

  if (subroot==NULL)
    return NULL;
  newNode->point = subroot->point;
  newNode->left = copyHelper(subroot->left);
  newNode->right = copyHelper(subroot->right);  //recurse to make deep copy

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs){
    clear(this->root);          //delete and copy
    KDTree<Dim> treeCopy(rhs);
    this->root = treeCopy.root;
    this->size = treeCopy.size;
  }

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree(){
  /**
   * @todo Implement this function!
   */
 clear(root);
}

template<int Dim>
void KDTree<Dim>::clear(KDTreeNode *& subroot){
  if (subroot == NULL)                 //delete tree
    return;
  clear(subroot->left);
  clear(subroot->right);
  if (subroot != NULL)
    delete subroot;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
  if (root == NULL)
    return Point<Dim>();

  Point<Dim> currBest = root->point;
  if (root->point == query)
    return root->point;
  else
    return findNearestHelper(root, query, currBest, 0);   //helper for recusion
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestHelper(KDTreeNode* subroot, const Point<Dim>& query, Point<Dim> currBest, int dimCount) const{
  bool flag = true;
  if (dimCount > Dim-1)
    dimCount = 0;

  if (subroot->left == NULL && subroot->right == NULL){  //leaf case, check if this is the closest pt
//    cout<<"NULL CASE   "<<shouldReplace(query, currBest, subroot->point)<<endl;
//    cout<<subroot->point<<endl;
//    cout<<currBest<<endl;

    if (shouldReplace(query, currBest, subroot->point))
      currBest = subroot->point;
//    cout<<currBest<<endl;
    return currBest;
  }

//  Point<Dim> test = query;
//  test[dimCount] = subroot->point[dimCount];

  if (smallerDimVal(query, subroot->point, dimCount)){  // check for if we want to go left or right
    if (subroot->left != NULL){
      flag = true;
      currBest = findNearestHelper(subroot->left, query, currBest, dimCount+1);  // go left

    if(shouldReplace(query, currBest, subroot->point))  // check if node on the way back is closer than closest
      currBest = subroot->point;

    double radius = 0;                        //Check if a line intersects the current radius
    for (int i = 0; i<Dim ; i++){
      radius += pow(query[i] - currBest[i], 2);
    }
    radius = sqrt(radius);
    

    if (abs(subroot->point[dimCount]-query[dimCount]) <= radius){  // if a line intersects than go into that subtree
//  if (shouldReplace(query, subroot->point, test)){
      if (subroot->right != NULL)
        currBest = findNearestHelper(subroot->right, query, currBest, dimCount+1);
      }

    }
  }else{
    if(subroot->right != NULL){         //same format as going into left
      flag = false;
//cout<<"entering right"<<endl;
      currBest = findNearestHelper(subroot->right, query, currBest, dimCount+1);
//cout<<"exiting right"<<endl;
//cout<<subroot->point<<endl;
//cout<<currBest<<endl;
     if(shouldReplace(query, currBest, subroot->point))
       currBest = subroot->point;
//cout<<currBest<<endl;

     double radius = 0;
     for (int i = 0; i<Dim ; i++){
       radius += pow(query[i] - currBest[i], 2);
      }
     radius = sqrt(radius);

     if (abs(subroot->point[dimCount]-query[dimCount]) <= radius){
//   if(shouldReplace(query, subroot->point, test)){
       if (subroot->left != NULL)
         currBest = findNearestHelper(subroot->left, query, currBest, dimCount+1);
     }
    }
  }

  if(shouldReplace(query, currBest, subroot->point))  //check if root is closest
    currBest = subroot->point;

  return currBest;
}




