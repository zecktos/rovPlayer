#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "player.h"


class oscControl : public ofThread{
	public:
	ofxOscReceiver oscReceiver;
	vector<Player> & players;

	oscControl(vector<Player> & p) : players(p){}

	void setup(vector<Player> & p){
	    players = p;
	}
	void setPort(int  port){
	    if(oscReceiver.isListening()){oscReceiver.stop();}
	    oscReceiver.setup(port);
	    ofLog() << "listening for osc messages on port " << port;
}
	
	protected:
	void threadedFunction() override {
	while(isThreadRunning()){
	    while(oscReceiver.hasWaitingMessages()){
	      lock();
	      ofxOscMessage msg;
	      oscReceiver.getNextMessage(msg);
	      ofLog() << msg;
	      vector<string> addr = ofSplitString(msg.getAddress(),"/");
	      if(addr[1] == "settings"){
		  if(addr[2] == "fullscreen"){ofToggleFullscreen();}

	      }
	      
	      else{
		  int index = msg.getArgAsInt(0);
		  if(index < players.size() && index >= 0 ){
		      if(addr[1] == "play"){ players[index].play();}
		      if(addr[1] == "stop"){ players[index].stop();}
		      if(addr[1] == "togglePause"){ players[index].togglePause();}
		      if(msg.getNumArgs() == 2){
			  if(addr[1] == "load"){ players[index].video.load(msg.getArgAsString(1));}
			  if(addr[1] == "loop"){ players[index].setLoop(msg.getArgAsInt(1));}
			  if(addr[1] == "pause"){ players[index].setPause(msg.getArgAsBool(1));}
			  if(addr[1] == "loadShaderA"){ players[index].loadShaderA(msg.getArgAsString(1));}
			  if(addr[1] == "loadShaderB"){ players[index].loadShaderB(msg.getArgAsString(1));}
			  if(addr[1] == "enableShaderA"){ players[index].enableShaderA(msg.getArgAsBool(1));}
			  if(addr[1] == "enableShaderB"){ players[index].enableShaderB(msg.getArgAsBool(1));}
			  if(addr[1] == "setShaderA"){ players[index].setShaderA(msg.getArgAsFloat(1));}
			  if(addr[1] == "setShaderB"){ players[index].setShaderB(msg.getArgAsFloat(1));}
		      }
		      if(msg.getNumArgs() == 3){
			  if(addr[1] == "pause"){ players[index].setPause(msg.getArgAsBool(1),msg.getArgAsBool(2));}
			  if(addr[1] == "setPosition"){ players[index].surface.setPosition(msg.getArgAsInt(1), msg.getArgAsInt(2));}
			  if(addr[1] == "setShaderA"){ players[index].setShaderA(msg.getArgAsFloat(1), msg.getArgAsFloat(2));}
			  if(addr[1] == "setShaderB"){ players[index].setShaderB(msg.getArgAsFloat(1), msg.getArgAsFloat(2));}

		      }
		      if(msg.getNumArgs() == 4){
			  if(addr[1] == "setCorner"){
				  players[index].surface.setCorner(msg.getArgAsInt(1),
								   msg.getArgAsInt(2), 
								   msg.getArgAsInt(3));
			  }
			  if(addr[1] == "setShaderA"){ players[index].setShaderA(msg.getArgAsFloat(1), 
										 msg.getArgAsFloat(2),
										 msg.getArgAsFloat(3));
			  }
			  if(addr[1] == "setShaderB"){ players[index].setShaderB(msg.getArgAsFloat(1), 
										 msg.getArgAsFloat(2),
										 msg.getArgAsFloat(3));
			  }
		      }
		  }
	     }
	     unlock();
	  }
	  sleep(100);
       }
    }

};
