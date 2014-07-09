//
//  StyleParser.cpp
//  HelloCpp
//
//  Created by chao on 14-7-1.
//
//

#include "StyleParser.h"


USING_NS_CC;

const char * BEGIN_MARK = "<";
const char * END_PRO_MARK = ">";
const char * END_MARK = "</";
//const char * BLANK_MARK = ;

const int MARK_LENGTH = 10;


StyleParser::StyleParser():styleArray(NULL),fontSize(20),fontName("Helvetica")
{
    
}

StyleParser::~StyleParser()
{
    CC_SAFE_RELEASE_NULL(styleArray);
}

StyleParser * StyleParser::create()
{
    StyleParser * pRet = new StyleParser();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool StyleParser::init()
{
    styleArray = CCArray::create();
    styleArray->retain();
    
//    this->parser(text);
    
    return true;
}

TStyle * StyleParser::createStyle(std::string & beginTag)
{
    if (beginTag == "<text") {
        TStyleText * style = TStyleText::create();
        style->setfontName(this->fontName);
        style->setfontSize(this->fontSize);
        style->setcolor(this->fontColor);
        return style;
    }
    
    return NULL;
}


void StyleParser::parser(const std::string &text)
{
    styleArray->removeAllObjects();
    int length = text.size();
    CCArray * styleStack = CCArray::create();
    
    int beginMarkPos = 0;
    int endMarkPos = 0;
    
    // 长度小于3的全部是文本
    if (length <= 3 || beginMarkPos == std::string::npos) {
        TStyleText * style = getDefautStyleText();
        style->setContent(text);
        styleArray->addObject(styleArray);
        return;
    }

    
    while (beginMarkPos < length) {
        beginMarkPos = text.find(BEGIN_MARK,endMarkPos);
        
        TStyle * style = NULL;
        
        if (beginMarkPos > endMarkPos) {
            std::string temp = text.substr(endMarkPos, beginMarkPos - endMarkPos);
            
            if (styleStack->count() > 0) {
                
                style = static_cast<TStyle *>(styleStack->lastObject())->clone();
            }else{
                style = getDefautStyleText();
            }
            
            CCLOG("begin text  %s",temp.c_str());
            style->setContent(temp);
            styleArray->addObject(style);
            
            endMarkPos = text.find(END_MARK, endMarkPos);
            
            if (beginMarkPos == endMarkPos){
                beginMarkPos = text.find(END_PRO_MARK, endMarkPos) + 1;
                endMarkPos = beginMarkPos;
                styleStack->removeLastObject();
            }else{
                endMarkPos = beginMarkPos;
            }
            
            continue;
        }else{
            int blankPos = text.find(' ', beginMarkPos);
            std::string beginTab = text.substr(beginMarkPos, blankPos - beginMarkPos);
            CCLOG("begin tab %s" , beginTab.c_str());
            
            style = createStyle(beginTab);
            
            int endPorMarkPos = text.find(END_PRO_MARK, blankPos);
            std::string proText = text.substr(beginMarkPos,endPorMarkPos - beginMarkPos + 1);
            CCLOG("pro text %s", proText.c_str());
            
            endMarkPos = beginMarkPos = endPorMarkPos;
            
            if (style && style->getType() == StyleTypeMark) {
                
                if (style->parsePorperty(proText)){
                    
                }
                
                beginMarkPos = endPorMarkPos + 1;
                endMarkPos = beginMarkPos;
                
            }else if (style && style->parsePorperty(proText)) {
                
                beginMarkPos = text.find(BEGIN_MARK, endPorMarkPos);
                endMarkPos = text.find(END_MARK, endPorMarkPos);
                
                if (beginMarkPos < endMarkPos) {
                    //新的标记
                    std::string content = text.substr(endPorMarkPos + 1, beginMarkPos - endPorMarkPos - 1);
                    
                    styleStack->addObject(style->clone());
                    
                    style->setContent(content);
                    CCLOG("content %s", content.c_str());
                    styleArray->addObject(style);
                    
                    endMarkPos = beginMarkPos;
                    
                    continue;
                }else{
                    std::string content = text.substr(endPorMarkPos + 1,endMarkPos - endPorMarkPos - 1);
                    style->setContent(content);
                    styleArray->addObject(style);
                    CCLOG("all content %s", content.c_str());
                    beginMarkPos = text.find(END_PRO_MARK, endMarkPos) + 1;
                    endMarkPos = beginMarkPos;
                    continue;
                    
                }
            }
        }
        
        
        
    }
    
    CCLOG("styleArray size %d ",styleArray->count());
    
}

TStyleText * StyleParser::getDefautStyleText()
{
    TStyleText * style = TStyleText::create();
    style->setcolor(this->fontColor);
    style->setfontName(this->fontName);
    style->setfontSize(this->fontSize);
    return style;
}


CCArray * StyleParser::getStyleArray()
{
    return styleArray;
}
