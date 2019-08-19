#pragma once

#include "ofMain.h"
//#include "ofApp.h"

class Serial {
public:

	struct section {
		ofBoxPrimitive mesh;
		ofPoint pos;
		ofColor color;
		int rot;
		int id;
		int mode;
		bool on;
	};
	


	void setup(int baud);

	void setMode(int mode);
	int getMode();

	void update(vector<section> l);

	int mode; //0 = load, 1 = live preview;

	ofSerial s;
	bool lastState;
	unsigned char b1;
	unsigned char b2;

	int baud_default = 9600;

};