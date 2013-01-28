#include "sxNode.h"

//--------------------------------------------------------------
sxNode::sxNode(){
	disableAppEvents(); //to prevent MSAInteractiveObject to call setup/update/draw
  mysetup();
}

//--------------------------------------------------------------
/*sxNode::sxNode(const sxNode& node){
	for (it = node._children.begin(); it < node._children.end(); it++ ) {
    //_children.push_back(new
  }
  cout << "sxNode: copy constructor is called" << endl;
}
*/

//--------------------------------------------------------------
void sxNode::mysetup(){
  _isVisible = true;
  rotation = 0;
  _rotation = 0;
  _scale = 1;
  _parent = 0;
  setWidth(0);
  setHeight(0);
  //cout << "sxNode: setup finished" << endl;
}

//--------------------------------------------------------------
void sxNode::start(){

}

//--------------------------------------------------------------
void sxNode::update(){
  ofxMtActionsObject::update();
  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  vector<sxNode*>::iterator it;
  // TODO: we should have an event for rescaling, instead of always rescaling
	for (it = _children.begin(); it < _children.end(); it++ ) {
      // scale children
      if (height != contentHeight){
        float scale = height/contentHeight;
        (*it)->scale(scale);
        /*
        (*it)->width = (*it)->contentWidth * scale;
        (*it)->height = (*it)->contentHeight * scale;
        (*it)->x = (*it)->_contentPositionCenter.x * scale;
        (*it)->y = (*it)->_contentPositionCenter.y * scale;
        */
        //cout << "sxNode: scale" << endl;
        // TODO : it seems that rescale is always called
      }
      (*it)->update();
  }
}

//--------------------------------------------------------------
void sxNode::drawContent(){
  if (isVisible()){
    //ofTranslate(_position);
    sort(_children.begin(), _children.end(), sxNode::compareZOrder);
    vector<sxNode*>::iterator it;
    for (it = _children.begin(); it < _children.end(); it++ ) {
      if ((*it)->isVisible()){
        (*it)->render();
      }
    }
    //ofTranslate(-_position);
  }
}

//--------------------------------------------------------------
void sxNode::mouseMoved(int x, int y ){
  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = _children.rbegin(); rit < _children.rend(); rit++ ) {
    if ((*rit)->isVisible()){
      // click is on node
      if ((*rit)->isInside(x, y)){
        (*rit)->mouseMoved(x - (*rit)->getPosition().x, y - (*rit)->getPosition().y);
        //break;
      }
    }
  }

}

//--------------------------------------------------------------
void sxNode::mouseDragged(int x, int y, int button){
  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  setPosition(getPosition() + ofVec2f(x,y) - firstTouch);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = _children.rbegin(); rit < _children.rend(); rit++ ) {
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
void sxNode::mousePressed(int x, int y, int button){
  cout << "sxNode: mousePressed " << x << ", " << y << endl;
  firstTouch.set(x,y);
  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = _children.rbegin(); rit < _children.rend(); rit++ ) {
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
void sxNode::mouseReleased(int x, int y, int button){
  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = _children.rbegin(); rit < _children.rend(); rit++ ) {
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
void sxNode::actionTouchDown(float x, float y, int touchId){
  //set vector p in the object's frame
  ofVec2f p = ofVec2f(x, y) - ofVec2f(this->x, this->y);
  p.rotateRad(-rotation);

  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = _children.rbegin(); rit < _children.rend(); rit++ ) {
    if ((*rit)->isVisible()){
      (*rit)->actionTouchDown(p.x, p.y, touchId);
      if ((*rit)->ownTouchCursor(touchId)){
        // touch is on node
        //break;
        return;
      }
    }
  }
  if (isTouchInteractive()){
    ofxMtActionsObject::actionTouchDown(x, y, touchId);
  }
}

//--------------------------------------------------------------
void sxNode::actionTouchMoved(float x, float y, int touchId){
  //set vector p in the object's frame
  ofVec2f p = ofVec2f(x, y) - ofVec2f(this->x, this->y);
  p.rotateRad(-rotation);

  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = _children.rbegin(); rit < _children.rend(); rit++ ) {
    if ((*rit)->isVisible()){
      if ((*rit)->ownTouchCursor(touchId)){
        // touch is on node
        (*rit)->actionTouchMoved(p.x, p.y, touchId);
        //break;
      }
    }
  }
  if (isTouchInteractive() && ownTouchCursor(touchId)){
    ofxMtActionsObject::actionTouchMoved(x, y, touchId);
  }
}

//--------------------------------------------------------------
void sxNode::actionTouchUp(float x, float y, int touchId){
  //set vector p in the object's frame
  ofVec2f p = ofVec2f(x, y) - ofVec2f(this->x, this->y);
  p.rotateRad(-rotation);

  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = _children.rbegin(); rit < _children.rend(); rit++ ) {
    if ((*rit)->isVisible()){
      //if ((*rit)->ownTouchCursor(touchId)){
        // touch is on node
        (*rit)->actionTouchUp(p.x, p.y, touchId);
        //break;
      //}
    }
  }
  if (isTouchInteractive()){
    ofxMtActionsObject::actionTouchUp(x, y, touchId);
  }
}

