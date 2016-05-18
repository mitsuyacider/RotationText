//
//  RotationText.cpp
//  TextRotation
//
//  Created by Mitstuya.WATANABE on 2016/04/19.
//
//

#include "RotationText.h"


void RotationText::setup(string text) {
    myFont.loadFont("Meiryo.ttf", 20, true, true);
    myFont.setSpaceSize(10);
    sampleString = text;

    analyzedList.push_back("あいうえお");
    analyzedList.push_back("かきくけこ");
    speed = 1;
    textSpeechMode = TextSpeechModeSpeaking;

    showLines = false;
    
    // Stringの配列を作成する
    sampleString = "あいうえおかきうけこあskファおph";
    addChars(sampleString);
}

void RotationText::update() {
    // MEMO: autoは型推論らしい
    for(auto itr = chars.begin(); itr != chars.end(); ++itr) {
        (*itr)->update();
    }
}

void RotationText::draw() {
    for(auto itr = chars.begin(); itr != chars.end(); ++itr) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2,  ofGetHeight() / 2);
        ofRotate((*itr)->angle);
        ofPushMatrix();
        ofTranslate(kRadius, 0);
        ofRotate(-90);
        
        ofPushStyle();
        ofSetColor((*itr)->color);
        myFont.drawString((*itr)->aChar, 0, 0);
        ofPopStyle();
        ofPopMatrix();
        ofPopMatrix();
    }
}


void RotationText::addChars(string text) {
    string tempStr = text;
    
    string str;
    int bytes = 1;
    int oldBytes = 1;
    
    float currentAngle = 0.0;
    if (chars.empty()) {
        // NOTE: A領域, B領域で、現在描画できる領域をみる必要がある。
        currentAngle = 90.0;
    } else {
        SingleChar *lastChar = chars.back();
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
        chars.push_back(char1);
        
        tempStr.erase(0, bytes);
        oldBytes = bytes;
    }
}
