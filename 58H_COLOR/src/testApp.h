#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void setBreathingForPoint(unsigned int i);
    void breath(float* arg);
    void setPulsarRightForPoint(unsigned int i);
    void pulsarRight(float* arg);
    void setPulsarLeftForPoint(unsigned int i);
    void pulsarLeft(float* arg);
		
    vector<ofVec3f> points;
    unsigned int breathingPoint;
    unsigned int lastPoint;
    bool isPulsarRight;
    bool isPulsarLeft;
    unsigned int pulsarRightPoint;
    unsigned int pulsarLeftPoint;

};