//--------------------------------------------------------------
bool sxNode::ownTouchCursor(int touchId){
  sort(_children.begin(), _children.end(), sxNode::compareZOrder);
  vector<sxNode*>::reverse_iterator rit;
	for (rit = _children.rbegin(); rit < _children.rend(); rit++ ) {
    if ((*rit)->isVisible()){
      if ((*rit)->ownTouchCursor(touchId)){
        return true;
      }
    }
  }
  if (isTouchInteractive()){
    return ofxMtActionsObject::ownTouchCursor(touchId);
  }
  return false;
}

//--------------------------------------------------------------
bool sxNode::actionTouchHitTest(float _x, float _y) {
  /* with rotation
  ofVec2f p = ofVec2f(_x, _y);
  for (sxNode* ancestor = this; ancestor != 0; ancestor = ancestor->getParent()){
		p.x -= ancestor->x;
		p.y -= ancestor->y;
		p.rotateRad(-ancestor->rotation);
		p.x += ancestor->x;
		p.y += ancestor->y;
  }
	return hitTest(p.x + width/2, p.y + height/2);
  */

  // normal
  return ofxMtActionsObject::actionTouchHitTest(_x, _y);

}

//--------------------------------------------------------------
int sxNode::getHighestZOrder(){
  return _children.back()->getZOrder();
}

//--------------------------------------------------------------
void sxNode::setScalable(bool set){
  // TODO:implement false
  if (set){
    int *tRange = new int[1];
    tRange[0] = 2;
    setIsScalable(true, tRange, 1);
    delete [] tRange;
  }
}

//--------------------------------------------------------------
void sxNode::setRotatable(bool set){
  // TODO:implement false
  if (set){
    int *tRange = new int[2];
    tRange[0] = 2;
    tRange[1] = 3;
    setIsRotatable(true, tRange, 2);
    delete [] tRange;
  }
}

//--------------------------------------------------------------
void sxNode::setDraggable(bool set){
  // TODO:implement false
  if (set){
    int *tRange = new int[2];
    tRange[0] = 1;
    tRange[1] = -4; //a negative value means the value and up. Is this case 4+
    setIsDraggable(true, tRange, 2);
    delete [] tRange;
  }
}

//--------------------------------------------------------------
bool sxNode::isInside(int x, int y) {
      ofRectangle rect(this->x - this->getScaledWidth()/2, this->y - this->getScaledHeight()/2, getScaledWidth(), getScaledHeight());
      return rect.inside(x, y);
}

//--------------------------------------------------------------
void sxNode::setHeight(float height){
  this->height = height;
  this->contentHeight = height;
  updateCenterPositionFromCornerPosition();
}

//--------------------------------------------------------------
float sxNode::getHeight() const {
    return contentHeight;
}

//--------------------------------------------------------------
float sxNode::getScaledHeight() const {
    return height;
}

//--------------------------------------------------------------
void sxNode::setWidth(float width){
  this->width = width;
  this->contentWidth = width;
  updateCenterPositionFromCornerPosition();
}

//--------------------------------------------------------------
float sxNode::getWidth() const {
    return contentWidth;
}

//--------------------------------------------------------------
float sxNode::getScaledWidth() const {
    return width;
}


//--------------------------------------------------------------
sxNode* sxNode::getParent() {
    return _parent;
}


//--------------------------------------------------------------
ofVec2f& sxNode::getPosition() {
    return _positionCorner;
}

