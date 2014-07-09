//
//  TagConfig.h
//  HelloCpp
//
//  Created by chao on 14-7-9.
//
//

#ifndef __HelloCpp__TagConfig__
#define __HelloCpp__TagConfig__

#include "cocos2d.h"

USING_NS_CC;

class TagConfig  {
public:
    
    static TagConfig * getInstance();
    static void purgeInstance();
    
protected:
    TagConfig();
    
    ~TagConfig();
    
    void init();
    
    static TagConfig * pInstance;
    
};

#endif /* defined(__HelloCpp__TagConfig__) */
