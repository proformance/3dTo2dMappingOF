/*
 * ShapeProperty.h
 *
 *  Created on: Feb 23, 2016
 *      Author: roar
 */

#ifndef SRC_SHAPEPROPERTY_H_
#define SRC_SHAPEPROPERTY_H_

class ShapeProperty {
public:
	ShapeProperty(float ulx,float uly,float urx,float ury,float lrx,float lry,float llx,float lly,int sort);
	ShapeProperty(int ulx,int uly,int urx,int ury,int lrx,int lry,int llx,int lly,int sort);
	ShapeProperty(int index);
	enum Corner{upperLeft,upperRight,lowerRight,lowerLeft};

	void setCorner(int corner, float posX, float posY);
	float getCornerX(int);
	float getCornerY(int);
	void setAll(float ulx,float uly,float urx,float ury,float lrx,float lry,float llx,float lly);
	int getType();

private:

	struct Location{
		float posX,posY;
	};

	int type;

	struct Location locations[4];
};

#endif /* SRC_SHAPEPROPERTY_H_ */
