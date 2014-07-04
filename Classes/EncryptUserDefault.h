//
//  EncryptUserDefault.h
//  BlackWings
//
//  Created by Jacky on 14-7-2.
//
//

#ifndef __BlackWings__EncryptUserDefault__
#define __BlackWings__EncryptUserDefault__

#include "cocos2d.h"

class EncryptUserDefault
{
public:
    static EncryptUserDefault* getInstance()
    {
        if ( m_pInstance == NULL )
            m_pInstance = new EncryptUserDefault();
        return m_pInstance;
    }
    
    //encrypt style
    bool _isKeyorValue;//true, use key; false, use value. default: true
    
    //setter
    void setBoolForKey(const char* pKey, bool value);
    void setIntegerForKey(const char* pKey, int value);
    void setFloatForKey(const char* pKey, float value);
    void setDoubleForKey(const char* pKey, double value);
    void setStringForKey(const char* pKey, const std::string & value);

    //getter
    bool getBoolForKey(const char* pKey);
    int getIntegerForKey(const char* pKey);
    float getFloatForKey(const char* pKey);
    double  getDoubleForKey(const char* pKey);
    std::string getStringForKey(const char* pKey);


private:
    
    EncryptUserDefault();
    
    static EncryptUserDefault* m_pInstance;
    
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (EncryptUserDefault::m_pInstance!=NULL)
            {
                delete EncryptUserDefault::m_pInstance;
            }
        }
    };
    
    static CGarbo m_garbo;
};

#endif /* defined(__BlackWings__EncryptUserDefault__) */
