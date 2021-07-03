#pragma once

#include "ofMain.h"


class Mapper
{
public:

    Mapper ();

    void setup(int w,int h,int x,int y,int _rows,int _cols);
    void enableMouseControls();
    void disableMouseControls();
    void draw(ofBaseHasTexture & tex);
    void toggleWarp();
    void setPosition(int x, int y);
    void setCorner(int i, int x, int y);


    glm::vec2 corners [4];
    int centerX;
    int centerY;
    int selectedCorner;
    int rows;
    int cols;
    bool warp;
    ofTrueTypeFont font;


private:
    void onMousePressed(ofMouseEventArgs & mouseArgs);
    void onMouseDragged(ofMouseEventArgs & mouseArgs);
    void onMouseReleased(ofMouseEventArgs & mouseArgs);

};

