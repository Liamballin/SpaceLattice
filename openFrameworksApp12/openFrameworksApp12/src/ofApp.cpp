#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	//box = ofBoxPrimitive();
	section newSec;
	newSec.color = ofColor(ofRandom(255), ofRandom(255), 255);
	newSec.pos = ofPoint(0,67,0);
	newSec.rot = 45;

	lattice.push_back(newSec);
	validPos = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	ofPoint m = easyCam.screenToWorld(mouse);
	ghostSec.pos = m;
	ghost.set(10, 190, 100);
	//ghostSec.pos.z = 0
}

//--------------------------------------------------------------
void ofApp::draw(){
	easyCam.begin();

	
	ofBackground(ofColor::grey);
	ofSetColor(ofColor::white);
	ofDrawGrid(100, 50, false, false, true, false);
	ofNoFill();
	ofPoint m = easyCam.screenToWorld(mouse);

	//ofDrawBox(500, 500, 0);
	float size = 134;
		//Generate grid and test mouse pos
	int width = 10;
	int height = 5;
	float offset = (135*(width/4))*-1;
	ofPoint closest;
	float closestDistance;
	
	for (unsigned int bx = 0; bx < 5; bx++) {
		for (unsigned int by = 0; by < 5; by++) {
			float x = (bx * size)+offset;
			float y = (by * size)+(size / 2);
			
			ofPoint current = easyCam.worldToScreen(ofPoint(x, y, 0));
			float distance = current.distance(mouse);
			if (bx == 0 && by == 0 || distance <closestDistance) {
				//ofFill();
				//ghost.setPosition(ofPoint(x, y, 0));
				//currentPos = ofPoint(x, y, 0);
				//validPos = true;
				closest = ofPoint(x, y, 0);
				closestDistance = distance;
				if (mouse.x < current.x) {
					currentRot = 45;
					ofSetColor(ofColor::red);
					//if(ghost.get)

				}
				else {
					currentRot = -45;
					ofSetColor(ofColor::blue);
				}
			}	
			else {
				ofNoFill();

			}
			if (ghost.getRollDeg() != currentRot) {

				std::cout << "roll: " << ghost.getRollDeg() << "cur: " << currentRot << endl;
				ghost.rollDeg(-ghost.getRollDeg());
				ghost.rollDeg(currentRot);
			}
				ofDrawBox(x, y, 0, size, size, 0);
		}
	}

	ghost.setPosition(closest);
	currentPos = closest;


	//ofRotateZDeg(currentRot);
		ghost.draw();
		//ofRotateZDeg(-currentRot);

	

	for (unsigned int i = 0; i < lattice.size(); i++) {
		ofPoint pos = lattice[i].pos;
		int rot = lattice[i].rot;
		ofColor col = lattice[i].color;

		ofDrawLine(pos, m);

		ofSetColor(col);

		ofTranslate(pos.x, pos.y, pos.z);
		ofRotateZDeg(rot);
		ofDrawBox(10, 190, 100);
		ofRotateZDeg(-rot);
		ofTranslate(-pos.x, -pos.y, -pos.z);
	}


	//for (int i = 0; i < 3; i++) {
	//	int deg = 45;
	//	ofTranslate(0, 140, 0);
	//	ofTranslate((-150*9), 0, 0);
	//	//ofTranslate(150,0, 0);
	//	for (int k = 0; k < 10; k++) {
	//		deg *= -1;
	//		ofTranslate(150, 0, 0);
	//		ofRotateZDeg(deg);
	//		//ofSetColor(ofColor::aqua);
	//		ofDrawRectangle(0,0,0,95, 95);

	//		ofNoFill();
	//		ofDrawBox(10, 190, 100);
	//		ofRotateZDeg(-deg);
	//	}
	//}

	easyCam.end();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mouse = ofPoint(x, y, 0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	section	 newSec;
	newSec.color = ofColor(ofRandom(255), ofRandom(255), 255);
	ofPoint m = easyCam.screenToWorld(mouse);
	newSec.pos = currentPos;
	newSec.rot = currentRot;

	lattice.push_back(newSec);
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


