#include "ofApp.h"
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#define pi 3.1415
#define WIDTH 1.0
#define HEIGHT 0.5625
#define KINECT_PROJ_DIST 0.85  //calibrate
//#define BEAM_ANGLE 0.27 //radians //calibrate
#define PROJECTION_ANGLE 24.5 //degrees //calibrate
#define numberOfEach 4
#define numberOfTypes 4


//#define PROJ_ANGLE_RAD PROJECTION_ANGLE*pi/180
double positions[numberOfEach*numberOfTypes][5][3];
double xx,yy,zz,dist1;
ofTrueTypeFont myfont;
unsigned int countBoxes;
unsigned int countPersons;
unsigned int countPaths;
int totalObjects[numberOfEach];
bool check;





// FOR DEBUGGING, IF IT IN SOME CASE IS NEEDED TO TEST DIFFERENT PERMUTATIONS OF EITHER THE COORDINATE SYSTEM (ii) OR CORNERS (aa) 
//int ii[6][3] = {{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
//int aa[24][4] = {{0, 2, 3, 1}, {0, 2, 1, 3}, {0, 3, 2, 1}, {0, 3, 1, 2}, {0, 1, 2, 3}, {0, 1, 3, 2}, {2, 0, 3, 1}, {2, 0, 1, 3}, {2, 3, 0, 1}, {2, 3, 1, 0}, {2, 1, 0, 3}, {2, 1, 3, 0}, {3, 0, 2, 1}, {3, 0, 1, 2}, {3, 2, 0, 1}, {3, 2, 1, 0}, {3, 1, 0, 2}, {3, 1, 2, 0}, {1, 0, 2, 3}, {1, 0, 3, 2}, {1, 2, 0, 3}, {1, 2, 3, 0}, {1, 3, 0, 2}, {1, 3, 2, 0}};
//int aaIndex = 0;




std::ofstream f;
bool printOutput;


