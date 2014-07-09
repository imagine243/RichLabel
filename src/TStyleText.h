//
//  TStyleText.h
//  HelloCpp
//
//  Created by chao on 14-7-1.
//
//

#ifndef __HelloCpp__TStyleText__
#define __HelloCpp__TStyleText__

#include "cocos2d.h"
#include "TStyle.h"

USING_NS_CC;

class TStyleText : public TStyle {
private:
    bool isBorder;
public:
    
    TStyleText():isBorder(false),color(ccBLACK),fontSize(20),fontName(""){};
    virtual ~TStyleText(){};
    
    static TStyleText * create();
    bool init();
    
    virtual bool parsePorperty(const std::string & proText);
    virtual TStyleType getType();
    virtual cocos2d::CCNode * createRender();
    
    CCLabelTTF * createLabelRender(const std::string & text);
    
    CCArray * splitRender(float width,float lineWidth,CCNode * node);

    virtual TStyle * clone();
    
    CC_SYNTHESIZE(ccColor3B,color,color);
    CC_SYNTHESIZE(std::string, fontName, fontName);
    CC_SYNTHESIZE(float, fontSize, fontSize);
    CC_SYNTHESIZE(ccColor3B, borderColor, borderColor);
};

#endif /* defined(__HelloCpp__TStyleText__) */
