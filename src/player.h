#pragma once

#include "ofMain.h"
#include "mapper.h"

class Player {

	public:

	int width;
	int height;
	int xpos;
	int ypos;
	bool isNew;
	ofVideoPlayer video;
	Mapper surface;
	ofImage frame;
	ofFbo 	fboA, fboB;
	ofShader shaderA, shaderB;
	bool shaderModeA, shaderModeB, shaderLoadA, shaderLoadB, black;
	float shaderValA[4], shaderValB[4];
	string shaderFileA, shaderFileB;

	Player (int x, int y, int w, int h){
		width = w;
		height = h;
		xpos = x;
		ypos = y;
		int res = width/20;
		surface.setup( width, height, xpos, ypos, res, res);
		frame.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
		frame.setColor(0);
		fboA.allocate(width, height);
		shaderFileA = "shader/default.frag";
		shaderA.load("",shaderFileA);
		shaderLoadA = false;
		shaderModeA = false;
		fboB.allocate(width, height);
		shaderModeB = false;
		shaderLoadB = false;
		shaderFileB = "shader/default.frag";
		shaderB.load("",shaderFileB);
		black = false;

	}

    void draw(){

	if(video.isLoaded()){video.update();}
	if(video.isFrameNew()){
	    frame = video.getPixels();
	    if(frame.getWidth() != width || frame.getHeight() != height){
		frame.resize(width, height);}
	}
	if(black == true){ frame.setColor(0);}
	
	frame.update();

	fboA.begin();
	ofClear(255, 255, 255, 255);
	if(shaderModeA == true){
	    shaderA.begin();
	    shaderA.setUniform2f("resolution",(float)width,(float)height);
	    shaderA.setUniform1f("time",ofGetElapsedTimef());
	    shaderA.setUniform4f("controlVal",shaderValA[0], shaderValA[1], shaderValA[2], shaderValA[3]);
	    frame.draw(0,0);
	    shaderA.end();
	}
	else{ frame.draw(0,0);}
	fboA.end();

	fboB.begin();
	ofClear(255, 255, 255, 255);
	if(shaderModeB == true){
	    shaderB.begin();
	    shaderB.setUniform2f("resolution",(float)width,(float)height);
	    shaderB.setUniform1f("time",ofGetElapsedTimef());
	    shaderB.setUniform4f("controlVal",shaderValB[0], shaderValB[1], shaderValB[2], shaderValB[3]);
	    fboA.draw(0,0);
	    shaderB.end();
	}
	else{ fboA.draw(0,0);}
	fboB.end();

	surface.draw(fboB);

	
    }

    void update(){
	if(shaderLoadA == true){
	    shaderA.load("",shaderFileA);
	    shaderLoadA = false;
	}

	if(shaderLoadB == true){
	    shaderB.load("",shaderFileB);
	    shaderLoadB = false;
	}
    }

    void play(){
	black = false;
	video.play();
    }

    void stop(){
	video.stop();
	shaderModeA = false;
	shaderModeB = false;
	black = true;
    }

    void setPause(const bool & mode, const bool & _black=false){
	video.setPaused(mode);
	black = _black;
    }

    void togglePause(const bool & _black=false){
	if(video.isPaused()){ 
	    video.setPaused(false);
	    black = false;
	}
	else{ 
	    video.setPaused(true);
	    black = _black;
	}
    }

    void setLoop(const int & mode){
	if(mode == 0){ video.setLoopState(OF_LOOP_NONE);}
	if(mode == 1){ video.setLoopState(OF_LOOP_NORMAL);}
	if(mode == 2){ video.setLoopState(OF_LOOP_PALINDROME);}
    }

    void loadShaderA(const string & pathToShader, const bool & mode=false){
	shaderFileA =  pathToShader;
	shaderLoadA = true;
	shaderModeA = mode;
    }

    void loadShaderB(const string & pathToShader){
	shaderFileB =  pathToShader;
	shaderLoadB = true;
	shaderModeB = true;
    }

    void enableShaderA(const bool & mode){
	shaderModeA = mode;
    }

   void enableShaderB(const bool & mode){
	shaderModeB = mode;
    }

   void setShaderA(const float & valA=0.0, const float & valB=0.0, const float & valC=0.0, const float & valD=0.0){
       shaderValA[0] = valA;
       shaderValA[1] = valB;
       shaderValA[2] = valC;
       shaderValA[3] = valD;
   }

   void setShaderB(const float & valA=0.0, const float & valB=0.0, const float & valC=0.0, const float & valD=0.0){
       shaderValB[0] = valA;
       shaderValB[1] = valB;
       shaderValB[2] = valC;
       shaderValB[3] = valD;
   }


};

