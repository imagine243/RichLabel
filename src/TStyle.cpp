//
//  TStyle.cpp
//  HelloCpp
//
//  Created by chao on 14-7-1.
//
//

#include "TStyle.h"

void TStyle::setContent(const std::string & contentText)
{
    this->content = contentText;
}


bool TStyle::parsePorperty(const std::string & proText)
{
    return true;
}

TStyleType TStyle::getType()
{
    return StyleTypeContent;
}

cocos2d::CCNode * TStyle::createRender()
{
    return NULL;
}
TStyle * TStyle::clone()
{
    TStyle * style = new TStyle();
    style->release();
    
    style->content = this->content;
    return style;
    
}