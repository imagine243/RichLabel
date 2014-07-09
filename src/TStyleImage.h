//
//  TStyleImage.h
//  HelloCpp
//
//  Created by chao on 14-7-3.
//
//

#ifndef __HelloCpp__TStyleImage__
#define __HelloCpp__TStyleImage__

#include "cocos2d.h"
#include "TStyle.h"

USING_NS_CC;

class TStyleImage : public TStyle{
public:
    
    TStyleImage(){};
    virtual ~TStyleImage(){};
    
    static TStyleImage * create();
    bool init();
    
    virtual bool parsePorperty(const std::string & proText);
    virtual TStyleType getType();};


#endif /* defined(__HelloCpp__TStyleImage__) */
