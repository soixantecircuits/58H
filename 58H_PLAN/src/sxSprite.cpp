#include "sxSprite.h"

//--------------------------------------------------------------
void sxSprite::drawContent(){
  if (isVisible()){
    if (_image.isAllocated()){
      _image.draw(-width/2., -height/2., width, height);
    }
    sxNode::drawContent();
  }
}

//--------------------------------------------------------------
void sxSprite::loadImage(const string& path){
  _image.loadImage(path);
  setWidth(_image.getWidth());
  setHeight( _image.getHeight());
}

