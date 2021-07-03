#include "mapper.h"

Mapper::Mapper (){

}

void Mapper::setup(int w,int h,int x,int y,int _rows,int _cols){
    font.load( OF_TTF_SANS,25,true,true,true);
    corners[0]=glm::vec2(x,y);
    corners[1]=glm::vec2(x+w,y);
    corners[2]=glm::vec2(x+w,y+h);
    corners[3]=glm::vec2(x,y+h);
    selectedCorner=-1;
    rows=_rows;
    cols=_cols;
    warp= true;
}

void Mapper::enableMouseControls() {

    ofAddListener(ofEvents().mousePressed, this, &Mapper::onMousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &Mapper::onMouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &Mapper::onMouseReleased);
}

void Mapper::disableMouseControls() {

    ofRemoveListener(ofEvents().mousePressed, this, &Mapper::onMousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this, &Mapper::onMouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &Mapper::onMouseReleased);
}

glm::vec2 ofxLerp(glm::vec2 start, glm::vec2 end, float amt) {

    return start + amt * (end - start);
}

int ofxIndex(float x, float y, float w) {

    return y*w+x;
}

void Mapper::draw(ofBaseHasTexture & tex){

    float tw = tex.getTexture().getWidth();
    float th = tex.getTexture().getHeight();

    ofMesh mesh;


    for (int x=0; x<=cols; x++) {
        float f = float(x)/cols;
	glm::vec2 vTop(ofxLerp(corners[0],corners[1],f));
	glm::vec2 vBottom(ofxLerp(corners[3],corners[2],f));
	glm::vec2 tTop(ofxLerp(glm::vec2(0,0),glm::vec2(tw,0),f));
        glm::vec2 tBottom(ofxLerp(glm::vec2(0,th),glm::vec2(tw,th),f));

        for (int y=0; y<=rows; y++) {
            float f = float(y)/rows;
            ofPoint v = ofxLerp(vTop,vBottom,f);
            mesh.addVertex(v);
            mesh.addTexCoord(ofxLerp(tTop,tBottom,f));
        }
    }

    for (int y=0; y<rows; y++) {
        for (int x=0; x<cols; x++) {
            mesh.addTriangle(ofxIndex(x,y,cols+1), ofxIndex(x+1,y,cols+1), ofxIndex(x,y+1,cols+1));
            mesh.addTriangle(ofxIndex(x+1,y,cols+1), ofxIndex(x+1,y+1,cols+1), ofxIndex(x,y+1,cols+1));
        }
   }


    tex.getTexture().bind();
    mesh.draw();
    tex.getTexture().unbind();


    if(warp==true){
        mesh.drawVertices();
        for (int i=0; i<4; i++) {
                ofSetColor(150,80,255,100);
                ofDrawCircle(corners[i],10);
		ofSetColor(50,255,0);
		ofDrawBitmapString(ofToString(corners[i].x) + " | " + ofToString(corners[i].y) ,corners[i]);
		
	}
	centerX=mesh.getCentroid().x;
	centerY=mesh.getCentroid().y;
        ofSetColor(150,80,255,100);
        ofDrawCircle(centerX, centerY,10);
	ofSetColor(50,255,0);
	ofDrawBitmapString(ofToString(centerX) + " | " + ofToString(centerY) , centerX, centerY);
	ofSetColor(255,255,255);
	centerX=mesh.getCentroid().x;
	centerY=mesh.getCentroid().y;
    }

}

void Mapper::setPosition(int x, int y) {
    int xOff = x - corners[0].x;
    int yOff = y - corners[0].y;
    for(int i=0; i<4; i++){
	corners[i]=glm::vec2(corners[i].x + xOff,corners[i].y + yOff);
    }
   
}

void Mapper::setCorner(int i, int x, int y) {
    corners[i].x = x;
    corners[i].y = y;
}

void Mapper::onMouseDragged(ofMouseEventArgs& mouseArgs) {

    if(selectedCorner==5){
    	for(int i=0; i<4; i++){
          corners[i]=glm::vec2(corners[i].x+(ofGetMouseX()-ofGetPreviousMouseX()),corners[i].y+(ofGetMouseY()-ofGetPreviousMouseY()));
        }
      }

    if(selectedCorner >= 0 && selectedCorner < 4){corners[selectedCorner]=glm::vec2(ofGetMouseX(),ofGetMouseY());}

}

void Mapper::onMousePressed (ofMouseEventArgs& mouseArgs) {

    selectedCorner = -1;
    for (int i=0; i<4; i++) {
	if (ofDist(corners[i].x, corners[i].y, ofGetMouseX(), ofGetMouseY())<10) {
	    selectedCorner = i;}
      }

     if(ofDist(centerX,centerY,ofGetMouseX(),ofGetMouseY())<10){
	    selectedCorner = 5;}

}

void Mapper::onMouseReleased(ofMouseEventArgs& mouseArgs) {
    selectedCorner = -1;
}

void Mapper::toggleWarp(){

  if(warp==false){
     enableMouseControls();
    }

  else {disableMouseControls();}

    warp= !warp;
}

