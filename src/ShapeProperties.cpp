/*
 * ShapeProperties.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: roar
 */

#include "ShapeProperties.h"

ShapeProperties::ShapeProperties() {
	// TODO Auto-generated constructor stub

}

int ShapeProperties::add(float ulx,float uly,float urx,float ury,float lrx,float lry,float llx,float lly,ofx2DMapping* mapping,int sort){
	ShapeProperty *sp = new ShapeProperty(urx,ury,ulx,uly,lrx,lry,llx,lly,sort);
	props.push_back(sp);
	mapping->addToView(sort);
	switch(sort){
		cout << sort;
		case 0:
			countBoxes++;
			break;
		case 1:
			countHumans++;
			break;
	}
	return props.size()-1;
}


int ShapeProperties::getHumans(){
	return countHumans;
}

int ShapeProperties::getBoxes(){
	return countBoxes;
}

void ShapeProperties::setCorner(int index,int corner, float posX, float posY){
	props[index]->setCorner(corner,posX,posY);
}
float ShapeProperties::getCornerX(int index,int corner){
	return props[index]->getCornerX(corner);
}
float ShapeProperties::getCornerY(int index,int corner){
	return props[index]->getCornerY(corner);
}
void ShapeProperties::setAll(int index,float ulx,float uly,float urx,float ury,float lrx,float lry,float llx,float lly){
	props[index]->setAll(ulx,uly,urx,ury,lrx,lry,llx,lly);
}

ShapeProperty* ShapeProperties::getShape(int i){
	if(i<props.size()){
		return props.at(i);
	}
	return 0;
}


int ShapeProperties::getSize(){
	return props.size();
}
