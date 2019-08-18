#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	//for (int i = 0; i < deviceList.size(); i++) {
	//	std::cout << to_string(deviceList[i]) << endl;

	//}
	int baud = 9600;
	serial.setup(0, baud);

	//addSection(ofPoint(0, 67, 0), 45);
	latticeInspect = 0;
	setupGui();

	ghost.set(10, 190, 100);

	easyCam.setPosition(-546.738, 659.731, 1120.2);
	easyCam.setTarget(ofPoint(0, 0, 0));

	dragging = false;
	lastState = false;
	b1 = 255;
	b2 = 0;
	

}

//--------------------------------------------------------------
void ofApp::update(){
	if (ortho) {
		easyCam.enableOrtho();
	}
	else {
		easyCam.disableOrtho();
	}
	currentGui.setPosition(easyCam.worldToScreen(mouse));

	if (lattice.size() > 0) {
		if (lattice[0].on != lastState) {
			if (lattice[0].on) {

				serial.writeByte(b1);
				std::cout << "Sending byte " << b1 << endl;

			}
			else {
				serial.writeByte(b2);
				std::cout << "Sending byte " << b2 << endl;

			}
		}
		lastState = lattice[0].on;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
	ofBackground(ofColor::grey);
	ofSetColor(ofColor::white);
	ofNoFill();
	
	easyCam.begin();

	if (showGrid) {
		ofDrawGrid(100, 50, false, false, true, false);
	}

	if (buildMode) {
		updateGrid();
		ghost.draw();
		ofDrawAxis(100);
	}
	else {

		inspectMode();
		
	}
	
	renderLattice();
	

	
	easyCam.end();

	renderSettings.draw();
	info.draw();
	if (buildMode) {
		buildTools.draw();
	}

	else {
		//segment_on.setup("Lights on", inspected.on);
		if (lattice.size() > 0) {
			ofDrawBitmapStringHighlight(ofToString(lattice[latticeInspect].on), mouse + 50);
		}
		for (unsigned int i = 0; i < lattice.size(); i++) {
			ofDrawBitmapStringHighlight(ofToString(lattice[i].id), easyCam.worldToScreen(lattice[i].pos));

		}
		//ofDrawBitmapStringHighlight()

		//cursorInfo.draw();
	}
}

//----------------------------------

void ofApp::inspectMode() {
	float closest;
	ofxPanel gui;
	for (unsigned int i = 0; i < lattice.size(); i++) {
		ofPoint cur = easyCam.worldToScreen(lattice[i].pos);
		float distance = cur.distance(mouse);
		if (i == 0 || distance < closest) {
			closest = distance;
			inspected = lattice[i];
			gui = lattice[i].gui;
			latticeInspect = i;
		}
	}
	ofDrawLine(inspected.pos,easyCam.screenToWorld(mouse));

}

void ofApp::updateGrid() {
	float size = 134;
	//Generate grid and test mouse pos
	int width = guideWidth;
	int height = guideHeight;
	float offset = (135 * (width / 4))*-1;
	ofPoint closest;
	float closestDistance;

	for ( int bx = 0; bx < width; bx++) {
		for ( int by = 0; by < height; by++) {
			float x = (bx * size) + offset;
			float y = (by * size) + (size / 2);

			ofPoint current = easyCam.worldToScreen(ofPoint(x, y, 0));
			float distance = current.distance(mouse);
			if (bx == 0 && by == 0 || distance < closestDistance) {
				//The current x and y are under the mouse
				closest = ofPoint(x, y, 0);
				closestDistance = distance;
				if (mouse.x < current.x) {
					currentRot = 45;
				}
				else {
					currentRot = -45;
				}
			}

			if (ghost.getRollDeg() != currentRot) {
					//if the cursor segment isn't correctly rotated, rotate it.

				//std::cout << "roll: " << ghost.getRollDeg() << "cur: " << currentRot << endl;
				ghost.rollDeg(-ghost.getRollDeg());
				ghost.rollDeg(currentRot);
			}
			ofDrawBox(x, y, 0, size, size, 0);
		}
	}

	ghost.setPosition(closest);
	currentPos = closest;
}

void ofApp::renderLattice() {
	for (unsigned int i = 0; i < lattice.size(); i++) {
		if (buildMode) {
			ofSetColor(lattice[i].color);
		}
		else {
			if (lattice[i].id != inspected.id) {
				if (lattice[i].on) {
					ofSetColor(ofColor::orange);
				}
				else {
					ofSetColor(ofColor::cornsilk);
				}
				}
			else {
				ofSetColor(ofColor::red);
			}
		}
		
		ofNoFill();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
		lattice[i].mesh.draw();
	}
}

void ofApp::addSection(ofPoint pos, int rot) {
	section	 newSec;
	newSec.mesh.set(10, 190, 100);
	newSec.mesh.rollDeg(rot);
	newSec.mesh.setPosition(pos);
	newSec.color = ofColor(ofRandom(255), ofRandom(255), 255);
	newSec.pos = pos;
	newSec.rot = rot;
	newSec.on = false;
	newSec.id = lattice.size() + 1;
	//newSec.gui.setup();
	//newSec.gui.setName(to_string(newSec.id));
	//newSec.gui.add(newSec.on.set("on", false));

	

	lattice.push_back(newSec);
	segCount.set("Segment count", (int)lattice.size(), 0, 100);

}

void ofApp::setupGui() {
	renderSettings.setup();
	renderSettings.setName("Render settings");
	renderSettings.add(ortho.setup("Orthographic view", false));
	renderSettings.add(showGrid.setup("Show grid", true));

	info.setup();
	info.setName("Info");
	segCount.set("Segment count", (int)lattice.size(), 0, 100);
	info.add(segCount);
	info.add(buildMode.setup("Build mode on/off", true));

	buildTools.setup();
	buildTools.setName("Build mode");
	buildTools.add(guideWidth.setup("Guide grid x size", 10, 1, 50));
	buildTools.add(guideHeight.setup("Guide grid y size", 5, 1, 50));

	//cursorInfo.setup();
	//cursorInfo.setName("Segment");
	//cursorInfo.add(segment_on.setup("Lights on", lattice[latticeInspect].on));



	renderSettings.setPosition(50, 0);
	info.setPosition(50, 100);
	buildTools.setPosition(50, 200);
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
	dragging = true;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (buildMode) {
		if (!dragging) {
			addSection(currentPos, currentRot);
		}
		else {
			dragging = false;
		}
	}
	else{
		if (!dragging) {
			//inspect mode
			if (lattice[latticeInspect].on) {
				lattice[latticeInspect].on = false;
				std::cout << "Turning off " << inspected.id << endl;
			}
			else {
				std::cout << "Turning on " << inspected.id << endl;
				lattice[latticeInspect].on = true;

			}
		}
		else {
			dragging = false;
		}
	}
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


