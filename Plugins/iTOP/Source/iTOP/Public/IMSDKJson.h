
#ifndef IMSDK_ANDROID_IMSDKJSON_H
#define IMSDK_ANDROID_IMSDKJSON_H

#include "IMSDKComm.h" 
#include "iTOPStruct.h"
#if PLATFORM_ANDROID
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#endif

//利用ue4的接口进行json解析将结构体转换和iOS对齐
#if PLATFORM_ANDROID
IMSDKLoginResult convertiTOPBaseLoginResult(std::string _jsonData);
IMSDKLoginResult convertiTOPLoginResult(std::string _jsonData);
IMSDKLoginResult convertiTOPQuickLoginResult(std::string _jsonData);
IMSDKLoginResult convertiTOPBindResult(std::string _jsonData);
IMSDKLocationInfo convertiTOPLbsResult(std::string _jsonData);
IMSDKBindInfo convertiTOPGetBindResult(std::string _jsonData);
IMSDKAuthConnectResult convertiTOPAuthConnectResult(std::string _jsonData);
IMSDKResult convertiTOPResult(std::string _jsonData);
IMSDKNoticeResult convertiTOPNoticeResult(std::string _jsonData);
IMSDKAuthResult convertiTOPAuthResult(std::string _jsonData);
IMSDKAuthMigrateResult convertiTOPAuthMigrateResult(std::string _jsonData); 
IMSDKWebViewTicketResult convertiTOPWebViewTicketResult(std::string _jsonData);
IMWebViewStatusResult convertiTOPWebViewStatusResult(std::string _jsonData);  
IMSDKFriendResult convertFriendResultFromJson(std::string json);
#endif 
#endif //IMSDK_ANDROID_IMSDKJSON_H


