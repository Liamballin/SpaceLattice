#include "Serial.h"

void Serial::setup(int baud) {
	mode = 0;
	s.listDevices();
	vector <ofSerialDeviceInfo> deviceList = s.getDeviceList();
	//for (int i = 0; i < deviceList.size(); i++) {
	//	std::cout << to_string(deviceList[i]) << endl;

	//}
	
	s.setup(0, baud);
	lastState = false;
	b1 = 255;
	b2 = 0;
}

void Serial::setMode(int m) {
	mode = m;
}

int Serial::getMode() {
	return mode;
}

void Serial::update(vector<section> l) {
	if (l.size() > 0) {
		if (l[0].on != lastState) {
			if (l[0].on) {

				s.writeByte(b1);
				std::cout << "Sending byte " << b1 << endl;

			}
			else {
				s.writeByte(b2);
				std::cout << "Sending byte " << b2 << endl;

			}
		}
		lastState = l[0].on;
	}
}