#include <iostream>
#include "math.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

void Image::lighten(){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      if (pix.l <=0.9){
	pix.l += 0.1; 
      }else{
	pix.l = 1.0;
      }
    }
  }
}

void Image::lighten(double amount){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      if (pix.l+amount<=1){
        pix.l += amount;
      }else{
	pix.l = 1.0;
      }
    }
  }
}

void Image::darken(){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      if (pix.l >=0.1){
        pix.l -= 0.1;
      }else{
	pix.l = 0.0;
      }
    }
  }
}

void Image::darken(double amount){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      if (pix.l-amount>=0.0){
        pix.l -= amount;
      }else{
	pix.l = 0.0;
      }
    }
  }
}

void Image::saturate(){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      if (pix.s <= 0.9){
        pix.s += 0.1;
      }else{
        pix.l = 1.0;
      }
    }
  }
}

void Image::saturate(double amount){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      if (pix.s+amount <= 1.0){
        pix.s += amount;
      }else{
	pix.s = 1.0;
      }
    }
  }
}

void Image::desaturate(){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      if (pix.s >=0.1){
        pix.s -= 0.1;
      }else{
	pix.s = 0.0;
      }
    }
  }
}

void Image::desaturate(double amount){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      if (pix.s-amount >= 0){
        pix.s -= amount;
      }else{
        pix.l = 0.0;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
      pix.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
        if (pix.h + degrees >360 || pix.h + degrees <0){
	while (pix.h + degrees >360){
	  pix.h = (pix.h+degrees)-360;
	}
	while (pix.h + degrees <0){
	  pix.h = (pix.h+degrees) +360;
	}
	}else {
	  pix.h+=degrees;
	}
    }
  }
}

void Image::illinify(){
  for (unsigned int x=0; x<this->width(); x++){
    for (unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel & pix = this->getPixel(x,y);
        if (pix.h<113 || pix.h>294){
	  pix.h = 11;
	}else{
	  pix.h = 216;
	}
    }
  }
}

void Image::scale(double factor){
  
  unsigned int newWidth = factor*this->width();
  unsigned int newHeight = factor*this->height();
  PNG * ori = new PNG (*this);
  this->resize(newWidth, newHeight);

  for (unsigned int x=0; x< this->width()-1; x++){
    for (unsigned int y=0; y< this->height()-1; y++){
      cs225:: HSLAPixel &newPix = this->getPixel(x,y);
      unsigned int newX = round(x/factor);
      unsigned int newY = round(y/factor);
      cs225:: HSLAPixel &pix = ori->getPixel(newX, newY);
      newPix = pix;
    }
  }
  delete ori; ori = NULL;
}


void Image::scale(unsigned int w, unsigned int h){
  PNG * ori = new PNG (*this);
  unsigned int oriW = ori->width();
  unsigned int oriH = ori->height();
  double factorX = w/oriW;
  double factorY = h/oriH;
  this->resize(w,h);
  
  for (unsigned int x=0; x< this->width()-1; x++){
    for (unsigned int y=0; y< this->height()-1; y++){
      cs225:: HSLAPixel &newPix = this->getPixel(x,y);
      unsigned int newX = round(x/factorX);
      unsigned int newY = round(y/factorY);
      cs225:: HSLAPixel &pix = ori->getPixel(newX, newY);
      newPix = pix;
    }
  }
  delete ori; ori = NULL;


}

