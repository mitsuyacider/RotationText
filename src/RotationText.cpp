//
//  RotationText.cpp
//  TextRotation
//
//  Created by Mitstuya.WATANABE on 2016/04/19.
//
//

#include "RotationText.h"

RotationText::RotationText(FieldType type) {
    rotSettings = &RotationSettings::getInstance();
    myFont.loadFont("Meiryo.ttf", rotSettings->fontSize, true, true);
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
        // MEMO: auto„ÅØÂûãÊé®Ë´ñ„Çâ„Åó„ÅÑ
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
            if ((*itr)->angle > startAngle && (*itr)->angle < endAngle) {
                ofSetColor((*itr)->color);
            }
            
            myFont.drawString((*itr)->aChar, 0, 0);
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
    
    int bytes = 1;
    int oldBytes = 1;
    
    float currentAngle = 0.0;
    if (charsQue.empty()) {
        // NOTE: AÈ†òÂüü, BÈ†òÂüü„Åß„ÄÅÁèæÂú®ÊèèÁîª„Åß„Åç„ÇãÈ†òÂüü„Çí„Åø„ÇãÂøÖË¶Å„Åå„ÅÇ„Çã„ÄÇ
        currentAngle = startAngle;
    } else {
        SingleChar *lastChar = charsQue.back();
        bool hasNum = isalnum(*lastChar->aChar.c_str());
        oldBytes = hasNum ? 1 : 3;
        currentAngle = lastChar->angle;
    }
    
    while(!tempStr.empty()) {
        // √Ç√ß√§√ã√ü√≠√ã√£¬±√ä√Ø‚àû√Ç‚â†√≥‚Äû√Ö√£‚Äû√Ö¬©‚Äû√Ö√ú‚Äû√Ö√£‚Äû√á√≠√Ç√†¬ß√Ç√†‚Ä¢‚Äû√Ö√¥‚Äû√á√£
        bool hasNum = isalnum(*tempStr.substr(0, 1).c_str());
        
        bytes = hasNum ? 1 : 3;
        str = tempStr.substr(0, bytes);
        
        // NOTE: ÂçäËßíËã±Êï∞Â≠ó„Å®„Éû„É´„ÉÅ„Éê„Ç§„ÉàÊñáÂ≠ó„ÅÆÂ§â„Çè„ÇäÁõÆ„Å´„Çπ„Éö„Éº„Çπ„ÅåÁ©∫„Åç„Åô„Åé„Å¶„Åó„Åæ„ÅÜ„Åü„ÇÅ„ÄÅ
        //       È†≠„Å®„ÅäÂ∞ª„ÅÆ„Çπ„Éö„Éº„Çπ„ÇíË™øÊï¥„Åô„ÇãÂøÖË¶Å„Åå„ÅÇ„Çã„ÄÇ
        if (oldBytes == 3 && bytes == 1) {
            // ÂâçÂõû„ÅÆÊñáÂ≠ó„Åå„Éû„É´„ÉÅ„Éê„Ç§„Éà„ÅÆÂ†¥Âêà („Éû„É´„ÉÅ„Éê„Ç§„Éà -> ÂçäËßíËã±Êï∞Â≠ó)
            currentAngle += rotSettings->multi2NumStepAngle;
        } else if (oldBytes == 1 && bytes == 3) {
            // ÂâçÂõû„ÅÆÊñáÂ≠ó„ÅåÂçäËßíËã±Êï∞Â≠ó„ÅÆÂ†¥Âêà (ÂçäËßíËã±Êï∞Â≠ó -> „Éû„É´„ÉÅ„Éê„Ç§„Éà)
            currentAngle += rotSettings->num2MultiStepAngle;
        } else {
            float angle = hasNum ? rotSettings->numStepAngle : rotSettings->multiStepAngle;
            currentAngle += angle;
        }
        
        SingleChar *char1 = new SingleChar(currentAngle, str);
        charsQue.push_back(char1);
        
        tempStr.erase(0, bytes);
        oldBytes = bytes;
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
    
    // Ëâ≤„ÇíÂ§âÊõ¥„Åô„Çã
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
                (*itr)->bAnalyzed = true;
            } else {
                (*itr)->changeColor(rotSettings->disableColor);
                (*itr)->bAnalyzed = false;
            }
            bytes += (*itr)->bytes;
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
