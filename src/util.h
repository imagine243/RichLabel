//
//  util.h
//  HelloCpp
//
//  Created by chao on 14-7-4.
//
//

#ifndef __HelloCpp__util__
#define __HelloCpp__util__

#include "cocos2d.h"

USING_NS_CC;

void split(const std::string& src, const std::string& separator, std::vector<std::string>& dest);

std::string trim(std::string &s);

ccColor3B str2color(const char *hexColor);

/**
 *	@brief	十六进制表示字符串转换未十进制整数
 *
 *	@param 	str 	十六进制字符串
 *
 *	@return	return 十进制整数
 */
int hexToInt(const char *str);


std::wstring utf8toUnicode(const std::string & text);

std::string unicodeToUtf8(const std::wstring & wText);

#endif /* defined(__HelloCpp__util__) */
