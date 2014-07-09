//
//  TStyleImage.cpp
//  HelloCpp
//
//  Created by chao on 14-7-3.
//
//

#include "TStyleImage.h"

TStyleImage * TStyleImage::create()
{
    TStyleImage * pRet = new TStyleImage();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool TStyleImage::init()
{
    return true;
}


bool TStyleImage::parsePorperty(const std::string & proText)
{
    return true;
}

TStyleType TStyleImage::getType()
{
    return StyleTypeMark;
}