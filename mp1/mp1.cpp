#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <iostream>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG image = PNG();  
  image.readFromFile(inputFile);
cout<<image.width()<<endl;
cout<<image.height()<<endl;
  for (unsigned x = 0; x < (image.width()/2); x++){
    for (unsigned y = 0; y < (image.height()); y++){
	HSLAPixel * pix = image.getPixel(x,y);
	HSLAPixel * pix2 = image.getPixel(image.width()-x-1, image.height()-y-1);
	double h = pix->h;
	double s = pix->s;
	double l = pix->l;
	double a = pix->a;
	pix->h = pix2->h;
	pix->s = pix2->s;
	pix->l = pix2->l;
	pix->a = pix2->a;
	pix2->h = h;
	pix2->s = s;
	pix2->l = l;
	pix2->a = a;
    }
  }
    if (image.width()%2==1){
    unsigned halfWidth = image.width()/2;
    for (unsigned y = 0; y < (image.height()/2); y++){
        HSLAPixel * pix = image.getPixel(halfWidth,y);
        HSLAPixel * pix2 = image.getPixel(halfWidth, image.height()-y-1);
        double h = pix->h;
        double s = pix->s;
        double l = pix->l;
        double a = pix->a;
        pix->h = pix2->h;
        pix->s = pix2->s;
        pix->l = pix2->l;
        pix->a = pix2->a;
        pix2->h = h;
        pix2->s = s;
        pix2->l = l;
        pix2->a = a;
}
}
  image. writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
  for (unsigned x = 0; x < (png.width()-1); x++){
    for (unsigned y = 0; y < (png.height()-1); y++){
	HSLAPixel * pix = png.getPixel(x,y);
	if (x % 26==0|| x % 26==1|| x % 26==2|| x % 26==3){
	  pix->h = 300.0;
	  pix->s = 100.0;
	  pix->l = 50.0;
	  pix->a = 1.0;
	}
        else if(y % 26==0|| y % 26==1|| y % 26==2|| y % 26==3){
          pix->h = 300.0;
          pix->s = 100.0;
          pix->l = 50.0;
          pix->a = 1.0;
        }
        else if(y % 26==5|| y % 26==4|| y % 26==6||x % 26==6|| x % 26==5|| x % 26==4||y % 26==7||x % 26==7){
          pix->h = 0.0;
          pix->s = 0.0;
          pix->l = 0.0;
          pix->a = 1.0;
        }
        else{
          pix->h = 180.0;
          pix->s = 100.0;
          pix->l = 50.0;
          pix->a = 1.0;
        }
    }
  }
  return png;
}
