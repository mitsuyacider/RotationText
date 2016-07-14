//
//  SingleChar.cpp
//  SingleChar
//
//  Created by Mitstuya.WATANABE on 2016/05/17.
//
//

#include "SingleChar.hpp"

SingleChar::SingleChar(float firstAngle, string txt) {
    speed = RotationSettings::getInstance().speed;
    duration = RotationSettings::getInstance().fadeDuration;
    aChar = txt;
    angle = firstAngle;
    color = ofColor(255);
    outlineColor.setHex(RotationSettings::getInstance().outlineColor);    
}

SingleChar::~SingleChar() {}

void SingleChar::update() {
    angle += speed;

    if (!rTween.isCompleted()) {
        outlineColor = ofColor(oRTween.update(), oGTween.update(), oBTween.update(), oATween.update());
        color = ofColor(rTween.update(), gTween.update(), bTween.update(), aTween.update());
    }
}

void SingleChar::draw() {}


// --------- template -------
void SingleChar::changeColor(ofColor c){
    rTween.setParameters(1, easingquart, ofxTween::easeOut, color.r, c.r, duration, 100);
    gTween.setParameters(1, easingquart, ofxTween::easeOut, color.g, c.g, duration, 100);
    bTween.setParameters(1, easingquart, ofxTween::easeOut, color.b, c.b, duration, 100);
    aTween.setParameters(1, easingquart, ofxTween::easeOut, color.a, c.a, duration, 100);
}

void SingleChar::changeColor(int c){
    int r = (c& 0xff0000) >> 16;
    int g = (c& 0xff00) >> 8;
    int b = (c& 0xff);

    rTween.setParameters(1, easingquart, ofxTween::easeOut, color.r, r, duration, 100);
    gTween.setParameters(1, easingquart, ofxTween::easeOut, color.g, g, duration, 100);
    bTween.setParameters(1, easingquart, ofxTween::easeOut, color.b, b, duration, 100);
    aTween.setParameters(1, easingquart, ofxTween::easeOut, color.a, 255, duration, 100);
}

void SingleChar::changeOutlineColor(int c) {
    int r = (c& 0xff0000) >> 16;
    int g = (c& 0xff00) >> 8;
    int b = (c& 0xff);
    
    oRTween.setParameters(1, easingquart, ofxTween::easeOut, outlineColor.r, r, duration, 100);
    oGTween.setParameters(1, easingquart, ofxTween::easeOut, outlineColor.g, g, duration, 100);
    oBTween.setParameters(1, easingquart, ofxTween::easeOut, outlineColor.b, b, duration, 100);
    oATween.setParameters(1, easingquart, ofxTween::easeOut, outlineColor.a, 255, duration, 100);
    
}