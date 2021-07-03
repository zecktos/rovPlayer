#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "oscControl.h"
#include "player.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void portChanged(string & portParameter);
		void vsyncChanged(bool & vsyncParameter);

		
		vector<Player> players;
		oscControl * oscThread;
		ofxXmlSettings posLayout;

		ofxPanel gui;
		bool editMode;
		ofTrueTypeFont font;
		
		ofParameter<string> portParameter;
		ofParameter<string> playerWidthParameter;
		ofParameter<string> playerHeightParameter;
		ofParameter<bool> vsyncParameter;
		ofParameter<bool> saveOnExit;

};
