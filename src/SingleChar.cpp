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
    
    int offset = 10;
    int size = RotationSettings::getInstance().fontSize;
    fbo.allocate(size + offset, size + offset, GL_RGBA, 4);
    fboD.allocate(size + offset, size + offset, GL_RGBA, 4);
    shader.load("outlineShader/outlineShader");
    myFont.load("ヒラギノ角ゴシック W7.ttc", size, true, true);
    
    // if you want use shader for drawing outline, should turn on following flag
    useShader = true;
}

SingleChar::~SingleChar() {}

void SingleChar::update() {
    angle += speed;
    if (!rTween.isCompleted()) {
        color = ofColor(rTween.update(), gTween.update(), bTween.update(), aTween.update());
        outlineColor = ofColor(oRTween.update(), oGTween.update(), oBTween.update(), oATween.update());
    }
    
    if (useShader) {
        // NOTE: update shader for drawing outline
        fbo.begin();
        ofClear(0,0,0,0);
        
        ofSetColor(255,255,255);
        myFont.drawString(aChar, 0, RotationSettings::getInstance().fontSize + 4);
        fbo.end();
        
        fboD.begin();
        ofClear(0,0,0,0);
        shader.begin();
        shader.setUniform1f("u_offset", 2.0f);
        fbo.draw(0,0);
        shader.end();
        fbo.draw(0,0);
        fboD.end();
    }
}

void SingleChar::draw() {
    fboD.draw(0,0);
}


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