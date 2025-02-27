//
//  EncryptUserDefault.cpp
//  BlackWings
//
//  Created by Jacky on 14-7-2.
//
//

#include "EncryptUserDefault.h"
USING_NS_CC;

static const std::string dataChars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

bool baseData(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string SaveData(unsigned char const* bytes_to_encode, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for(i = 0; (i <4) ; i++)
                ret += dataChars[char_array_4[i]];
            i = 0;
        }
    }
    
    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        
        for (j = 0; (j < i + 1); j++)
            ret += dataChars[char_array_4[j]];
        
        while((i++ < 3))
            ret += '=';
        
    }
    
    return ret;
    
}

std::string ParseData(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    
    while (in_len-- && ( encoded_string[in_] != '=') && baseData(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = dataChars.find(char_array_4[i]);
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        
        for (j = 0; j <4; j++)
            char_array_4[j] = dataChars.find(char_array_4[j]);
        
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    
    return ret;
}

EncryptUserDefault* EncryptUserDefault::m_pInstance=NULL;
EncryptUserDefault::CGarbo EncryptUserDefault::m_garbo;

EncryptUserDefault::EncryptUserDefault()
{
    _isKeyorValue = true;
}

void EncryptUserDefault::setIntegerForKey(const char* pKey, int value)
{
    char buffer[50];
    sprintf(buffer,"%d",value);
    std::string data = buffer;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
    if(_isKeyorValue)
        UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    else
        UserDefault::getInstance()->setStringForKey(pKey, data);
}

void EncryptUserDefault::setBoolForKey(const char* pKey, bool value)
{
//    char buffer[50];
//    sprintf(buffer,"%d",value);
//    std::string data = buffer;
//    std::string key = pKey;
//    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
//    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
//    if(_isKeyorValue)
//        UserDefault::getInstance()->setStringForKey(key.c_str(), data);
//    else
//        UserDefault::getInstance()->setStringForKey(pKey, data);
    
    if (value) {
        setIntegerForKey(pKey, 1);
    }
    else
        setIntegerForKey(pKey, 0);
}

void EncryptUserDefault::setFloatForKey(const char* pKey, float value)
{
    char buffer[50];
    sprintf(buffer,"%f",value);
    std::string data = buffer;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
    if(_isKeyorValue)
        UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    else
        UserDefault::getInstance()->setStringForKey(pKey, data);
}

void EncryptUserDefault::setDoubleForKey(const char* pKey, double value)
{    char buffer[50];
    sprintf(buffer,"%lf",value);
    std::string data = buffer;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
    if(_isKeyorValue)
        UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    else
        UserDefault::getInstance()->setStringForKey(pKey, data);
}

void EncryptUserDefault::setStringForKey(const char* pKey, const std::string & value)
{
    std::string data = value;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
    if(_isKeyorValue)
        UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    else
        UserDefault::getInstance()->setStringForKey(pKey, data);
}

int EncryptUserDefault::getIntegerForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data;
    if(_isKeyorValue)
        data = UserDefault::getInstance()->getStringForKey(key.c_str());
    else
        data = UserDefault::getInstance()->getStringForKey(pKey);
    data = ParseData(data);
    return Value(data.c_str()).asInt();
}

bool EncryptUserDefault::getBoolForKey(const char* pKey)
{
//    std::string key = pKey;
//    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
//    std::string data;
//    if(_isKeyorValue)
//        data = UserDefault::getInstance()->getStringForKey(key.c_str());
//    else
//        data = UserDefault::getInstance()->getStringForKey(pKey);
//    data = ParseData(data);
//    return Value(data.c_str()).asBool();
    return Value(getIntegerForKey(pKey)).asBool();
}

float EncryptUserDefault::getFloatForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data;
    if(_isKeyorValue)
        data = UserDefault::getInstance()->getStringForKey(key.c_str());
    else
        data = UserDefault::getInstance()->getStringForKey(pKey);
    data = ParseData(data);
    return Value(data.c_str()).asFloat();
}

double EncryptUserDefault::getDoubleForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data;
    if(_isKeyorValue)
        data = UserDefault::getInstance()->getStringForKey(key.c_str());
    else
        data = UserDefault::getInstance()->getStringForKey(pKey);
    data = ParseData(data);
    return Value(data.c_str()).asDouble();
}

std::string EncryptUserDefault::getStringForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data;
    if(_isKeyorValue)
        data = UserDefault::getInstance()->getStringForKey(key.c_str());
    else
        data = UserDefault::getInstance()->getStringForKey(pKey);
    data = ParseData(data);
    return data;
}
