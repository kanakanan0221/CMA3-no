#pragma once

#include "ofMain.h"

#include "ofxLeapMotion2.h"



class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    void exit();
    
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simpleHands;
    
    ofEasyCam cam;
    
    vector<ofVec3f> fingerPos;
    vector<ofPoint> handPos;
    
       ofImage manbo1;
    ofImage manbo2;
    ofImage img01_body, img01_mouse1, img01_mouse2;
    
    ofRectangle rectangle;

    
    
       
};
