//
//  RotationText.cpp
//  TextRotation
//
//  Created by Mitstuya.WATANABE on 2016/04/19.
//
//

#include "RotationText.h"

RotationText::RotationText(FieldType type) {
    myFont.loadFont("Meiryo.ttf", kFontSize, true, true);
    textSpeechMode = TextSpeechModeReady;
    
    if (type == FieldTypeA) {
        startAngle = 90 + kMarginAngle;
        endAngle = 270 - kMarginAngle;
    } else if (type == FieldTypeB) {
        startAngle = 270 + kMarginAngle;
        endAngle = 450 - kMarginAngle;
    }
}

RotationText::~RotationText() {
    
}

void RotationText::setup(string text) {
    sampleString = text;

    analyzedList.push_back("あいうえお");
    analyzedList.push_back("かきくけこ");
    speed = 1;

    showLines = false;
    
    // Stringの配列を作成する
    sampleString = "あいうえおかきうけこあskファおph";
    addChars(sampleString);
}

void RotationText::update() {
    
    if (!charsQue.empty()) {
        // MEMO: autoは型推論らしい
        for(auto itr = charsQue.begin(); itr != charsQue.end(); ++itr) {
            (*itr)->update();
        }
    }
    
    // erase char
    std::deque<SingleChar *>::iterator it = charsQue.begin();
    while(it != charsQue.end()){
        SingleChar *c = *it;
        if (c->angle > endAngle) {
                it = charsQue.erase(it);
            delete c;
        } else {
            ++it;
        }
    }
    
    if (charsQue.empty()) {
        textSpeechMode = TextSpeechModeReady;
    }
}

void RotationText::draw() {
    if (!charsQue.empty())  {
        for(auto itr = charsQue.begin(); itr != charsQue.end(); ++itr) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2,  ofGetHeight() / 2);
            ofRotate((*itr)->angle);
            ofPushMatrix();
            ofTranslate(kRadius, 0);
            ofRotate(-90);
            
            ofPushStyle();
            if ((*itr)->angle > startAngle && (*itr)->angle < endAngle) {
                ofSetColor(255);
            } else {
                ofSetColor(0);
            }
            myFont.drawString((*itr)->aChar, 0, 0);
            ofPopStyle();
            ofPopMatrix();
            ofPopMatrix();
        }
    }
}

void RotationText::addChars(string text) {
    string tempStr = text;
    
    string str;
    int bytes = 1;
    int oldBytes = 1;
    
    float currentAngle = 0.0;
    if (charsQue.empty()) {
        // NOTE: A領域, B領域で、現在描画できる領域をみる必要がある。
        currentAngle = startAngle;
    } else {
        SingleChar *lastChar = charsQue.back();
        bool hasNum = isalnum(*lastChar->aChar.c_str());
        oldBytes = hasNum ? 1 : 3;
        currentAngle = lastChar->angle;
    }
    
    while(!tempStr.empty()) {
        // ÂçäËßíËã±Êï∞Â≠ó„Åã„Å©„ÅÜ„Åã„ÇíÂà§Âà•„Åô„Çã
        bool hasNum = isalnum(*tempStr.substr(0, 1).c_str());
        
        bytes = hasNum ? 1 : 3;
        str = tempStr.substr(0, bytes);
        
        // NOTE: 半角英数字とマルチバイト文字の変わり目にスペースが空きすぎてしまうため、
        //       頭とお尻のスペースを調整する必要がある。
        if (oldBytes == 3 && bytes == 1) {
            // 前回の文字がマルチバイトの場合 (マルチバイト -> 半角英数字)
            currentAngle -= kMulti2NumStepAngle;
        } else if (oldBytes == 1 && bytes == 3) {
            // 前回の文字が半角英数字の場合 (半角英数字 -> マルチバイト)
            currentAngle -= kNum2MultiStepAngle;
        } else {
            float angle = hasNum ? kNumStepAngle : kMultiStepAngle;
            currentAngle -= angle;
        }
        
        SingleChar *char1 = new SingleChar(currentAngle, str);
        charsQue.push_back(char1);
        
        tempStr.erase(0, bytes);
        oldBytes = bytes;
    }
    
    textSpeechMode = TextSpeechModeSpeaking;
}
