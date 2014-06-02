//
//  PersonalApi.h
//  GreTest
//
//  Created by lyy on 13-6-14.
//
//

#ifndef __GreTest__PersonalApi__
#define __GreTest__PersonalApi__

#include<vector>
#include<string>
#include<cstdio>
#include <sstream>
#include<map>
#include "cocos2d.h"
using namespace std;

class PersonalApi
{
public:
    
    static vector<string> split(string str,string pattern);//◊÷∑˚¥Æ∑÷∏Ó
    static bool isContantString(string sourceStr,string patternStr);//≈–∂œ“ª∏ˆ◊÷∑˚¥Æ «∑Ò∞¸∫¨¡ÌÕ‚“ª∏ˆ
    static size_t SafeStringCopy(void* dest,size_t destLen,const char* src);
    static string string_replace(string & strBig, const string & strsrc, const string &strdst);//◊÷∑˚¥ÆÃÊªª
    static string convertIntToString (int aNum); //int ◊™ string
    static string convertfloatToString (float aNum);
    static int convertStringToInt (string aStr); //string ◊™ int
  
};

#endif /* defined(__GreTest__PersonalApi__) */
