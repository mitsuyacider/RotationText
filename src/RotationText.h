//
//  RotationText.hpp
//  TextRotation
//
//  Created by Mitstuya.WATANABE on 2016/04/19.
//
//

#ifndef RotationText_hpp
#define RotationText_hpp

#include <stdio.h>

#endif /* RotationText_hpp */

#pragma once
#include "ofxTrueTypeFontUC.h"
#include "ofMain.h"
#include "SingleChar.hpp"

static const float kMultiStepAngle = 8.6;     // マルチバイト
static const float kNum2MultiStepAngle = 7.0; // 半角英数字 -> マルチバイト
static const float kNumStepAngle = 5.6;       // 半角英数字
static const float kMulti2NumStepAngle = 8.6; // マルチバイト -> 半角英数字
static const float kRotationSpeed = 0.5;
static const float kRadius = 300.0;
static const int kCharBytes = 3;
static const int kMarginAngle = 30;


typedef enum {
    
    TextSpeechModeSpeaking, // 話した先からタイピングされていくモード
    TextSpeechModeAnalyzed, // 確定された文章から検索にかける名刺を抽出(形態素解析)するモード
    TextSpeechModeResult    // 抽出された名詞の結果を連結させて表示するモード
}TextSpeechMode;

class RotationText {
    public:
        void setup(string text);
        void update();
        void draw();
        void addChars(string text);
    
    ofxTrueTypeFontUC myFont;
    string sampleString;
    float speed;
    
    TextSpeechMode textSpeechMode;
    vector<string> analyzedList;
    bool showLines;
    
    vector<SingleChar *> chars;
};