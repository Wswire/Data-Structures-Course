/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
  int sRow = theSource.getRows();
  int sCol = theSource.getColumns();
  MosaicCanvas* canvas  = new MosaicCanvas(sRow, sCol);  // make mosaic with same number of tiles as 
  vector<Point<3>> sourceVec;
  vector<Point<3>> tileVec;
  vector<HSLAPixel> hslaTile;
  int ct = 0;

cout<<"alakazam"<<endl;
/*
  for (unsigned i = 0; i<theTiles.size(); i++){
    hslaTile.push_back(theTiles[i].getAverageColor());
  }
 
  for(unsigned i = 0; i< hslaTile.size() ; i++){
    hslaTile[i].h = (hslaTile[i].h)/360;
  }
*/
  for (int i = 0; i<sRow ; i++){
    for (int j = 0; j<sCol; j++){
      HSLAPixel pix = theSource.getRegionColor(i,j); //get source tile color and store in point vector while converting hsla to [0 1]
      Point<3> shsl;
      double num = (pix.h)/360;
      shsl[0] = num;
      shsl[1] = pix.s;
      shsl[2] = pix.l;
      sourceVec.push_back(shsl);
    }
  }
  
  for (unsigned i = 0; i< theTiles.size(); i++){
    HSLAPixel pix = theTiles[i].getAverageColor();  //get color for tile images
    Point<3> thsl;
    double num = (pix.h)/360;
//cout<<num<<endl;
    thsl[0] = num;
    thsl[1] = pix.s;
    thsl[2] = pix.l;
    tileVec.push_back(thsl);
  }

  KDTree<3> kd(tileVec);
//  kd.printTree(cout);
//cout<<"jigglypuff"<<endl;
  for (int i = 0; i<sRow ; i++){
    for (int j = 0; j<sCol; j++){
//cout<<"sourceVec"<<endl;
//cout<<sourceVec[ct]<<endl;
      Point<3> nearest = kd.findNearestNeighbor(sourceVec[ct]);  // using kdtree to find closest to target
      for (unsigned z =0; z < tileVec.size(); z++){
        if (tileVec[z] == nearest){  //used to find index in which the nearest point resides
//cout<<"nearest"<<endl;
//cout<<nearest<<endl;
//cout<<"tileVec"<<endl;
//cout<<tileVec[0]<<endl;
//cout<<tileVec[1]<<endl;
//cout<<tileVec[2]<<endl;
          TileImage* tileImg = &theTiles[z];  //as the index values of the tile imgaes and color of tile images are the same we can use the index in the color of tile image vector to find the actual image
          canvas->setTile(i,j,tileImg); //set image in canvas
        }
      }
      ct++;

    }
  }
  
cout<<"Gengar"<<endl;
  return canvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
