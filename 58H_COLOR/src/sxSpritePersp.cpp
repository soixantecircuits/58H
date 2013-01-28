#include "sxSpritePersp.h"
#include "ofxTweenzor.h"
#define MINBREATH 0.f

//--------------------------------------------------------------
void sxSpritePersp::renderMove( ){
  /*for (unsigned int i = 0; i < (*points).size(); i++){
    (*points)[i] = MINBREATH;
  }*/
  float yy = y + height/2;
  yy = ofGetHeight() -yy;
  int size = ofGetHeight()/(*points).size()/2.;
  unsigned int point = ceil(yy/size);
  if (point >= (*points).size()){
    point = (*points).size()-1;
  }
  Tween* t = Tweenzor::getTween(&(*points)[point].y);
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
  Tweenzor::add(&hues[pulsarLeftPoint], 0.f, 1.f, 0.f, 2.0f);

  Tweenzor::add(&(*points)[pulsarLeftPoint].y,(*points)[pulsarLeftPoint].y, 100.f, 0.f, 0.03f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[pulsarLeftPoint].y), this, &sxSpritePersp::pulsarLeft);
}

//--------------------------------------------------------------
void sxSpritePersp::pulsarLeft(float* arg){
  Tweenzor::add(&(*points)[pulsarLeftPoint].y, 100.f, MINBREATH, 0.f, 2.0f);
  Tweenzor::add(&hues[pulsarLeftPoint], 1.f, 0.f, 0.f, 2.0f);

  if (pulsarLeftPoint > 0){
    pulsarLeftPoint--;
    Tweenzor::add(&hues[pulsarLeftPoint], 0.f, 1.f, 0.f, 2.0f);
    Tweenzor::add(&(*points)[pulsarLeftPoint].y,(*points)[pulsarLeftPoint].y, 100.f, 0.f, 0.03f);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[pulsarLeftPoint].y), this, &sxSpritePersp::pulsarLeft);
  } else {
    isPulsarLeft = false;
  }
}
//--------------------------------------------------------------
void sxSpritePersp::setPulsarRightForPoint(unsigned int i){
  pulsarRightPoint = i+1;
  isPulsarRight = true;

  Tweenzor::add(&hues[pulsarRightPoint], 0.f, 1.f, 0.f, 2.0f);
  Tweenzor::add(&(*points)[pulsarRightPoint].y,(*points)[pulsarRightPoint].y, 100.f, 0.f, 0.03f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[pulsarRightPoint].y), this, &sxSpritePersp::pulsarRight);
}

//--------------------------------------------------------------
void sxSpritePersp::pulsarRight(float* arg){
  Tweenzor::add(&(*points)[pulsarRightPoint].y, 100.f, MINBREATH, 0.f, 2.0f);
  Tweenzor::add(&hues[pulsarRightPoint], 1.f, 0.f, 0.f, 2.0f);

  pulsarRightPoint++;
  if (pulsarRightPoint < (*points).size()){
  Tweenzor::add(&hues[pulsarRightPoint], 0.f, 1.f, 0.f, 2.0f);
    Tweenzor::add(&(*points)[pulsarRightPoint].y,(*points)[pulsarRightPoint].y, 100.f, 0.f, 0.03f);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[pulsarRightPoint].y), this, &sxSpritePersp::pulsarRight);
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
  Tweenzor::add(&hues[breathingPoint], 1.f, 0.f, 0.f, 2.0f);
  Tweenzor::add(&(*points)[breathingPoint].y, 100.f, MINBREATH, 0.f, 2.0f);

  breathingPoint = i;
  Tweenzor::add(&(*points)[i].y,(*points)[i].y, 100.f, 0.f, 0.1f);
  Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[i].y), this, &sxSpritePersp::breath);
}

//--------------------------------------------------------------
void sxSpritePersp::breath(float* arg) {
  hues[breathingPoint] = 1;
  float breathMin = MINBREATH;
  float breathMax = 100;
  if (*arg > breathMax-1){
    //go down
    Tweenzor::add(&(*points)[breathingPoint].y,(*points)[breathingPoint].y, breathMin, 0.f, 2.0f);
  } else {
    Tweenzor::add(&(*points)[breathingPoint].y,(*points)[breathingPoint].y, breathMax, 0.f, 2.0f);
  }
  Tweenzor::addCompleteListener(Tweenzor::getTween(&(*points)[breathingPoint].y), this, &sxSpritePersp::breath);
}
