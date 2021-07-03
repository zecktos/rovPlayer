#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	font.load( OF_TTF_SANS,9,true,true);
	editMode = false;
	
	oscThread = new oscControl(players);
	gui.setup();
	gui.add(vsyncParameter.set("vSync", true));
	gui.add(saveOnExit.set("save layout on exit", true));
	gui.add(portParameter.set("port", "3030"));
	gui.add(playerWidthParameter.set("new player width", "720"));
	gui.add(playerHeightParameter.set("new player height", "480")); 
	
	portParameter.addListener(this, &ofApp::portChanged);
	vsyncParameter.addListener(this, &ofApp::vsyncChanged);

	gui.loadFromFile("settings.xml");

	if(posLayout.loadFile("positions.xml")){
		if(posLayout.tagExists("SESSION")){
			posLayout.pushTag("SESSION");
			for(int i=0; i < posLayout.getNumTags("PLAYER"); i++){
				posLayout.pushTag("PLAYER", i);
				int w = posLayout.getValue("WIDTH", 720);
				int h = posLayout.getValue("HEIGHT", 480);
				if(posLayout.getNumTags("CORNER") != 4){
					ofLog() << "error in positions.xml";
					ofExit();
				}
				ofVec2f corner[4];
				for(int j=0; j < 4; j++){
					posLayout.pushTag("CORNER",j);
					corner[j].x = posLayout.getValue("X",0);
					corner[j].y = posLayout.getValue("Y",0);
					posLayout.popTag();
				}
				players.push_back(Player(0,0,w,h));
				for(int c=0; c < 4; c++){
					players[i].surface.setCorner(c, (int)corner[c].x, (int)corner[c].y);
					players[i].surface.warp = false;
				}
				posLayout.popTag();
			}
			posLayout.popTag();
			ofLog() << "loaded positions"; 
		}
	}
	else{ ofLog() << "unable to load positions.xml";}

	ofSetWindowTitle("rovPlayer");
	ofBackground(0);
	ofSetVerticalSync(vsyncParameter);
	oscThread->startThread(true);
	
}

void ofApp::exit(){
	oscThread->stopThread();
	oscThread->waitForThread();
	delete oscThread;
	ofLog()<< "save settings..";
	gui.saveToFile("settings.xml");
	if(saveOnExit == true){
		ofLog()<< "save layout";
		posLayout.clear();
		posLayout.addTag("SESSION");
		posLayout.pushTag("SESSION", 0);
		for(int i=0; i < players.size(); i++){
			posLayout.addTag("PLAYER");
			posLayout.pushTag("PLAYER", i);
			posLayout.addValue("WIDTH", players[i].width);
			posLayout.addValue("HEIGHT", players[i].height);
			for (int j=0; j < 4; j++){
				posLayout.addTag("CORNER");
				posLayout.pushTag("CORNER", j);
				posLayout.addValue("X", players[i].surface.corners[j].x);
				posLayout.addValue("Y", players[i].surface.corners[j].y);
				posLayout.popTag();
			}
			posLayout.popTag();
		}
		posLayout.popTag();
		posLayout.saveFile("positions.xml");
	}
	ofLog()<< "exit app";
}


void ofApp::portChanged(string & portParameter){
	oscThread->setPort(ofToInt(portParameter));
}

void ofApp::vsyncChanged(bool & vsyncParameter){
	ofSetVerticalSync(vsyncParameter);
}

//--------------------------------------------------------------
void ofApp::update(){
	for(int i = 0; i < players.size(); i++){
		players[i].update();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	for(int i = 0; i < players.size(); i++){
		players[i].draw();
	}

	if(editMode){
		gui.draw();
		font.drawString("fps: " + ofToString((int)ofGetFrameRate()),ofGetWidth()-150,40);
		font.drawString("a -> add player", ofGetWidth()-150, 80);
		font.drawString("R -> remove last player", ofGetWidth()-150, 100);
		font.drawString("f -> toggle fullscreen", ofGetWidth()-150, 120);
		font.drawString("num of players :" + ofToString(players.size()), ofGetWidth()-150, 140);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'e'){
		editMode = !editMode;
		for(int i=0; i < players.size(); i++){
			players[i].surface.toggleWarp();
		}
	}

	if(key == 'f'){ ofToggleFullscreen();}
			
	if(key == 'a' && editMode == true){ 
		players.push_back(Player(mouseX - ofToInt(playerWidthParameter)/2, 
					 mouseY - ofToInt(playerHeightParameter)/2, 
					 ofToInt(playerWidthParameter), 
					 ofToInt(playerHeightParameter)));
		players[players.size()-1].surface.enableMouseControls();	
	}
	
	if(key == 'R' && editMode == true){
		if(players.size() >= 1){ players.erase(players.end());}
	}

}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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


