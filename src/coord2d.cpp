/*
 * coord2d.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: roar
 */

#include "coord2d.h"

coord2d::coord2d(double x,double y){
	this->x=x;
	this->y=y;
}

double coord2d::getX(){
	return x;
}

double coord2d::getY(){
	return y;
}

void coord2d::print(){
	std::ostringstream strs;
	strs << "x=" << x << ", y=" << y << '\n';
	std::string str = strs.str();
	std::cout << str;
	return;
}
