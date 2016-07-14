//
//  RotationText.cpp
//  TextRotation
//
//  Created by Mitstuya.WATANABE on 2016/04/19.
//
//

#include "RotationText.h"
#include <regex>

RotationText::RotationText(FieldType type) {
    rotSettings = &RotationSettings::getInstance();
    myFont.loadFont("ヒラギノ角ゴシック W7.ttc", rotSettings->fontSize, true, true);
    textSpeechMode = TextSpeechModeReady;
    
    
    if (type == FieldTypeA) {
        startAngle = 90 + rotSettings->fieldMarginAngle;
        endAngle = 270 - rotSettings->fieldMarginAngle;
    } else if (type == FieldTypeB) {
        startAngle = 270 + rotSettings->fieldMarginAngle;
        endAngle = 450 - rotSettings->fieldMarginAngle;
    }
    
    showLines = false;
}

RotationText::~RotationText() {
    
}

void RotationText::update() {
    
    if (!charsQue.empty()) {
        // MEMO: auto‚Äû√Ö√ò√Ç√ª√£√ä√©¬Æ√ã¬¥√±‚Äû√á√¢‚Äû√Ö√≥‚Äû√Ö√ë
        float lastAngle = 0.0;
        for(auto itr = charsQue.begin(); itr != charsQue.end(); ++itr) {
            if (textSpeechMode == TextSpeechModeAnalyzed) {
                // NOTE: add force
                
            }
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
    
    startAngle += rotSettings->speed;
    endAngle += rotSettings->speed;
}

void RotationText::draw() {
    if (!charsQue.empty())  {
        for(auto itr = charsQue.begin(); itr != charsQue.end(); ++itr) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2,  ofGetHeight() / 2);
            ofRotate((*itr)->angle);
            ofPushMatrix();
            ofTranslate(rotSettings->radius, 0);
            ofRotate(-90);
            
            ofPushStyle();
            ofPushMatrix();
            // NOTE: we should move the anchor point because the path start point is difference.
            ofTranslate(0, kCharBytes);
            
            if ((*itr)->useShader) {
                (*itr)->draw();
            } else {
                // draw font with outline. if we use the same color at outline and inside, the lools is bold font.
                vector<ofPath> paths = myFont.getStringAsPoints((*itr)->aChar);
                for (auto itr2 = paths.begin(); itr2 != paths.end(); ++itr2) {
                    ofPath path = (*itr2);
                    path.setStrokeColor((*itr)->outlineColor);
                    path.setStrokeWidth(rotSettings->outlineWidth);
                    path.setFillColor((*itr)->color);
                    path.draw();
                }
            }
            
            ofPopMatrix();
            ofPopStyle();
            
            ofPopMatrix();
            ofPopMatrix();
        }
    }
    
    if (showLines) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofPushStyle();
        ofSetColor(21, 159, 190);
        ofDrawLine(0, 0, cos(ofDegToRad(startAngle)) * rotSettings->radius, sin(ofDegToRad(startAngle)) * rotSettings->radius);
        ofDrawLine(0, 0, cos(ofDegToRad(endAngle)) * rotSettings->radius, sin(ofDegToRad(endAngle)) * rotSettings->radius);
        ofPopStyle();
        ofPopMatrix();
    }
}

