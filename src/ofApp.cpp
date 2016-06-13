#include "ofApp.h"
#include "AppSettings.hpp"
#include <regex>

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    text = "ｃ＋＋にｃ＃を弾いて－したところのｃ言語というのはｏｂｊｅｃｔｉｖｅｃ";
    
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
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    string s;
    bool newText = false;
    bool analyzed = false;
    switch (key) {
        case '1':
            s = "ÊòéÊó•„ÅØ";
            break;
            
        case '2':
            s = "ÊòéÊó•„ÅØ„ÅÑ„ÅÑÂ§©Ê∞ó";
            break;
            
        case '3':
            s = "ÊòéÊó•„ÅØ„ÅÑ„ÅÑÂ§©Ê∞ó„Å´„Å™„Çã„Å®„ÅÑ„ÅÑ";
            break;

        case '4':
            s = "ÊòéÊó•„ÅØ„ÅÑ„ÅÑÂ§©Ê∞ó„Å®„ÅÑ„ÅÜ";
            break;

        case '5':
            s = "ÊòéÊó•„ÅØ„ÅÑ„ÅÑÂ§©Ê∞ó„Å´„Å™„Çã„Å®„ÅÑ„ÅÑ„Å™„ÄÇ„Çπ„Ç±„Ç∏„É•„Éº„É´„Çí";
            break;

        case '6':
            s = "ÊòéÊó•„ÅØ„ÅÑ„ÅÑÂ§©Ê∞ó„Å´„Å™„Çã„Å®„ÅÑ„ÅÑ„Å™„ÄÇ„Çπ„Ç±„Ç∏„É•„Éº„É´„ÇíÁ¢∫Ë™ç„Åó„Å¶Tokyo„Å´„Åß„ÇÇÈÅä„Å≥„Å´Ë°å„Åì„ÅÜ";
            break;

            
        case 's':
            rotManager.swap();
            newText = true;
            s = "newText";
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
