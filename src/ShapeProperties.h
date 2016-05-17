/*
 * ShapeProperties.h
 *
 *  Created on: Feb 25, 2016
 *      Author: roar
 */

#ifndef ADDONS_OFX2DMAPPING_MASTER_SRC_SHAPEPROPERTIES_H_
#define ADDONS_OFX2DMAPPING_MASTER_SRC_SHAPEPROPERTIES_H_

#include "ShapeProperty.h"
#include "ofx2DMapping.h"
#include <vector>


class ShapeProperties {
public:
	ShapeProperties();

	int add(float ulx,float uly,float urx,float ury,float lrx,float lry,float llx,float lly,ofx2DMapping*,int sort);
	void setCorner(int index,int corner, float posX, float posY);
	float getCornerX(int index,int corner);
	float getCornerY(int index,int corner);
	void setAll(int index,float ulx,float uly,float urx,float ury,float lrx,float lry,float llx,float lly);

	ShapeProperty* getShape(int);
	int getSize();

	int getHumans();
	int getBoxes();



private:
	std::vector<ShapeProperty*> props;
	int countHumans,countBoxes;
};

#endif /* ADDONS_OFX2DMAPPING_MASTER_SRC_SHAPEPROPERTIES_H_ */
