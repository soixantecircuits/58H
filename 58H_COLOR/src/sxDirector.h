#pragma once

#include "ofMain.h"
#include "sxNode.h"
#include "ofxTuio.h"

class sxDirector{

	public:
		static void setup();
		static void update();
		static void draw();

		static void keyPressed  (int key);
		static void keyReleased(int key);
		static void mouseMoved(int x, int y );
		static void mouseDragged(int x, int y, int button);
		static void mousePressed(int x, int y, int button);
		static void mouseReleased(int x, int y, int button);
		static void cursorPressed(ofxTuioCursor &tuioCursor);
		static void cursorDragged(ofxTuioCursor &tuioCursor);
		static void cursorReleased(ofxTuioCursor &tuioCursor);
		static void windowResized(int w, int h);
		static void dragEvent(ofDragInfo dragInfo);
		static void gotMessage(ofMessage msg);

    static void	tuioAdded(ofxTuioCursor & tuioCursor);
    static void	tuioRemoved(ofxTuioCursor & tuioCursor);
    static void	tuioUpdated(ofxTuioCursor & tuioCursor);
		
    static void addChild(sxNode* sprite );
    static void removeChild(sxNode* sprite);
    static float getHighestZOrder();
    static float getHighestZOrder(string type);
    static sxDirector* instance();

protected:
	sxDirector() {};

  private:
    static sxDirector* __instance;
    vector<sxNode*> _sprites;
};
