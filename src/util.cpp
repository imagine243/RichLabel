//
//  util.cpp
//  HelloCpp
//
//  Created by chao on 14-7-4.
//
//

#include "util.h"

void split(const std::string& src, const std::string& separator, std::vector<std::string>& dest)
{
    std::string str = src;
    std::string substring;
    std::string::size_type start = 0, index;
    
    do
    {
        index = str.find_first_of(separator,start);
        if (index != std::string::npos)
        {
            substring = str.substr(start,index-start);
            substring = trim(substring);
            dest.push_back(substring);
            start = str.find_first_not_of(separator,index);
            if (start == std::string::npos) return;
        }
    }while(index != std::string::npos);
    
    //the last token
    substring = str.substr(start);
    substring = trim(substring);
    dest.push_back(substring);
}

std::string trim(std::string &s)
{
    if (s.length() == 0) return s;
    size_t beg = s.find_first_not_of(" ");
    size_t end = s.find_last_not_of(" ");
    if (beg == std::string::npos){
        return "";
    }
    
    s = s.substr(beg,end - beg + 1);
    return s;
}


ccColor3B str2color(const char *hexColor)
{
    ccColor3B labColor;
    std::string colorStr = hexColor;
    if(colorStr.length() < 6)
    {
        labColor = ccBLACK;
        return labColor;
    }
    
    std::string redStr = colorStr.substr(0, 2);
    int red = hexToInt(redStr.c_str());
    colorStr.erase(0, 2);
    
    std::string greenStr = colorStr.substr(0, 2);
    int green = hexToInt(greenStr.c_str());
    colorStr.erase(0, 2);
    
    std::string blueStr = colorStr.substr(0, 2);
    int blue = hexToInt(blueStr.c_str());
    colorStr.erase(0, 2);
    
    labColor = ccc3(red, green, blue);
    return labColor;
}

/**
 *	@brief	十六进制表示字符串转换未十进制整数
 *
 *	@param 	str 	十六进制字符串
 *
 *	@return	return 十进制整数
 */
int hexToInt(const char *str)
{
    std::string string = str;
    std::string charStr = "0123456789abcdefABCDEF";
    int size = string.length();
    if (size <= 0) {
        return 0;
    }
    int *charArray = new int[size];
    for (int index = 0; index < size; index++) {
        int location = charStr.find(string[index]);
        if (location >= 0) {
            if (location >= 16) {
                location -= 6;
            }
        }else{
            //未找到
            location = 0;
        }
        charArray[index] = location;
    }
    
    int value = 0;
    for (int index = 0; index < size; index++) {
        int valueOne = charArray[index];
        value += (1<<(4*(size-1-index)))*valueOne;
    }
    
    delete [] charArray;
    
    return value;
}

std::wstring utf8toUnicode(const std::string & text)
{
    int sSize = text.size();
    
    wchar_t * wBuf = NULL;
    
    setlocale(LC_CTYPE, "");
    
    int wSize = mbstowcs(wBuf, text.c_str(), 0) + 1;
    
    wBuf = new wchar_t[wSize];
    wmemset(wBuf, 0, wSize);
    
    int ret = mbstowcs(wBuf, text.c_str(), sSize);
    
    if (ret <= 0) {
        std::wstring wText;
        return wText;
    }else{
        std::wstring wText(wBuf);
        return wText;
    }
    
//    wchar_t wcs[text.size() + 1];
//    
//    setlocale(LC_CTYPE, "");
//    mbstowcs(wcs, text.c_str(), text.size());
//    
//    std::wstring newText(wcs);
//    return newText;
}


std::string unicodeToUtf8(const std::wstring & wText)
{
    int wSize = wText.size();
    
    char * sBuf = NULL;
    
    int sSize = wcstombs(sBuf, wText.c_str(), 0) + 1;
    
    sBuf = new char[sSize];
    memset(sBuf, 0, sSize);
    
    int ret = wcstombs(sBuf, wText.c_str(), wSize);
    if (ret <= 0) {
        std::string text;
        return text;
    }else{
        std::string text(sBuf);
        return text;
    }
    
}
