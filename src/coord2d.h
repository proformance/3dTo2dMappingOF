/*
 * coord2d.h
 *
 *  Created on: Mar 4, 2016
 *      Author: roar
 */
#pragma once
#include <sstream>
#include <string>
#include <iostream>

#ifndef COORD2D_H_
#define COORD2D_H_

class coord2d {
public:
	coord2d(double x,double y);
	double getX();
	double getY();
	void print();
private:
	double x,y;
};

#endif /* COORD2D_H_ */
