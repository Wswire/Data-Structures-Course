
#include "StickerSheet.h"
#include <iostream>
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

StickerSheet::StickerSheet( const Image &picture, unsigned max){
  max_ = max;
  count = 1;
  basepic_ = new  Image *[max]; //layers
  xAxis_ = new int [max]; // corresponding x,y coordinates of image at any given index
  yAxis_ = new int [max];

  for (unsigned int i =0; i<max_;i++){
    basepic_[i]= NULL;
    xAxis_[i] = 0;
    yAxis_[i] = 0;
  }
  Image * temp = new Image();
  *temp = picture;
  basepic_[0] = temp;
std::cout<<"Apple Pie"<<endl;
}


StickerSheet::~StickerSheet(){
  clear();
}


StickerSheet::StickerSheet(const StickerSheet &other): count(other.count), max_(other.max_){
  basepic_ = new Image* [other.max_];
  xAxis_ = new int [other.max_];
  yAxis_ = new int [other.max_];
std::cout<<"cinnamon bun"<<endl;
  for (unsigned int i =0; i<other.max_;i++){
    if (other.basepic_[i] != NULL){
    basepic_[i] = new Image (*other.basepic_[i]);
    xAxis_[i] = other.xAxis_[i];
    yAxis_[i] = other.yAxis_[i];
    }
  }
std::cout<<"cinnamon bun"<<endl;

}


void StickerSheet::clear(){
  for (unsigned int i = 0; i<count; i++){
    if (basepic_[i] != NULL){
    delete basepic_[i]; basepic_[i] = NULL;
    }
  }
  delete[] basepic_; basepic_= NULL;
  delete[] xAxis_; xAxis_ = NULL;
  delete[] yAxis_; yAxis_ = NULL;

}


void StickerSheet::copy(const StickerSheet &other){
  max_ = other.max_;
  count = other.count;
  basepic_ = new  Image* [other.max_];
  xAxis_ = new int [other.max_];
  yAxis_ = new int [other.max_];
std::cout<<"boston creme pie"<<endl;
  for (unsigned int i =0; i<other.count;i++){
    basepic_[i] = new Image (*other.basepic_[i]);
    xAxis_[i] = other.xAxis_[i];
    yAxis_[i] = other.yAxis_[i];
  }

}


const StickerSheet& StickerSheet::operator=(const StickerSheet &rhs){
std::cout<<"blueberry tart"<<endl;
  if(this == &rhs){
    return *this;
  }
  clear();
  copy(rhs);
  return *this;
}


void StickerSheet::changeMaxStickers(unsigned max){
  max++;
  Image ** arr = new Image* [max];
  int * tempx = new int [max]; // corresponding x,y coordinates of image at any given index
  int * tempy = new int [max];
  int ct = 0;
  for (unsigned int i =0; i<max;i++){
    arr[i]= NULL;
    tempx[i] = 0;
    tempy[i] = 0;
  }

  if (max<count){
  for (unsigned int i =0; i<max; i++){
    if(basepic_[i] != NULL){
    arr[i] = basepic_[i];
    tempx[i] = xAxis_[i];
    tempy[i] = yAxis_[i];
    ct++;
    }
  }
  }else{
    for (unsigned int i =0; i<count; i++){
    if(basepic_[i] != NULL){
    arr[i] = basepic_[i];
    tempx[i] = xAxis_[i];
    tempy[i] = yAxis_[i];
    ct++;
    }
  }
  }
  delete[] basepic_; this->basepic_ = arr;
  delete[] xAxis_; xAxis_ = tempx;
  delete[] yAxis_; yAxis_ = tempy;
  max_ = max;
  count = ct;
}


int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
std::cout<<"chocolate cake"<<endl;
  Image * temp3 = new Image();
  *temp3 = sticker;

  if (count <= max_){
    basepic_[count] = temp3;
    this->xAxis_[count] = x;
    this->yAxis_[count] = y;
    count++;
    return count-1;
  }else{
    return -1;
  }
}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  index++;
  if (index >max_|| index > count-1){
    return false;
  }else{
    this->xAxis_[index] = x;
    this->yAxis_[index] = y;
    return true;
  }
}


void StickerSheet::removeSticker(unsigned index){
  index++;
  if (basepic_[index] != NULL){
    delete basepic_[index]; basepic_[index] = NULL;
    xAxis_[index]=0;
    yAxis_[index]=0;
  }
}


Image* StickerSheet::getSticker(unsigned index) const{
  index++;
  if (basepic_[index] == NULL){
    return NULL;
  }else{
    return basepic_[index];
  }
}


Image StickerSheet::render() const{
  Image render;
  unsigned int rendW = 0;
  unsigned int rendH = 0;
  for (unsigned int i =0; i<count; i++){
    if(basepic_[i] == NULL){std::cout<<"brownies"<<endl;}
    if (basepic_[i] != NULL){
    Image sticker = *basepic_[i];
    int x = xAxis_[i];
    int y = yAxis_[i];
std::cout<<sticker<<endl;
std::cout<<sticker.height()<<endl;
std::cout<<sticker.width()<<endl;
    if(sticker.width()+x > rendW){
      rendW = sticker.width()+x;
    }
    if(sticker.height()+y > rendH){
      rendH = sticker.height()+y;
    }
    }
  }

  render.resize(rendW, rendH);

  for (unsigned int i =0; i<count; i++){
    if (basepic_[i] == NULL){ std::cout<<"sugar plum"<<endl;} //deref NULL check
    if (basepic_[i] != NULL){

    Image sticker = *basepic_[i];
    int x = xAxis_[i];
    int y = yAxis_[i];

std::cout<<"candied apple"<<endl;

    for (unsigned int j =0; j<sticker.height(); j++){
    for (unsigned int i =0; i<sticker.width(); i++){
      cs225::HSLAPixel* rendPix = &render.getPixel(x,y);
      cs225::HSLAPixel* stickPix = &sticker.getPixel(i,j);
      if (rendPix == NULL || stickPix == NULL){std::cout<<"New York Cheescake"<<endl;}
      if (stickPix->a != 0 && rendPix != NULL && stickPix != NULL){
        *rendPix = *stickPix;
      }
      x++;
    }
    y++;
    x = xAxis_[i];
    }
    y = yAxis_[i];
    }
  }
  return render;
}














