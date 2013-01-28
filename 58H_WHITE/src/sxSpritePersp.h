#include "sxSprite.h"

class sxSpritePersp : public sxSprite {
  public:
    vector<float> * points; 
    virtual void drawContent(){
      width = _image.getWidth();
      height = _image.getHeight();
      float coef = ofMap(y, ofGetHeight()/2, ofGetHeight(), 8, 2);
      coef = ofClamp(coef, 2, 8);
      width /= coef;
      height /= coef;

      sxSprite::drawContent();
      renderMove();
    }
    virtual void mouseMoved(int x, int y){
      sxSprite::mouseMoved(x, y);
    }
    void renderMove();
    void setBreathingForPoint(unsigned int i);
    void breath(float* arg);
    void setPulsarRightForPoint(unsigned int i);
    void pulsarRight(float* arg);
    void setPulsarLeftForPoint(unsigned int i);
    void pulsarLeft(float* arg);
	
    unsigned int breathingPoint;
    unsigned int lastPoint;
    bool isPulsarRight;
    bool isPulsarLeft;
    unsigned int pulsarRightPoint;
    unsigned int pulsarLeftPoint;

};
