#include "testApp.h"
#include "ofxTweenzor.h"
#include "sxSpritePersp.h"
#include "sxDirector.h"
#define MINBREATH 70.
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
    points[i] = MINBREATH;
  }
  lastPoint = 0;
  isPulsarRight = false;
  human1.loadImage("personne.png");
  human1.points = &points;
  human1.setPosition(300,450);
  human1.setDraggable(true);
  human1.setRotatable(true);
  human1.setScalable(true);
  sxDirector::addChild(human1.node());

  human2.loadImage("personne.png");
  human2.points = &points;
  human2.setPosition(400,200);
  human2.setDraggable(true);
  human2.setRotatable(true);
  human2.setScalable(true);
  sxDirector::addChild(human2.node());
}

//--------------------------------------------------------------
void testApp::setPulsarLeftForPoint(unsigned int i){
  pulsarLeftPoint = i-1;
  isPulsarLeft = true;

  Tweenzor::add(&points[pulsarLeftPoint],points[pulsarLeftPoint], 100.f, 0.f, 0.03f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&points[pulsarLeftPoint]), this, &testApp::pulsarLeft);
}

//--------------------------------------------------------------
void testApp::pulsarLeft(float* arg){
  Tweenzor::add(&points[pulsarLeftPoint], 100.f, MINBREATH, 0.f, 2.0f);

  if (pulsarLeftPoint > 0){
    pulsarLeftPoint--;
    Tweenzor::add(&points[pulsarLeftPoint],points[pulsarLeftPoint], 100.f, 0.f, 0.03f);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&points[pulsarLeftPoint]), this, &testApp::pulsarLeft);
  } else {
    isPulsarLeft = false;
  }
}
//--------------------------------------------------------------
void testApp::setPulsarRightForPoint(unsigned int i){
  pulsarRightPoint = i+1;
  isPulsarRight = true;

  Tweenzor::add(&points[pulsarRightPoint],points[pulsarRightPoint], 100.f, 0.f, 0.03f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&points[pulsarRightPoint]), this, &testApp::pulsarRight);
}

//--------------------------------------------------------------
void testApp::pulsarRight(float* arg){
  Tweenzor::add(&points[pulsarRightPoint], 100.f, MINBREATH, 0.f, 2.0f);

  pulsarRightPoint++;
  if (pulsarRightPoint < points.size()){
    Tweenzor::add(&points[pulsarRightPoint],points[pulsarRightPoint], 100.f, 0.f, 0.03f);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&points[pulsarRightPoint]), this, &testApp::pulsarRight);
  } else {
    isPulsarRight = false;
  }
}

//--------------------------------------------------------------
void testApp::setBreathingForPoint(unsigned int i){
  //Tweenzor::getTween(&points[breathingPoint])->remove();
  //Tweenzor::add(&points[breathingPoint], points[breathingPoint], MINBREATH, 0.f, 2.0f);
  if (isPulsarRight && i > pulsarRightPoint){
    isPulsarRight = false;
  }
  if (isPulsarLeft && i < pulsarLeftPoint){
    isPulsarLeft = false;
  }

  Tweenzor::add(&points[breathingPoint], 100.f, MINBREATH, 0.f, 2.0f);

  breathingPoint = i;
  Tweenzor::add(&points[i],points[i], 100.f, 0.f, 0.1f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&points[i]), this, &testApp::breath);
}

//--------------------------------------------------------------
void testApp::breath(float* arg) {
  float breathMin = MINBREATH;
  float breathMax = 100;
  if (*arg > breathMax-1){
    //go down
    Tweenzor::add(&points[breathingPoint],points[breathingPoint], breathMin, 0.f, 2.0f);
  } else {
    Tweenzor::add(&points[breathingPoint],points[breathingPoint], breathMax, 0.f, 2.0f);
  }
  Tweenzor::addCompleteListener(Tweenzor::getTween(&points[breathingPoint]), this, &testApp::breath);
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
    ofSetColor(255.*points[i]/100.);
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
    points[i] = MINBREATH;
  }*/
  /*
  y = human1.y + human1.height/2;
  y = ofGetHeight() -y;
  int size = ofGetHeight()/points.size()/2.;
  unsigned int point = ceil(y/size);
  cout << "point: " << point << endl;
  if (point > 55){
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
