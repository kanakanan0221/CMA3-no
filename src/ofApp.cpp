#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
//           p.setIntialCondition(ofGetWidth()/2, ofGetHeight()/2, ofRandom(-10,10), ofRandom(-10,10));
    
    cam.setOrientation(ofPoint(-20,0,0));
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    leap.open();
    ofEnableAlphaBlending();
    ofRectMode();

//    manbo1.loadImage("名称未設定-111.png");
//    manbo2.loadImage("名称未設定1111.png");
    img01_body.loadImage("body_dag.png");
    img01_mouse1.loadImage("ue.png");
    img01_mouse2.loadImage("sita.png");
    
    rectangle.set(20, 20, 100, 100);//座標、幅、高さをセット
    


    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    simpleHands = leap.getSimpleHands();
    if (leap.isFrameNew() && simpleHands.size() ) {
        fingerPos.clear();
        
        handPos.clear();
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2
                         , ofGetHeight()/2);
        leap.setMappingZ(-150,150,-200,200);
        
        fingerType fingerTypes[] = {THUMB, INDEX,MIDDLE,RING,PINKY};
        
        for (int i = 0; i < simpleHands.size(); i++) {
            
            handPos.push_back(simpleHands[i].handPos);
            
            for (int f = 0; f<5 ; f++ ) {
                
                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;
                fingerPos.push_back(mcp);
                
                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;
                fingerPos.push_back(pip);
                
                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;
                fingerPos.push_back(dip);
                
                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;
                fingerPos.push_back(tip);
                
            }
        }
    }
    leap.markFrameAsOld();
    

    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(255, 255,255);
//  
    
    
    ofBackground(100);
    cam.begin();
    
    
    for (int i = 0; i <simpleHands.size(); i++) {
        for (int f =0; f<5; f++) {
            
            ofSetColor(0, 255, 0);
            ofDrawSphere(handPos.at(i), 20);//手の中心を描画
            
            ofSetColor(ofColor::fromHsb(255/4*f, 255, 255));
            
            ofDrawSphere(fingerPos.at(20*i+4*f+0),10);
            ofDrawSphere(fingerPos.at(20*i+4*f+1),10);
            ofDrawSphere(fingerPos.at(20*i+4*f+2),10);
            
            if (i==0 && (f==0 || f == 1)){//.at(3), (7) のとき
                ofSetColor(255, 255, 0);
            }

            ofDrawSphere(fingerPos.at(20*i+4*f+3),10);
            
            ofLine(fingerPos.at(20*i+4*f+0), fingerPos.at(20*i+4*f+1));
            ofLine(fingerPos.at(20*i+4*f+1), fingerPos.at(20*i+4*f+2));
            ofLine(fingerPos.at(20*i+4*f+2), fingerPos.at(20*i+4*f+3));
            
            
        }
        
    }
    
    
    float dist = 0;//関節の間の長さを保存する変数
    
    //fingerPos = 検出された指の関節の座標を保存
    //fingerPos.size = 保存されている座標の数
    if (fingerPos.size() != 0){//もしもfingerPosのサイズが、0じゃなかったら。つまり、指が検出されていたら。
        

        

        dist = ofDist(fingerPos.at(3).x, fingerPos.at(3).y, fingerPos.at(7).x, fingerPos.at(7).y) ;
    }
    
//        dist = 0;
        
        ofPushMatrix();
        
        
        ofDisableDepthTest();//深度関係を無効に。透過画像をきれいに表示するため。
        ofTranslate(fingerPos.at(3));//fingerPos.at(3)を原点に
        
        ofSetColor(255);
    img01_body.draw(-80, -img01_body.getHeight() + 60, img01_body.getWidth(), img01_body.getHeight());
        
        
        
        ofPushMatrix();
       ofTranslate(-img01_mouse1.getWidth() + img01_mouse2.getWidth(), 0);
        ofRotateZ(-dist);//-dist度（度数法）　回転
//        ofPoint pImg02 = ofPoint(-img01_mouse2.getWidth(), 0);
        img01_mouse2.draw(-80,-220, img01_mouse2.getWidth(), img01_mouse2.getHeight());
//        ofCircle(pImg02, 10);
        ofCircle(0, 0, 10);
        ofPopMatrix();
        
        
        ofPushMatrix();
        ofRotateZ(dist);//dist度（度数法）　回転
//        ofPoint pImg01 = ofPoint(-img01_mouse1.getWidth(), 0);
        img01_mouse1.draw(-90,-210, img01_mouse1.getWidth(), img01_mouse1.getHeight());
//        ofCircle(pImg01, 10);
        ofCircle(0, 0, 10);
        
        ofPopMatrix();
        
        
        ofEnableDepthTest();//深度関係を有効に
        ofPopMatrix();//元の座標に戻す
        
        cout << "x:" << fingerPos.at(7).x << "  y:" << fingerPos.at(7).y << "  z:" << fingerPos.at(7).z << endl;
        
    
    
    
    
    cam.end();
    
//    ofSetColor(255, 0, 0);
//    ofCircle(ofGetMouseX(), ofGetMouseY(), 10);
//    
//    ofSetColor(255);
//    img01_body.draw(rectangle);
    
    
    
}

void ofApp::exit(){
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
//    if (rectangle.inside(x, y)) {//もし、マウスがrectangleの中だったら
//        cout << "画像の中"<< endl;
//    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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
