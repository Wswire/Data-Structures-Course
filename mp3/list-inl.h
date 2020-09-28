/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include <iostream>
#include <math.h>

template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  while (head_ != NULL){
    ListNode * temp = head_;
    head_ = head_->next;
    delete temp;
    length_--;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if (head_!= NULL){
    ListNode* e = new ListNode(ndata);
    e->next = head_;
    head_->prev = e;
    head_ = e;
    e = NULL; 
  }else{
    ListNode* e = new ListNode(ndata);
    head_ = e;
    tail_ = e;
    e = NULL;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if (tail_ !=NULL){
    ListNode *e = new ListNode(ndata);
    e->prev = tail_;
    tail_->next = e;
    tail_ = e;
  }else{
    ListNode* e = new ListNode(ndata);
    head_ = e;
    tail_ = e;
  }
  length_++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  ListNode* count = startPoint;
  ListNode * oriStart = startPoint;
  if (startPoint != NULL || endPoint != NULL || startPoint != endPoint){
//std::cout<<startPoint<<"   "<<endPoint<<std::endl;
//std::cout<<head_<<"   "<<tail_<<std::endl;
//std::cout<<length_<<std::endl;

  if (startPoint == head_ && endPoint == tail_){
    while (startPoint != endPoint){
      ListNode * temp = startPoint->prev;
      startPoint->prev = startPoint->next;
      startPoint->next = temp;
      startPoint = startPoint->prev;
    } 
    count = startPoint->prev;
    startPoint->prev = oriStart->next;
    startPoint->next = count;
    endPoint = oriStart;;
std::cout<<endPoint->next<<std::endl;
    head_ = startPoint;
    tail_ = endPoint;
  }else{ 
    while (startPoint != endPoint){
      ListNode * temp = startPoint->prev;
      startPoint->prev = startPoint->next;
      startPoint->next = temp;
      startPoint = startPoint->prev;
    }
    ListNode* temp = endPoint->next;
    count = startPoint->prev;
    startPoint->prev = oriStart->next;
    startPoint->next = count;
    endPoint = oriStart;
    if (temp != NULL){
      endPoint->next = temp;
      temp->prev = endPoint;
    }else{
      endPoint->next = NULL;
      tail_ = endPoint;
    }
    if (startPoint->prev != NULL){
      startPoint->prev->next = startPoint;
    }else{
      head_ = startPoint;
    }
  }
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  int ct = n;
  int i = 0;
  int remainder = length_%n;
  ListNode * startPoint = head_;
  ListNode * endPoint = head_;
  if (length_ != 0){
  while (i <(length_/n)){
    while (ct>1){
      endPoint = endPoint->next;
      ct--;
    }
    ListNode* temp = endPoint->next;
    reverse (startPoint, endPoint);

    startPoint = temp;
    endPoint = temp;
    ct = n;
    i++;
std::cout<<"whipped creme"<<std::endl;
    }
std::cout<<"gelato"<<std::endl;
    if (remainder >0){
      startPoint = tail_;
      endPoint = tail_;
      while (remainder>1){
        startPoint = startPoint->prev;
        remainder--;
      }
      reverse (startPoint, endPoint);
    }
std::cout<<"flan"<<std::endl;
  }
std::cout<<"sorbet"<<std::endl;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  int i = 0;
  ListNode * curr = head_;
  ListNode *temp = head_;
  if (length_>2){
  while (curr != tail_ || curr != NULL || curr!= tail_->prev){
//    curr = curr->next;
//    temp = curr;
//std::cout<<"flan"<<std::endl;
    if (curr != NULL){
      curr = curr->next;
    }
//std::cout<<"ice cream"<<std::endl;
    temp->next = temp->next->next;
//std::cout<<"tiramisu"<<std::endl;
    temp->next->prev = temp; 
    curr->next = NULL;
    curr->prev = tail_;
    tail_->next = curr;
    tail_ = curr;
    temp = temp->next;
    curr = temp;
  i++;
//std::cout<<i<<std::endl;
  if (i==length_-2)
    break;
  }
std::cout<<"donut"<<std::endl;

  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if (splitPoint ==0 )
    return start;
  ListNode * curr = start;
  for (int i =0 ;i<splitPoint; i++){
    curr = curr->next;
  }
  
  curr->prev->next = NULL;
  curr->prev = NULL;
  return curr;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (second == NULL)
    return first;
  if (first == NULL)
    return second;

  ListNode * curr = first;
  ListNode * curr2 = second;
  if (second->data < first->data){
    if (second->next != NULL)
        second = second->next;
      else
        second = NULL;
      curr2->next = curr;
      curr->prev = curr2;
      curr2->prev = NULL;
      curr2 = second;
      first = first->prev;
      curr = first;
  }

  while (second != NULL){
    if (curr ->next ==NULL){
      if (second->next != NULL)
            second = second->next;
        else
            second = NULL;        
        curr->next = curr2;
        curr2->prev = curr;
        curr2->next = NULL;
        curr2 = second;      
    }else if(curr2->data < curr->next->data){
      if (second->next != NULL)
            second = second->next;
          else
            second = NULL;
          curr2->prev = curr;
          curr2->next = curr->next;
          curr->next = curr2;
          curr2->next->prev = curr2;
          curr2 = second;
    }else{
      curr = curr->next;
    }
  }
return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1)
    return start;
  
  int restLength = 0;
  int halfLength = chainLength/2;
  if (chainLength%2 == 0)
    restLength = halfLength;
  else
    restLength =  halfLength +1;

  ListNode * splitNode = split(start, halfLength);
  splitNode = mergesort(splitNode, restLength);
  start = mergesort(start, halfLength);
  return merge(start, splitNode);
}
