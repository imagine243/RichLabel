//
//  RichLabel.cpp
//  HelloCpp
//
//  Created by chao on 14-7-1.
//
//

#include "RichLabel.h"

TLineLabel::TLineLabel():width(0),height(0),nodeArray(NULL)
{
    
}

TLineLabel::~TLineLabel()
{
    CC_SAFE_RELEASE_NULL(nodeArray);
}

TLineLabel * TLineLabel::create()
{
    TLineLabel * pRet = new TLineLabel();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool TLineLabel::init()
{
    if (CCNode::init()) {
        
        nodeArray = CCArray::create();
        nodeArray->retain();
        return true;
    }
    return false;
}

void TLineLabel::drawContent()
{
    CCObject * object = NULL;
    CCARRAY_FOREACH(this->nodeArray, object)
    {
        CCNode * node = static_cast<CCNode *>(object);
        node->setAnchorPoint(ccp(0, 0));
        node->setPosition(ccp(this->width, 0));
        this->addChild(node);
        
        CCSize size = node->getContentSize();
        
        this->width = this->width + size.width;
        
        if (size.height > this->height) {
            this->height = size.height;
        }
    }
}


RichLabel::RichLabel():pParser(NULL),lineArray(NULL)
{
    
}

RichLabel::~RichLabel()
{
    CC_SAFE_RELEASE_NULL(pParser);
    CC_SAFE_RELEASE_NULL(lineArray);
}

RichLabel * RichLabel::create(const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment)
{
    RichLabel * pRet = new RichLabel();
    if (pRet && pRet->init(string, fontName, fontSize, dimensions, hAlignment)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool RichLabel::init(const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment)
{
    if (CCNode::init()) {
        
        contentSize = dimensions;
        
        pParser = StyleParser::create();
        pParser->retain();
        pParser->setDefalutFontColor(ccWHITE);
        pParser->setDefaultFontName(fontName);
        pParser->setDefaultFontSize(fontSize);
        
        pParser->parser(string);
        
        lineArray = CCArray::create();
        lineArray->retain();
        
        
        this->renderContent();
        
        this->drawContent();
        return true;
    }
    return false;
}

void RichLabel::setString(const char *label)
{
    
}

void RichLabel::addNewLine()
{
    TLineLabel * line = TLineLabel::create();
    lineArray->addObject(line);
    leftWidth = contentSize.width;
}

void RichLabel::pushToContainer(CCNode * node)
{
    if (lineArray->count() <= 0) {
        return;
    }
    
    TLineLabel * line = static_cast<TLineLabel *>(lineArray->lastObject());
    line->nodeArray->addObject(node);
}

void RichLabel::renderContent()
{
    CCArray * styleArray = pParser->getStyleArray();
    
    CCObject * object = NULL;
    addNewLine();
    CCARRAY_FOREACH(styleArray, object)
    {
        TStyle * style = static_cast<TStyle *>(object);
        
        CCLOG("style content %s",style->content.c_str());
        
        int type = style->getType();
        
        CCNode * node = style->createRender();
        
        CCSize size = node->getContentSize();
        
        this->leftWidth -= size.width;
        
        if (this->leftWidth < 0) {
            
            if (style->getType() == StyleTypeContent) {
                
                TStyleText * styleText = static_cast<TStyleText *>(style);
                CCArray * textArray = styleText->splitRender(size.width + this->leftWidth, this->contentSize.width,node);
                
                CCNode * node = static_cast<CCNode *>(textArray->objectAtIndex(0));
                pushToContainer(node);
                
                
                for (int i = 1; i < textArray->count(); i++) {
                    addNewLine();
                    CCNode * temp = static_cast<CCNode *>(textArray->objectAtIndex(1));
                    pushToContainer(temp);
                    continue;
                }
                
            }else if (style->getType() == StyleTypeMark){
                this->addNewLine();
                this->leftWidth -= size.width;
                pushToContainer(node);
                continue;
            }
            
        }else {
            pushToContainer(node);
            continue;
        }
        
    }
}

void RichLabel::drawContent()
{
    float height = this->contentSize.height;
    CCObject * object = NULL;
    CCARRAY_FOREACH(this->lineArray, object)
    {
        TLineLabel * line = static_cast<TLineLabel *>(object);
        line->drawContent();
        height -= line->getheight();
        line->setPosition(ccp(0, height));
        this->addChild(line);
    }
}

