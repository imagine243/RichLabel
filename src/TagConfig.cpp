//
//  TagConfig.cpp
//  HelloCpp
//
//  Created by chao on 14-7-9.
//
//

#include "TagConfig.h"
#include "CsvParser.h"

TagConfig *  TagConfig::pInstance = NULL;

TagConfig::TagConfig()
{
    
}

TagConfig::~TagConfig()
{
    
}

TagConfig * TagConfig::getInstance()
{
    if (pInstance == NULL) {
        pInstance = new TagConfig();
    }
    return pInstance;
}

void TagConfig::purgeInstance()
{
    if (pInstance) {
        delete pInstance;
    }
}

void TagConfig::init()
{
    CsvParser * textParser = CsvParser::create(const char *filename);
    CsvParser * soundParser = CsvParser::create(<#const char *filename#>);
}


