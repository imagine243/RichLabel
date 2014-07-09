//
//  RichLabel.h
//  HelloCpp
//
//  Created by chao on 14-7-1.
//
//

#ifndef __HelloCpp__RichLabel__
#define __HelloCpp__RichLabel__

#include "cocos2d.h"
#include "StyleParser.h"

USING_NS_CC;

class TLineLabel : public CCNode {
public:
    TLineLabel();
    virtual ~TLineLabel();
    
    static TLineLabel * create();
    bool init();
    
    CCArray * nodeArray;
    
    void drawContent()	;
    
    CC_SYNTHESIZE(float, width, width);
    CC_SYNTHESIZE(float, height, height);
};

class RichLabel : public cocos2d::CCNode{
private:
    StyleParser * pParser;
    CCArray * lineArray;
    float leftWidth;
    CCSize contentSize;
public:
    
    RichLabel();
    virtual ~ RichLabel();
    
    static RichLabel * create(const char *string, const char *fontName, float fontSize,const CCSize& dimensions, CCTextAlignment hAlignment);
    
    bool init(const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment);
    
    virtual void setString(const char *label);
    
    void renderContent();
    void pushToContainer(CCNode * node);
    void addNewLine();
    
    void drawContent();
};

#endif /* defined(__HelloCpp__RichLabel__) */
