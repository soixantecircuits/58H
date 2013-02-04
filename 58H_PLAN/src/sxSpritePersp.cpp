#include "sxSpritePersp.h"
#include "ofxTweenzor.h"
#define MINBREATH 70.f

//--------------------------------------------------------------
void sxSpritePersp::drawContent(){
  ofFill();
  ofSetColor(0);
  ofEllipse(0, -10, 5, 5);
  ofLine(0, -2, 0, 10);
  ofLine(-6, -2, 0, -2);
  sxNode::drawContent();
}
//--------------------------------------------------------------
void sxSpritePersp::renderMove( ){
  /*for (unsigned int i = 0; i < (*points).size(); i++){
    (*points)[i] = MINBREATH;
  }*/
  int size = (746 - 284)/28;
  int start = 284;
  unsigned int point = 0;
  if ( x < start){
    point = 0;
  }
  else if ( x < start + size*(*points).size()/2){
    point = floor((x - start)/size);
  }
  else if ( x < start + size*(8+(*points).size()/2)){
    point = (*points).size()/2;
  }
  else if ( x < start + size*(8+(*points).size())){
    float startofthis = start + ( 8 + (*points).size()/2)*size; 
    point = ((*points).size()/2) + floor((x - startofthis)/size);
  }
  else {
    point = (*points).size() - 1;
  }
  cout << "point: " << point << endl;

  if (point >= (*points).size()){
    point = (*points).size()-1;
  }
  Tween* t = Tweenzor::getTween(&(*points)[point]);
  if (t == 0){
    setBreathingForPoint(point);
  }

  if (point != lastPoint){
    setBreathingForPoint(point);
    //(*points)[point] = 100;
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

}
//--------------------------------------------------------------
void sxSpritePersp::setPulsarLeftForPoint(unsigned int i){
  pulsarLeftPoint = i-1;
  isPulsarLeft = true;

  Tweenzor::add(&(*points)[pulsarLeftPoint],(*points)[pulsarLeftPoint], 100.f, 0.f, 0.03f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[pulsarLeftPoint]), this, &sxSpritePersp::pulsarLeft);
}

//--------------------------------------------------------------
void sxSpritePersp::pulsarLeft(float* arg){
  Tweenzor::add(&(*points)[pulsarLeftPoint], 100.f, MINBREATH, 0.f, 2.0f);

  if (pulsarLeftPoint > 0){
    pulsarLeftPoint--;
    Tweenzor::add(&(*points)[pulsarLeftPoint],(*points)[pulsarLeftPoint], 100.f, 0.f, 0.03f);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[pulsarLeftPoint]), this, &sxSpritePersp::pulsarLeft);
  } else {
    isPulsarLeft = false;
  }
}
//--------------------------------------------------------------
void sxSpritePersp::setPulsarRightForPoint(unsigned int i){
  pulsarRightPoint = i+1;
  isPulsarRight = true;

  Tweenzor::add(&(*points)[pulsarRightPoint],(*points)[pulsarRightPoint], 100.f, 0.f, 0.03f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[pulsarRightPoint]), this, &sxSpritePersp::pulsarRight);
}

//--------------------------------------------------------------
void sxSpritePersp::pulsarRight(float* arg){
  Tweenzor::add(&(*points)[pulsarRightPoint], 100.f, MINBREATH, 0.f, 2.0f);

  pulsarRightPoint++;
  if (pulsarRightPoint < (*points).size()){
    Tweenzor::add(&(*points)[pulsarRightPoint],(*points)[pulsarRightPoint], 100.f, 0.f, 0.03f);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[pulsarRightPoint]), this, &sxSpritePersp::pulsarRight);
  } else {
    isPulsarRight = false;
  }
}

//--------------------------------------------------------------
void sxSpritePersp::setBreathingForPoint(unsigned int i){
  //Tweenzor::getTween(&(*points)[breathingPoint])->remove();
  //Tweenzor::add(&(*points)[breathingPoint], (*points)[breathingPoint], MINBREATH, 0.f, 2.0f);
  if (isPulsarRight && i > pulsarRightPoint){
    isPulsarRight = false;
  }
  if (isPulsarLeft && i < pulsarLeftPoint){
    isPulsarLeft = false;
  }

  Tweenzor::add(&(*points)[breathingPoint], 100.f, MINBREATH, 0.f, 2.0f);

  breathingPoint = i;
  Tweenzor::add(&(*points)[i],(*points)[i], 100.f, 0.f, 0.1f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[i]), this, &sxSpritePersp::breath);
}

//--------------------------------------------------------------
void sxSpritePersp::breath(float* arg) {
  float breathMin = MINBREATH;
  float breathMax = 100;
  if (*arg > breathMax-1){
    //go down
    Tweenzor::add(&(*points)[breathingPoint],(*points)[breathingPoint], breathMin, 0.f, 2.0f);
  } else {
    Tweenzor::add(&(*points)[breathingPoint],(*points)[breathingPoint], breathMax, 0.f, 2.0f);
  }
  Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[breathingPoint]), this, &sxSpritePersp::breath);
}
