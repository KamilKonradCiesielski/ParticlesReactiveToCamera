#pragma once

#include "ofMain.h"
#include "particle.h"
#include "ofxGui.h"
#include <ofxOpenCv.h>
#include "ofVideoGrabber.h"
#include "ofVideoPlayer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);



		vector<particle>p;

		ofxPanel gui;
		ofxFloatSlider overallSpeed;
		ofxFloatSlider noiseAmount; 


		ofxToggle bLearnBackground; //when your scene is empty and you need to capture the background
		ofxIntSlider threshold; //changing the threshold of difference in background subtraction

		ofVideoPlayer vidPlayer; 

		ofVideoGrabber webCam;

		ofxCvColorImage colorImg; // we get input data from the video player
		ofxCvGrayscaleImage grayImg;//to use the background subtraction technique, we replace the colored input image with a gray scale image  
  
	    //ofVideoGrabber for web cam 
		
		ofxCvGrayscaleImage grayBg;// we need another gray scale image for the background we capture 
		ofxCvGrayscaleImage grayDiff; //the difference between the gray live image and the background


		ofxCvContourFinder contourFinder;  //object to extract objects in grayDiff that we get 


};
