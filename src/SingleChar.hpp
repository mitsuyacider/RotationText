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
#include "ofxTween.h"
#include "RotationSettings.hpp"

/**
 *  This class is for one character
 */

template <class T> void changeColor(T temp) {
    printf("\nchangecolor default");
    return 0;
}
class SingleChar {
    
    public:
        SingleChar(float firstAngle, string txt);
        ~SingleChar();
        void update();
        void draw();
        void changeColor(ofColor c);
        void changeColor(int c);
        ofxTrueTypeFontUC myFont;
        string aChar;
        float speed;
        float angle;
        float radius;
        ofColor color;
        float deadAngle;
        int bytes;
    
        ofxTween rTween;
        ofxTween gTween;
        ofxTween bTween;
        ofxTween aTween;
        ofxEasingQuart 	easingquart;
        bool bAnalyzed;
        int duration;
};

#endif /* SingleChar_hpp */