void RotationText::setText(string text) {
    string tempStr = utf8rev(text);
    
    charsQue.clear();
    string str;
    
    bool bAlphanumeric = false;
    bool bOldAlphanumeric = false;
    
    float currentAngle = 0.0;
    if (charsQue.empty()) {
        currentAngle = startAngle;
    } else {
        SingleChar *lastChar = charsQue.back();
        bool hasNum = isalnum(*lastChar->aChar.c_str());
        bOldAlphanumeric = lastChar->alphanumeric;
        currentAngle = lastChar->angle;
    }

    // NOTE: arrange the reading bytes. the bytes is always multi byte
    //       we should devide the alphanumeric and japanese char with using
    //       regular expression.
    //       the regular expression target is Ôº°-Ôº∫ Ôºë-Ôºô ÔΩÅ-ÔΩö
    //       Although we used A-Z a-z 0-9 for dividing alphanumeric, OS could not divide '„ÅÇ' and 'a'
    std::regex re("^[ÔºêÔºëÔºíÔºìÔºîÔºïÔºñÔºóÔºòÔºôÔº°Ôº¢Ôº£Ôº§Ôº•Ôº¶ÔºßÔº®Ôº©Ôº™Ôº´Ôº¨Ôº≠ÔºÆÔºØÔº∞Ôº±Ôº≤Ôº≥Ôº¥ÔºµÔº∂Ôº∑Ôº∏ÔºπÔº∫ÔΩÅÔΩÇÔΩÉÔΩÑÔΩÖÔΩÜÔΩáÔΩàÔΩâÔΩäÔΩãÔΩåÔΩçÔΩéÔΩèÔΩêÔΩëÔΩíÔΩìÔΩîÔΩïÔΩñÔΩóÔΩòÔΩôÔΩö]+$");
    while(!tempStr.empty()) {
        bool hasNum = isalnum(*tempStr.substr(0, 1).c_str());
        
        str = tempStr.substr(0, kCharBytes);
        bAlphanumeric = std::regex_match(str, re) ;
        if (!bOldAlphanumeric && bAlphanumeric) {
            currentAngle += rotSettings->multi2NumStepAngle;
        } else if (bOldAlphanumeric && !bAlphanumeric) {
            currentAngle += rotSettings->num2MultiStepAngle;
        } else {
            float angle = bAlphanumeric ? rotSettings->numStepAngle : rotSettings->multiStepAngle;
            currentAngle += angle;
        }
        
        SingleChar *char1 = new SingleChar(currentAngle, str);
        charsQue.push_back(char1);
        char1->alphanumeric = bAlphanumeric;
        tempStr.erase(0, kCharBytes);
        bOldAlphanumeric = bAlphanumeric;
    }
    
    textSpeechMode = TextSpeechModeSpeaking;
}

string RotationText::getCurrentText() {
    string result = "";
    
    for(auto itr = charsQue.begin(); itr != charsQue.end(); ++itr) {
        result += (*itr)->aChar;
    }
    return result;
}

std::vector<int> RotationText::search( std::string const & text, std::regex const & re ) {
    std::vector<int> result ;
    
    std::sregex_iterator iter( text.cbegin(), text.cend(), re ) ;
    std::sregex_iterator end ;
    
    for ( ; iter != end ; ++iter ) {
        for (int i = iter->position(); i < iter->length() + iter->position(); i++) {
            result.push_back(i);
        }
    }
    
    return result;
}

void RotationText::changeColor(TextSpeechMode mode) {
    textSpeechMode = mode;
    
    // √ã√¢‚â§‚Äû√á√≠√Ç¬ß√¢√ä√µ¬•‚Äû√Ö√¥‚Äû√á√£
    if (mode == TextSpeechModeAnalyzed) {
        string tempStr = getCurrentText();
        //        vector colorPos =
        std::regex re(analyzedString) ;
        std::string text(tempStr);
        vector <int> colorPos = search( text, re ) ;
        int bytes = 0;
        for(auto itr = charsQue.begin(); itr != charsQue.end(); ++itr) {
            vector<int>::iterator cIter = find( colorPos.begin(),colorPos.end(), bytes);
            
            if( cIter != colorPos.end() ){
                (*itr)->changeColor(rotSettings->highlightColor);
                (*itr)->changeOutlineColor(rotSettings->outlineHighlightColor);
                (*itr)->bAnalyzed = true;
            } else {
                (*itr)->changeColor(rotSettings->disableColor);
                (*itr)->changeOutlineColor(rotSettings->outlineDisableColor);
                (*itr)->bAnalyzed = false;
            }
            
            bytes += kCharBytes;
        }
    }
}

void RotationText::analyzed(string text) {
    analyzedString = utf8rev(text);
    changeColor(TextSpeechModeAnalyzed);
}

std::string RotationText::utf8rev(std::string str) {
    std::string r;
    
    unsigned char lead;
    int char_size = 0;
    
    for (std::string::iterator it = str.begin(); it != str.end(); it += char_size) {
        lead = *it;
        
        if (lead < 0x80) {
            char_size = 1;
        } else if (lead < 0xE0) {
            char_size = 2;
        } else if (lead < 0xF0) {
            char_size = 3;
        } else {
            char_size = 4;
        }
        r.insert(0, str.substr(distance(str.begin(), it), char_size));
    }
    return r;
}
