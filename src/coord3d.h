/*
 * coord3d.h
 *
 *  Created on: Mar 4, 2016
 *      Author: roar
 */
#pragma once
#include <sstream>
#include <string>
#include <iostream>

#ifndef COORD3D_H_
#define COORD3D_H_

class coord3d {
public:
	coord3d(double x,double y,double z);
	coord3d();
	double getX();
	double getY();
	double getZ();

	void setX(double data);
	void setY(double data);
	void setZ(double data);

	void print();
private:
	double x,y,z;
};

#endif /* COORD3D_H_ */
