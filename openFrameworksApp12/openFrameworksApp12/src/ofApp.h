#pragma once

#include "ofMain.h"
#include "../addons/ofxGui/src/ofxGui.h"


class ofApp : public ofBaseApp{
	struct section {
		ofBoxPrimitive mesh;
		ofPoint pos;
		ofColor color;
		int rot;
		int id;
		//bool on;
		ofParameter<bool> on;
		ofxPanel gui;
	};

	public:
		void setup();
		void update();
		void draw();

		void updateGrid();
		void renderLattice();
		void addSection(ofPoint pos, int rot);
		void inspectMode();
		void setupGui();

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
		void drawBox(float x, float y, float z, float deg);

		ofxPanel currentGui;
			
		ofEasyCam easyCam;
		vector<section>lattice;
		section ghostSec;
		section inspected;

		int latticeInspect;

		ofBoxPrimitive ghost;

		ofPoint currentPos;

		int currentRot;
		bool validPos;

		ofPoint mouse;

		ofxPanel renderSettings;
		ofxToggle ortho;
		ofxToggle showGrid;

		ofxPanel info;
		ofParameter<int> segCount;
		ofxToggle buildMode;

		ofxPanel buildTools;
		ofxIntSlider guideHeight;
		ofxIntSlider guideWidth;

		ofxPanel cursorInfo;
		ofParameter<char> id;
		ofxToggle segment_on;

		bool dragging;

		ofSerial serial;
		bool lastState;
		unsigned char b1;
		unsigned char b2;



};
