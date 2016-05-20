//
//  RotationTextManager.hpp
//  RotationText
//
//  Created by Mitstuya.WATANABE on 2016/05/18.
//
//

#ifndef RotationTextManager_hpp
#define RotationTextManager_hpp

#include <stdio.h>
#include "RotationText.h"

class RotationTextManager {
public:
    RotationTextManager();
    ~RotationTextManager();
    
    void update();
    void draw();
    // テキストを追加する
    void addText(string text);
    // 初期化する (新規テキストを挿入する前にからなず呼ぶ
    void refresh();
    // 新規テキストが挿入できるかどうかを調べる
    bool canAddNewText();
    void analyzed(string text);
    vector<RotationText *>rotTextQue;
    
    bool showLines;
};

#endif /* RotationTextManager_hpp */
