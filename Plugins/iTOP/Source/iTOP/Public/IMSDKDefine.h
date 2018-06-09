//
// Created by dandiliu on 17/10/13.
//

#ifndef IMSDK_ANDROID_IMSDKDEFINE_H
#define IMSDK_ANDROID_IMSDKDEFINE_H

#include "IMSDKComm.h" 

typedef void (*ResultDelegate)(IMSDKResult &result);

typedef void (*MetaDataDelegate)(std::string str, int tag, ResultDelegate callback);


#endif //IMSDK_ANDROID_IMSDKDEFINE_H


