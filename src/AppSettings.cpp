//
//  AppSettings.cpp
//  RotationText
//
//  Created by Mitstuya.WATANABE on 2016/05/24.
//
//

#include "AppSettings.hpp"

// NOTE: This private constractor is called only once.
//       Read a xml file to set up parameter
AppSettings::AppSettings(void) {
    
    printf("\nappsettengs");

    if(!settings.load("settings.xml")){
        ofLogError("\nsettings.xml did not loaded!");
    }
}

AppSettings::~AppSettings() {
    
}

AppSettings &AppSettings::getInstance(void) {
    static AppSettings singleton;
    
    return singleton;
}


// --------- template -------
// NOTE: the value from xml node is unpredictable value.
int AppSettings::getValue(const string key, int temp){
    printf("\nkey = %s", key.c_str());
    return settings.getValue(key, temp);
}

double AppSettings::getValue(const string key, double temp){
    return settings.getValue(key, temp);
}

float AppSettings::getValue(const string key, float temp){
    return settings.getValue(key, temp);
}

string AppSettings::getValue(const string key, string temp){
    return settings.getValue(key, temp);
}
