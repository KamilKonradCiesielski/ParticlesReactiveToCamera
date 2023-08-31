#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//vidPlayer.load("finger"); 
	//vidPlayer.play(); 
	//vidPlayer.setLoopState(OF_LOOP_NORMAL);
	webCam.setup(320, 240);

	colorImg.allocate(320,240);//we assign pixels to different images so that the program knows that part of the memory must be reserved
	grayImg.allocate(320, 240);
	grayBg.allocate(320, 240);
	grayDiff.allocate(320, 240);

	gui.setup(); 
	gui.add(overallSpeed.setup("speed", 1,0,3));
	gui.add(noiseAmount.setup("noise", 1, 0, 3));
	gui.add(threshold.setup("threshold", 80, 0, 255));
	gui.add(bLearnBackground.setup("capture background", false));

	
	p.assign(1000, particle());// in this way we create 100 particules object to work with

	for (int i = 0; i < p.size(); i++)
	{
		p[i].setup();

	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofBackground(0, 0, 0);


	ofSetFrameRate(60);

	bool bNewFrame = false; //will ask the video player if this is a new frame or not?


	//vidPlayer.update(); 
	webCam.update();

	//bNewFrame = vidPlayer.isFrameNew();
	bNewFrame = webCam.isFrameNew();

	if (bNewFrame = true) {// if we have a new cage, we can perform background subtraction operations

		//colorImg.setFromPixels(vidPlayer.getPixels());
		colorImg.setFromPixels(webCam.getPixels());
		grayImg = colorImg;
	}

	if (bLearnBackground == true) {
		grayBg = grayImg;
		bLearnBackground = false;
	}

	grayDiff.absDiff(grayBg, grayImg);
	grayDiff.threshold(threshold);

	contourFinder.findContours(grayDiff, 20, (340 * 20) / 2, 10, true);
	
	vector<ofVec2f>blobPts;//get these repel points from contour, blobPts are the points of repel  
	int j = 0;
	for (int i = 0; i < contourFinder.nBlobs; i++) {// to get all blobs and all the points from blobs, contourFinder.nBlobs - number of points from blobs
		for (int j = 0; j < contourFinder.blobs[i].pts.size(); j++); {//for all the blobs are neew find points along this blobs 
			blobPts.push_back(contourFinder.blobs[i].pts[j] * ofGetWidth() / 320);//we go through all the points from all the blobs and this is scaled to the width of the screen size of contour finder 
		}
	}

	for (int i = 0; i < p.size(); i++)
	{
		p[i].repel(blobPts);
		p[i].update(overallSpeed,noiseAmount);
		
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	webCam.draw(0, 0);

	for (int i = 0; i < p.size(); i++)
	{
		p[i].draw(1);

	}

	//draw the incoming, the grayscale, the bg and the threshold difference
	ofSetHexColor(0xffffff);
	colorImg.draw(20, 20);
	grayImg.draw(360, 20);
	grayBg.draw(20, 280);
	grayDiff.draw(360, 280);

	// draw the contours

	ofFill();
	ofSetHexColor(0x333333);
	ofDrawRectangle(360, 540, 320, 240);
	ofSetHexColor(0xffffff);

	contourFinder.draw(360, 540);

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
