/*
 * coord3d.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: roar
 */

#include "coord3d.h"


coord3d::coord3d(double x,double y,double z){
	this->x=x;
	this->y=y;
	this->z=z;
}
coord3d::coord3d(){
}

double coord3d::getX(){
	return x;
}

double coord3d::getY(){
	return y;
}

double coord3d::getZ(){
	return z;
}

void coord3d::print(){
	std::ostringstream strs;
	strs << x << " " << y << " " << z << '\n';
	std::string str = strs.str();
	std::cout << str;
	return;
}


void coord3d::setX(double data){
	x=data;
}

void coord3d::setY(double data){
	y=data;
}

void coord3d::setZ(double data){
	z=data;
}