double offY,dist,PROJ_ANGLE_RAD,vinkel;
//--------------------------------------------------------------
void ofApp::setup(){

    show_controls = false;
    ofBackground(255,255,255);
    mapping.addImageTemplate("image","images/red_box.jpeg");
    mapping.addImageTemplate("image2","images/green_ring.jpeg");
    mapping.addImageTemplate("image4","images/green_box.jpeg");
    mapping.addImageTemplate("image5","images/green_placehere.jpeg");
    //init mapping and load mapping settings from xml
    //mapping.setup("mapping/mapping.xml");
    mapping.setup();
    mapping.showControls(false);
    //set output position and size
    mapping.setOutputShape(0, 0, ofGetWidth(), ofGetHeight());
    //set position and size of control panel
    //mapping.setControlShape(0, 0, ofGetWindowWidth()/2, ofGetWindowHeight());

    client.connect("localhost",9090);
    client.addListener(this);
    ofSetFrameRate(10); //Dubblade från 10 20160514 för att öka hastigheten
    ofSetLogLevel(OF_LOG_ERROR);
    sett[0]=1;

dist = 1.38; // var minus...
offY = -0.8; //KINECT_PROJ_DIST-1.25;
PROJ_ANGLE_RAD = PROJECTION_ANGLE*pi/180;
vinkel = -27;//27;

totalObjects[0]=6;//6 boxes
totalObjects[1]=6;//6 humans
totalObjects[2]=6;//6 green box
totalObjects[3]=6;//bygglåda
}
//--------------------------------------------------------------
void ofApp::exit() {
}
//--------------------------------------------------------------
void ofApp::update() {
    //update the addon
    mapping.update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    //draw the mapped output image and the controls
    mapping.draw();

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch(key) {
        case '1': {
        	dist+=0.01;
		cout << "distance = " << dist << endl;
            break;
        }
        case '2': {
        	dist-=0.01;
		cout << "distance = " << dist << endl;
            break;
        }
        case '8': {
        	offY+=0.1;
		cout << "offset in y for plane = " << offY << endl;
            break;
        }
        case '9': {
        	offY-=0.1;
		cout << "offset in y for plane = " << offY << endl;
            break;
        }
        case '4': {
		vinkel+=2.0;
        	PROJ_ANGLE_RAD = vinkel*pi/180;
		cout << "angle for plane = " << vinkel << endl;
            break;
        }
        case '5': {
		vinkel-=2.0;
        	PROJ_ANGLE_RAD = vinkel*pi/180;
		cout << "angle for plane = " << vinkel << endl;
            break;
        }
		

        case 'f': {
            ofToggleFullscreen();
            break;
        }
        case 'a': {
            aaIndex +=1;
		aaIndex = aaIndex%24;
            break;
        }
        case 'q' : {
            ic +=1;
            ic = ic%6;
            break;
        }
        case 'c' : {


	int id=0;
	for(int e=0;e<numberOfEach;e++){
		if(e>0)		
			id+=totalObjects[e-1];
	   	 for(int k=0;k<totalObjects[e];k++){ //have to add boxes
		        sprops.add(0.f,0.0,0.0,0.0,0.0,0.0,0.0,0.0,&mapping,e);
		
			//e*totalObjects+k;
			mapping.setPosition(sprops.getShape(id+k),id+k);
	         }
	}

		//cout << "krasch??";
	check=true;
        std::stringstream ss;
        ss << "{\"op\":\"subscribe\",\"topic\":\"/box_corners\"}";
        client.send(ss.str());
        ss << "{\"op\":\"subscribe\",\"topic\":\"/ground_based_rgbd_people_detector/PeopleCorners\"}";
        client.send(ss.str());
	//ss << "{\"op\":\"subscribe\",\"topic\":\"/path_corner_creator/NavigationCorners\"}";
        //client.send(ss.str());
            break;
        }
        case 'p' : { //for debugging, do a simulated message from people 
	  /*
	    ofxLibwebsockets::Connection c;
            ofxLibwebsockets::Event args(c, "{"topic": "/ground_based_rgbd_people_detector/PeopleCorners", "msg": {"data": [-0.14264883175492288, 0.1981800377368927, -0.0, -0.14264883175492288, 0.5981800377368927, -0.0, 0.25735116824507714, 0.1981800377368927, -0.0, 0.25735116824507714, 0.5981800377368927, -0.0, 100.0, 100.0], "layout": {"dim": [{"stride": 14, "size": 6, "label": ""}, {"stride": 14, "size": 14, "label": ""}], "data_offset": 0}}, "op": "publish"}",false);
            
            ofApp::onMessage(args);
	  */p
            break;
        }
    case 'l' : { //for debugging, do a simulated message of corners
	  /*
            ofxLibwebsockets::Connection c;
            ofxLibwebsockets::Event args(c, "{\"topic\": \"/box_corners\", \"msg\": {\"data\": [3.6210500230044276, -0.01811362813217099, -0.7265350072918831, 3.62096579321145, 0.03905565090588978, -1.1224285112037438, 3.6210347866225354, 0.3777798838112091, -0.6693657238523522, 3.6209505568295577, 0.4349491628492699, -1.0652592277642126, 1.0, 0.0, 3.6210500230044276, -0.01811362813217099, -0.7265350072918831, 3.62096579321145, 0.03905565090588978, -1.1224285112037438, 3.6210347866225354, 0.3777798838112091, -0.6693657238523522, 3.6209505568295577, 0.4349491628492699, -1.0652592277642126, 1.0, 0.0], \"layout\": {\"dim\": [{\"stride\": 28, \"size\": 6, \"label\": \"\"}, {\"stride\": 14, \"size\": 14, \"label\": \"\"}], \"data_offset\": 0}}, \"op\": \"publish\"}",false);
            
	    ofApp::onMessage(args);
            break;
	  */
        }
        default: break;
    }
}
//--------------------------------------------------------------
void ofApp::mouseMoved(ofMouseEventArgs &args){
}
//--------------------------------------------------------------
void ofApp::mouseDragged(ofMouseEventArgs &args){
}
//--------------------------------------------------------------
void ofApp::mousePressed(ofMouseEventArgs &args){
}
//--------------------------------------------------------------
void ofApp::mouseReleased(ofMouseEventArgs &args){
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    mapping.setOutputShape(0, 0, ofGetWidth(), ofGetHeight());
}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
  //cout<<"on connected"<<endl;
  client.send("rawrnrn");
  /* Try to add here to not having to press c to start the mapping
     check=true;
     std::stringstream ss;
     ss << "{\"op\":\"subscribe\",\"topic\":\"/box_corners\"}";
     client.send(ss.str());
     ss << "{\"op\":\"subscribe\",\"topic\":\"/ground_based_rgbd_people_detector/PeopleCorners\"}";
     client.send(ss.str());
     //ss << "{\"op\":\"subscribe\",\"topic\":\"/path_corner_creator/NavigationCorners\"}";
     //client.send(ss.str());
     */
}
//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
  //cout<<"on open"<<endl;
}
//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
  cout << args.message;
  // cout<<"on close"<<endl;
}
//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
  //cout<<"on idle"<<endl;
}
//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
  
  cout<<"got message "<<args.message<<endl;
  stringstream ss;
  Json::Value parsedFromString;
  Json::Reader reader;
  ss << args.message;




  /* IF MESSAGE HAS BEEN RECEIVED PROPERLY */
  
  if(reader.parse(ss.str(),parsedFromString)){
    
    //f.open("data.txt");
    
    Json::ArrayIndex t = 1;
    //  std::cout << parsedFromString.toStyledString()<<endl;
    Json::Value cornerCountV = parsedFromString["msg"]["layout"]["dim"][t]["size"];
    Json::ArrayIndex cornerCount = cornerCountV.asInt();
    t=0;
    Json::Value objectCountV = parsedFromString["msg"]["layout"]["dim"][t]["size"];
    Json::ArrayIndex objectCount = objectCountV.asInt();


    /* IF THE MESSAGE IS EMPTY, THEN DO NOTHING */

    if(objectCount==0){
      return;
    }

    
    cout << "---------------------------------------------------------" << endl; // for debugging
    for(int i=0;i<numberOfEach;i++){
      if(objectsOfEach[i]!=0){
	countDifferent++;
	cout << "har mottagit data att rita ut " << objectsOfEach[i];
	switch(i){
	case 0:
	  cout << " boxar";
	  break;
	case 1:
	  //cout << " människor"; //will cause the messages to wiggle in the console because it belongs to another topic, either ONLY this or the others
	  break;
	case 2:
	  cout << " rätt position";
	  break;
	case 3:
	  cout << " byggposition";
	  break;
	}
	cout << endl;
      }
      objectProj[i]=0; //set that none of the objects have yet been projected
    }
    cout << "---------------------------------------------------------" << endl;


    /* SET THE PLANE, DISTANCE TO PROJECTOR AND OFFSET */
    
    //move this block of code to setup when fully calibrated. **********************************************************
    double distToCamera = dist;//(WIDTH/2)/tan(BEAM_ANGLE); 
    double planeOffsetY = offY;//KINECT_PROJ_DIST-distToCamera*sin(PROJ_ANGLE_RAD);
    
    coord3d *s1 = new coord3d(-WIDTH/2,sin(pi/2-PROJ_ANGLE_RAD)*HEIGHT/2+planeOffsetY,cos(pi/2-PROJ_ANGLE_RAD)*HEIGHT/2);  //framecorner upper left
    coord3d *s2 = new coord3d(WIDTH/2,sin(pi/2-PROJ_ANGLE_RAD)*HEIGHT/2+planeOffsetY,cos(pi/2-PROJ_ANGLE_RAD)*HEIGHT/2);  //framecorner upper right
    coord3d *s3 = new coord3d(-WIDTH/2,-sin(pi/2-PROJ_ANGLE_RAD)*HEIGHT/2+planeOffsetY,-cos(pi/2-PROJ_ANGLE_RAD)*HEIGHT/2); //framecorner lower left
    
    EQsolve *eq1 = new EQsolve();
    coord3d* N1 = eq1->solve(s1->getX(),s1->getY(),s1->getZ(),s2->getX(),s2->getY(),s2->getZ(),s3->getX(),s3->getY(),s3->getZ());
    
    double normalization_length = sqrt(pow(N1->getX(),2)+pow(N1->getY(),2)+pow(N1->getZ(),2));
    N1->setX(N1->getX()/normalization_length);
    N1->setY(N1->getY()/normalization_length);
    N1->setZ(N1->getZ()/normalization_length);
    s1->setX(s1->getX()+dist*N1->getX());
    s1->setY(s1->getY()+dist*N1->getY());
    s1->setZ(s1->getZ()+dist*N1->getZ());
    
    s2->setX(s2->getX()+dist*N1->getX());
    s2->setY(s2->getY()+dist*N1->getY());
    s2->setZ(s2->getZ()+dist*N1->getZ());
    
    s3->setX(s3->getX()+dist*N1->getX());
    s3->setY(s3->getY()+dist*N1->getY());
    s3->setZ(s3->getZ()+dist*N1->getZ());
    //*******************************************************************************************************************


    
    /* debugging of plane
       std::cout << "s1-s2-s3" << "\n";
       s1->print();
       //std::cout << " ";
       s2->print();
       //std::cout << " ";
       s3->print();
       std::cout << "\n";
       std::cout << "dist=" << distToCamera << " planeoffset=" << planeOffsetY  << "q=" << ic << endl;
    */




    
    /* DRAW EVERY OBJECT THAT HAS BEEN RECEIVED IN THE MESSAGE */
    
    for(int nr = 0;nr<objectCount;nr++){
      
      /* CHECK THE TYPE OF THE OBJECT THAT IS GOING TO BE DRAWN */
      
      int currentType=-1;
      int reading = positions[nr][4][1];
      if(reading==0.0){
	currentType=0; //röd låda
      }else if(reading==100.0){
	currentType=1; //Människa
      }else if(reading==-1.0){
	currentType=2; //grön låda
      }else if(reading==-2.0){
	currentType=3; //bygglåda 20160512
      }else{
	break; //not a valid reading
      }
      



      
      /* ADD ONE OBJECT TO THE COUNTER THAT HAS BEEN DRAWN */
      
      int object=0;
      for(int i=0;i<currentType;i++){
	object+=totalObjects[i];
      }
      object+=objectProj[currentType];




      /* MAP EVERY CORNER OF THE CURRENT OBJECT AND THEN SET IT TO THE PROPERTIES */
      
      for(int corner = 0; corner < 4; corner++){
	
	double x,y,z;
	x = positions[nr][corner][0];
	y = positions[nr][corner][1];
	z = positions[nr][corner][2];
	coord3d *point = new coord3d(x,y,z);
	Map3Dto2D *mapper = new Map3Dto2D();
	if(printOutput){
	  mapper->setFstream();
	}else{
	  
	}
	coord2d *map2d = mapper->map(point,s1,s2,s3,distToCamera);

	int corners[]={3,0,2,1};
	/*if (currentType==0)  //if some type needs a "special treatment" to work properly
	  {

	  }*/
	int c = corners[corner%4];
	
	sprops.setCorner(object,c,map2d->getX(),1-map2d->getY());
	//std::cout << "hörn: " << corner << " x=" << x << " y=" << y << " z=" << z <<  " X=" << map2d->getX() << " Y=" << map2d->getY() << endl; //debugging
      }

      //std::cout << "redrawing " << currentType << " number " << object << endl;
      //std::cout << "setting position for object=" << object << std::endl;


      /* SET POSITIONS FOR THE OBJECT, THAT HAS JUST BEEN PROCESSED, AT THE MAPPER AND THEN INCREASE NUMBER OF OBJECTS THAT HAS BEEN PROCESSED */
      
      mapping.setPosition(sprops.getShape(object),object);
      objectProj[currentType]++;
            

      /* "ERASE" EVERY IMAGE OF THE CURRENT TYPE THAT NOT HAS BEEN RECEIVED (SET EVERY CORNER OF THE IMAGE TO 0) */
      if(objectProj[currentType]==objectsOfEach[currentType]){
	while(objectProj[currentType]++<totalObjects[currentType]){
	  object++;
	  //std::cout << "erasing " << currentType << " number " << object << endl;
	  sprops.getShape(object)->setAll(0.f,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
	  mapping.setPosition(sprops.getShape(object),object);
	}
	
      }
    }
  }

  
  /*	FOR DEBUGGING

	cout << "distance = " << dist << endl;
	cout << "offset in y for plane = " << offY << endl;
	cout << "angle for plane = " << vinkel << endl;
  */
  //cout << ofGetFrameRate() << endl;
}
//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
  cout<<"got broadcast "<<args.message<<endl;
}
