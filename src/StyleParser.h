//
//  StyleParser.h
//  HelloCpp
//
//  Created by chao on 14-7-1.
//
//

#ifndef __HelloCpp__StyleParser__
#define __HelloCpp__StyleParser__

#include "cocos2d.h"
#include "TStyle.h"
#include "TStyleText.h"

USING_NS_CC;

class StyleParser :public cocos2d::CCObject {
private:
    cocos2d::CCArray * styleArray;
    std::string fontName;
    float fontSize;
    ccColor3B fontColor;
public:
    StyleParser();
    virtual ~StyleParser();
    
//    static StyleParser * create(const std::string &text);
//    bool init(const std::string &text);
    
    static StyleParser * create();
    bool init();
    
    void parser(const std::string &text);
    
    TStyleText * getDefautStyleText();
    
    TStyle * createStyle(std::string & beginTag);
    
    CCArray * getStyleArray();
    
    void setDefaultFontName(const std::string & fontName){this->fontName = fontName;};
    void setDefaultFontSize(float fontSize){this->fontSize = fontSize;};
    void setDefalutFontColor(ccColor3B fontColor){this->fontColor = fontColor;};
};

#endif /* defined(__HelloCpp__StyleParser__) */
