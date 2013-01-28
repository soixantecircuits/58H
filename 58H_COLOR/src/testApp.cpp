#include "testApp.h"
#include "ofxTweenzor.h"
#include "sxSpritePersp.h"
#include "sxDirector.h"
sxSpritePersp human1;
sxSpritePersp human2;
//--------------------------------------------------------------
void testApp::setup(){
  ofEnableAlphaBlending();
  Tweenzor::init();
  sxDirector::setup();
  ofBackground(0);
  points.resize(55);
  for (unsigned int i = 0; i < points.size(); i++){
    points[i].x = 0.;
    points[i].y = 0.;
    points[i].z = 255.;
  }
  lastPoint = 0;
  isPulsarRight = false;
  human1.loadImage("personne.png");
  human1.points = &points;
  human1.hues.resize(points.size());
  human1.setPosition(300,450);
  human1.setDraggable(true);
  human1.setRotatable(true);
  human1.setScalable(true);
  sxDirector::addChild(human1.node());

  human2.loadImage("personne.png");
  human2.points = &points;
  human2.hues.resize(points.size());
  human2.setPosition(400,200);
  human2.setDraggable(true);
  human2.setRotatable(true);
  human2.setScalable(true);
  sxDirector::addChild(human2.node());
  //human1.hue = 85;
  human1.hue = 170;
  human2.hue = 0;
}

//--------------------------------------------------------------
void testApp::update(){
  sxDirector::update();
  Tweenzor::update( ofGetElapsedTimeMillis() );
}

//--------------------------------------------------------------
void testApp::draw(){
  ofBackgroundGradient(ofColor::white, ofColor::gray);
  sxDirector::draw();
  ofSetColor(ofColor::blue);
  int size = ofGetHeight()/points.size()/2.;
  for (unsigned int i = 0; i < points.size(); i++){
    float hue = 0;
    if (human1.hues[i] < 0.05 && human2.hues[i] > 0.05){
      hue = human2.hue;
    }
    if (human1.hues[i] > 0.05 && human2.hues[i] < 0.05){
      hue = human1.hue;
    }
    if (human1.hues[i] > 0.05 && human2.hues[i] > 0.05){
      hue = (ofColor::fromHsb(human1.hue, 255, 255) + ofColor::fromHsb(human2.hue, 255, 255)).getHue();
    }
    ofSetColor(ofColor::fromHsb(hue, 255.*points[i].y/100., 255.*points[i].z/100.));
    //ofLine(i*size,10,(i+1)*size,10); //2D
    float y1 = i*size;
    float y2 = (i+1)*size;
    float x1 = y1*1.3;
    float x2 = y2*1.3;
    y1 = ofGetHeight() - y1;
    y2 = ofGetHeight() - y2;
    ofLine(x1, y1, x2, y2); //2D
    ofLine(x1, ofGetHeight() - y1, x2, ofGetHeight() - y2); //2D
    ofLine(ofGetWidth()-x1, y1, ofGetWidth()-x2, y2); //2D
    ofLine(ofGetWidth()-x1, ofGetHeight() - y1, ofGetWidth()-x2, ofGetHeight() - y2); //2D
  }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  switch(key){
    case 'a':
      human1.y--;
      break;
    case 'q':
      human1.y++;
      break;
    case 'p':
      human2.y--;
      break;
    case 'm':
      human2.y++;
      break;
  }
  human1.renderMove();
  human2.renderMove();

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
  sxDirector::mouseMoved(x,y);
  human1.renderMove();
  human2.renderMove();
  /*for (unsigned int i = 0; i < points.size(); i++){
    points[i] = MIN;
  }*/
  /*
  y = human1.y + human1.height/2;
  y = ofGetHeight() -y;
  int size = ofGetHeight()/points.size()/2.;
  unsigned int point = ceil(y/size);
  cout << "point: " << point << endl;
:cn

:cn
:cn
    point = 54;
  }
  if (point != lastPoint){
    setBreathingForPoint(point);
    //points[point] = 100;
    if (point > lastPoint){
      if (!isPulsarRight){
        setPulsarRightForPoint(point);
      }
    }
    else if (point < lastPoint){
      if (!isPulsarLeft && point > 0){
        setPulsarLeftForPoint(point);
      }
    }
    lastPoint = point;
  }
  */
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  sxDirector::mouseDragged(x,y, button);
  human1.renderMove();
  human2.renderMove();

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  sxDirector::mousePressed(x,y, button);
  human1.renderMove();
  human2.renderMove();

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
  sxDirector::mouseReleased(x,y, button);
  human1.renderMove();
  human2.renderMove();

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
