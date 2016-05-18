#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    text = "あいうえおabsあksldfじゅおい";
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
    switch (key) {
        case '1':
            s = "ああsfじ";
            break;
            
        case '2':
            s = "かっくいかsdふぉ";
            break;
            
        case '3':
            s = "さしすせふぉ";
            break;
            
        case 's':
            rotManager.refresh();
            newText = true;
            s = "newText";
            break;
            
        default:
            std::ostringstream sout;
            sout << key;
            s = sout.str();
            break;
    }
    
    if(newText) {
        if (rotManager.canAddNewText()) {
            rotManager.addText(s);
        } else {
            printf("\ncan not insert");
        }
        
    } else {
        rotManager.addText(s);
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
