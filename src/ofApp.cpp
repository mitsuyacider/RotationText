#include "ofApp.h"
#include "AppSettings.hpp"
#include <regex>

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    text = "１０月２２にちｗｉｎｄｏｗｓとかｇｏｏｇｌｅとかＣ＃％ｏｂｊｅｃｔｉｖｅｃ１０％";
    
//    std::regex re("^[０１２３４５６７８９ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ]+$");
//    std::string text("ｂ") ;
//    bool result = std::regex_match( text, re ) ;
//    if (result) printf("\ndetect!!");
    
//    int color = 0xff0000;
//    int r = (color& 0xff0000) >> 16;
//    int g = (color& 0xff00) >> 8;
//    int b = (color& 0xff);
    
//    std::regex re( R"(\d+)" ) ;
//    std::string text="There are 99 bottles." ;
//    
//    std::smatch m ; // std::match_results<string::const_iterator>
//    std::regex_search( text, m, re ) ;
//    
//    std::cout << m.str() << "****" << std::endl ;
    
    AppSettings *settings = &AppSettings::getInstance();
    rotManager.setText(text);
}
//--------------------------------------------------------------
void ofApp::update(){
    rotManager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    rotManager.draw();
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() / 2, ofGetHeight() / 2);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    string s;
    bool newText = false;
    bool analyzed = false;
    switch (key) {
        case '1':
            newText = true;
            s = "あいうえお";
            break;
            
        case '2':
            newText = true;
            s = "あいうえおかきくけお";
            break;
            
        case '3':
            newText = true;
            s = "あいうえおかきくけこかさいあおう";
            break;

        case '4':
            newText = true;
            s = "あいうえおかきくけこさしすせそたちつけてａｌｄｓｇｏｕ";
            break;

        case '5':
            newText = true;
            s = "１０月２２にちｗｉｎｄｏｗｓとかｇｏｏｇｌｅとかＣ＃％ｏｂｊｅｃｔｉｖｅｃ１０％";
            break;

        case '6':
            newText = true;
            s = "";
            break;

            
        case 's':
            rotManager.swap();
            newText = true;
            s = "ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ１２３４５６７８９０";
            break;
        
        case'a':
            break;
            
        case'b': {
            analyzed = true;
            string s = "ｏｂｊｅｃｔｉｖｅｃ";
            rotManager.analyzed(s);
        }
            break;

        default:
            std::ostringstream sout;
            sout << key;
            s = sout.str();
            break;
    }
    
    if (!analyzed) {
        if(newText) {
            if (rotManager.canAddNewText()) {
                rotManager.setText(s);
            } else {
                printf("\ncan not insert");
            }
            
        } else {
//            rotManager.setText(s);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    printf("\n text = %s", rotText.sampleString.c_str());
//    rotText.sampleString.erase(0, 3);
//    printf("\n text = %s", rotText.sampleString.c_str());
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
