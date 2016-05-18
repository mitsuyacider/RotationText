//
//  SingleChar.hpp
//  SingleChar
//
//  Created by Mitstuya.WATANABE on 2016/05/17.
//
//

#ifndef SingleChar_hpp
#define SingleChar_hpp

#include <stdio.h>
#pragma once
#include "ofxTrueTypeFontUC.h"
#include "ofMain.h"

static const int kFontSize = 10;

class SingleChar {
    
    public:
        SingleChar(float firstAngle, string txt);
        ~SingleChar();
        void update();
        void draw();
    
        ofxTrueTypeFontUC myFont;
        string aChar;
        float speed;
        float angle;
        float radius;
        ofColor color;
        float deadAngle;
};

#endif /* SingleChar_hpp */
