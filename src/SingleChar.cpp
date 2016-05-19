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
}

void SingleChar::draw() {}