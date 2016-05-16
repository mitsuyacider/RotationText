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
}

void RotationText::update() {

}

void RotationText::draw() {

    
    string tempStr;
    char temp[sizeof(sampleString.c_str())];
    if (textSpeechMode == TextSpeechModeResult) {
        for (int i = 0; i < analyzedList.size(); i++) {
            tempStr += "„Éª" + analyzedList[i];
        }
    } else {
        char cstr[sizeof(sampleString)];
        strcpy(cstr, sampleString.c_str());
        std::cout << cstr << std::endl;

        tempStr = cstr;
//        tempStr = sampleString.copy(temp, 0);
    }


    

    string str;
    int bytes = 1;
    int oldBytes = 1;
    float currentAngle = 0;
    while (!tempStr.empty()) {
        // ÂçäËßíËã±Êï∞Â≠ó„Åã„Å©„ÅÜ„Åã„ÇíÂà§Âà•„Åô„Çã
        bool hasNum = isalnum(*tempStr.substr(0, 1).c_str());
        bytes = hasNum ? 1 : 3;
        str = tempStr.substr(0, bytes);

        // NOTE: 半角英数字とマルチバイト文字の変わり目にスペースが空きすぎてしまうため、
        //       頭とお尻のスペースを調整する必要がある。
        if (oldBytes == 3 && bytes == 1) {
            // 前回の文字がマルチバイトの場合 (マルチバイト -> 半角英数字)
            currentAngle += kMulti2NumStepAngle;
        } else if (oldBytes == 1 && bytes == 3) {
            // 前回の文字が半角英数字の場合 (半角英数字 -> マルチバイト)
            currentAngle += kNum2MultiStepAngle;
        } else {
            float angle = hasNum ? kNumStepAngle : kMultiStepAngle;
            currentAngle += angle;
        }

        ofPushMatrix();
        float degrees = -1 * currentAngle + speed;
//        float degrees = 90 - kMarginAngle;
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofRotate(degrees);
//        ofRotate(90);
        
        // ラインを描画
        if (showLines) {
            ofPushStyle();
            if (hasNum) {
                ofSetColor(0, 0, 255);

            } else {
                ofSetColor(255, 0, 0);
            }
            ofDrawLine(0.0, 0.0, kRadius, 0.0);
            ofPopStyle();
        }

        ofTranslate(kRadius, 0);
        ofRotate(-1 * 90);
        
        if (textSpeechMode == TextSpeechModeAnalyzed) {
            // NOTE: 形態素解析した結果、対象の文字が単語の構成要素になっているかどうかを
            //       判別する。(文章確定後)
            //       構成要素 -> 黒文字
            //       構成要素以外 -> グレー
            int detect = (int)analyzedList[0].find(str);
            if (detect != -1) {
                ofPushStyle();
                ofSetColor(0);
            } else {
                ofPushStyle();
                ofSetColor(200);
            }
        } else if (textSpeechMode == TextSpeechModeSpeaking) {
            ofPushStyle();
            ofSetColor(0);
        } else if (textSpeechMode == TextSpeechModeResult) {
            // NOTE: ÂΩ¢ÊÖãÁ¥†Ëß£Êûê„Å†„Åë„ÅÆÊñáÂ≠ó„ÇíË°®Á§∫
            ofPushStyle();
            ofSetColor(255, 0, 0);
        }


        if (degrees > 90 + kMarginAngle && degrees < 270 - kMarginAngle) {
            ofSetColor(255);
        } else {
            if (degrees > 270 - kMarginAngle) {
                ofSetColor(0);
                sampleString.erase(0, oldBytes);
            } else {
                ofSetColor(100);
            }
        }
        
        myFont.drawString(str.c_str(), 0, 0);
        ofPopStyle();
        ofPopMatrix();
        
        tempStr.erase(0, bytes);
        oldBytes = bytes;
    }

//    printf("\nrotation");
    speed += kRotationSpeed;
}


//void RotationText::draw() {
//    
//}