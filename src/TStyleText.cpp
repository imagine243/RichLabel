//
//  TStyleText.cpp
//  HelloCpp
//
//  Created by chao on 14-7-1.
//
//

#include "TStyleText.h"
#include "util.h"

#define TYPE_EQUAL  "="
#define TYPE_BLANK  " "
#define TYPE_COLOR  "color"
#define TYPE_BORDER "border"

TStyleText * TStyleText::create()
{
    TStyleText * pRet = new TStyleText();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool TStyleText::init()
{
    return true;
}

bool TStyleText::parsePorperty(const std::string & proText)
{
    std::vector<std::string> proVector;
    split(proText,TYPE_BLANK, proVector);
    
    int size = proVector.size();
    for (int i = 0; i < size; i++) {
        if (proVector[i].find(TYPE_EQUAL, 0) > 0) {
            std::vector<std::string> keyVector;
            split(proVector[i], TYPE_EQUAL, keyVector);
            if (keyVector.size() != 2) {
                continue;
            }
            
            if (keyVector[0] == TYPE_COLOR) {
                color = str2color(keyVector[1].c_str());
                CCLOG("color %s",keyVector[1].c_str());
            }
            
            if (keyVector[0] == TYPE_BORDER) {
                borderColor = str2color(keyVector[1].c_str());
                this->isBorder = true;
                CCLOG("border color %s",keyVector[1].c_str());
            }
        }
    }
    
    return true;
}

TStyleType TStyleText::getType()
{
    return StyleTypeContent;
}

cocos2d::CCNode * TStyleText::createRender()
{
    return createLabelRender(this->content);
}


CCLabelTTF * TStyleText::createLabelRender(const std::string & text)
{
    CCLabelTTF * render = CCLabelTTF::create(this->content.c_str(), this->fontName.c_str(), this->fontSize);
    
    render->setColor(this->color);
    
    return render;
}

CCArray * TStyleText::splitRender(float width,float lineWidth,CCNode * node)
{
    CCArray * array = CCArray::create();
    
    CCSize size = node->getContentSize();
    
    std::wstring wContent = utf8toUnicode(this->content);
    
    float totalWidth = size.width;
    int contentLength = wContent.size();
    int num = width/totalWidth * contentLength;
    
    if (num > 0){
        std::wstring firstWContent = wContent.substr(0,num);
        std::string firstContent = unicodeToUtf8(firstWContent);
        CCLabelTTF * firstLabel = createLabelRender(firstContent);
        
        array->addObject(firstLabel);
    }
    
    for(int i = 1 ; width + lineWidth * i < totalWidth; i++) {
        int num2 = lineWidth/totalWidth * contentLength;
        
        if (num2 > 0) {
            std::wstring sencondWContent = wContent.substr(num,num2);
            std::string secondContent = unicodeToUtf8(sencondWContent);
            CCLabelTTF * secondLabel = createLabelRender(secondContent);
            
            num = num + num2;
            array->addObject(secondLabel);
        }
    }
    
    int lastNum = contentLength - num;
    if (lastNum > 0) {
        std::wstring lastWContent = wContent.substr(num, lastNum);
        std::string lastContent = unicodeToUtf8(lastWContent);
        CCLabelTTF * lastLabel = createLabelRender(lastContent);
        array->addObject(lastLabel);
    }
    
    return array;
}


TStyle * TStyleText::clone()
{
    TStyleText * style = TStyleText::create();
    style->isBorder = this->isBorder;
    style->setcolor(this->color);
    style->setborderColor(this->borderColor);
    style->setfontName(this->fontName);
    style->setfontSize(this->fontSize);
    return style;
}
