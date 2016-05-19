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
#include <regex>


static const float kMultiStepAngle = 4.6;     // マルチバイト
static const float kNum2MultiStepAngle = 3.0; // 半角英数字 -> マルチバイト
static const float kNumStepAngle = 2.8;       // 半角英数字
static const float kMulti2NumStepAngle = 5.8; // マルチバイト -> 半角英数字
static const float kRotationSpeed = 0.5;
static const float kRadius = 300.0;
static const int kCharBytes = 3;
static const int kFontSize = 20;
static const int kMarginAngle = 30;
static const ofColor kAnalyzedHilightColor = ofColor(255, 0, 0); // 形態素解析された文字の色
static const ofColor kAnalyzedDisableColor = ofColor(120, 120); // 形態素解析されてない文字の色

typedef enum {
    
    TextSpeechModeSpeaking, // 話した先からタイピングされていくモード
    TextSpeechModeAnalyzed, // 確定された文章から検索にかける名刺を抽出(形態素解析)するモード
    TextSpeechModeResult,   // 抽出された名詞の結果を連結させて表示するモード
    TextSpeechModeReady
}TextSpeechMode;

typedef enum {
    
    FieldTypeA,
    FieldTypeB
} FieldType;

class RotationText {
    public:

    RotationText(FieldType type);
    ~RotationText();
    void setup(string text);
    void update();
    void draw();
    // 文字列を追加する
    void addChars(string text);
    // 現在表示されているテキストを取得する
    string getCurrentText();
    // 正規表現でマッチングしたテキスト情報を取得する
    std::vector<int> search( std::string const & text, std::regex const & re );
    // 文字色を変更する
    void changeColor(TextSpeechMode mode);
    void analyzed(string text[]);
    
    ofxTrueTypeFontUC myFont;
    string sampleString;
    float speed;
    
    TextSpeechMode textSpeechMode;
    vector<string> analyzedList;
    bool showLines;
    std::deque<SingleChar *> charsQue;
    float startAngle;
    float endAngle;
    string analyzedString;
};