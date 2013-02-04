#pragma once
#include "ofMain.h"
#include "ofxTuio.h"
#include "sxNode.h"

//----------------------------------------------------------
// sxSprite
//----------------------------------------------------------

class sxSprite: public sxNode{
  public:
    virtual ~sxSprite(){}
    virtual void drawContent();
    void loadImage(const string& path);

  protected:
    ofImage _image;
};


