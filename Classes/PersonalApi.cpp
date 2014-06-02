//
//  PersonalApi.cpp
//  GreTest
//
//  Created by lyy on 13-6-14.
//
//

#include "PersonalApi.h"
#include "cocos2d.h"

using namespace cocos2d;

 vector<string> PersonalApi::split(string str,string pattern)
{
    string::size_type pos;
    vector<string> result;
    str+=pattern;
    int size=str.size();
    
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}


bool PersonalApi::isContantString(string sourceStr,string patternStr)
{
    const char *show;
    
    show=strstr(sourceStr.c_str(),patternStr.c_str()); 
    
    bool isContant;
    if (show == NULL)
    {
        isContant = false;
    }
    else
    {
        isContant = true;
    }
    
    return isContant;
}

size_t PersonalApi::SafeStringCopy(void* dest,size_t destLen,const char* src)
{
	size_t stringLen = strlen(src);
	size_t size=min(destLen-1,stringLen);
	memcpy(dest,src,size);
	((char*)dest)[size]='\0';
	return size;
}

string PersonalApi::string_replace(string & strBig, const string & strsrc, const string &strdst)
{
    string::size_type pos=0;
    string::size_type srclen=strsrc.size();
    string::size_type dstlen=strdst.size();
    
    while( (pos=strBig.find(strsrc, pos)) != string::npos)
    {
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
    
    return strBig;
}

string PersonalApi::convertIntToString (int aNum) //int ?? string
{
    ostringstream oss;
    oss<<aNum;
    return oss.str();
}
string PersonalApi::convertfloatToString (float aNum) //int ?? string
{
    ostringstream oss;
    oss<<aNum;
    return oss.str();
}
int PersonalApi::convertStringToInt (string aStr) //string ?? int
{
    return  atoi( aStr.c_str());
}

