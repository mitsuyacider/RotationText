//
//  SingleChar.cpp
//  SingleChar
//
//  Created by Mitstuya.WATANABE on 2016/05/17.
//
//

#include "SingleChar.hpp"

SingleChar::SingleChar(float firstAngle, string txt) {
    aChar = txt;
    angle = firstAngle;
    radius = 200.0;
    speed = 0.2;
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
    rTween.setParameters(1, easingquart, ofxTween::easeOut, color.r, c.r, 2000, 100);
    gTween.setParameters(1, easingquart, ofxTween::easeOut, color.g, c.g, 2000, 100);
    bTween.setParameters(1, easingquart, ofxTween::easeOut, color.b, c.b, 2000, 100);
    aTween.setParameters(1, easingquart, ofxTween::easeOut, color.a, c.a, 2000, 100);
}