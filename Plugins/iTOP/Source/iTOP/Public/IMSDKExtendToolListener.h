/*!
 @header IMSDKExtendToolListener.h
 @abstract IMSDKExtendToolListener.h in IMSDK
 @author Created by yuanchengsu on 16/4/27.
 @versino 1.0.0
   Copyright © 2016年 Tencent. All rights reserved.
 */
#ifndef IMSDKExtendToolListener_H
#define IMSDKExtendToolListener_H
 
#include "IMSDKComm.h" 
#include "IMSDKJson.h"

class IMSDKExtendToolListener{
    
public:
    virtual void OninitUrlShceme(std::map<std::string,std::string>params){
        printf("you should override this function for your purpose");
    }

};

#endif
