#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    text = "あいうえおabsあksldfじゅおい";
    rotText.setup(text);

//    printf("\n text = %s", rotText.sampleString.c_str());
//    rotText.sampleString.erase(0, 3);
//    printf("\n text = %s", rotText.sampleString.c_str());
    
    
    //空白を削除する場合
    string testString = " a b c あ ";
    for(size_t c = testString.find_first_of(" "); c != string::npos; c = c = testString.find_first_of(" ")){
        testString.erase(c,1);
    }
    printf("\n%s\n",testString.c_str());
    
    //空白とeを削除する場合
    testString = " a eb c eあ ";
    for(size_t c = testString.find_first_of(" e"); c != string::npos; c = c = testString.find_first_of(" e")){
        testString.erase(c,1);
    }
    printf("\n%s\n",testString.c_str());
}

//--------------------------------------------------------------
void ofApp::update(){
    rotText.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    rotText.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    std::ostringstream sout;
    sout << key;
    text += sout.str();
    rotText.sampleString = text;
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
