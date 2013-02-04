#include "sxDirector.h"

sxDirector* sxDirector::__instance = 0;

//--------------------------------------------------------------
sxDirector* sxDirector::instance(){
  if (__instance == 0){
    __instance = new sxDirector();
  }
  return __instance;
}

//--------------------------------------------------------------
void sxDirector::setup(){
  instance();
}

//--------------------------------------------------------------
void sxDirector::update(){
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
  vector<sxNode*>::iterator it;
	for (it = __instance->_sprites.begin(); it < __instance->_sprites.end(); it++ ) { 
    (*it)->update();
  }
}

//--------------------------------------------------------------
void sxDirector::draw(){
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
  vector<sxNode*>::iterator it;
	for (it = __instance->_sprites.begin(); it < __instance->_sprites.end(); it++ ) { 
    if ((*it)->isVisible()){
      (*it)->render();
    }
  }
}

//--------------------------------------------------------------
void sxDirector::keyPressed(int key){

}

//--------------------------------------------------------------
void sxDirector::keyReleased(int key){

}

//--------------------------------------------------------------
void sxDirector::mouseMoved(int x, int y ){

}
//--------------------------------------------------------------
void sxDirector::mouseDragged(int x, int y, int button){
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = __instance->_sprites.rbegin(); rit < __instance->_sprites.rend(); rit++ ) { 
    if ((*rit)->isVisible()){
      // click is on node
      if ((*rit)->isInside(x, y)){
        (*rit)->mouseDragged(x - (*rit)->getPosition().x, y - (*rit)->getPosition().y, button);
        //break;
      }
    }
  }
}

//--------------------------------------------------------------
void sxDirector::mousePressed(int x, int y, int button){
  cout << "sxDirector: mousePressed " << x << ", " << y << endl;
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = __instance->_sprites.rbegin(); rit < __instance->_sprites.rend(); rit++ ) { 
    if ((*rit)->isVisible()){
      // click is on node
      if ((*rit)->isInside(x, y)){
        (*rit)->mousePressed(x - (*rit)->getPosition().x, y - (*rit)->getPosition().y, button);
        break;
      }
    }
  }
}

//--------------------------------------------------------------
void sxDirector::mouseReleased(int x, int y, int button){
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = __instance->_sprites.rbegin(); rit < __instance->_sprites.rend(); rit++ ) { 
    if ((*rit)->isVisible()){
      // click is on node
      if ((*rit)->isInside(x, y)){
        (*rit)->mouseReleased(x - (*rit)->getPosition().x, y - (*rit)->getPosition().y, button);
        //break;
      }
    }
  }
}

//--------------------------------------------------------------
void sxDirector::cursorDragged(ofxTuioCursor &tuioCursor){
  int x = tuioCursor.getX() * ofGetWidth();
  int y = tuioCursor.getY() * ofGetHeight();
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = __instance->_sprites.rbegin(); rit < __instance->_sprites.rend(); rit++ ) { 
    if ((*rit)->isVisible()){
      if ((*rit)->ownTouchCursor(tuioCursor.getSessionId())){
        // click is on node
        (*rit)->actionTouchMoved(x, y, tuioCursor.getSessionId());
      }
    }
  }
}

//--------------------------------------------------------------
void sxDirector::cursorPressed(ofxTuioCursor &tuioCursor){
  int x = tuioCursor.getX() * ofGetWidth();
  int y = tuioCursor.getY() * ofGetHeight();
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = __instance->_sprites.rbegin(); rit < __instance->_sprites.rend(); rit++ ) { 
    if ((*rit)->isVisible()){
      (*rit)->actionTouchDown(x, y, tuioCursor.getSessionId());
      if ((*rit)->ownTouchCursor(tuioCursor.getSessionId())){
        cout << "sxDirector: tuio found a target" << endl;
        // click is on node
        break;
      }
    }
  }
}

//--------------------------------------------------------------
void sxDirector::cursorReleased(ofxTuioCursor &tuioCursor){
  int x = tuioCursor.getX() * ofGetWidth();
  int y = tuioCursor.getY() * ofGetHeight();
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = __instance->_sprites.rbegin(); rit < __instance->_sprites.rend(); rit++ ) { 
    if ((*rit)->isVisible()){
      (*rit)->actionTouchUp(x, y, tuioCursor.getSessionId());
    }
  }
}

//--------------------------------------------------------------
void sxDirector::windowResized(int w, int h){

}

//--------------------------------------------------------------
void sxDirector::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void sxDirector::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void sxDirector::addChild(sxNode* sprite){
  __instance->_sprites.push_back(sprite);
  sort(__instance->_sprites.begin(), __instance->_sprites.end(), sxNode::compareZOrder);
}

//--------------------------------------------------------------
void sxDirector::removeChild(sxNode* sprite){
  vector<sxNode*>::iterator it;
	for (it = __instance->_sprites.begin(); it < __instance->_sprites.end(); it++ ) { 
    if (*it == sprite){
      cout << "Removed child from sxDirector" << endl;
      __instance->_sprites.erase(it);
      break;
    }
  }
}

//--------------------------------------------------------------
float sxDirector::getHighestZOrder(){
  return __instance->_sprites.back()->getZOrder();
}

//--------------------------------------------------------------
float sxDirector::getHighestZOrder(string name){
  cout << "Looking for zOrder " << endl;
  float zOrder = 0;
  vector<sxNode*>::iterator it;
	for (it = __instance->_sprites.begin(); it < __instance->_sprites.end(); it++ ) { 
    if ((*it)->getName() == name && (*it)->getZOrder() > zOrder){
      zOrder = (*it)->getZOrder();
      cout << "zOrder: " << (*it)->getName() << ": " << zOrder << endl;
    }
  }
  return zOrder;
}

//--------------------------------------------------------------
void sxDirector::tuioAdded(ofxTuioCursor &tuioCursor){	
  //sxDirector::mousePressed(tuioCursor.getX()*ofGetWidth(), tuioCursor.getY()*ofGetHeight(), 0);
  sxDirector::cursorPressed(tuioCursor);
}

//--------------------------------------------------------------
void sxDirector::tuioUpdated(ofxTuioCursor &tuioCursor){
  //sxDirector::mouseDragged(tuioCursor.getX()*ofGetWidth(), tuioCursor.getY()*ofGetHeight(), 0);
  sxDirector::cursorDragged(tuioCursor);
}

//--------------------------------------------------------------
void sxDirector::tuioRemoved(ofxTuioCursor &tuioCursor){
  //sxDirector::mouseReleased(tuioCursor.getX()*ofGetWidth(), tuioCursor.getY()*ofGetHeight(), 0);
  sxDirector::cursorReleased(tuioCursor);
}

