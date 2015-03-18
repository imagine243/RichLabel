//
//  TStyle.h
//  HelloCpp
//
//  Created by chao on 14-7-1.
//
//

#ifndef __HelloCpp__TStyle__
#define __HelloCpp__TStyle__

#include "cocos2d.h"

typedef enum {
    StyleTypeContent,
    StyleTypeMark
} TStyleType ;

class TStyle : public cocos2d::CCObject{
public:
    TStyle(){};
    virtual ~TStyle(){};
    
    virtual bool parsePorperty(const std::string & proText);
    virtual void setContent(const std::string & contentText);
    virtual TStyleType getType();
    virtual cocos2d::CCNode * createRender();
    virtual TStyle * clone();
    virtual std::string toString();
    std::string content;
protected:
};


#endif /* defined(__HelloCpp__TStyle__) */