//--------------------------------------------------------------
void sxNode::setPosition(int x, int y){
  _positionCorner.set(x, y);
  updateCenterPositionFromCornerPosition();
}

//--------------------------------------------------------------
void sxNode::setPosition(const ofVec2f& pos){
  setPosition(pos.x, pos.y);
}

//--------------------------------------------------------------
void sxNode::updateCenterPositionFromCornerPosition(){
  x = _positionCorner.x + getWidth()/2.;
  y = _positionCorner.y + getHeight()/2.;
  if (_parent){
    //x -= _parent->getWidth()/2.;
    //y -= _parent->getHeight()/2.;
    x -= _parent->getWidth()/2.;
    y -= _parent->getHeight()/2.;
    /*float scale = _parent->height/_parent->contentHeight;
    width = contentWidth * scale;
    height = contentHeight * scale;
    x *= scale;
    y *= scale;
    */
  }
  _contentPositionCenter.set(x, y);

  //update children too
  vector<sxNode*>::iterator it;
  for (it = _children.begin(); it < _children.end(); it++ ) {
    (*it)->updateCenterPositionFromCornerPosition();
  }

  //cout << "sxNode: x, y " << this->x << ", " << this->y << endl;

}


//--------------------------------------------------------------
void sxNode::resetToInitialValues(){
  width = contentWidth;
  height = contentHeight;
  updateCenterPositionFromCornerPosition();
  //update children too
  vector<sxNode*>::iterator it;
  for (it = _children.begin(); it < _children.end(); it++ ) {
    (*it)->resetToInitialValues();
  }
  rotate(_rotation);
  scale(_scale);
}

//--------------------------------------------------------------
vector<sxNode*> sxNode::getChildren() const {
    return _children;
}


//--------------------------------------------------------------
int sxNode::getZOrder() const {
    return _zOrder;
}

//--------------------------------------------------------------
void sxNode::setZOrder(int zOrder){
  _zOrder = zOrder;
}

//--------------------------------------------------------------
bool sxNode::isVisible() const {
    return _isVisible;
}

//--------------------------------------------------------------
void sxNode::setVisible(bool isVisible){
  _isVisible = isVisible;
}

//--------------------------------------------------------------
bool sxNode::isTouchInteractive(){
  return draggable || scalable || rotatable || tappable;
}

//--------------------------------------------------------------
void sxNode::setRotation(float rotation){
  _rotation = rotation;
  this->rotate(rotation);
}

//--------------------------------------------------------------
float sxNode::getScale(){
  return _scale;
}

//--------------------------------------------------------------
void sxNode::setScale(float scale){
  _scale = scale;
  this->scale(scale);
}

//--------------------------------------------------------------
void sxNode::rotate(float rotation){
  this->rotation = rotation;
}

//--------------------------------------------------------------
void sxNode::scale(float scale){
  width = contentWidth*scale;
  height = contentHeight*scale;
  if (_parent){
    x = _contentPositionCenter.x * scale;
    y = _contentPositionCenter.y * scale;
  }
  // scale children
  vector<sxNode*>::iterator it;
  for (it = _children.begin(); it < _children.end(); it++ ) {
    (*it)->scale(scale);
    //(*it)->width = (*it)->contentWidth * scale;
    //(*it)->height = (*it)->contentHeight * scale;
    //(*it)->x = (*it)->_contentPositionCenter.x * scale;
    //(*it)->y = (*it)->_contentPositionCenter.y * scale;
    //cout << "sxNode: scale children" << endl;
  }

}

//--------------------------------------------------------------
const string& sxNode::getName() const {
    return _name;
}

//--------------------------------------------------------------
void sxNode::setName(const string& name){
    _name = name;
}

//--------------------------------------------------------------
void sxNode::setParent(sxNode* node){
  _parent = node;
  updateCenterPositionFromCornerPosition();
}

//--------------------------------------------------------------
void sxNode::addChild(sxNode* node){
  node->setParent(this);
  _children.push_back(node);
}

//--------------------------------------------------------------
sxNode* sxNode::node(){
  return static_cast<sxNode*> (this);
}

//--------------------------------------------------------------
sxNode::~sxNode(){
  vector<sxNode*>::iterator it;
  for (it = _children.begin(); it < _children.end(); it++ ) {
    delete (*it);
    *it = 0;
  }
}

