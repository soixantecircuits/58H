#pragma once
#include "ofMain.h"
#include "ofxTuio.h"
#include "ofxMtActionsObject.h"

//----------------------------------------------------------
// sxNode
//----------------------------------------------------------
class sxNode: public ofxMtActionsObject {
  public:
    virtual ~sxNode();
    sxNode();
    //sxNode(const sxNode& node);
    virtual void drawContent();
    virtual void mysetup();
    virtual void update();
    virtual void start();
    virtual void stop(){};
		virtual void mouseMoved(int x, int y);
		virtual void mousePressed(int x, int y, int button);
		virtual void mouseDragged(int x, int y, int button);
		virtual void mouseReleased(int x, int y, int button);
		virtual void actionTouchDown(float x, float y, int touchId);
		virtual void actionTouchMoved(float x, float y, int touchId);
		virtual void actionTouchUp(float x, float y, int touchId);
    virtual bool ownTouchCursor(int touchId);
    virtual bool actionTouchHitTest(float _x, float _y);
    virtual float getHeight() const;
    virtual float getScaledHeight() const;
    virtual void setHeight(float height);
    virtual float getWidth() const;
    virtual float getScaledWidth() const;
    virtual void setWidth(float width);
    virtual ofVec2f& getPosition() ;
    void setPosition(int x, int y);
    void setPosition(const ofVec2f& pos);

    vector<sxNode*> getChildren() const;
    virtual int getZOrder() const;
    virtual void setZOrder(int zOrder);
    virtual bool isVisible() const;
    virtual void setVisible(bool isVisible);
    void scale(float scale);
    void rotate(float rotation);
    void setScale(float scale);
    float getScale();
    void setRotation(float rotation);
    bool isTouchInteractive();
    const string& getName() const;
    void setName(const string& name);
    void setParent(sxNode* node);
    sxNode* getParent();
    void addChild(sxNode* node);
    sxNode* node();
    bool isInside(int x, int y);
    int getHighestZOrder();

    void setScalable(bool set);
    void setRotatable(bool set);
    void setDraggable(bool set);

    static bool compareZOrder(sxNode* a, sxNode* b) {
      return (a->getZOrder() < b->getZOrder());
    }

    void updateCenterPositionFromCornerPosition();
    virtual void resetToInitialValues();
    ofVec2f _contentPositionCenter;

  protected:
    string _name;
    int _zOrder;
    float _rotation;
    float _scale;
    //float _scaleX;
    //float _scaleY;
    ofVec2f _positionCorner;
    //ofVec2f _anchorPoint;
    //float _width;
    //float _height;
    sxNode* _parent;
    vector<sxNode*> _children;
    bool _isVisible;
    ofVec2f firstTouch;
};


