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
#include "RotationSettings.hpp"


static const int kCharBytes = 3;

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
        void update();
        void draw();
        // 文字列を追加する
        void setText(string text);
        // 現在表示されているテキストを取得する
        string getCurrentText();
        // 正規表現でマッチングしたテキスト情報を取得する
        std::vector<int> search( std::string const & text, std::regex const & re );
        // 文字色を変更する
        void changeColor(TextSpeechMode mode);
        void analyzed(string text);
        std::string utf8rev(std::string str);
        
        ofxTrueTypeFontUC myFont;
        string sampleString;
        TextSpeechMode textSpeechMode;
        vector<string> analyzedList;
        bool showLines;
        std::deque<SingleChar *> charsQue;
        float startAngle;
        float endAngle;
        string analyzedString;
        RotationSettings *rotSettings;
    
    ofFbo fbo;
    ofFbo fboD;
    ofShader shader;
    bool useShader;
    ofxTrueTypeFontUC myFontB;
  
};