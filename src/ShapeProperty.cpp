/*
 * ShapeProperty.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: roar
 */

#include "ShapeProperty.h"

ShapeProperty::ShapeProperty(float ulx,float uly,float urx,float ury,float lrx,float lry,float llx,float lly,int sort){
	// TODO Auto-generated constructor stub
	setAll(ulx,uly,urx,ury,llx,lly,lrx,lry);
	type=sort;
}

ShapeProperty::ShapeProperty(int ulx,int uly,int urx,int ury,int lrx,int lry,int llx,int lly,int sort){
	setAll(ulx/100.0,uly/100.0,urx/100.0,ury/100.0,llx/100.0,lly/100.0,lrx/100.0,lry/100.0);
	type=sort;
}

int ShapeProperty::getType(){
	return type;
}

void ShapeProperty::setAll(float ulx,float uly,float urx,float ury,float lrx,float lry,float llx,float lly){
	locations[upperLeft].posX = ulx;
	locations[upperLeft].posY = uly;
	locations[lowerLeft].posX = llx;
	locations[lowerLeft].posY = lly;
	locations[upperRight].posX = urx;
	locations[upperRight].posY = ury;
	locations[lowerRight].posX = lrx;
	locations[lowerRight].posY = lry;
}

void ShapeProperty::setCorner(int corner, float posX, float posY){
	int c = corner;
	locations[c].posX = posX;
	locations[c].posY = posY;
}

float ShapeProperty::getCornerX(int corner){
	return locations[corner].posX;
}

float ShapeProperty::getCornerY(int corner){
	return locations[corner].posY;
}
