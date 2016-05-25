//
//  AppSettings.hpp
//  RotationText
//
//  Created by Mitstuya.WATANABE on 2016/05/24.
//
//

#ifndef AppSettings_hpp
#define AppSettings_hpp

#include <stdio.h>
#include "ofxXmlSettings.h"

/**
 *  This is singleton class for setting up parameters in this app
 */
class AppSettings {
private:
    AppSettings();
    ~AppSettings();
    ofxXmlSettings settings;
//    AppSettings(const AppSettings &x) { printf("\napp settengs **");};
//    AppSettings &operator=(const AppSettings &) { printf("\napp settengs **");return *this; };
    
public:
    static AppSettings &getInstance(void);
    
    template <typename T> T getValue(const string key, T temp){
        printf("\ngetParam default");
        return 0;
    }
};

#endif /* AppSettings_hpp */
