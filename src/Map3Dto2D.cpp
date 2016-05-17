/*
 * Map3Dto2D.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: Marius Grimstad
 */

#include "Map3Dto2D.h"
#include "coord2d.h"
#include "coord3d.h"
#include <sstream>
#include <string>

bool writef;

Map3Dto2D::Map3Dto2D(){

}

void Map3Dto2D::setFstream(){
	writef=true;
}

// TODO Auto-generated constructor stub
coord2d* Map3Dto2D::map(coord3d* point,coord3d* frameUpperLeft,coord3d* frameUpperRight, coord3d* frameLowerLeft,double distance){
	
	coord3d* s1=frameUpperLeft;
	coord3d* s2=frameUpperRight;
	coord3d* s3=frameLowerLeft;
	double W=sqrt(pow(s2->getX()-s1->getX(),2)+pow(s2->getY()-s1->getY(),2)+pow(s2->getZ()-s1->getZ(),2));
	coord3d* M = new coord3d((s2->getX()+s3->getX())/2,(s2->getY()+s3->getY())/2,(s2->getZ()+s3->getZ())/2);
	//z1=z2 !! Nope.
	
	//x1=x3
	//double H=sqrt(pow(s3->getX()-s1->getX(),2)+pow(s3->getY()-s1->getY(),2)+pow(s3->getZ()-s1->getZ(),2));

	double distFromCam = distance;

	EQsolve *eq = new EQsolve();
	coord3d* N = eq->solve(s1->getX(),s1->getY(),s1->getZ(),s2->getX(),s2->getY(),s2->getZ(),s3->getX(),s3->getY(),s3->getZ());
    //N->print();
	coord3d* N2 = new coord3d(N->getX(),N->getY(),N->getZ());

	double normalization_length = sqrt(pow(N->getX(),2)+pow(N->getY(),2)+pow(N->getZ(),2));
	N->setX(N->getX()/normalization_length);
	N->setY(N->getY()/normalization_length);
	N->setZ(N->getZ()/normalization_length);
	double lengthOfNormal = sqrt(pow(N->getX(),2)+pow(N->getY(),2)+pow(N->getZ(),2));
	double h=-distFromCam; //Causing C to stay in the same place and we instead move the plane

    double D = N2->getX()*s1->getX() + N2->getY()*s1->getY() + N2->getZ()*s1->getZ();
	coord3d* C = new coord3d(M->getX()+h*N->getX(),M->getY()+h*N->getY(),M->getZ()+h*N->getZ());

    double k = (D-N2->getX()*point->getX()-N2->getY()*point->getY()-N2->getZ()*point->getZ())/(N2->getX()*(C->getX()-point->getX())+N2->getY()*(C->getY()-point->getY())+N2->getZ()*(C->getZ()-point->getZ()));
    //std::cout << "point-c-m-n-a" << "\n";
 /*   point->print();
    C->print();
    M->print();
*/
	
//std::cout << "Normal för plan = ";
//    N->print();


    double x=((C->getX()-point->getX())*k)+point->getX();
    double y=(((C->getY()-point->getY())*k)+point->getY());
    double z=((C->getZ()-point->getZ())*k)+point->getZ();

coord3d* A = new coord3d(x,y,z);
//A->print();
    
    double cosU = ((s2->getX()-s1->getX())*(x-s1->getX())+(s2->getY()-s1->getY())*(y-s1->getY())+(s2->getZ()-s1->getZ())*(z-s1->getZ()))/(W*sqrt(pow(x-s1->getX(),2)+pow(y-s1->getY(),2)+pow(z-s1->getZ(),2)));
    
    double sinU = sin(acos(cosU));
    //std::cout << "sinU = " << sinU << "triggettan = " << pow(sinU,2) + pow(cosU,2) << std::endl;

    coord3d* NX = eq->solve(s1->getX(),s1->getY(),s1->getZ(),s2->getX(),s2->getY(),s2->getZ(),x,y,z);
	//std::cout << "Normal för punkten och planet typ = ";
	//NX->print();
    NX->setX(N->getX()-NX->getX());
    NX->setY(N->getY()-NX->getY());
    NX->setZ(N->getZ()-NX->getZ());
    double normalization_length_NX = sqrt(pow(NX->getX(),2)+pow(NX->getY(),2)+pow(NX->getZ(),2));   

    //std::cout << "NX_length=" << normalization_length_NX << std::endl; 

if(normalization_length_NX>lengthOfNormal){
	sinU=sin(-acos(cosU));
	//std::cout<<"Nu går vi in i IF!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
}
    //std::cout << "cosU=" << cosU << " xyz" << ((s2->getX()-s1->getX())*(x-s1->getX())+(s2->getY()-s1->getY())*(y-s1->getY())+(s2->getZ()-s1->getZ())*(z-s1->getZ())) << " hjds:" << (W*sqrt(pow(x-s1->getX(),2)+pow(y-s1->getY(),2)+pow(z-s1->getZ(),2)));
    //point->print();
    //std::cout << "|B1B2| = "<< W << std::endl;
    //std::cout << "|B1A| = " << sqrt(pow(x-s1->getX(),2)+pow(y-s1->getY(),2)+pow(z-s1->getZ(),2)) << std::endl;
    
    //std::cout << ((s2->getX()-s1->getX())*(x-s1->getX())+(s2->getY()-s1->getY())*(y-s1->getY())+(s2->getZ()-s1->getZ())*(z-s1->getZ())) << std::endl;
    //std::cout << " x = " << x << " y = " << y  << " z = " << z << "på planet" << std::endl;
     
    double m = cosU*sqrt(pow(x-s1->getX(),2)+pow(y-s1->getY(),2)+pow(z-s1->getZ(),2));
    double n = sinU*sqrt(pow(x-s1->getX(),2)+pow(y-s1->getY(),2)+pow(z-s1->getZ(),2));

    n*=16/9.0;

    //double n = x/y;
    //double m = z/y;

    //double m = sqrt(pow(s2->getX()-s1->getX(),2)+pow(s2->getY()-s1->getY(),2)+pow(s2->getZ()-s1->getZ(),2))*cosU;
    //double n = sqrt(pow(s3->getX()-s1->getX(),2)+pow(s3->getY()-s1->getY(),2)+pow(s3->getZ()-s1->getZ(),2))*sinU;


    //std::cout << "D=" << D << "k=" << k << " cosU=" << cosU << " sinU=" << sinU << " m=" << m << " n=" << n << std::endl; 
    
    coord2d* pointMapped = new coord2d(m,n);



   // std::cout << "C: x: "<< C->getX()<< "y: "<<C->getY() <<"z: "<<C->getZ()<<std::endl;
//std::cout << "M: x: "<< M->getX()<< "y: "<<M->getY() <<"z: "<<M->getZ()<<std::endl;
    //pointMapped->print();

	return pointMapped;
}
