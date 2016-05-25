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
    aChar = txt;
    angle = firstAngle;
    color = ofColor(255);
    bool hasNum = isalnum(*txt.substr(0, 1).c_str());    
    bytes = hasNum ? 1 : 3;
}

SingleChar::~SingleChar() {}

void SingleChar::update() {
    angle += speed;
    if (!rTween.isCompleted()) {
        color = ofColor(rTween.update(), gTween.update(), bTween.update(), aTween.update());
    }
}

void SingleChar::draw() {}

void SingleChar::changeColor(ofColor c) {
    rTween.setParameters(1, easingquart, ofxTween::easeOut, color.r, c.r, kFadeDuration, 100);
    gTween.setParameters(1, easingquart, ofxTween::easeOut, color.g, c.g, kFadeDuration, 100);
    bTween.setParameters(1, easingquart, ofxTween::easeOut, color.b, c.b, kFadeDuration, 100);
    aTween.setParameters(1, easingquart, ofxTween::easeOut, color.a, c.a, kFadeDuration, 100);
}