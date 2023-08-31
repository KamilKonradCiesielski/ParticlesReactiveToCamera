#include "particle.h"

particle::particle()
{
}

void particle::setup()
{
	pos.x = ofRandomWidth();
	pos.y - ofRandomHeight();

	vel.x = ofRandom(-4, 4);
	vel.y = ofRandom(-4, 4); 

	frc = ofVec2f(0, 0); 

	uniqueVal.x = ofRandom(-1000, 1000); 
	uniqueVal.y = ofRandom(-1000, 1000);

	size = ofRandom(3, 15); 

	drag = ofRandom(0.97, 0.98); 


}

void particle::update(float speed, float noise)
{
	frc.x = ofSignedNoise(uniqueVal.x, ofGetElapsedTimeMillis());
	frc.y = ofSignedNoise(uniqueVal.y, ofGetElapsedTimeMillis());


	frc *= noise;

	vel *= drag;

	vel -= repelFrc; // minus here works as the repeling force, plus will work as attraction force

	vel += frc; 



	// reset at border

	if (pos.x + vel.x > ofGetWidth()) {
		pos.x -= ofGetWidth();
	}
	else if (pos.x + vel.x < 0) {
		pos.x += ofGetWidth();
	}
	if (pos.y + vel.y > ofGetHeight()) {
		pos.y -= ofGetHeight();
	}
	else if (pos.y + vel.y < 0) {
		pos.y += ofGetHeight();
	}


	pos += vel*speed; 
 

}

void particle::draw(float sizeDot)
{
	ofDrawCircle(pos.x, pos.y, size * sizeDot);
	

	ofSetColor(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
	


}

void particle::repel(vector<ofVec2f> repelPt)
{
	repelFrc.set(0, 0);//ustawiamy repel Force to zero, every frame we reset that force

	for (int i = 0; i < repelPt.size(); i++) //get acess to all repel points 
	{

		float dist = pos.distance(repelPt[i])// the distance from the point of repel to the particule, distance equal to the position of particule and current repal point in the loop 
			;
		if (dist < 150) {// if the distance is smaller than 150 - distance our repal point to the poistion of the particule, small enough that we can add repel force to that 

			ofVec2f newRepelPt; 
			newRepelPt = repelPt[i] - pos; //we get vector direction to repel in a appropriate direction
			repelFrc += newRepelPt * 0.01; 
		}
	}

}
