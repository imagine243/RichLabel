#include "HelloWorldScene.h"
#include "AppMacros.h"
//#include "StyleParser.h"
#include "RichLabel.h"
#include "util.h"
#include "CsvParser.h"
USING_NS_CC;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
//    pLabel->enableStroke(ccBLACK, 2,true);
    pLabel->enableShadow(CCSizeMake(2, 2), 1, 1);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    std::string temp = "加三大哈佛阿萨德发<text color=666666 border=777777 >说的粉<text color=000000>上帝粉红色</text>红色的</text>";
    
//    StyleParser * parser = StyleParser::create();
//    parser->parser(temp);
    
    
    
    RichLabel * label = RichLabel::create(temp.c_str(), "", 20, CCSizeMake(500, 100), kCCTextAlignmentCenter);
    label->setPosition(ccp(0, visibleSize.height/2));
    this->addChild(label,10);
    
//    std::string text("加三大哈佛阿萨德发");
//    std::wstring wtext = utf8toUnicode(text);
//    wprintf(L"%ls\n",wtext.c_str());
//    std::string temp2 = unicodeToUtf8(wtext);
//    printf("%s\n",temp2.c_str());
    
    CsvParser * parser = CsvParser::create("file.csv");
    
    std::map<std::string, std::string> result = parser->findOne(2);
    
    CCLOG("tag 1 %s", result.at("tag1").c_str());
    CCLOG("tag 2 %s", result.at("tag2").c_str());
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
