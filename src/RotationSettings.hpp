//
//  RotationSettings.hpp
//  RotationText
//
//  Created by Mitstuya.WATANABE on 2016/05/25.
//
//

#ifndef RotationSettings_hpp
#define RotationSettings_hpp

#include <stdio.h>

#pragma once
#include "AppSettings.hpp"


static const float kMultiStepAngle = 4.8;     // „Éû„É´„ÉÅ„Éê„Ç§„Éà
static const float kNum2MultiStepAngle = 5.8; // ÂçäËßíËã±Êï∞Â≠ó -> „Éû„É´„ÉÅ„Éê„Ç§„Éà
static const float kNumStepAngle = 2.8;       // ÂçäËßíËã±Êï∞Â≠ó
static const float kMulti2NumStepAngle = 5.0; // „Éû„É´„ÉÅ„Éê„Ç§„Éà -> ÂçäËßíËã±Êï∞Â≠ó
static const float kRadius = 300.0;
static const int kFontSize = 20;
static const int kFieldMarginAngle = 10;
static const string kHighlightColor = "0xff0000"; // ÂΩ¢ÊÖãÁ¥†Ëß£Êûê„Åï„Çå„ÅüÊñáÂ≠ó„ÅÆËâ≤
static const string kDisableColor = "0x646464"; // ÂΩ¢ÊÖãÁ¥†Ëß
static const float kRotationSpeed = 0.2;
static const int kFadeDuration = 2000;
static const string kOutlineColor = "0xff0000";
static const string kOutlineHighlightColor = "0xff0000";
static const string kOutlineDisableColor = "0x646464";

static const float kOutlineWidth = 1.0;

class RotationSettings {
private:
    RotationSettings(void) {
        AppSettings *settings = &AppSettings::getInstance();
        
        speed = settings->getValue("TextRotation:Speed", kRotationSpeed);
        multiStepAngle = settings->getValue("TextRotation:MultiStepAngle", kMultiStepAngle);
        numStepAngle = settings->getValue("TextRotation:NumStepAngle", kNumStepAngle);
        multi2NumStepAngle = settings->getValue("TextRotation:Multi2NumStepAngle", kMulti2NumStepAngle);
        num2MultiStepAngle = settings->getValue("TextRotation:Num2MultiStepAngle", kNum2MultiStepAngle);
        radius = settings->getValue("TextRotation:Radius", kRadius);
        fontSize = settings->getValue("TextRotation:FontSize", kFontSize);
        fieldMarginAngle = settings->getValue("TextRotation:FieldMarginAngle", kFieldMarginAngle);
        
        
        int highlightHex = std::stoi(settings->getValue("TextRotation:HighlightColor", kHighlightColor), nullptr, 16);
        int disableHex = std::stoi(settings->getValue("TextRotation:DisableColor", kDisableColor), nullptr, 16);
        int outlineHex = std::stoi(settings->getValue("TextRotation:OutlineColor", kOutlineColor), nullptr, 16);
        int outlineHighlightHex = std::stoi(settings->getValue("TextRotation:OutlineHighlightColor", kOutlineHighlightColor), nullptr, 16);
        int outlineDisableHex = std::stoi(settings->getValue("TextRotation:OutlineDisableColor", kOutlineDisableColor), nullptr, 16);
        highlightColor = highlightHex;
        disableColor = disableHex;
        outlineColor = outlineHex;
        outlineHighlightColor = outlineHighlightHex;
        outlineDisableColor = outlineDisableHex;
        
        outlineWidth = kOutlineWidth;
        fadeDuration = settings->getValue("TextRotation:FadeDuration", kFadeDuration);
    };
    ~RotationSettings() {};

    
public:
    static RotationSettings &getInstance(void) {
        static RotationSettings singleton;
        return singleton;
    };

    float speed;
    float multiStepAngle;
    float numStepAngle;
    float multi2NumStepAngle;
    float num2MultiStepAngle;
    float radius;
    float fontSize;
    float fieldMarginAngle;
    float outlineWidth;
    int highlightColor;
    int disableColor;
    int fadeDuration;
    int outlineColor;
    int outlineHighlightColor;
    int outlineDisableColor;
};
#endif /* RotationSettings_hpp */
