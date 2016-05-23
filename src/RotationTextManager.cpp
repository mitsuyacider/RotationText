//
//  RotationTextManager.cpp
//  RotationText
//
//  Created by Mitstuya.WATANABE on 2016/05/18.
//
//

#include "RotationTextManager.hpp"

RotationTextManager::RotationTextManager() {

    RotationText *rotTxtA = new RotationText(FieldTypeA);
    RotationText *rotTxtB = new RotationText(FieldTypeB);
    rotTextQue.push_back(rotTxtA);
    rotTextQue.push_back(rotTxtB);
    
    showLines = false;
}

RotationTextManager:: ~RotationTextManager() {
    
}

void RotationTextManager::update() {
    for(auto itr = rotTextQue.begin(); itr != rotTextQue.end(); ++itr) {
        (*itr)->update();
//        if ((*itr)->textSpeechMode != TextSpeechModeReady) {
//            (*itr)->update();
//        }
    }
}

void RotationTextManager::draw() {
    for(auto itr = rotTextQue.begin(); itr != rotTextQue.end(); ++itr) {
        (*itr)->draw();
//        if ((*itr)->textSpeechMode != TextSpeechModeReady) {
//            (*itr)->draw();
//        }
    }
}

void RotationTextManager::setText(string text) {
    RotationText *rotT = rotTextQue.front();
    rotT->setText(text);
}

void RotationTextManager::swap() {
    // NOTE: 領域の入れ替えを行う。
    std::swap(rotTextQue[0], rotTextQue[1]);
}

bool RotationTextManager::canAddNewText() {
    for(auto itr = rotTextQue.begin(); itr != rotTextQue.end(); ++itr) {
        if ((*itr)->textSpeechMode == TextSpeechModeReady) {
            return true;
        }
    }
    
    return false;
}

void RotationTextManager::analyzed(string text) {
    RotationText *rotT = rotTextQue.front();
    rotT->analyzed(text);
//    rotT->changeColor(TextSpeechModeAnalyzed);
}
