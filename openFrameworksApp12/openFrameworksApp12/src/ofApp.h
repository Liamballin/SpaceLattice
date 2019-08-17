#pragma once

#include "ofMain.h"


class ofApp : public ofBaseApp{
	struct section {
		ofPoint pos;
		ofColor color;
		int rot;
	};

	public:
		void setup();
		void update();
		void draw();

		void updateGrid();
		void renderLattice();
		void addSection(ofPoint pos, int rot);

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
			
		ofEasyCam easyCam;
		vector<section>lattice;
		section ghostSec;

		ofBoxPrimitive ghost;

		ofPoint currentPos;

		int currentRot;
		bool validPos;

		ofPoint mouse;

};
