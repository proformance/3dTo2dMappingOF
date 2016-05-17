/*
 * Map3Dto2D.h
 *
 *  Created on: Mar 4, 2016
 *      Author: roar
 */


#include <string>
#include <iostream>
#include "coord2d.h"
#include "coord3d.h"
#include "EQsolve.h"
#include <cmath>
#include <fstream>

#ifndef MAP3DTO2D_H_
#define MAP3DTO2D_H_

class Map3Dto2D {
public:
	Map3Dto2D();
	coord2d* map(coord3d* point,coord3d* frameUpperLeft,coord3d* frameUpperRight, coord3d* frameLowerRight, double distance);
	void setFstream();
};

#endif /* MAP3DTO2D_H_ */
